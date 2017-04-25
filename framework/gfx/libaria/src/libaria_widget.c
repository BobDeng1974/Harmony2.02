#include "gfx/libaria/inc/libaria_widget.h"

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_layer.h"
#include "gfx/libaria/inc/libaria_utils.h"

#include "gfx/hal/inc/gfx_math.h"

static void update(laWidget* widget, uint32_t ms)
{
    //printf("updating %u\n", widget->id);
}

static void moved(laWidget* widget) { }
static void resized(laWidget* widget) { }
static void focusGained(laWidget* widget) { }
static void focusLost(laWidget* widget) { }

static void touchDownEvent(laWidget* widget, laInput_TouchDownEvent* evt) { }
static void touchUpEvent(laWidget* widget, laInput_TouchUpEvent* evt) { }
static void touchMovedEvent(laWidget* widget, laInput_TouchMovedEvent* evt) { }

void _laWidget_Constructor(laWidget* widget)
{
	widget->id = laContext_GetActive()->widgetIDs++;

	widget->type = LA_WIDGET_WIDGET;
	
	widget->visible = LA_TRUE;
	widget->enabled = LA_TRUE;
	widget->dirtyState = LA_WIDGET_DIRTY_STATE_DIRTY;
	widget->drawState = LA_WIDGET_DRAW_STATE_READY;

	widget->rect.x = 0;
	widget->rect.y = 0;
	widget->rect.width = 1;
	widget->rect.height = 1;

	widget->borderType = LA_WIDGET_BORDER_NONE;
	widget->drawBackground = LA_TRUE;
			
    widget->alphaEnabled = LA_FALSE;
    widget->alphaAmount = 255;
			
	widget->margin.left = DEFAULT_BORDER_MARGIN;
	widget->margin.top = DEFAULT_BORDER_MARGIN;
	widget->margin.right = DEFAULT_BORDER_MARGIN;
	widget->margin.bottom = DEFAULT_BORDER_MARGIN;
	
	widget->scheme = laContext_GetDefaultScheme();

	widget->parent = NULL;
	laList_Create(&widget->children);

	widget->reader = NULL;
	
	widget->destructor = &_laWidget_Destructor;

	widget->moved = &moved;
	widget->resized = &resized;
	
	widget->focusGained = &focusGained;
	widget->focusLost = &focusLost;

	widget->update = &update;
	widget->paint = &_laWidget_Paint;

	widget->touchDown = &touchDownEvent;
	widget->touchUp = &touchUpEvent;
	widget->touchMoved = &touchMovedEvent;
	widget->destructor = &_laWidget_Destructor;
}

laWidget* laWidget_New()
{
	laWidget* wgt = NULL;

	if(laContext_GetActive() == NULL)
		return NULL;

	wgt = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laWidget));

    if(wgt == NULL)
        return NULL;
    
	_laWidget_Constructor(wgt);

	return wgt;
}

void laWidget_Delete(laWidget* widget)
{
    if(widget == NULL || laContext_GetActive() == NULL)
        return;
        
    widget->destructor(widget);
    
    laContext_GetActive()->memIntf.heap.free(widget);
}

void _laWidget_Destructor(laWidget* widget)
{
    laListNode* node;
    laWidget* child;
    
	if(widget == NULL)
		return;
		
    node = widget->children.head;
    
    while(node != NULL)
    {
        child = (laWidget*)node->val;
        
        child->destructor(child);
        
        laContext_GetActive()->memIntf.heap.free(child);
        
        node = node->next;
    }

	laList_Clear(&widget->children);
}

void _laWidget_Update(laWidget* widget, uint32_t ms)
{ }

laBool laWidget_GetEnabled(laWidget* widget)
{
    if(widget == NULL)
        return LA_FALSE;
        
    return widget->enabled;
}

void laWidget_SetEnabled(laWidget* widget, laBool enable)
{
    if(widget == NULL || widget->enabled == enable)
        return;
        
    widget->enabled = enable;
    
    laWidget_Invalidate(widget);
}

laBool laWidget_GetVisible(laWidget* widget)
{
    if(widget == NULL)
        return LA_FALSE;
        
    return widget->enabled;
}

void laWidget_SetVisible(laWidget* widget, laBool visible)
{
    if(widget == NULL || widget->visible == visible)
        return;
        
    widget->visible = visible;
    
    laWidget_Invalidate(widget);
}

int32_t laWidget_GetX(laWidget* widget)
{
	if(widget == NULL)
		return 0;

	return widget->rect.x;
}

