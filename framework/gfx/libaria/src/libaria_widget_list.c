#include "gfx/libaria/inc/libaria_widget_list.h"

#if LA_LIST_WIDGET_ENABLED && LA_SCROLLBAR_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define DEFAULT_WIDTH           100
#define DEFAULT_HEIGHT          100

#define DEFAULT_SCROLL_WIDTH    20
#define DEFAULT_STEP_SIZE       10

#define DEFAULT_MARGIN          10

static void resized(laListWidget* lst);
static void recalculateScrollBarValues(laListWidget* lst);
static void scrollBarMoved(laScrollBarWidget* bar);
static uint32_t getRowAtPoint(laListWidget* lst, GFX_Point* pnt);


static void touchDown(laListWidget* lst, laInput_TouchDownEvent* evt);
static void touchUp(laListWidget* lst, laInput_TouchUpEvent* evt);
static void touchMoved(laListWidget* lst, laInput_TouchMovedEvent* evt);

void _laListWidget_Constructor(laListWidget* lst)
{
	_laWidget_Constructor((laWidget*)lst);
	
	lst->widget.destructor = (laWidget_Destructor_FnPtr)&_laListWidget_Destructor;

	lst->widget.type = LA_WIDGET_LIST;

	// override base class methods
	lst->widget.paint = (laWidget_Paint_FnPtr)&_laListWidget_Paint;
	lst->widget.resized = (laWidget_Resized_FnPtr)&resized;

    lst->widget.touchDown = (laWidget_TouchDownEvent_FnPtr)&touchDown;
	lst->widget.touchUp = (laWidget_TouchUpEvent_FnPtr)&touchUp;
	lst->widget.touchMoved = (laWidget_TouchMovedEvent_FnPtr)&touchMoved;

	lst->widget.rect.width = DEFAULT_WIDTH;
	lst->widget.rect.height = DEFAULT_HEIGHT;

	lst->widget.borderType = LA_WIDGET_BORDER_BEVEL;
	lst->widget.drawBackground = LA_TRUE;
	lst->itemDown = -1;
	//lst->allowEmpty = LA_TRUE;
	lst->mode = LA_LIST_WIDGET_SELECTION_MODE_CONTIGUOUS;
	

	//laString_Initialize(&lst->text);
	
	laList_Create(&lst->items);
	
	// create scrollbar
	_laScrollBarWidget_Constructor(&lst->scrollbar);
	laScrollBarWidget_SetValueChangedEventCallback(&lst->scrollbar, &scrollBarMoved);
	
	laWidget_AddChild((laWidget*)lst, (laWidget*)&lst->scrollbar);
	
	laWidget_SetSize((laWidget*)&lst->scrollbar,
	                 DEFAULT_SCROLL_WIDTH,
	                 lst->widget.rect.height);
	                 
	laWidget_SetPosition((laWidget*)&lst->scrollbar,
                         lst->widget.rect.width - DEFAULT_SCROLL_WIDTH,
                         0);
                         
    laScrollBarWidget_SetStepSize(&lst->scrollbar, DEFAULT_STEP_SIZE);
                         
    recalculateScrollBarValues(lst);
	
	lst->halign = LA_HALIGN_LEFT;
	lst->iconMargin = DEFAULT_MARGIN;
	//lst->scrollBarWidth = DEFAULT_SCROLL_WIDTH;
}

void _laListWidget_Destructor(laListWidget* lst)
{
	//laString_Destroy(&lst->text);
	
	// free all item memory
	laListWidget_RemoveAllItems(lst);
	
	// free any existing memory reader
	if(lst->reader != NULL)
	{
	    laContext_GetActive()->memIntf.heap.free(lst->reader);
	    
	    lst->reader = NULL;
	}

	_laWidget_Destructor((laWidget*)lst);
}

laListWidget* laListWidget_New()
{
	laListWidget* lst = NULL;

	if(laContext_GetActive() == NULL)
		return NULL;

	lst = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laListWidget));

	_laListWidget_Constructor(lst);

	return lst;
}

