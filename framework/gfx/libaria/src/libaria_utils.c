#include "gfx/libaria/inc/libaria_utils.h"

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_layer.h"
#include "gfx/libaria/inc/libaria_list.h"
#include "gfx/libaria/inc/libaria_screen.h"
#include "gfx/libaria/inc/libaria_widget.h"

static laWidget* pickChild(laWidget* parent, int32_t x, int32_t y)
{
	laListNode* node;
	laWidget* child;
	laWidget* result;
	GFX_Point pnt;

	node = parent->children.head;

	pnt.x = x;
	pnt.y = y;

	result = parent;

	while(node != NULL)
	{
		child = (laWidget*)node->val;

		// widget must be enabled and visible
		if(child->enabled == LA_TRUE &&
		   child->visible == LA_TRUE &&
		   GFX_RectContainsPoint(&child->rect, &pnt) == GFX_TRUE)
		{
			result = pickChild(child, x - child->rect.x, y - child->rect.y);
		}

		node = node->next;
	}

	return result;
}

laWidget* laUtils_Pick(int32_t x, int32_t y)
{
	laContext* context = laContext_GetActive();
	laScreen* screen = NULL;
	laLayer* layer = NULL;
	laWidget* widget = NULL;
	GFX_Point pnt;
	GFX_Rect rect;
	uint32_t i;

	if(context == NULL)
		return NULL;

	pnt.x = x;
	pnt.y = y;

	// get the active screen
	screen = context->activeScreen;

	rect = laContext_GetScreenRect();

	// screen must contain point
	if(GFX_RectContainsPoint(&rect, &pnt) == GFX_FALSE)
		return NULL;

	// find the topmost visible layer that contains the point
	for(i = 0; i < LA_MAX_LAYERS; i++)
	{
		layer = screen->layers[i];

		// layer must exist and be enabled and visible
		if(layer == NULL ||
		   layer->widget.enabled == LA_FALSE ||
		   layer->widget.visible == LA_FALSE)
		   continue;

		// layer zero has the lowest z order, always favor higher layers
		if(GFX_RectContainsPoint(&layer->widget.rect, &pnt) == GFX_TRUE)
			widget = (laWidget*)layer;
	}

	// no layer qualified
	if(widget == NULL)
		return NULL;

	widget = pickChild(widget, x - widget->rect.x, y - widget->rect.y);

	return widget;
}

static void pickChildRect(laWidget* parent, GFX_Rect rect, laList* list)
{
    laWidget* child;
	GFX_Rect childRect;
	uint32_t i;

    for(i = 0; i < parent->children.size; i++)
    {
        child = (laWidget*)laList_Get(&parent->children, i);
        
        childRect = laWidget_RectToLayerSpace(child);
        
        if(GFX_RectIntersects(&rect, &childRect) == LA_TRUE)
            laList_PushBack(list, child);
            
        pickChildRect(child, rect, list);
    }
}

void laUtils_PickRect(laLayer* layer, GFX_Rect rect, laList* list)
{
    laWidget* child;
    GFX_Rect childRect;
	uint32_t i;

	if(layer == NULL ||
	   layer->widget.enabled == LA_FALSE ||
	   layer->widget.visible == LA_FALSE ||
	   list == NULL)
		return;
		
    laList_Clear(list);

	// layer must contain rect
	if(GFX_RectIntersects(&layer->widget.rect, &rect) == GFX_FALSE)
		return;
		
    //GFX_RectClip(&rect, &layer->widget.rect, &clippedRect);

    for(i = 0; i < layer->widget.children.size; i++)
    {
        child = (laWidget*)laList_Get(&layer->widget.children, i);
        
        childRect = laWidget_RectToLayerSpace(child);
        
        if(GFX_RectIntersects(&rect, &childRect) == LA_TRUE)
            laList_PushBack(list, child);
            
        pickChildRect(child, rect, list);
    }
}

