#include "gfx/libaria/inc/libaria_widget_checkbox.h"

#if LA_CHECKBOX_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_scheme.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define CHECKBOX_SIZE       13
#define CHECKBOX_SIZE_HALF  6

enum
{
    NOT_STARTED = LA_WIDGET_DRAW_STATE_READY,
    DONE = LA_WIDGET_DRAW_STATE_DONE,
    DRAW_IMAGE,
    WAIT_IMAGE,
    DRAW_STRING,
    WAIT_STRING,
    DRAW_BORDER
};

static void drawBackground(laCheckBoxWidget* cbox);
static void drawImage(laCheckBoxWidget* cbox);
static void waitImage(laCheckBoxWidget* cbox);
static void drawString(laCheckBoxWidget* cbox);
static void waitString(laCheckBoxWidget* cbox);
static void drawBorder(laCheckBoxWidget* cbox);

void _laCheckBoxWidget_GetImageRect(laCheckBoxWidget* cbox, GFX_Rect* rect)
{
    GFX_Rect textRect;
    GFX_Rect bounds = cbox->widget.rect;
    bounds.x = 0;
    bounds.y = 0;
    
    rect->x = 0;
    rect->y = 0;
    
    laString_GetRect(&cbox->text, &textRect);
    
    if(cbox->checked == LA_FALSE)
    {
        if(cbox->uncheckedImage == NULL)
        {
            rect->width = CHECKBOX_SIZE;
            rect->height = CHECKBOX_SIZE;
        }
        else
        {
            rect->width = cbox->uncheckedImage->width;
            rect->height = cbox->uncheckedImage->height;
        }
    }
    else
    {
        if(cbox->checkedImage == NULL)
        {
            rect->width = CHECKBOX_SIZE;
            rect->height = CHECKBOX_SIZE;
        }
        else
        {
            rect->width = cbox->checkedImage->width;
            rect->height = cbox->checkedImage->height;
        }
    }
    
    laUtils_ArrangeRectangle(rect,
                             textRect,
                             bounds,
                             cbox->halign,
                             cbox->valign,
                             cbox->imagePosition,
                             cbox->widget.margin.left,
                             cbox->widget.margin.top,
                             cbox->widget.margin.right,
                             cbox->widget.margin.bottom,
                             cbox->imageMargin);
}

static void drawCheckBox(laCheckBoxWidget* cbox, GFX_Rect* rect)
{
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    // draw box fill
    GFX_Set(GFXF_DRAW_COLOR, cbox->widget.scheme->background);
    GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
	GFX_DrawRect(rect->x,
				 rect->y,
				 CHECKBOX_SIZE,
				 CHECKBOX_SIZE);
    
    // draw box border
    laDraw_2x2BevelBorder(rect,
						  cbox->widget.scheme->shadow,
						  cbox->widget.scheme->shadowDark,
						  cbox->widget.scheme->highlight,
						  cbox->widget.scheme->highlightLight);
        
    if(cbox->checked == LA_TRUE)
    {
        GFX_Set(GFXF_DRAW_COLOR, cbox->widget.scheme->foreground);
        GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_LINE);
        GFX_Set(GFXF_DRAW_THICKNESS, 3);
        
        GFX_DrawLine(rect->x + 3, rect->y + 5,
				     rect->x + 5, rect->y + 7);
        GFX_DrawLine(rect->x + 5, rect->y + 7,
				     rect->x + 9, rect->y + 3);
        
        GFX_DrawLine(rect->x + 3, rect->y + 6,
				     rect->x + 5, rect->y + 8);
        GFX_DrawLine(rect->x + 5, rect->y + 8,
				     rect->x + 9, rect->y + 4);
				     
	    GFX_DrawLine(rect->x + 3, rect->y + 7,
				     rect->x + 5, rect->y + 9);
        GFX_DrawLine(rect->x + 5, rect->y + 9,
				     rect->x + 9, rect->y + 5);
    }
}

static void drawBackground(laCheckBoxWidget* cbox)
{
    GFX_Rect rect;

	if(cbox->widget.drawBackground == LA_TRUE)
	{
        rect = cbox->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)cbox->widget.parent, &rect);

        GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
        GFX_Set(GFXF_DRAW_COLOR, cbox->widget.scheme->base);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_DrawRect(rect.x,
					 rect.y,
					 rect.width,
					 rect.height);
	}
	
	cbox->widget.drawState = DRAW_IMAGE;
	cbox->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawImage;
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    cbox->widget.drawFunc(cbox);
}

