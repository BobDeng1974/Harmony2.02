#include "gfx/libaria/inc/libaria_widget_scrollbar.h"

#if LA_SCROLLBAR_WIDGET_ENABLED

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
    DRAW_UP_BUTTON,
    DRAW_DOWN_BUTTON,
    DRAW_HANDLE
};

static void drawBackground(laScrollBarWidget* bar);
static void drawUpButton(laScrollBarWidget* bar);
static void drawDownButton(laScrollBarWidget* bar);
static void drawHandle(laScrollBarWidget* bar);

static void drawBackground(laScrollBarWidget* bar)
{
    GFX_Rect rect = bar->widget.rect;
	
	//printf("button painting\n");
	
	if(bar->widget.drawBackground == LA_TRUE)
	{
	    laUtils_RectToScreenSpace(bar->widget.parent, &rect);
	    
		GFX_Set(GFXF_DRAW_COLOR, bar->widget.scheme->background);

        GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_DrawRect(rect.x,
					 rect.y,
					 rect.width,
					 rect.height);
	}
	
    bar->widget.drawState = DRAW_UP_BUTTON;
    bar->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawUpButton;
}

static void drawUpButton(laScrollBarWidget* bar)
{
    GFX_Rect rect;
    GFX_Point pnt;
    uint32_t arrowOffset = 0;
    
    _laScrollBar_GetUpLeftButtonRect(bar, &rect);
    
    laUtils_ClipRectToParent((laWidget*)bar, &rect);
	laUtils_RectToScreenSpace((laWidget*)bar, &rect);
	
	// fill button area
	if(bar->state == LA_SCROLLBAR_STATE_TOP_INSIDE)
	{
	    GFX_Set(GFXF_DRAW_COLOR, bar->widget.scheme->background);
	    
	    arrowOffset = 1;
	}
	else
        GFX_Set(GFXF_DRAW_COLOR, bar->widget.scheme->base);
        
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
	GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
	
	GFX_DrawRect(rect.x,
				 rect.y,
				 rect.width,
				 rect.height);
    
    GFX_Set(GFXF_DRAW_COLOR, bar->widget.scheme->foreground);
				 
	// draw button arrow
	if(bar->alignment == LA_SCROLLBAR_ORIENT_VERTICAL)
	{
	    pnt.x = rect.x + (rect.width / 2) - 1 + arrowOffset;
	    pnt.y = rect.y + (rect.height / 2) - 1 + arrowOffset;
	    
	    GFX_DrawPixel(pnt.x, pnt.y - 1);
	    GFX_DrawLine(pnt.x - 1, pnt.y + 0, pnt.x + 1, pnt.y + 0);
	    GFX_DrawLine(pnt.x - 2, pnt.y + 1, pnt.x + 2, pnt.y + 1);
	    GFX_DrawLine(pnt.x - 3, pnt.y + 2, pnt.x + 3, pnt.y + 2);
	}
	else
	{
	    pnt.x = rect.x + (rect.width / 2) - 1 + arrowOffset;
	    pnt.y = rect.y + (rect.height / 2) - 1 + arrowOffset;
	    
	    GFX_DrawPixel(pnt.x - 1, pnt.y);
	    GFX_DrawLine(pnt.x, pnt.y - 1, pnt.x, pnt.y + 1);
	    GFX_DrawLine(pnt.x + 1, pnt.y - 2, pnt.x + 1, pnt.y + 2);
	    GFX_DrawLine(pnt.x + 2, pnt.y - 3, pnt.x + 2, pnt.y + 3);
	}
    
    // draw button border
    if(bar->widget.borderType == LA_WIDGET_BORDER_LINE)
    {
        laUtils_RectToLayerSpace((laWidget*)bar->widget.parent, &rect);
	    
		laDraw_LineBorder(&rect, bar->widget.scheme->shadowDark);
    }
    else if(bar->widget.borderType == LA_WIDGET_BORDER_BEVEL)
    {
	    if(bar->state == LA_SCROLLBAR_STATE_TOP_INSIDE)
	    {
		    laDraw_2x2BevelBorder(&rect,
						          bar->widget.scheme->shadowDark,
						          bar->widget.scheme->shadow,
						          bar->widget.scheme->highlight,
							      bar->widget.scheme->highlightLight);
	    }
	    else
	    {
		    laDraw_1x2BevelBorder(&rect,
						          bar->widget.scheme->highlightLight,
						          bar->widget.scheme->shadow,
						          bar->widget.scheme->shadowDark);
	    }
    }
	
	bar->widget.drawState = DRAW_DOWN_BUTTON;
	bar->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawDownButton;
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    bar->widget.drawFunc((laWidget*)bar);
}

