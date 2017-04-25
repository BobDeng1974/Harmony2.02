#include "gfx/libaria/inc/libaria_widget_listwheel.h"

#if LA_LISTWHEEL_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define DEFAULT_WIDTH           100
#define DEFAULT_HEIGHT          100

#define DEFAULT_MARGIN          10

#define SCROLL_DIVISOR          5

static void touchDown(laListWheelWidget* whl, laInput_TouchDownEvent* evt);
static void touchUp(laListWheelWidget* whl, laInput_TouchUpEvent* evt);
static void touchMoved(laListWheelWidget* whl, laInput_TouchMovedEvent* evt);

void _laListWheelWidget_Constructor(laListWheelWidget* whl)
{
	_laWidget_Constructor((laWidget*)whl);
	
	whl->widget.destructor = (laWidget_Destructor_FnPtr)&_laListWheelWidget_Destructor;

	whl->widget.type = LA_WIDGET_LIST;

	// override base class methods
	whl->widget.paint = (laWidget_Paint_FnPtr)&_laListWheelWidget_Paint;

    whl->widget.touchDown = (laWidget_TouchDownEvent_FnPtr)&touchDown;
	whl->widget.touchUp = (laWidget_TouchUpEvent_FnPtr)&touchUp;
	whl->widget.touchMoved = (laWidget_TouchMovedEvent_FnPtr)&touchMoved;

	whl->widget.rect.width = DEFAULT_WIDTH;
	whl->widget.rect.height = DEFAULT_HEIGHT;

	whl->widget.borderType = LA_WIDGET_BORDER_BEVEL;
	whl->widget.drawBackground = LA_TRUE;
	whl->itemDown = -1;
	//whl->allowEmpty = LA_TRUE;
	

	//laString_Initialize(&whl->text);
	
	laList_Create(&whl->items);
	
	whl->halign = LA_HALIGN_CENTER;
	whl->iconMargin = DEFAULT_MARGIN;
	//whl->scrollBarWidth = DEFAULT_SCROLL_WIDTH;
}

void _laListWheelWidget_Destructor(laListWheelWidget* whl)
{
    // destroy all items
	laListWheelWidget_RemoveAllItems(whl);
	
	// free any existing memory reader
	if(whl->reader != NULL)
	{
	    laContext_GetActive()->memIntf.heap.free(whl->reader);
	    
	    whl->reader = NULL;
	}

	_laWidget_Destructor((laWidget*)whl);
}

laListWheelWidget* laListWheelWidget_New()
{
	laListWheelWidget* whl = NULL;

	if(laContext_GetActive() == NULL)
		return NULL;

	whl = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laListWheelWidget));

	_laListWheelWidget_Constructor(whl);

	return whl;
}

static void touchDown(laListWheelWidget* whl, laInput_TouchDownEvent* evt)
{
    whl->touchY = evt->y;
    
    evt->event.accepted = LA_TRUE;
}

static void touchUp(laListWheelWidget* whl, laInput_TouchUpEvent* evt)
{
	evt->event.accepted = LA_TRUE;
}

static void touchMoved(laListWheelWidget* whl, laInput_TouchMovedEvent* evt)
{
    GFX_Rect rect = whl->widget.rect;
    
    rect.x = 0;
    rect.y = 0;
    
    laUtils_ClipRectToParent((laWidget*)whl, &rect);
	laUtils_RectToScreenSpace((laWidget*)whl, &rect);
    
    //printf("%i, %i, %i\n", evt->y, whl->touchY, evt->y - whl->touchY);

    if(evt->y - whl->touchY >= whl->widget.rect.height / SCROLL_DIVISOR ||
       evt->y - whl->touchY <= -(whl->widget.rect.height / SCROLL_DIVISOR))
    {
        if(evt->y < whl->touchY)
            laListWheelWidget_SelectNextItem(whl);
        else
            laListWheelWidget_SelectPreviousItem(whl);
            
        whl->touchY = evt->y;
    }
	
	evt->event.accepted = LA_TRUE;
}

