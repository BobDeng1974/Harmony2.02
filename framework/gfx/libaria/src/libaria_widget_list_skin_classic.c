#include "gfx/libaria/inc/libaria_widget_list.h"

#if LA_LIST_WIDGET_ENABLED && LA_SCROLLBAR_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

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

static void drawBackground(laListWidget* lst);
static void drawString(laListWidget* lst);
static void waitString(laListWidget* lst);
static void drawIcon(laListWidget* lst);
static void waitIcon(laListWidget* lst);
static void drawBorder(laListWidget* lst);

static void nextItem(laListWidget* lst)
{
    if(lst->paintState.nextItem + 1 < lst->items.size)
    {
        lst->paintState.y += lst->paintState.itemRect.height;
        lst->paintState.nextItem++;
        
        lst->widget.drawState = DRAW_STRING;
	    lst->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
    }
    else if(lst->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    lst->widget.drawState = DRAW_BORDER;
	    lst->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
	{
	    lst->widget.drawState = DONE;
        lst->widget.drawFunc = NULL;
	}
}

static void drawBackground(laListWidget* lst)
{
    GFX_Rect rect;
    
	if(lst->widget.drawBackground == LA_TRUE)
	{
	    rect = lst->widget.rect;
	    
	    laUtils_RectToLayerSpace((laWidget*)lst->widget.parent, &rect);
	    
	    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_Set(GFXF_DRAW_COLOR, lst->widget.scheme->background);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(lst->widget.rect.x,
					 lst->widget.rect.y,
					 lst->widget.rect.width,
					 lst->widget.rect.height);
	}
	
	if(lst->items.size > 0)
	{
	    lst->widget.drawState = DRAW_STRING;
	    lst->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
	}
	else if(lst->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    lst->widget.drawState = DRAW_BORDER;
	    lst->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
    {
        lst->widget.drawState = DONE;
        lst->widget.drawFunc = NULL;
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2 &&
	   lst->widget.drawFunc != NULL)
	    lst->widget.drawFunc(lst);
}

static void drawString(laListWidget* lst)
{
    GFX_Rect textRect, itemRect, widgetRect, imageRect;
        
    // get rectangles
    lst->paintState.item = laList_Get(&lst->items, lst->paintState.nextItem);
    
    laString_GetRect(&lst->paintState.item->string, &textRect);
    
    lst->paintState.itemRect.x = 0;
    lst->paintState.itemRect.width = lst->widget.rect.width;
    
    if(lst->scrollbar.widget.visible == LA_TRUE)
        lst->paintState.itemRect.width -= lst->scrollbar.widget.rect.width;
        
    lst->paintState.itemRect.y = 0;
    lst->paintState.itemRect.height = textRect.height +
                                      lst->widget.margin.top +
                                      lst->widget.margin.bottom;

    imageRect = GFX_Rect_Zero;
    
    if(lst->paintState.item->icon != NULL)
    {
        imageRect.width = lst->paintState.item->icon->width;
        imageRect.height = lst->paintState.item->icon->height;
    }
    
    // arrange relative to image rect
    laUtils_ArrangeRectangleRelative(&textRect,
                                     imageRect,
                                     lst->paintState.itemRect,
                                     lst->halign,
                                     LA_VALIGN_MIDDLE,
                                     lst->iconPos,
                                     lst->widget.margin.left,
                                     lst->widget.margin.top,
                                     lst->widget.margin.right,
                                     lst->widget.margin.bottom,
                                     lst->iconMargin);
                                     
    
    
    // move the rect to parent space
    //rect.x += lst->widget.rect.x;
    //rect.y += lst->widget.rect.y;
    
    laUtils_RectToScreenSpace((laWidget*)lst, &textRect);
    textRect.y += lst->paintState.y - lst->scrollbar.value;
    
    widgetRect = lst->widget.rect;
    widgetRect.x = 0;
    widgetRect.y = 0;
    
    laUtils_RectToScreenSpace((laWidget*)lst, &widgetRect);
    
    itemRect = lst->paintState.itemRect;
    laUtils_RectToScreenSpace((laWidget*)lst, &itemRect);
    itemRect.y += lst->paintState.y - lst->scrollbar.value;
    
    // only need to draw item fill color if inside parent bounds
    if(GFX_RectIntersects(&textRect, &itemRect) == GFX_TRUE)
    {
        if(lst->paintState.nextItem == lst->itemDown)
            GFX_Set(GFXF_DRAW_COLOR, lst->widget.scheme->backgroundInactive);
        else if(lst->paintState.item->selected == LA_TRUE)
            GFX_Set(GFXF_DRAW_COLOR, lst->widget.scheme->textHighlight);
        else
            GFX_Set(GFXF_DRAW_COLOR, lst->widget.scheme->background);
            
        GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
        GFX_DrawRect(itemRect.x, itemRect.y, itemRect.width, itemRect.height);
    }
    
    // only need to render strings inside bounds
    if(GFX_RectIntersects(&textRect, &widgetRect) == GFX_TRUE)
    {
        if(lst->paintState.nextItem == lst->itemDown ||
           lst->paintState.item->selected == LA_FALSE)
            GFX_Set(GFXF_DRAW_COLOR, lst->widget.scheme->text);
        else
            GFX_Set(GFXF_DRAW_COLOR, lst->widget.scheme->textHighlightText);
    
        GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
        laString_Draw(&lst->paintState.item->string,
                      textRect.x,
                      textRect.y,
                      &lst->reader);
                      
        //itemRect.y += lst->paintState.y;
    
        //GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_LINE);
        //GFX_Set(GFXF_DRAW_COLOR, GFX_ColorValue(GFX_COLOR_MODE_RGB_565, GFX_COLOR_RED));
        //GFX_DrawRect(itemRect.x, itemRect.y, itemRect.width, itemRect.height);
    }
    
    if(lst->reader != NULL)
    {
        lst->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&waitString;
	    lst->widget.drawState = WAIT_STRING;
    }
    else if(lst->paintState.item->icon != NULL)
    {
        lst->widget.drawState = DRAW_ICON;
	    lst->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawIcon;
    }
    else
    {
        nextItem(lst);
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2 &&
	   lst->widget.drawFunc != NULL)
	    lst->widget.drawFunc(lst);
}

static void waitString(laListWidget* lst)
{
    if(lst->reader->status != GFXU_READER_STATUS_FINISHED)
    {
        lst->reader->run(lst->reader);
        
        return;
    }
    
    // free the reader
    lst->reader->memIntf->heap.free(lst->reader);
    lst->reader = NULL;
    
    if(lst->paintState.item->icon != NULL)
    {
        lst->widget.drawState = DRAW_ICON;
	    lst->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawIcon;
    }
    else
    {
        nextItem(lst);
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2 &&
	   lst->widget.drawFunc != NULL)
	    lst->widget.drawFunc(lst);
}

static void drawIcon(laListWidget* lst)
{
    GFX_Rect rect = {0};
    GFX_Rect textRect = {0};
    GFX_Rect clippedItem;
    GFX_Rect clipRect;
    
    GFXU_ImageAsset* img;
    
    // calculate image dimensions
    img = lst->paintState.item->icon;
            
    rect.width = img->width;
    rect.height = img->height;
    
    laString_GetRect(&lst->paintState.item->string, &textRect);
    
    // arrange image rect
    laUtils_ArrangeRectangle(&rect,
                             textRect,
                             lst->paintState.itemRect,
                             lst->halign,
                             LA_VALIGN_MIDDLE,
                             lst->iconPos,
                             lst->widget.margin.left,
                             lst->widget.margin.top,
                             lst->widget.margin.right,
                             lst->widget.margin.bottom,
                             lst->iconMargin);
    
    clippedItem = lst->paintState.itemRect;
    clippedItem.height -= lst->widget.margin.top + lst->widget.margin.bottom;
    
    GFX_RectClip(&clippedItem, &rect, &clipRect);
    
    //clipRect = rect;
    
    // move the rect to parent space
    //rect.x += lst->widget.rect.x;
    //rect.y += lst->widget.rect.y;
    
    
    
    //GFX_Set(GFXF_DRAW_COLOR, lst->widget.scheme->text);
    
    clipRect.y -= rect.y;
    //rect.y += img->height - clipRect.height;
    
    rect.y += lst->paintState.y - lst->scrollbar.value;
    
    laUtils_RectToScreenSpace(&lst->widget, &rect);
    
    GFXU_DrawImage(img,
                   0,
                   clipRect.y /*+ lst->widget.margin.top*/,
                   img->width,
                   clipRect.height /*- lst->widget.margin.top - lst->widget.margin.bottom*/,
                   rect.x,
                   rect.y,
                   &laContext_GetActive()->memIntf,
                   &lst->reader);
                
    if(lst->reader != NULL)
    {
        lst->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&waitIcon;
	    lst->widget.drawState = WAIT_ICON;
    }
    else
    {
        nextItem(lst);
    }
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2 &&
	   lst->widget.drawFunc != NULL)
	    lst->widget.drawFunc(lst);
}

static void waitIcon(laListWidget* lst)
{
    if(lst->reader->status != GFXU_READER_STATUS_FINISHED)
    {
        lst->reader->run(lst->reader);
        
        return;
    }
    
    // free the reader
    lst->reader->memIntf->heap.free(lst->reader);
    lst->reader = NULL;
    
    nextItem(lst);
    
    if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2 &&
	   lst->widget.drawFunc != NULL)
	    lst->widget.drawFunc(lst);
}