laLayer* laUtils_GetLayer(laWidget* widget)
{
    laWidget* parent;
    
    if(widget == NULL)
        return NULL;
   
    if(widget->type == LA_WIDGET_LAYER)
        return (laLayer*)widget;
        
    parent = widget->parent;
    
    while(parent != NULL)
    {
        if(parent->parent == NULL)
            break;
            
        parent = parent->parent;
    }
    
    if(parent == NULL || parent->type != LA_WIDGET_LAYER)
        return NULL;
    
    return (laLayer*)parent;
}

void laUtils_PointToScreenSpace(laWidget* widget, GFX_Point* pnt)
{
	laWidget* parent;

	if(widget == NULL || pnt == NULL)
		return;
		
    pnt->x += widget->rect.x;
    pnt->y += widget->rect.y;

	parent = widget->parent;

	while(parent != NULL)
	{
		pnt->x += parent->rect.x;
		pnt->y += parent->rect.y;

		parent = parent->parent;
	}
}

void laUtils_PointScreenToLocalSpace(laWidget* widget, GFX_Point* pnt)
{
    laWidget* parent;

	if(widget == NULL || pnt == NULL)
		return;
		
    pnt->x -= widget->rect.x;
    pnt->y -= widget->rect.y;

	parent = widget->parent;

	while(parent != NULL)
	{
		pnt->x -= parent->rect.x;
		pnt->y -= parent->rect.y;

		parent = parent->parent;
	}
}

void laUtils_ClipRectToParent(laWidget* parent, GFX_Rect* rect)
{
	GFX_Rect result;

	if(parent == NULL || rect == NULL)
		return;

	rect->x += parent->rect.x;
	rect->y += parent->rect.y;

	GFX_RectClip(rect, &parent->rect, &result);

	result.x -= parent->rect.x;
	result.y -= parent->rect.y;

	*rect = result;
}

void laUtils_RectToParentSpace(laWidget* widget, GFX_Rect* rect)
{
	if(widget == NULL || rect == NULL || widget->parent == NULL)
		return;

	rect->x += widget->parent->rect.x;
	rect->y += widget->parent->rect.y;
}

void laUtils_RectFromParentSpace(laWidget* widget, GFX_Rect* rect)
{
	if(widget == NULL || rect == NULL || widget->parent == NULL)
		return;

	rect->x -= widget->parent->rect.x;
	rect->y -= widget->parent->rect.y;
}

void laUtils_RectToLayerSpace(laWidget* parent, GFX_Rect* rect)
{
	if(parent == NULL || rect == NULL)
		return;

	while(parent != NULL && parent->parent != NULL)
	{
	    rect->x += parent->rect.x;
	    rect->y += parent->rect.y;
        
		parent = parent->parent;
	}
}

void laUtils_RectToScreenSpace(laWidget* parent, GFX_Rect* rect)
{
	if(parent == NULL || rect == NULL)
		return;
		
    rect->x += parent->rect.x;
    rect->y += parent->rect.y;

	parent = parent->parent;

	while(parent != NULL)
	{
		rect->x += parent->rect.x;
		rect->y += parent->rect.y;

		parent = parent->parent;
	}
}

laBool laUtils_ChildIntersectsParent(laWidget* parent, laWidget* child)
{
    GFX_Rect childRect;
    
    if(parent == NULL || child == NULL)
        return LA_FALSE;
        
    childRect = child->rect;
    
    childRect.x += parent->rect.x;
	childRect.y += parent->rect.y;

	return GFX_RectIntersects(&childRect, &parent->rect);
}

