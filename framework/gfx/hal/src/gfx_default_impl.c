#include "gfx/hal/inc/gfx_default_impl.h"

#include "gfx/hal/inc/gfx_color.h"
#include "gfx/hal/inc/gfx_context.h"
#include "gfx/hal/inc/gfx_draw.h"
#include "gfx/hal/inc/gfx_layer.h"
#include "gfx/hal/inc/gfx_pixel_buffer.h"
#include "gfx/hal/inc/gfx_util.h"

/*void *aligned_malloc(size_t size, size_t align_size)
{
    char *ptr,*ptr2,*aligned_ptr;
    int align_mask = align_size - 1;

    ptr=(char *)__pic32_alloc_coherent(size + align_size + sizeof(int));
    if(ptr==NULL) return(NULL);

    ptr2 = ptr + sizeof(int);
    aligned_ptr = ptr2 + (align_size - ((size_t)ptr2 & align_mask));

    ptr2 = aligned_ptr - sizeof(int);
    *((int *)ptr2)=(int)(aligned_ptr - ptr);

    return(aligned_ptr);
}

void aligned_free(void *ptr)
{
    int *ptr2=(int *)ptr - 1;
    ptr -= *ptr2;
    __pic32_free_coherent(ptr);
}*/

static GFX_Result layerBufferAllocate(GFX_Context* context,
                                      GFX_Layer* layer,
                                      uint32_t idx)
{
    void* pixelData;
    //void* mem;
    //void* ptr;
    
    if(layer->buffers[idx].state != GFX_BS_NONE)
        return GFX_FAILURE;
        
    // create pixel buffer construct
    GFX_PixelBufferCreate(layer->rect.local.width,
                          layer->rect.local.height,
                          context->colorMode,
                          NULL,
                          &layer->buffers[idx].pb);
    
    // allocate memory
    if(layer->buffers[idx].coherent == GFX_TRUE)
    {
        pixelData = context->memory.coherent_alloc(layer->buffers[idx].pb.buffer_length);
        //pixelData = frameBuffer;
        
        //pixelData = aligned_malloc(size, 16);
        
        //pixelData = malloc(size);
        
        //mem = context->memory.coherent_alloc(size+15);
        //pixelData = (void*)(((uintptr_t)mem+15) & ~ (uintptr_t)0x0F);
        //memset_16aligned(ptr, 0, 1024);
        //free(mem);
        
        //pixelData = frameBuffer;
        
    }
    else
        pixelData = context->memory.malloc(layer->buffers[idx].pb.buffer_length);
    
    if(pixelData == NULL)
        return GFX_FAILURE;
        
    // clear memory
    memset(pixelData, 0, layer->buffers[idx].pb.buffer_length);
    
    // set pixel data pointer and set allocated status
    layer->buffers[idx].pb.pixels = pixelData;
    layer->buffers[idx].state = GFX_BS_MALLOC;
    
    return GFX_SUCCESS;
}

static GFX_Result layerBufferFree(GFX_Context* context,
                                  GFX_Layer* layer,
                                  uint32_t idx)
{
    GFX_FrameBuffer* buf;
    
    buf = &layer->buffers[idx];
    
    // shouldn't free memory that wasn't allocated with buffer allocate
    if(buf->state != GFX_BS_MALLOC)
        return GFX_FAILURE;
    
    // free the memory
    if(buf->pb.pixels != GFX_NULL)
    {
        if(buf->coherent == GFX_TRUE)
            context->memory.coherent_free(buf->pb.pixels);
        else
            context->memory.free(buf->pb.pixels);
        
        buf->pb.pixels = GFX_NULL;
    }
    
    // change pixel buffer allocated status
    buf->state = GFX_BS_NONE;
    
    return GFX_SUCCESS;
}

GFX_Result defUnsupported(void)
{
    return GFX_UNSUPPORTED;
}

GFX_Result defInitialize(GFX_Context* context)
{
    uint32_t i;
    
    // initialize all layers
    for(i = 0; i < context->layer.count; i++)
    {
        // enables the layer
        context->layer.layers[i].enabled = GFX_TRUE;
    
        // sets all layer rectangles to the size of the display
        context->layer.layers[i].rect.local.x = 0;
        context->layer.layers[i].rect.local.y = 0;
        context->layer.layers[i].rect.local.width = context->display_info->rect.width;
        context->layer.layers[i].rect.local.height = context->display_info->rect.height;

        context->layer.layers[i].rect.display = context->layer.layers[i].rect.local;

        // disables alpha blending and sets opacity to full
		context->layer.layers[i].alphaEnable = GFX_FALSE;
        context->layer.layers[i].alphaAmount = 255;
        
        // disables masking and sets mask color to black
        context->layer.layers[i].maskEnable = GFX_FALSE;
        context->layer.layers[i].maskColor = 0;
    }
    
    return GFX_SUCCESS;
}

