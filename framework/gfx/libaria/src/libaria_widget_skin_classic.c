#include "gfx/libaria/inc/libaria_widget.h"

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_utils.h"

enum
{
    NOT_STARTED = LA_WIDGET_DRAW_STATE_READY,
    DONE = LA_WIDGET_DRAW_STATE_DONE,
    DRAW_BORDER,
};

static void drawBackground(laWidget* wdg);
static void drawBorder(laWidget* wdg);

static void drawBackground(laWidget* wdg)
{
    GFX_Rect rect;
	
	//printf("button painting\n");
	
	if(wdg->drawBackground == LA_TRUE)
	{
	    rect = wdg->rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToScreenSpace(wdg, &rect);
	    
		GFX_Set(GFXF_DRAW_COLOR, wdg->scheme->base);
        GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(rect.x, rect.y, rect.width, rect.height);
	}
	
	if(wdg->borderType != LA_WIDGET_BORDER_NONE)
	{
	    wdg->drawState = DRAW_BORDER;
	    wdg->drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
	{
	    wdg->drawState = DONE;
	    wdg->drawFunc = NULL;
	    
	    return;
	}
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    wdg->drawFunc((laWidget*)wdg);
}

static void drawBorder(laWidget* wdg)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(wdg->borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = wdg->rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace(wdg, &rect);
	    
		laDraw_LineBorder(&rect, wdg->scheme->shadowDark);
	}
	else if(wdg->borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = wdg->rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace(wdg, &rect);
	    
		laDraw_2x2BevelBorder(&wdg->rect,
						      wdg->scheme->highlightLight,
						      wdg->scheme->highlightLight,
						      wdg->scheme->shadow,
							  wdg->scheme->shadowDark);
	}
	
	wdg->drawState = DONE;
	wdg->drawFunc = NULL;
}

void _laWidget_Paint(laWidget* wdg)
{
    if(wdg->scheme == NULL)
    {
        wdg->drawState = DONE;
        
        return;
    }
    
    if(wdg->drawState == NOT_STARTED)
        wdg->drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
	
	wdg->drawFunc((laWidget*)wdg);
}