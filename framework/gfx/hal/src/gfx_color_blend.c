#include "gfx/hal/inc/gfx_color.h"
#include "gfx/hal/inc/gfx_math.h"
#include "gfx/hal/inc/gfx_util.h"

#if GFX_DRAW_PIPELINE_ENABLED && GFX_ALPHA_BLENDING_ENABLED

#define BLEND_MODE_COUNT 3

typedef GFX_Color (*color_blend_fn_ptr)(GFX_Color, GFX_Color, uint32_t alpha);
typedef GFX_Color (*color_alpha_set_fn_ptr)(GFX_Color, uint32_t);

/* color blend function definitions */
static GFX_Color blend_none(GFX_Color fore, GFX_Color back, uint32_t alpha);
static GFX_Color blend_rgb565(GFX_Color fore, GFX_Color back, uint32_t alpha);
static GFX_Color blend_rgba5551(GFX_Color fore, GFX_Color back, uint32_t alpha);
static GFX_Color blend_rgba8888(GFX_Color fore, GFX_Color back, uint32_t alpha);
static GFX_Color blend_argb8888(GFX_Color fore, GFX_Color back, uint32_t alpha);

color_blend_fn_ptr color_blend_table[GFX_COLOR_MODE_COUNT] =
{
    &blend_none,     /* GFX_COLOR_MODE_GS_8 */ 
    &blend_none,     /* GFX_COLOR_MODE_RGB_332 */ 
    &blend_rgb565,   /* GFX_COLOR_MODE_RGB_565 */ 
    &blend_rgba5551, /* GFX_COLOR_MODE_RGBA_5551 */ 
    &blend_none,     /* GFX_COLOR_MODE_RGB_888 */ 
    &blend_rgba8888, /* GFX_COLOR_MODE_RGBA_8888 */ 
    &blend_argb8888, /* GFX_COLOR_MODE_ARGB_8888 */ 
    &blend_none,     /* GFX_COLOR_MODE_YUV */ 
};

/* color blend function definitions */
static GFX_Color alpha_none(GFX_Color clr, uint32_t alpha);
static GFX_Color alpha_rgba5551(GFX_Color clr, uint32_t alpha);
static GFX_Color alpha_rgba8888(GFX_Color clr, uint32_t alpha);
static GFX_Color alpha_argb8888(GFX_Color clr, uint32_t alpha);

color_alpha_set_fn_ptr alpha_set_table[GFX_COLOR_MODE_COUNT] =
{
    &alpha_none,     /* GFX_COLOR_MODE_GS_8 */ 
    &alpha_none,     /* GFX_COLOR_MODE_RGB_332 */ 
    &alpha_none,     /* GFX_COLOR_MODE_RGB_565 */ 
    &alpha_rgba5551, /* GFX_COLOR_MODE_RGBA_5551 */ 
    &alpha_none,     /* GFX_COLOR_MODE_RGB_888 */ 
    &alpha_rgba8888, /* GFX_COLOR_MODE_RGBA_8888 */ 
    &alpha_argb8888, /* GFX_COLOR_MODE_ARGB_8888 */ 
    &alpha_none,     /* GFX_COLOR_MODE_YUV */ 
};

/*static float calculateAlphaPercentage(uint32_t alpha)
{
	float per = (float)(alpha);
    
    if(per < 1.0f)
        per += 0.001f;
    else
        per /= 255.0f;

	return per;
}*/

static uint8_t calculateBlendColor(uint8_t lclr,
								   uint32_t lper,
								   uint8_t rclr,
								   uint32_t rper,
								   uint8_t max)
{
	uint8_t res = 0;

    /*lper *= (float)lclr;    // translate to color space
	lper += 0.5f;           // round
    lclr = (uint8_t)(lper); // truncate

	rper *= (float)rclr;    // translate to color space
	rper += 0.5f;           // round
    rclr = (uint8_t)(rper); // truncate
    
    res = lclr + rclr; // sum
    
    if(res > max) // clamp
        res = max;*/

	lper *= lclr;        // translate to color space
	lper += 50;          // round
	lclr = lper / 10000; // truncate

	rper *= rclr;        // translate to color space
	rper += 50;          // round
	rclr = rper / 10000; // truncate
	
	/*if(lclr != 0)
	    lclr = GFX_PercentWholeRounded(lper, lclr);
	else
	    lclr = 0;
	    
	if(rclr != 0)
	    rclr = GFX_PercentWholeRounded(rper, rclr);
    else
        rclr = 0;*/
        
	res = lclr + rclr;   // sum

	if(res > max)        // clamp
		res = max;

    return res;
}

static GFX_Color blend_none(GFX_Color fore, GFX_Color back, uint32_t alpha)
{
    back = back;
    
    return fore;
}