void laUtils_ArrangeRectangle(GFX_Rect* sub,
                              GFX_Rect obj,
                              GFX_Rect bounds,
                              laHAlignment hAlignment,
                              laVAlignment vAlignment,
                              laRelativePosition position,
                              uint8_t leftMargin,
                              uint8_t topMargin,
                              uint8_t rightMargin,
                              uint8_t bottomMargin,
                              uint16_t rectMargin)
{
    sub->x = 0;
    sub->y = 0;
    
    if(hAlignment == LA_HALIGN_LEFT)
    {
        sub->x = bounds.x + leftMargin;
        
        if(obj.width > 0 && position == LA_RELATIVE_POSITION_RIGHTOF)
            sub->x += obj.width + rectMargin;
    }
    else if(hAlignment == LA_HALIGN_CENTER)
    {
        sub->x = bounds.x + (bounds.width / 2) - (sub->width / 2);
        
        if(obj.width > 0)
        {
            if(position == LA_RELATIVE_POSITION_LEFTOF)
                sub->x -= (obj.width / 2) + (rectMargin / 2);
            else if(position == LA_RELATIVE_POSITION_RIGHTOF)
                sub->x += (obj.width / 2) + (rectMargin / 2);
        }
    }
    else
    {
        sub->x = bounds.x + bounds.width - sub->width - rightMargin;
        
        if(obj.width > 0 && position == LA_RELATIVE_POSITION_LEFTOF)
            sub->x -= obj.width + rectMargin;
    }
    
    if(vAlignment == LA_VALIGN_TOP)
    {
        sub->y = bounds.y + topMargin + 1;
        
        if(obj.height > 0)
        {
            if(position == LA_RELATIVE_POSITION_BELOW)
                sub->y += obj.height + rectMargin;
        }
    }
    else if(vAlignment == LA_VALIGN_MIDDLE)
    {
        sub->y = bounds.y + (bounds.height / 2) - (sub->height / 2);
        
        if(obj.height > 0)
        {
            if(position == LA_RELATIVE_POSITION_ABOVE)
                sub->y -= (obj.height / 2) + (rectMargin / 2);
            else if(position == LA_RELATIVE_POSITION_BELOW)
                sub->y += (obj.height / 2) + (rectMargin / 2);
        }
    }
    else
    {
        sub->y = bounds.y + bounds.height - sub->height - bottomMargin ;
        
        if(obj.height > 0 && position == LA_RELATIVE_POSITION_ABOVE)
            sub->y -= obj.height + rectMargin;
    }
}

void laUtils_ArrangeRectangleRelative(GFX_Rect* sub,
                                      GFX_Rect obj,
                                      GFX_Rect bounds,
                                      laHAlignment hAlignment,
                                      laVAlignment vAlignment,
                                      laRelativePosition position,
                                      uint8_t leftMargin,
                                      uint8_t topMargin,
                                      uint8_t rightMargin,
                                      uint8_t bottomMargin,
                                      uint16_t rectMargin)
{
    sub->x = 0;
    sub->y = 0;
    
    if(hAlignment == LA_HALIGN_LEFT)
    {
        sub->x = bounds.x + leftMargin;
        
        if(obj.width > 0)
        {
            if(position == LA_RELATIVE_POSITION_LEFTOF)
                sub->x += obj.width + rectMargin;
            //else
            //    sub->x += (obj.width / 2) - (sub->width / 2);
        }
    }
    else if(hAlignment == LA_HALIGN_CENTER)
    {
        sub->x = bounds.x + (bounds.width / 2) - (sub->width / 2);
        
        if(obj.width > 0)
        {
            if(position == LA_RELATIVE_POSITION_LEFTOF)
                sub->x += (obj.width / 2) + (rectMargin / 2);
            else if(position == LA_RELATIVE_POSITION_RIGHTOF)
                sub->x -= (obj.width / 2) + (rectMargin / 2);
        }
    }
    else
    {
        sub->x = bounds.x + bounds.width - sub->width - rightMargin;
        
        if(obj.width > 0)
        {   
            if(position == LA_RELATIVE_POSITION_RIGHTOF)
                sub->x -= obj.width + rectMargin;
            //else
            //    sub->x -= (obj.width / 2) - (sub->width / 2);
        }
    }
    
    if(vAlignment == LA_VALIGN_TOP)
    {
        sub->y = bounds.y + topMargin + 1;
        
        if(obj.height > 0 && position != LA_RELATIVE_POSITION_BELOW)
        {
            if(position == LA_RELATIVE_POSITION_ABOVE)
                sub->y += obj.height + rectMargin;
            else
                sub->y += (obj.height / 2) - (sub->height / 2);
        }
    }
    else if(vAlignment == LA_VALIGN_MIDDLE)
    {
        sub->y = bounds.y + (bounds.height / 2) - (sub->height / 2);
        
        if(obj.height > 0)
        {
            if(position == LA_RELATIVE_POSITION_ABOVE)
                sub->y += (obj.height / 2) + (rectMargin / 2);
            else if(position == LA_RELATIVE_POSITION_BELOW)
                sub->y -= (obj.height / 2) + (rectMargin / 2);
        }
    }
    else
    {
        sub->y = bounds.y + bounds.height - sub->height - bottomMargin ;
        
        if(obj.height > 0 && position != LA_RELATIVE_POSITION_ABOVE)
        {
            if(position == LA_RELATIVE_POSITION_BELOW)
                sub->y -= obj.height + rectMargin;
            else
                sub->y -= (obj.height / 2) - (sub->height / 2);
        }
    }
}

