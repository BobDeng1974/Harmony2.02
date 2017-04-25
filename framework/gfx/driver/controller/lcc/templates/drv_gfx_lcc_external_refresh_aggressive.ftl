void DRV_GFX_LCC_DisplayRefresh(void)
{
    static uint8_t GraphicsState = ACTIVE_PERIOD;
    static uint16_t remaining = 0;
    static short line = 0;
<#if CONFIG_DRV_GFX_LCC_DMA_WRITE_STRATEGY == "Draw Count Limited">
    DrawCount = 0;
</#if>
<#if CONFIG_DEVICE == "PIC32MX460F512L" || CONFIG_DEVICE == "PIC32MX360F512L">
        static uint16_t dmatransfersremaining = 0;

        if(dmatransfersremaining != 0)
        {

            if(dmatransfersremaining > 254)
             {
                   //Setup DMA Transfer
                   PLIB_DMA_ChannelXDestinationSizeSet(DMA_ID_0, DRV_GFX_LCC_DMA_CHANNEL_INDEX, 254);
                   dmatransfersremaining -= 254;
             }
             else
             {
                   //Setup DMA Transfer
                   PLIB_DMA_ChannelXDestinationSizeSet(DMA_ID_0, DRV_GFX_LCC_DMA_CHANNEL_INDEX, dmatransfersremaining);
                   dmatransfersremaining -= dmatransfersremaining;
             }

         PLIB_DMA_ChannelXINTSourceFlagClear(DMA_ID_0, DRV_GFX_LCC_DMA_CHANNEL_INDEX, DMA_INT_BLOCK_TRANSFER_COMPLETE);
         PLIB_DMA_ChannelXEnable(DMA_ID_0,DRV_GFX_LCC_DMA_CHANNEL_INDEX);
         return;
        }
</#if>

    switch(GraphicsState)
    {
        case ACTIVE_PERIOD:
            remaining = DISP_HOR_RESOLUTION;
            GraphicsState = BLANKING_PERIOD;
<#if CONFIG_PIC32MX == true>
            DCH1CSIZ = DISP_HOR_RESOLUTION;
</#if>

<#if CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "WVGA">
<#if CONFIG_DRV_GFX_DISPLAY_HSYNC_NEGATIVE_POLARITY == true>
            BSP_LCD_HSYNCOff();
<#else>
            BSP_LCD_HSYNCOn();
</#if></#if>
            if(line >= 0)
            {
                PMADDR = ((PMP_ADDRESS_LINES) & ((line) * DISP_HOR_RESOLUTION));

                if((line) == (DISP_VER_RESOLUTION))
                {
					if(cntxt->layer.active->vsync == GFX_TRUE
						&& cntxt->layer.active->swap == GFX_TRUE)
						vsyncSwap();
				
<#if CONFIG_DRV_GFX_DISPLAY_VSYNC_NEGATIVE_POLARITY == true>
                    BSP_LCD_VSYNCOn();
<#else>
                    BSP_LCD_VSYNCOff();
</#if>
                    line = (-VER_BLANK);
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
               else
               {
<#if CONFIG_DRV_GFX_DISPLAY_USE_DATA_ENABLE == true>
<#if CONFIG_DRV_GFX_DISPLAY_DATA_ENABLE_POSITIVE_POLARITY == true>
                    BSP_LCD_DEOn();
<#else>
                    BSP_LCD_DEOff();
</#if></#if>
					if((PMADDR_OVERFLOW - PMADDR) < (DISP_HOR_RESOLUTION))       
					{   
						  GraphicsState = OVERFLOW;      //Do Overflow routine
						  PLIB_DMA_ChannelXDestinationSizeSet(DMA_ID_0, DRV_GFX_LCC_DMA_CHANNEL_INDEX, (uint16_t)(((PMADDR_OVERFLOW)- PMADDR)<<1));
						  PLIB_DMA_ChannelXINTSourceFlagClear(DMA_ID_0, DRV_GFX_LCC_DMA_CHANNEL_INDEX, DMA_INT_BLOCK_TRANSFER_COMPLETE);
						  PLIB_DMA_ChannelXEnable(DMA_ID_0,DRV_GFX_LCC_DMA_CHANNEL_INDEX);
						  remaining = DISP_HOR_RESOLUTION - ((PMADDR_OVERFLOW)- PMADDR);
						  return;
					}           
                }
            }
            break;

       case OVERFLOW: //Adjust the address lines that aren't part of PMP
            GraphicsState = BLANKING_PERIOD;     //goto Front Porch
<#if CONFIG_PIC32MX == true>
		#ifdef BSP_SRAM_A15StateSet
            BSP_SRAM_A15StateSet(++overflowcount&0x1);          //count holds the additional address line count
            BSP_SRAM_A16StateSet((overflowcount>>1)&0x1);
		#else
            BSP_SRAM_A16StateSet(overflowcount&0x1);
		#endif
<#elseif CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "WQVGA or lower">
            BSP_SRAM_A16StateSet(++overflowcount&0x1);
</#if>
<#if CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "HVGA">
            BSP_SRAM_A16StateSet(++overflowcount&0x1);
			BSP_SRAM_A17StateSet((overflowcount>>1)&0x1);
			BSP_SRAM_A18StateSet((overflowcount>>2)&0x1);
</#if>
<#if CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "VGA">
            BSP_SRAM_A16StateSet(++overflowcount&0x1);
			BSP_SRAM_A17StateSet((overflowcount>>1)&0x1);
			BSP_SRAM_A18StateSet((overflowcount>>2)&0x1);
			BSP_SRAM_A19StateSet((overflowcount>>3)&0x1);
</#if>
<#if CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL == "WVGA">
            BSP_SRAM_A16StateSet(++overflowcount&0x1);
			BSP_SRAM_A17StateSet((overflowcount>>1)&0x1);
			BSP_SRAM_A18StateSet((overflowcount>>2)&0x1);
			BSP_SRAM_A19StateSet((overflowcount>>3)&0x1);
</#if>
			break;

        case BLANKING_PERIOD:   //Front Porch then Back Porch Start 
<#if CONFIG_DRV_GFX_DISPLAY_HSYNC_NEGATIVE_POLARITY == true>
            BSP_LCD_HSYNCOn();
<#else>
            BSP_LCD_HSYNCOff();
</#if>
<#if CONFIG_DRV_GFX_DISPLAY_USE_DATA_ENABLE == true>
<#if CONFIG_DRV_GFX_DISPLAY_DATA_ENABLE_POSITIVE_POLARITY == true>
            BSP_LCD_DEOff();
<#else>
            BSP_LCD_DEOn();
</#if></#if>
<#if CONFIG_DRV_GFX_LCC_PIXEL_SUPPORT_LEVEL != "WVGA">
            GraphicsState = PMDIN;
            while(PMMODEbits.BUSY == 1);
<#if CONFIG_DRV_GFX_DISPLAY_HSYNC_NEGATIVE_POLARITY == true>
            BSP_LCD_HSYNCOff();
<#else>
            BSP_LCD_HSYNCOn();
</#if></#if>
<#if CONFIG_DRV_GFX_DISPLAY_VSYNC_NEGATIVE_POLARITY == true>
            BSP_LCD_VSYNCOff();
<#else>
            BSP_LCD_VSYNCOn();
</#if>
            //Setup DMA Back Porch
            remaining = HBackPorch;
            GraphicsState = ACTIVE_PERIOD;   
            line++;
<#if CONFIG_PIC32MX == true>
            DCH1CSIZ = 1;
</#if>
            break;

        default:
            break;
    }

    //Setup DMA Transfer
<#if CONFIG_DEVICE == "PIC32MX460F512L" || CONFIG_DEVICE == "PIC32MX360F512L">
    if((remaining) > 254)
    {
        dmatransfersremaining = (remaining ) - 254;
        remaining = (254 >> 1);
    }
</#if>
    PLIB_DMA_ChannelXDestinationSizeSet(DMA_ID_0, DRV_GFX_LCC_DMA_CHANNEL_INDEX, (uint16_t) (remaining << 1));
    PLIB_DMA_ChannelXINTSourceFlagClear(DMA_ID_0, DRV_GFX_LCC_DMA_CHANNEL_INDEX, DMA_INT_BLOCK_TRANSFER_COMPLETE);
    SYS_DMA_ChannelEnable(dmaHandle);
}
  
