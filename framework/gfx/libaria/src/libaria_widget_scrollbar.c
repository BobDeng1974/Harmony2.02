#include "gfx/libaria/inc/libaria_widget_scrollbar.h"

#if LA_SCROLLBAR_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_widget.h"
#include "gfx/libaria/inc/libaria_utils.h"

#include "gfx/hal/inc/gfx_math.h"
#include "gfx/hal/inc/gfx_util.h"

#define DEFAULT_WIDTH           20
#define DEFAULT_HEIGHT          100

#define DEFAULT_MIN             0
#define DEFAULT_MAX             100
#define DEFAULT_EXTENT          10
#define DEFAULT_VALUE           0

#define DEFAULT_STEP            1

#define MIN_HANDLE_HEIGHT       16

void _laScrollBar_GetUpLeftButtonRect(laScrollBarWidget* bar, GFX_Rect* rect)
{
    rect->x = 0;
    rect->y = 0;
        
    if(bar->alignment == LA_SCROLLBAR_ORIENT_VERTICAL)
    {
        rect->width = bar->widget.rect.width;
        rect->height = rect->width;
    }
    else
    {
        rect->width = bar->widget.rect.height;
        rect->height = rect->width;
    }
}

void _laScrollBar_GetDownRightButtonRect(laScrollBarWidget* bar, GFX_Rect* rect)
{
    if(bar->alignment == LA_SCROLLBAR_ORIENT_VERTICAL)
    {
        rect->width = bar->widget.rect.width;
        rect->height = rect->width;
        rect->x = 0;
        rect->y = bar->widget.rect.height - rect->width;
    }
    else
    {
        rect->width = bar->widget.rect.height;
        rect->height = rect->width;
        rect->y = 0;
        rect->x = bar->widget.rect.width - rect->height;
    }
}

void _laScrollBar_GetScrollAreaRect(laScrollBarWidget* bar, GFX_Rect* rect)
{
    GFX_Rect scrollRect;
    
    if(bar->alignment == LA_SCROLLBAR_ORIENT_VERTICAL)
    {
        scrollRect.x = 0;
        scrollRect.y = bar->widget.rect.width;
        scrollRect.width = bar->widget.rect.width;
        scrollRect.height = bar->widget.rect.height - (bar->widget.rect.width * 2);
    }
    else
    {
        scrollRect.x = bar->widget.rect.height;
        scrollRect.y = 0;
        scrollRect.width = bar->widget.rect.width - (bar->widget.rect.height * 2);
        scrollRect.height = bar->widget.rect.height;
    }
    
    *rect = scrollRect;
}

void _laScrollBar_GetHandleRect(laScrollBarWidget* bar, GFX_Rect* rect)
{
    GFX_Rect scrollRect;
    uint32_t extent;
    uint32_t sizePercent;
    uint32_t locPercent;
    
    extent = _laScrollWidget_GetExtent(bar);
        
    if(bar->value >= 1)
        extent = extent;
    
    sizePercent = GFX_PercentWholeRounded(extent, bar->max);
    locPercent = GFX_PercentWholeRounded(bar->value, bar->max);
    
    _laScrollBar_GetScrollAreaRect(bar, &scrollRect);
    
    if(bar->alignment == LA_SCROLLBAR_ORIENT_VERTICAL)
    {
        sizePercent = GFX_PercentOf(scrollRect.height, sizePercent);
        locPercent = GFX_PercentOf(scrollRect.height - sizePercent, locPercent);
        
        rect->x = scrollRect.x;
        rect->y = scrollRect.y + locPercent;
        rect->width = scrollRect.width;
        rect->height = sizePercent;
    }
    else
    {
        sizePercent = GFX_PercentOf(scrollRect.width, sizePercent);
        locPercent = GFX_PercentOf(scrollRect.width - sizePercent, locPercent);
        
        rect->x = scrollRect.x + locPercent;
        rect->y = scrollRect.y;
        rect->width = sizePercent;
        rect->height = scrollRect.height;
    }
}

uint32_t _laScrollWidget_GetExtent(laScrollBarWidget* bar)
{
    uint32_t extent = bar->extent;
    
    if(extent >= bar->max)
        extent = bar->max - 1;
        
    return extent;
}

