#include "gfx/hal/inc/gfx_draw.h"

#if GFX_DRAW_PIPELINE_ENABLED

#include <math.h>

#include "gfx/hal/inc/gfx_context.h"
#include "gfx/hal/inc/gfx_layer.h"
#include "gfx/hal/inc/gfx_rect.h"
#include "gfx/hal/inc/gfx_util.h"

GFX_Result cpuDrawCircle_Line(GFX_Point* pt,
                              int32_t r,
                              GFX_DrawState* state)
{
    int x = -r, y = 0, err = 2-2*r;
    int xm = pt->x;
    int ym = pt->y;
    
    GFX_Context* context = GFX_ActiveContext();
    GFX_Point dp;
    
    do
    {
        dp.x = xm-x;
        dp.y = ym+y;
        context->hal.drawPixel[GFX_ANTIALIAS_OFF](&dp, state);        
        dp.x = xm-y;
        dp.y = ym-x;
        context->hal.drawPixel[GFX_ANTIALIAS_OFF](&dp, state);        
        dp.x = xm+x;
        dp.y = ym-y;
        context->hal.drawPixel[GFX_ANTIALIAS_OFF](&dp, state);
        
        dp.x = xm+y;
        dp.y = ym+x;
        context->hal.drawPixel[GFX_ANTIALIAS_OFF](&dp, state);
        r = err;
        if (r <= y) err += ++y*2+1;           /* e_xy+e_y < 0 */
        if (r > x || err > y) err += ++x*2+1; /* e_xy+e_x > 0 or no 2nd y-step */
    } while (x < 0);
    
    return GFX_SUCCESS;
}

#endif // GFX_DRAW_PIPELINE_ENABLED