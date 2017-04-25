<#macro MACRO_HSYNC_OFF><#if CONFIG_DRV_GFX_DISPLAY_HSYNC_NEGATIVE_POLARITY == true>BSP_LCD_HSYNCOn();<#else>BSP_LCD_HSYNCOff();</#if></#macro>
<#macro MACRO_HSYNC_ON><#if CONFIG_DRV_GFX_DISPLAY_HSYNC_NEGATIVE_POLARITY == true>BSP_LCD_HSYNCOff();<#else>BSP_LCD_HSYNCOn();</#if></#macro>
<#macro MACRO_VSYNC_OFF><#if CONFIG_DRV_GFX_DISPLAY_VSYNC_NEGATIVE_POLARITY == true>BSP_LCD_VSYNCOn();<#else>BSP_LCD_VSYNCOff();</#if></#macro>
<#macro MACRO_VSYNC_ON><#if CONFIG_DRV_GFX_DISPLAY_VSYNC_NEGATIVE_POLARITY == true>BSP_LCD_VSYNCOff();<#else>BSP_LCD_VSYNCOn();</#if></#macro>
<#macro MACRO_DE_OFF><#if CONFIG_DRV_GFX_DISPLAY_DATA_ENABLE_POSITIVE_POLARITY == true>BSP_LCD_DEOn();<#else>BSP_LCD_DEOff();</#if></#macro>
<#macro MACRO_DE_ON><#if CONFIG_DRV_GFX_DISPLAY_DATA_ENABLE_POSITIVE_POLARITY == true>BSP_LCD_DEOff();<#else>BSP_LCD_DEOn();</#if></#macro>
<#macro MACRO_RESET_OFF><#if CONFIG_DRV_GFX_DISPLAY_RESET_POSITIVE_POLARITY == true>BSP_LCD_RESETOn();<#else>BSP_LCD_RESETOff();</#if></#macro>
<#macro MACRO_RESET_ON><#if CONFIG_DRV_GFX_DISPLAY_RESET_POSITIVE_POLARITY == true>BSP_LCD_RESETOff();<#else>BSP_LCD_RESETOn();</#if></#macro>
<#macro MACRO_CS_OFF><#if CONFIG_DRV_GFX_DISPLAY_CHIP_SELECT_POSITIVE_POLARITY == true>BSP_LCD_CSOff();<#else>BSP_LCD_CSOn();</#if></#macro>
<#macro MACRO_CS_ON><#if CONFIG_DRV_GFX_DISPLAY_CHIP_SELECT_POSITIVE_POLARITY == true>BSP_LCD_CSOn();<#else>BSP_LCD_CSOff();</#if></#macro>
/*******************************************************************************
  MPLAB Harmony LCC Generated Driver Implementation File

  File Name:
    drv_gfx_lcc_generic.c

  Summary:
    Build-time generated implementation for the LCC Driver.

  Description:
    Build-time generated implementation for the LCC Driver.

    Created with MPLAB Harmony Version ${CONFIG_MPLAB_HARMONY_VERSION_STRING}
*******************************************************************************/
// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2016 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#include "framework/gfx/driver/controller/lcc/drv_gfx_lcc_generic.h"

#include <xc.h>
#include <sys/attribs.h>

#include "peripheral/pmp/plib_pmp.h"
#include "peripheral/tmr/plib_tmr.h"
<#if CONFIG_PIC32MX == false && CONFIG_DRV_GFX_LCC_DMA_BUFFER_SIZE_MODE == "Large Buffer">
#include "peripheral/ebi/plib_ebi.h"
</#if>

<#if CONFIG_DRV_GFX_USE_LCC_PALETTE == true>
#include "gfx/gfx_palette.h"
uint16_t LUT[256];
</#if>

#ifndef PMADDR_OVERFLOW
#define  PMADDR_OVERFLOW               65536
#endif
static void vsyncSwap(void);
static GFX_Result recoverData(void);
static GFX_Result saveData(void);