uint32_t _laScrollBar_GetPercentFromPoint(laScrollBarWidget* bar, GFX_Point* pnt)
{
    GFX_Rect scrollRect, handleRect;
    int32_t val;
    int32_t size;
    
    _laScrollBar_GetScrollAreaRect(bar, &scrollRect);
    _laScrollBar_GetHandleRect(bar, &handleRect);
    
    laUtils_ClipRectToParent((laWidget*)bar, &scrollRect);
	laUtils_RectToScreenSpace((laWidget*)bar, &scrollRect);
    
    if(bar->alignment == LA_SCROLLBAR_ORIENT_VERTICAL)
    {
        size = scrollRect.height - handleRect.height;
                
        // translate rect and point in to rect space
        val = pnt->y - scrollRect.y;
        scrollRect.y = 0;
        
        if(val <= 0)
            return 0;
        else if(val >= size)
            return 100;
        
        return GFX_PercentWholeRounded(val, size);
    }
    else
    {
        size = scrollRect.width - handleRect.width;
        
        // translate rect and point in to rect space
        val = pnt->x - scrollRect.x;
        scrollRect.x = 0;
        
        //scrollRect.width -= _laScrollWidget_GetExtent(bar);
        
        if(val <= 0)
            return 0;
        else if(val >= size)
            return 100;
        
        return GFX_PercentWholeRounded(val, size);
    }
}

uint32_t _laScrollBar_GetValueFromPercent(laScrollBarWidget* bar, uint32_t per)
{
    int32_t max;
    
    if(per == 0)
        return DEFAULT_MIN;
    else if(per == 100)
        return bar->max;
    
    // zero based range
    max = bar->max;
    
    return GFX_PercentOf(max, per);
}

void _laScrollBarWidget_Constructor(laScrollBarWidget* bar)
{
	_laWidget_Constructor((laWidget*)bar);
	
	bar->widget.destructor = (laWidget_Destructor_FnPtr)&_laScrollBarWidget_Destructor;

	bar->widget.type = LA_WIDGET_SCROLLBAR;

	// override base class methods
	bar->widget.update = (laWidget_Update_FnPtr)&_laScrollBarWidget_Update;
	bar->widget.paint = (laWidget_Paint_FnPtr)&_laScrollBarWidget_Paint;

	bar->widget.rect.width = DEFAULT_WIDTH;
	bar->widget.rect.height = DEFAULT_HEIGHT;

	bar->state = LA_SCROLLBAR_STATE_NONE;

	bar->widget.borderType = LA_WIDGET_BORDER_NONE;

	bar->alignment = LA_SCROLLBAR_ORIENT_VERTICAL;
	
	//bar->min = DEFAULT_MIN;
	bar->max = DEFAULT_MAX;
	bar->extent = DEFAULT_EXTENT;
	bar->value = DEFAULT_VALUE;
	bar->step = DEFAULT_STEP;

	bar->widget.touchDown = (laWidget_TouchDownEvent_FnPtr)&_laScrollBarWidget_TouchDownEvent;
	bar->widget.touchUp = (laWidget_TouchUpEvent_FnPtr)&_laScrollBarWidget_TouchUpEvent;
	bar->widget.touchMoved = (laWidget_TouchMovedEvent_FnPtr)&_laScrollBarWidget_TouchMovedEvent;
}

void _laScrollBarWidget_Destructor(laScrollBarWidget* bar)
{
	_laWidget_Destructor((laWidget*)bar);
}

void _laScrollBarWidget_Update(laScrollBarWidget* bar)
{

}

laScrollBarWidget* laScrollBarWidget_New()
{
	laScrollBarWidget* bar = NULL;

	if(laContext_GetActive() == NULL)
		return NULL;

	bar = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laScrollBarWidget));
    
	_laScrollBarWidget_Constructor(bar);

	return bar;
}

laScrollBarOrientation laScrollBarWidget_GetOrientation(laScrollBarWidget* bar)
{
	if(bar == NULL)
		return 0;

	return bar->alignment;
}

