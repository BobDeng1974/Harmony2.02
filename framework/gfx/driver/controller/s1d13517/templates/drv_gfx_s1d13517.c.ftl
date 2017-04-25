/*******************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    drv_gfx_s1d13517.c

  Summary:

  Description:
    
*******************************************************************************/
//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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

#include "gfx/hal/inc/gfx_driver_interface.h"
#include "gfx/hal/inc/gfx_default_impl.h"

#include "framework/driver/pmp/drv_pmp_static.h"
#include "system/clk/sys_clk.h"

#include "gfx/driver/controller/s1d13517/drv_gfx_s1d13517_common.h"

#define MAX_LAYER_COUNT 1

static uint32_t supportedColorModes = GFX_COLOR_MASK_${CONFIG_DRV_GFX_S1D13517_COLOR_MODE};
//static GFX_ColorMode colorMode = GFX_COLOR_MODE_${CONFIG_DRV_GFX_S1D13517_COLOR_MODE};

const char* DRIVER_NAME = "S1D13517";

#define MIN_BRIGHTNESS    0
#define MAX_BRIGHTNESS    100

#define CLK_THRESHOLD     480 // don't know why this is set
#define INIT_DELAY_STAGE  11

enum
{
    INITITIALIZE = 0,
    RUN
};

static void initializeHardware();

static GFX_Result brightnessRangeGet(uint32_t* low, uint32_t* high);
static GFX_Result brightnessSet(uint32_t val);

static GFX_Result vsyncSet(GFX_Bool enable);
static GFX_Result vsyncCallbackSet(GFX_SyncCallback_FnPtr cb);
static GFX_Result hsyncCallbackSet(GFX_SyncCallback_FnPtr cb);

static GFX_Result orientationSet(GFX_Orientation ori);
static GFX_Result mirroringSet(GFX_Bool mirr);

static GFX_Result layerActiveSet(uint32_t idx);
static GFX_Result layerEnabledSet(GFX_Bool val);

static GFX_Result layerPositionSet(int32_t x, int32_t y);
static GFX_Result layerSizeSet(int32_t width, int32_t height);

static GFX_Result layerBufferCountSet(uint32_t count);
static GFX_Result layerBufferAddressSet(uint32_t idx, GFX_Buffer address);

static GFX_Result layerBufferCoherentSet(uint32_t idx, GFX_Bool coherent);
static GFX_Result layerBufferAllocate(uint32_t idx);
static GFX_Result layerBufferFree(uint32_t idx);

static GFX_Result layerVisibleSet(GFX_Bool value);
static GFX_Result layerSwapSet(GFX_Bool value);

static GFX_Result layerColorModeSet(GFX_ColorMode mode);
static GFX_Result layerAlphaEnableSet(GFX_Bool enable);
static GFX_Result layerMaskEnableSet(GFX_Bool enable);
static GFX_Result layerMaskColorSet(GFX_Color clr);

static GFX_Color  pixelGet(GFX_BufferSelection,
                           GFX_Point*,
                           GFX_ColorMode);
						   
static GFX_Result pixelArrayGet(GFX_BufferSelection target,
                                GFX_Rect* rect,
                                GFX_PixelBuffer* buffer);
								
static GFX_Result drawPixel(GFX_Point* pnt, GFX_DrawState* state);					
								
static void writePixel565(GFX_Color clr);
static void writePixel888(GFX_Color clr);

static void setupWriteWindow(GFX_Context* context,
                             int16_t x,
                             int16_t y,
                             uint16_t count,
                             uint16_t lines);
static void drawEmptyPixels(S1D13517DriverData* data, uint32_t count);

static void _DELAY(int ms)
{
    uint32_t start = _CP0_GET_COUNT();
    uint32_t end = start + SYS_CLK_SystemFrequencyGet() / 1000 / 2 * ms;
    if (end > start)
    {
        while (_CP0_GET_COUNT() < end);
    }
    else
    {
        while (_CP0_GET_COUNT() > start || _CP0_GET_COUNT() < end);
    }
}