laBool _occlusionCullTestAscending(laWidget* widget, GFX_Rect* bounds)
{
    uint32_t i, idx;
    laWidget *parent, *child;
    GFX_Rect childRect;
    
    // root node of tree, can't possibly occlude
    if(widget->parent == NULL)
        return LA_FALSE;
        
    parent = widget->parent;
        
    bounds->x += parent->rect.x;
    bounds->y += parent->rect.y;
    
    idx = laList_Find(&parent->children, widget);
    
    if(idx < parent->children.size - 1)
    {    
        idx += 1;
        
        // test all rightside siblings, leftside can't occlude
        for(i = idx; i < parent->children.size; i++)
        {
            child = (laWidget*)laList_Get(&parent->children, i);
            
            childRect = child->rect;
            
            // move child rect into parent space
            //childRect.x += widget->rect.x;
            //childRect.y += widget->rect.y;
            
            if(GFX_RectContainsRect(&childRect, bounds) == LA_TRUE)
                return LA_TRUE;
        }
    }
    
    return _occlusionCullTestAscending(parent, bounds);
}

laBool laUtils_OcclusionCullTest(laWidget* widget)
{
    uint32_t i;
    laWidget* child;
    GFX_Rect childRect;
    
    if(widget == NULL)
        return LA_FALSE;
    
    // test children first
    for(i = 0; i < widget->children.size; i++)
    {
        child = laList_Get(&widget->children, i);
        
        childRect = child->rect;
        
        // move child rect into parent space
        //childRect.x += widget->rect.x;
        //childRect.y += widget->rect.y;
        
        if(GFX_RectContainsRect(&childRect, &widget->rect) == LA_TRUE)
            return LA_TRUE;
    }
    
    // test rightmost ancestors
    childRect = widget->rect;
    
    return _occlusionCullTestAscending(widget, &childRect);
}

void laUtils_ListOcclusionCullTest(laList* list, GFX_Rect rect)
{
    uint32_t i, j;
    laWidget *widget, *higherWidget;
    GFX_Rect widgetRect;//, lclippedRect, rclippedRect;
    laList cullList;
    laBool cull;
    
    laList_Create(&cullList);
    laList_Copy(&cullList, list);
    laList_Clear(list);
    
    if(cullList.size == 0)
        return;

    for(i = 0; i <= cullList.size - 1; i++)
    {
        cull = LA_FALSE;
        
        widget = (laWidget*)laList_Get(&cullList, i);
        
        // topmost widget is always a pass
        if(i == cullList.size - 1)
        {
            laList_PushBack(list, widget);
        
            continue;
        }
        
        widgetRect = laWidget_RectToLayerSpace(widget);
        
        //GFX_RectClip(&widgetRect, &rect, &lclippedRect);
        
        for(j = i + 1; j < cullList.size; j++)
        {
            higherWidget = (laWidget*)laList_Get(&cullList, j);
            
            //GFX_RectClip(&higherWidget->rect, &widgetRect, &rclippedRect);
            
            if(GFX_RectContainsRect(&higherWidget->rect, &widgetRect) == LA_TRUE &&
               laWidget_isOpaque(higherWidget) == LA_TRUE)
            {
                cull = LA_TRUE;
                
                break;
            }
        }
        
        if(cull == LA_FALSE)
            laList_PushBack(list, widget);
    }
    
    laList_Clear(&cullList);
}