#include "gfx/libaria/inc/libaria_widget_groupbox.h"

#if LA_GROUPBOX_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define OUTLINE_SPACE 2

enum
{
    NOT_STARTED = LA_WIDGET_DRAW_STATE_READY,
    DONE = LA_WIDGET_DRAW_STATE_DONE,
    DRAW_OUTLINE,
    DRAW_STRING,
    WAIT_STRING,
    DRAW_BORDER,
};

static void drawBackground(laGroupBoxWidget* box);
static void drawOutline(laGroupBoxWidget* box);
static void drawString(laGroupBoxWidget* box);
static void waitString(laGroupBoxWidget* box);
static void drawBorder(laGroupBoxWidget* box);

static void drawBackground(laGroupBoxWidget* box)
{
    GFX_Rect rect;
	
	if(box->widget.drawBackground == LA_TRUE)
	{
	    rect = box->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)box->widget.parent, &rect);
	    
		GFX_Set(GFXF_DRAW_COLOR, box->widget.scheme->base);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		
		GFX_DrawRect(box->widget.rect.x,
					 box->widget.rect.y,
					 box->widget.rect.width,
					 box->widget.rect.height);
	}
	
    box->widget.drawState = DRAW_OUTLINE;
    box->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawOutline;
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    box->widget.drawFunc(box);
}

static void drawOutline(laGroupBoxWidget* box)
{
    GFX_Rect widgetRect, textRect; 
    int32_t top, bottom, left, right;
    
    widgetRect = box->widget.rect;
    widgetRect.x = 0;
    widgetRect.y = 0;
    
    laUtils_RectToScreenSpace((laWidget*)box, &widgetRect);
    
    laString_GetRect(&box->text, &textRect);
    
    // draw vertical lines
    top = widgetRect.y + textRect.height / 2;   
    bottom = widgetRect.y + widgetRect.height - OUTLINE_SPACE;

	GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_LINE);
	GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
	
	GFX_Set(GFXF_DRAW_COLOR, box->widget.scheme->shadow);
	
	// left outer line
	GFX_DrawLine(widgetRect.x + OUTLINE_SPACE,
	             top,
	             widgetRect.x + OUTLINE_SPACE,
	             bottom);
	
	// right inner line
	GFX_DrawLine(widgetRect.x + box->widget.rect.width - OUTLINE_SPACE - 2,
	             top,
	             widgetRect.x + box->widget.rect.width - OUTLINE_SPACE - 2,
	             bottom - 1);
	             
	GFX_Set(GFXF_DRAW_COLOR, box->widget.scheme->highlightLight);
	
	// left inner line
	GFX_DrawLine(widgetRect.x + OUTLINE_SPACE + 1,
	             top + 1,
	             widgetRect.x + OUTLINE_SPACE + 1,
	             bottom - 1);
	
	// right outer line
	GFX_DrawLine(widgetRect.x + box->widget.rect.width - OUTLINE_SPACE - 1,
	             top,
	             widgetRect.x + box->widget.rect.width - OUTLINE_SPACE - 1,
	             bottom);
	
	if(box->halign == LA_HALIGN_LEFT)
    {   
	    left = OUTLINE_SPACE * 3;
	    right = left + textRect.width + 1;
	    
	    if(right > box->widget.rect.width - OUTLINE_SPACE * 3)
	        right = box->widget.rect.width - OUTLINE_SPACE * 3;
	}
	else if(box->halign == LA_HALIGN_CENTER)
	{
	    left = box->widget.rect.width / 2 - textRect.width / 2 - 2;
	    right = left + textRect.width + 3;
	}
	else
	{
	    right = box->widget.rect.width - OUTLINE_SPACE * 3;
	    left = right - textRect.width - 1;
	    
	    if(left < OUTLINE_SPACE * 3)
	        left = OUTLINE_SPACE * 3;
	}
	         
    // draw horizontal lines
    GFX_Set(GFXF_DRAW_COLOR, box->widget.scheme->shadow);
    
    left += widgetRect.x;
    right += widgetRect.x;
    
    // top outer line left segment
    GFX_DrawLine(widgetRect.x + OUTLINE_SPACE + 1,
                 top,
                 left,
                 top);
                 
    // top outer line right segment
    GFX_DrawLine(right,
                 top,
                 widgetRect.x + widgetRect.width - OUTLINE_SPACE * 2,
                 top);
                 
    // bottom inner line
    GFX_DrawLine(widgetRect.x + OUTLINE_SPACE + 1,
                 bottom - 1,
                 widgetRect.x + widgetRect.width - (OUTLINE_SPACE * 2),
                 bottom - 1);
                 
    GFX_Set(GFXF_DRAW_COLOR, box->widget.scheme->highlightLight);
    
    // top inner line left segment
    GFX_DrawLine(widgetRect.x + OUTLINE_SPACE * 2,
                 top + 1,
                 left,
                 top + 1);
                 
    // top inner line right segment
    GFX_DrawLine(right,
                 top + 1,
                 widgetRect.x + widgetRect.width - (OUTLINE_SPACE * 2) - 1,
                 top + 1);
                 
    // bottom outer line
    GFX_DrawLine(widgetRect.x + OUTLINE_SPACE,
                 bottom,
                 widgetRect.x + widgetRect.width - (OUTLINE_SPACE * 2),
                 bottom);
           
    if(box->text.length > 0 || box->text.table_index != LA_STRING_NULLIDX)
	{
	    box->widget.drawState = DRAW_STRING;
	    box->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
	}
    else if(box->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    box->widget.drawState = DRAW_BORDER;
	    box->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        box->widget.drawState = DONE;
        box->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    box->widget.drawFunc(box);
}

