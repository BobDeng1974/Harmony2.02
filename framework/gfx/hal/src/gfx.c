#include "gfx/hal/gfx.h"

#include <stdlib.h>
#include <string.h>

#include "gfx/hal/inc/gfx_common.h"
#include "gfx/hal/inc/gfx_context.h"
#include "gfx/hal/inc/gfx_default_impl.h"
#include "gfx/hal/inc/gfx_display.h"
#include "gfx/hal/inc/gfx_driver_interface.h"
#include "gfx/hal/inc/gfx_hal.h"
#include "gfx/hal/inc/gfx_interface.h"
#include "gfx/hal/inc/gfx_layer.h"

GFX_Result GFX_Initialize(void)
{
    if(GFX_DriverIntfInitialize() == GFX_FAILURE)
        return GFX_FAILURE;

    return GFX_SUCCESS;
}

GFX_Handle GFX_Open(GFX_Driver driver,
                    GFX_Display display,
                    GFX_Processor processor,
                    GFX_MemoryIntf* memintf)
{
    GFX_Context* context;
    GFX_Result res = GFX_FAILURE;
    GFX_DriverInfo info;
    GFX_DriverIntf iface;
    GFX_MemoryIntf mem;
    GFX_ColorMode minDisplayMode;
    uint32_t i;
    
    ASSERT(driver < GFX_DRIVER_COUNT);
    ASSERT(display < GFX_DISPLAY_COUNT);
    
    if(driver >= GFX_DRIVER_COUNT || display >= GFX_DISPLAY_COUNT)
        return NULL;
        
    if(memintf == GFX_NULL)
    {
        mem.malloc = &malloc;
        mem.coherent_alloc = &malloc;//&__pic32_alloc_coherent;
        mem.calloc = &calloc;
        mem.realloc = &realloc;
        mem.free = &free;
        mem.coherent_free = &free;//&__pic32_free_coherent;
        mem.memset = &memset;
        mem.memcpy = &memcpy;
    }
    else
        mem = *memintf;
        
    // get the driver interface
    GFX_DriverIntfGet(driver, &iface);
    iface.infoGet(&info);
        
    context = mem.calloc(1, sizeof(GFX_Context));
    
    if(context == NULL)
        return NULL;
    
    // set context memory interface
    context->memory = mem;
        
    // set display info
    context->display_idx = display;
    context->display_info = GFX_DisplayInfoPtrGet(display);
    
    
    minDisplayMode = 0;
    
    // determine minimum display mode format
    for(i = 0; i < GFX_COLOR_MODE_LAST_COLOR; i++)
    {
        if((context->display_info->color_formats & (1 << i)) != 0)
        {
            minDisplayMode = i;
            
            break;
        }
    }
    
    context->colorMode = minDisplayMode;
    
    context->brightness = 0;
    
    // allocate layers
    context->layer.count = info.layer_count;
    context->layer.layers = context->memory.calloc(info.layer_count, sizeof(GFX_Layer));
    
    // set layer IDs
    for(i = 0; i < context->layer.count; i++)
    {
        context->layer.layers[i].id = i;
        context->layer.layers[i].vsync = GFX_TRUE;
    }
        
    // set layer 0 as active by default
    context->layer.active = &context->layer.layers[0];
    
    // set layer 0 size to the screen size by default
    context->layer.layers[0].rect.display = context->display_info->rect;
    context->layer.layers[0].rect.local = context->layer.layers[0].rect.display;
	
	// default sync callbacks
	context->vsyncCB = &_GFX_DefaultSyncCallback;
	context->hsyncCB = &_GFX_DefaultSyncCallback;

#if GFX_DRAW_PIPELINE_ENABLED
    // set initial draw state
    context->draw.mode = GFX_DRAW_LINE;
    context->draw.color = 0x0;
    context->draw.gradient.c0 = 0x0;
    context->draw.gradient.c1 = 0x0;
    context->draw.gradient.c2 = 0x0;
    context->draw.gradient.c3 = 0x0;
    context->draw.alphaEnable = GFX_FALSE;
    context->draw.alphaValue = 0;
    context->draw.maskEnable = GFX_FALSE;
    context->draw.maskValue = 0;
    context->draw.thickness = 1;
    
    // set initial clip space (entire display)
    context->draw.clipRect.width = context->display_info->rect.width;
    context->draw.clipRect.height = context->display_info->rect.height;
#endif // GFX_DRAW_PIPELINE_ENABLED    
    
    // default driver hal initialization
    res = contextDefInitialization(context);
    
    if(res == GFX_FAILURE)
    {
        GFX_Close(context);
        
        return NULL;
    }
    
    // driver-specific context initialization
    res = iface.contextInitialize(context);
    
    if(res == GFX_FAILURE)
    {
        GFX_Close(context);
        
        return NULL;
    }
    
    // driver initialize
    res = context->hal.initialize(context);
    
    if(res == GFX_FAILURE)
    {
        GFX_Close(context);
        
        return NULL;
    }
    
    // set as active context if no exists
    if(GFX_ActiveContext() == NULL)
        GFX_ContextActiveSet(context);
    
    return (GFX_Handle*)context;
}

