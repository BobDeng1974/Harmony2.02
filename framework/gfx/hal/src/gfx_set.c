#include "gfx/hal/inc/gfx_interface.h"

#include "gfx/hal/inc/gfx_context.h"
#include "gfx/hal/inc/gfx_display.h"
#include "gfx/hal/inc/gfx_driver_interface.h"

GFX_Result set_unimplemented(va_list args)
{
    args = args;
    
    return GFX_FAILURE;
}

GFX_Result set_brightness(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    uint32_t val = va_arg(args, uint32_t);

    ASSERT(context != NULL);
            
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif

    return context->hal.brightnessSet(val);
}

GFX_Result set_vsyncCallback(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_SyncCallback_FnPtr ptr = va_arg(args, GFX_SyncCallback_FnPtr);
    
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif                                                               

    return context->hal.vsyncCallbackSet(ptr);
}

GFX_Result set_hsyncCallback(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_SyncCallback_FnPtr ptr = va_arg(args, GFX_SyncCallback_FnPtr);
    
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif                                                               

    return context->hal.hsyncCallbackSet(ptr);
}

GFX_Result set_orientation(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_Orientation ori = va_arg(args, GFX_Orientation);
    
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif                                                               

    return context->hal.orientationSet(ori);
}

GFX_Result set_mirroring(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_Bool mirr = va_arg(args, GFX_Bool);
    
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif                                                               

    return context->hal.mirroringSet(mirr);
}

GFX_Result set_colorMode(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_ColorMode mode = va_arg(args, GFX_ColorMode);
            
    ASSERT(context != NULL);
            
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif
            
    return context->hal.colorModeSet(mode);
}

GFX_Result set_layerActive(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    uint32_t idx = va_arg(args, uint32_t);

    ASSERT(context != NULL && idx < context->layer.count);
            
#ifdef GFX_DEBUG
    if(context == NULL || idx >= context->layer.count)
        return GFX_FAILURE;
#endif

    return context->hal.layerActiveSet(idx);
}

GFX_Result set_layerEnabled(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_Bool enabled = va_arg(args, GFX_Bool);

    ASSERT(context != NULL);
            
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif

    return context->hal.layerEnabledSet(enabled);
}

GFX_Result set_layerVisible(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_Bool visible = va_arg(args, GFX_Bool);

    ASSERT(context != NULL);
            
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif

    return context->hal.layerVisibleSet(visible);
}

GFX_Result set_layerVsync(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_Bool vsync = va_arg(args, GFX_Bool);
    
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif                                                               

    return context->hal.layerVsyncSet(vsync);
}

GFX_Result set_layerSwap(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_Bool swap = va_arg(args, GFX_Bool);

    ASSERT(context != NULL);
            
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif

    return context->hal.layerSwapSet(swap);
}

GFX_Result set_layerPosition(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    int32_t x = va_arg(args, int32_t);
    int32_t y = va_arg(args, int32_t);
            
    ASSERT(context != NULL);
            
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif
            
    return context->hal.layerPositionSet(x, y);
}

GFX_Result set_layerSize(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    uint32_t width = va_arg(args, uint32_t);
    uint32_t height = va_arg(args, uint32_t);
            
    ASSERT(context != NULL);
            
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif
            
    return context->hal.layerSizeSet(width, height);
}

GFX_Result set_layerAlphaEnable(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_Bool enable = va_arg(args, GFX_Bool);
    
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif   
    
    return context->hal.layerAlphaEnableSet(enable);
}

GFX_Result set_layerAlphaAmount(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    uint32_t amount = va_arg(args, uint32_t);
    
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif   
    
    return context->hal.layerAlphaAmountSet(amount);
}

GFX_Result set_layerMaskEnable(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_Bool enable = va_arg(args, GFX_Bool);
    
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif   
    
    return context->hal.layerMaskEnableSet(enable);
}

GFX_Result set_layerMaskColor(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_Color color = va_arg(args, GFX_Color);
    
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif                                                               

    return context->hal.layerMaskColorSet(color);
}

