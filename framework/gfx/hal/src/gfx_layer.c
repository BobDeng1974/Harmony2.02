#include "gfx/hal/inc/gfx_layer.h"
#include "gfx/hal/inc/gfx_context.h"

GFX_PixelBuffer* GFX_LayerReadBuffer(GFX_Layer* layer)
{
    return &layer->buffers[layer->buffer_read_idx].pb;
}

GFX_PixelBuffer* GFX_LayerWriteBuffer(GFX_Layer* layer)
{
    return &layer->buffers[layer->buffer_write_idx].pb;
}

void GFX_LayerRotate(GFX_Layer* layer)
{
    int32_t t;
    
    t = layer->rect.local.width;
    layer->rect.local.width = layer->rect.local.height;
    layer->rect.local.height = t;
    
    t = layer->rect.display.height;
    layer->rect.display.height = layer->rect.display.width;
    layer->rect.display.width = t;
}

//int instance = 0;

void GFX_LayerSwap(GFX_Layer* layer)
{
    layer->swap = GFX_FALSE;
    
    //printf("GFX_LayerSwap: layer %u swap = FALSE\n", layer->id);
    
    if(layer->buffer_count <= 1)
        return;
    
    // might be first swap, in this case the first buffer is
    // acting as both read and write
    if(layer->buffer_read_idx != layer->buffer_write_idx)
        layer->buffer_read_idx = layer->buffer_write_idx;

    layer->buffer_write_idx++;
    
    if(layer->buffer_write_idx >= layer->buffer_count)
        layer->buffer_write_idx = 0;
        
    GFX_ActiveContext()->hal.layerSwapped(layer);
    
    //printf("%i - GFX_LayerSwap: layer %u swap, read=%u, write=%u\n", instance++, layer->id, layer->buffer_read_idx, layer->buffer_write_idx);
}

void _GFX_LayerSizeSet(GFX_Layer* layer, int32_t width, int32_t height)
{
	uint32_t i;

	layer->rect.local.width = width;
    layer->rect.local.height = height;

	layer->rect.display.width = width;
    layer->rect.display.height = height;

	for(i = 0; i < layer->buffer_count; i++)
	{
		layer->buffers[i].pb.size.width = width;
		layer->buffers[i].pb.size.height = height;
	}
}