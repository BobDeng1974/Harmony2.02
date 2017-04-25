#include "gfx/libaria/inc/libaria_widget_image.h"

#if LA_IMAGE_WIDGET_ENABLED

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
    DRAW_BORDER,
};

static void drawBackground(laImageWidget* img);
static void drawImage(laImageWidget* img);
static void waitImage(laImageWidget* img);
static void drawBorder(laImageWidget* img);

static void drawBackground(laImageWidget* img)
{
    GFX_Rect rect;
	
	//printf("image painting\n");
	
	if(img->widget.drawBackground == LA_TRUE)
	{
	    rect = img->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)img, &rect);
	    
		GFX_Set(GFXF_DRAW_COLOR, img->widget.scheme->base);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(rect.x, rect.y, rect.width, rect.height);
	}
	
	if(img->image != NULL)
	{
	    img->widget.drawState = DRAW_IMAGE;
	    img->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawImage;
	}
	else if(img->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    img->widget.drawState = DRAW_BORDER;
	    img->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        img->widget.drawState = DONE;
        img->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    img->widget.drawFunc(img);
}

static void drawImage(laImageWidget* img)
{
    GFX_Rect rect = {0};
    GFX_Rect bounds = img->widget.rect;
	GFX_Rect source_rect = {0};
    
    // calculate image dimensions
    bounds.x = 0;
    bounds.y = 0;
    rect.width = img->image->width;
    rect.height = img->image->height;

    // arrange image rect
    laUtils_ArrangeRectangle(&rect,
                             GFX_Rect_Zero,
                             bounds,
                             img->halign,
                             img->valign,
                             0,
                             img->widget.margin.left,
                             img->widget.margin.top,
                             img->widget.margin.right,
                             img->widget.margin.bottom,
                             0);
    
	if (!GFX_RectContainsRect(&bounds, &rect))
	{
		source_rect.x = abs(rect.x);
		source_rect.y = abs(rect.y);
	}

    // move the rect to parent space
    laUtils_RectToScreenSpace((laWidget*)img, &rect);
    //laUtils_RectToLayerSpace((laWidget*)img->widget.parent, &rect);
    //rect.x += img->widget.rect.x;
    //rect.y += img->widget.rect.y;
    
    //GFX_Set(GFXF_DRAW_COLOR, img->widget.scheme->text);

    GFXU_DrawImage(img->image,
				   source_rect.x,
				   source_rect.y,
				   rect.width,
				   rect.height,
                   rect.x,
                   rect.y,
                   &laContext_GetActive()->memIntf,
                   &img->reader);
                   
    //GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_LINE);
    //GFX_Set(GFXF_DRAW_COLOR, GFX_ColorValue(GFX_COLOR_MODE_RGB_888, GFX_COLOR_RED));
    //GFX_DrawRect(rect.x, rect.y, rect.width, rect.height);
                
    if(img->reader != NULL)
    {  
        img->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&waitImage;
	    img->widget.drawState = WAIT_IMAGE;
	}
	else if(img->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    img->widget.drawState = DRAW_BORDER;
	    img->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        img->widget.drawState = DONE;
        img->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    img->widget.drawFunc(img);
}

static void waitImage(laImageWidget* img)
{
    if(img->reader->status != GFXU_READER_STATUS_FINISHED)
    {
        img->reader->run(img->reader);
        
        return;
    }
    
    // free the reader
    img->reader->memIntf->heap.free(img->reader);
    img->reader = NULL;
    
    if(img->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    img->widget.drawState = DRAW_BORDER;
	    img->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        img->widget.drawState = DONE;
        img->widget.drawFunc = NULL;
        
        return;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    img->widget.drawFunc(img);
}

static void drawBorder(laImageWidget* img)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(img->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = img->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)img, &rect);
	    
		laDraw_LineBorder(&rect, img->widget.scheme->shadowDark);
	}
	else if(img->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = img->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)img, &rect);
	    
		laDraw_2x2BevelBorder(&img->widget.rect,
						      img->widget.scheme->highlightLight,
						      img->widget.scheme->highlightLight,
						      img->widget.scheme->shadow,
							  img->widget.scheme->shadowDark);
	}
	
	img->widget.drawState = DONE;
	img->widget.drawFunc = NULL;
}

void _laImageWidget_Paint(laImageWidget* img)
{
    if(img->widget.scheme == NULL)
    {
        img->widget.drawState = DONE;
        
        return;
    }
    
    if(img->widget.drawState == NOT_STARTED)
        img->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
	
	img->widget.drawFunc((laWidget*)img);
}

#endif // LA_IMAGE_WIDGET_ENABLED