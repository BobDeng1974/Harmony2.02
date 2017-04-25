#include "gfx/libaria/inc/libaria_widget_textfield.h"

#if LA_TEXTFIELD_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

enum
{
    NOT_STARTED = LA_WIDGET_DRAW_STATE_READY,
    DONE = LA_WIDGET_DRAW_STATE_DONE,
    DRAW_STRING,
    WAIT_STRING,
    DRAW_CURSOR,
    DRAW_BORDER,
};

static void drawBackground(laTextFieldWidget* txt);
static void drawString(laTextFieldWidget* txt);
static void waitString(laTextFieldWidget* txt);
static void drawCursor(laTextFieldWidget* txt);
static void drawBorder(laTextFieldWidget* txt);

static void drawBackground(laTextFieldWidget* txt)
{
    GFX_Rect rect;
	
	//printf("button painting\n");
	
	if(txt->editWidget.widget.drawBackground == LA_TRUE)
	{
	    rect = txt->editWidget.widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)txt->editWidget.widget.parent, &rect);
	    
	    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_Set(GFXF_DRAW_COLOR, txt->editWidget.widget.scheme->background);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(txt->editWidget.widget.rect.x,
					 txt->editWidget.widget.rect.y,
					 txt->editWidget.widget.rect.width,
					 txt->editWidget.widget.rect.height);
	}
	
	if(txt->text.length > 0 || txt->text.table_index != LA_STRING_NULLIDX)
	{
	    txt->editWidget.widget.drawState = DRAW_STRING;
	    txt->editWidget.widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
	}
	else if(txt->cursorEnable == LA_TRUE && txt->cursorVisible == LA_TRUE)
	{
	    txt->editWidget.widget.drawState = DRAW_CURSOR;
	    txt->editWidget.widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawCursor;   
	}
	else if(txt->editWidget.widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    txt->editWidget.widget.drawState = DRAW_BORDER;
	    txt->editWidget.widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        txt->editWidget.widget.drawState = DONE;
        txt->editWidget.widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    txt->editWidget.widget.drawFunc(txt);
}