static void destroy(GFX_Context* context)
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

static GFX_Result initialize(GFX_Context* context)
{
	S1D13517DriverData* data = context->driver_data;
	uint32_t i;
	
	// initialize all layers
    for(i = 0; i < context->layer.count; i++)
    {
        context->layer.layers[i].enabled = GFX_TRUE;
		context->layer.layers[i].visible = GFX_TRUE;

		context->layer.layers[i].swap = GFX_FALSE;
    
        context->layer.layers[i].rect.local.x = 0;
        context->layer.layers[i].rect.local.y = 0;
        context->layer.layers[i].rect.local.width = context->display_info->rect.width;
        context->layer.layers[i].rect.local.height = context->display_info->rect.height;

        context->layer.layers[i].rect.display = context->layer.layers[i].rect.local;

		context->layer.layers[i].alphaEnable = GFX_FALSE;
        context->layer.layers[i].alphaAmount = 255;
        
        context->layer.layers[i].maskEnable = GFX_FALSE;
        context->layer.layers[i].maskColor = 0;

        context->layer.layers[i].color_mode = GFX_COLOR_MODE_${CONFIG_DRV_GFX_S1D13517_COLOR_MODE};
    }
	
    // initialize the display
    //if (data->TCON_Init != GFX_NULL)
    //    data->TCON_Init();
	
	initializeHardware(context);

	return GFX_SUCCESS;
}

static uint8_t getReg(uint8_t index)
{
    uint16_t myReadBuffer = 0xff;

	// set RS line to low for command
    DisplaySetCommand(); 

    DRV_PMP0_Write(index);

	// set RS line to high for data
    DisplaySetData();    

	//Perform the fake read
    DRV_PMP0_Read(); 

    PMCONbits.PMPEN = 0; // disable PMP
    myReadBuffer = DRV_PMP0_Read();
    PMCONbits.PMPEN = 1; // enable PMP

    return((uint8_t)myReadBuffer);
}

static uint16_t setReg(uint8_t index, uint8_t value)
{
	// set RS line to low for command
    DisplaySetCommand(); 

    DRV_PMP0_Write(index);

	// set RS line to high for data
    DisplaySetData();    

    DRV_PMP0_Write(value);
	
	return 0;
}