laHAlignment laListWheelWidget_GetAlignment(laListWheelWidget* whl)
{
	if(whl == NULL)
		return 0;

	return whl->halign;
}

laResult laListWheelWidget_SetAlignment(laListWheelWidget* whl, laHAlignment align)
{
	if(whl == NULL)
        return LA_FAILURE;
        
    if(whl->halign == align)
		return LA_SUCCESS;

	whl->halign = align;

	laWidget_Invalidate((laWidget*)whl);
	
	return LA_SUCCESS;
}

laRelativePosition laListWheelWidget_GetIconPosition(laListWheelWidget* whl)
{
    if(whl == NULL)
		return 0;

	return whl->iconPos;
}
                                               
laResult laListWheelWidget_SetIconPosition(laListWheelWidget* whl,
                                      laRelativePosition pos)
{
    if(whl == NULL ||
       (pos != LA_RELATIVE_POSITION_LEFTOF && pos != LA_RELATIVE_POSITION_RIGHTOF))
        return LA_FAILURE;
        
    if(whl->iconPos == pos)
		return LA_SUCCESS;

	whl->iconPos = pos;

	laWidget_Invalidate((laWidget*)whl);
	
	return LA_SUCCESS;
}

uint32_t laListWheelWidget_GetIconMargin(laListWheelWidget* whl)
{
    if(whl == NULL)
		return 0;

	return whl->iconMargin;
}
                                               
laResult laListWheelWidget_SetIconMargin(laListWheelWidget* whl, uint32_t mg)
{
    if(whl == NULL)
        return LA_FAILURE;
        
    if(whl->iconMargin == mg)
		return LA_SUCCESS;

	whl->iconMargin = mg;

	laWidget_Invalidate((laWidget*)whl);
	
	return LA_SUCCESS;
}
                                                        
uint32_t laListWheelWidget_GetItemCount(laListWheelWidget* whl)
{
    if(whl == NULL)
		return 0;

	return whl->items.size;
}

uint32_t laListWheelWidget_AppendItem(laListWheelWidget* whl)
{
    laListWheelItem* item;
    
    if(whl == NULL)
        return -1;
        
    item = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laListWheelItem));
    
    if(item == NULL)
        return -1;
        
    laString_Initialize(&item->string);
    
    laList_PushBack(&whl->items, item);
    
    if(whl->items.size == 1)
        whl->selectedItem = 0;
    
    return whl->items.size - 1;
}

uint32_t laListWheelWidget_InsertItem(laListWheelWidget* whl, uint32_t idx)
{
    laListWheelItem* item;
    
    if(whl == NULL)
        return -1;
        
    item = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laListWheelItem));
    
    if(item == NULL)
        return -1;
        
    laString_Initialize(&item->string);
    
    laList_InsertAt(&whl->items, item, idx);
    
    if(whl->items.size == 1)
        whl->selectedItem = 0;
    
    return idx;
}

laResult laListWheelWidget_RemoveItem(laListWheelWidget* whl, uint32_t idx)
{
    laResult res;
    laListWheelItem* item;
    
    if(whl == NULL)
        return LA_FAILURE;
        
    item = laList_Get(&whl->items, idx);
    
    if(item == NULL)
        return LA_FAILURE;
        
    res = laList_RemoveAt(&whl->items, idx);
    
    if(whl->items.size == 0)
        whl->selectedItem = -1;
    
    laString_Destroy(&item->string);
    
    laContext_GetActive()->memIntf.heap.free(item);

    if(res == LA_SUCCESS)
	    laWidget_Invalidate((laWidget*)whl);
	
	return res;
}

void laListWheelWidget_RemoveAllItems(laListWheelWidget* whl)
{
    laListWheelItem* item;
    
    if(whl == NULL)
        return;
        
    while(whl->items.size > 0)
    {
        item = laList_Get(&whl->items, 0);
    
        if(item != NULL)
        {
            laString_Destroy(&item->string);
        
            laContext_GetActive()->memIntf.heap.free(item);
        }
        
        laList_RemoveAt(&whl->items, 0);
    }
    
    whl->selectedItem = -1;
        
    laWidget_Invalidate((laWidget*)whl);
}

