/********************************************************************************
  GFX NANO2D Driver Functions for Static Single Instance Driver

  Company:
    Microchip Technology Inc.

  File Name:
    drv_gfx_nano2D.c

  Summary:
    Source code for the GFX NANO2D driver static implementation.

  Description:
    This file contains the source code for the static implementation of the
    GFX NANO2D driver.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2016 released Microchip Technology Inc.  All rights reserved.

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

#include "framework/gfx/driver/processor/nano2d/drv_gfx_nano2d.h"
#include "framework/gfx/driver/processor/nano2d/libnano2D.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************

/*** @TODO Requires GFX2 Integration begin ***/

#define MAX_LAYER_COUNT 1
#define DISPLAY_WIDTH   ${CONFIG_DRV_GFX_DISPLAY_WIDTH}
#define DISPLAY_HEIGHT  ${CONFIG_DRV_GFX_DISPLAY_HEIGHT}
const char* DRIVER_GPU_NAME = "NANO2D";
static uint32_t supported_color_formats = GFX_COLOR_MASK_RGB_565;

/*** @TODO Requires GFX2 Integration end ***/

uint32_t state;


/**** Hardware Abstraction Interfaces ****/
enum
{
    INIT = 0,
    RUN
};

static int DRV_GFX_NANO2D_Start();

GFX_Context* cntxt;

// function that returns the information for this driver
GFX_Result driverNano2DInfoGet(GFX_DriverInfo* info)
{
        if(info == NULL)
        return GFX_FAILURE;

    // populate info struct
    strcpy(info->name, DRIVER_GPU_NAME);
    info->color_formats = supported_color_formats;
    info->layer_count = MAX_LAYER_COUNT;

    return GFX_SUCCESS;
}

static GFX_Result nano2DUpdate()
{
    GFX_Context* context = GFX_ActiveContext();

    if(context == NULL)
        return GFX_FAILURE;

    if(state == INIT)
    {
        if(DRV_GFX_NANO2D_Start() != 0)
            return GFX_FAILURE;

        state = RUN;
    }

    return GFX_SUCCESS;
}

static void nano2DDestroy(GFX_Context* context)
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
    
GFX_Result nano2DInitialize(GFX_Context* context)
{

    static n2d_module_parameters_t gpu_params;

    cntxt = context;

    // general default initialization
    if(defInitialize(context) == GFX_FAILURE)
            return GFX_FAILURE;

    // override default HAL functions with NANO2D specific implementations
    context->hal.update = &nano2DUpdate;
    context->hal.destroy = &nano2DDestroy;

    gpu_params.registerMemBase2D = 0xBF8EB000;
    gpu_params.contiguousBase = 0xA85DC000;
    gpu_params.baseAddress = 0;

    n2d_init_hardware(&gpu_params);

    /* open and initialize gpu software  */
    if (N2D_IS_ERROR(n2d_open()))
    {
        return GFX_FAILURE;
    }

    <#if CONFIG_DRV_GFX_DISPLAY_SYS_INIT_SCRIPT?has_content>
    ${CONFIG_DRV_GFX_DISPLAY_SYS_INIT_SCRIPT}
    </#if>

    return GFX_SUCCESS;
}

// function that initialized the driver context
GFX_Result driverNano2DContextInitialize(GFX_Context* context)
{
        // set driver-specific data initialization function address
        context->hal.initialize = &nano2DInitialize;

        // set driver-specific destroy function address
        context->hal.destroy = &nano2DDestroy;

        return GFX_SUCCESS;
}

/**** End Hardware Abstraction Interfaces ****/


static int DRV_GFX_NANO2D_Start()
{
    return 0;
}

/*******************************************************************************
 End of File
*/
