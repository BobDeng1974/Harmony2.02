#include "gfx/hal/inc/gfx_draw_pixel.h"

#if GFX_DRAW_PIPELINE_ENABLED

#include "gfx/hal/inc/gfx_color.h"
#include "gfx/hal/inc/gfx_context.h"
#include "gfx/hal/inc/gfx_layer.h"
#include "gfx/hal/inc/gfx_pixel_buffer.h"
#include "gfx/hal/inc/gfx_rect.h"
#include "gfx/hal/inc/gfx_util.h"

GFX_Result cpuDrawPixel(GFX_Point* pnt, GFX_DrawState* state)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Layer* layer = context->layer.active;
    GFX_Point tf_pnt = *pnt;
    
#if GFX_LAYER_CLIPPING_ENABLED
    if(GFX_RectContainsPoint(&layer->rect.local, &tf_pnt) == GFX_FALSE)
        return GFX_FAILURE;
#endif

#if GFX_ORIENTATION_ENABLED
    // reorient point to layer
    GFX_UtilOrientPoint(&tf_pnt, &layer->rect.local, context->orientation, GFX_FALSE);
#endif
    
    return cpuDrawPixel_Unsafe(&tf_pnt, state);
}

GFX_Result cpuDrawPixel_Unsafe(GFX_Point* pnt, GFX_DrawState* state)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Layer* layer = context->layer.active;
    GFX_PixelBuffer* buffer;
#if GFX_ALPHA_BLENDING_ENABLED
    GFX_Color dest;
#endif
    GFX_Color result;
    
    buffer = &layer->buffers[layer->buffer_write_idx].pb;
    result = state->color;
    
#if GFX_BOUNDS_CLIPPING_ENABLED
    // clip point
    if((state->clipEnable == GFX_TRUE) && 
        GFX_RectContainsPoint(&state->clipRect, pnt) == GFX_FALSE)
        return GFX_FAILURE;
#endif
    
#if GFX_COLOR_MASKING_ENABLED
    // mask color
    if(state->maskEnable == GFX_TRUE && result == state->maskValue)
       return GFX_SUCCESS;
#endif
    
#if GFX_ALPHA_BLENDING_ENABLED
    // blend color
    if(state->alphaEnable == GFX_TRUE ||
	   context->colorMode == GFX_COLOR_MODE_RGBA_5551 ||
       context->colorMode == GFX_COLOR_MODE_RGBA_8888 ||
       context->colorMode == GFX_COLOR_MODE_ARGB_8888)
    {
        dest = context->hal.pixelGet(buffer, pnt);
        
		result = GFX_ColorBlendAlpha(result, dest, context->colorMode, state->alphaValue);
    }
#endif
    
    // write color
    return context->hal.pixelSet(buffer, pnt, result);
}

#endif // GFX_DRAW_PIPELINE_ENABLED