static void drawBorder(laListWidget* lst)
{
    GFX_Rect rect;
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    // kind of a hack to make sure the border types stay in sync
    // without having to create an event to override
    laWidget_SetBorderType((laWidget*)&lst->scrollbar, lst->widget.borderType);
    
    if(lst->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
	    rect = lst->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)lst->widget.parent, &rect);
	    
		laDraw_LineBorder(&rect, lst->widget.scheme->shadowDark);
	}
	else if(lst->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
	    rect = lst->widget.rect;
	    rect.x = 0;
	    rect.y = 0;
	    
	    laUtils_RectToLayerSpace((laWidget*)lst, &rect);
	    
		laDraw_2x2BevelBorder(&rect,
						      lst->widget.scheme->shadow,
						      lst->widget.scheme->shadowDark,
						      lst->widget.scheme->highlight,
						      lst->widget.scheme->highlight);
	}
	
	lst->widget.drawState = DONE;
	lst->widget.drawFunc = NULL;
}

void _laListWidget_Paint(laListWidget* lst)
{
    if(lst->widget.scheme == NULL)
    {
        lst->widget.drawState = DONE;
        
        return;
    }

    if(lst->widget.drawState == NOT_STARTED)
    {
        lst->paintState.nextItem = 0;
        lst->paintState.y = 0;
        
        if(lst->widget.drawBackground == LA_TRUE)
        {
            lst->widget.drawState = DRAW_BACKGROUND;
            lst->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
        }
        else if(lst->items.size > 0)
        {
            lst->widget.drawState = DRAW_STRING;
            lst->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawString;
        }
        else if(lst->widget.borderType != LA_WIDGET_BORDER_NONE)
        {
            lst->widget.drawState = DRAW_BORDER;
	        lst->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
        }
        else
        {
            lst->widget.drawState = DONE;
	        lst->widget.drawFunc = NULL;
        }
    }
    
	lst->widget.drawFunc((laWidget*)lst);
}

#endif // LA_LIST_WIDGET_ENABLED && LA_SCROLLBAR_WIDGET_ENABLED