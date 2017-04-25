#include "gfx/libaria/inc/libaria_widget_touchtest.h"

#if LA_TOUCHTEST_WIDGET_ENABLED

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
    DRAW_LINES,
    DRAW_BORDER,
};

static void drawBackground(laTouchTestWidget* tch);
static void drawLines(laTouchTestWidget* tch);
static void drawBorder(laTouchTestWidget* tch);

static void drawBackground(laTouchTestWidget* tch)
{
    GFX_Rect rect;
	
	if(tch->widget.drawBackground == LA_TRUE)
	{
	    rect = tch->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)tch->widget.parent, &rect);
	    
		GFX_Set(GFXF_DRAW_COLOR, tch->widget.scheme->base);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(tch->widget.rect.x,
					 tch->widget.rect.y,
					 tch->widget.rect.width,
					 tch->widget.rect.height);
	}
	
	if(tch->size != 0)
	{
	    tch->widget.drawState = DRAW_LINES;
	    tch->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawLines;
	}
	else if(tch->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    tch->widget.drawState = DRAW_BORDER;
	    tch->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        tch->widget.drawState = DONE;
        tch->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    tch->widget.drawFunc(tch);
}

static void drawLines(laTouchTestWidget* tch)
{
    GFX_Rect rect;
    GFX_Point pnt;
    uint32_t per;
    uint32_t i, j;
    GFX_Color c1, c2;
    
    rect = tch->widget.rect;
	    
	laUtils_RectToLayerSpace((laWidget*)tch->widget.parent, &rect);
    
    // draw lines
    j = tch->start;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    for(i = 0; i < tch->size; i++)
    {
        if(j >= tch->size)
            j = 0;
        
        pnt = tch->pnts[j];
        
        per = GFX_PercentWholeRounded(pnt.y, rect.height);
        
        //printf("per: %i, %u\n", j, per);
        
        c1 = tch->widget.scheme->foreground;
        c2 = tch->widget.scheme->foregroundInactive;
        
        GFX_Set(GFXF_DRAW_COLOR, GFX_ColorLerp(c1,
                                               c2,
                                               per,
                                               laContext_GetActive()->colorMode));
        
        GFX_DrawLine(rect.x, rect.y + pnt.y, rect.x + rect.width, rect.y + pnt.y);
        
        per = GFX_PercentWholeRounded(pnt.x, rect.width);
        
        c1 = tch->widget.scheme->background;
        c2 = tch->widget.scheme->backgroundInactive;
        
        GFX_Set(GFXF_DRAW_COLOR, GFX_ColorLerp(c1,
                                               c2,
                                               per,
                                               laContext_GetActive()->colorMode));
        
        GFX_DrawLine(rect.x + pnt.x, rect.y, rect.x + pnt.x, rect.y + rect.height);
        
        j++;
    }

	if(tch->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    tch->widget.drawState = DRAW_BORDER;
	    tch->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        tch->widget.drawState = DONE;
        tch->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    tch->widget.drawFunc(tch);
}

static void drawBorder(laTouchTestWidget* tch)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(tch->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = tch->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)tch->widget.parent, &rect);
	    
		laDraw_LineBorder(&rect, tch->widget.scheme->shadowDark);
	}
	else if(tch->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = tch->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)tch->widget.parent, &rect);
	    
		laDraw_2x2BevelBorder(&tch->widget.rect,
						      tch->widget.scheme->highlightLight,
						      tch->widget.scheme->highlightLight,
						      tch->widget.scheme->shadow,
							  tch->widget.scheme->shadowDark);
	}
	
	tch->widget.drawState = DONE;
	tch->widget.drawFunc = NULL;
}

void _laTouchTestWidget_Paint(laTouchTestWidget* tch)
{
    if(tch->widget.scheme == NULL)
    {
        tch->widget.drawState = DONE;
        
        return;
    }
    
	if (tch->state == LA_TOUCHTEST_STATE_UP)
	{
		if (tch->widget.drawState == NOT_STARTED)
			tch->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
	}
	else
	{
		if (tch->size != 0)
		{
			tch->widget.drawState = DRAW_LINES;
			tch->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawLines;
		}
	}
	
	tch->widget.drawFunc((laWidget*)tch);
}

#endif // LA_TOUCHTEST_WIDGET_ENABLED