void _laListWidget_GetRowRect(laListWidget* lst,
                              uint32_t idx,
                              GFX_Rect* rect)
{
    GFX_Rect textRect;
    
    laListItem* item;
    
    // get list item
    item = laList_Get(&lst->items, idx);

    // get text rectangle
    laString_GetRect(&item->string, &textRect);
    
    // craft item entry rectangle
    rect->x = 0;
    rect->width = lst->widget.rect.width;
    
    if(lst->scrollbar.widget.visible == LA_TRUE)
        rect->width -= lst->scrollbar.widget.rect.width;
        
    rect->y = 0;
    rect->height = textRect.height +
                   lst->widget.margin.top +
                   lst->widget.margin.bottom;
}

int32_t _laListWidget_GetRowY(laListWidget* lst, uint32_t idx)
{
    uint32_t row;
    int32_t y = 0;
    GFX_Rect rect;
    
    //rect.x = 0;
    //rect.y = 0;
    //rect->width = lst->widget.rect.width;
    //rect->height = 0;
    
    for(row = 0; row < idx - 1; row++)
    {
        _laListWidget_GetRowRect(lst, row, &rect);
        
        y += rect.height;
    }
    
    return y;
}

void _laListWidget_GetLogicalRect(laListWidget* lst, GFX_Rect* rect)
{
    uint32_t idx;
    GFX_Rect row;
    
    rect->x = 0;
    rect->y = 0;
    rect->width = lst->widget.rect.width;
    rect->height = 0;
    
    for(idx = 0; idx < lst->items.size; idx++)
    {
        _laListWidget_GetRowRect(lst, idx, &row);
        
        rect->height += row.height;
    }
}

uint32_t getRowAtPoint(laListWidget* lst, GFX_Point* pnt)
{
    GFX_Point local = *pnt;
    uint32_t idx;
    GFX_Rect row;
    uint32_t y = 0;
    
    laUtils_PointScreenToLocalSpace((laWidget*)lst, &local);
    
    for(idx = 0; idx < lst->items.size; idx++)
    {
        _laListWidget_GetRowRect(lst, idx, &row);
        
        row.y += y - lst->scrollbar.value;
        
        if(GFX_RectContainsPoint(&row, &local) == GFX_TRUE)
            return idx;
            
        y += row.height;
    }
    
    return -1;
}

static void resized(laListWidget* lst)
{
    laWidget_SetSize((laWidget*)&lst->scrollbar,
                     lst->scrollbar.widget.rect.width,
                     lst->widget.rect.height);
                     
    laWidget_SetPosition((laWidget*)&lst->scrollbar,
                         lst->widget.rect.width - lst->scrollbar.widget.rect.width,
                         0);
}

static void recalculateScrollBarValues(laListWidget* lst)
{
    GFX_Rect totalRect;
    
    _laListWidget_GetLogicalRect(lst, &totalRect);
    
    if(totalRect.height < lst->widget.rect.height)
    {
        laWidget_SetVisible((laWidget*)&lst->scrollbar, LA_FALSE);
    }
    else
    {
        laWidget_SetVisible((laWidget*)&lst->scrollbar, LA_TRUE);
        laScrollBarWidget_SetMaximumValue(&lst->scrollbar, totalRect.height - lst->widget.rect.height);
    }
    
    laWidget_Invalidate((laWidget*)lst);
}

static void scrollBarMoved(laScrollBarWidget* bar)
{
    laWidget_Invalidate((laWidget*)bar->widget.parent);
}

static void touchDown(laListWidget* lst, laInput_TouchDownEvent* evt)
{
    GFX_Point pnt;
    uint32_t idx;
    
    pnt.x = evt->x;
    pnt.y = evt->y;
    
    idx = getRowAtPoint(lst, &pnt);
    
    if(idx >= 0 && idx < lst->items.size)
    {
        lst->itemDown = idx;
        
        laWidget_Invalidate((laWidget*)lst);
    }
    else if(lst->itemDown != -1)
    {
        lst->itemDown = -1;
     
        laWidget_Invalidate((laWidget*)lst);
    }   
	
	evt->event.accepted = LA_TRUE;
}

