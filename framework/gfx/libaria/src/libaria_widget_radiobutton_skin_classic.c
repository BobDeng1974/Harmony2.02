#include "gfx/libaria/inc/libaria_widget_radiobutton.h"

#if LA_RADIOBUTTON_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define CIRCLE_SIZE       12
#define CIRCLE_SIZE_HALF  6

enum
{
    NOT_STARTED = LA_WIDGET_DRAW_STATE_READY,
    DONE = LA_WIDGET_DRAW_STATE_DONE,
    DRAW_IMAGE,
    WAIT_IMAGE,
    DRAW_STRING,
    WAIT_STRING,
    DRAW_BORDER,
};

static void drawBackground(laRadioButtonWidget* btn);
static void drawImage(laRadioButtonWidget* btn);
static void waitImage(laRadioButtonWidget* btn);
static void drawString(laRadioButtonWidget* btn);
static void waitString(laRadioButtonWidget* btn);
static void drawBorder(laRadioButtonWidget* btn);

void _laRadioButtonWidget_GetImageRect(laRadioButtonWidget* btn, GFX_Rect* rect)
{
    GFX_Rect textRect;
    GFX_Rect boundsRect;
    
    boundsRect = btn->widget.rect;
    boundsRect.x = 0;
    boundsRect.y = 0;
    
    rect->x = 0;
    rect->y = 0;
    
    laString_GetRect(&btn->text, &textRect);
    
    if(btn->selected == LA_FALSE)
    {
        if(btn->unselectedImage == NULL)
        {
			rect->width = btn->widget.rect.width;
			rect->height = btn->widget.rect.height;
        }
        else
        {
            rect->width = btn->unselectedImage->width;
            rect->height = btn->unselectedImage->height;
        }
    }
    else if(btn->selected == LA_TRUE)
    {
        if(btn->selectedImage == NULL)
        {
			rect->width = btn->widget.rect.width;
			rect->height = btn->widget.rect.height;
        }
        else
        {
            rect->width = btn->selectedImage->width;
            rect->height = btn->selectedImage->height;
        }
    }
    
    laUtils_ArrangeRectangle(rect,
                             textRect,
                             boundsRect,
                             btn->halign,
                             btn->valign,
                             btn->imagePosition,
                             btn->widget.margin.left,
                             btn->widget.margin.top,
                             btn->widget.margin.right,
                             btn->widget.margin.bottom,
                             btn->imageMargin);
}

static void drawCircle(laRadioButtonWidget* btn, GFX_Rect* rect, laBool filled)
{
    int x = rect->x;
    int y = rect->y;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    // fill
    GFX_Set(GFXF_DRAW_COLOR, btn->widget.scheme->background);
    GFX_DrawLine(x + 4, y + 2, x + 10, y + 2);
    GFX_DrawLine(x + 3, y + 3, x + 10, y + 3);
    GFX_DrawLine(x + 2, y + 4, x + 11, y + 4);
    GFX_DrawLine(x + 2, y + 5, x + 11, y + 5);
    GFX_DrawLine(x + 2, y + 6, x + 11, y + 6);
    GFX_DrawLine(x + 2, y + 7, x + 11, y + 7);
    GFX_DrawLine(x + 3, y + 8, x + 10, y + 8);
    GFX_DrawLine(x + 4, y + 9, x + 10, y + 9);
    GFX_DrawLine(x + 2, y + 10, x + 9, y + 10);
    GFX_DrawLine(x + 4, y + 11, x + 7, y + 11);
    
    // upper outer ring
    GFX_Set(GFXF_DRAW_COLOR, btn->widget.scheme->shadow);
    GFX_DrawLine(x + 4, y + 0, x + 7, y + 0);
    GFX_DrawLine(x + 2, y + 1, x + 3, y + 1);
    GFX_DrawLine(x + 8, y + 1, x + 9, y + 1);
    GFX_DrawLine(x + 8, y + 1, x + 9, y + 1);
    GFX_DrawLine(x + 1, y + 2, x + 1, y + 3);
    GFX_DrawLine(x + 1, y + 8, x + 1, y + 9);
    GFX_DrawLine(x + 1, y + 2, x + 1, y + 3);
    GFX_DrawLine(x + 0, y + 4, x + 0, y + 7);
    
    // upper inner ring
    GFX_Set(GFXF_DRAW_COLOR, btn->widget.scheme->shadowDark);
    GFX_DrawLine(x + 4, y + 1, x + 7, y + 1);
    GFX_DrawLine(x + 2, y + 2, x + 3, y + 2);
    GFX_DrawLine(x + 8, y + 2, x + 9, y + 2);
    GFX_DrawPixel(x + 2, y + 3);
    GFX_DrawLine(x + 1, y + 4, x + 1, y + 7);
    GFX_DrawPixel(x + 2, y + 8);
    
    // lower inner ring
    GFX_Set(GFXF_DRAW_COLOR, btn->widget.scheme->highlight);
    GFX_DrawPixel(x + 9, y + 3);
    GFX_DrawLine(x + 10, y + 4, x + 10, y + 7);
    GFX_DrawPixel(x + 9, y + 8);
    GFX_DrawLine(x + 2, y + 9, x + 3, y + 9);
    GFX_DrawLine(x + 8, y + 9, x + 9, y + 9);    
    GFX_DrawLine(x + 4, y + 10, x + 7, y + 10);
    
    if(filled == LA_TRUE)
    {
        GFX_Set(GFXF_DRAW_COLOR, btn->widget.scheme->foreground);
        GFX_DrawLine(x + 5, y + 4, x + 6, y + 4);
        GFX_DrawLine(x + 4, y + 5, x + 7, y + 5);
        GFX_DrawLine(x + 4, y + 6, x + 7, y + 6);
        GFX_DrawLine(x + 5, y + 7, x + 6, y + 7);
    }
}

