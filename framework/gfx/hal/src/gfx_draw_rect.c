#include "gfx/hal/inc/gfx_draw.h"

#if GFX_DRAW_PIPELINE_ENABLED

#include "gfx/hal/inc/gfx_context.h"
#include "gfx/hal/inc/gfx_draw_line.h"
#include "gfx/hal/inc/gfx_layer.h"
#include "gfx/hal/inc/gfx_math.h"

GFX_Result cpuDrawRect_Line(GFX_Rect* rect, GFX_DrawState* state)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Point pnt1, pnt2;
        
    // top line
    pnt1.x = rect->x;
    pnt1.y = rect->y;
    pnt2.x = rect->x + rect->width - 1;
    pnt2.y = rect->y;
    
    context->hal.drawLine[GFX_DRAW_LINE]
                         [GFX_ANTIALIAS_OFF]
                         (&pnt1, &pnt2, state);
    // bottom line
    pnt1.y = rect->y + rect->height - 1;
    pnt2.y = pnt1.y;                            
    context->hal.drawLine[GFX_DRAW_LINE]
                         [GFX_ANTIALIAS_OFF]
                         (&pnt1, &pnt2, state);
                
    // left line
    pnt1.x = rect->x;
    pnt1.y = rect->y;
    pnt2.x = rect->x;
    context->hal.drawLine[GFX_DRAW_LINE]
                         [GFX_ANTIALIAS_OFF]
                         (&pnt1, &pnt2, state);
    
    // right line
    pnt1.x = rect->x + rect->width - 1;
    pnt2.x = pnt1.x;                            
    context->hal.drawLine[GFX_DRAW_LINE]
                         [GFX_ANTIALIAS_OFF]
                         (&pnt1, &pnt2, state);
    
    return GFX_SUCCESS;
}

GFX_Result cpuDrawRect_Fill(GFX_Rect* rect, GFX_DrawState* state)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Layer* layer = context->layer.active;
    GFX_Rect clipRect;
    int32_t row, row_max, col, col_max;
    GFX_Point pnt;
    
    if(state->clipEnable == GFX_TRUE)
    {
        if(GFX_RectIntersects(rect, &state->clipRect) == GFX_FALSE)
            return GFX_SUCCESS;
            
        GFX_RectClip(rect, &state->clipRect, &clipRect);
    }
    else
        clipRect = *rect;
    
    if(GFX_PixelBufferClipRect(&layer->buffers[layer->buffer_write_idx].pb,
                               rect,
                               &clipRect) == GFX_FAILURE)
    {
        return GFX_FAILURE;
    }
    
    // calculate minimums
    row_max = rect->height;
    col_max = rect->width;
    
    for(row = 0; row < row_max; row++)
    {
        pnt.y = rect->y + row;
        
        for(col = 0; col < col_max; col++)
        {
            pnt.x = rect->x + col;
            
            // set dest pixel
            cpuDrawPixel_Unsafe(&pnt, state);
        }
    }
    
    return GFX_SUCCESS;
}

GFX_Result cpuDrawRect_Gradient_LeftRight(GFX_Rect* rect, GFX_DrawState* state)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Rect clipRect;
    GFX_Point pnt1, pnt2;
    int32_t col, val;
    uint32_t percent;
    GFX_Color oldColor = state->color;
    
    if(state->clipEnable == GFX_TRUE)
    {
        if(GFX_RectIntersects(rect, &state->clipRect) == GFX_FALSE)
            return GFX_SUCCESS;
            
        GFX_RectClip(rect, &state->clipRect, &clipRect);
    }
    else
        clipRect = *rect;
    
    pnt1.x = clipRect.x;
    pnt1.y = clipRect.y;
    pnt2.x = clipRect.x + clipRect.width;
    pnt2.y = clipRect.y + clipRect.height;
    
    for(col = clipRect.x; col < clipRect.x + clipRect.width; col++)
    {
        val = col - clipRect.x;
        
        percent = GFX_PercentWholeRounded(val, clipRect.width);
        
        state->color = GFX_ColorLerp(state->gradient.c0, state->gradient.c1, percent, context->colorMode);
        
        pnt1.x = col;
        pnt2.x = col;                            
        context->hal.drawLine[GFX_DRAW_LINE]
                             [GFX_ANTIALIAS_OFF]
                             (&pnt1, &pnt2, state);
    }
    
    state->color = oldColor;

    return GFX_SUCCESS;
}

GFX_Result cpuDrawRect_Gradient_TopBottom(GFX_Rect* rect, GFX_DrawState* state)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Rect clipRect;
    GFX_Point pnt1, pnt2;
    int32_t row, val;
    uint32_t percent;
    GFX_Color oldColor = state->color;
    
    if(state->clipEnable == GFX_TRUE)
    {
        if(GFX_RectIntersects(rect, &state->clipRect) == GFX_FALSE)
            return GFX_SUCCESS;
            
        GFX_RectClip(rect, &state->clipRect, &clipRect);
    }
    else
        clipRect = *rect;
    
    pnt1.x = clipRect.x;
    pnt1.y = clipRect.y;
    pnt2.x = clipRect.x + clipRect.width;
    pnt2.y = clipRect.y;
    
    for(row = clipRect.y; row < clipRect.y + clipRect.height; row++)
    {
        val = row - clipRect.y;
        
        percent = GFX_PercentWholeRounded(val, clipRect.height);
        
        state->color = GFX_ColorLerp(state->gradient.c0,
                                     state->gradient.c1,
                                     percent,
                                     context->colorMode);
        
        pnt1.y = row;
        pnt2.y = row;                            
        context->hal.drawLine[GFX_DRAW_LINE]
                             [GFX_ANTIALIAS_OFF]
                             (&pnt1, &pnt2, state);
    }
    
    state->color = oldColor;

    return GFX_SUCCESS;
}
                          
GFX_Result cpuDrawRect_Gradient_Quad(GFX_Rect* rect, GFX_DrawState* state)
{
    return GFX_UNSUPPORTED;
}

GFX_Result cpuDrawRect_Line_AA(GFX_Rect* rect, GFX_DrawState* state)
{   
    return GFX_UNSUPPORTED;
}

GFX_Result cpuDrawRect_Fill_AA(GFX_Rect* rect, GFX_DrawState* state)
{
    return GFX_UNSUPPORTED;
}

GFX_Result cpuDrawRect_Gradient_Bi_AA(GFX_Rect* rect, GFX_DrawState* state)
{
    return GFX_UNSUPPORTED;
}
                          
GFX_Result cpuDrawRect_Gradient_Quad_AA(GFX_Rect* rect, GFX_DrawState* state)
{
    return GFX_UNSUPPORTED;
}

#endif // GFX_DRAW_PIPELINE_ENABLED