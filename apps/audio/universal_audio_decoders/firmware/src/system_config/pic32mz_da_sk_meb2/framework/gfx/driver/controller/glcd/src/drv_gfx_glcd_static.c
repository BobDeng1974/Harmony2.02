/********************************************************************************
  GFX GLCD Driver Functions for Static Single Instance Driver

  Company:
    Microchip Technology Inc.

  File Name:
    drv_gfx_glcd.c

  Summary:
    Source code for the GFX GLCD driver static implementation.

  Description:
    This file contains the source code for the static implementation of the
    GFX GLCD driver.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute Software
only when embedded on a Microchip microcontroller or digital  signal  controller
that is integrated into your product or third party  product  (pursuant  to  the
sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS  WITHOUT  WARRANTY  OF  ANY  KIND,
EITHER EXPRESS  OR  IMPLIED,  INCLUDING  WITHOUT  LIMITATION,  ANY  WARRANTY  OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A  PARTICULAR  PURPOSE.
IN NO EVENT SHALL MICROCHIP OR  ITS  LICENSORS  BE  LIABLE  OR  OBLIGATED  UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,  BREACH  OF  WARRANTY,  OR
OTHER LEGAL  EQUITABLE  THEORY  ANY  DIRECT  OR  INDIRECT  DAMAGES  OR  EXPENSES
INCLUDING BUT NOT LIMITED TO ANY  INCIDENTAL,  SPECIAL,  INDIRECT,  PUNITIVE  OR
CONSEQUENTIAL DAMAGES, LOST  PROFITS  OR  LOST  DATA,  COST  OF  PROCUREMENT  OF
SUBSTITUTE  GOODS,  TECHNOLOGY,  SERVICES,  OR  ANY  CLAIMS  BY  THIRD   PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE  THEREOF),  OR  OTHER  SIMILAR  COSTS.
*******************************************************************************/
//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "framework/gfx/driver/controller/glcd/drv_gfx_glcd_static.h"
#include "framework/gfx/driver/processor/nano2d/drv_gfx_nano2d.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************

/*** @TODO Requires GFX2 Integration begin ***/

/*** GLCD Driver Configuration ***/
#define  GFX_USE_DISPLAY_CONTROLLER_GLCD
#define  GFX_GLCD_CONFIG_CONTROL                       0xC0000000
#define  GFX_GLCD_BACKGROUND_COLOR                     0xFFFFFF00
#define  GFX_GLCD_LAYERS                               3
/*** GLCD Layer 0 Configuration ***/
#define  GFX_GLCD_LAYER0_BASEADDR                      0xA8000000
#define  GFX_GLCD_LAYER0_DBL_BASEADDR                  0xA8465000
#define  GFX_GLCD_LAYER0_RES_X                         480
#define  GFX_GLCD_LAYER0_RES_Y                         272
#define  GFX_GLCD_LAYER0_START_X                       0
#define  GFX_GLCD_LAYER0_START_Y                       0
#define  GFX_GLCD_LAYER0_COLORSPACE                    GLCD_LAYER_COLOR_MODE_RGBA8888
/*** GLCD Layer 1 Configuration ***/
#define  GFX_GLCD_LAYER1_BASEADDR                      0xA8177000
#define  GFX_GLCD_LAYER1_DBL_BASEADDR                  0xA85DC000
#define  GFX_GLCD_LAYER1_RES_X                         480
#define  GFX_GLCD_LAYER1_RES_Y                         272
#define  GFX_GLCD_LAYER1_START_X                       0
#define  GFX_GLCD_LAYER1_START_Y                       0
#define  GFX_GLCD_LAYER1_COLORSPACE                    GLCD_LAYER_COLOR_MODE_RGBA8888
/*** GLCD Layer 2 Configuration ***/
#define  GFX_GLCD_LAYER2_BASEADDR                      0xA82EE000
#define  GFX_GLCD_LAYER2_DBL_BASEADDR                  0xA8753000
#define  GFX_GLCD_LAYER2_RES_X                         480
#define  GFX_GLCD_LAYER2_RES_Y                         272
#define  GFX_GLCD_LAYER2_START_X                       0
#define  GFX_GLCD_LAYER2_START_Y                       0
#define  GFX_GLCD_LAYER2_COLORSPACE                    GLCD_LAYER_COLOR_MODE_RGBA8888