void laScrollBarWidget_SetOrientation(laScrollBarWidget* bar,
									  laScrollBarOrientation align,
								      laBool swapDimensions)
{
    uint32_t t;
    
	if(bar == NULL || bar->alignment == align)
		return;

	bar->alignment = align;
	
	// reverse dimensions
	if(swapDimensions == LA_TRUE)
	{
	    t = bar->widget.rect.width;
    	bar->widget.rect.width = bar->widget.rect.height;
	    bar->widget.rect.height = t;
    }
    
	laWidget_Invalidate((laWidget*)bar);
}

laScrollBarWidget_ValueChangedEvent laScrollBarWidget_GetValueChangedEventCallback(laScrollBarWidget* bar)
{
	if(bar == NULL)
		return NULL;

	return bar->valueChangedEvent;
}

uint32_t laScrollBarWidget_GetMaxinumValue(laScrollBarWidget* bar)
{
    if(bar == NULL)
        return 0;
        
    return bar->max;
}

laResult laScrollBarWidget_SetMaximumValue(laScrollBarWidget* bar,
                                           uint32_t val)
{
    if(bar == NULL)
        return LA_FAILURE;
        
    if(bar->max == val)
        return LA_SUCCESS;
        
    bar->max = val;
    
    laWidget_Invalidate((laWidget*)bar);
        
    return LA_SUCCESS;
}                                                 

uint32_t laScrollBarWidget_GetExtentValue(laScrollBarWidget* bar)
{
    if(bar == NULL)
        return 0;
        
    return bar->extent;
}

laResult laScrollBarWidget_SetExtentValue(laScrollBarWidget* bar,
                                          uint32_t val)
{
    if(bar == NULL)
        return LA_FAILURE;
        
    if(bar->extent == val)
        return LA_SUCCESS;
        
    bar->extent = val;
    
    laWidget_Invalidate((laWidget*)bar);
        
    return LA_SUCCESS;
}

uint32_t laScrollBarWidget_GetScrollPercentage(laScrollBarWidget* bar)
{
    if(bar == NULL)
        return 0;
        
    return GFX_PercentWholeRounded(bar->value, bar->max);
}

laResult laScrollBarWidget_SetScrollPercentage(laScrollBarWidget* bar,
                                               uint32_t val)
{
    if(bar == NULL)
        return LA_FAILURE;
        
    if(bar->value == val)
        return LA_SUCCESS;
        
    bar->value = val;
    
    if(bar->valueChangedEvent != NULL)
        bar->valueChangedEvent(bar);
    
    laWidget_Invalidate((laWidget*)bar);
        
    return LA_SUCCESS;
} 
                                                                                                               
uint32_t laScrollBarWidget_GetScrollValue(laScrollBarWidget* bar)
{
    if(bar == NULL)
        return 0;
        
    return bar->value;
}

laResult laScrollBarWidget_SetScrollValue(laScrollBarWidget* bar,
                                          uint32_t val) 
{
    if(bar == NULL)
        return LA_FAILURE;
        
    if(bar->value == val)
        return LA_SUCCESS;
        
    if(val > bar->max)
        val = bar->max;
        
    bar->value = val;
    
    if(bar->valueChangedEvent != NULL)
        bar->valueChangedEvent(bar);
    
    laWidget_Invalidate((laWidget*)bar);
        
    return LA_SUCCESS;
}

uint32_t laScrollBarWidget_GetStepSize(laScrollBarWidget* bar)
{
    if(bar == NULL)
        return 0;
        
    return bar->step;
}

laResult laScrollBarWidget_SetStepSize(laScrollBarWidget* bar,
                                       uint32_t val)
{
    if(bar == NULL)
        return LA_FAILURE;
        
    bar->step = val;
        
    return LA_SUCCESS;
}

laResult laScrollBarWidget_StepBackward(laScrollBarWidget* bar)
{
    if(bar == NULL || bar->value == DEFAULT_MIN)
        return LA_FAILURE;
        
    if(bar->value - bar->step < DEFAULT_MIN ||
       bar->value - bar->step > bar->max)
    {
        bar->value = DEFAULT_MIN;
    }
    else
        bar->value -= bar->step;
        
    if(bar->valueChangedEvent != NULL)
        bar->valueChangedEvent(bar);
        
    //printf("%u\n", bar->value);
        
    laWidget_Invalidate((laWidget*)bar);
        
    return LA_SUCCESS;
}

