#include "gfx/libaria/inc/libaria_widget_slider.h"

#if LA_SLIDER_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_widget.h"
#include "gfx/libaria/inc/libaria_utils.h"

#include "gfx/hal/inc/gfx_math.h"
#include "gfx/hal/inc/gfx_util.h"

#define DEFAULT_WIDTH           20
#define DEFAULT_HEIGHT          100

#define DEFAULT_MIN             0
#define DEFAULT_MAX             100
#define DEFAULT_VALUE           0

#define DEFAULT_STEP            1

#define DEFAULT_GRIP            10

void _laSlider_GetSlideAreaRect(laSliderWidget* sld, GFX_Rect* rect)
{
    GFX_Rect scrollRect;
    
    if(sld->alignment == LA_SLIDER_ORIENT_VERTICAL)
    {
        scrollRect.width = sld->widget.rect.width / 4;
        scrollRect.height = sld->widget.rect.height - sld->grip;
        scrollRect.x = (sld->widget.rect.width / 2) - (scrollRect.width / 2);
        scrollRect.y = sld->grip / 2;
    }
    else
    {
        scrollRect.width = sld->widget.rect.width - sld->grip;
        scrollRect.height = sld->widget.rect.height / 4;
        scrollRect.x = sld->grip / 2;
        scrollRect.y = (sld->widget.rect.height / 2) - (scrollRect.height / 2);
    }
    
    *rect = scrollRect;
}

void _laSlider_GetHandleRect(laSliderWidget* sld, GFX_Rect* rect)
{
    GFX_Rect scrollRect;
    uint32_t val, max, percent;
    
    val = sld->value - sld->min;
    max = sld->max - sld->min;
    
    percent = GFX_PercentWholeRounded(val, max);
    
    _laSlider_GetSlideAreaRect(sld, &scrollRect);
    
    if(sld->alignment == LA_SLIDER_ORIENT_VERTICAL)
    {
        percent = GFX_PercentOf(scrollRect.height, percent);
        
        rect->x = 0;
        rect->y = ((scrollRect.y + scrollRect.height) - percent) - (sld->grip / 2);
        rect->width = sld->widget.rect.width;
        rect->height = sld->grip;
    }
    else
    {
        percent = GFX_PercentOf(scrollRect.width, percent);
        
        rect->x = (scrollRect.x + percent) - (sld->grip / 2);
        rect->y = 0;
        rect->width = sld->grip;
        rect->height = sld->widget.rect.height;
    }
}

uint32_t _laSlider_GetPercentFromPoint(laSliderWidget* sld, GFX_Point* pnt)
{
    GFX_Rect scrollRect;
    int32_t val;
    
    _laSlider_GetSlideAreaRect(sld, &scrollRect);
    
    laUtils_ClipRectToParent((laWidget*)sld, &scrollRect);
	laUtils_RectToScreenSpace((laWidget*)sld, &scrollRect);
    
    if(sld->alignment == LA_SLIDER_ORIENT_VERTICAL)
    {
        // translate rect and point in to rect space
        val = scrollRect.height - (pnt->y - scrollRect.y);
        scrollRect.y = 0;
        
        if(val <= 0)
            return 0;
        else if(val >= scrollRect.height)
            return 100;
            
        return GFX_PercentWholeRounded(val, scrollRect.height);
    }
    else
    {
        // translate rect and point in to rect space
        val = pnt->x - scrollRect.x;
        scrollRect.x = 0;
        
        if(val <= 0)
            return 0;
        else if(val >= scrollRect.width)
            return 100;
        
        return GFX_PercentWholeRounded(val, scrollRect.width);
    }
}

uint32_t _laSlider_GetValueFromPercent(laSliderWidget* sld, uint32_t per)
{
    int32_t max, val;
    
    if(per == 0)
        return sld->min;
    else if(per == 100)
        return sld->max;
    
    // zero based range
    max = sld->max - sld->min;
    
    val = GFX_PercentOf(max, per);
        
    return val - sld->min;
}