static void touchUp(laListWidget* lst, laInput_TouchUpEvent* evt)
{
	GFX_Point pnt;
    uint32_t idx;
    
    pnt.x = evt->x;
    pnt.y = evt->y;
    
    idx = getRowAtPoint(lst, &pnt);
    
    if(idx == lst->itemDown)
        laListWidget_ToggleItemSelected(lst, idx); 
        
    lst->itemDown = -1;

	evt->event.accepted = LA_TRUE;

	laWidget_Invalidate((laWidget*)lst);
}

static void touchMoved(laListWidget* lst, laInput_TouchMovedEvent* evt)
{
	GFX_Point pnt;
    uint32_t idx;
    
    pnt.x = evt->x;
    pnt.y = evt->y;
    
    idx = getRowAtPoint(lst, &pnt);
    
    if(idx >= 0 && idx < lst->items.size)
    {
        lst->itemDown = idx;
        
        laWidget_Invalidate((laWidget*)lst);
    }
    else if(lst->itemDown != -1)
    {
        lst->itemDown = -1;
     
        laWidget_Invalidate((laWidget*)lst);
    }   
	
	evt->event.accepted = LA_TRUE;
}

laListWidget_SelectionMode laListWidget_GetSelectionMode(laListWidget* lst)
{
    if(lst == NULL)
		return LA_LIST_WIDGET_SELECTION_MODE_SINGLE;
		
    return lst->mode;
}

laResult laListWidget_SetSelectionMode(laListWidget* lst, 
                                       laListWidget_SelectionMode mode)
{
    if(lst == NULL)
        return LA_FAILURE;
        
    if(lst->mode == mode)
        return LA_SUCCESS;
        
    lst->mode = mode;
    
    laListWidget_DeselectAll(lst);
        
    return LA_SUCCESS;
}

laBool laListWidget_GetAllowEmptySelection(laListWidget* lst)
{
    if(lst == NULL)
        return LA_FALSE;
    
    return lst->allowEmpty;
}

laResult laListWidget_SetAllowEmptySelection(laListWidget* lst, laBool allow)
{
    if(lst == NULL)
        return LA_FAILURE;
        
    if(lst->allowEmpty == allow)
        return LA_SUCCESS;
        
    lst->allowEmpty = allow;
    
    // automatically select if needed
    if(allow == LA_FALSE && laListWidget_GetSelectionCount(lst) == 0)
        laListWidget_SetItemSelected(lst, 0, LA_TRUE);
        
    return LA_SUCCESS;
}

laHAlignment laListWidget_GetAlignment(laListWidget* lst)
{
	if(lst == NULL)
		return 0;

	return lst->halign;
}

laResult laListWidget_SetAlignment(laListWidget* lst, laHAlignment align)
{
	if(lst == NULL)
        return LA_FAILURE;
        
    if(lst->halign == align)
		return LA_SUCCESS;

	lst->halign = align;

	laWidget_Invalidate((laWidget*)lst);
	
	return LA_SUCCESS;
}

laRelativePosition laListWidget_GetIconPosition(laListWidget* lst)
{
    if(lst == NULL)
		return 0;

	return lst->iconPos;
}
                                               
laResult laListWidget_SetIconPosition(laListWidget* lst,
                                      laRelativePosition pos)
{
    if(lst == NULL ||
       (pos != LA_RELATIVE_POSITION_LEFTOF && pos != LA_RELATIVE_POSITION_RIGHTOF))
        return LA_FAILURE;
        
    if(lst->iconPos == pos)
		return LA_SUCCESS;

	lst->iconPos = pos;

	laWidget_Invalidate((laWidget*)lst);
	
	return LA_SUCCESS;
}

uint32_t laListWidget_GetIconMargin(laListWidget* lst)
{
    if(lst == NULL)
		return 0;

	return lst->iconMargin;
}
                                               