laResult laScrollBarWidget_StepForward(laScrollBarWidget* bar)
{
    if(bar == NULL || bar->value == bar->max)
        return LA_FAILURE;
        
    if(bar->value + bar->step < DEFAULT_MIN ||
       bar->value + bar->step > bar->max)
    {
        bar->value = bar->max;
    }
    else
        bar->value += bar->step;
        
    if(bar->valueChangedEvent != NULL)
        bar->valueChangedEvent(bar);
        
    //printf("%u\n", bar->value);
        
    laWidget_Invalidate((laWidget*)bar);
        
    return LA_SUCCESS;
}

void laScrollBarWidget_SetValueChangedEventCallback(laScrollBarWidget* bar,
											        laScrollBarWidget_ValueChangedEvent cb)
{
	if(bar == NULL || bar->valueChangedEvent == cb)
		return;

	bar->valueChangedEvent = cb;
}

void _laScrollBarWidget_TouchDownEvent(laScrollBarWidget* bar,
							           laInput_TouchDownEvent* evt)
{
    GFX_Rect rect;
    GFX_Point pnt;

	pnt.x = evt->x;
	pnt.y = evt->y;
    
    // already guaranteed to be inside widget rectangle, accept event
	evt->event.accepted = LA_TRUE;

    // was the up/left button pressed
    _laScrollBar_GetUpLeftButtonRect(bar, &rect);
    
    laUtils_ClipRectToParent((laWidget*)bar, &rect);
	laUtils_RectToScreenSpace((laWidget*)bar, &rect);
    
    if(GFX_RectContainsPoint(&rect, &pnt) == GFX_TRUE)
    {
        bar->state = LA_SCROLLBAR_STATE_TOP_INSIDE;
        
        laWidget_Invalidate((laWidget*)bar);
        
        return;
    }
    
    // was the up/left button pressed
    _laScrollBar_GetDownRightButtonRect(bar, &rect);
    
    laUtils_ClipRectToParent((laWidget*)bar, &rect);
	laUtils_RectToScreenSpace((laWidget*)bar, &rect);
    
    if(GFX_RectContainsPoint(&rect, &pnt) == GFX_TRUE)
    {
        bar->state = LA_SCROLLBAR_STATE_BOTTOM_INSIDE;
        
        laWidget_Invalidate((laWidget*)bar);
        
        return;
    }
    
    // was the handle touched
    _laScrollBar_GetHandleRect(bar, &rect);
    
    laUtils_ClipRectToParent((laWidget*)bar, &rect);
	laUtils_RectToScreenSpace((laWidget*)bar, &rect);
    
    if(GFX_RectContainsPoint(&rect, &pnt) == GFX_TRUE)
    {
        bar->state = LA_SCROLLBAR_STATE_HANDLE_DOWN;
        
        bar->handleDownOffset.x = evt->x - rect.x;
        bar->handleDownOffset.y = evt->y - rect.y;
        
        //printf("%i, %i\n", bar->handleDownOffset.x, bar->handleDownOffset.y); 
        
        laWidget_Invalidate((laWidget*)bar);
        
        return;
    }
}

void _laScrollBarWidget_TouchUpEvent(laScrollBarWidget* bar,
							      laInput_TouchUpEvent* evt)
{
	GFX_Rect rect = bar->widget.rect;
	GFX_Point pnt;

	pnt.x = evt->x;
	pnt.y = evt->y;

	evt->event.accepted = LA_TRUE;
    
    if(bar->state == LA_SCROLLBAR_STATE_TOP_INSIDE)
	{
		_laScrollBar_GetUpLeftButtonRect(bar, &rect);
    
        laUtils_ClipRectToParent((laWidget*)bar, &rect);
	    laUtils_RectToScreenSpace((laWidget*)bar, &rect);

		if(GFX_RectContainsPoint(&rect, &pnt) == GFX_TRUE)
		{
			laScrollBarWidget_StepBackward(bar);
			
			//printf("bar up event\n");

			laWidget_Invalidate((laWidget*)bar);
		}
	}
	else if(bar->state == LA_SCROLLBAR_STATE_BOTTOM_INSIDE)
	{
		_laScrollBar_GetDownRightButtonRect(bar, &rect);
    
        laUtils_ClipRectToParent((laWidget*)bar, &rect);
	    laUtils_RectToScreenSpace((laWidget*)bar, &rect);

		if(GFX_RectContainsPoint(&rect, &pnt) == GFX_TRUE)
		{
			laScrollBarWidget_StepForward(bar);
			
			//printf("bar down event\n");

			laWidget_Invalidate((laWidget*)bar);
		}
	}
    
    bar->state = LA_SCROLLBAR_STATE_NONE;
	
	laWidget_Invalidate((laWidget*)bar);
}