static void drawImage(laCheckBoxWidget* cbox)
{
    GFX_Rect rect, textRect, bounds;
    GFXU_ImageAsset* img = NULL;
    
    bounds = cbox->widget.rect;
    bounds.x = 0;
    bounds.y = 0;
    
    laString_GetRect(&cbox->text, &textRect);
    
    // calculate image dimensions
    if(cbox->checked == LA_TRUE)
    {
        if(cbox->checkedImage != NULL)
        {
            img = cbox->checkedImage;
            
            rect.width = cbox->checkedImage->width;
            rect.height = cbox->checkedImage->height;
        }
        else
        {
            rect.width = CHECKBOX_SIZE;
            rect.height = CHECKBOX_SIZE;
        }
    }
    else
    {
        if(cbox->uncheckedImage != NULL)
        {
            img = cbox->uncheckedImage;
            
            rect.width = cbox->uncheckedImage->width;
            rect.height = cbox->uncheckedImage->height;
        }
        else
        {
            rect.width = CHECKBOX_SIZE;
            rect.height = CHECKBOX_SIZE;
        }
    }
    
    // arrange image rect
    laUtils_ArrangeRectangle(&rect,
                             textRect,
                             bounds,
                             cbox->halign,
                             cbox->valign,
                             cbox->imagePosition,
                             cbox->widget.margin.left,
                             cbox->widget.margin.top,
                             cbox->widget.margin.right,
                             cbox->widget.margin.bottom,
                             cbox->imageMargin);
    
    // move the rect to parent space
    //rect.x += cbox->widget.rect.x;
    //rect.y += cbox->widget.rect.y;
    
    laUtils_RectToScreenSpace((laWidget*)cbox, &rect);
    
    //GFX_Set(GFXF_DRAW_COLOR, cbox->widget.scheme->text);
    
    if(img == NULL)
    {
        drawCheckBox(cbox, &rect);
    }
    else
    {
        GFXU_DrawImage(img,
                       0,
                       0,
                       img->width,
                       img->height,
                       rect.x,
                       rect.y,
                       &laContext_GetActive()->memIntf,
                       &cbox->reader);
    }
                
    if(cbox->reader == NULL)
    {  
        if(cbox->text.length > 0 || cbox->text.table_index != LA_STRING_NULLIDX)
	    {
	        cbox->widget.drawState = DRAW_STRING;
	        cbox->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
	    }
	    else if(cbox->widget.borderType != LA_WIDGET_BORDER_NONE)
	    {
	        cbox->widget.drawState = DRAW_BORDER;
	        cbox->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	    }
	    else
	    {
	        cbox->widget.drawState = DONE;
	        cbox->widget.drawFunc = NULL;
	        
	        return;
	    }
	}
	else
	{
	    cbox->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&waitImage;
	    cbox->widget.drawState = WAIT_IMAGE;
	}
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    cbox->widget.drawFunc(cbox);
}

static void waitImage(laCheckBoxWidget* cbox)
{
    if(cbox->reader->status != GFXU_READER_STATUS_FINISHED)
    {
        cbox->reader->run(cbox->reader);
        
        return;
    }
    else
    {
        // free the reader
        cbox->reader->memIntf->heap.free(cbox->reader);
        cbox->reader = NULL;
        
        if(cbox->text.length > 0 || cbox->text.table_index != LA_STRING_NULLIDX)
	    {
	        cbox->widget.drawState = DRAW_STRING;
	        cbox->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
	    }
	    else if(cbox->widget.borderType != LA_WIDGET_BORDER_NONE)
	    {
	        cbox->widget.drawState = DRAW_BORDER;
	        cbox->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	    }
	    else
	    {
	        cbox->widget.drawState = DONE;
	        cbox->widget.drawFunc = NULL;
	        
	        return;
	    }
    }
    
    if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    cbox->widget.drawFunc(cbox);
}