laResult laListWidget_SetIconMargin(laListWidget* lst, uint32_t mg)
{
    if(lst == NULL)
        return LA_FAILURE;
        
    if(lst->iconMargin == mg)
		return LA_SUCCESS;

	lst->iconMargin = mg;

	laWidget_Invalidate((laWidget*)lst);
	
	return LA_SUCCESS;
}
                                                        
uint32_t laListWidget_GetItemCount(laListWidget* lst)
{
    if(lst == NULL)
		return 0;

	return lst->items.size;
}

uint32_t laListWidget_AppendItem(laListWidget* lst)
{
    laListItem* item;
    
    if(lst == NULL)
        return -1;
        
    item = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laListItem));
    
    if(item == NULL)
        return -1;
        
    laString_Initialize(&item->string);
    
    laList_PushBack(&lst->items, item);
    
    if(lst->allowEmpty == LA_FALSE && laListWidget_GetSelectionCount(lst) == 0)
        laListWidget_SetItemSelected(lst, lst->items.size - 1, LA_TRUE);
    
    recalculateScrollBarValues(lst);
        
    return lst->items.size - 1;
}

uint32_t laListWidget_InsertItem(laListWidget* lst, uint32_t idx)
{
    laListItem* item;
    
    if(lst == NULL)
        return -1;
        
    item = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laListItem));
    
    if(item == NULL)
        return -1;
        
    laString_Initialize(&item->string);
    
    laList_InsertAt(&lst->items, item, idx);
    
    if(lst->allowEmpty == LA_FALSE && laListWidget_GetSelectionCount(lst) == 0)
        laListWidget_SetItemSelected(lst, idx, LA_TRUE);
    
    recalculateScrollBarValues(lst);
        
    return idx;
}

laResult laListWidget_RemoveItem(laListWidget* lst, uint32_t idx)
{
    laResult res;
    laListItem* item;
    
    if(lst == NULL)
        return LA_FAILURE;
        
    item = laList_Get(&lst->items, idx);
    
    if(item == NULL)
        return LA_FAILURE;
    
    laString_Destroy(&item->string);
        
    res = laList_RemoveAt(&lst->items, idx);
    
    laContext_GetActive()->memIntf.heap.free(item);

    if(res == LA_SUCCESS)
	    laWidget_Invalidate((laWidget*)lst);
	    
	recalculateScrollBarValues(lst);
	
	return res;
}

void laListWidget_RemoveAllItems(laListWidget* lst)
{
    laListItem* item;
    
    if(lst == NULL)
        return;
        
    while(lst->items.size > 0)
    {
        item = laList_Get(&lst->items, 0);
    
        laString_Destroy(&item->string);
    
        if(item != NULL)
            laContext_GetActive()->memIntf.heap.free(item);
        
        laList_RemoveAt(&lst->items, 0);
    }
        
    laWidget_Invalidate((laWidget*)lst);
	    
	recalculateScrollBarValues(lst);
}

laBool laListWidget_GetItemSelected(laListWidget* lst, uint32_t idx)
{
    laListItem* item;
    
    if(lst == NULL)
        return LA_FALSE;
    
    item = (laListItem*)laList_Get(&lst->items, idx);
    
    if(item == NULL)
        return LA_FALSE;
        
    return item->selected;
}