#define MAX_LAYER_COUNT 1
#define DISPLAY_WIDTH   480
#define DISPLAY_HEIGHT  272
const char* DRIVER_NAME = "GLCD";
static uint32_t supported_color_formats = GFX_COLOR_MASK_RGB_565;
uint16_t * frameBuffer[MAX_LAYER_COUNT];

/*** @TODO Requires GFX2 Integration end ***/

uint32_t state;

//Layer Parameters
//--------------------------------------------------------------------------
typedef struct __display_layer {
    uint16_t  *baseaddr[2];
    int        draw;
    int        frame;
    uint32_t   resx;
    uint32_t   resy;
    uint32_t   buscfg;
    uint32_t   format;
    uint32_t   stride;
    uint32_t   startx;
    uint32_t   starty;
    uint32_t   sizex;
    uint32_t   sizey;
    uint32_t   alpha;
    uint32_t   dblend;
    uint32_t   sblend;
    uint32_t   colorspace;
    uint16_t  color;
} DISPLAY_LAYER;
static DISPLAY_LAYER layer[GLCD_LAYER_ID_MAX];


/**** Hardware Abstraction Interfaces ****/
enum
{
    INIT = 0,
    RUN
};

static int DRV_GFX_GLCD_Start();

GFX_Context* cntxt;

// function that returns the information for this driver
GFX_Result driverGLCDInfoGet(GFX_DriverInfo* info)
{
        if(info == NULL)
        return GFX_FAILURE;

        // populate info struct
    strcpy(info->name, DRIVER_NAME);
    info->color_formats = supported_color_formats;
    info->layer_count = MAX_LAYER_COUNT;

    return GFX_SUCCESS;
}

static GFX_Result glcdUpdate()
{
    GFX_Context* context = GFX_ActiveContext();

    if(context == NULL)
        return GFX_FAILURE;

    if(state == INIT)
    {
        if(DRV_GFX_GLCD_Start() != 0)
            return GFX_FAILURE;

        state = RUN;
    }

    return GFX_SUCCESS;
}

static void glcdDestroy(GFX_Context* context)
{
        // driver specific shutdown tasks
        if(context->driver_data != GFX_NULL)
        {
                context->memory.free(context->driver_data);
                context->driver_data = GFX_NULL;
        }

        // general default shutdown
        defDestroy(context);
}

static GFX_Result layerBufferCountSet(uint32_t count)
{
    count = count;

    return GFX_FAILURE;
}

static GFX_Result layerBufferAddressSet(uint32_t idx, GFX_Buffer address)
{
    idx = 0;
    address = address;

    return GFX_FAILURE;
}

static GFX_Result layerBufferAllocate(uint32_t idx)
{
    idx = 0;

    return GFX_FAILURE;
}

static GFX_Result layerBufferFree(uint32_t idx)
{
    idx = 0;

    return GFX_FAILURE;
}
    