static void drawString(laCheckBoxWidget* cbox)
{
    GFX_Rect textRect;
    GFX_Rect imageRect;
    GFX_Rect bounds;
    
    bounds = cbox->widget.rect;
    bounds.x = 0;
    bounds.y = 0;
    
    laString_GetRect(&cbox->text, &textRect);
    
    // calculate image dimensions
    if(cbox->checked == LA_TRUE)
    {
        if(cbox->checkedImage != NULL)
        {
            imageRect.width = cbox->checkedImage->width;
            imageRect.height = cbox->checkedImage->height;
        }
        else
        {
            imageRect.width = CHECKBOX_SIZE;
            imageRect.height = CHECKBOX_SIZE;
        }
    }
    else
    {
        if(cbox->uncheckedImage != NULL)
        {
            imageRect.width = cbox->uncheckedImage->width;
            imageRect.height = cbox->uncheckedImage->height;
        }
        else
        {
            imageRect.width = CHECKBOX_SIZE;
            imageRect.height = CHECKBOX_SIZE;
        }
    }
    
    //rect.width = cbox->paintData.stringRect.width;
    //rect.height = cbox->paintData.stringRect.height;
    
    // arrange relative to image rect
    laUtils_ArrangeRectangleRelative(&textRect,
                                     imageRect,
                                     bounds,
                                     cbox->halign,
                                     cbox->valign,
                                     cbox->imagePosition,
                                     cbox->widget.margin.left,
                                     cbox->widget.margin.top,
                                     cbox->widget.margin.right,
                                     cbox->widget.margin.bottom,
                                     cbox->imageMargin);
    
    // move the rect to parent space
    //rect.x += cbox->widget.rect.x;
    //rect.y += cbox->widget.rect.y;
    
    laUtils_RectToScreenSpace((laWidget*)cbox, &textRect);
    
    //cbox->paintData.stringRect.x = rect.x;
    //cbox->paintData.stringRect.y = rect.y;
        
    /*GFX_Set(GFXF_DRAW_COLOR, GFX_ColorValue(GFX_COLOR_MODE_RGB_888, GFX_COLOR_RED));
    GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_LINE);
    GFX_DrawRect(cbox->paintData.stringRect.x,
                 cbox->paintData.stringRect.y,
                 rect.width,
                 rect.height);*/
        
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    GFX_Set(GFXF_DRAW_COLOR, cbox->widget.scheme->text);
    
    laString_Draw(&cbox->text,
                  textRect.x,
                  textRect.y,
                  &cbox->reader);
    
    if(cbox->reader != NULL)
    {
        cbox->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&waitString;
	    cbox->widget.drawState = WAIT_STRING;
    }
    else if(cbox->widget.borderType != LA_WIDGET_BORDER_NONE)
    {
	    cbox->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	    cbox->widget.drawState = DRAW_BORDER;
	}
	else
	{
	    cbox->widget.drawFunc = NULL;
	    cbox->widget.drawState = DONE;
	    
	    return;
	}
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    cbox->widget.drawFunc(cbox);
}

static void waitString(laCheckBoxWidget* cbox)
{
    if(cbox->reader->status != GFXU_READER_STATUS_FINISHED)
    {
        cbox->reader->run(cbox->reader);
        
        return;
    }
    
    // free the reader
    cbox->reader->memIntf->heap.free(cbox->reader);
    cbox->reader = NULL;
    
    if(cbox->widget.borderType != LA_WIDGET_BORDER_NONE)
    {
	    cbox->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	    cbox->widget.drawState = DRAW_BORDER;
	    
	    cbox->widget.drawFunc(cbox);
	}
	else
	{
	    cbox->widget.drawFunc = NULL;
	    cbox->widget.drawState = DONE;
	
	    return;
	}
    
    if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    cbox->widget.drawFunc(cbox);
}

static void drawBorder(laCheckBoxWidget* cbox)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(cbox->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = cbox->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)cbox->widget.parent, &rect);
	    
		laDraw_LineBorder(&rect, cbox->widget.scheme->shadowDark);
	}
	else if(cbox->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = cbox->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)cbox, &rect);
	    
		laDraw_2x2BevelBorder(&cbox->widget.rect,
						      cbox->widget.scheme->highlightLight,
						      cbox->widget.scheme->highlightLight,
						      cbox->widget.scheme->shadow,
							  cbox->widget.scheme->shadowDark);
    }
	
	cbox->widget.drawState = DONE;
	cbox->widget.drawFunc = NULL;
}

void _laCheckBoxWidget_Paint(laCheckBoxWidget* cbox)
{
    if(cbox->widget.scheme == NULL)
    {
        cbox->widget.drawState = DONE;
        
        return;
    }
    
    if(cbox->widget.drawState == NOT_STARTED)
        cbox->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
	
	cbox->widget.drawFunc((laWidget*)cbox);
}

/*void _laCheckBoxWidget_GetCheckRect(laCheckBoxWidget* cbox, GFX_Rect* rect)
{
    if(cbox->halign == LA_HALIGN_LEFT)
        rect->x = BORDER_MARGIN;
    else if(cbox->halign == LA_HALIGN_CENTER)
        rect->x = (cbox->widget.rect.width / 2) -
                  ((CHECKBOX_SIZE + TEXT_MARGIN + cbox->paintData.stringRect.width) / 2);
    else
        rect->x = cbox->widget.rect.width - 
                  (BORDER_MARGIN + CHECKBOX_SIZE + TEXT_MARGIN + cbox->paintData.stringRect.width);
    
    if(cbox->valign == LA_VALIGN_TOP)
        rect->y = BORDER_MARGIN;
    else if(cbox->valign == LA_VALIGN_MIDDLE)
        rect->y = (cbox->widget.rect.height / 2) - CHECKBOX_SIZE_HALF;
    else
        rect->y = cbox->widget.rect.height - CHECKBOX_SIZE - BORDER_MARGIN;
        
    rect->width = CHECKBOX_SIZE;
    rect->height = CHECKBOX_SIZE;
}*/

#endif // LA_CHECKBOX_WIDGET_ENABLED