static GFX_Color blend_rgb565(GFX_Color c1, GFX_Color c2, uint32_t alpha)
{
    GFX_Color result;
	uint32_t ia1, ia2;

	result = 0;

	if(alpha == 255)
		return c1;

	if(alpha == 0)
		return c2;

	// calculate result alpha
	ia1 = GFX_Percent(alpha, 255);
	ia2 = 10000 - ia1;

    // red channel
	result |= calculateBlendColor((c1 & RGB_565_RED_MASK) >> 11,
		                          ia1,
		                          (c2 & RGB_565_RED_MASK) >> 11,
								  ia2,
								  31) << 11;

    // green channel
	result |= calculateBlendColor((c1 & RGB_565_GREEN_MASK) >> 5,
		                          ia1,
		                          (c2 & RGB_565_GREEN_MASK) >> 5,
								  ia2,
								  63) << 5;

    // blue channel
	result |= calculateBlendColor((c1 & RGB_565_BLUE_MASK),
		                          ia1,
		                          (c2 & RGB_565_BLUE_MASK),
								  ia2,
								  31);

	return result;
}

static GFX_Color blend_rgba5551(GFX_Color fore, GFX_Color back, uint32_t alpha)
{
    if((fore & 0x0001) > 0)
        return fore;
        
    return back;
}

static GFX_Color blend_rgba8888(GFX_Color c1, GFX_Color c2, uint32_t alpha)
{
	GFX_Color result;
	uint32_t ia1, ia2, iag;
	uint32_t c1a, c2a;

	result = 0;

	/*if(((c1 & 0xFF) == 255 && alpha == 255) && (c2 & 0xFF) == 255)
		return c1;

	if(((c1 & 0xFF) == 0 || alpha == 0) && (c2 & 0xFF) == 0)
		return 0;
		
    if((c1 & 0xFF) == 0)
        return c2;*/
        
    c1a = c1 & RGBA_8888_ALPHA_MASK;
    ia1 = GFX_Percent(c1a, 255);
    
    // apply global alpha value
    if(alpha != 255 && ia1 != 0)
    {
        //c1a += alpha;
        
        iag = GFX_PercentWholeRounded(alpha, 255);
        
        ia1 = GFX_PercentOf(ia1, iag);
    }
    
    c2a = c2 & RGBA_8888_ALPHA_MASK;

	// calculate result alpha
	
	ia2 = GFX_Percent(c2a, 255);
	ia2 = 10000 - ia1;
	
	

    // red channel
	result |= calculateBlendColor((c1 & RGBA_8888_RED_MASK) >> 24,
		                          ia1,
		                          (c2 & RGBA_8888_RED_MASK) >> 24,
								  ia2,
								  255) << 24;

    // green channel
	result |= calculateBlendColor((c1 & RGBA_8888_GREEN_MASK) >> 16,
		                          ia1,
		                          (c2 & RGBA_8888_GREEN_MASK) >> 16,
								  ia2,
								  255) << 16;

    // blue channel
	result |= calculateBlendColor((c1 & RGBA_8888_BLUE_MASK) >> 8,
		                          ia1,
		                          (c2 & RGBA_8888_BLUE_MASK) >> 8,
								  ia2,
								  255) << 8;

	return result;
}

static GFX_Color blend_argb8888(GFX_Color fore, GFX_Color back, uint32_t alpha)
{
    GFX_Color res;
    
    fore = GFX_ColorConvert(GFX_COLOR_MODE_ARGB_8888, GFX_COLOR_MODE_RGBA_8888, fore);
    back = GFX_ColorConvert(GFX_COLOR_MODE_ARGB_8888, GFX_COLOR_MODE_RGBA_8888, back);
    
    res = blend_rgba8888(fore, back, alpha);
    
    res = GFX_ColorConvert(GFX_COLOR_MODE_RGBA_8888, GFX_COLOR_MODE_ARGB_8888, res);
    
    return res;
}

static GFX_Color alpha_none(GFX_Color clr, uint32_t alpha)
{
    alpha = alpha;
    
    return clr;
}

static GFX_Color alpha_rgba5551(GFX_Color clr, uint32_t alpha)
{
    return alpha > 0 ? clr : clr | 0x1;
}

static GFX_Color alpha_rgba8888(GFX_Color clr, uint32_t alpha)
{
    return ((clr & ~0xFF) | alpha);
}

static GFX_Color alpha_argb8888(GFX_Color clr, uint32_t alpha)
{
    return clr | ((alpha & 0xFF) << 24);
}

GFX_Color last;

GFX_Color GFX_ColorBlendAlpha(GFX_Color fore,
                              GFX_Color back,
                              GFX_ColorMode mode,
							  uint32_t alpha)
{
	GFX_Color res = color_blend_table[mode](fore, back, alpha);

	if(last != res)
    {                        
        last = res;
		//printf("%#010x %#010x %#010x %#010x\n", fore, back, res, GFX_ColorConvert(mode, GFX_COLOR_MODE_RGBA_8888, res));
    }
    
	return res;
}

#endif // GFX_DRAW_PIPELINE_ENABLED && GFX_ALPHA_BLENDING_ENABLED