#include "gfx/libaria/inc/libaria_widget_listwheel.h"

#if LA_LISTWHEEL_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define DISPLAY_ITEM_COUNT 5

enum
{
    NOT_STARTED = LA_WIDGET_DRAW_STATE_READY,
    DONE = LA_WIDGET_DRAW_STATE_DONE,
    DRAW_BACKGROUND,
    DRAW_STRING,
    WAIT_STRING,
    DRAW_ICON,
    WAIT_ICON,
    DRAW_BORDER,
};

static void drawBackground(laListWheelWidget* whl);
static void drawString(laListWheelWidget* whl);
static void waitString(laListWheelWidget* whl);
static void drawIcon(laListWheelWidget* whl);
static void waitIcon(laListWheelWidget* whl);
static void drawBorder(laListWheelWidget* whl);

static int prev(int size, int idx)
{
    int prevIdx = idx;
    
    if(prevIdx == 0)
        prevIdx = size - 1;
    else
        prevIdx--;
    
    return prevIdx;
}
    
static void firstItem(laListWheelWidget* whl)
{
    int idx;
    
    whl->paintState.nextItem = whl->selectedItem;
    whl->paintState.y = 0;
    
    if(whl->items.size == 0)
        return;
    
    for(idx = 0; idx < 2; idx++)
        whl->paintState.nextItem = prev(whl->items.size, whl->paintState.nextItem);
}

