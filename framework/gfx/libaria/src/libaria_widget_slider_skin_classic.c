#include "gfx/libaria/inc/libaria_widget_slider.h"

#if LA_SLIDER_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

enum
{
    NOT_STARTED = LA_WIDGET_DRAW_STATE_READY,
    DONE = LA_WIDGET_DRAW_STATE_DONE,
    DRAW_BORDER,
    DRAW_BAR,
    DRAW_HANDLE,
};

static void drawBackground(laSliderWidget* sld);
static void drawBar(laSliderWidget* sld);
static void drawHandle(laSliderWidget* sld);

static void drawBackground(laSliderWidget* sld)
{
    GFX_Rect rect = sld->widget.rect;
	
	//printf("button painting\n");
	
	if(sld->widget.drawBackground == LA_TRUE)
	{
	    laUtils_RectToScreenSpace(sld->widget.parent, &rect);
	    
		GFX_Set(GFXF_DRAW_COLOR, sld->widget.scheme->base);

        GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_DrawRect(rect.x,
					 rect.y,
					 rect.width,
					 rect.height);
	}
	
	sld->widget.drawState = DRAW_BAR;
	sld->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBar;
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    sld->widget.drawFunc((laWidget*)sld);
}

static void drawBar(laSliderWidget* sld)
{
    GFX_Rect rect;
    
    _laSlider_GetSlideAreaRect(sld, &rect);
    
    laUtils_ClipRectToParent((laWidget*)sld, &rect);
	laUtils_RectToScreenSpace((laWidget*)sld, &rect);
	
	// fill bar area
    GFX_Set(GFXF_DRAW_COLOR, sld->widget.scheme->background);
        
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
	GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
	
	GFX_DrawRect(rect.x,
				 rect.y,
				 rect.width,
				 rect.height);
				 
	// draw border
	GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(sld->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
		laDraw_LineBorder(&rect, sld->widget.scheme->shadowDark);
	}
	else if(sld->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
		laDraw_2x2BevelBorder(&rect,
			          sld->widget.scheme->shadowDark,
			          sld->widget.scheme->shadow,
			          sld->widget.scheme->highlight,
			          sld->widget.scheme->highlightLight);
    }
	
	sld->widget.drawState = DRAW_HANDLE;
	sld->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawHandle;
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    sld->widget.drawFunc((laWidget*)sld);
}

static void drawHandle(laSliderWidget* sld)
{
    GFX_Rect rect;
    
    _laSlider_GetHandleRect(sld, &rect);
    
    laUtils_ClipRectToParent((laWidget*)sld, &rect);
	laUtils_RectToScreenSpace((laWidget*)sld, &rect);
	
	//printf("drawing\n");
	
	// fill handle area       
    GFX_Set(GFXF_DRAW_COLOR, sld->widget.scheme->base);
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
	GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
	
	GFX_DrawRect(rect.x,
				 rect.y,
				 rect.width,
				 rect.height);
				 
    // draw handle border
    if(sld->widget.borderType == LA_WIDGET_BORDER_LINE)
    {
        laUtils_RectToLayerSpace((laWidget*)sld->widget.parent, &rect);
	    
		laDraw_LineBorder(&rect, sld->widget.scheme->shadowDark);
    }
    else if(sld->widget.borderType == LA_WIDGET_BORDER_BEVEL)
    {
	    laDraw_1x2BevelBorder(&rect,
			          sld->widget.scheme->highlightLight,
			          sld->widget.scheme->shadow,
			          sld->widget.scheme->shadowDark);
    }
	
	sld->widget.drawState = DONE;
	sld->widget.drawFunc = NULL;
}

void _laSliderWidget_Paint(laSliderWidget* sld)
{
    if(sld->widget.scheme == NULL)
    {
        sld->widget.drawState = DONE;
        
        return;
    }
    
    if(sld->widget.drawState == NOT_STARTED)
        sld->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
	
	sld->widget.drawFunc((laWidget*)sld);
}

#endif // LA_SLIDER_WIDGET_ENABLED