void _laSliderWidget_Constructor(laSliderWidget* sld)
{
	_laWidget_Constructor((laWidget*)sld);
	
	sld->widget.destructor = (laWidget_Destructor_FnPtr)&_laSliderWidget_Destructor;

	sld->widget.type = LA_WIDGET_SLIDER;

	// override base class methods
	sld->widget.update = (laWidget_Update_FnPtr)&_laSliderWidget_Update;
	sld->widget.paint = (laWidget_Paint_FnPtr)&_laSliderWidget_Paint;

	sld->widget.rect.width = DEFAULT_WIDTH;
	sld->widget.rect.height = DEFAULT_HEIGHT;

	sld->state = LA_SLIDER_STATE_NONE;

	sld->widget.borderType = LA_WIDGET_BORDER_BEVEL;
	sld->widget.drawBackground = LA_FALSE;

	sld->alignment = LA_SLIDER_ORIENT_VERTICAL;
	
	sld->min = DEFAULT_MIN;
	sld->max = DEFAULT_MAX;
	sld->value = DEFAULT_VALUE;
	sld->grip = DEFAULT_GRIP;

	sld->widget.touchDown = (laWidget_TouchDownEvent_FnPtr)&_laSliderWidget_TouchDownEvent;
	sld->widget.touchUp = (laWidget_TouchUpEvent_FnPtr)&_laSliderWidget_TouchUpEvent;
	sld->widget.touchMoved = (laWidget_TouchMovedEvent_FnPtr)&_laSliderWidget_TouchMovedEvent;
}

void _laSliderWidget_Destructor(laSliderWidget* sld)
{
	_laWidget_Destructor((laWidget*)sld);
}

void _laSliderWidget_Update(laSliderWidget* sld)
{

}

laSliderWidget* laSliderWidget_New()
{
	laSliderWidget* sld = NULL;

	if(laContext_GetActive() == NULL)
		return NULL;

	sld = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laSliderWidget));
    
	_laSliderWidget_Constructor(sld);

	return sld;
}

laSliderOrientation laSliderWidget_GetOrientation(laSliderWidget* sld)
{
	if(sld == NULL)
		return 0;

	return sld->alignment;
}

laResult laSliderWidget_SetOrientation(laSliderWidget* sld,
								       laSliderOrientation align,
								       laBool swapDimensions)
{
    uint32_t t;
    
	if(sld == NULL)
		return LA_FAILURE;
		
    if(sld->alignment == align)
        return LA_SUCCESS;

	sld->alignment = align;
	
	// reverse dimensions
	if(swapDimensions == LA_TRUE)
	{
	    t = sld->widget.rect.width;
	    sld->widget.rect.width = sld->widget.rect.height;
	    sld->widget.rect.height = t;
    }
    
	laWidget_Invalidate((laWidget*)sld);
	
	return LA_SUCCESS;
}

laSliderOrientation laSliderWidget_GetGripSize(laSliderWidget* sld)
{
    if(sld == NULL)
        return 0;
        
    return sld->grip;
}

laResult laSliderWidget_SetGripSize(laSliderWidget* sld, uint32_t size)
{
    if(sld == NULL)
        return LA_FAILURE;
        
    if(sld->grip == size)
        return LA_SUCCESS;
        
    sld->grip = size;
    
    laWidget_Invalidate((laWidget*)sld);
        
    return LA_SUCCESS;
}

uint32_t laSliderWidget_GetMininumValue(laSliderWidget* sld)
{
    if(sld == NULL)
        return 0;
        
    return sld->min;
}

laResult laSliderWidget_SetMinimumValue(laSliderWidget* sld, 
                                           uint32_t val)
{
    if(sld == NULL)
        return LA_FAILURE;
        
    if(sld->min == val)
        return LA_SUCCESS;
        
    sld->min = val;
    
    laWidget_Invalidate((laWidget*)sld);
    
    if(sld->valueChangedEvent != NULL)
        sld->valueChangedEvent(sld);
        
    return LA_SUCCESS;
}
                                                      
uint32_t laSliderWidget_GetMaxinumValue(laSliderWidget* sld)
{
    if(sld == NULL)
        return 0;
        
    return sld->max;
}

laResult laSliderWidget_SetMaximumValue(laSliderWidget* sld,
                                        uint32_t val)
{
    if(sld == NULL)
        return LA_FAILURE;
        
    if(sld->max == val)
        return LA_SUCCESS;
        
    sld->max = val;
    
    laWidget_Invalidate((laWidget*)sld);
        
    if(sld->valueChangedEvent != NULL)
        sld->valueChangedEvent(sld);
        
    return LA_SUCCESS;
}                                                 

uint32_t laSliderWidget_GetSliderPercentage(laSliderWidget* sld)
{
    if(sld == NULL)
        return 0;
        
    return GFX_PercentWholeRounded(sld->value, sld->max - sld->min);
}

laResult laSliderWidget_SetSliderPercentage(laSliderWidget* sld,
                                            uint32_t val)
{
    if(sld == NULL)
        return LA_FAILURE;
        
    if(sld->value == val)
        return LA_SUCCESS;
        
    sld->value = val;
    
    laWidget_Invalidate((laWidget*)sld);
    
    if(sld->valueChangedEvent != NULL)
        sld->valueChangedEvent(sld);
        
    return LA_SUCCESS;
} 
                                                                                                               
int32_t laSliderWidget_GetSliderValue(laSliderWidget* sld)
{
    if(sld == NULL)
        return 0;
        
    return sld->value;
}