GFX_Result defBegin(void)
{
    GFX_Context* context = GFX_ActiveContext();
    
    // return false if active layer has a pending swap operation
	if(context->layer.active->locked == GFX_TRUE ||
	   context->layer.active->swap == GFX_TRUE)
		return GFX_FAILURE;
		
    context->layer.active->locked = GFX_TRUE;

    return GFX_SUCCESS;
}

void defEnd(void)
{
    GFX_ActiveContext()->layer.active->locked = GFX_FALSE;
}

GFX_Result defUpdate(void)
{
    return GFX_SUCCESS;
}

void defDestroy(GFX_Context* context)
{ 
    uint32_t i, j;
    
    // attempt to free all layer buffers
    for(i = 0; i < context->layer.count; i++)
    {
        for(j = 0; j < context->layer.layers[i].buffer_count; j++)
        {
            if(context->layer.layers[i].buffers[j].coherent == GFX_TRUE)
                context->memory.coherent_free(context->layer.layers[i].buffers[j].pb.pixels);
            else
                context->memory.free(context->layer.layers[i].buffers[j].pb.pixels);
                
            context->layer.layers[i].buffers[j].pb.pixels = NULL;
        }
    }
}

GFX_Result defBrightnessRangeGet(uint32_t* low, uint32_t* high)
{
    *low = 0;
    *high = 1;
    
    return GFX_SUCCESS;
}
       
uint32_t defBrightnessGet(void)
{
    return GFX_ActiveContext()->brightness;
}

GFX_Result defBrightnessSet(uint32_t val)
{
    if(val > 1)
        return GFX_FAILURE;
        
    GFX_ActiveContext()->brightness = val;
    
    return GFX_SUCCESS;
}  

GFX_SyncCallback_FnPtr defVSyncCallbackGet(void)
{
    return GFX_ActiveContext()->vsyncCB;
}

GFX_Result defVSyncCallbackSet(GFX_SyncCallback_FnPtr cb)
{
    if(cb == NULL)
        cb = _GFX_DefaultSyncCallback;
    
    GFX_ActiveContext()->vsyncCB = cb;
    
    return GFX_SUCCESS;
}

GFX_SyncCallback_FnPtr defHSyncCallbackGet(void)
{
    return GFX_ActiveContext()->hsyncCB;
}

GFX_Result defHSyncCallbackSet(GFX_SyncCallback_FnPtr cb)
{
    if(cb == NULL)
        cb = _GFX_DefaultSyncCallback;
    
    GFX_ActiveContext()->hsyncCB = cb;
    
    return GFX_SUCCESS;
}

GFX_Orientation defOrientationGet(void)
{
    return GFX_ActiveContext()->orientation;
}

GFX_Result defOrientationSet(GFX_Orientation ori)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Layer* layer;
	GFX_Size size;
	GFX_Point pnt;
    uint32_t i;
       
    if(context->orientation == ori)
        return GFX_SUCCESS;

	/* convert layer positions from old orientation to new */
	for(i = 0; i < context->layer.count; i++)
	{
		layer = &context->layer.layers[i];

		pnt.x = layer->rect.display.x;
		pnt.y = layer->rect.display.y;

		size.width = layer->rect.display.width;
		size.height = layer->rect.display.height;

		GFX_LayerSizeFromOrientedSpace(&size, context->orientation);

		GFX_LayerOriginFromOrientedSpace(&pnt,
		                                 &context->display_info->rect,
								         &layer->rect.display,
								         context->orientation,
								         context->mirrored);

		GFX_LayerSizeToOrientedSpace(&size, ori);

		_GFX_LayerSizeSet(layer, size.width, size.height);

		GFX_LayerOriginToOrientedSpace(&pnt,
		                               &context->display_info->rect,
								       &layer->rect.display,
								       ori,
								       context->mirrored);

		layer->rect.display.x = pnt.x;
		layer->rect.display.y = pnt.y;
	}
    
    GFX_ActiveContext()->orientation = ori;

    return GFX_SUCCESS;
}
 
GFX_Bool defMirroringGet(void)
{
    return GFX_ActiveContext()->mirrored;
}

