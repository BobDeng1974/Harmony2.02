#include "gfx/libaria/inc/libaria_widget_line.h"

#if LA_LINE_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

enum
{
    NOT_STARTED = LA_WIDGET_DRAW_STATE_READY,
    DONE = LA_WIDGET_DRAW_STATE_DONE,
    DRAW_LINE,
    DRAW_BORDER,
};

static void drawBackground(laLineWidget* line);
static void drawLine(laLineWidget* line);
static void drawBorder(laLineWidget* line);

static void drawBackground(laLineWidget* line)
{
    GFX_Rect rect;
	
	//printf("image painting\n");
	
	if(line->widget.drawBackground == LA_TRUE)
	{
	    rect = line->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)line->widget.parent, &rect);
	    
		GFX_Set(GFXF_DRAW_COLOR, line->widget.scheme->base);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(line->widget.rect.x,
					 line->widget.rect.y,
					 line->widget.rect.width,
					 line->widget.rect.height);
	}
	
    line->widget.drawState = DRAW_LINE;
	line->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawLine;
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    line->widget.drawFunc(line);
}

static void drawLine(laLineWidget* line)
{
    GFX_Point p1, p2;
    
    p1.x = line->x1;
    p1.y = line->y1;
    p2.x = line->x2;
    p2.y = line->y2;
    
    laUtils_PointToScreenSpace((laWidget*)line, &p1);
    laUtils_PointToScreenSpace((laWidget*)line, &p2);
    
    GFX_Set(GFXF_DRAW_COLOR, line->widget.scheme->foreground);
    GFX_DrawLine(p1.x, p1.y, p2.x, p2.y);
    
    if(line->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    line->widget.drawState = DRAW_BORDER;
	    line->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        line->widget.drawState = DONE;
        line->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    line->widget.drawFunc(line);
}

static void drawBorder(laLineWidget* line)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(line->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = line->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)line->widget.parent, &rect);
	    
		laDraw_LineBorder(&rect, line->widget.scheme->shadowDark);
	}
	else if(line->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = line->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)line, &rect);
	    
		laDraw_2x2BevelBorder(&line->widget.rect,
						      line->widget.scheme->highlightLight,
						      line->widget.scheme->highlightLight,
						      line->widget.scheme->shadow,
							  line->widget.scheme->shadowDark);
	}
	
	line->widget.drawState = DONE;
	line->widget.drawFunc = NULL;
}

void _laLineWidget_Paint(laLineWidget* line)
{
    if(line->widget.scheme == NULL)
    {
        line->widget.drawState = DONE;
        
        return;
    }
    
    if(line->widget.drawState == NOT_STARTED)
    {
        if(line->widget.drawBackground == LA_TRUE)
            line->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
        else
            line->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawLine;
	}
	
	line->widget.drawFunc((laWidget*)line);
}

#endif // LA_LINE_WIDGET_ENABLED