laResult laWidget_SetX(laWidget* widget, int32_t x)
{
    if(widget == NULL)
        return LA_FAILURE;
        
    if(widget->rect.x == x)
        return LA_SUCCESS;
        
    widget->rect.x = x;
    
    laWidget_Invalidate(widget);
        
    return LA_SUCCESS;
}

int32_t laWidget_GetY(laWidget* widget)
{
	if(widget == NULL)
		return 0;

	return widget->rect.y;
}

laResult laWidget_SetY(laWidget* widget, int32_t y)
{
    if(widget == NULL)
        return LA_FAILURE;
        
    if(widget->rect.y == y)
        return LA_SUCCESS;
        
    widget->rect.y = y;
    
    laWidget_Invalidate(widget);
        
    return LA_SUCCESS;
}

void laWidget_SetPosition(laWidget* widget, int32_t x, int32_t y)
{   
	if(widget == NULL ||
	   (widget->rect.x == x && widget->rect.y == y))
		return;
		
	// invalidate old area	
    _laWidget_InvalidateArea(widget->parent, &widget->rect);

	widget->rect.x = x;
	widget->rect.y = y;

    // invalidate new area
	_laWidget_InvalidateArea(widget->parent, &widget->rect);

	widget->moved(widget);
}

void laWidget_Translate(laWidget* widget, int32_t x, int32_t y)
{
	if(widget == NULL || (x == 0 && y == 0))
		return;

    // invalidate old area	
    _laWidget_InvalidateArea(widget->parent, &widget->rect);
    
	widget->rect.x += x;
	widget->rect.y += y;

	// invalidate new area	
    _laWidget_InvalidateArea(widget->parent, &widget->rect);

	widget->moved(widget);
}

int32_t laWidget_GetWidth(laWidget* widget)
{
	if(widget == NULL)
		return 0;

	return widget->rect.width;
}

laResult laWidget_SetWidth(laWidget* widget, int32_t width)
{
    if(widget == NULL)
        return LA_FAILURE;
        
    if(widget->rect.width == width)
        return LA_SUCCESS;
        
    widget->rect.width = width;
    
    laWidget_Invalidate(widget);
        
    return LA_SUCCESS;
}

int32_t laWidget_GetHeight(laWidget* widget)
{
	if(widget == NULL)
		return 0;

	return widget->rect.height;
}

laResult laWidget_SetHeight(laWidget* widget, int32_t height)
{
    if(widget == NULL)
        return LA_FAILURE;
        
    if(widget->rect.height == height)
        return LA_SUCCESS;
        
    widget->rect.height = height;
    
    laWidget_Invalidate(widget);
        
    return LA_SUCCESS;
}

laBool laWidget_GetAlphaEnable(laWidget* widget)
{
    if(widget == NULL)
        return 0;
        
    return widget->alphaEnabled;
}

laBool laWidget_GetCumulativeAlphaEnable(laWidget* widget)
{
    laWidget* wgt = widget;
    
    if(widget == NULL)
        return 0;
        
    while(wgt != NULL)
    {
        if(wgt->alphaEnabled == LA_TRUE)
            return LA_TRUE;
        
        wgt = wgt->parent; 
    }
    
    return LA_FALSE;
}

laResult laWidget_SetAlphaEnable(laWidget* widget, laBool enable)
{
    if(widget == NULL || widget->alphaEnabled == enable)
        return LA_FAILURE;
        
    widget->alphaEnabled = enable;
    
    laWidget_Invalidate(widget);
        
    return LA_SUCCESS;
}

uint32_t laWidget_GetAlphaAmount(laWidget* widget)
{
    if(widget == NULL)
        return 0;
        
    return widget->alphaAmount;
}

uint32_t laWidget_GetCumulativeAlphaAmount(laWidget* widget)
{
    int32_t amount = 0;
    int32_t localAmount = 0;
    int32_t actualAmount = 0;
    laWidget* wgt = widget;
    
    if(widget == NULL || laWidget_GetCumulativeAlphaEnable(wgt) == GFX_FALSE)
        return 255;
        
    localAmount = GFX_PercentWholeRounded(wgt->alphaAmount, 255);
    actualAmount = localAmount;
        
    wgt = wgt->parent;
        
    while(wgt != NULL && laWidget_GetCumulativeAlphaEnable(wgt) == GFX_TRUE)
    {
        amount = GFX_PercentWholeRounded(wgt->alphaAmount, 255);
        
        actualAmount = GFX_PercentOf(actualAmount, amount);
        
        //localAmount = GFX_PercentWholeRounded(wgt->alphaAmount, 255);
        
        //if(amount > 255)
        //    return 0;
        
        wgt = wgt->parent;
        
        //if(laWidget_GetCumulativeAlphaEnable(wgt) == GFX_FALSE)
        //    break;
    }
    
    return GFX_PercentOf(255, actualAmount);
}

