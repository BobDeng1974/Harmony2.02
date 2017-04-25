#include "gfx/libaria/inc/libaria_widget_circle.h"

#if LA_CIRCLE_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

enum
{
    NOT_STARTED = LA_WIDGET_DRAW_STATE_READY,
    DONE = LA_WIDGET_DRAW_STATE_DONE,
    DRAW_CIRCLE,
    DRAW_BORDER,
};

static void drawBackground(laCircleWidget* cir);
static void drawCircle(laCircleWidget* cir);
static void drawBorder(laCircleWidget* cir);

static void drawBackground(laCircleWidget* cir)
{
    GFX_Rect rect;
	
	//printf("image painting\n");
	
	if(cir->widget.drawBackground == LA_TRUE)
	{
	    rect = cir->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)cir->widget.parent, &rect);
	    
		GFX_Set(GFXF_DRAW_COLOR, cir->widget.scheme->base);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(cir->widget.rect.x,
					 cir->widget.rect.y,
					 cir->widget.rect.width,
					 cir->widget.rect.height);
	}
	
    cir->widget.drawState = DRAW_CIRCLE;
	cir->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawCircle;
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    cir->widget.drawFunc(cir);
}

static void drawCircle(laCircleWidget* cir)
{
    GFX_Point p;
    
    p.x = cir->x;
    p.y = cir->y;
    
    laUtils_PointToScreenSpace((laWidget*)cir, &p);
    
    GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_LINE);
    GFX_Set(GFXF_DRAW_COLOR, cir->widget.scheme->foreground);
    GFX_DrawCircle(p.x, p.y, cir->radius);
    
    if(cir->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    cir->widget.drawState = DRAW_BORDER;
	    cir->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        cir->widget.drawState = DONE;
        cir->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    cir->widget.drawFunc(cir);
}

static void drawBorder(laCircleWidget* cir)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(cir->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = cir->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)cir->widget.parent, &rect);
	    
		laDraw_LineBorder(&rect, cir->widget.scheme->shadowDark);
	}
	else if(cir->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = cir->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)cir, &rect);
	    
		laDraw_2x2BevelBorder(&cir->widget.rect,
						      cir->widget.scheme->highlightLight,
						      cir->widget.scheme->highlightLight,
						      cir->widget.scheme->shadow,
							  cir->widget.scheme->shadowDark);
	}
	
	cir->widget.drawState = DONE;
	cir->widget.drawFunc = NULL;
}

void _laCircleWidget_Paint(laCircleWidget* cir)
{
    if(cir->widget.scheme == NULL)
    {
        cir->widget.drawState = DONE;
        
        return;
    }
    
    if(cir->widget.drawState == NOT_STARTED)
    {
        if(cir->widget.drawBackground == LA_TRUE)
            cir->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
        else
            cir->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawCircle;
	}
	
	cir->widget.drawFunc((laWidget*)cir);
}

#endif // LA_CIRCLE_WIDGET_ENABLED