GFX_Result defMirroringSet(GFX_Bool mirr)
{
	GFX_Context* context = GFX_ActiveContext();
	GFX_Layer* layer;
	GFX_Point pnt;
	uint32_t i;

	if(context->mirrored == mirr)
		return GFX_SUCCESS;

	/* convert layer positions from old mirror position to new */
	for(i = 0; i < context->layer.count; i++)
	{
		layer = &context->layer.layers[i];

		pnt.x = layer->rect.display.x;
		pnt.y = layer->rect.display.y;

		GFX_LayerOriginFromOrientedSpace(&pnt,
		                                 &context->display_info->rect,
								         &layer->rect.display,
								         context->orientation,
								         context->mirrored);

		GFX_LayerOriginToOrientedSpace(&pnt,
		                               &context->display_info->rect,
								       &layer->rect.display,
								       context->orientation,
								       mirr);

		layer->rect.display.x = pnt.x;
		layer->rect.display.y = pnt.y;
	}

    context->mirrored = mirr;

    return GFX_SUCCESS;
}

GFX_ColorMode defColorModeGet(void)
{
    return GFX_ActiveContext()->colorMode;
}

GFX_Result defColorModeSet(GFX_ColorMode mode)
{
    uint32_t i, j;
    GFX_Layer* layer;
    GFX_Bool reallocate = GFX_FALSE;
    
    if(GFX_ActiveContext()->colorMode == mode)
        return GFX_SUCCESS;
        
    reallocate = GFX_ColorInfo[GFX_ActiveContext()->colorMode].bpp ==
                 GFX_ColorInfo[mode].bpp;
    
    for(i = 0; i < GFX_ActiveContext()->layer.count; i++)
    {
        layer = &GFX_ActiveContext()->layer.layers[i];
        
        for(j = 0; j < layer->buffer_count; j++)
        {
            // if color bpp is equal then buffers don't need to be reallocated
            if(reallocate == GFX_FALSE)
            {
                layer->buffers[j].pb.mode = mode; // just set new pixel mode
            }
            else if(layer->buffers[j].state == GFX_BS_MALLOC)
            {
                // reallocate buffer memory and pixel buffer construct
                layerBufferFree(GFX_ActiveContext(), layer, j);
                layerBufferAllocate(GFX_ActiveContext(), layer, j);
            }
        }
    }
        
    // set new global color mode
    GFX_ActiveContext()->colorMode = mode;
       
    return GFX_SUCCESS;
}

uint32_t defLayerActiveGet(void)
{
    return GFX_ActiveContext()->layer.active_idx;
}

GFX_Result defLayerActiveSet(uint32_t idx)
{
    GFX_Context* context = GFX_ActiveContext();
    
    if(idx >= context->layer.count)
        return GFX_FAILURE;
        
    context->layer.active = &context->layer.layers[idx];
    
    return GFX_SUCCESS;
}

GFX_Bool defLayerEnabledGet(void)
{
    return GFX_ActiveContext()->layer.active->enabled;
}

GFX_Result defLayerEnabledSet(GFX_Bool val)
{
    GFX_ActiveContext()->layer.active->enabled = val;

    return GFX_SUCCESS;
}

GFX_Bool defLayerVisibleGet(void)
{
    return GFX_ActiveContext()->layer.active->visible;
}

GFX_Result defLayerVisibleSet(GFX_Bool value)
{
    GFX_ActiveContext()->layer.active->visible = value;
    
    return GFX_SUCCESS;
}

GFX_Result defLayerPositionGet(int32_t* x, int32_t* y)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Point pnt;

	pnt.x = context->layer.active->rect.display.x;
	pnt.y = context->layer.active->rect.display.y;

	GFX_LayerOriginFromOrientedSpace(&pnt,
		                             &context->display_info->rect,
								     &context->layer.active->rect.display,
								     context->orientation,
								     context->mirrored);

    return GFX_SUCCESS;
}

GFX_Result defLayerPositionSet(int32_t x, int32_t y)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Point pnt;
    
	pnt.x = x;
	pnt.y = y;

	GFX_LayerOriginToOrientedSpace(&pnt,
		                           &context->display_info->rect,
								   &context->layer.active->rect.display,
								   context->orientation,
								   context->mirrored);

    context->layer.active->rect.display.x = pnt.x;
    context->layer.active->rect.display.y = pnt.y;
    
    return GFX_SUCCESS;
}

GFX_Result defLayerSizeGet(int32_t* width, int32_t* height)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Size size;

	// transform from oriented space
	size.width = context->layer.active->rect.local.width;
	size.height = context->layer.active->rect.local.height;

	GFX_LayerSizeFromOrientedSpace(&size, context->orientation);

    *width  = size.width;
    *height = size.height;
    
    return GFX_SUCCESS;
}

GFX_Result defLayerSizeSet(int32_t width, int32_t height)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Size size;

	// transform to oriented space
	size.width = width;
	size.height = height;

	GFX_LayerSizeFromOrientedSpace(&size, context->orientation);

	_GFX_LayerSizeSet(context->layer.active, size.width, size.height);

	// TODO 
	// reallocate buffers if necessary

    //context->layer.active->rect.local.width = size.width;
    //context->layer.active->rect.local.height = size.height;

	//context->layer.active->rect.display.width = size.width;
    //context->layer.active->rect.display.height = size.height;
    
    return GFX_SUCCESS;
}