static void drawString(laGroupBoxWidget* box)
{
    GFX_Rect textRect;//, boundRect; 
    GFX_Rect bounds = box->widget.rect;
    
    bounds.x = 0;
    bounds.y = 0;
    
    laString_GetRect(&box->text, &textRect);
    
    //boundRect = box->widget.rect;
    //boundRect.x += OUTLINE_SPACE * 2;
    //boundRect.width -= OUTLINE_SPACE * 4;
    
    // arrange relative to image rect
    laUtils_ArrangeRectangleRelative(&textRect,
                                     GFX_Rect_Zero,
                                     bounds,
                                     box->halign,
                                     LA_VALIGN_TOP,
                                     0,
                                     OUTLINE_SPACE * 3,
                                     OUTLINE_SPACE,
                                     (OUTLINE_SPACE * 3) + 1,
                                     OUTLINE_SPACE,
                                     0);
    
    // move the rect to parent space
    //rect.x += box->widget.rect.x;
    //rect.y += box->widget.rect.y;
    
    laUtils_RectToScreenSpace((laWidget*)box, &textRect);
    
    /*GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_LINE);
    GFX_Set(GFXF_DRAW_COLOR, GFX_ColorValue(GFX_COLOR_MODE_RGB_888, GFX_COLOR_RED));
    GFX_DrawRect(rect.x, rect.y, rect.width, rect.height);*/
        
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    GFX_Set(GFXF_DRAW_COLOR, box->widget.scheme->text);
    
    // really need a clipped string function for large text
    laString_Draw(&box->text, textRect.x, textRect.y, &box->reader);
    
    if(box->reader != NULL)
    {
        box->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&waitString;
	    box->widget.drawState = WAIT_STRING;
    }
    else if(box->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    box->widget.drawState = DRAW_BORDER;
	    box->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        box->widget.drawState = DONE;
        box->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    box->widget.drawFunc(box);
}

static void waitString(laGroupBoxWidget* box)
{
    if(box->reader->status != GFXU_READER_STATUS_FINISHED)
    {
        box->reader->run(box->reader);
        
        return;
    }
    
    // free the reader
    box->reader->memIntf->heap.free(box->reader);
    box->reader = NULL;
    
    if(box->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    box->widget.drawState = DRAW_BORDER;
	    box->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        box->widget.drawState = DONE;
        box->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    box->widget.drawFunc(box);
}

static void drawBorder(laGroupBoxWidget* box)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(box->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = box->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)box->widget.parent, &rect);
	    
		laDraw_LineBorder(&rect, box->widget.scheme->shadowDark);
	}
	else if(box->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = box->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)box, &rect);
	    
		laDraw_2x2BevelBorder(&box->widget.rect,
						      box->widget.scheme->highlightLight,
						      box->widget.scheme->highlightLight,
						      box->widget.scheme->shadow,
							  box->widget.scheme->shadowDark);
	}
	
	box->widget.drawState = DONE;
	box->widget.drawFunc = NULL;
}

void _laGroupBoxWidget_Paint(laGroupBoxWidget* box)
{
    if(box->widget.scheme == NULL)
    {
        box->widget.drawState = DONE;
        
        return;
    }

    if(box->widget.drawState == NOT_STARTED)
        box->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;

	box->widget.drawFunc((laWidget*)box);
}

#endif // LA_GROUPBOX_WIDGET_ENABLED