static GFX_Color  pixelGet(const GFX_PixelBuffer* buffer,
                           const GFX_Point* pnt);
                       
static GFX_Result pixelSet(const GFX_PixelBuffer* buffer,
                           const GFX_Point* pnt,
                           GFX_Color color); 

<#if CONFIG_DRV_GFX_LCC_DMA_WRITE_STRATEGY == "Draw Count Limited">
#define PIXEL_DRAW_PER_DMA_TX          ${CONFIG_USE_DRV_GFX_LCC_DRAW_COUNT_PER_TX}
volatile uint8_t DrawCount = 0;        /* The current status of how many pixels have been drawn inbetween a DMA IR*/
</#if>
volatile uint8_t overflowcount;        /* The count for the amount of overflows that have happened in the PMP Adress*/

#define SRAM_ADDR_CS0  0xE0000000
<#if CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "WQVGA or lower">
#define SRAM_ADDR_CS1  0xE0040000
<#elseif CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "HVGA">
#define SRAM_ADDR_CS1  0xE0060000
<#elseif CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "VGA">
#define SRAM_ADDR_CS1  0xE00A0000
<#elseif CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "WVGA">
#define SRAM_ADDR_CS1  0xE00C0000
</#if>

//#define VER_BLANK                 (DISP_VER_PULSE_WIDTH+DISP_VER_BACK_PORCH+DISP_VER_FRONT_PORCH-1)


static SYS_DMA_CHANNEL_HANDLE dmaHandle = SYS_DMA_CHANNEL_HANDLE_INVALID;

<#if CONFIG_PIC32MX == true>
#define PMP_ADDRESS_LINES 0x7fff
<#else>
#define PMP_ADDRESS_LINES 0xffff
</#if>

<#if CONFIG_DRV_GFX_DISPLAY_DATA_WIDTH == "8">
#define PMP_DATA_LENGTH PMP_DATA_SIZE_8_BITS
<#elseif CONFIG_DRV_GFX_DISPLAY_DATA_WIDTH == "16">
#define PMP_DATA_LENGTH PMP_DATA_SIZE_16_BITS 
</#if>

#define MAX_LAYER_COUNT 1
<#if CONFIG_DRV_GFX_LCC_BUFFER_MODE == "Double Buffer">
#define BUFFER_COUNT    2
<#else>
#define BUFFER_COUNT    1
</#if>
#define DISPLAY_WIDTH   ${CONFIG_DRV_GFX_DISPLAY_WIDTH}
#define DISPLAY_HEIGHT  ${CONFIG_DRV_GFX_DISPLAY_HEIGHT}

uint16_t GraphicsFrame[DISPLAY_WIDTH];

const char* DRIVER_NAME = "LCC";
static uint32_t supported_color_formats = GFX_COLOR_MASK_RGB_565;

uint32_t state;

#define DRV_GFX_LCC_DMA_CHANNEL_INDEX     ${CONFIG_DRV_GFX_LCC_DMA_CHANNEL_INDEX}
#define DRV_GFX_LCC_DMA_TRIGGER_SOURCE    ${CONFIG_DRV_GFX_LCC_DMA_TRIGGER_SOURCE}
#define DRV_GFX_LCC_TMR_INDEX             ${CONFIG_DRV_GFX_LCC_TMR_INDEX}
#define DRV_GFX_LCC_DMA_TRANSFER_LENGTH   2

//volatile uint16_t _pixelRendercount;
//volatile uint16_t* _framePoint;
//volatile uint32_t _frameAddress;

//volatile bool allowFrameUpdate = false;
//volatile bool allowLineUpdate = false;


/**** Hardware Abstraction Interfaces ****/
enum
{
    INIT = 0,
    RUN
};

static int DRV_GFX_LCC_Start();

GFX_Context* cntxt;

uint16_t HBackPorch;
uint32_t VER_BLANK;