uint32_t defLayerBufferCountGet(void)
{
    return GFX_ActiveContext()->layer.active->buffer_count;
}

GFX_Result defLayerBufferCountSet(uint32_t count)
{
    uint32_t i;
    GFX_Context* context = GFX_ActiveContext();
    GFX_Layer* layer = context->layer.active;
    
    if(layer->buffer_count == count)
        return GFX_SUCCESS;
    
    // delete buffers past buffer count
    if(count < layer->buffer_count)
    {
        for(i = count; i < layer->buffer_count; i++)
            layerBufferFree(context, layer, i);
    }
    else
    {
        // set up buffer struct but don't allocate memory
        for(i = layer->buffer_count; i < count; i++)
        {
            layer->buffers[i].coherent = GFX_FALSE;             
            layer->buffers[i].state = GFX_BS_NONE;
            layer->buffers[i].driver_data = NULL;
            
            GFX_PixelBufferCreate(layer->rect.local.width,
                                  layer->rect.local.height,
                                  context->colorMode,
                                  NULL,
                                  &layer->buffers[i].pb);
        }
    }
        
    layer->buffer_count = count;

    return GFX_SUCCESS;
}

GFX_Buffer defLayerBufferAddressGet(uint32_t idx)
{
    return GFX_ActiveContext()->layer.active->buffers[idx].pb.pixels;
}

GFX_Result defLayerBufferAddressSet(uint32_t idx, GFX_Buffer address)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Layer* layer = context->layer.active;
    
    if(layer->buffers[idx].state != GFX_BS_NONE)
        return GFX_FAILURE;
    
    if(address != NULL)
    {
        layer->buffers[idx].pb.pixels = address;
        layer->buffers[idx].state = GFX_BS_ADDRESS;
    
        GFX_PixelBufferCreate(layer->rect.local.width,
                              layer->rect.local.height,
                              context->colorMode,
                              address,
                              &layer->buffers[idx].pb);
    }
    else
    {
        layer->buffers[idx].pb.pixels = NULL;
        
        GFX_PixelBufferDestroy(&layer->buffers[idx].pb, &context->memory);
        
        layer->buffers[idx].state = GFX_BS_NONE;
    }
    
    return GFX_SUCCESS;
}

GFX_Bool defLayerBufferCoherentGet(uint32_t idx)
{
    return GFX_ActiveContext()->layer.active->buffers[idx].coherent;
}

GFX_Result defLayerBufferCoherentSet(uint32_t idx, GFX_Bool coherent)
{
    GFX_ActiveContext()->layer.active->buffers[idx].coherent = coherent;
    
    return GFX_SUCCESS;
}

GFX_Result defLayerBufferAllocate(uint32_t idx)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Layer* layer = context->layer.active;
    
    return layerBufferAllocate(context, layer, idx);
}

GFX_Bool defLayerBufferIsAllocated(uint32_t idx)
{
    return GFX_ActiveContext()->layer.active->buffers[idx].state == GFX_BS_MALLOC;
}

GFX_Result defLayerBufferFree(uint32_t idx)
{
    GFX_Context* context = GFX_ActiveContext();
    
    return layerBufferFree(context, context->layer.active, idx);
}

GFX_Bool defLayerVsyncGet(void)
{
    return GFX_ActiveContext()->layer.active->vsync;
}

GFX_Result defLayerVsyncSet(GFX_Bool vsync)
{
    GFX_ActiveContext()->layer.active->vsync = vsync;
    
    return GFX_SUCCESS;
}

GFX_Bool defLayerSwapGet(void)
{
    return GFX_ActiveContext()->layer.active->swap;
}

GFX_Result defLayerSwapSet(GFX_Bool value)
{
    if(GFX_ActiveContext()->layer.active->locked == GFX_TRUE)
        return GFX_FAILURE;
    
    if(GFX_ActiveContext()->layer.active->vsync == GFX_TRUE)
        GFX_ActiveContext()->layer.active->swap = value;
    else
        GFX_LayerSwap(GFX_ActiveContext()->layer.active);
    
    return GFX_SUCCESS;
}

void defLayerSwapped(GFX_Layer* layer)
{ }

GFX_Bool defLayerAlphaEnableGet(void)
{
    return GFX_ActiveContext()->layer.active->alphaEnable;
}

GFX_Result defLayerAlphaEnableSet(GFX_Bool enable)
{
    GFX_ActiveContext()->layer.active->alphaEnable = enable;
    
    return GFX_SUCCESS;
}

