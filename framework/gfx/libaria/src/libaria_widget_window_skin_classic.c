#include "gfx/libaria/inc/libaria_widget_window.h"

#if LA_WINDOW_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define DEFAULT_BAR_HEIGHT 20

enum
{
    NOT_STARTED = LA_WIDGET_DRAW_STATE_READY,
    DONE = LA_WIDGET_DRAW_STATE_DONE,
    DRAW_TITLE_BAR,
    DRAW_ICON,
    WAIT_ICON,
    DRAW_STRING,
    WAIT_STRING,
    DRAW_BORDER,
};

static void drawBackground(laWindowWidget* win);
static void drawTitleBar(laWindowWidget* win);
static void drawIcon(laWindowWidget* win);
static void waitIcon(laWindowWidget* win);
static void drawString(laWindowWidget* win);
static void waitString(laWindowWidget* win);
static void drawBorder(laWindowWidget* win);

static void drawBackground(laWindowWidget* win)
{
    GFX_Rect rect;
	
	//printf("button painting\n");
	
	if(win->widget.drawBackground == LA_TRUE)
	{
	    rect = win->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)win->widget.parent, &rect);
	    
	    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_Set(GFXF_DRAW_COLOR, win->widget.scheme->base);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		
		GFX_DrawRect(win->widget.rect.x,
					 win->widget.rect.y,
					 win->widget.rect.width,
					 win->widget.rect.height);
	}
	
	win->widget.drawState = DRAW_TITLE_BAR;
    win->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawTitleBar;
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    win->widget.drawFunc(win);
}

static void drawTitleBar(laWindowWidget* win)
{
    GFX_Rect barRect;
    
    win->paintData.barRect.x = win->widget.margin.left;
    win->paintData.barRect.y = win->widget.margin.top;
    win->paintData.barRect.width = win->widget.rect.width -
                                   win->widget.margin.left -
                                   win->widget.margin.right;
    win->paintData.barRect.height = laString_GetHeight(&win->title) +
                                    win->widget.margin.top +
                                    win->widget.margin.bottom;
    
    if(win->paintData.barRect.height == 0)
        win->paintData.barRect.height = DEFAULT_BAR_HEIGHT;
    
    barRect = win->paintData.barRect;
    
    laUtils_RectToLayerSpace((laWidget*)win, &barRect);
        
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
	GFX_Set(GFXF_DRAW_COLOR, win->widget.scheme->background);
	GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
	
	GFX_DrawRect(barRect.x, barRect.y, barRect.width, barRect.height);
	
	// draw title bar border
	/*if(win->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
		laDraw_LineBorder(&barRect, win->widget.scheme->shadowDark);
	}
	else if(win->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
		laDraw_2x2BevelBorder(&barRect,
						      win->widget.scheme->base,
						      win->widget.scheme->highlightLight,
						      win->widget.scheme->shadow,
							  win->widget.scheme->shadowDark);
	}*/
    
    if(win->icon != NULL)
    {
        win->widget.drawState = DRAW_ICON;
	    win->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawIcon;
    }
    else if(win->title.length > 0 || win->title.table_index != LA_STRING_NULLIDX)
	{
	    win->widget.drawState = DRAW_STRING;
	    win->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
	}
	else if(win->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    win->widget.drawState = DRAW_BORDER;
	    win->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        win->widget.drawState = DONE;
        win->widget.drawFunc = NULL;
        
        return;
    }
    
    if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    win->widget.drawFunc(win);
}

static void drawIcon(laWindowWidget* win)
{
    GFX_Rect widgetRect, barRect, imageRect;
    GFX_Rect clipRect;
    
    widgetRect = win->widget.rect;
    barRect = win->paintData.barRect;
       
    imageRect.x = 0;
    imageRect.y = 0;
    imageRect.width = win->icon->width;
    imageRect.height = win->icon->height;
    
    widgetRect.x = 0;
    widgetRect.y = 0;
        
    laUtils_RectToLayerSpace((laWidget*)win, &widgetRect);
    laUtils_RectToLayerSpace((laWidget*)win, &barRect);
    
    laUtils_ArrangeRectangleRelative(&imageRect,
                                     GFX_Rect_Zero,
                                     barRect,
                                     LA_HALIGN_LEFT,
                                     LA_VALIGN_MIDDLE,
                                     LA_RELATIVE_POSITION_LEFTOF,
                                     win->widget.margin.left,
                                     win->widget.margin.top,
                                     win->widget.margin.right,
                                     win->widget.margin.bottom,
                                     win->iconMargin);
                                     
    clipRect = barRect;
    clipRect.y += 1;
    clipRect.height -= 2;
    
    GFX_RectClip(&widgetRect, &clipRect, &barRect);
    
    GFX_Set(GFXF_DRAW_CLIP_RECT, &barRect);
    
    GFXU_DrawImage(win->icon,
                   0,
                   0,
                   win->icon->width,
                   win->icon->height,
                   imageRect.x,
                   imageRect.y,
                   &laContext_GetActive()->memIntf,
                   &win->reader);
        
    if(win->reader != NULL)
    {
        win->widget.drawState = WAIT_ICON;
	    win->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&waitIcon;
    }
    else if(win->title.length > 0 || win->title.table_index != LA_STRING_NULLIDX)
	{
	    win->widget.drawState = DRAW_STRING;
	    win->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
	}
	else if(win->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    win->widget.drawState = DRAW_BORDER;
	    win->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        win->widget.drawState = DONE;
        win->widget.drawFunc = NULL;
        
        return;
    }
    
    if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    win->widget.drawFunc(win);
}