static void nextItem(laListWheelWidget* whl)
{
    if(whl->paintState.y < DISPLAY_ITEM_COUNT)
    {
        whl->paintState.nextItem++;
        whl->paintState.y++;
        
        if(whl->paintState.nextItem >= whl->items.size)
            whl->paintState.nextItem = 0;
        
        whl->widget.drawState = DRAW_STRING;
	    whl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
    }
    else if(whl->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    whl->widget.drawState = DRAW_BORDER;
	    whl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
	{
	    whl->widget.drawState = DONE;
        whl->widget.drawFunc = NULL;
	}
}

static void drawBackground(laListWheelWidget* whl)
{
    GFX_Rect rect;
    int32_t rowSize = whl->widget.rect.height / 5;
    
    rect = whl->widget.rect;
    rect.x = 0;
    rect.y = 0;
    
    laUtils_RectToLayerSpace((laWidget*)whl, &rect);
	    
	if(whl->widget.drawBackground == LA_TRUE)
	{
	    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_Set(GFXF_DRAW_COLOR, whl->widget.scheme->background);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(rect.x,
					 rect.y,
					 rect.width,
					 rect.height);
	    
	    
					 
	    /*GFX_Set(GFXF_DRAW_COLOR, whl->widget.scheme->backgroundInactive);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(rect.x,
					 rect.y + rect.height - (rect.height / 4),
					 rect.width,
					 rect.height / 4);*/
	}
	
	// draw middle lines
    GFX_Set(GFXF_DRAW_COLOR, whl->widget.scheme->foreground);
	GFX_DrawLine(rect.x, rect.y + (rowSize * 2), rect.x + rect.width, rect.y + (rowSize * 2));
	GFX_DrawLine(rect.x, rect.y + (rowSize * 3), rect.x + rect.width, rect.y + (rowSize * 3));
	
	GFX_Set(GFXF_DRAW_COLOR, whl->widget.scheme->foregroundDisabled);
	GFX_DrawLine(rect.x, rect.y + (rowSize * 2) + 1, rect.x + rect.width, rect.y + (rowSize * 2) + 1);
	GFX_DrawLine(rect.x, rect.y + (rowSize * 3) + 1, rect.x + rect.width, rect.y + (rowSize * 3) + 1);
	
	if(whl->items.size > 0)
	{
	    whl->widget.drawState = DRAW_STRING;
	    whl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
	}
	else if(whl->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    whl->widget.drawState = DRAW_BORDER;
	    whl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        whl->widget.drawState = DONE;
        whl->widget.drawFunc = NULL;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2 &&
	   whl->widget.drawFunc != NULL)
	    whl->widget.drawFunc(whl);
}

static void drawString(laListWheelWidget* whl)
{
    GFX_Rect textRect, itemRect, widgetRect, imageRect;
        
    // get rectangles
    whl->paintState.item = laList_Get(&whl->items, whl->paintState.nextItem);
    
    laString_GetRect(&whl->paintState.item->string, &textRect);
    
    whl->paintState.itemRect.x = 0;
    whl->paintState.itemRect.width = whl->widget.rect.width;
    
    whl->paintState.itemRect.y = 0;
    whl->paintState.itemRect.height = whl->widget.rect.height / DISPLAY_ITEM_COUNT;
    
    whl->paintState.itemRect.y = (whl->paintState.y * whl->paintState.itemRect.height);
    
    imageRect = GFX_Rect_Zero;
    
    if(whl->paintState.item->icon != NULL)
    {
        imageRect.width = whl->paintState.item->icon->width;
        imageRect.height = whl->paintState.item->icon->height;
    }
    
    // arrange relative to image rect
    laUtils_ArrangeRectangleRelative(&textRect,
                                     imageRect,
                                     whl->paintState.itemRect,
                                     whl->halign,
                                     LA_VALIGN_MIDDLE,
                                     whl->iconPos,
                                     whl->widget.margin.left,
                                     whl->widget.margin.top,
                                     whl->widget.margin.right,
                                     whl->widget.margin.bottom,
                                     whl->iconMargin);
                                     
    
    
    // move the rect to parent space
    laUtils_RectToScreenSpace((laWidget*)whl, &textRect);
    
    widgetRect = whl->widget.rect;
    widgetRect.x = 0;
    widgetRect.y = 0;
    
    laUtils_RectToScreenSpace((laWidget*)whl, &widgetRect);
    
    itemRect = whl->paintState.itemRect;
    laUtils_RectToScreenSpace((laWidget*)whl, &itemRect);
    
    // only need to render strings inside bounds
    if(GFX_RectIntersects(&textRect, &widgetRect) == GFX_TRUE)
    {
        if(whl->paintState.y == 2)
            GFX_Set(GFXF_DRAW_COLOR, whl->widget.scheme->text);
        else if(whl->paintState.y == 1 || whl->paintState.y == 3)
            GFX_Set(GFXF_DRAW_COLOR, whl->widget.scheme->textDisabled);
        else
            GFX_Set(GFXF_DRAW_COLOR, whl->widget.scheme->textInactive);
            
        //printf("%u\n", whl->paintState.item->string.table_index);
    
        GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
        laString_Draw(&whl->paintState.item->string,
                      textRect.x,
                      textRect.y,
                      &whl->reader);
                      
                     /* if(whl->paintState.item->string.table_index == 12)
                      {
                        widgetRect.x = widgetRect.x;
                      }*/
                      
        //itemRect.y += whl->paintState.y;
    
        //GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_LINE);
        //GFX_Set(GFXF_DRAW_COLOR, GFX_ColorValue(GFX_COLOR_MODE_RGB_565, GFX_COLOR_RED));
        //GFX_DrawRect(itemRect.x, itemRect.y, itemRect.width, itemRect.height);
    }
    
    if(whl->reader != NULL)
    {
        whl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&waitString;
	    whl->widget.drawState = WAIT_STRING;
    }
    else if(whl->paintState.item->icon != NULL)
    {
        whl->widget.drawState = DRAW_ICON;
	    whl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawIcon;
    }
    else
    {
        nextItem(whl);
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2 &&
	   whl->widget.drawFunc != NULL)
	    whl->widget.drawFunc(whl);
}

static void waitString(laListWheelWidget* whl)
{
    if(whl->reader->status != GFXU_READER_STATUS_FINISHED)
    {
        whl->reader->run(whl->reader);
        
        return;
    }
    
    // free the reader
    whl->reader->memIntf->heap.free(whl->reader);
    whl->reader = NULL;
    
    if(whl->paintState.item->icon != NULL)
    {
        whl->widget.drawState = DRAW_ICON;
	    whl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawIcon;
    }
    else
    {
        nextItem(whl);
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2 &&
	   whl->widget.drawFunc != NULL)
	    whl->widget.drawFunc(whl);
}

static void drawIcon(laListWheelWidget* whl)
{
    GFX_Rect rect = {0};
    GFX_Rect textRect = {0};
    GFX_Rect clippedItem;
    GFX_Rect clipRect;
    
    GFXU_ImageAsset* img;
    
    // calculate image dimensions
    img = whl->paintState.item->icon;
            
    rect.width = img->width;
    rect.height = img->height;
    
    laString_GetRect(&whl->paintState.item->string, &textRect);
    
    // arrange image rect
    laUtils_ArrangeRectangle(&rect,
                             textRect,
                             whl->paintState.itemRect,
                             whl->halign,
                             LA_VALIGN_MIDDLE,
                             whl->iconPos,
                             whl->widget.margin.left,
                             whl->widget.margin.top,
                             whl->widget.margin.right,
                             whl->widget.margin.bottom,
                             whl->iconMargin);
    
    clippedItem = whl->paintState.itemRect;
    clippedItem.height -= whl->widget.margin.top + whl->widget.margin.bottom;
    
    GFX_RectClip(&clippedItem, &rect, &clipRect);
    
    //clipRect = rect;
    
    // move the rect to parent space
    //rect.x += whl->widget.rect.x;
    //rect.y += whl->widget.rect.y;
    
    
    
    //GFX_Set(GFXF_DRAW_COLOR, whl->widget.scheme->text);
    
    clipRect.y -= rect.y;
    //rect.y += img->height - clipRect.height;
    
    rect.y += whl->paintState.y;
    
    laUtils_RectToScreenSpace(&whl->widget, &rect);
    
    GFXU_DrawImage(img,
                   0,
                   clipRect.y /*+ whl->widget.margin.top*/,
                   img->width,
                   clipRect.height /*- whl->widget.margin.top - whl->widget.margin.bottom*/,
                   rect.x,
                   rect.y,
                   &laContext_GetActive()->memIntf,
                   &whl->reader);
                
    if(whl->reader != NULL)
    {
        whl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&waitIcon;
	    whl->widget.drawState = WAIT_ICON;
    }
    else
    {
        nextItem(whl);
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2 &&
	   whl->widget.drawFunc != NULL)
	    whl->widget.drawFunc(whl);
}

static void waitIcon(laListWheelWidget* whl)
{
    if(whl->reader->status != GFXU_READER_STATUS_FINISHED)
    {
        whl->reader->run(whl->reader);
        
        return;
    }
    
    // free the reader
    whl->reader->memIntf->heap.free(whl->reader);
    whl->reader = NULL;
    
    nextItem(whl);
    
    if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2 &&
	   whl->widget.drawFunc != NULL)
	    whl->widget.drawFunc(whl);
}