laResult laListWidget_SetItemSelected(laListWidget* lst,
                                      uint32_t idx,
                                      laBool selected)
{
    laListItem* item;
    uint32_t firstIdx, lastIdx, count;
    
    if(lst == NULL || idx == -1 || idx >= lst->items.size)
        return LA_FAILURE;
        
    count = laListWidget_GetSelectionCount(lst);
        
    item = (laListItem*)laList_Get(&lst->items, idx);
        
    if(item == NULL)
        return LA_FAILURE;
        
    // nothing to do
    if(item->selected == selected)
        return LA_SUCCESS;
        
    if(lst->mode == LA_LIST_WIDGET_SELECTION_MODE_SINGLE)
    {
        if(lst->allowEmpty == LA_FALSE && selected == LA_FALSE)
            return LA_FAILURE;
          
        if(count > 0)  
            laListWidget_DeselectAll(lst);
    
        item->selected = selected;
        
        if(lst->cb != NULL)
            lst->cb(lst, idx, selected);
    }
    else if(lst->mode == LA_LIST_WIDGET_SELECTION_MODE_MULTIPLE)
    {
        if(lst->allowEmpty == LA_FALSE &&
           selected == LA_FALSE &&
           laListWidget_GetSelectionCount(lst) == 1)
            return LA_FAILURE;
            
        item = laList_Get(&lst->items, idx);
        
        item->selected = selected;
        
        if(lst->cb != NULL)
            lst->cb(lst, idx, selected);
    }
    else if(lst->mode == LA_LIST_WIDGET_SELECTION_MODE_CONTIGUOUS)
    {
        if(lst->allowEmpty == LA_FALSE &&
           selected == LA_FALSE &&
           laListWidget_GetSelectionCount(lst) == 1)
            return LA_FAILURE;
            
        // empty selection case
        if(count == 0 && selected == LA_TRUE)
        {
            item->selected = selected;
            
            if(lst->cb != NULL)
                lst->cb(lst, idx, selected);
        }
        // test range
        else
        {
            firstIdx = laListWidget_GetFirstSelectedItem(lst);
            lastIdx = laListWidget_GetLastSelectedItem(lst);
        
            if(selected == LA_TRUE)
            {
                // selection is contiguous, add to selection        
                if(idx == firstIdx - 1 || idx == lastIdx + 1)
                {
                    item->selected = selected;
                
                    if(lst->cb != NULL)
                        lst->cb(lst, idx, selected);
                }
                // outside of range, deselect all and select target
                else
                {
                    laListWidget_DeselectAll(lst);
                    
                    item->selected = selected;
            
                    if(lst->cb != NULL)
                        lst->cb(lst, idx, selected);
                }
            }
            else
            {
                // selection is contiguous, remove from end caps        
                if(idx == firstIdx || idx == lastIdx)
                {
                    item->selected = selected;
                
                    if(lst->cb != NULL)
                        lst->cb(lst, idx, selected);
                }
                // outside of range, deselect all and select target
                else
                {
                    laListWidget_DeselectAll(lst);
                    
                    if(lst->allowEmpty == LA_FALSE)
                    {
                        item->selected = LA_TRUE;
                
                        if(lst->cb != NULL)
                            lst->cb(lst, idx, LA_TRUE);
                    }
                }
            }
        }
    }
        
    laWidget_Invalidate((laWidget*)lst);
        
    return LA_SUCCESS;
}
                                                 
laResult laListWidget_ToggleItemSelected(laListWidget* lst,
                                         uint32_t idx)
{
    laListItem* item;
    
    if(lst == NULL)
        return LA_FAILURE;
    
    item = (laListItem*)laList_Get(&lst->items, idx);
    
    if(item == NULL)
        return LA_FAILURE;
        
    return laListWidget_SetItemSelected(lst, idx, !item->selected);
}

void laListWidget_SelectAll(laListWidget* lst)
{
    laListItem* item;
    uint32_t i;
    uint32_t count = 0;
    
    if(lst == NULL)
        return;
        
    if(lst->mode == LA_LIST_WIDGET_SELECTION_MODE_SINGLE)
    {
        laListWidget_SetItemSelected(lst, 0, LA_TRUE);
        
        return;
    }
    
    for(i = 0; i < lst->items.size; i++)
    {
        item = laList_Get(&lst->items, i);
        
        if(item->selected == LA_FALSE)
        {
            item->selected = LA_TRUE;
            
            if(lst->cb != NULL)
                lst->cb(lst, i, LA_TRUE);
                
            count++;
        }
    }
    
    if(count > 0)
        laWidget_Invalidate((laWidget*)lst);
}