static void initializeHardware(GFX_Context* context)
{
	int32_t i, j;
    
    GFX_DisplayInfo info = *context->display_info;
    
	uint16_t horizontalTiming = info.attributes.horz.pulse_width +
	                            info.attributes.horz.back_porch +
							    info.attributes.horz.front_porch;
								
	uint16_t horizontalSize = info.rect.width;
	
	uint16_t verticalTiming = info.attributes.vert.pulse_width +
	                          info.attributes.vert.back_porch +
							  info.attributes.vert.front_porch;
							  
	uint16_t verticalSize = info.rect.height;
	
	uint8_t state = 0;
	
	// set up register initialization values
	
	// S1D13517_REG12_CLK_SRC_SELECT
	if(horizontalSize <= CLK_THRESHOLD)
		registers[7][1] = 0x02;
	else
		registers[7][1] = 0x92;
	
<#if CONFIG_DRV_GFX_S1D13517_COLOR_MODE == "RGB_565">
	registers[10][1] = 0x05;                        // S1D13517_REG14_LCD_PANEL_TYPE
<#elseif CONFIG_DRV_GFX_S1D13517_COLOR_MODE == "RGB_888">
	registers[10][1] = 0x02;                        // S1D13517_REG14_LCD_PANEL_TYPE
</#if>
	registers[11][1] = (info.rect.width >> 3) - 1;   // S1D13517_REG16_HDISP_WIDTH
	registers[12][1] = (horizontalTiming >> 1) - 1; // S1D13517_REG18_HNDP_PERIOD
	registers[13][1] = info.rect.height - 1;            // S1D13517_REG1A_VDISP_HEIGHT_0
	registers[14][1] = (info.rect.height - 1) >> 8;     // S1D13517_REG1C_VDISP_HEIGHT_1
	registers[15][1] = (verticalTiming >> 1) - 1;   // S1D13517_REG1E_VNDP_PERIOD
	registers[16][1] = info.attributes.horz.pulse_width - 1;   // S1D13517_REG20_PHS_PULSE_WIDTH
	registers[17][1] = info.attributes.horz.front_porch;      // S1D13517_REG22_PHS_PULSE_START
	registers[18][1] = info.attributes.vert.pulse_width - 1;   // S1D13517_REG24_PVS_PULSE_WIDTH
	registers[19][1] = info.attributes.vert.front_porch;      // S1D13517_REG22_PHS_PULSE_START
	registers[20][1] = info.attributes.inv_left_shift << 7; // S1D13517_REG28_PCLK_POLARITY
	
	// config registers
	DisplayResetEnable();               // hold in reset by default

    DisplayResetConfig();               // enable RESET line

    DisplayCmdDataConfig();

    DisplayConfig();                    // enable chip select line

    DisplayBacklightConfig();
	
	while(state <= INIT_REGISTER_COUNT)
    {
        switch(state)
        {
            case 0:
                DisplayResetDisable();              // release from reset
                DisplayEnable();

                state++;
                break;

            case INIT_DELAY_STAGE:
                _DELAY(100);
                break;
        }

        /* initialize registers */
        while(setReg(*registers[state-1], registers[state-1][1]));

        state++;
    }
	
	_DELAY(500);

    brightnessSet(100);
	
	for(i = 0; i < 272; i++)
    {
        setupWriteWindow(context, 0, i, 240, 1);
        
        for(j = 0; j < 240; j++)
            writePixel565(GFX_ColorValue(GFX_COLOR_MODE_RGB_565, GFX_COLOR_BLACK));
        
        setupWriteWindow(context, 240, i, 480, 1);
        
        for(j = 240; j < 480; j++)
            writePixel565(GFX_ColorValue(GFX_COLOR_MODE_RGB_565, GFX_COLOR_BLACK));
    }
}

// function that returns the information for this driver
GFX_Result driverS1D13517InfoGet(GFX_DriverInfo* info)
{
	if(info == GFX_NULL)
        return GFX_FAILURE;

	// populate info struct
    strcpy(info->name, DRIVER_NAME);
    info->color_formats = supportedColorModes;
    info->layer_count = MAX_LAYER_COUNT;
    
    return GFX_SUCCESS;
}

// function that initialized the driver context
GFX_Result driverS1D13517ContextInitialize(GFX_Context* context)
{
	S1D13517DriverData* data;
	
	// set driver-specific function implementations
	context->hal.initialize = &initialize; 
    context->hal.destroy = &destroy;
	context->hal.brightnessRangeGet = &brightnessRangeGet;
	context->hal.brightnessSet = &brightnessSet;
	context->hal.vsyncSet = &vsyncSet;
	context->hal.vsyncCallbackSet = &vsyncCallbackSet;
	context->hal.hsyncCallbackSet = &hsyncCallbackSet;
	context->hal.orientationSet = &orientationSet;
	context->hal.mirroringSet = &mirroringSet;
	context->hal.layerActiveSet = &layerActiveSet;
	context->hal.layerEnabledSet = &layerEnabledSet;
	context->hal.layerPositionSet = &layerPositionSet;
	context->hal.layerSizeSet = &layerSizeSet;
	context->hal.layerBufferCountSet = &layerBufferCountSet;
	context->hal.layerBufferAddressSet = &layerBufferAddressSet;
	context->hal.layerBufferCoherentSet = &layerBufferCoherentSet;
	context->hal.layerBufferAllocate = &layerBufferAllocate;
	context->hal.layerBufferFree = &layerBufferFree;
	context->hal.layerVisibleSet = &layerVisibleSet;
	context->hal.layerSwapSet = &layerSwapSet;
	context->hal.layerColorModeSet = &layerColorModeSet;
	context->hal.layerAlphaEnableSet = &layerAlphaEnableSet;
	context->hal.layerMaskEnableSet = &layerMaskEnableSet;
	context->hal.layerMaskColorSet = &layerMaskColorSet;
	context->hal.pixelGet = &pixelGet;
	context->hal.pixelArrayGet = &pixelArrayGet;
	context->hal.drawPixel[GFX_ANTIALIAS_OFF] = &drawPixel;
	context->hal.drawPixel[GFX_ANTIALIAS_ON] = &drawPixel;
	
	// allocate space for driver-specific data
	data = context->memory.calloc(1, sizeof(S1D13517DriverData));
	
	if(data == GFX_NULL)
		return GFX_FAILURE;
		
<#if CONFIG_DRV_GFX_S1D13517_COLOR_MODE == "RGB_565">
	data->writePixel = &writePixel565;
<#elseif CONFIG_DRV_GFX_S1D13517_COLOR_MODE == "RGB_888">
	data->writePixel = &writePixel888;
</#if>	
		
	context->driver_data = data;
	
	return GFX_SUCCESS;
}

