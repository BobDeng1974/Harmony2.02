#include "gfx/libaria/inc/libaria_widget_keypad.h"

#if LA_KEYPAD_WIDGET_ENABLED && LA_BUTTON_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_draw.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

enum
{
    NOT_STARTED = LA_WIDGET_DRAW_STATE_READY,
    DONE = LA_WIDGET_DRAW_STATE_DONE,
    DRAW_BORDER,
};

static void drawBackground(laKeyPadWidget* pad);
static void drawBorder(laKeyPadWidget* pad);

static void drawBackground(laKeyPadWidget* pad)
{
    GFX_Rect rect = pad->widget.rect;
	
	//printf("button painting\n");
	
	if(pad->widget.drawBackground == LA_TRUE)
	{
	    laUtils_RectToScreenSpace(pad->widget.parent, &rect);
	    
		GFX_Set(GFXF_DRAW_COLOR, pad->widget.scheme->base);
		GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
		GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
		GFX_DrawRect(pad->widget.rect.x,
					 pad->widget.rect.y,
					 pad->widget.rect.width,
					 pad->widget.rect.height);
	}
	
	if(pad->widget.borderType != LA_WIDGET_BORDER_NONE)
	{
	    pad->widget.drawState = DRAW_BORDER;
	    pad->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	}
	else
	{
	    pad->widget.drawState = DONE;
	    pad->widget.drawFunc = NULL;
	    
	    return;
	}
	
	if(laContext_GetActive()->preemptLevel < LA_PREEMPTION_LEVEL_2)
	    pad->widget.drawFunc((laWidget*)pad);
}

static void drawBorder(laKeyPadWidget* pad)
{
    GFX_Rect rect = pad->widget.rect;
    
    laUtils_RectToScreenSpace(pad->widget.parent, &rect);
    
    GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_FALSE);
    
    if(pad->widget.borderType == LA_WIDGET_BORDER_LINE)
	{
		laDraw_LineBorder(&rect, pad->widget.scheme->shadowDark);
	}
	else if(pad->widget.borderType == LA_WIDGET_BORDER_BEVEL)
	{
		laDraw_2x2BevelBorder(&pad->widget.rect,
						      pad->widget.scheme->highlightLight,
						      pad->widget.scheme->highlightLight,
						      pad->widget.scheme->shadow,
							  pad->widget.scheme->shadowDark);
	}
	
	pad->widget.drawState = DONE;
	pad->widget.drawFunc = NULL;
}

void _laKeyPadWidget_Paint(laKeyPadWidget* pad)
{
    laWidget* child;
    uint32_t i;
    
    // hack to sync child attributes to key pad style
	for(i = 0; i < pad->widget.children.size; i++)
	{
	    child = laList_Get(&pad->widget.children, i);
	    
	    child->borderType = pad->widget.borderType;
	    child->scheme = pad->widget.scheme;
	}
	
    if(pad->widget.scheme == NULL)
    {
        pad->widget.drawState = DONE;
        
        return;
    }
    
    if(pad->widget.drawState == NOT_STARTED)
    {
        if(pad->widget.drawBackground == LA_TRUE)
            pad->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBackground;
	    else if(pad->widget.borderType == LA_WIDGET_BORDER_NONE)
	        pad->widget.drawFunc = (laWidget_DrawFunction_FnPtr)&drawBorder;
	    else
	    {
	        pad->widget.drawState = DONE;
	        
	        return;
	    }
	}
	
	pad->widget.drawFunc((laWidget*)pad);
}

#endif // LA_WIDGET_KEYPAD_ENABLED && LA_WIDGET_BUTTON_ENABLED