uint32_t DISP_HOR_FRONT_PORCH;
uint32_t DISP_HOR_RESOLUTION;
uint32_t DISP_HOR_BACK_PORCH;
uint32_t DISP_HOR_PULSE_WIDTH;

uint32_t DISP_VER_FRONT_PORCH;
uint32_t DISP_VER_RESOLUTION;
uint32_t DISP_VER_BACK_PORCH;
uint32_t DISP_VER_PULSE_WIDTH;

int16_t line = 0;
uint32_t offset = 0;
uint16_t pixels = 0;
uint32_t hSyncs = 0;
    
uint32_t vsyncPeriod = 0;
uint32_t vsyncPulseDown = 0;
uint32_t vsyncPulseUp = 0;
uint32_t vsyncEnd = 0;

volatile bool allowFrameUpdate = false;
volatile bool allowLineUpdate = false;

uint16_t HBackPorch;

// function that returns the information for this driver
GFX_Result driverLCCInfoGet(GFX_DriverInfo* info)
{
	if(info == NULL)
        return GFX_FAILURE;

	// populate info struct
    strcpy(info->name, DRIVER_NAME);
    info->color_formats = supported_color_formats;
    info->layer_count = MAX_LAYER_COUNT;
    
    return GFX_SUCCESS;
}

static GFX_Result lccUpdate()
{
    GFX_Context* context = GFX_ActiveContext();
   
    if(context == NULL)
        return GFX_FAILURE;
    
    if(state == INIT)
    {
        if(DRV_GFX_LCC_Start() != 0)
            return GFX_FAILURE;
        
        state = RUN;
    }
    
    return GFX_SUCCESS;
}

static void lccDestroy(GFX_Context* context)
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

