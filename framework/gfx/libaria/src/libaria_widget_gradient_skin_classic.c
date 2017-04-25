#include "gfx/libaria/inc/libaria_widget_gradient.h"

#if LA_GRADIENT_WIDGET_ENABLED

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
};

static void drawBackground(laGradientWidget* grad);
static void drawBorder(laGradientWidget* grad);

static void drawBackground(laGradientWidget* grad)
{
    GFX_Rect rect;
	GFX_Color lclr, rclr;
	uint32_t flag;
	
	//printf("image painting\n");
	
	if(grad->widget.drawBackground == LA_TRUE)
	{
	    rect = grad->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)grad->widget.parent, &rect);
	    
	    if(grad->dir == LA_GRADIENT_DIRECTION_RIGHT ||
	       grad->dir == LA_GRADIENT_DIRECTION_DOWN)
        {
            lclr = grad->widget.scheme->foreground;
            rclr = grad->widget.scheme->foregroundInactive;
        }
        else
        {
            lclr = grad->widget.scheme->foregroundInactive;
            rclr = grad->widget.scheme->foreground;
        }
	    
	    if(grad->dir == LA_GRADIENT_DIRECTION_RIGHT ||
	       grad->dir == LA_GRADIENT_DIRECTION_LEFT)
        {
            flag = GFX_DRAW_GRADIENT_LEFT_RIGHT;
        }
        else
        {
            flag = GFX_DRAW_GRADIENT_TOP_BOTTOM;
        }
        
		GFX_Set(GFXF_DRAW_GRADIENT_COLOR, lclr, rclr, NULL, NULL);
		GFX_Set(GFXF_DRAW_MODE, flag);
		//GFX_Set(GFXF_DRAW_COLOR, GFX_ColorValue(GFX_COLOR_MODE_RGB_565, GFX_COLOR_MAGENTA));
		//GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		
		GFX_DrawRect(rect.x, rect.y, rect.width, rect.height);
	}
	
	if(grad->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    grad->widget.drawState = DRAW_BORDER;
	    grad->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        grad->widget.drawState = DONE;
        grad->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    grad->widget.drawFunc(grad);
}

#if 0
static void drawEdge(laGradientWidget* grad)
{
    GFX_Rect rect;
    
    rect = grad->widget.rect;
    rect.x = 0;
    rect.y = 0;
    
    // move the rect to parent space
    laUtils_RectToScreenSpace((laWidget*)grad, &rect);
    //laUtils_RectToLayerSpace((laWidget*)rect->widget.parent, &rect);
    //rect.x += rect->widget.rect.x;
    //rect.y += rect->widget.rect.y;
    
    GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
    GFX_Set(GFXF_DRAW_COLOR, grad->widget.scheme->foreground);
    
    // left bar
    GFX_DrawRect(rect.x,
                 rect.y,
                 grad->thickness,
                 rect.height);
                 
    // top bar
    GFX_DrawRect(rect.x + grad->thickness,
                 rect.y,
                 rect.width - (grad->thickness * 2),
                 grad->thickness);
                 
    // right bar
    GFX_DrawRect(rect.x + rect.width - grad->thickness,
                 rect.y,
                 grad->thickness,
                 rect.height);
                 
    // bottom bar
    GFX_DrawRect(rect.x + grad->thickness,
                 rect.y + rect.height - grad->thickness,
                 rect.width - (grad->thickness * 2),
                 grad->thickness);
                
    if(grad->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    grad->widget.drawState = DRAW_BORDER;
	    grad->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        grad->widget.drawState = DONE;
        grad->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    grad->widget.drawFunc(grad);
}
#endif

static void drawBorder(laGradientWidget* grad)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(grad->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = grad->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)grad->widget.parent, &rect);
	    
		laDraw_LineBorder(&rect, grad->widget.scheme->shadowDark);
	}
	else if(grad->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = grad->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)grad, &rect);
	    
		laDraw_2x2BevelBorder(&grad->widget.rect,
						      grad->widget.scheme->highlightLight,
						      grad->widget.scheme->highlightLight,
						      grad->widget.scheme->shadow,
							  grad->widget.scheme->shadowDark);
	}
	
	grad->widget.drawState = DONE;
	grad->widget.drawFunc = NULL;
}

void _laGradientWidget_Paint(laGradientWidget* grad)
{
    if(grad->widget.scheme == NULL)
    {
        grad->widget.drawState = DONE;
        
        return;
    }
    
    if(grad->widget.drawState == NOT_STARTED)
    {
        if(grad->widget.drawBackground == LA_TRUE)
            grad->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
        else if(grad->widget.borderType != LA_WIDGET_BORDER_NONE)
            grad->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
        else
        {
            grad->widget.drawState = DONE;
            
            return;
        }
	}
	
	grad->widget.drawFunc((laWidget*)grad);
}

#endif // LA_GRADIENT_WIDGET_ENABLED