void _laScrollBarWidget_TouchMovedEvent(laScrollBarWidget* bar,
							         laInput_TouchMovedEvent* evt)
{
	GFX_Rect rect = bar->widget.rect;
	GFX_Point pnt;
	uint32_t percent;
	uint32_t val;

	pnt.x = evt->x;
	pnt.y = evt->y;

	evt->event.accepted = LA_TRUE;

	if(bar->state == LA_SCROLLBAR_STATE_TOP_PRESSED ||
	   bar->state == LA_SCROLLBAR_STATE_TOP_INSIDE)
	{
		_laScrollBar_GetUpLeftButtonRect(bar, &rect);
    
        laUtils_ClipRectToParent((laWidget*)bar, &rect);
	    laUtils_RectToScreenSpace((laWidget*)bar, &rect);

		if(bar->state == LA_SCROLLBAR_STATE_TOP_INSIDE &&
		   GFX_RectContainsPoint(&rect, &pnt) == GFX_FALSE)
		{
			bar->state = LA_SCROLLBAR_STATE_TOP_PRESSED;

			laWidget_Invalidate((laWidget*)bar);
		}
		else if(bar->state == LA_SCROLLBAR_STATE_TOP_PRESSED &&
		   GFX_RectContainsPoint(&rect, &pnt) == GFX_TRUE)
		{
			bar->state = LA_SCROLLBAR_STATE_TOP_INSIDE;

			laWidget_Invalidate((laWidget*)bar);
		}
	}
	else if(bar->state == LA_SCROLLBAR_STATE_BOTTOM_PRESSED ||
	        bar->state == LA_SCROLLBAR_STATE_BOTTOM_INSIDE)
	{
		_laScrollBar_GetDownRightButtonRect(bar, &rect);
    
        laUtils_ClipRectToParent((laWidget*)bar, &rect);
	    laUtils_RectToScreenSpace((laWidget*)bar, &rect);

		if(bar->state == LA_SCROLLBAR_STATE_BOTTOM_INSIDE &&
		   GFX_RectContainsPoint(&rect, &pnt) == GFX_FALSE)
		{
			bar->state = LA_SCROLLBAR_STATE_BOTTOM_PRESSED;

			laWidget_Invalidate((laWidget*)bar);
		}
		else if(bar->state == LA_SCROLLBAR_STATE_BOTTOM_PRESSED &&
		   GFX_RectContainsPoint(&rect, &pnt) == GFX_TRUE)
		{
			bar->state = LA_SCROLLBAR_STATE_BOTTOM_INSIDE;

			laWidget_Invalidate((laWidget*)bar);
		}
	}
	else if(bar->state == LA_SCROLLBAR_STATE_HANDLE_DOWN)
	{
	    //_laScrollBar_GetDownRightButtonRect(bar, &rect);
	    
	    
	    
	    pnt.x = evt->x - bar->handleDownOffset.x;
	    pnt.y = evt->y - bar->handleDownOffset.y;
	    
	    //printf("%i, %i\n", pnt.x, pnt.y);
	    
        percent = _laScrollBar_GetPercentFromPoint(bar, &pnt);
        
        //if(percent > 80)
        //    percent = percent;
        
        val = _laScrollBar_GetValueFromPercent(bar, percent);
        
        //if(bar->value >= 1)
        //    percent = percent;
            
        //printf("%u, %i\n", percent, bar->value);
        
        if(bar->value != val)
            laScrollBarWidget_SetScrollValue(bar, val);
	}
}

#endif // LA_SCROLLBAR_WIDGET_ENABLED