laResult laSliderWidget_SetSliderValue(laSliderWidget* sld, int32_t val) 
{
    if(sld == NULL)
        return LA_FAILURE;
        
    if(sld->value == val)
        return LA_SUCCESS;
        
    if(val > sld->max)
        val = sld->max;
        
    if(val < sld->min)
        val = sld->min;
        
    sld->value = val;
    
    laWidget_Invalidate((laWidget*)sld);
    
    if(sld->valueChangedEvent != NULL)
        sld->valueChangedEvent(sld);
        
    return LA_SUCCESS;
}

laResult laSliderWidget_Step(laSliderWidget* sld, int32_t amount)
{
    if(sld == NULL || amount == 0)
        return LA_FAILURE;
        
    if(amount < 0)
    {
        sld->value -= amount;
        
        if(sld->value < sld->min)
            sld->value = sld->min;
    }
    else
    {
        sld->value += amount;
        
        if(sld->value > sld->max)
            sld->value = sld->max;
    }
        
    if(sld->valueChangedEvent != NULL)
        sld->valueChangedEvent(sld);
        
    //printf("%u\n", sld->value);
        
    laWidget_Invalidate((laWidget*)sld);
        
    return LA_SUCCESS;
}

laSliderWidget_ValueChangedEvent laSliderWidget_GetValueChangedEventCallback(laSliderWidget* sld)
{
	if(sld == NULL)
		return NULL;

	return sld->valueChangedEvent;
}

void laSliderWidget_SetValueChangedEventCallback(laSliderWidget* sld,
											     laSliderWidget_ValueChangedEvent cb)
{
	if(sld == NULL || sld->valueChangedEvent == cb)
		return;

	sld->valueChangedEvent = cb;
}

void _laSliderWidget_TouchDownEvent(laSliderWidget* sld,
							        laInput_TouchDownEvent* evt)
{
    GFX_Rect rect;
    GFX_Point pnt;
    uint32_t percent;
    uint32_t value;

	pnt.x = evt->x;
	pnt.y = evt->y;
    
    // already guaranteed to be inside widget rectangle, accept event
	evt->event.accepted = LA_TRUE;
    
    // was the handle touched
    _laSlider_GetHandleRect(sld, &rect);
    
    laUtils_ClipRectToParent((laWidget*)sld, &rect);
	laUtils_RectToScreenSpace((laWidget*)sld, &rect);
    
    if(GFX_RectContainsPoint(&rect, &pnt) == GFX_TRUE)
    {
        sld->handleDownOffset.x = evt->x - rect.x - (rect.width / 2);
        sld->handleDownOffset.y = evt->y - rect.y - (rect.height / 2);
    }
    else
    {
        sld->handleDownOffset.x = 0;
        sld->handleDownOffset.y = 0;
        
        percent = _laSlider_GetPercentFromPoint(sld, &pnt);
        
        value = _laSlider_GetValueFromPercent(sld, percent);
        
        if(sld->value != value)
        {
            sld->value = value;
            
            laWidget_Invalidate((laWidget*)sld);
            
            if(sld->valueChangedEvent != NULL)
                sld->valueChangedEvent(sld);
        }
    }
    
    sld->state = LA_SLIDER_STATE_HANDLE_DOWN;
}

void _laSliderWidget_TouchUpEvent(laSliderWidget* sld,
							      laInput_TouchUpEvent* evt)
{
	evt->event.accepted = LA_TRUE;
    
    sld->state = LA_SLIDER_STATE_NONE;
}

void _laSliderWidget_TouchMovedEvent(laSliderWidget* sld,
							         laInput_TouchMovedEvent* evt)
{
	GFX_Point pnt;
	uint32_t percent;

	pnt.x = evt->x;
	pnt.y = evt->y;

	evt->event.accepted = LA_TRUE;

	if(sld->state == LA_SLIDER_STATE_HANDLE_DOWN)
	{
	    pnt.x = evt->x - sld->handleDownOffset.x;
	    pnt.y = evt->y - sld->handleDownOffset.y;
	    
	    //printf("%i, %i\n", pnt.x, pnt.y);
	    
        percent = _laSlider_GetPercentFromPoint(sld, &pnt);
        
        //printf("%u\n", percent);
        
        percent = _laSlider_GetValueFromPercent(sld, percent);
        
        //printf("    %u, %u\n", percent, i);
        
        if(percent != sld->value)
        {
            sld->value = percent;
            
            laWidget_Invalidate((laWidget*)sld);
            
            if(sld->valueChangedEvent != NULL)
                sld->valueChangedEvent(sld);
        }
	}
}

#endif // LA_SLIDER_WIDGET_ENABLED