static GFX_Result lccInitialize(GFX_Context* context)
{
	cntxt = context;
	
	// general default initialization
	if(defInitialize(context) == GFX_FAILURE)
		return GFX_FAILURE;	
		
	// override default HAL functions with LCC specific implementations
    context->hal.update = &lccUpdate;
    context->hal.destroy = &lccDestroy;
	context->hal.layerBufferCountSet = &layerBufferCountSet;
    context->hal.layerBufferAddressSet = &layerBufferAddressSet;
    context->hal.layerBufferAllocate = &layerBufferAllocate;
	context->hal.drawLock = &saveData;
	context->hal.drawUnlock = &recoverData;
	context->hal.pixelGet = &pixelGet;
	context->hal.pixelSet = &pixelSet;
	context->layer.layers[0].vsync = GFX_TRUE;
	
	// driver specific initialization tasks	
	// initialize all layer color modes
    GFX_PixelBufferCreate(DISPLAY_WIDTH,
                          DISPLAY_HEIGHT,
                          GFX_COLOR_MODE_RGB_565,
                          (void*)SRAM_ADDR_CS0,
                          &context->layer.layers[0].buffers[0].pb);
            
    context->layer.layers[0].buffers[0].state = GFX_BS_MANAGED;
	
	if(BUFFER_COUNT == 2)
	{
		GFX_PixelBufferCreate(DISPLAY_WIDTH,
							  DISPLAY_HEIGHT,
							  GFX_COLOR_MODE_RGB_565,
							  (void*)SRAM_ADDR_CS1,
							  &context->layer.layers[0].buffers[1].pb);
				
		context->layer.layers[0].buffers[1].state = GFX_BS_MANAGED;
	}
	
	VER_BLANK = context->display_info->attributes.vert.pulse_width +
	            context->display_info->attributes.vert.back_porch +
				context->display_info->attributes.vert.front_porch - 1;
	
	HBackPorch = context->display_info->attributes.horz.pulse_width +
	             context->display_info->attributes.horz.back_porch;
	
	DISP_HOR_FRONT_PORCH = context->display_info->attributes.horz.front_porch;
	DISP_HOR_RESOLUTION = DISPLAY_WIDTH;
	DISP_HOR_BACK_PORCH = context->display_info->attributes.horz.back_porch;
	DISP_HOR_PULSE_WIDTH = context->display_info->attributes.horz.pulse_width;
	
	DISP_VER_FRONT_PORCH = context->display_info->attributes.vert.front_porch;
	DISP_VER_RESOLUTION = DISPLAY_HEIGHT;
	DISP_VER_BACK_PORCH = context->display_info->attributes.vert.back_porch;
	DISP_VER_PULSE_WIDTH = context->display_info->attributes.vert.pulse_width;

<#if CONFIG_DRV_GFX_LCC_REFRESH_STRATEGY == "Conventional">
	vsyncPeriod = DISP_VER_FRONT_PORCH + DISP_VER_RESOLUTION + DISP_VER_BACK_PORCH;
	
</#if>
<#if CONFIG_DRV_GFX_DISPLAY_SYS_INIT_SCRIPT?has_content>
	${CONFIG_DRV_GFX_DISPLAY_SYS_INIT_SCRIPT}
	
</#if>
<#if CONFIG_DRV_GFX_DISPLAY_USE_RESET == true>
	{<@MACRO_RESET_OFF/>}
	
</#if>
<#if CONFIG_DRV_GFX_DISPLAY_USE_CHIP_SELECT == true>
	{<@MACRO_CS_ON/>}
	
</#if>
    /* Disable the PMP module */
    PLIB_PMP_Disable(0);

    PLIB_PMP_OperationModeSelect(0, PMP_MASTER_READ_WRITE_STROBES_INDEPENDENT);

    /* pins polarity setting */
    PLIB_PMP_ReadWriteStrobePolaritySelect(0, 1 - ((cntxt->display_info->attributes.inv_left_shift)));
    PLIB_PMP_WriteEnableStrobePolaritySelect(0, PMP_POLARITY_ACTIVE_LOW);

    PLIB_PMP_ReadWriteStrobePortEnable(0);
    PLIB_PMP_WriteEnableStrobePortEnable(0);

    PLIB_PMP_DataSizeSelect(0, PMP_DATA_LENGTH);

    /* wait states setting */
    PLIB_PMP_WaitStatesDataHoldSelect(0, PMP_DATA_HOLD_1);
    PLIB_PMP_WaitStatesDataSetUpSelect(0, PMP_DATA_WAIT_ONE);
    PLIB_PMP_WaitStatesStrobeSelect(0, PMP_STROBE_WAIT_3);

    /* setting the hardware for the required interrupt mode */
    PLIB_PMP_InterruptModeSelect(0, PMP_INTERRUPT_EVERY_RW_CYCLE);

    PLIB_PMP_AddressIncrementModeSelect(0, PMP_ADDRESS_AUTO_INCREMENT);

    /* Enable the PMP module */
    PLIB_PMP_Enable(0);
    /* Ports Setting */
    PLIB_PMP_AddressPortEnable(0, PMP_ADDRESS_LINES);
    PLIB_PMP_AddressSet(0, 0);

<#if CONFIG_PIC32MX == true>
#ifdef BSP_SRAM_A15Off
    BSP_SRAM_A15Off();
#endif
<#else>
    BSP_SRAM_A16Off();
    BSP_SRAM_A17Off();
    BSP_SRAM_A18Off();

<#if CONFIG_USE_DRV_GFX_LCC_EXTERNAL_MEMORY_ADDRESS_19 == true>
    BSP_SRAM_A19Off();
</#if>

<#if CONFIG_PIC32MX == false && CONFIG_DRV_GFX_LCC_DMA_BUFFER_SIZE_MODE == "Large Buffer">
    PLIB_EBI_WriteOutputControlSet(EBI_ID_0, true, false);
    PLIB_EBI_DataEnableSet(EBI_ID_0, true, true);
    PLIB_EBI_BaseAddressSet(EBI_ID_0, 0, 0x20000000);
    PLIB_EBI_MemoryCharacteristicsSet(EBI_ID_0, 0, ${CONFIG_DRV_GFX_LCC_EXTERNAL_MEMORY_TYPE}, ${CONFIG_DRV_GFX_LCC_EXTERNAL_MEMORY_SIZE}, CS_TIMING_0);
    PLIB_EBI_MemoryTimingConfigSet(EBI_ID_0, ${CONFIG_DRV_GFX_LCC_EXTERNAL_MEMORY_CHIP_SELECT}, 0, 0, 0, 0, 0, 1);
    PLIB_EBI_StaticMemoryWidthRegisterSet(EBI_ID_0, 0, ${CONFIG_DRV_GFX_LCC_EXTERNAL_MEMORY_WIDTH});
    PLIB_EBI_FlashPowerDownModeSet(EBI_ID_0, true);
</#if>
</#if>

    /*Turn Backlight on*/
<#if CONFIG_DRV_GFX_DISPLAY_BACKLIGHT_ENABLE_LEVEL == "1">
    BSP_LCD_BACKLIGHTOn();
<#else>
    BSP_LCD_BACKLIGHTOff();
</#if>

	return GFX_SUCCESS;
}