int32_t laListWheelWidget_GetSelectedItem(laListWheelWidget* whl)
{
    if(whl == NULL)
        return -1;
        
    return whl->selectedItem;
}

laResult laListWheelWidget_SetSelectedItem(laListWheelWidget* whl, uint32_t idx)
{
    if(whl == NULL || idx >= whl->items.size)
        return LA_FAILURE;
        
    if(whl->selectedItem == idx)
        return LA_SUCCESS;
        
    whl->selectedItem = idx;
    
    if(whl->cb != NULL)
        whl->cb(whl, idx);
    
    laWidget_Invalidate((laWidget*)whl);
        
    return LA_SUCCESS;
}

laResult laListWheelWidget_SelectPreviousItem(laListWheelWidget* whl)
{
    uint32_t idx;
    
    if(whl == NULL || whl->items.size == 0)
        return LA_FAILURE;
        
    idx = whl->selectedItem;
    
    if(idx == 0)
        idx = whl->items.size - 1;
    else
        idx -= 1; 
        
    if(whl->selectedItem == idx)
        return LA_SUCCESS;
        
    whl->selectedItem = idx;
    
    if(whl->cb != NULL)
        whl->cb(whl, idx);
    
    laWidget_Invalidate((laWidget*)whl);
        
    return LA_SUCCESS;
}

laResult laListWheelWidget_SelectNextItem(laListWheelWidget* whl)
{
    uint32_t idx;
    
    if(whl == NULL || whl->items.size == 0)
        return LA_FAILURE;
        
    idx = whl->selectedItem;
    
    if(idx == whl->items.size - 1)
        idx = 0;
    else
        idx += 1;  
        
    if(whl->selectedItem == idx)
        return LA_SUCCESS;
        
    whl->selectedItem = idx;
    
    if(whl->cb != NULL)
        whl->cb(whl, idx);
    
    laWidget_Invalidate((laWidget*)whl);
        
    return LA_SUCCESS;
}
                                                 
void laListWheelWidget_GetItemText(laListWheelWidget* whl,
                                   uint32_t idx,
                                   laString* str)
{
    laListWheelItem* item;
    
    if(whl == NULL || idx >= whl->items.size)
        return;
        
    item = laList_Get(&whl->items, idx);
    
    laString_Copy(str, &item->string);
}
                                               
void laListWheelWidget_SetItemText(laListWheelWidget* whl,
                                   uint32_t idx,
                                   laString str)
{
    laListWheelItem* item;
    
    if(whl == NULL || idx >= whl->items.size)
        return;
       
    item = laList_Get(&whl->items, idx);
    
    laString_Copy(&item->string, &str);
    
    laWidget_Invalidate((laWidget*)whl);
}
                                               
GFXU_ImageAsset* laListWheelWidget_GetItemIcon(laListWheelWidget* whl,
                                          uint32_t idx)
{
    laListWheelItem* item;
    
    if(whl == NULL || idx >= whl->items.size)
        return NULL;
        
    item = laList_Get(&whl->items, idx);
        
    return item->icon;
}
                                                              
void laListWheelWidget_SetItemIcon(laListWheelWidget* whl,
                              uint32_t idx,
							  GFXU_ImageAsset* img)
{
    laListWheelItem* item;
    
    if(whl == NULL || idx >= whl->items.size)
        return;
        
    item = laList_Get(&whl->items, idx);
        
    item->icon = img;
    
    laWidget_Invalidate((laWidget*)whl);
}

laListWheelWidget_SelectedItemChangedEvent laListWheelWidget_GetSelectedItemChangedEventCallback(laListWheelWidget* whl)
{
	if(whl == NULL)
		return NULL;

	return whl->cb;
}

void laListWheelWidget_SetSelectedItemChangedEventCallback(laListWheelWidget* whl,
											               laListWheelWidget_SelectedItemChangedEvent cb)
{
	if(whl == NULL || whl->cb == cb)
		return;

	whl->cb = cb;
}

#endif // LA_LISTWHEEL_WIDGET_ENABLED