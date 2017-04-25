#include "gfx/libaria/inc/libaria_context.h"

#include "gfx/hal/gfx.h"

#include "gfx/libaria/inc/libaria_layer.h"
#include "gfx/libaria/inc/libaria_screen.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

void _laContext_PaintWidget(laWidget* widget)
{
	laWidget* child;
	laListNode* node;
	GFX_Rect clipRect, childRect;
	laBool alphaEnable;

	// skip any child that isn't dirty or that does not have a dirty descendent
	if(widget->dirtyState == LA_WIDGET_DIRTY_STATE_CLEAN)
		return;
		
    // if widget is completely transparent just mark clean and return
	if(widget->alphaEnabled == GFX_TRUE && widget->alphaAmount == 0)
	{
	    _laWidget_ValidateChildren(widget);
	    
	    return;
	}
	
	// paint this widget and clear dirty flag
	if(widget->dirtyState == LA_WIDGET_DIRTY_STATE_DIRTY)
	{
	    // manage alpha blending
	    alphaEnable = laWidget_GetCumulativeAlphaEnable(widget);
	    GFX_Set(GFXF_DRAW_ALPHA_ENABLE, alphaEnable);
	    
	    if(alphaEnable == LA_TRUE)
	        GFX_Set(GFXF_DRAW_ALPHA_VALUE, laWidget_GetCumulativeAlphaAmount(widget));
	    
	    // turn on clipping
	    clipRect = widget->rect;
	    
	    if(widget->parent != NULL)
	    {
	        clipRect = widget->rect;
	        
	        laUtils_ClipRectToParent(widget->parent, &clipRect);
	    }
	    else
	        clipRect = widget->rect;
	        
	    laUtils_RectToScreenSpace(widget->parent, &clipRect);
	    
	    GFX_Set(GFXF_DRAW_CLIP_RECT, &clipRect);
	    
	    // attempt to cull via occlusion test
	    if(laUtils_OcclusionCullTest(widget) == LA_FALSE)
	    {
		    widget->paint(widget);
		    
		    //printf("painting widget - %i, %i\n", widget->type, widget->id);
		    
		    if(widget->drawState != LA_WIDGET_DRAW_STATE_DONE)
			    return;

		    widget->drawState = LA_WIDGET_DRAW_STATE_READY;
		}
        /*else
        {
            //printf("occluded widget - %i, %i\n", widget->type, widget->id);
            
            _laWidget_ValidateChildren(widget);
		}*/
	}
	
	if(laContext_GetActive()->preemptLevel >= LA_PREEMPTION_LEVEL_1)
	    return;
	
	node = widget->children.head;
	
	widget->dirtyState = LA_WIDGET_DIRTY_STATE_CLEAN;
	
	if(node == NULL)
	    return;
	
	// see if children exist and need to be drawn
	while(node != NULL)
	{
		child = (laWidget*)node->val;
		
		childRect = child->rect;
		childRect.x += widget->rect.x;
		childRect.y += widget->rect.y;

		// pre-cull based on visibility and rectangle intersection
		// anything not visible or completely outside parent can be ignored.
		if(child->visible == LA_TRUE &&
		   child->dirtyState != LA_WIDGET_DIRTY_STATE_CLEAN &&
		   GFX_RectIntersects(&widget->rect, &childRect) == LA_TRUE)
		{
			_laContext_PaintWidget(child);
		}
		else
		{		    
			// clear all dirty flags for this child and its descendents
			_laWidget_ValidateChildren(child);
		}

		node = node->next;
	}
	
	// check all children for dirty flags
	node = widget->children.head;
	
	//printf("%u clean\n", widget->id);
	
	while(node != NULL)
	{
		child = (laWidget*)node->val;

		if(child->dirtyState != LA_WIDGET_DIRTY_STATE_CLEAN)
		{
			widget->dirtyState = LA_WIDGET_DIRTY_STATE_CHILD;

			break;
		}

		node = node->next;
	}
}

void _laContext_Paint()
{
	laScreen* activeScreen;
	laLayer* layer;
	GFX_Rect screenRect;
	int32_t i;

	activeScreen = laContext_GetActive()->activeScreen;
    
    if(activeScreen == NULL)
        return;

	screenRect = laContext_GetScreenRect();

	
			
	GFX_Set(GFXF_DRAW_CLIP_ENABLE, GFX_TRUE);
	GFX_Set(GFXF_DRAW_BLEND_MODE, GFX_BLEND_NONE);

	// iterate over all qualifying layers and paint
	for(i = 0; i < LA_MAX_LAYERS; i++)
	{
		layer = activeScreen->layers[i];

		if(layer == NULL ||
		   layer->widget.enabled == LA_FALSE ||
		   layer->widget.visible == LA_FALSE ||
		   (layer->widget.alphaEnabled == LA_TRUE && layer->widget.alphaAmount == 0) ||
		   GFX_RectIntersects(&screenRect, &layer->widget.rect) == LA_FALSE ||
		   layer->widget.dirtyState == LA_WIDGET_DIRTY_STATE_CLEAN)
			continue;
        
        //BSP_LED_2Toggle();
        
        // set active driver layer
	    GFX_Set(GFXF_LAYER_ACTIVE, i);
	    
        // notify the draw layer that the library wants to start drawing to the active layer
	    if(GFX_Begin() != GFX_SUCCESS)
		    return;
			
		// paint root node
		_laContext_PaintWidget((laWidget*)layer);
		
		 // notify the draw layer that drawing is over
	    GFX_End();
	    
		// indicate swap if layer is clean
		if(layer->widget.dirtyState == LA_WIDGET_DIRTY_STATE_CLEAN)
		{
			GFX_Set(GFXF_LAYER_SWAP, GFX_TRUE);
			
			//printf("request layer %u swap\n", i);
        }
	}
	
	GFX_Set(GFXF_DRAW_CLIP_ENABLE, GFX_FALSE);
}