static GFX_Result brightnessRangeGet(uint32_t* low, uint32_t* high)
{
	*low = 0;
	*high = 100;
	
	return GFX_SUCCESS;
}

static GFX_Result brightnessSet(uint32_t val)
{
	if(val > MAX_BRIGHTNESS)
		val = MAX_BRIGHTNESS;
		
	if(val == MAX_BRIGHTNESS)
	{
		while(setReg(S1D13517_REG70_PWM_CONTROL, 0x85)); // turn on Backlight
	}
	else if (val == 0)
	{    
		setReg(S1D13517_REG70_PWM_CONTROL, 0x84);        // turn off Backlight
	}
	else if (val <= (MAX_BRIGHTNESS / 2))
	{
		val >>= 1;
		val *=  5;  // sets the value from (0-250)

		setReg(S1D13517_REG72_PWM_HIGH_DC_0, 0xff);
		setReg(S1D13517_REG74_PWM_HIGH_DC_1, val);
		setReg(S1D13517_REG7A_PWM_LOW_DC_0,  0xff);
		setReg(S1D13517_REG7C_PWM_LOW_DC_1,  0xff);
		setReg(S1D13517_REG70_PWM_CONTROL,   0x86); // turn off Backlight PWM
	}
	else
	{
		val >>= 1;
		val *=  5;  // sets the value from (0-250)

		setReg(S1D13517_REG72_PWM_HIGH_DC_0, val);
		setReg(S1D13517_REG74_PWM_HIGH_DC_1, 0xff);
		setReg(S1D13517_REG7A_PWM_LOW_DC_0,  0xff);
		setReg(S1D13517_REG7C_PWM_LOW_DC_1,  0xff);
		setReg(S1D13517_REG70_PWM_CONTROL,   0x86);   // turn off Backlight PWM
    }
	
	return GFX_SUCCESS;
}