// function that initialized the driver context
GFX_Result driverLCCContextInitialize(GFX_Context* context)
{
	// set driver-specific data initialization function address
	context->hal.initialize = &lccInitialize; 
	
	// set driver-specific destroy function address
    context->hal.destroy = &lccDestroy;
	
	return GFX_SUCCESS;
}

static int DRV_GFX_LCC_Start()
{
	/*Suspend DMA Module*/
    SYS_DMA_Suspend();
	
    /* Allocate DMA channel */
    dmaHandle = SYS_DMA_ChannelAllocate(DRV_GFX_LCC_DMA_CHANNEL_INDEX);
    
	if (SYS_DMA_CHANNEL_HANDLE_INVALID == dmaHandle)
        return -1;
		
    // set the transfer parameters: source & destination address,
    // source & destination size, number of bytes per event
    SYS_DMA_ChannelTransferAdd(dmaHandle, (void *) &PMDIN, 2, &GraphicsFrame[0],
    HBackPorch, DRV_GFX_LCC_DMA_TRANSFER_LENGTH);

<#if CONFIG_DRV_GFX_LCC_DMA_BUFFER_SIZE_MODE == "Large Buffer">
    /* Enable the transfer done interrupt, when all buffer transferred */
    PLIB_DMA_ChannelXINTSourceEnable(DMA_ID_0,
	                                 DRV_GFX_LCC_DMA_CHANNEL_INDEX,
                                     DMA_INT_BLOCK_TRANSFER_COMPLETE);

    SYS_INT_SourceEnable(INT_SOURCE_DMA_0 + DRV_GFX_LCC_DMA_CHANNEL_INDEX);

    // set the transfer event control: what event is to start the DMA transfer
    SYS_DMA_ChannelSetup(dmaHandle,
                         SYS_DMA_CHANNEL_OP_MODE_BASIC,
                         DRV_GFX_LCC_DMA_TRIGGER_SOURCE);

</#if>
    PLIB_TMR_PrescaleSelect(DRV_GFX_LCC_TMR_INDEX, ${CONFIG_DRV_GFX_LCC_TMR_PRESCALE_VALUE});
    PLIB_TMR_Period16BitSet(DRV_GFX_LCC_TMR_INDEX, 1);
    PLIB_TMR_Start(DRV_GFX_LCC_TMR_INDEX);

    // once we configured the DMA channel we can enable it
    SYS_DMA_ChannelEnable(dmaHandle);
	
	SYS_INT_VectorPrioritySet(INT_VECTOR_DMA1, INT_PRIORITY_LEVEL7);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_DMA1, INT_SUBPRIORITY_LEVEL0);

<#if CONFIG_DRV_GFX_DISPLAY_SYS_START_SCRIPT?has_content>
	${CONFIG_DRV_GFX_DISPLAY_SYS_START_SCRIPT}