GFX_Result GFX_Update()
{
    GFX_Context* context = GFX_ActiveContext();
    
    if(context == NULL)
        return GFX_FAILURE;
    
    return context->hal.update();
}

void GFX_Close()
{
    GFX_Context* context;
    uint32_t i, j;

    context = GFX_ActiveContext();
    
    if(context == NULL)
        return;
    
    // driver destroy
    context->hal.destroy(context);
    
    // free driver data
    if(context->driver_data != GFX_NULL)
    {
        free(context->driver_data);
        context->driver_data = GFX_NULL;
    }
    
    // free driver layers
    if(context->layer.layers != NULL)
    {
        for(i = 0; i < context->layer.count; i++)
        {
            for(j = 0; j < GFX_MAX_BUFFER_COUNT; j++)
            {
                if(context->layer.layers[i].buffers[j].state == GFX_BS_MALLOC)
                {
                    if(context->layer.layers[i].buffers[j].pb.pixels != GFX_NULL)
                    {
                        free(context->layer.layers[i].buffers[j].pb.pixels);
                        context->layer.layers[i].buffers[j].pb.pixels = GFX_NULL;
                    }
                }
            }
            
            if(context->layer.layers != GFX_NULL)
            {
                free(context->layer.layers);
                context->layer.layers = GFX_NULL;
            }
        }           
    }
    
    // free context
    free(context);
}

GFX_Result GFX_Begin()
{
	GFX_Context* context;

    context = GFX_ActiveContext();
    
    if(context == NULL)
        return GFX_FAILURE;

	return context->hal.begin();
}

void GFX_End()
{
	GFX_Context* context = GFX_ActiveContext();
    
    if(context == NULL)
        return;

	context->hal.end();
}

GFX_Result GFX_Get(GFX_Flag flag, ...)
{
    GFX_Result result = GFX_FAILURE;
    va_list args;
    
    if(flag > GFXF_LAST_FLAG)
        return GFX_FAILURE;
    
    va_start(args, flag);
    
    result = GFX_InterfaceTable[flag][GFX_GET](args);
    
    va_end(args);
    
    return result;
}

GFX_Result GFX_Set(GFX_Flag flag, ...)
{
    GFX_Result result = GFX_FAILURE;
    va_list args;

	GFX_Context* context = GFX_ActiveContext();
    
    if(flag > GFXF_LAST_FLAG ||
	   context == NULL)
        return GFX_FAILURE;
    
    va_start(args, flag);
    
    result = GFX_InterfaceTable[flag][GFX_SET](args);
    
    va_end(args);
    
    return result;
}

#if GFX_DRAW_PIPELINE_ENABLED

