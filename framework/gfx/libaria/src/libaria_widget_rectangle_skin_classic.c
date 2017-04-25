#include "gfx/libaria/inc/libaria_widget_rectangle.h"

#if LA_RECTANGLE_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

enum
{
    NOT_STARTED = LA_WIDGET_DRAW_STATE_READY,
    DONE = LA_WIDGET_DRAW_STATE_DONE,
    DRAW_EDGE,
    DRAW_BORDER,
};

static void drawBackground(laRectangleWidget* rect);
static void drawEdge(laRectangleWidget* rect);
static void drawBorder(laRectangleWidget* rect);

static void drawBackground(laRectangleWidget* rct)
{
    GFX_Rect rect;
	
	//printf("image painting\n");
	
	if(rct->widget.drawBackground == LA_TRUE)
	{
	    rect = rct->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)&rct->widget, &rect);
	    
		GFX_Set(GFXF_DRAW_COLOR, rct->widget.scheme->base);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(rect.x,
					 rect.y,
					 rect.width,
					 rect.height);
	}
	
	if(rct->thickness > 0)
	{
	    rct->widget.drawState = DRAW_EDGE;
	    rct->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawEdge;
	}
	else if(rct->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    rct->widget.drawState = DRAW_BORDER;
	    rct->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        rct->widget.drawState = DONE;
        rct->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    rct->widget.drawFunc(rct);
}

static void drawEdge(laRectangleWidget* rct)
{
    GFX_Rect rect;
    
    rect = rct->widget.rect;
    rect.x = 0;
    rect.y = 0;
    
    // move the rect to parent space
    laUtils_RectToScreenSpace((laWidget*)rct, &rect);
    //laUtils_RectToLayerSpace((laWidget*)rect->widget.parent, &rect);
    //rect.x += rect->widget.rect.x;
    //rect.y += rect->widget.rect.y;
    
    GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
    GFX_Set(GFXF_DRAW_COLOR, rct->widget.scheme->foreground);
    
    // left bar
    GFX_DrawRect(rect.x,
                 rect.y,
                 rct->thickness,
                 rect.height);
                 
    // top bar
    GFX_DrawRect(rect.x + rct->thickness,
                 rect.y,
                 rect.width - (rct->thickness * 2),
                 rct->thickness);
                 
    // right bar
    GFX_DrawRect(rect.x + rect.width - rct->thickness,
                 rect.y,
                 rct->thickness,
                 rect.height);
                 
    // bottom bar
    GFX_DrawRect(rect.x + rct->thickness,
                 rect.y + rect.height - rct->thickness,
                 rect.width - (rct->thickness * 2),
                 rct->thickness);
                
    if(rct->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    rct->widget.drawState = DRAW_BORDER;
	    rct->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        rct->widget.drawState = DONE;
        rct->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    rct->widget.drawFunc(rct);
}

static void drawBorder(laRectangleWidget* rct)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(rct->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = rct->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)rct->widget.parent, &rect);
	    
		laDraw_LineBorder(&rect, rct->widget.scheme->shadowDark);
	}
	else if(rct->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = rct->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)rct, &rect);
	    
		laDraw_2x2BevelBorder(&rct->widget.rect,
						      rct->widget.scheme->highlightLight,
						      rct->widget.scheme->highlightLight,
						      rct->widget.scheme->shadow,
							  rct->widget.scheme->shadowDark);
	}
	
	rct->widget.drawState = DONE;
	rct->widget.drawFunc = NULL;
}

void _laRectangleWidget_Paint(laRectangleWidget* rct)
{
    if(rct->widget.scheme == NULL)
    {
        rct->widget.drawState = DONE;
        
        return;
    }
    
    if(rct->widget.drawState == NOT_STARTED)
    {
        if(rct->widget.drawBackground == LA_TRUE)
            rct->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
        else if(rct->thickness > 0)
            rct->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawEdge;
        else if(rct->widget.borderType != LA_WIDGET_BORDER_NONE)
            rct->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
        else
        {
            rct->widget.drawState = DONE;
            
            return;
        }
	}
	
	rct->widget.drawFunc((laWidget*)rct);
}

#endif // LA_RECTANGLE_WIDGET_ENABLED