laResult laWidget_SetAlphaAmount(laWidget* widget, uint32_t alpha)
{
    if(widget == NULL || widget->alphaAmount == alpha)
        return LA_FAILURE;
        
    if(alpha > 255)
        alpha = 255;
        
    widget->alphaAmount = alpha;
    
    laWidget_Invalidate(widget);
        
    return LA_SUCCESS;
}

laBool laWidget_isOpaque(laWidget* widget)
{
    return !(laWidget_GetCumulativeAlphaEnable(widget) == LA_TRUE &&
             laWidget_GetCumulativeAlphaAmount(widget) < 255);
}

GFX_Rect laWidget_RectToParentSpace(laWidget* widget)
{
    GFX_Rect rect = {0};
    
    if(widget != NULL && widget->parent != NULL)
    {
        rect = widget->rect;
        
        rect.x += widget->parent->rect.x;
        rect.y += widget->parent->rect.y;
    }
    
    return rect;
}

GFX_Rect laWidget_RectToLayerSpace(laWidget* widget)
{
    GFX_Rect rect = {0};
    
    if(widget == NULL)
        return rect;
    
    rect = widget->rect;
    
    if(widget->parent != NULL)
    {
        laUtils_RectToLayerSpace(widget->parent, &rect);
    }
    
    return rect;
}

GFX_Rect laWidget_RectToScreenSpace(laWidget* widget)
{
    GFX_Rect rect = {0};
    
    if(widget != NULL && widget->parent != NULL)
    {
        rect = widget->rect;
        
        laUtils_RectToScreenSpace(widget->parent, &rect);
    }
    
    return rect;
}

void laWidget_SetSize(laWidget* widget, uint32_t width, uint32_t height)
{
	if(widget == NULL ||
	   (widget->rect.width == width && widget->rect.height == height))
		return;

	if(width == 0)
		width = 1;

	if(height == 0)
		height = 1;
		
	// invalidate old area
    _laWidget_InvalidateArea(widget->parent, &widget->rect);

	widget->rect.width = width;
	widget->rect.height = height;

	// invalidate new area
    _laWidget_InvalidateArea(widget->parent, &widget->rect);

	widget->resized(widget);
}

void laWidget_Resize(laWidget* widget, int32_t width, int32_t height)
{    
	if(widget == NULL || (width == 0 && height == 0))
		return;

    // invalidate old area	
    _laWidget_InvalidateArea(widget->parent, &widget->rect);
    
	widget->rect.width += width;
	widget->rect.height += height;

	if(widget->rect.width < 1)
		widget->rect.width = 1;

	if(widget->rect.height < 1)
		widget->rect.height = 1;

	// invalidate new area	
    _laWidget_InvalidateArea(widget->parent, &widget->rect);

	widget->resized(widget);
}

laBorderType laWidget_GetBorderType(laWidget* widget)
{
	if(widget == NULL)
		return LA_WIDGET_BORDER_NONE;

	return widget->borderType;
}

void laWidget_SetBorderType(laWidget* widget, laBorderType type)
{
	if(widget == NULL)
		return;

	widget->borderType = type;
	
	laWidget_Invalidate(widget);
}

laBool laWidget_GetDrawBackground(laWidget* widget)
{
	if(widget == NULL)
		return LA_FALSE;

	return widget->drawBackground;
}

void laWidget_SetDrawBackground(laWidget* widget, laBool enable)
{
	if(widget == NULL)
		return;

	widget->drawBackground = enable;
	
	laWidget_Invalidate(widget);
}

laBool laWidget_GetLocalRedraw(laWidget* widget)
{
	if(widget == NULL)
		return LA_FALSE;

	return widget->localRedraw;
}

void laWidget_SetLocalRedraw(laWidget* widget, laBool enable)
{
	if(widget == NULL)
		return;

	widget->localRedraw = enable;
	
	laWidget_Invalidate(widget);
}

laResult laWidget_GetMargins(laWidget* widget, laMargin* mg)
{
    if(widget == NULL)
        return LA_FAILURE;
        
    *mg = widget->margin;
    
    return LA_SUCCESS;
}