uint32_t defLayerAlphaAmountGet(void)
{
    return GFX_ActiveContext()->layer.active->alphaAmount;
}

GFX_Result defLayerAlphaAmountSet(uint32_t amount)
{
    if(amount > 255)
        amount = 255;
        
    GFX_ActiveContext()->layer.active->alphaAmount = amount;
    
    return GFX_SUCCESS;
}

GFX_Bool defLayerMaskEnableGet(void)
{
    return GFX_ActiveContext()->layer.active->maskEnable;
}

GFX_Result defLayerMaskEnableSet(GFX_Bool enable)
{
    GFX_ActiveContext()->layer.active->maskEnable = enable;
    
    return GFX_SUCCESS;
}

GFX_Color defLayerMaskColorGet(void)
{
    return GFX_ActiveContext()->layer.active->maskColor;
}

GFX_Result defLayerMaskColorSet(GFX_Color color)
{
    GFX_ActiveContext()->layer.active->maskColor = color;
    
    return GFX_SUCCESS;
}

#if GFX_DRAW_PIPELINE_ENABLED

GFX_DrawMode defDrawModeGet(void)
{
    return GFX_ActiveContext()->draw.mode;
}

GFX_Result defDrawModeSet(GFX_DrawMode mode)
{    
    GFX_ActiveContext()->draw.mode = mode;
    
    /*if(mode == GFX_DRAW_LINE)
        GFX_ActiveContext()->hal.drawRect = &cpuDrawRect;
    else if(mode == GFX_DRAW_FILL)
        GFX_ActiveContext()->hal.drawRect = &cpuFillRect;*/
    
    return GFX_SUCCESS;
}

GFX_Color defDrawColorGet(void)
{
    return GFX_ActiveContext()->draw.color;
}

GFX_Result defDrawColorSet(GFX_Color color)
{   
    GFX_ActiveContext()->draw.color = color;
    
    return GFX_SUCCESS;
}

void defDrawGradientColorGet(GFX_Color* c0,
                             GFX_Color* c1,
                             GFX_Color* c2,
                             GFX_Color* c3)
{
    GFX_Context* context = GFX_ActiveContext();
    
    *c0 = context->draw.gradient.c0;
    *c1 = context->draw.gradient.c1;
    *c2 = context->draw.gradient.c2;
    *c3 = context->draw.gradient.c3;
}

GFX_Result defDrawGradientColorSet(GFX_Color c0,
                                   GFX_Color c1,
                                   GFX_Color c2,
                                   GFX_Color c3)
{   
    GFX_Context* context = GFX_ActiveContext();
    
    context->draw.gradient.c0 = c0;
    context->draw.gradient.c1 = c1;
    context->draw.gradient.c2 = c2;
    context->draw.gradient.c3 = c3;
    
    return GFX_SUCCESS;
}

GFX_Result defDrawPaletteGet(GFX_PixelBuffer* pb)
{
    *pb = GFX_ActiveContext()->draw.palette;
    
    return GFX_SUCCESS;
}

GFX_Result defDrawPaletteSet(GFX_PixelBuffer* pb)
{
    GFX_Context* context = GFX_ActiveContext();
    
    context->draw.palette.buffer_length = 0;
    context->draw.palette.mode = 0;
    context->draw.palette.pixels = GFX_NULL;
    context->draw.palette.size.width = 0;
    context->draw.palette.size.height = 0;
    
    // null palette is OK
    if(pb == GFX_NULL)
    {
        return GFX_SUCCESS;
    }
    // palettes must be a valid actual color format (not indexed)
    else if(pb->mode < 0 || pb->mode > GFX_COLOR_MODE_LAST_COLOR)
    {
        return GFX_FAILURE;
    }
    else
    {
        context->draw.palette = *pb;
        
        return GFX_SUCCESS;
    }
}

GFX_BlendMode defDrawBlendModeGet(void)
{
    GFX_Context* context = GFX_ActiveContext();
    uint32_t mode = 0;
    
    mode &= context->draw.maskEnable << (GFX_BLEND_MASK >> 1);   
    mode &= context->draw.alphaEnable << (GFX_BLEND_ALPHA >> 1);
    
    return mode;
}

GFX_Result defDrawBlendModeSet(GFX_BlendMode mode)
{
    GFX_Context* context = GFX_ActiveContext();
    
    context->draw.maskEnable = (mode & GFX_BLEND_MASK) > 0;
    context->draw.alphaEnable = (mode & GFX_BLEND_ALPHA) > 0;
    
    return GFX_SUCCESS;
}

GFX_Bool defDrawAlphaEnableGet(void)
{
    return GFX_ActiveContext()->draw.alphaEnable;
}