static void drawBackground(laRadioButtonWidget* btn)
{
    GFX_Rect rect;
	
	//printf("button painting\n");
	
	if(btn->widget.drawBackground == LA_TRUE)
	{
	    rect = btn->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)btn->widget.parent, &rect);
	    
		GFX_Set(GFXF_DRAW_COLOR, btn->widget.scheme->base);
		
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(btn->widget.rect.x,
					 btn->widget.rect.y,
					 btn->widget.rect.width,
					 btn->widget.rect.height);
	}
	
	
	/*if((btn->selected == LA_FALSE && btn->unselectedImage != NULL) ||
	   (btn->selected == LA_TRUE && btn->unselectedImage != NULL))
	{
	    
	}
	else if(btn->text.length > 0 || btn->text.table_index != LA_STRING_NULLIDX)
	{
	    btn->widget.drawState = DRAW_STRING;
	    btn->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
	}
	else if(btn->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    btn->widget.drawState = DRAW_BORDER;
	    btn->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
	{
	    btn->widget.drawState = DONE;
	    btn->widget.drawFunc = NULL;
	    
	    return;
	}*/
	
	btn->widget.drawState = DRAW_IMAGE;
	btn->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawImage;
	
	//btn->widget.drawFunc((laWidget*)btn);
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    btn->widget.drawFunc(btn);
}

static void drawImage(laRadioButtonWidget* btn)
{
    GFX_Rect rect = {0};
    GFX_Rect textRect;
    GFX_Rect boundsRect;
    
    GFXU_ImageAsset* img = NULL;
    laBool filled = LA_FALSE;
    
    boundsRect = btn->widget.rect;
    boundsRect.x = 0;
    boundsRect.y = 0;
    
    // calculate image dimensions
    if(btn->selected == LA_TRUE)
    {
        if(btn->selectedImage != NULL)
        {
            img = btn->selectedImage;
            
            rect.width = btn->selectedImage->width;
            rect.height = btn->selectedImage->height;
        }
        else
        {
            rect.width = CIRCLE_SIZE;
            rect.height = CIRCLE_SIZE;
            
            filled = LA_TRUE;
        }
    }
    else
    {
        if(btn->unselectedImage != NULL)
        {
            img = btn->unselectedImage;
            
            rect.width = btn->unselectedImage->width;
            rect.height = btn->unselectedImage->height;
        }
        else
        {
            rect.width = CIRCLE_SIZE;
            rect.height = CIRCLE_SIZE;
        }
    }
    
    laString_GetRect(&btn->text, &textRect);
    
    // arrange image rect
    laUtils_ArrangeRectangle(&rect,
                             textRect,
                             boundsRect,
                             btn->halign,
                             btn->valign,
                             btn->imagePosition,
                             btn->widget.margin.left,
                             btn->widget.margin.top,
                             btn->widget.margin.right,
                             btn->widget.margin.bottom,
                             btn->imageMargin);
    
    // move the rect to parent space
    //rect.x += btn->widget.rect.x;
    //rect.y += btn->widget.rect.y;
    laUtils_RectToScreenSpace((laWidget*)btn, &rect);
    
    //GFX_Set(GFXF_DRAW_COLOR, btn->widget.scheme->text);
    
    if(img == NULL)
    {
        drawCircle(btn, &rect, filled);
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
                       &btn->reader);
    }
                
    if(btn->reader == NULL)
    {  
        if(btn->text.length > 0 || btn->text.table_index != LA_STRING_NULLIDX)
	    {
	        btn->widget.drawState = DRAW_STRING;
	        btn->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
	    }
	    else if(btn->widget.borderType != LA_WIDGET_BORDER_NONE)
	    {
	        btn->widget.drawState = DRAW_BORDER;
	        btn->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	    }
	    else
	    {
	        btn->widget.drawState = DONE;
	        btn->widget.drawFunc = NULL;
    	    
	        return;
	    }
	}
	else
	{
	    btn->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&waitImage;
	    btn->widget.drawState = WAIT_IMAGE;
	}
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    btn->widget.drawFunc(btn);
}

