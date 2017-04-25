#include "gfx/hal/inc/gfx_rect.h"

#if GFX_DRAW_PIPELINE_ENABLED

GFX_Bool GFX_RectContainsPoint(const GFX_Rect* rect, const GFX_Point* point)
{
    if(point->x < rect->x || point->x >= rect->x + rect->width ||
       point->y < rect->y || point->y >= rect->y + rect->height)
        return GFX_FALSE;
        
    return GFX_TRUE;
}

GFX_Bool GFX_RectContainsRect(const GFX_Rect* l_rect, const GFX_Rect* r_rect)
{
    if (l_rect->x <= r_rect->x && 
        r_rect->x  + r_rect->width - 1 <= l_rect->x + l_rect->width - 1 &&
        l_rect->y <= r_rect->y && 
        r_rect->y  + r_rect->height - 1 <= l_rect->y + l_rect->height - 1)
        return GFX_TRUE;
    
    return GFX_FALSE;
}

GFX_Bool GFX_RectIntersects(const GFX_Rect* l_rect, const GFX_Rect* r_rect)
{
    if (l_rect->x <= r_rect->x + r_rect->width - 1 &&
        r_rect->x <= l_rect->x + l_rect->width - 1 &&
        l_rect->y <= r_rect->y + r_rect->height - 1)
        return r_rect->y <= l_rect->y + l_rect->height - 1;
    
    return GFX_FALSE;
}

void GFX_RectClip(const GFX_Rect* l_rect,
                  const GFX_Rect* r_rect, 
                  GFX_Rect* result)
{
    GFX_Rect res;

    res = *l_rect;

    if(res.x < r_rect->x)
    {
        res.x = r_rect->x;
        res.width -= res.x - l_rect->x;
    }
    
    if(res.x + res.width - 1 > r_rect->x + r_rect->width - 1)
        res.width = r_rect->x + r_rect->width - res.x;
        
    if(res.y < r_rect->y)
    {
        res.y = r_rect->y;
        res.height -= res.y - l_rect->y;
    }
    
    if(res.y + res.height > r_rect->y + r_rect->height)
        res.height = r_rect->y + r_rect->height - res.y;
        
    *result = res;
}

#endif // GFX_DRAW_PIPELINE_ENABLED