static void waitIcon(laWindowWidget* win)
{
    if(win->reader->status != GFXU_READER_STATUS_FINISHED)
    {
        win->reader->run(win->reader);
        
        return;
    }
    
    // free the reader
    win->reader->memIntf->heap.free(win->reader);
    win->reader = NULL;
    
    if(win->title.length > 0 || win->title.table_index != LA_STRING_NULLIDX)
	{
	    win->widget.drawState = DRAW_STRING;
	    win->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
	}
	else if(win->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    win->widget.drawState = DRAW_BORDER;
	    win->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        win->widget.drawState = DONE;
        win->widget.drawFunc = NULL;
        
        return;
    }
    
    if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    win->widget.drawFunc(win);
}

static void drawString(laWindowWidget* win)
{
    GFX_Rect widgetRect, imageRect, textRect, barRect, clipRect;
    
    widgetRect = win->widget.rect;
    
    widgetRect.x = 0;
    widgetRect.y = 0;
        
    laUtils_RectToLayerSpace((laWidget*)win, &widgetRect);
    
    laString_GetRect(&win->title, &textRect);
    
    imageRect = GFX_Rect_Zero;
    
    if(win->icon != NULL)
    {
        imageRect.width = win->icon->width;
        imageRect.height = win->icon->height;
    }
    
    textRect.x = win->widget.margin.left +
                 imageRect.width +
                 win->iconMargin;
                 
    textRect.y = win->widget.margin.top;
    
    barRect = win->paintData.barRect;
    
    //GFX_RectClip(&textRect, &barRect, &textClipRect);
    
    // arrange relative to image rect
    laUtils_ArrangeRectangleRelative(&textRect,
                                     imageRect,
                                     barRect,
                                     LA_HALIGN_LEFT,
                                     LA_VALIGN_MIDDLE,
                                     LA_RELATIVE_POSITION_LEFTOF,
                                     win->widget.margin.left,
                                     win->widget.margin.top,
                                     win->widget.margin.right,
                                     win->widget.margin.bottom,
                                     win->iconMargin);
                                     
    
    
    
    
    // move the rect to parent space
    laUtils_RectToScreenSpace((laWidget*)win, &textRect);
    laUtils_RectToScreenSpace((laWidget*)win, &barRect);
    
    GFX_RectClip(&widgetRect, &barRect, &clipRect);
    
    GFX_Set(GFXF_DRAW_CLIP_RECT, &clipRect);
    
    //GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_LINE);
    //GFX_Set(GFXF_DRAW_COLOR, GFX_ColorValue(GFX_COLOR_MODE_RGB_565, GFX_COLOR_RED));
    //GFX_DrawRect(textRect.x, textRect.y, textRect.width, textRect.height);
        
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    GFX_Set(GFXF_DRAW_COLOR, win->widget.scheme->text);
    
    laString_Draw(&win->title, textRect.x, textRect.y, &win->reader);
    
    if(win->reader != NULL)
    {
        win->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&waitString;
	    win->widget.drawState = WAIT_STRING;
    }
    else if(win->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    win->widget.drawState = DRAW_BORDER;
	    win->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        win->widget.drawState = DONE;
        win->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    win->widget.drawFunc(win);
}

static void waitString(laWindowWidget* win)
{
    if(win->reader->status != GFXU_READER_STATUS_FINISHED)
    {
        win->reader->run(win->reader);
        
        return;
    }
    
    // free the reader
    win->reader->memIntf->heap.free(win->reader);
    win->reader = NULL;
    
    if(win->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    win->widget.drawState = DRAW_BORDER;
	    win->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        win->widget.drawState = DONE;
        win->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    win->widget.drawFunc(win);
}

static void drawBorder(laWindowWidget* win)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(win->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = win->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)win->widget.parent, &rect);
	    
	    GFX_Set(GFXF_DRAW_CLIP_RECT, &rect);
	    
		laDraw_LineBorder(&rect, win->widget.scheme->shadowDark);
	}
	else if(win->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = win->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)win, &rect);
	    
	    GFX_Set(GFXF_DRAW_CLIP_RECT, &rect);
	    
		laDraw_2x2BevelBorder(&win->widget.rect,
						      win->widget.scheme->base,
						      win->widget.scheme->highlightLight,
						      win->widget.scheme->shadow,
							  win->widget.scheme->shadowDark);
	}
	
	win->widget.drawState = DONE;
	win->widget.drawFunc = NULL;
}

void _laWindowWidget_Paint(laWindowWidget* win)
{
    if(win->widget.scheme == NULL)
    {
        win->widget.drawState = DONE;
        
        return;
    }

    if(win->widget.drawState == NOT_STARTED)
        win->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;

	win->widget.drawFunc((laWidget*)win);
}

#endif // LA_WINDOW_WIDGET_ENABLED