#include "gfx/libaria/inc/libaria_widget_drawsurface.h"

#if LA_DRAWSURFACE_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

enum
{
    NOT_STARTED = LA_WIDGET_DRAW_STATE_READY,
    DONE = LA_WIDGET_DRAW_STATE_DONE,
    DRAW_CALLBACK,
    DRAW_BORDER,
};

static void drawBackground(laDrawSurfaceWidget* sfc);
static void drawCallback(laDrawSurfaceWidget* sfc);
static void drawBorder(laDrawSurfaceWidget* sfc);

static void drawBackground(laDrawSurfaceWidget* sfc)
{
    GFX_Rect rect;
	
	if(sfc->widget.drawBackground == LA_TRUE)
	{
	    rect = sfc->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)sfc->widget.parent, &rect);
	    
		GFX_Set(GFXF_DRAW_COLOR, sfc->widget.scheme->base);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(sfc->widget.rect.x,
					 sfc->widget.rect.y,
					 sfc->widget.rect.width,
					 sfc->widget.rect.height);
	}
	
	if(sfc->cb != NULL)
	{
	    sfc->widget.drawState = DRAW_CALLBACK;
	    sfc->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawCallback;
	}
	else if(sfc->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    sfc->widget.drawState = DRAW_BORDER;
	    sfc->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        sfc->widget.drawState = DONE;
        sfc->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    sfc->widget.drawFunc(sfc);
}

static void drawCallback(laDrawSurfaceWidget* sfc)
{
    GFX_Rect rect;
    
    // paint callback
    if(sfc->cb != NULL)
    {
        rect = sfc->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)sfc->widget.parent, &rect);
	    
        if(sfc->cb(sfc, &rect) == LA_FALSE)
            return;
    }
    
	if(sfc->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    sfc->widget.drawState = DRAW_BORDER;
	    sfc->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        sfc->widget.drawState = DONE;
        sfc->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    sfc->widget.drawFunc(sfc);
}

static void drawBorder(laDrawSurfaceWidget* sfc)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(sfc->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = sfc->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)sfc->widget.parent, &rect);
	    
		laDraw_LineBorder(&rect, sfc->widget.scheme->shadowDark);
	}
	else if(sfc->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = sfc->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)sfc->widget.parent, &rect);
	    
		laDraw_2x2BevelBorder(&sfc->widget.rect,
						      sfc->widget.scheme->highlightLight,
						      sfc->widget.scheme->highlightLight,
						      sfc->widget.scheme->shadow,
							  sfc->widget.scheme->shadowDark);
	}
	
	sfc->widget.drawState = DONE;
	sfc->widget.drawFunc = NULL;
}

void _laDrawSurfaceWidget_Paint(laDrawSurfaceWidget* sfc)
{
    if(sfc->widget.scheme == NULL)
    {
        sfc->widget.drawState = DONE;
        
        return;
    }
    
    if(sfc->widget.drawState == NOT_STARTED)
        sfc->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
	
	sfc->widget.drawFunc((laWidget*)sfc);
}

#endif // LA_DRAWSURFACE_WIDGET_ENABLED