static void waitImage(laRadioButtonWidget* btn)
{
    if(btn->reader->status != GFXU_READER_STATUS_FINISHED)
    {
        btn->reader->run(btn->reader);
        
        return;
    }
    
    // free the reader
    btn->reader->memIntf->heap.free(btn->reader);
    btn->reader = NULL;
    
    if(btn->text.length > 0 || btn->text.table_index != LA_STRING_NULLIDX)
    {
        btn->widget.drawState = DRAW_STRING;
        btn->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
    }
    else if(btn->widget.borderType != LA_WIDGET_BORDER_NONE)
    {
        btn->widget.drawState = DRAW_BORDER;
        btn->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
    }
    else
    {
        btn->widget.drawState = DONE;
        btn->widget.drawFunc = NULL;
	    
        return;
    }
    
    if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    btn->widget.drawFunc(btn);
}

static void drawString(laRadioButtonWidget* btn)
{
    GFX_Rect textRect;// = {0};
    GFX_Rect imageRect = {0};
    GFX_Rect boundsRect;
    
    boundsRect = btn->widget.rect;
    boundsRect.x = 0;
    boundsRect.y = 0;
    
    // calculate image dimensions
    if(btn->selected == LA_TRUE)
    {
        if(btn->selectedImage != NULL)
        {
            imageRect.width = btn->selectedImage->width;
            imageRect.height = btn->selectedImage->height;
        }
        else
        {
            imageRect.width = CIRCLE_SIZE;
            imageRect.height = CIRCLE_SIZE;
        }
    }
    else
    {
        if(btn->unselectedImage != NULL)
        {
            imageRect.width = btn->unselectedImage->width;
            imageRect.height = btn->unselectedImage->height;
        }
        else
        {
            imageRect.width = CIRCLE_SIZE;
            imageRect.height = CIRCLE_SIZE;
        }
    }
    
    laString_GetRect(&btn->text, &textRect);
    
    // arrange relative to image rect
    laUtils_ArrangeRectangleRelative(&textRect,
                                     imageRect,
                                     boundsRect,
                                     btn->halign,
                                     btn->valign,
                                     btn->imagePosition,
                                     btn->widget.margin.left,
                                     btn->widget.margin.top,
                                     btn->widget.margin.right,
                                     btn->widget.margin.bottom,
                                     btn->imageMargin);
    
    // move the rect to parent space
    //rect.x += btn->widget.rect.x;
    //rect.y += btn->widget.rect.y;
    laUtils_RectToScreenSpace((laWidget*)btn, &textRect);
    
    //btn->paintData.stringRect.x = rect.x;
    //btn->paintData.stringRect.y = rect.y;
        
    /*GFX_Set(GFXF_DRAW_COLOR, GFX_ColorValue(GFX_COLOR_MODE_RGB_888, GFX_COLOR_RED));
    GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_LINE);
    GFX_DrawRect(btn->paintData.stringRect.x,
                 btn->paintData.stringRect.y,
                 rect.width,
                 rect.height);*/
        
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    GFX_Set(GFXF_DRAW_COLOR, btn->widget.scheme->text);
    laString_Draw(&btn->text,
                  textRect.x,
                  textRect.y,
                  &btn->reader);
    
    
    if(btn->reader != NULL)
    {
        btn->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&waitString;
	    btn->widget.drawState = WAIT_STRING;
    }
    else if(btn->widget.borderType != LA_WIDGET_BORDER_NONE)
    {
        btn->widget.drawState = DRAW_BORDER;
        btn->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
    }
    else
    {
        btn->widget.drawState = DONE;
        btn->widget.drawFunc = NULL;
	    
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    btn->widget.drawFunc(btn);
}

static void waitString(laRadioButtonWidget* btn)
{
    if(btn->reader->status != GFXU_READER_STATUS_FINISHED)
    {
        btn->reader->run(btn->reader);
        
        return;
    }
    
    // free the reader
    btn->reader->memIntf->heap.free(btn->reader);
    btn->reader = NULL;
    
    if(btn->widget.borderType != LA_WIDGET_BORDER_NONE)
    {
        btn->widget.drawState = DRAW_BORDER;
        btn->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
    }
    else
    {
        btn->widget.drawState = DONE;
        btn->widget.drawFunc = NULL;
	    
        return;
    }
    
    if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    btn->widget.drawFunc(btn);
}

static void drawBorder(laRadioButtonWidget* btn)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(btn->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = btn->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)btn, &rect);
	    
		laDraw_LineBorder(&rect, btn->widget.scheme->shadowDark);
	}
	else if(btn->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = btn->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)btn, &rect);
	    
		laDraw_2x2BevelBorder(&btn->widget.rect,
						      btn->widget.scheme->highlightLight,
						      btn->widget.scheme->highlightLight,
						      btn->widget.scheme->shadow,
							  btn->widget.scheme->shadowDark);
    }
	
	btn->widget.drawState = DONE;
	btn->widget.drawFunc = NULL;
}

void _laRadioButtonWidget_Paint(laRadioButtonWidget* btn)
{
    if(btn->widget.scheme == NULL)
    {
        btn->widget.drawState = DONE;
        
        return;
    }
    
    if(btn->widget.drawState == NOT_STARTED)
        btn->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
	
	btn->widget.drawFunc((laWidget*)btn);
}

#endif // LA_RADIOBUTTON_WIDGET_ENABLED