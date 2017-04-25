#include "gfx/hal/inc/gfx_color.h"

LIB_EXPORT GFX_ColorModeInfo GFX_ColorInfo[] =
{
    
    {1,8,  GFX_BPP8,  {0x0,0x0,0x0,0x0}},                              // GFX_COLOR_MODE_GS_8
    {1,8,  GFX_BPP8,  {0xE0,0x1C,0x3,0x0}},                            // GFX_COLOR_MODE_RGB_332
    {2,16, GFX_BPP16, {0xF800,0x07E0,0x001F,0x0}},                     // GFX_COLOR_MODE_RGB_565
    {2,16, GFX_BPP16, {0xF800,0x07C0,0x003E,0x0001}},                  // GFX_COLOR_MODE_RGBA_5551
    {3,24, GFX_BPP24, {0xFF0000,0x00FF00,0x0000FF,0x0}},               // GFX_COLOR_MODE_RGB_888
    {4,32, GFX_BPP32, {0xFF000000,0x00FF0000,0x0000FF00,0x000000FF}},  // GFX_COLOR_MODE_RGBA_8888
    {4,32, GFX_BPP32, {0x00FF0000,0x0000FF00,0x000000FF,0xFF000000}},  // GFX_COLOR_MODE_ARGB_8888
    {4,32, GFX_BPP32, {0x0,0x0,0x0,0x0}},                              // GFX_COLOR_MODE_YUV
    {1,1,  GFX_BPP1,  {0x0,0x0,0x0,0x0}},                              // GFX_COLOR_MODE_INDEX_1
    {1,4,  GFX_BPP4,  {0x0,0x0,0x0,0x0}},                              // GFX_COLOR_MODE_INDEX_4
    {1,8,  GFX_BPP8,  {0x0,0x0,0x0,0x0}},                              // GFX_COLOR_MODE_INDEX_8
};

GFX_ColorModeInfo GFX_ColorModeInfoGet(GFX_ColorMode mode)
{
    return GFX_ColorInfo[mode];
}

uint32_t GFX_ColorChannelRed(GFX_Color clr, GFX_ColorMode mode)
{
    return clr & GFX_ColorInfo[mode].mask.red;
}

uint32_t GFX_ColorChannelGreen(GFX_Color clr, GFX_ColorMode mode)
{
    return clr & GFX_ColorInfo[mode].mask.red;
}

uint32_t GFX_ColorChannelBlue(GFX_Color clr, GFX_ColorMode mode)
{
    return clr & GFX_ColorInfo[mode].mask.red;
}

uint32_t GFX_ColorChannelAlpha(GFX_Color clr, GFX_ColorMode mode)
{
    if(mode == GFX_COLOR_MODE_RGBA_5551 ||
       mode == GFX_COLOR_MODE_RGBA_8888 ||
       mode == GFX_COLOR_MODE_ARGB_8888)
        return clr & GFX_ColorInfo[mode].mask.alpha;
    
    return 0xFF;
}