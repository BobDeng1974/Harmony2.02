#include "gfx/libaria/inc/libaria_widget_button.h"

#if LA_BUTTON_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

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

static void drawBackground(laButtonWidget* btn);
static void drawString(laButtonWidget* btn);
static void waitString(laButtonWidget* btn);
static void drawImage(laButtonWidget* btn);
static void waitImage(laButtonWidget* btn);
static void drawBorder(laButtonWidget* btn);

static void drawBackground(laButtonWidget* btn)
{
    GFX_Rect rect = btn->widget.rect;
	
	//printf("button painting\n");
	
	if(btn->widget.drawBackground == LA_TRUE)
	{
	    laUtils_RectToScreenSpace(btn->widget.parent, &rect);
	    
		if(btn->state != LA_BUTTON_STATE_UP)
			GFX_Set(GFXF_DRAW_COLOR, btn->widget.scheme->background);
		else
			GFX_Set(GFXF_DRAW_COLOR, btn->widget.scheme->base);

        GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(rect.x,
					 rect.y,
					 rect.width,
					 rect.height);
	}
	
	
	if((btn->state != LA_BUTTON_STATE_UP && btn->pressedImage != NULL) ||
	   (btn->state == LA_BUTTON_STATE_UP && btn->releasedImage != NULL))
	{
	    btn->widget.drawState = DRAW_IMAGE;
	    btn->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawImage;
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
	}
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    btn->widget.drawFunc((laWidget*)btn);
}

static void drawImage(laButtonWidget* btn)
{
    GFX_Rect rect = {0};
    GFX_Rect textRect = {0};
    GFXU_ImageAsset* img = NULL;
    GFX_Rect bounds = btn->widget.rect;
    
    bounds.x = 0;
    bounds.y = 0;
    
    // calculate image dimensions
    if(btn->state != LA_BUTTON_STATE_UP)
    {
        if(btn->pressedImage != NULL)
        {
            img = btn->pressedImage;
            
            rect.width = btn->pressedImage->width;
            rect.height = btn->pressedImage->height;
        }
    }
    else
    {
        if(btn->releasedImage != NULL)
        {
            img = btn->releasedImage;
            
            rect.width = btn->releasedImage->width;
            rect.height = btn->releasedImage->height;
        }
    }
    
    laString_GetRect(&btn->text, &textRect);
    
    // arrange image rect
    laUtils_ArrangeRectangle(&rect,
                             textRect,
                             bounds,
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
    laUtils_RectToScreenSpace(&btn->widget, &rect);
    
    if(btn->state != LA_BUTTON_STATE_UP)
    {
        rect.x += btn->pressedOffset;
        rect.y += btn->pressedOffset;
    }
    
    //GFX_Set(GFXF_DRAW_COLOR, btn->widget.scheme->text);
    
    GFXU_DrawImage(img,
                   0,
                   0,
                   img->width,
                   img->height,
                   rect.x,
                   rect.y,
                   &laContext_GetActive()->memIntf,
                   &btn->reader);
                
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
	    btn->widget.drawFunc((laWidget*)btn);
}

static void waitImage(laButtonWidget* btn)
{
    if(btn->reader->status != GFXU_READER_STATUS_FINISHED)
    {
        btn->reader->run(btn->reader);
        
        return;
    }
    else
    {
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
    }
    
    if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    btn->widget.drawFunc((laWidget*)btn);
}

static void drawString(laButtonWidget* btn)
{
    GFX_Rect textRect;
    GFX_Rect imageRect = {0};
    GFX_Rect bounds = btn->widget.rect;
    
    bounds.x = 0;
    bounds.y = 0;
        
    // calculate image dimensions
    if(btn->state != LA_BUTTON_STATE_UP)
    {
        if(btn->pressedImage != NULL)
        {
            imageRect.width = btn->pressedImage->width;
            imageRect.height = btn->pressedImage->height;
        }
    }
    else
    {
        if(btn->releasedImage != NULL)
        {
            imageRect.width = btn->releasedImage->width;
            imageRect.height = btn->releasedImage->height;
        }
    }
    
    laString_GetRect(&btn->text, &textRect);
    
    // arrange relative to image rect
    laUtils_ArrangeRectangleRelative(&textRect,
                                     imageRect,
                                     bounds,
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
    
    if(btn->state != LA_BUTTON_STATE_UP)
    {
        textRect.x += btn->pressedOffset;
        textRect.y += btn->pressedOffset;
    }
    
    //btn->paintData.stringRect.x = textRect.x;
    //btn->paintData.stringRect.y = textRect.y;
        
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
	    btn->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	    btn->widget.drawState = DRAW_BORDER;
	}
	else
    {
        btn->widget.drawState = DONE;
        btn->widget.drawFunc = NULL;
    
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    btn->widget.drawFunc((laWidget*)btn);
}

static void waitString(laButtonWidget* btn)
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
	    btn->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	    btn->widget.drawState = DRAW_BORDER;
	}
	else
    {
        btn->widget.drawState = DONE;
        btn->widget.drawFunc = NULL;
    
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    btn->widget.drawFunc((laWidget*)btn);
}

static void drawBorder(laButtonWidget* btn)
{
    GFX_Rect rect = btn->widget.rect;
    
    laUtils_RectToScreenSpace(btn->widget.parent, &rect);
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(btn->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
		laDraw_LineBorder(&rect, btn->widget.scheme->shadowDark);
	}
	else if(btn->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
		if(btn->state != LA_BUTTON_STATE_UP)
		{
			laDraw_2x2BevelBorder(&rect,
							      btn->widget.scheme->shadowDark,
							      btn->widget.scheme->shadow,
							      btn->widget.scheme->highlight,
								  btn->widget.scheme->highlightLight);
		}
		else
		{
			laDraw_1x2BevelBorder(&rect,
							      btn->widget.scheme->highlightLight,
							      btn->widget.scheme->shadow,
							      btn->widget.scheme->shadowDark);
		}
	}
	
	btn->widget.drawState = DONE;
	btn->widget.drawFunc = NULL;
}

void _laButtonWidget_Paint(laButtonWidget* btn)
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

#endif // LA_BUTTON_WIDGET_ENABLED