GFX_Result set_layerBufferCount(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    uint32_t count = va_arg(args, uint32_t);
    
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif
    
    return context->hal.layerBufferCountSet(count);
}

GFX_Result set_layerBufferAddress(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    uint32_t idx = va_arg(args, uint32_t);
    GFX_Buffer address = va_arg(args, GFX_Buffer);
        
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif   
    
    return context->hal.layerBufferAddressSet(idx, address);
}

GFX_Result set_layerBufferCoherent(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    uint32_t idx = va_arg(args, uint32_t);
    GFX_Bool coherent = va_arg(args, GFX_Bool);
        
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif   
    
    return context->hal.layerBufferCoherentSet(idx, coherent);
}

GFX_Result set_layerBufferAllocated(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    uint32_t idx = va_arg(args, uint32_t);
    
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif  
    
    return context->hal.layerBufferAllocate(idx);
}

GFX_Result set_layerBufferFree(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    uint32_t idx = va_arg(args, uint32_t);
    
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif  
    
    return context->hal.layerBufferFree(idx);
}

#if GFX_DRAW_PIPELINE_ENABLED

GFX_Result set_drawMode(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_DrawMode mode = va_arg(args, GFX_DrawMode);
    
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif                                                               

    return context->hal.drawModeSet(mode);
}

GFX_Result set_drawColor(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_Color color = va_arg(args, GFX_Color);
    
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif                                                               

    return context->hal.drawColorSet(color);
}

GFX_Result set_drawGradientColor(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_Color tl = va_arg(args, GFX_Color);
    GFX_Color tr = va_arg(args, GFX_Color);
    GFX_Color bl = va_arg(args, GFX_Color);
    GFX_Color br = va_arg(args, GFX_Color);
    
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif                                                               

    return context->hal.drawGradientColorSet(tl, tr, bl, br);
}

GFX_Result set_drawPalette(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_PixelBuffer* pb = va_arg(args, GFX_PixelBuffer*);
       
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif                                                               

    return context->hal.drawPaletteSet(pb);
}

GFX_Result set_drawBlendMode(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_BlendMode mode = va_arg(args, GFX_BlendMode);
            
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif 
    
    return context->hal.drawBlendModeSet(mode);
}

GFX_Result set_drawAlphaEnable(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_Bool enable = va_arg(args, GFX_Bool);
            
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif 
    
    return context->hal.drawAlphaEnableSet(enable);
}

GFX_Result set_drawAlphaValue(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    uint32_t alpha = va_arg(args, uint32_t);
            
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif 
    
    return context->hal.drawAlphaValueSet(alpha);
}

GFX_Result set_drawMaskEnable(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_Bool enable = va_arg(args, GFX_Bool);
            
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif 
    
    return context->hal.drawMaskEnableSet(enable);
}

GFX_Result set_drawMaskValue(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    uint32_t mask = va_arg(args, uint32_t);
            
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif 
    
    return context->hal.drawMaskValueSet(mask);
}

GFX_Result set_drawAntialias(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    GFX_Bool aa = va_arg(args, GFX_Bool);
            
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif 
    
    return context->hal.drawAntialiasSet(aa);
}

GFX_Result set_drawThickness(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();
    
    uint32_t thickness = va_arg(args, uint32_t);
            
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif 
    
    return context->hal.drawThicknessSet(thickness);
}

GFX_Result set_drawClipEnable(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();

    GFX_Bool enabled = va_arg(args, GFX_Bool);
            
    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif  
    
    return context->hal.drawClipEnableSet(enabled);
}

GFX_Result set_drawClipRect(va_list args)
{
    GFX_Context* context = GFX_ActiveContext();

    GFX_Rect* rect = va_arg(args, GFX_Rect*);

    ASSERT(context != NULL);
    
#ifdef GFX_DEBUG
    if(context == NULL)
        return GFX_FAILURE;
#endif  

    return context->hal.drawClipRectSet(rect);
}

#endif // GFX_DRAW_PIPELINE_ENABLED