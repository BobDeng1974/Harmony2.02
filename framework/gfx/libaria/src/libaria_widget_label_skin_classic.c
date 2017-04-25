#include "gfx/libaria/inc/libaria_widget_label.h"

#if LA_LABEL_WIDGET_ENABLED

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
    DRAW_BORDER,
};

static void drawBackground(laLabelWidget* lbl);
static void drawString(laLabelWidget* lbl);
static void waitString(laLabelWidget* lbl);
static void drawBorder(laLabelWidget* lbl);

static void drawBackground(laLabelWidget* lbl)
{
    GFX_Rect rect;
	
	//printf("button painting\n");
	
	if(lbl->widget.drawBackground == LA_TRUE)
	{
	    rect = lbl->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)lbl->widget.parent, &rect);
	    
	    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_Set(GFXF_DRAW_COLOR, lbl->widget.scheme->base);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(lbl->widget.rect.x,
					 lbl->widget.rect.y,
					 lbl->widget.rect.width,
					 lbl->widget.rect.height);
	}
	
	if(lbl->text.length > 0 || lbl->text.table_index != LA_STRING_NULLIDX)
	{
	    lbl->widget.drawState = DRAW_STRING;
	    lbl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
	}
	else if(lbl->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    lbl->widget.drawState = DRAW_BORDER;
	    lbl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        lbl->widget.drawState = DONE;
        lbl->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    lbl->widget.drawFunc(lbl);
}

static void drawString(laLabelWidget* lbl)
{
    GFX_Rect textRect;
    GFX_Rect bounds = lbl->widget.rect;
    
    bounds.x = 0;
    bounds.y = 0;
    
    laString_GetRect(&lbl->text, &textRect);
    
    // arrange relative to image rect
    laUtils_ArrangeRectangleRelative(&textRect,
                                     GFX_Rect_Zero,
                                     bounds,
                                     lbl->halign,
                                     lbl->valign,
                                     0,
                                     lbl->widget.margin.left,
                                     lbl->widget.margin.top,
                                     lbl->widget.margin.right,
                                     lbl->widget.margin.bottom,
                                     0);
    
    // move the rect to parent space
    //rect.x += lbl->widget.rect.x;
    //rect.y += lbl->widget.rect.y;
    
    laUtils_RectToScreenSpace((laWidget*)lbl, &textRect);
    
    /*GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_LINE);
    GFX_Set(GFXF_DRAW_COLOR, GFX_ColorValue(GFX_COLOR_MODE_RGB_888, GFX_COLOR_RED));
    GFX_DrawRect(rect.x, rect.y, rect.width, rect.height);*/
        
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    GFX_Set(GFXF_DRAW_COLOR, lbl->widget.scheme->text);
    laString_Draw(&lbl->text, textRect.x, textRect.y, &lbl->reader);
    
    if(lbl->reader != NULL)
    {
        lbl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&waitString;
	    lbl->widget.drawState = WAIT_STRING;
    }
    else if(lbl->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    lbl->widget.drawState = DRAW_BORDER;
	    lbl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        lbl->widget.drawState = DONE;
        lbl->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    lbl->widget.drawFunc(lbl);
}

static void waitString(laLabelWidget* lbl)
{
    if(lbl->reader->status != GFXU_READER_STATUS_FINISHED)
    {
        lbl->reader->run(lbl->reader);
        
        return;
    }
    
    // free the reader
    lbl->reader->memIntf->heap.free(lbl->reader);
    lbl->reader = NULL;
    
    if(lbl->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    lbl->widget.drawState = DRAW_BORDER;
	    lbl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        lbl->widget.drawState = DONE;
        lbl->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    lbl->widget.drawFunc(lbl);
}

static void drawBorder(laLabelWidget* lbl)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(lbl->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = lbl->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)lbl, &rect);
	    
		laDraw_LineBorder(&rect, lbl->widget.scheme->shadowDark);
	}
	else if(lbl->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = lbl->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)lbl, &rect);
	    
		laDraw_2x2BevelBorder(&lbl->widget.rect,
						      lbl->widget.scheme->highlightLight,
						      lbl->widget.scheme->highlightLight,
						      lbl->widget.scheme->shadow,
							  lbl->widget.scheme->shadowDark);
	}
	
	lbl->widget.drawState = DONE;
	lbl->widget.drawFunc = NULL;
}

void _laLabelWidget_Paint(laLabelWidget* lbl)
{
    if(lbl->widget.scheme == NULL)
    {
        lbl->widget.drawState = DONE;
        
        return;
    }

    if(lbl->widget.drawState == NOT_STARTED)
        lbl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;

	lbl->widget.drawFunc((laWidget*)lbl);
}

#endif // LA_IMAGE_WIDGET_ENABLED