</#if>
    /*Unsuspend DMA Module*/
    SYS_DMA_Resume();
	
	return GFX_SUCCESS;
}

<#if CONFIG_DRV_GFX_LCC_REFRESH_STRATEGY == "Conventional">
<#include "framework/gfx/driver/controller/lcc/templates/drv_gfx_lcc_external_refresh_conventional.ftl">
<#elseif CONFIG_DRV_GFX_LCC_REFRESH_STRATEGY == "Aggressive">
<#include "framework/gfx/driver/controller/lcc/templates/drv_gfx_lcc_external_refresh_aggressive.ftl">
</#if>

uint16_t prevaddr;

static GFX_Result saveData(void)
{
<#if CONFIG_USE_DRV_GFX_LCC_DMA_WRITE_STRATEGY_IN_BETWEEN_FRAME_AND_LINE == true>
    while ( allowFrameUpdate == false && allowLineUpdate == false ) ;
</#if>
<#if CONFIG_PIC32MX == true>
    while(DCH1CSIZ != 1);
</#if>
<#if CONFIG_DRV_GFX_LCC_DMA_WRITE_STRATEGY == "Draw Count Limited">
    while(DrawCount > PIXEL_DRAW_PER_DMA_TX);
</#if>
<#if CONFIG_PIC32MZ == true || CONFIG_PIC32MK == true>
<#if CONFIG_USE_DRV_GFX_LCC_DMA_WRITE_STRATEGY_IN_BETWEEN_FRAME_AND_LINE == true>
    PLIB_OSC_PBClockDivisorSet (OSC_ID_0, 7, 1);
</#if>
<#if CONFIG_DRV_GFX_LCC_DMA_WRITE_STRATEGY == "Draw Count Limited">
    PLIB_TMR_Stop(DRV_GFX_LCC_TMR_INDEX);
    while(PMMODEbits.BUSY == 1); //WAIT for DMA transfer to be suspended
</#if>
    CFGEBIA = 0x000fffff;
    CFGEBIC = 0x00002003;
<#elseif CONFIG_PIC32MX == true>
    DMACONbits.SUSPEND = 1;
    while(PMMODEbits.BUSY == 1); //WAIT for DMA transfer to be suspended
    //Perform Write
<#if CONFIG_PIC32MX == true>
#ifdef BSP_SRAM_A15StateSet
    BSP_SRAM_A15StateSet((_frameAddress >> 15)&0x1);
#endif
</#if>
    BSP_SRAM_A16StateSet((_frameAddress >> 16)&0x1);
    BSP_SRAM_A17StateSet((drvLCCObj.initData->activePage)&0x1);
    BSP_SRAM_A18StateSet((drvLCCObj.initData->activePage>>1)&0x1);

    //Save previous address value
    prevaddr = PMADDR;
    PMADDR = _frameAddress;
</#if>

	return GFX_SUCCESS;
}

static GFX_Result recoverData(void)
{
<#if CONFIG_PIC32MZ == true || CONFIG_PIC32MK == true>
    CFGEBIA = 0;
    CFGEBIC = 0;
<#if CONFIG_DRV_GFX_LCC_DMA_WRITE_STRATEGY == "Draw Count Limited">
    PLIB_TMR_Start(DRV_GFX_LCC_TMR_INDEX);
</#if>
<#if CONFIG_USE_DRV_GFX_LCC_DMA_WRITE_STRATEGY_IN_BETWEEN_FRAME_AND_LINE == true>
    PLIB_OSC_PBClockDivisorSet (OSC_ID_0, 7, 1);
</#if>
<#elseif CONFIG_PIC32MX == true>
    //Clean-up Address Lines
#ifdef BSP_SRAM_A15StateSet
    BSP_SRAM_A15StateSet((overflowcount)&0x1);          //count holds the additional address line count
    BSP_SRAM_A16StateSet((overflowcount>>1)&0x1);
#else
    BSP_SRAM_A16StateSet((overflowcount)&0x1);
#endif
    BSP_SRAM_A17StateSet((drvLCCObj.initData->visualPage)&0x1);
    BSP_SRAM_A18StateSet((drvLCCObj.initData->visualPage>>1)&0x1);
    PMADDR = prevaddr;
    DMACONbits.SUSPEND = 0;
</#if>
<#if CONFIG_DRV_GFX_LCC_DMA_WRITE_STRATEGY == "Draw Count Limited">
    DrawCount++;
</#if>

	return GFX_SUCCESS;
}