void laWidget_SetMargins(laWidget* widget, uint32_t left, uint32_t top, uint32_t right, uint32_t bottom)
{
    if(widget == NULL)
        return;
        
    if(widget->margin.left == left &&
       widget->margin.top == top &&
       widget->margin.right == right &&
       widget->margin.bottom == bottom)
       return;
        
    widget->margin.left = left;
    widget->margin.top = top;
    widget->margin.right = right;
    widget->margin.bottom = bottom;
    
    laWidget_Invalidate(widget);
}

laBool laWidget_HasFocus(laWidget* widget)
{
	if(laContext_GetActive() == NULL)
		return LA_FALSE;
		
	return laContext_GetActive()->focus == widget;
}

laResult laWidget_SetFocus(laWidget* widget)
{
	return laContext_SetFocusWidget(widget);
}

laResult laWidget_OverrideTouchDownEvent(laWidget* widget,
                                         laWidget_TouchDownEvent_FnPtr ptr)
{
    if(widget == NULL || ptr == NULL)
        return LA_FAILURE;
        
    widget->touchDown = ptr;
        
    return LA_SUCCESS;
}

laResult laWidget_OverrideTouchUpEvent(laWidget* widget,
                                       laWidget_TouchUpEvent_FnPtr ptr)
{
    if(widget == NULL || ptr == NULL)
        return LA_FAILURE;
        
    widget->touchUp = ptr;
        
    return LA_SUCCESS;
}

laResult laWidget_OverrideTouchMovedEvent(laWidget* widget,
                                          laWidget_TouchMovedEvent_FnPtr ptr)
{
    if(widget == NULL || ptr == NULL)
        return LA_FAILURE;
        
    widget->touchMoved = ptr;
        
    return LA_SUCCESS;
}

static laBool isAncestorOf(laWidget* sub, laWidget* obj)
{
    if(sub == NULL || obj == NULL)
        return LA_FALSE;
        
    if(obj->parent == NULL)
        return LA_FALSE;
        
    if(sub == obj->parent)
        return LA_TRUE;
        
    return isAncestorOf(sub, obj->parent);
}

laResult laWidget_AddChild(laWidget* parent, laWidget* child)
{
	if(parent == NULL || child == NULL || child->root == LA_TRUE ||
	   isAncestorOf(child, parent) == LA_TRUE)
		return LA_FAILURE;
		
    if(child->parent != NULL)
        laWidget_RemoveChild(child->parent, child);

	laList_PushBack(&parent->children, child);
	child->parent = parent;

	laWidget_Invalidate(child);

	return LA_SUCCESS;
}

laResult laWidget_RemoveChild(laWidget* parent, laWidget* child)
{
    if(child == NULL || parent == NULL || child->parent != parent)
        return LA_FAILURE;
        
    laList_Remove(&parent->children, child);
    child->parent = NULL;
        
    laWidget_Invalidate(parent);
    
	return LA_SUCCESS;
}

laResult laWidget_SetParent(laWidget* wgt, laWidget* parent)
{
    if(wgt == NULL || parent == NULL)
        return LA_FAILURE;
        
    if(wgt->parent != NULL)
        laWidget_RemoveChild(wgt->parent, wgt);

    if(parent == NULL)
        return LA_SUCCESS;
        
    return laWidget_AddChild(parent, wgt);
}

uint32_t laWidget_GetChildCount(laWidget* parent)
{
    if(parent == NULL)
        return 0;
        
    return parent->children.size;
}

laWidget* laWidget_GetChildAtIndex(laWidget* parent, uint32_t idx)
{
    if(parent == NULL || idx >= parent->children.size)
        return NULL;
        
    return laList_Get(&parent->children, idx);
}

int32_t laWidget_GetIndexOfChild(laWidget* parent, laWidget* child)
{
    if(parent == NULL || child == NULL)
        return 0;
        
    return laList_Find(&parent->children, child);
}

laScheme* laWidget_GetScheme(laWidget* widget)
{
	if(widget == NULL)
		return NULL;

	return widget->scheme;
}

void laWidget_SetScheme(laWidget* widget, laScheme* scheme)
{
	if(widget == NULL || widget->scheme == scheme)
		return;

	widget->scheme = scheme;

	laWidget_Invalidate(widget);
}