static void drawBorder(laListWheelWidget* whl)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(whl->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = whl->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)whl->widget.parent, &rect);
	    
		laDraw_LineBorder(&rect, whl->widget.scheme->shadowDark);
	}
	else if(whl->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = whl->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)whl, &rect);
	    
		laDraw_2x2BevelBorder(&rect,
						      whl->widget.scheme->shadow,
						      whl->widget.scheme->shadowDark,
						      whl->widget.scheme->highlight,
						      whl->widget.scheme->highlightLight);
	}
	
	whl->widget.drawState = DONE;
	whl->widget.drawFunc = NULL;
}

void _laListWheelWidget_Paint(laListWheelWidget* whl)
{
    if(whl->widget.scheme == NULL)
    {
        whl->widget.drawState = DONE;
        
        return;
    }

    if(whl->widget.drawState == NOT_STARTED)
    {
        firstItem(whl);
        
        if(whl->widget.drawBackground == LA_TRUE)
        {
            whl->widget.drawState = DRAW_BACKGROUND;
            whl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
        }
        else if(whl->items.size > 0)
        {
            whl->widget.drawState = DRAW_STRING;
            whl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
        }
        else if(whl->widget.borderType != LA_WIDGET_BORDER_NONE)
        {
            whl->widget.drawState = DRAW_BORDER;
	        whl->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
        }
        else
        {
            whl->widget.drawState = DONE;
	        whl->widget.drawFunc = NULL;
        }
    }
    
	whl->widget.drawFunc((laWidget*)whl);
}

#endif // LA_LISTWHEEL_WIDGET_ENABLED