void laListWidget_DeselectAll(laListWidget* lst)
{
    laListItem* item;
    uint32_t i;
    uint32_t count = 0;
    
    for(i = 0; i < lst->items.size; i++)
    {
        item = laList_Get(&lst->items, i);
        
        if(item->selected == LA_TRUE)
        {
            item->selected = LA_FALSE;
            
            if(lst->cb != NULL)
                lst->cb(lst, i, LA_FALSE);
                
            count++;
        }
    }
    
    if(count > 0)
        laWidget_Invalidate((laWidget*)lst);
}

uint32_t laListWidget_GetFirstSelectedItem(laListWidget* lst)
{
    uint32_t idx;
    laListItem* item;
    
    for(idx = 0; idx < lst->items.size; idx++)
    {
        item = laList_Get(&lst->items, idx);
        
        if(item->selected == LA_TRUE)
            return idx;
    }
    
    return -1;
}

uint32_t laListWidget_GetLastSelectedItem(laListWidget* lst)
{
    uint32_t idx;
    uint32_t last = -1;
    laListItem* item;
    
    for(idx = 0; idx < lst->items.size; idx++)
    {
        item = laList_Get(&lst->items, idx);
        
        if(item->selected == LA_TRUE)
            last = idx;
    }
    
    return last;
}

uint32_t laListWidget_GetSelectionCount(laListWidget* lst)
{
    uint32_t idx, count = 0;
    laListItem* item;
    
    for(idx = 0; idx < lst->items.size; idx++)
    {
        item = laList_Get(&lst->items, idx);
        
        if(item->selected == LA_TRUE)
            count++;
    }
    
    return count;
}



void laListWidget_GetItemText(laListWidget* lst, uint32_t idx, laString* str)
{
    laListItem* item;
    
    if(lst == NULL || idx >= lst->items.size)
        return;
        
    item = laList_Get(&lst->items, idx);
    
    laString_Copy(str, &item->string);
}
                                               
void laListWidget_SetItemText(laListWidget* lst,
                              uint32_t idx,
                              laString str)
{
    laListItem* item;
    
    if(lst == NULL || idx >= lst->items.size)
        return;
       
    item = laList_Get(&lst->items, idx);
    
    laString_Copy(&item->string, &str);
    
    laWidget_Invalidate((laWidget*)lst);
    
    recalculateScrollBarValues(lst);
}
                                               
GFXU_ImageAsset* laListWidget_GetItemIcon(laListWidget* lst,
                                          uint32_t idx)
{
    laListItem* item;
    
    if(lst == NULL || idx >= lst->items.size)
        return NULL;
        
    item = laList_Get(&lst->items, idx);
        
    return item->icon;
}
                                                              
void laListWidget_SetItemIcon(laListWidget* lst,
                              uint32_t idx,
							  GFXU_ImageAsset* img)
{
    laListItem* item;
    
    if(lst == NULL || idx >= lst->items.size)
        return;
        
    item = laList_Get(&lst->items, idx);
        
    item->icon = img;
    
    laWidget_Invalidate((laWidget*)lst);
}

void laListWidget_SetItemVisible(laListWidget* lst, uint32_t idx)
{
    int32_t y;
    
    if(lst == NULL || idx >= lst->items.size)
        return;
        
    y = _laListWidget_GetRowY(lst, idx);
   
    laScrollBarWidget_SetScrollValue(&lst->scrollbar, y);
}

laListWidget_SelectedItemChangedEvent laListWidget_GetSelectedItemChangedEventCallback(laListWidget* lst)
{
	if(lst == NULL)
		return NULL;

	return lst->cb;
}

void laListWidget_SetSelectedItemChangedEventCallback(laListWidget* lst,
													  laListWidget_SelectedItemChangedEvent cb)
{
	if(lst == NULL || lst->cb == cb)
		return;

	lst->cb = cb;
}

#endif // LA_LIST_WIDGET_ENABLED && LA_SCROLLBAR_WIDGET_ENABLED