GFX_Result defDrawAlphaEnableSet(GFX_Bool enabled)
{    
    GFX_ActiveContext()->draw.alphaEnable = enabled;
    
    return GFX_SUCCESS;
}

uint32_t defDrawAlphaValueGet(void)
{
    return GFX_ActiveContext()->draw.alphaValue;
}

GFX_Result defDrawAlphaValueSet(uint32_t value)
{    
    GFX_ActiveContext()->draw.alphaValue = value;
    
    return GFX_SUCCESS;
}

GFX_Bool defDrawMaskEnableGet(void)
{
    return GFX_ActiveContext()->draw.maskEnable;
}

GFX_Result defDrawMaskEnableSet(GFX_Bool enabled)
{    
    GFX_ActiveContext()->draw.maskEnable = enabled;
    
    return GFX_SUCCESS;
}

uint32_t defDrawMaskValueGet(void)
{
    return GFX_ActiveContext()->draw.maskValue;
}

GFX_Result defDrawMaskValueSet(uint32_t value)
{    
    GFX_ActiveContext()->draw.maskValue = value;
    
    return GFX_SUCCESS;
}

uint32_t defDrawThicknessGet(void)
{
    return GFX_ActiveContext()->draw.thickness;
}

GFX_Result defDrawThicknessSet(uint32_t value)
{    
    GFX_ActiveContext()->draw.thickness = value;
    
    return GFX_SUCCESS;
}

GFX_Bool defDrawClipEnabledGet(void)
{
    return GFX_ActiveContext()->draw.clipEnable;
}

GFX_Result defDrawClipEnabledSet(GFX_Bool value)
{
    GFX_ActiveContext()->draw.clipEnable = value;
    
    return GFX_SUCCESS;
}

GFX_Result defDrawClipRectGet(GFX_Rect* rect)
{
    *rect = GFX_ActiveContext()->draw.clipRect;
    
    return GFX_SUCCESS;
}

GFX_Result defDrawClipRectSet(GFX_Rect* rect)
{
    GFX_ActiveContext()->draw.clipRect = *rect;
    
    return GFX_SUCCESS;
}

GFX_Result defDrawLock(void)
{
    return GFX_SUCCESS;
}

GFX_Result defDrawUnlock(void)
{
    return GFX_SUCCESS;
}

#endif // GFX_DRAW_PIPELINE_ENABLED

GFX_Result defSwap(void)
{
    GFX_Context* context;
    GFX_Layer* layer;
    GFX_Bool l;
    GFX_Result res = GFX_SUCCESS;

    context = GFX_ActiveContext();
    
	// iterate over each layer and decide whether the context
	// needs to swap at the next opportunity
	for(l = 0; l < context->layer.count; l++)
    {
        layer = &context->layer.layers[l];
     
        if(layer->enabled == GFX_TRUE &&
		   layer->visible == GFX_TRUE &&
		   layer->swap == GFX_TRUE &&
		   layer->locked == GFX_FALSE)
		{
		    // turn on swap flag
		    if(layer->vsync == GFX_TRUE)
		    {			    
			    //printf("defswap: layer swap = TRUE\n");
			    
			    res = GFX_FAILURE;

			    break;
			}
			// vsync is off, swap immediately
			else
			{
			    GFX_LayerSwap(layer);
			    
			    //printf("defswap: swap immediately\n");
			}
		}
    }

	return res;
}

GFX_Result defInterrupt(uint32_t id)
{
    return GFX_SUCCESS;
}

GFX_Color defPixelGet(const GFX_PixelBuffer* buffer, const GFX_Point* pnt)
{
    return GFX_PixelBufferGet(buffer, pnt);
}

#if GFX_DRAW_PIPELINE_ENABLED
GFX_Result defPixelSet(const GFX_PixelBuffer* buffer,
                       const GFX_Point* pnt,
                       GFX_Color color)
{
    return GFX_PixelBufferSet(buffer, pnt, color);
}
#endif // GFX_DRAW_PIPELINE_ENABLED


