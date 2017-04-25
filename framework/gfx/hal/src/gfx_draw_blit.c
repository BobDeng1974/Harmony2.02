#include "gfx/hal/inc/gfx_draw.h"

#if GFX_DRAW_PIPELINE_ENABLED

#include "gfx/hal/inc/gfx_color.h"
#include "gfx/hal/inc/gfx_context.h"
#include "gfx/hal/inc/gfx_layer.h"
#include "gfx/hal/inc/gfx_pixel_buffer.h"
#include "gfx/hal/inc/gfx_rect.h"

static GFX_Result cpuPixelBlit(const GFX_PixelBuffer* source,
                               const GFX_Rect* source_rect,
                               const GFX_Rect* source_clip_rect,
                               const GFX_PixelBuffer* dest,
                               const GFX_Point* dest_pnt,
                               GFX_DrawState* state)
{
    uint32_t row, row_max, col, col_max, index;
    GFX_Point draw_point;
#if GFX_LAYER_CLIPPING_ENABLED
    GFX_Rect dest_rect;
#endif
    GFX_Color color;
#if GFX_ALPHA_BLENDING_ENABLED
    GFX_Color destColor;
#endif
    GFX_Bool blendMode = GFX_FALSE;
    GFX_ColorMode sourceMode;
    GFX_Context* context = GFX_ActiveContext();
    
    // calculate minimums
    row_max = source_clip_rect->height;
    col_max = source_clip_rect->width;
    
#if GFX_LAYER_CLIPPING_ENABLED
    dest_rect.x = 0;
    dest_rect.y = 0;
    dest_rect.width = dest->size.width;
    dest_rect.height = dest->size.height;
#endif
    
    // check for blend mode
    sourceMode = source->mode;
       
    if(GFX_COLOR_MODE_IS_INDEX(source->mode) == GFX_TRUE)
        sourceMode = state->palette.mode;
        
#if GFX_ALPHA_BLENDING_ENABLED
    if(GFX_COLOR_MODE_IS_ALPHA(sourceMode) == GFX_TRUE)
       blendMode = GFX_TRUE;
#endif
    
    for(row = 0; row < row_max; row++)
    {
        draw_point.y = dest_pnt->y + row;
     
#if GFX_LAYER_CLIPPING_ENABLED   
        if(draw_point.y < 0 || draw_point.y >= dest_rect.height)
            continue;
#endif
    
        for(col = 0; col < col_max; col++)
        {
            // calculate dest offset
            draw_point.x = dest_pnt->x + col;
        
#if GFX_LAYER_CLIPPING_ENABLED
            if(draw_point.x < 0 || draw_point.x >= dest_rect.width)
                continue;
#endif
        
            // calculate source index
            index = (source_clip_rect->x + col) +
                    ((source_clip_rect->y + row) * source->size.width);

            // get color value/index
            color = GFX_PixelBufferGetIndex(source, index);
            
            // look up source color from buffer or palette
            color = GFX_ColorConvert(source->mode, sourceMode, color);
            
#if GFX_COLOR_MASKING_ENABLED
            // handle transparency if enabled
            if(state->maskEnable == GFX_TRUE && color == state->maskValue)
                continue;
#endif                
         
#if GFX_ALPHA_BLENDING_ENABLED
            // blend color if necessary
            if(blendMode == GFX_TRUE || state->alphaEnable == GFX_TRUE)
            {
                // get the destination color
                destColor = context->hal.pixelGet(dest, &draw_point);
                
                color = GFX_ColorConvert(sourceMode, GFX_COLOR_MODE_ARGB_8888, color);
                destColor = GFX_ColorConvert(dest->mode, GFX_COLOR_MODE_ARGB_8888, destColor);
                
                color = GFX_ColorBlendAlpha(color, 
                                            destColor,
                                            GFX_COLOR_MODE_ARGB_8888,
                                            state->alphaEnable == GFX_TRUE ? state->alphaValue : 255);
                                            
                color = GFX_ColorConvert(GFX_COLOR_MODE_ARGB_8888, dest->mode, color);
            }
            else
            {     
#endif                  
#if GFX_COLOR_CONVERSION_ENABLED   
                // convert color
                color = GFX_ColorConvert(sourceMode, dest->mode, color);
#endif
#if GFX_ALPHA_BLENDING_ENABLED
            }
#endif            
            
            // copy the pixel value
            context->hal.pixelSet(dest, &draw_point, color);
        }
    }
    
    return GFX_SUCCESS;
}

GFX_Result cpuDrawBlit(const GFX_PixelBuffer* source,
                       const GFX_Rect* source_rect,
                       const GFX_Point* dest_pnt,
                       GFX_DrawState* state)
{
    GFX_Layer* layer;
    GFX_PixelBuffer* dest;
    GFX_Rect source_clip_rect = {0};
#if GFX_BOUNDS_CLIPPING_ENABLED
    GFX_Rect draw_clip_rect;
#endif
    GFX_Point drawPoint;
    GFX_Result res;
    
    layer = GFX_ActiveContext()->layer.active;
    dest = &layer->buffers[layer->buffer_write_idx].pb;
    
    if(source == NULL || source_rect == NULL ||
       dest == NULL || dest_pnt == NULL)
        return GFX_FAILURE;
    
    drawPoint = *dest_pnt;

#if GFX_IMAGE_CLIPPING_ENABLED
    // clip image rect against buffer rect
    if(GFX_PixelBufferClipRect(source,
                               source_rect,
                               &source_clip_rect) == GFX_FAILURE)
        return GFX_FAILURE;
#else
    source_clip_rect = *source_rect;
#endif
        
#if GFX_BOUNDS_CLIPPING_ENABLED
    // clip image rect against draw clipping rect
    if(state->clipEnable == GFX_TRUE)
    {
        draw_clip_rect = source_clip_rect;
        
        draw_clip_rect.x += drawPoint.x;
        draw_clip_rect.y += drawPoint.y;
        
        if(GFX_RectIntersects(&draw_clip_rect, &state->clipRect) == GFX_TRUE)
        {
            GFX_RectClip(&draw_clip_rect, &state->clipRect, &source_clip_rect);
            
            source_clip_rect.x -= drawPoint.x;
            source_clip_rect.y -= drawPoint.y;
            
            drawPoint.x += source_clip_rect.x;
            drawPoint.y += source_clip_rect.y;
        }
        else
            return GFX_SUCCESS;
    }
#endif
    
    res = cpuPixelBlit(source,
                       source_rect,
                       &source_clip_rect,
                       dest,
                       &drawPoint,
                       state);
    
    return res;
}

#endif // GFX_DRAW_PIPELINE_ENABLED