static GFX_Result vsyncSet(GFX_Bool enable)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result vsyncCallbackSet(GFX_SyncCallback_FnPtr cb)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result hsyncCallbackSet(GFX_SyncCallback_FnPtr cb)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result orientationSet(GFX_Orientation ori)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result mirroringSet(GFX_Bool mirr)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result layerActiveSet(uint32_t idx)
{
	GFX_Context* context = GFX_ActiveContext();
	GFX_Layer* layer;
	uint8_t reg = 0;
	
	// default handling of state change
	if(defLayerActiveSet(idx) == GFX_FAILURE)
		return GFX_FAILURE;
	
	layer = context->layer.active;
	
	// set write buffer
	reg |= (layer->buffer_write_idx << 4);
	
	// set transparency
	if(layer->maskEnable == GFX_TRUE)
	{
		reg |= 0x4;
		
		setReg(S1D13517_REG54_TRANSP_KEY_RED,
		       GFX_ColorChannelRed(layer->maskColor, GFX_COLOR_MODE_${CONFIG_DRV_GFX_S1D13517_COLOR_MODE}));
		setReg(S1D13517_REG56_TRANSP_KEY_GREEN,
		       GFX_ColorChannelGreen(layer->maskColor, GFX_COLOR_MODE_${CONFIG_DRV_GFX_S1D13517_COLOR_MODE}));
		setReg(S1D13517_REG58_TRANSP_KEY_BLUE,
		       GFX_ColorChannelBlue(layer->maskColor, GFX_COLOR_MODE_${CONFIG_DRV_GFX_S1D13517_COLOR_MODE}));
	}
	
	setReg(S1D13517_REG52_INPUT_MODE, reg);
	
	return GFX_SUCCESS;
}

static GFX_Result layerEnabledSet(GFX_Bool val)
{
	// layers are always enabled
	if(val == GFX_FALSE)
		return GFX_FAILURE;
		
	return GFX_SUCCESS;
}

static GFX_Result layerPositionSet(int32_t x, int32_t y)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result layerSizeSet(int32_t width, int32_t height)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result layerBufferCountSet(uint32_t count)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result layerBufferAddressSet(uint32_t idx, GFX_Buffer address)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result layerBufferCoherentSet(uint32_t idx, GFX_Bool coherent)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result layerBufferAllocate(uint32_t idx)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result layerBufferFree(uint32_t idx)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result layerVisibleSet(GFX_Bool val)
{
	// layers are always visible
	if(val == GFX_FALSE)
		return GFX_FAILURE;
		
	return GFX_SUCCESS;
}

static GFX_Result layerSwapSet(GFX_Bool value)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result layerColorModeSet(GFX_ColorMode mode)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result layerAlphaEnableSet(GFX_Bool enable)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result layerMaskEnableSet(GFX_Bool enable)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result layerMaskColorSet(GFX_Color clr)
{
	return GFX_UNSUPPORTED;
}

static GFX_Color pixelGet(GFX_BufferSelection target,
                          GFX_Point* pnt,
						  GFX_ColorMode mode)
{
	return 0;
}

static GFX_Result pixelArrayGet(GFX_BufferSelection target,
                                GFX_Rect* rect,
                                GFX_PixelBuffer* buffer)
{
	return GFX_UNSUPPORTED;
}

static GFX_Result drawPixel(GFX_Point* pnt, GFX_DrawState* state)
{
	GFX_Context* context = GFX_ActiveContext();
	S1D13517DriverData* data = (S1D13517DriverData*)context->driver_data;
    GFX_Layer* layer = context->layer.active;
    GFX_Point tf_pnt = *pnt;
	
	// clip point
    if((state->clipEnable == GFX_TRUE) && 
        GFX_RectContainsPoint(&state->clipRect, pnt) == GFX_FALSE)
        return GFX_FAILURE;
		
	// enable masking
	
	// enable blending
	
	// enable orientation
	
	// enable mirroring
		
	
	// setup write window
	setupWriteWindow(context, pnt->x, pnt->y, 1, 1);
	
    // draw predraw pixels
    if(data->predrawCount > 0)
        drawEmptyPixels(data, data->predrawCount);
    
	// write pixel
	data->writePixel(state->color);
	
    // draw postdraw pixels
    if(data->postdrawCount > 0)
        drawEmptyPixels(data, data->postdrawCount);
    
	return GFX_SUCCESS;
}

static void writePixel565(GFX_Color clr)
{
<#if CONFIG_DRV_PMP_DATA_SIZE == "PMP_DATA_SIZE_8_BITS">
	DRV_PMP0_Write((uint8_t)((clr & 0xFF00) >> 8));
    DRV_PMP0_Write((uint8_t)(clr & 0xFF));
<#elseif CONFIG_DRV_PMP_DATA_SIZE == "PMP_DATA_SIZE_16_BITS">
	DRV_PMP0_Write(clr & 0xFFFF);
</#if>
}