static void drawDownButton(laScrollBarWidget* bar)
{
    GFX_Rect rect;
    GFX_Point pnt;
    uint32_t arrowOffset = 0;
    
    _laScrollBar_GetDownRightButtonRect(bar, &rect);
    
    laUtils_ClipRectToParent((laWidget*)bar, &rect);
	laUtils_RectToScreenSpace((laWidget*)bar, &rect);
	
	// fill button area
	if(bar->state == LA_SCROLLBAR_STATE_BOTTOM_INSIDE)
	{
	    GFX_Set(GFXF_DRAW_COLOR, bar->widget.scheme->background);
	    
	    arrowOffset = 1;
	}
	else
        GFX_Set(GFXF_DRAW_COLOR, bar->widget.scheme->base);
        
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
	GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
	
	GFX_DrawRect(rect.x,
				 rect.y,
				 rect.width,
				 rect.height);
				 
	GFX_Set(GFXF_DRAW_COLOR, bar->widget.scheme->foreground);
				 
	// draw button arrow
	if(bar->alignment == LA_SCROLLBAR_ORIENT_VERTICAL)
	{
	    pnt.x = rect.x + (rect.width / 2) - 1 + arrowOffset;
	    pnt.y = rect.y + (rect.height / 2) - 1 + arrowOffset;
	    
	    GFX_DrawLine(pnt.x - 3, pnt.y - 1, pnt.x + 3, pnt.y - 1);
	    GFX_DrawLine(pnt.x - 2, pnt.y + 0, pnt.x + 2, pnt.y + 0);
	    GFX_DrawLine(pnt.x - 1, pnt.y + 1, pnt.x + 1, pnt.y + 1);
	    GFX_DrawPixel(pnt.x, pnt.y + 2);
	}
	else
	{
	    pnt.x = rect.x + (rect.width / 2) - 1 + arrowOffset;
	    pnt.y = rect.y + (rect.height / 2) - 1 + arrowOffset;
	    
	    GFX_DrawLine(pnt.x - 1, pnt.y - 3, pnt.x - 1, pnt.y + 3);
	    GFX_DrawLine(pnt.x + 0, pnt.y - 2, pnt.x + 0, pnt.y + 2);
	    GFX_DrawLine(pnt.x + 1, pnt.y - 1, pnt.x + 1, pnt.y + 1);
	    GFX_DrawPixel(pnt.x + 2, pnt.y);
	}
    
    // draw button border
    if(bar->widget.borderType == LA_WIDGET_BORDER_LINE)
    {
        laUtils_RectToLayerSpace((laWidget*)bar->widget.parent, &rect);
	    
		laDraw_LineBorder(&rect, bar->widget.scheme->shadowDark);
    }
    else if(bar->widget.borderType == LA_WIDGET_BORDER_BEVEL)
    {
	    if(bar->state == LA_SCROLLBAR_STATE_BOTTOM_INSIDE)
	    {
		    laDraw_2x2BevelBorder(&rect,
						          bar->widget.scheme->shadowDark,
						          bar->widget.scheme->shadow,
						          bar->widget.scheme->highlight,
							      bar->widget.scheme->highlightLight);
	    }
	    else
	    {
		    laDraw_1x2BevelBorder(&rect,
						          bar->widget.scheme->highlightLight,
						          bar->widget.scheme->shadow,
						          bar->widget.scheme->shadowDark);
	    }
    }
	
	bar->widget.drawState = DRAW_HANDLE;
	bar->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawHandle;
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    bar->widget.drawFunc((laWidget*)bar);
}

static void drawHandle(laScrollBarWidget* bar)
{
    GFX_Rect rect;
    
    _laScrollBar_GetHandleRect(bar, &rect);
    
    laUtils_ClipRectToParent((laWidget*)bar, &rect);
	laUtils_RectToScreenSpace((laWidget*)bar, &rect);
	
	// fill handle area       
    GFX_Set(GFXF_DRAW_COLOR, bar->widget.scheme->base);
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
	GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
	
	GFX_DrawRect(rect.x,
				 rect.y,
				 rect.width,
				 rect.height);
				 
    // draw handle border
    if(bar->widget.borderType == LA_WIDGET_BORDER_LINE)
    {
        laUtils_RectToLayerSpace((laWidget*)bar->widget.parent, &rect);
	    
		laDraw_LineBorder(&rect, bar->widget.scheme->shadowDark);
    }
    else if(bar->widget.borderType == LA_WIDGET_BORDER_BEVEL)
    {
	    laDraw_1x2BevelBorder(&rect,
			          bar->widget.scheme->highlightLight,
			          bar->widget.scheme->shadow,
			          bar->widget.scheme->shadowDark);
    }
	
	bar->widget.drawState = DONE;
	bar->widget.drawFunc = NULL;
}

void _laScrollBarWidget_Paint(laScrollBarWidget* bar)
{
    if(bar->widget.scheme == NULL)
    {
        bar->widget.drawState = DONE;
        
        return;
    }
    
    if(bar->widget.drawState == NOT_STARTED)
        bar->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
	
	bar->widget.drawFunc((laWidget*)bar);
}

#endif // LA_SCROLLBAR_WIDGET_ENABLED