void laWidget_Invalidate(laWidget* widget)
{
    GFX_Rect invalidArea;
    laLayer* layer;
    
    if(widget == NULL || widget->visible == LA_FALSE)
        return;
    
	invalidArea = widget->rect;

    layer = laUtils_GetLayer(widget);

    // refresh entire layer in a multi-buffer environment
    if(layer != NULL && (laWidget*)layer != widget && layer->bufferCount > 1)
    {
        _laLayer_Invalidate(layer);
        
        return;
    }
    
    // if widget has no parent or is completely outside of parent's
    // bounds then nothing needs to be done
    if(widget->type != LA_WIDGET_LAYER && 
       (widget->parent == NULL || 
        laUtils_ChildIntersectsParent(widget->parent, widget) == GFX_FALSE))
	{
	    // mark this widget and all children as clean
	    _laWidget_ValidateChildren(widget);
	    
	    return;
    }
    
	if(widget->dirtyState == LA_WIDGET_DIRTY_STATE_DIRTY)
		return;
		
    widget->dirtyState = LA_WIDGET_DIRTY_STATE_DIRTY;
		
    // if alpha is enabled just invalidate the widget rect area
	/*if(widget->localRedraw == LA_FALSE && laWidget_GetCumulativeAlphaAmount(widget) < 255)
	{
	    laWidget_Invalidate(widget->parent);
	                            
	    return;
	}*/
		
    // if no background then parent needs to be redrawn
	if(widget->localRedraw == LA_FALSE &&
	   (widget->drawBackground == LA_FALSE ||
	    laWidget_GetCumulativeAlphaAmount(widget) < 255))
	    laWidget_Invalidate(widget->parent);
    
    // children always need to be invalidated
    _laWidget_InvalidateChildren(widget);
    
    // any siblings or ancestors to the right need to be checked for
    // intersection with this widget's bounding rectangle
    _laWidget_InvalidateRight(widget, &invalidArea);
}

void _laWidget_InvalidateArea(laWidget* widget, GFX_Rect* area)
{
    if(widget == NULL || widget->visible == LA_FALSE)
        return;
        
    if(GFX_RectIntersects(&widget->rect, area) == GFX_FALSE)
        return;
        
    laWidget_Invalidate(widget);
}

void _laWidget_InvalidateRight(laWidget* widget, GFX_Rect* rect)
{
    laWidget *parent, *sibling;
    uint32_t idx, i;
    GFX_Rect siblingRect;
    
    // get the widget's parent
    parent = widget->parent;
    
    if(parent == NULL)
        return;
        
    // at least indicate that parent has dirty children
    if(parent->dirtyState != LA_WIDGET_DIRTY_STATE_DIRTY)
        parent->dirtyState = LA_WIDGET_DIRTY_STATE_CHILD;
    
    parent->drawState = LA_WIDGET_DRAW_STATE_READY;
        
    // find the widget's index in regards to its siblings
    idx = laList_Find(&parent->children, widget);
    
    if(idx == -1)
        return;
        
    // test each sibling rectangle against the target rectangle
    for(i = idx + 1; i < parent->children.size; i++)
    {
        sibling = (laWidget*)laList_Get(&parent->children, i);
        
        siblingRect = sibling->rect;
        
        if(GFX_RectIntersects(&siblingRect, rect) == GFX_TRUE)
            laWidget_Invalidate(sibling);
    }
    
    // move target rectangle to next higher space
    rect->x += parent->rect.x;
    rect->y += parent->rect.y;
    
    // test parent
    _laWidget_InvalidateRight(parent, rect);
}

void _laWidget_InvalidateChildren(laWidget* widget)
{
	laListNode* node;
	laWidget* child;

	widget->dirtyState = LA_WIDGET_DIRTY_STATE_DIRTY;
	widget->drawState = LA_WIDGET_DRAW_STATE_READY;

	node = widget->children.head;

	while(node != NULL)
	{
		child = (laWidget*)node->val;

        //if(child->dirtyState != LA_WIDGET_DIRTY_STATE_DIRTY)
		_laWidget_InvalidateChildren(child);

		node = node->next;
	}
}

void _laWidget_ValidateChildren(laWidget* widget)
{
	laListNode* node;
	laWidget* child;

	widget->dirtyState = LA_WIDGET_DIRTY_STATE_CLEAN;
	widget->drawState = LA_WIDGET_DRAW_STATE_READY;

	node = widget->children.head;

	while(node != NULL)
	{
		child = (laWidget*)node->val;

		_laWidget_ValidateChildren(child);

		node = node->next;
	}
}