GFX_Result GFX_DrawPixel(int32_t x, int32_t y)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Point p;
    GFX_Result res;
    
    ASSERT(context != NULL);

	if(context == NULL ||
       context->layer.active == NULL ||
       context->layer.active->locked == GFX_FALSE)
        return GFX_FAILURE;

    p.x = x;
    p.y = y;
    
    GFX_ActiveContext()->hal.drawLock();

    res = context->hal.drawPixel[context->draw.antialias](&p, &context->draw);
    
    GFX_ActiveContext()->hal.drawUnlock();
    
    return res;
}

GFX_Result GFX_DrawLine(int32_t x1,
                        int32_t y1,
                        int32_t x2,
                        int32_t y2)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Point p1, p2;
    GFX_Result res;

    ASSERT(context != NULL);

	if(context == NULL ||
       context->layer.active == NULL ||
       context->layer.active->locked == GFX_FALSE)
        return GFX_FAILURE;

    p1.x = x1;
    p1.y = y1;

    p2.x = x2;
    p2.y = y2;

    GFX_ActiveContext()->hal.drawLock();

    res = context->hal.drawLine[context->draw.mode]
                               [context->draw.antialias]
                               (&p1, &p2, &context->draw);
               
    GFX_ActiveContext()->hal.drawUnlock();
                               
    return res;
}

GFX_Result GFX_DrawRect(int32_t x,
                        int32_t y,
                        int32_t width,
                        int32_t height)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Rect rect;
    GFX_Result res;
   
    ASSERT(context != NULL);

	if(context == NULL ||
       context->layer.active == NULL ||
       context->layer.active->locked == GFX_FALSE)
        return GFX_FAILURE;

    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;

    GFX_ActiveContext()->hal.drawLock();

    res = context->hal.drawRect[context->draw.mode]
                               [context->draw.antialias]
                               (&rect, &context->draw);
               
    GFX_ActiveContext()->hal.drawUnlock();
                               
    return res;
}

GFX_Result GFX_DrawCircle(int32_t x,
                                        int32_t y,
                                        int32_t radius)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Point pt;
    GFX_Result res;
   
    ASSERT(context != NULL);

	if(context == NULL ||
       context->layer.active == NULL ||
       context->layer.active->locked == GFX_FALSE)
        return GFX_FAILURE;

    pt.x = x;
    pt.y = y;
    
    GFX_ActiveContext()->hal.drawLock();
    
    res = context->hal.drawCircle[context->draw.mode]
                                 [context->draw.antialias]
                                 (&pt, radius, &context->draw);
               
    GFX_ActiveContext()->hal.drawUnlock();
                                 
    return res;
}

GFX_Result GFX_DrawBlit(GFX_PixelBuffer* buffer,
                                      int32_t src_x,
                                      int32_t src_y,
                                      int32_t src_width,
                                      int32_t src_height,
                                      int32_t dest_x,
                                      int32_t dest_y)
{
    GFX_Context* context = GFX_ActiveContext();
    GFX_Rect src_rect;
    GFX_Point pnt;
    GFX_Result res;

    ASSERT(context != NULL && buffer != NULL);

	if(context == NULL ||
       context->layer.active == NULL ||
       context->layer.active->locked == GFX_FALSE)
        return GFX_FAILURE;

    src_rect.x = src_x;
    src_rect.y = src_y;
    src_rect.width = src_width;
    src_rect.height = src_height;

    pnt.x = dest_x;
    pnt.y = dest_y;

    GFX_ActiveContext()->hal.drawLock();

    res = context->hal.drawBlit(buffer, &src_rect, &pnt, &context->draw);
    
    GFX_ActiveContext()->hal.drawUnlock();
    
    return res;
}

#endif // GFX_DRAW_PIPELINE_ENABLED

GFX_Result GFX_HandleInterrupt(uint32_t id)
{
    GFX_Context* context = GFX_ActiveContext();
    
    ASSERT(context != NULL);
    
    if(context == NULL)
        return GFX_FAILURE;
        
    return context->hal.interrupt(id);
}