static void writePixel888(GFX_Color clr)
{
<#if CONFIG_DRV_PMP_DATA_SIZE == "PMP_DATA_SIZE_8_BITS">
	DRV_PMP0_Write((clr & 0xFF0000) >> 16);
    DRV_PMP0_Write((clr & 0x00FF00) >> 8);
	DRV_PMP0_Write((clr & 0x0000FF));
<#elseif CONFIG_DRV_PMP_DATA_SIZE == "PMP_DATA_SIZE_16_BITS">
	DRV_PMP0_Write((clr & 0xFF0000) >> 16);
    DRV_PMP0_Write(clr & 0xFFFF);
</#if>
}

static void setupWriteWindow(GFX_Context* context,
                             int16_t x,
                             int16_t y,
                             uint16_t width,
                             uint16_t height)
{
	S1D13517DriverData* data = (S1D13517DriverData*)context->driver_data;
	
	data->predrawCount = x & 7;
    data->postdrawCount = ((data->predrawCount + width) & 7);
    data->postdrawCount = (8 - data->postdrawCount) & 7;
    
	/*setReg(S1D13517_REG5A_WRITE_WIN_X_SP, (x >> 2));

    DRV_PMP0_Write(y >> 2);                 // S1D13517_REG5C_WRITE_WIN_Y_SP_0
    DRV_PMP0_Write(y);                      // S1D13517_REG5E_WRITE_WIN_Y_SP_1
    DRV_PMP0_Write((x + (count - 1)) >> 2); // S1D13517_REG60_WRITE_WIN_X_EP
    DRV_PMP0_Write((y + lines - 1) >> 2);   // S1D13517_REG62_WRITE_WIN_Y_EP_0
    DRV_PMP0_Write(y + lines - 1);          // S1D13517_REG64_WRITE_WIN_Y_EP_1*/
    
    setReg(S1D13517_REG5A_WRITE_WIN_X_SP, x >> 2);

    DRV_PMP0_Write(y >> 2);                 // S1D13517_REG5C_WRITE_WIN_Y_SP_0
    DRV_PMP0_Write(y);                      // S1D13517_REG5E_WRITE_WIN_Y_SP_1
    DRV_PMP0_Write((x + (width - 1)) >> 2); // S1D13517_REG60_WRITE_WIN_X_EP
    DRV_PMP0_Write((y + (height - 1)) >> 2);   // S1D13517_REG62_WRITE_WIN_Y_EP_0
    DRV_PMP0_Write(y + height - 1);          // S1D13517_REG64_WRITE_WIN_Y_EP_1
}

static void drawEmptyPixels(S1D13517DriverData* data, uint32_t count)
{
	uint32_t red, green, blue, input, i;

	input = getReg(S1D13517_REG52_INPUT_MODE);
	red = getReg(S1D13517_REG54_TRANSP_KEY_RED);
	green = getReg(S1D13517_REG56_TRANSP_KEY_GREEN);
	blue = getReg(S1D13517_REG58_TRANSP_KEY_BLUE);
	
	setReg(S1D13517_REG52_INPUT_MODE, input |= 0x8);
	setReg(S1D13517_REG54_TRANSP_KEY_RED, 0x0);
	setReg(S1D13517_REG56_TRANSP_KEY_GREEN, 0x0);
	setReg(S1D13517_REG58_TRANSP_KEY_BLUE, 0x0);
	
	for(i = 0; i < count; i++)
		data->writePixel(0x0);
		
	setReg(S1D13517_REG52_INPUT_MODE, input);
	setReg(S1D13517_REG54_TRANSP_KEY_RED, red);
	setReg(S1D13517_REG56_TRANSP_KEY_GREEN, green);
	setReg(S1D13517_REG58_TRANSP_KEY_BLUE, blue);
}