static GFX_Result glcdInitialize(GFX_Context* context)
{
    uint32_t      modeReg;
    uint32_t      xResolution;
    uint32_t      yResolution;
    uint32_t      rightMargin;
    uint32_t      lowerMargin;
    uint32_t      hsyncLength;
    uint32_t      vsyncLength;
    uint32_t      leftMargin;
    uint32_t      upperMargin;

    uint32_t i, j;

    cntxt = context;

    // general default initialization
    if(defInitialize(context) == GFX_FAILURE)
            return GFX_FAILURE;

    // override default HAL functions with GLCD specific implementations
    context->hal.update = &glcdUpdate;
    context->hal.destroy = &glcdDestroy;
    context->hal.layerBufferCountSet = &layerBufferCountSet;
    context->hal.layerBufferAddressSet = &layerBufferAddressSet;
    context->hal.layerBufferAllocate = &layerBufferAllocate;


    /* set temporary information */
    xResolution     = context->display_info->rect.width;
    yResolution     = context->display_info->rect.height;
    rightMargin     = context->display_info->attributes.horz.front_porch;
    leftMargin      = context->display_info->attributes.horz.back_porch;
    hsyncLength     = context->display_info->attributes.horz.pulse_width;
    vsyncLength     = context->display_info->attributes.vert.pulse_width;
    upperMargin     = context->display_info->attributes.vert.back_porch;
    lowerMargin     = context->display_info->attributes.vert.front_porch;

    /* glcd initialization */
    PLIB_GLCD_Disable(GLCD_ID_0);
    PLIB_GLCD_BackgroundColorSet(GLCD_ID_0, GFX_GLCD_BACKGROUND_COLOR);
    PLIB_GLCD_VSyncInterruptEnable(GLCD_ID_0);
    PLIB_GLCD_RGBSequentialModeSet(GLCD_ID_0, 1<<31);
 
    PLIB_GLCD_FrontPorchXYSet(GLCD_ID_0, xResolution + rightMargin, yResolution + lowerMargin);
    PLIB_GLCD_BlankingXYSet(GLCD_ID_0, xResolution + rightMargin + hsyncLength, yResolution + lowerMargin + vsyncLength);
    PLIB_GLCD_BackPorchXYSet(GLCD_ID_0, xResolution + rightMargin + hsyncLength + leftMargin, yResolution + lowerMargin + vsyncLength + upperMargin);
    PLIB_GLCD_ClockDividerSet(GLCD_ID_0, 4);
    PLIB_GLCD_ResolutionXYSet(GLCD_ID_0, xResolution, yResolution);


    PLIB_GLCD_Enable(GLCD_ID_0);   

/*** @TODO Requires GFX2 Integration begin
 . only supports two layers at fixed addresses
 . layer is not configurable
 . only supports 565
 . set for opaque
***/

    DISPLAY_LAYER layer;
    frameBuffer[0] = (uint16_t*)0xA8000000;
    frameBuffer[1] = (uint16_t*)0xA8177000;

    // initialize all layer color modes
    for(i = 0; i < MAX_LAYER_COUNT; i++)
    {      
        GFX_PixelBufferCreate(DISPLAY_WIDTH,
                  DISPLAY_HEIGHT,
                  GFX_COLOR_MODE_RGB_565,
                  frameBuffer[i],
                  &context->layer.layers[i].buffers[i].pb);

        context->layer.layers[i].buffers[i].state = GFX_BS_MANAGED;

        layer.baseaddr[i] = frameBuffer[i];

        layer.resx       = DISPLAY_WIDTH;
        layer.resy       = DISPLAY_HEIGHT;
        layer.startx     = 0;
        layer.starty     = 0;
        layer.sizex      = layer.resx;
        layer.sizey      = layer.resy;
        layer.alpha      = 0xFF;
        layer.dblend     = GLCD_LAYER_DEST_BLEND_BLACK;
        layer.sblend     = GLCD_LAYER_SRC_BLEND_WHITE;
        layer.colorspace = GLCD_LAYER_COLOR_MODE_RGB565;

        PLIB_GLCD_LayerBaseAddressSet(GLCD_ID_0, i, (uint32_t)layer.baseaddr[i]);
        PLIB_GLCD_LayerStrideSet(GLCD_ID_0, i, layer.resx*4 );
        PLIB_GLCD_LayerResXYSet( GLCD_ID_0, i, layer.resx, layer.resy );
        PLIB_GLCD_LayerStartXYSet( GLCD_ID_0, i, layer.startx, layer.starty );
        PLIB_GLCD_LayerSizeXYSet( GLCD_ID_0, i, layer.sizex, layer.sizey);
        PLIB_GLCD_LayerGlobalAlphaSet( GLCD_ID_0, i, layer.alpha);
        PLIB_GLCD_LayerDestBlendFuncSet(GLCD_ID_0, i, layer.dblend );
        PLIB_GLCD_LayerSrcBlendFuncSet(GLCD_ID_0, i, layer.sblend );
        PLIB_GLCD_LayerColorModeSet(GLCD_ID_0, i, layer.colorspace );
        PLIB_GLCD_LayerEnable(GLCD_ID_0, i);

    /*** @TODO Requires GFX2 Integration end ***/

        /* initialize gpu hardware and peripheral software */
        nano2DInitialize(context);

    }

    return GFX_SUCCESS;
}