static void drawString(laTextFieldWidget* txt)
{
    GFX_Rect textRect;
    GFX_Rect bounds = txt->editWidget.widget.rect;
    
    bounds.x = 0;
    bounds.y = 0;
    
    laString_GetRect(&txt->text, &textRect);
    
    laUtils_ArrangeRectangleRelative(&textRect,
                                     GFX_Rect_Zero,
                                     bounds,
                                     txt->halign,
                                     LA_VALIGN_MIDDLE,
                                     0,
                                     txt->editWidget.widget.margin.left,
                                     txt->editWidget.widget.margin.top,
                                     txt->editWidget.widget.margin.right,
                                     txt->editWidget.widget.margin.bottom,
                                     0);
    
    // move the rect to parent space
    //rect.x += txt->widget.rect.x;
    //rect.y += txt->widget.rect.y;
    
    laUtils_RectToScreenSpace((laWidget*)txt, &textRect);
    
    /*GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_LINE);
    GFX_Set(GFXF_DRAW_COLOR, GFX_ColorValue(GFX_COLOR_MODE_RGB_888, GFX_COLOR_RED));
    GFX_DrawRect(rect.x, rect.y, rect.width, rect.height);*/
        
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    GFX_Set(GFXF_DRAW_COLOR, txt->editWidget.widget.scheme->text);
    laString_Draw(&txt->text, textRect.x, textRect.y, &txt->reader);
    
    if(txt->reader != NULL)
    {
        txt->editWidget.widget.drawFunc = (laWidget_DrawFunction_FnPtr)&waitString;
	    txt->editWidget.widget.drawState = WAIT_STRING;
    }
    else if(txt->cursorEnable == LA_TRUE && txt->cursorVisible == LA_TRUE)
	{
	    txt->editWidget.widget.drawState = DRAW_CURSOR;
	    txt->editWidget.widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawCursor;   
	}
	else if(txt->editWidget.widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    txt->editWidget.widget.drawState = DRAW_BORDER;
	    txt->editWidget.widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        txt->editWidget.widget.drawState = DONE;
        txt->editWidget.widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    txt->editWidget.widget.drawFunc(txt);
}

static void waitString(laTextFieldWidget* txt)
{
    if(txt->reader->status != GFXU_READER_STATUS_FINISHED)
    {
        txt->reader->run(txt->reader);
        
        return;
    }
    
    // free the reader
    txt->reader->memIntf->heap.free(txt->reader);
    txt->reader = NULL;
    
    if(txt->cursorEnable == LA_TRUE && txt->cursorVisible == LA_TRUE)
	{
	    txt->editWidget.widget.drawState = DRAW_CURSOR;
	    txt->editWidget.widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawCursor;   
	}
	else if(txt->editWidget.widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    txt->editWidget.widget.drawState = DRAW_BORDER;
	    txt->editWidget.widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        txt->editWidget.widget.drawState = DONE;
        txt->editWidget.widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    txt->editWidget.widget.drawFunc(txt);
}

static void drawCursor(laTextFieldWidget* txt)
{
    uint32_t cursorX;
    GFX_Rect textRect;
    GFX_Rect bounds = txt->editWidget.widget.rect;
    
    bounds.x = 0;
    bounds.y = 0;
    
    laString_GetRect(&txt->text, &textRect);
    
    laUtils_ArrangeRectangleRelative(&textRect,
                                     GFX_Rect_Zero,
                                     bounds,
                                     txt->halign,
                                     LA_VALIGN_MIDDLE,
                                     0,
                                     txt->editWidget.widget.margin.left,
                                     txt->editWidget.widget.margin.top,
                                     txt->editWidget.widget.margin.right,
                                     txt->editWidget.widget.margin.bottom,
                                     0);
    
    if(textRect.height == 0)
    {
        textRect.y = bounds.y + txt->editWidget.widget.margin.top + 2;
        textRect.height = bounds.height - txt->editWidget.widget.margin.top - txt->editWidget.widget.margin.bottom - 4;
    }
    
    laUtils_RectToScreenSpace((laWidget*)txt, &textRect);
    
    // draw cursor line
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    GFX_Set(GFXF_DRAW_COLOR, txt->editWidget.widget.scheme->foreground);
    
    cursorX = laString_GetCharOffset(&txt->text, txt->cursorPos);
    
    GFX_DrawLine(textRect.x + cursorX,
                 textRect.y,
                 textRect.x + cursorX,
                 textRect.y + textRect.height);
    
    if(txt->editWidget.widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    txt->editWidget.widget.drawState = DRAW_BORDER;
	    txt->editWidget.widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
	{
	    txt->editWidget.widget.drawState = DONE;
	    txt->editWidget.widget.drawFunc = NULL;
	}
}

static void drawBorder(laTextFieldWidget* txt)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(txt->editWidget.widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = txt->editWidget.widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)txt, &rect);
	    
		laDraw_LineBorder(&rect, txt->editWidget.widget.scheme->shadowDark);
	}
	else if(txt->editWidget.widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = txt->editWidget.widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)txt, &rect);
	    
		laDraw_2x2BevelBorder(&rect,
						      txt->editWidget.widget.scheme->shadow,
						      txt->editWidget.widget.scheme->shadowDark,
						      txt->editWidget.widget.scheme->highlight,
						      txt->editWidget.widget.scheme->highlightLight);
	}
	
	txt->editWidget.widget.drawState = DONE;
	txt->editWidget.widget.drawFunc = NULL;
}

void _laTextFieldWidget_Paint(laTextFieldWidget* txt)
{
    if(txt->editWidget.widget.scheme == NULL)
    {
        txt->editWidget.widget.drawState = DONE;
        
        return;
    }

    if(txt->editWidget.widget.drawState == NOT_STARTED)
        txt->editWidget.widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;

	txt->editWidget.widget.drawFunc((laWidget*)txt);
}

#endif // LA_TEXTFIELD_WIDGET_ENABLED