static GFX_Color  pixelGet(const GFX_PixelBuffer* buffer,
                           const GFX_Point* pnt)
{
	GFX_Color color;
	
<#if CONFIG_PIC32MZ == true || CONFIG_PIC32MK == true>
	color = GFX_PixelBufferGet(buffer, pnt);
<#elseif CONFIG_PIC32MX == true>
    color = PMDIN;
</#if>
	
	return color;
}
                       
static GFX_Result pixelSet(const GFX_PixelBuffer* buffer,
                           const GFX_Point* pnt,
                           GFX_Color color)
{
<#if CONFIG_PIC32MZ == true || CONFIG_PIC32MK == true>
	return GFX_PixelBufferSet(buffer, pnt, color);
<#elseif CONFIG_PIC32MX == true>
    PMDIN = color;
	return GFX_SUCCESS;
</#if>
}

<#if CONFIG_DRV_GFX_USE_LCC_PALETTE == true>
uint8_t DRV_GFX_PaletteSet(uint16_t *pPaletteEntry, uint16_t startEntry, uint16_t length)
{
    uint16_t counter;

    if((pPaletteEntry == NULL) || ((startEntry + length) > 256))
    {
        return -1;
    }

    for(counter = 0; counter < length; counter++)
    {
        LUT[counter]  = *pPaletteEntry++;
    }

    return 0;
}
</#if>

void vsyncSwap()
{
	// swap layer if necessary
	if(cntxt->layer.layers[0].swap == GFX_TRUE)
	{
		GFX_LayerSwap(&cntxt->layer.layers[0]);
		
		// clear new write layer if auto clear is set
		//if(cntxt->layer.layers[0].auto_clear == GFX_TRUE &&
		//   cntxt->layer.layers[0].buffer_write_idx != cntxt->layer.layers[0].buffer_read_idx)
		//	cntxt->layer.layers[0].color_clear();
	
<#if CONFIG_DRV_GFX_LCC_BUFFER_MODE == "Double Buffer">
		// set sram address pins for read buffer
		if(cntxt->layer.layers[0].buffer_read_idx == 0)
		{
<#if CONFIG_PIC32MX == false>
<#if CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "WQVGA or lower">
			BSP_SRAM_A17StateSet(0 & 0x1);
			BSP_SRAM_A18StateSet(0 >> 1 & 0x1);
<#elseif CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "HVGA">
<#elseif CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "VGA">
<#elseif CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "WVGA">
</#if>
</#if>
		}
		else
		{
<#if CONFIG_PIC32MX == false>
<#if CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "WQVGA or lower">
			BSP_SRAM_A17StateSet(1 & 0x1);
			BSP_SRAM_A18StateSet(1 >> 1 & 0x1);
<#elseif CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "HVGA">
<#elseif CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "VGA">
<#elseif CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "WVGA">
</#if>
</#if>
		}
</#if>		
		GFX_ActiveContext()->layer.active->swap = GFX_FALSE;
	}
}

void __ISR(_DMA0_VECTOR + DMA_CHANNEL_1, ipl7AUTO) _LCCRefreshISR(void)
{
    SYS_INT_SourceStatusClear(INT_SOURCE_DMA_0 + DMA_CHANNEL_1);
	
    DRV_GFX_LCC_DisplayRefresh();
}
