#include "gfx/libaria/inc/libaria_widget_progressbar.h"

#if LA_PROGRESSBAR_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#include "gfx/hal/inc/gfx_math.h"
#include "gfx/hal/inc/gfx_util.h"

enum
{
    NOT_STARTED = LA_WIDGET_DRAW_STATE_READY,
    DONE = LA_WIDGET_DRAW_STATE_DONE,
    DRAW_FILL,
    DRAW_BORDER,
};

static void drawBackground(laProgressBarWidget* bar);
static void drawFill(laProgressBarWidget* bar);
static void drawBorder(laProgressBarWidget* bar);

static void drawBackground(laProgressBarWidget* bar)
{
    GFX_Rect rect;
	
	//printf("image painting\n");
	
	if(bar->widget.drawBackground == LA_TRUE)
	{
	    rect = bar->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)bar->widget.parent, &rect);
	    
		GFX_Set(GFXF_DRAW_COLOR, bar->widget.scheme->background);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(bar->widget.rect.x,
					 bar->widget.rect.y,
					 bar->widget.rect.width,
					 bar->widget.rect.height);
	}
	
	if(bar->value > 0)
	{
	    bar->widget.drawState = DRAW_FILL;
	    bar->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawFill;
	}
	else if(bar->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    bar->widget.drawState = DRAW_BORDER;
	    bar->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        bar->widget.drawState = DONE;
        bar->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    bar->widget.drawFunc(bar);
}

static void drawFill(laProgressBarWidget* bar)
{
    GFX_Rect rect;
    GFX_Rect fill = {0};
    
    rect = bar->widget.rect;
    rect.x = 0;
    rect.y = 0;
    
    // move the rect to parent space
    laUtils_RectToScreenSpace((laWidget*)bar, &rect);

    // fill bar
    if(bar->direction == LA_PROGRESSBAR_DIRECTION_RIGHT)
    {
        fill.x = rect.x;
        fill.y = rect.y;
        fill.width = GFX_PercentOf(rect.width, bar->value);
        fill.height = rect.height;
    }
    else if(bar->direction == LA_PROGRESSBAR_DIRECTION_UP)
    {
        fill.height = GFX_PercentOf(rect.height, bar->value);
        fill.x = rect.x;
        fill.y = rect.y + rect.height - fill.height;
        fill.width = rect.width;
        
    }
    else if(bar->direction == LA_PROGRESSBAR_DIRECTION_LEFT)
    {
        fill.width = GFX_PercentOf(rect.width, bar->value);
        fill.x = rect.x + rect.width - fill.width;
        fill.y = rect.y;
        fill.height = rect.height;
    }
    else if(bar->direction == LA_PROGRESSBAR_DIRECTION_DOWN)
    {
        fill.x = rect.x;
        fill.y = rect.y;
        fill.width = rect.width;
        fill.height = GFX_PercentOf(rect.height, bar->value);
    }
    
    GFX_Set(GFXF_DRAW_COLOR, bar->widget.scheme->textHighlight);
    GFX_DrawRect(fill.x, fill.y, fill.width, fill.height);
                 
    if(bar->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    bar->widget.drawState = DRAW_BORDER;
	    bar->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        bar->widget.drawState = DONE;
        bar->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    bar->widget.drawFunc(bar);
}

static void drawBorder(laProgressBarWidget* bar)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(bar->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = bar->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)bar->widget.parent, &rect);
	    
		laDraw_LineBorder(&rect, bar->widget.scheme->shadowDark);
	}
	else if(bar->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = bar->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)bar, &rect);
	    
		laDraw_2x2BevelBorder(&rect,
						      bar->widget.scheme->shadow,
						      bar->widget.scheme->shadowDark,
						      bar->widget.scheme->highlight,
						      bar->widget.scheme->highlightLight);
	}
	
	bar->widget.drawState = DONE;
	bar->widget.drawFunc = NULL;
}

void _laProgressBarWidget_Paint(laProgressBarWidget* bar)
{
    if(bar->widget.scheme == NULL)
    {
        bar->widget.drawState = DONE;
        
        return;
    }
    
    if(bar->widget.drawState == NOT_STARTED)
    {
        if(bar->widget.drawBackground == LA_TRUE)
            bar->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
        else if(bar->value > 0)
            bar->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawFill;
        else if(bar->widget.borderType != LA_WIDGET_BORDER_NONE)
            bar->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
        else
        {
            bar->widget.drawState = DONE;
            
            return;
        }
	}
	
	bar->widget.drawFunc((laWidget*)bar);
}

#endif // LA_PROGRESSBAR_WIDGET_ENABLED