GFX_Result contextDefInitialization(GFX_Context* context)
{
    if(context == NULL)
        return GFX_FAILURE;

    // set HAL interfaces
    context->hal.initialize = &defInitialize;
	context->hal.begin = &defBegin;
	context->hal.end = &defEnd;
    context->hal.update = &defUpdate;
    context->hal.destroy = &defDestroy;
    context->hal.brightnessRangeGet = &defBrightnessRangeGet;
    context->hal.brightnessGet = &defBrightnessGet;
    context->hal.brightnessSet = &defBrightnessSet;
    context->hal.vsyncCallbackGet = &defVSyncCallbackGet;
    context->hal.vsyncCallbackSet = &defVSyncCallbackSet;
    context->hal.hsyncCallbackGet = &defHSyncCallbackGet;
    context->hal.hsyncCallbackSet = &defHSyncCallbackSet;
    
    context->hal.orientationGet = &defOrientationGet;
    context->hal.orientationSet = &defOrientationSet;
    context->hal.mirroringGet = &defMirroringGet;
    context->hal.mirroringSet = &defMirroringSet;
    
    context->hal.colorModeGet = &defColorModeGet;
    context->hal.colorModeSet = &defColorModeSet;
    
    context->hal.layerEnabledGet = &defLayerEnabledGet;
    context->hal.layerEnabledSet = &defLayerEnabledSet;
    context->hal.layerBufferCountGet = &defLayerBufferCountGet;
    context->hal.layerBufferCountSet = &defLayerBufferCountSet;
    context->hal.layerBufferAddressGet = &defLayerBufferAddressGet;
    context->hal.layerBufferAddressSet = &defLayerBufferAddressSet;
    context->hal.layerBufferCoherentGet = &defLayerBufferCoherentGet;
    context->hal.layerBufferCoherentSet = &defLayerBufferCoherentSet;
    context->hal.layerBufferAllocate = &defLayerBufferAllocate;
    context->hal.layerBufferIsAllocated = &defLayerBufferIsAllocated;
    context->hal.layerBufferFree = &defLayerBufferFree;
    context->hal.layerVisibleGet = &defLayerVisibleGet;
    context->hal.layerVisibleSet = &defLayerVisibleSet;
    context->hal.layerVsyncGet = &defLayerVsyncGet;
    context->hal.layerVsyncSet = &defLayerVsyncSet;
	context->hal.layerSwapGet = &defLayerSwapGet;
    context->hal.layerSwapSet = &defLayerSwapSet;
    context->hal.layerSwapped = &defLayerSwapped;
    context->hal.layerActiveGet = &defLayerActiveGet;
    context->hal.layerActiveSet = &defLayerActiveSet;
    context->hal.layerPositionGet = &defLayerPositionGet;
    context->hal.layerPositionSet = &defLayerPositionSet;
    context->hal.layerSizeGet = &defLayerSizeGet;
    context->hal.layerSizeSet = &defLayerSizeSet;
    context->hal.layerAlphaEnableGet = &defLayerAlphaEnableGet;
    context->hal.layerAlphaEnableSet = &defLayerAlphaEnableSet;
    context->hal.layerAlphaAmountGet = &defLayerAlphaAmountGet;
    context->hal.layerAlphaAmountSet = &defLayerAlphaAmountSet;
    context->hal.layerMaskEnableGet = &defLayerMaskEnableGet;
    context->hal.layerMaskEnableSet = &defLayerMaskEnableSet;
    context->hal.layerMaskColorGet = &defLayerMaskColorGet;
    context->hal.layerMaskColorSet = &defLayerMaskColorSet;
    
#if GFX_DRAW_PIPELINE_ENABLED
    
    context->hal.drawModeGet = &defDrawModeGet;
    context->hal.drawModeSet = &defDrawModeSet;
    context->hal.drawColorGet = &defDrawColorGet;
    context->hal.drawColorSet = &defDrawColorSet;
    context->hal.drawGradientColorGet = &defDrawGradientColorGet;
    context->hal.drawGradientColorSet = &defDrawGradientColorSet;
    context->hal.drawPaletteGet = &defDrawPaletteGet;
    context->hal.drawPaletteSet = &defDrawPaletteSet;
    context->hal.drawBlendModeGet = &defDrawBlendModeGet;
    context->hal.drawBlendModeSet = &defDrawBlendModeSet;
    context->hal.drawAlphaEnableGet = &defDrawAlphaEnableGet;
    context->hal.drawAlphaEnableSet = &defDrawAlphaEnableSet;
    context->hal.drawAlphaValueGet = &defDrawAlphaValueGet;
    context->hal.drawAlphaValueSet = &defDrawAlphaValueSet;
    context->hal.drawMaskEnableGet = &defDrawMaskEnableGet;
    context->hal.drawMaskEnableSet = &defDrawMaskEnableSet;
    context->hal.drawMaskValueGet = &defDrawMaskValueGet;
    context->hal.drawMaskValueSet = &defDrawMaskValueSet;
    context->hal.drawThicknessGet = &defDrawThicknessGet;
    context->hal.drawThicknessSet = &defDrawThicknessSet;
    context->hal.drawClipEnableGet = &defDrawClipEnabledGet;
    context->hal.drawClipEnableSet = &defDrawClipEnabledSet;
    context->hal.drawClipRectGet = &defDrawClipRectGet;
    context->hal.drawClipRectSet = &defDrawClipRectSet;
    
    context->hal.drawPixel[GFX_ANTIALIAS_OFF] = &cpuDrawPixel;
    context->hal.drawPixel[GFX_ANTIALIAS_ON] = &cpuDrawPixel;
    
    context->hal.drawLine[GFX_DRAW_LINE][GFX_ANTIALIAS_OFF] = &cpuDrawLine;
    context->hal.drawLine[GFX_DRAW_FILL][GFX_ANTIALIAS_OFF] = &cpuDrawLine;
    //context->hal.drawLine[GFX_DRAW_GRADIENT_LEFT_RIGHT][GFX_ANTIALIAS_OFF] = &cpuDrawLine_Gradient;
    //context->hal.drawLine[GFX_DRAW_GRADIENT_TOP_BOTTOM][GFX_ANTIALIAS_OFF] = &cpuDrawLine_Gradient;
    //context->hal.drawLine[GFX_DRAW_GRADIENT_RECT][GFX_ANTIALIAS_OFF] = &cpuDrawLine_Gradient;
    
    context->hal.drawLine[GFX_DRAW_LINE][GFX_ANTIALIAS_ON] = &cpuDrawLine_AA;
    context->hal.drawLine[GFX_DRAW_FILL][GFX_ANTIALIAS_ON] = &cpuDrawLine_AA;
    //context->hal.drawLine[GFX_DRAW_GRADIENT_LEFT_RIGHT][GFX_ANTIALIAS_ON] = &cpuDrawLine_Gradient_AA;
    //context->hal.drawLine[GFX_DRAW_GRADIENT_TOP_BOTTOM][GFX_ANTIALIAS_ON] = &cpuDrawLine_Gradient_AA;
    //context->hal.drawLine[GFX_DRAW_GRADIENT_RECT][GFX_ANTIALIAS_ON] = &cpuDrawLine_Gradient_AA;
    
    context->hal.drawRect[GFX_DRAW_LINE][GFX_ANTIALIAS_OFF] = &cpuDrawRect_Line;
    context->hal.drawRect[GFX_DRAW_FILL][GFX_ANTIALIAS_OFF] = &cpuDrawRect_Fill;
    context->hal.drawRect[GFX_DRAW_GRADIENT_LEFT_RIGHT][GFX_ANTIALIAS_OFF] = &cpuDrawRect_Gradient_LeftRight;
    context->hal.drawRect[GFX_DRAW_GRADIENT_TOP_BOTTOM][GFX_ANTIALIAS_OFF] = &cpuDrawRect_Gradient_TopBottom;
    //context->hal.drawRect[GFX_DRAW_GRADIENT_RECT][GFX_ANTIALIAS_OFF] = &cpuDrawRect_Gradient_Quad;
    
    context->hal.drawRect[GFX_DRAW_LINE][GFX_ANTIALIAS_ON] = &cpuDrawRect_Line_AA;
    context->hal.drawRect[GFX_DRAW_FILL][GFX_ANTIALIAS_ON] = &cpuDrawRect_Fill_AA;
    //context->hal.drawRect[GFX_DRAW_GRADIENT_LEFT_RIGHT][GFX_ANTIALIAS_ON] = &cpuDrawRect_Gradient_Bi_AA;
    //context->hal.drawRect[GFX_DRAW_GRADIENT_TOP_BOTTOM][GFX_ANTIALIAS_ON] = &cpuDrawRect_Gradient_Quad_AA;
    //context->hal.drawRect[GFX_DRAW_GRADIENT_RECT][GFX_ANTIALIAS_ON] = &cpuDrawRect_Gradient_Quad_AA;
    
    context->hal.drawCircle[GFX_DRAW_LINE][GFX_ANTIALIAS_OFF] = &cpuDrawCircle_Line;
    //context->hal.drawRect[GFX_DRAW_FILL][GFX_ANTIALIAS_OFF] = &cpuDrawRect_Fill_AA;
    
    //context->hal.drawLineHorz = &cpuDrawLineHorz;
    //context->hal.drawLineVert = &cpuDrawLineVert;
    //context->hal.drawRect = &cpuDrawRect;
    //context->hal.fillRect = &cpuFillRect;
    context->hal.drawBlit = &cpuDrawBlit;
    //context->hal.blit_mask = &gfx_cpu_blit_mask;
    
    context->hal.drawLock = &defDrawLock;
    context->hal.drawUnlock = &defDrawUnlock;
    
    context->hal.pixelGet = &defPixelGet;
    context->hal.pixelSet = &defPixelSet;

#endif // GFX_DRAW_PIPELINE_ENABLED

    context->hal.interrupt = &defInterrupt;
    
    return GFX_SUCCESS;
}