// function that initialized the driver context
GFX_Result driverGLCDContextInitialize(GFX_Context* context)
{
        // set driver-specific data initialization function address
        context->hal.initialize = &glcdInitialize;

        // set driver-specific destroy function address
        context->hal.destroy = &glcdDestroy;

        return GFX_SUCCESS;
}

/**** End Hardware Abstraction Interfaces ****/


static int DRV_GFX_GLCD_Start()
{
    return 0;
}


/*

void  DRV_GFX_GLCD_BackgroundColorSet(uint32_t bgColor)
{
    PLIB_GLCD_BackgroundColorSet(GLCD_ID_0, bgColor);
}

void DRV_GFX_GLCD_LayerAlphaSet(uint8_t alpha)
{
    PLIB_GLCD_LayerGlobalAlphaSet( GLCD_ID_0, 0, alpha);
}

void DRV_GFX_GLCD_LayerDestBlendSet(GLCD_LAYER_DEST_BLEND_FUNC blend)
{
    PLIB_GLCD_LayerDestBlendFuncSet(GLCD_ID_0, 0, blend );
}

void DRV_GFX_GLCD_LayerSrcBlendSet(GLCD_LAYER_SRC_BLEND_FUNC blend)
{
    PLIB_GLCD_LayerSrcBlendFuncSet(GLCD_ID_0, 0, blend );
}

void DRV_GFX_GLCD_LayerColorSpaceSet(GLCD_LAYER_COLOR_MODE colorSpace)
{
    PLIB_GLCD_LayerColorModeSet(GLCD_ID_0, 0, colorSpace );
}

void DRV_GFX_GLCD_LayerEnableSet(bool enable)
{
    if ( enable )
    {
        PLIB_GLCD_LayerEnable(GLCD_ID_0, 0);
    } else {
        PLIB_GLCD_LayerDisable(GLCD_ID_0, 0 );
    }
}

void DRV_GFX_GLCD_LayerModeSet(uint32_t layerMode)
{
    if ( layerMode & GLCD_LAYER_ENABLE )
    {
        PLIB_GLCD_LayerEnable(GLCD_ID_0, 0 );
    } else {
        PLIB_GLCD_LayerDisable(GLCD_ID_0, 0 );
    }
}

void DRV_GFX_GLCD_LayerFrameBufferSet(uint32_t * frame)
{
    PLIB_GLCD_LayerBaseAddressSet(GLCD_ID_0, 0, (uint32_t)drvGLCDObj.layer[0].baseaddr[0]);
}

void  DRV_GFX_GLCD_CursorSetPosition(uint32_t x, uint32_t y, bool enable)
{
    if ( enable )
    {
        PLIB_GLCD_CursorEnable(GLCD_ID_0);
        PLIB_GLCD_CursorXYSet(GLCD_ID_0, x, y);
    } else {
        PLIB_GLCD_CursorDisable(GLCD_ID_0);
    }
}

void  DRV_GFX_GLCD_CursorImageSet(uint32_t * cursorImage)
{
    int addr;
    int mask;
    int shift;
    int x, y;
    int color;
    uint32_t cursorData[128];

    for(x=0;x<32;x++)
        for(y=0;y<32;y++)
        {
            color = cursorImage[y*32+x] & 0xf;
            shift = (x*4);
            addr  = (y*4)+(x>>3);
            mask  = (0xf << shift);
            cursorData[addr] = (cursorData[addr] & ~mask) | (mask & (color << (shift) ));
        }

    PLIB_GLCD_CursorDataSet(GLCD_ID_0, cursorData );
}

void  DRV_GFX_GLCD_CursorPaletteSet(uint32_t * cursorPalette)
{
    PLIB_GLCD_CursorLUTSet( 0, cursorPalette );
}

void  DRV_GFX_GLCD_GammaPaletteSet(uint32_t * gammaPalette)
{
    PLIB_GLCD_GlobalColorLUTSet( 0, gammaPalette );
}
*/

/*******************************************************************************
 End of File
*/
