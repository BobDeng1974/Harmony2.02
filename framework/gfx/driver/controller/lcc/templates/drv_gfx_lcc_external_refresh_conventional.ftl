void DRV_GFX_LCC_DisplayRefresh(void)
{
    typedef enum
	{
        HSYNC_FRONT_PORCH,
        HSYNC_PULSE,
        HSYNC_BACK_PORCH,
        HSYNC_DATA_ENABLE,
        HSYNC_DATA_ENABLE_OVERFLOW        
    } HSYNC_STATES;

    typedef enum
    {
        VSYNC_FRONT_PORCH,
        VSYNC_PULSE,
        VSYNC_BACK_PORCH,
        VSYNC_BLANK        
    } VSYNC_STATES;

    static int16_t line = 0;
	
<#if CONFIG_DRV_GFX_USE_LCC_PALETTE == true>
    static GFX_COLOR *point;
    int i;
</#if>
    /*static uint16_t pixels = 0;
    static uint32_t hSyncs = 0;
    
    static uint32_t vsyncPeriod = DISP_VER_FRONT_PORCH + DISP_VER_RESOLUTION + DISP_VER_BACK_PORCH;
    static uint32_t vsyncPulseDown = 0;
    static uint32_t vsyncPulseUp = 0;
    static uint32_t vsyncEnd = 0;*/

    static HSYNC_STATES hsyncState = HSYNC_FRONT_PORCH;
    static VSYNC_STATES vsyncState = VSYNC_BLANK;

<#if CONFIG_DRV_GFX_LCC_DMA_WRITE_STRATEGY == "Draw Count Limited">
    DrawCount = 0;
	
</#if>
    switch(vsyncState)
    {
        case VSYNC_FRONT_PORCH:
		{
            if (hSyncs > vsyncPulseDown)
            {
				{<@MACRO_VSYNC_OFF/>}
                vsyncPulseUp = hSyncs + DISP_VER_PULSE_WIDTH;
                vsyncState = VSYNC_PULSE;

				if(cntxt->layer.active->vsync == GFX_TRUE
					&& cntxt->layer.active->swap == GFX_TRUE)
					vsyncSwap();
				
                allowFrameUpdate = false;
                line = 0;
<#if CONFIG_PIC32MX == true>
#ifdef BSP_SRAM_A15StateSet
                BSP_SRAM_A15StateSet(0&0x1);
#endif
                BSP_SRAM_A16StateSet(0&0x1);
</#if>

<#if CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "WQVGA or lower">
                BSP_SRAM_A16StateSet(0&0x1);
                overflowcount = 0;
<#elseif CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "HVGA">
                BSP_SRAM_A16StateSet(drvLCCObj.initData->visualPage&0x1);
                BSP_SRAM_A17StateSet(drvLCCObj.initData->visualPage&0x1);
                BSP_SRAM_A18StateSet(0&0x1);
				if ( drvLCCObj.initData->visualPage == 1 )
					overflowcount = 3;
				else
					overflowcount = 0;
<#elseif CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "VGA">
                BSP_SRAM_A16StateSet(drvLCCObj.initData->visualPage&0x1);
                BSP_SRAM_A17StateSet(0&0x1);
                BSP_SRAM_A18StateSet(drvLCCObj.initData->visualPage&0x1);
				if ( drvLCCObj.initData->visualPage == 1 )
					overflowcount = 5;
				else
					overflowcount = 0;
<#elseif CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "WVGA">
                BSP_SRAM_A16StateSet(0&0x1);
                BSP_SRAM_A17StateSet(drvLCCObj.initData->visualPage&0x1);
                BSP_SRAM_A18StateSet(drvLCCObj.initData->visualPage&0x1);
				if ( drvLCCObj.initData->visualPage == 1 )
					overflowcount = 6;
				else
					overflowcount = 0;
</#if>
<#if CONFIG_USE_DRV_GFX_LCC_EXTERNAL_MEMORY_ADDRESS_19 == true>

                BSP_SRAM_A19StateSet(0&0x1);
</#if>
            }
            break;
		}	
        case VSYNC_PULSE:
		{
            if (hSyncs >= vsyncPulseUp)
            {
				{<@MACRO_VSYNC_ON/>}

                vsyncEnd = hSyncs + DISP_VER_BACK_PORCH;
                vsyncState = VSYNC_BACK_PORCH;
            }
			
            break;
		}
        case VSYNC_BACK_PORCH:
		{
            if (hSyncs >= vsyncEnd)
            {
                vsyncState = VSYNC_BLANK;
<#if CONFIG_PIC32MX == true>
				DCH1CSIZ = DISP_HOR_RESOLUTION;
</#if>
            }
            break;
		}
        case VSYNC_BLANK:
        {
    		break;
		}
    }

    switch (hsyncState)
    {
        case HSYNC_FRONT_PORCH:
		{
<#if CONFIG_DRV_GFX_DISPLAY_USE_DATA_ENABLE == true>
			{<@MACRO_DE_ON/>}
</#if>
            hsyncState = HSYNC_PULSE;
            allowLineUpdate = true;
			
			if (DISP_HOR_FRONT_PORCH > 0)
			{
	            pixels = DISP_HOR_FRONT_PORCH;
	            break;
			}
		}
        case HSYNC_PULSE:
		{
            {<@MACRO_HSYNC_OFF/>}
			
            if (hSyncs >= vsyncPeriod)
            {
				vsyncPeriod = hSyncs + DISP_VER_PULSE_WIDTH + DISP_VER_FRONT_PORCH + DISP_VER_RESOLUTION + DISP_VER_BACK_PORCH;
                vsyncPulseDown = hSyncs + DISP_VER_FRONT_PORCH;
                vsyncState = VSYNC_FRONT_PORCH;
                allowFrameUpdate = true;
            }
            hSyncs++; 
            pixels = DISP_HOR_PULSE_WIDTH;
            hsyncState = HSYNC_BACK_PORCH;
			
            break;
		}
        case HSYNC_BACK_PORCH:
		{
			{<@MACRO_HSYNC_ON/>}
			
            hsyncState = HSYNC_DATA_ENABLE; 
            allowLineUpdate = false;
			
			if (DISP_HOR_BACK_PORCH > 0)
			{
				pixels = DISP_HOR_BACK_PORCH;
				break;
			}
		}
        case HSYNC_DATA_ENABLE:
		{
            if (vsyncState == VSYNC_BLANK)
            {
<#if CONFIG_DRV_GFX_DISPLAY_USE_DATA_ENABLE == true>
				{<@MACRO_DE_OFF/>}
</#if>
<#if CONFIG_PIC32MX == true>
				DCH1CSIZ = 1;
</#if>

                PMADDR = ((PMP_ADDRESS_LINES) & ((line++) * DISP_HOR_RESOLUTION));
				
                if((PMADDR_OVERFLOW - PMADDR) < (DISP_HOR_RESOLUTION))       
				{   
					hsyncState = HSYNC_DATA_ENABLE_OVERFLOW;      //Do Overflow routine
					
					PLIB_DMA_ChannelXDestinationSizeSet(DMA_ID_0, DRV_GFX_LCC_DMA_CHANNEL_INDEX, (uint16_t)(((PMADDR_OVERFLOW)- PMADDR)<<1));
					PLIB_DMA_ChannelXINTSourceFlagClear(DMA_ID_0, DRV_GFX_LCC_DMA_CHANNEL_INDEX, DMA_INT_BLOCK_TRANSFER_COMPLETE);
					PLIB_DMA_ChannelXEnable(DMA_ID_0,DRV_GFX_LCC_DMA_CHANNEL_INDEX);
                    pixels = DISP_HOR_RESOLUTION - ((PMADDR_OVERFLOW)- PMADDR);
					
					return;
				}
			}
			
            pixels = DISP_HOR_RESOLUTION;
            hsyncState = HSYNC_FRONT_PORCH;
			
			break;
		}
        case HSYNC_DATA_ENABLE_OVERFLOW:
		{
<#if CONFIG_PIC32MX == true>
		#ifdef BSP_SRAM_A15StateSet
            BSP_SRAM_A15StateSet(overflowcount&0x1);
            BSP_SRAM_A16StateSet(overflowcount>>1&0x1);
		#else
            BSP_SRAM_A16StateSet(overflowcount>>1&0x1);
        #endif
</#if>
<#if CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "WQVGA or lower">
            BSP_SRAM_A16StateSet(++overflowcount&0x1);
</#if>
<#if CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "HVGA">
            BSP_SRAM_A16StateSet(++overflowcount&0x1);
            BSP_SRAM_A17StateSet(overflowcount>>1&0x1);
            BSP_SRAM_A18StateSet(overflowcount>>2&0x1);
</#if>
<#if CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "VGA">
            BSP_SRAM_A16StateSet(++overflowcount&0x1);
            BSP_SRAM_A17StateSet(overflowcount>>1&0x1);
            BSP_SRAM_A18StateSet(overflowcount>>2&0x1);
            BSP_SRAM_A19StateSet(overflowcount>>3&0x1);
</#if>
<#if CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "WVGA">
            BSP_SRAM_A16StateSet(++overflowcount&0x1);
            BSP_SRAM_A17StateSet(overflowcount>>1&0x1);
            BSP_SRAM_A18StateSet(overflowcount>>2&0x1);
            BSP_SRAM_A19StateSet(overflowcount>>3&0x1);
</#if>
            hsyncState = HSYNC_FRONT_PORCH;
            break;
		}
    }

    PLIB_DMA_ChannelXDestinationSizeSet(DMA_ID_0, DRV_GFX_LCC_DMA_CHANNEL_INDEX, (uint16_t)(pixels<<1));
    PLIB_DMA_ChannelXINTSourceFlagClear(DMA_ID_0, DRV_GFX_LCC_DMA_CHANNEL_INDEX, DMA_INT_BLOCK_TRANSFER_COMPLETE);
    
	SYS_DMA_ChannelEnable(dmaHandle);
}