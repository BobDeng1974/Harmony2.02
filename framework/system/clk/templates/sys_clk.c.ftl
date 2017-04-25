/*******************************************************************************
  SYS CLK Functions for Clock System Service

  Company:
    Microchip Technology Inc.

  File Name:
    sys_clk.c

  Summary:
    SYS CLK function implementations for the Clock System Service.

  Description:
    The Clock System Service provides a simple interface to manage the oscillators
    on Microchip microcontrollers. This file defines the implementation for the 
    Clock System Service.
    
  Remarks:
    The functions incorporate all system clock configuration settings as
    determined by the user via the Microchip Harmony Configurator GUI.  
	
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************

#include "system_config.h"
#include "system_definitions.h"
#include "peripheral/osc/plib_osc.h"
#include "system/devcon/sys_devcon.h"
#include "framework/system/clk/src/sys_clk_local.h"

SYS_CLK_OBJECT clkObject;

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************
<#macro SYS_CLK_PERIPHERAL_CLK_ENABLE_INSTANCE SYS_CLK_PBCLKX SYS_CLK_PBDIV SYS_CLK_PBCLKNUM>
    /* Enable Peripheral Bus ${SYS_CLK_PBCLKNUM} */
    PLIB_OSC_PBClockDivisorSet (OSC_ID_0, ${SYS_CLK_PBCLKX}, ${SYS_CLK_PBDIV} );
<#if (CONFIG_PIC32MZ == true || CONFIG_PIC32MK == true || CONFIG_PIC32WK == true || CONFIG_DS60001404 = true)>    
    PLIB_OSC_PBOutputClockEnable (OSC_ID_0, ${SYS_CLK_PBCLKX} );
</#if>
</#macro>
<#macro SYS_CLK_PERIPHERAL_CLK_DISABLE_INSTANCE SYS_CLK_PBCLKX SYS_CLK_PBCLKNUM>
<#if (CONFIG_PIC32MZ == true || CONFIG_PIC32MK == true || CONFIG_PIC32WK == true || CONFIG_DS60001404 = true)>       /* Disable Peripheral Bus ${SYS_CLK_PBCLKNUM} */
    PLIB_OSC_PBOutputClockDisable (OSC_ID_0, ${SYS_CLK_PBCLKX} );
</#if>

</#macro>
<#macro SYS_CLK_REFCLK_ENABLE_INSTANCE SYS_CLK_REFCLKX SYS_CLK_REFCLK_SOURCE SYS_CLK_REFCLKNUM 
SYS_CLK_REFCLK_ROSEL SYS_CLK_REFCLK_RODIV SYS_CLK_REFCLK_ROTRIM>
    /* Enable and configure REFCLKO${SYS_CLK_REFCLKNUM}*/
    
    /* ROSEL ${SYS_CLK_REFCLK_SOURCE} */
    PLIB_OSC_ReferenceOscBaseClockSelect ( OSC_ID_0, ${SYS_CLK_REFCLKX}, ${SYS_CLK_REFCLK_ROSEL} );
    /* RODIV */
    PLIB_OSC_ReferenceOscDivisorValueSet ( OSC_ID_0, ${SYS_CLK_REFCLKX}, ${SYS_CLK_REFCLK_RODIV} );
    /* ROTRIM */
    PLIB_OSC_ReferenceOscTrimSet ( OSC_ID_0, ${SYS_CLK_REFCLKX}, ${SYS_CLK_REFCLK_ROTRIM} );

    PLIB_OSC_ReferenceOscEnable ( OSC_ID_0, ${SYS_CLK_REFCLKX} );
	/* Set Reference clock frequency */
	clkObject.referenceClock[${SYS_CLK_REFCLKX}] = SYS_CLK_BUS_REFERENCE_${SYS_CLK_REFCLKNUM};
	
	clkObject.referenceClosestClock[${SYS_CLK_REFCLKX}] = SYS_CLK_BUS_REFERENCE_${SYS_CLK_REFCLKNUM};
</#macro>
<#macro SYS_CLK_REFCLK_DISABLE_INSTANCE SYS_CLK_REFCLKX SYS_CLK_REFCLKNUM>
    /* Disable REFCLKO${SYS_CLK_REFCLKNUM}*/
    PLIB_OSC_ReferenceOscDisable ( OSC_ID_0, ${SYS_CLK_REFCLKX} );
</#macro>
<#macro SYS_CLK_REFCLK_OUTPUT_ENABLE_INSTANCE SYS_CLK_REFCLKX SYS_CLK_REFCLKNUM>
    /* Disable REFCLK${SYS_CLK_REFCLKNUM}_OE*/
    PLIB_OSC_ReferenceOutputEnable ( OSC_ID_0, ${SYS_CLK_REFCLKX} );
</#macro>
<#macro SYS_CLK_REFCLK_OUTPUT_DISABLE_INSTANCE SYS_CLK_REFCLKX SYS_CLK_REFCLKNUM>
    /* Disable REFCLK${SYS_CLK_REFCLKNUM}_OE*/
    PLIB_OSC_ReferenceOutputDisable ( OSC_ID_0, ${SYS_CLK_REFCLKX} );
</#macro>

// *****************************************************************************
/* Function:
    void SYS_CLK_Initialize ( const SYS_CLK_INIT * clkInit  )

  Summary:
    Initializes hardware and internal data structure of the System Clock.

  Description:
    This function initializes the hardware and internal data structure of System
    Clock Service.

  Remarks:
    None. 
*/

void SYS_CLK_Initialize( const SYS_CLK_INIT * clkInit )
{
    SYS_DEVCON_SystemUnlock ( );

    PLIB_OSC_FRCDivisorSelect( OSC_ID_0, ${CONFIG_SYS_CLK_FRCDIV});

<#if CONFIG_PIC32MX == true && CONFIG_SYS_CLK_CONFIG_UFRCEN == "ON" && CONFIG_DS60001404 == false>
    /* Enable Secondary Oscillator */
    PLIB_OSC_UsbClockSourceSelect( OSC_ID_0 , SYS_OSC_USBCLK_FRC );

<#elseif CONFIG_PIC32MX == true && CONFIG_SYS_CLK_CONFIG_UFRCEN == "OFF" && CONFIG_DS60001404 == false>
    /* Disable Secondary Oscillator */
    PLIB_OSC_UsbClockSourceSelect( OSC_ID_0 , SYS_OSC_USBCLK_PRIMARY );

</#if>
<#if (CONFIG_PIC32MK == true || CONFIG_DS60001404 == true) && (CONFIG_USE_USB_STACK == true)>	
	/* Configure UPLL */
<#if CONFIG_DS60001404 == false>
<#if CONFIG_SYS_CLK_UPOSCEN == "POSC">
	// PLIB_OSC_PLLBypassEnable(OSC_ID_0, OSC_PLL_USB);
<#else>
	// PLIB_OSC_PLLBypassDisable(OSC_ID_0, OSC_PLL_USB);
</#if>
	PLIB_OSC_UPLLInputDivisorSet(OSC_ID_0, ${CONFIG_SYS_CLK_UPLLIDIV});
	PLIB_OSC_UPLLFrequencyRangeSet(OSC_ID_0, ${CONFIG_SYS_CLK_UPLLRNG});	
</#if>
	PLIB_OSC_UPLLMultiplierSelect(OSC_ID_0, ${CONFIG_SYS_CLK_UPLLMULT});
	PLIB_OSC_UPLLOutputDivisorSet(OSC_ID_0, ${CONFIG_SYS_CLK_UPLLODIV});

<#if CONFIG_SYS_CLK_UFRCEN == "FRC">	
	PLIB_OSC_UsbClockSourceSelect (OSC_ID_0, SYS_OSC_USBCLK_FRC);
<#else>
	PLIB_OSC_UsbClockSourceSelect (OSC_ID_0, SYS_OSC_USBCLK_PRIMARY);
</#if>
</#if>
<#if CONFIG_PIC32WK == true >
	/* Configure SPLL */
<#if CONFIG_SYS_CLK_SBYPASS == true>
	PLIB_OSC_PLLBypassEnable(OSC_ID_0, OSC_PLL_SYSTEM);
<#else>
	PLIB_OSC_PLLBypassDisable(OSC_ID_0, OSC_PLL_SYSTEM);
</#if>
	PLIB_OSC_SysPLLInputClockSourceSet(OSC_ID_0, ${CONFIG_SYS_CLK_SPLLICLK});
	PLIB_OSC_SysPLLInputDivisorSet(OSC_ID_0, ${CONFIG_SYS_CLK_SPLLIDIV} - 1);
	PLIB_OSC_SysPLLMultiplierSelect(OSC_ID_0, ${CONFIG_SYS_CLK_SPLLMULT});
	PLIB_OSC_SysPLLOutputDivisorSet(OSC_ID_0, ${CONFIG_SYS_CLK_SPLLODIV});
	PLIB_OSC_SysPLLFrequencyRangeSet(OSC_ID_0, ${CONFIG_SYS_CLK_SPLLRNG});
	
	/* Configure UPLL */
<#if CONFIG_SYS_CLK_UPOSCEN == "POSC">
	PLIB_OSC_PLLBypassEnable(OSC_ID_0, OSC_PLL_USB);
<#else>
	PLIB_OSC_PLLBypassDisable(OSC_ID_0, OSC_PLL_USB);
</#if>
	PLIB_OSC_UPLLInputDivisorSet(OSC_ID_0, ${CONFIG_SYS_CLK_UPLLIDIV});
	PLIB_OSC_UPLLMultiplierSelect(OSC_ID_0, ${CONFIG_SYS_CLK_UPLLMULT});
	PLIB_OSC_UPLLOutputDivisorSet(OSC_ID_0, ${CONFIG_SYS_CLK_UPLLODIV});
	PLIB_OSC_UPLLFrequencyRangeSet(OSC_ID_0, ${CONFIG_SYS_CLK_UPLLRNG});	
<#if CONFIG_SYS_CLK_UFRCEN == "FRC">	
	PLIB_OSC_UsbClockSourceSelect (OSC_ID_0, SYS_OSC_USBCLK_FRC);
<#else>
	PLIB_OSC_UsbClockSourceSelect (OSC_ID_0, SYS_OSC_USBCLK_PRIMARY);
</#if>

	/* Configure BTPLL */
<#if CONFIG_SYS_CLK_BTBYPASS == true>
	PLIB_OSC_PLLBypassEnable(OSC_ID_0, OSC_PLL_BT);
<#else>
	PLIB_OSC_PLLBypassDisable(OSC_ID_0, OSC_PLL_BT);
</#if>
	PLIB_OSC_BTPLLInputClockSourceSet(OSC_ID_0, ${CONFIG_SYS_CLK_BTPLLICLK});
	PLIB_OSC_BTPLLInputDivisorSet(OSC_ID_0, ${CONFIG_SYS_CLK_BTPLLIDIV} - 1);
	PLIB_OSC_BTPLLMultiplierSelect(OSC_ID_0, ${CONFIG_SYS_CLK_BTPLLMULT});
	PLIB_OSC_BTPLLOutputDivisorSet(OSC_ID_0, ${CONFIG_SYS_CLK_BTPLLODIV});
	PLIB_OSC_BTPLLFrequencyRangeSet(OSC_ID_0, ${CONFIG_SYS_CLK_BTPLLRNG});
<#if CONFIG_SYS_CLK_BTCLKOUTEN == true>
	PLIB_OSC_BTPLLClockOutEnable(OSC_ID_0);
<#else>
	PLIB_OSC_BTPLLClockOutDisable(OSC_ID_0);
</#if>
	
	/* Secondary Oscillator Configuration */
<#if CONFIG_SYS_CLK_SOSCEN == true>
	PLIB_OSC_SecondaryEnable(OSC_ID_0);
<#else>
	PLIB_OSC_SecondaryDisable(OSC_ID_0);
</#if>
	
	/* Switch to requested clock source if needed */
	if(PLIB_OSC_CurrentSysClockGet(OSC_ID_0) != ${CONFIG_SYS_CLK_NOSC})
	{
		PLIB_OSC_SysClockSelect(OSC_ID_0, ${CONFIG_SYS_CLK_NOSC});
		while(!PLIB_OSC_ClockSwitchingIsComplete(OSC_ID_0));
	}
</#if>

<#if CONFIG_SYS_CLK_CONFIG_SOSCEN == "ON">
    /* Enable Secondary Oscillator */
    PLIB_OSC_SecondaryEnable( OSC_ID_0 );

<#elseif CONFIG_SYS_CLK_CONFIG_SOSCEN == "OFF">
    /* Disable Secondary Oscillator */
    PLIB_OSC_SecondaryDisable( OSC_ID_0 );

</#if>
<#if CONFIG_HAVE_MPLL == true>
    /* Memory PLL */
<#if CONFIG_SYS_CLK_MPLL_ENABLE == true>
	PLIB_DEVCON_MPLLVregEnable( DEVCON_ID_0 );
	while (!PLIB_DEVCON_MPLLVregIsReady(DEVCON_ID_0));

	PLIB_DEVCON_MPLLVrefSet(DEVCON_ID_0, DEVCON_MPLL_VREF_EXT);
    PLIB_DEVCON_MPLLInputDivSet( DEVCON_ID_0, ${CONFIG_SYS_CLK_MPLLIDIV} );
    PLIB_DEVCON_MPLLMultiplierSet ( DEVCON_ID_0, ${CONFIG_SYS_CLK_MPLLMULT} );
    PLIB_DEVCON_MPLLODiv1Set( DEVCON_ID_0, DEVCON_MPLL_ODIV_${CONFIG_SYS_CLK_MPLLODIV1} );
    PLIB_DEVCON_MPLLODiv2Set( DEVCON_ID_0, DEVCON_MPLL_ODIV_${CONFIG_SYS_CLK_MPLLODIV2} );
    PLIB_DEVCON_MPLLEnable( DEVCON_ID_0 );
	while(!PLIB_DEVCON_MPLLIsReady( DEVCON_ID_0 ));
<#else>
    PLIB_DEVCON_MPLLDisable( DEVCON_ID_0 );
</#if></#if>
<#if CONFIG_SYS_CLK_PBCLK0_ENABLE == true>
<@SYS_CLK_PERIPHERAL_CLK_ENABLE_INSTANCE SYS_CLK_PBCLKX="OSC_PERIPHERAL_BUS_1" SYS_CLK_PBCLKNUM="1" SYS_CLK_PBDIV=CONFIG_SYS_CLK_PBDIV0 />
</#if>
<#if CONFIG_DS60001404 == false && CONFIG_PIC32MX == false>

<#if CONFIG_SYS_CLK_PBCLK1_ENABLE == true>
<@SYS_CLK_PERIPHERAL_CLK_ENABLE_INSTANCE SYS_CLK_PBCLKX="OSC_PERIPHERAL_BUS_2" SYS_CLK_PBCLKNUM="2" SYS_CLK_PBDIV=CONFIG_SYS_CLK_PBDIV1 />
<#else>
<@SYS_CLK_PERIPHERAL_CLK_DISABLE_INSTANCE SYS_CLK_PBCLKX="OSC_PERIPHERAL_BUS_2" SYS_CLK_PBCLKNUM="2" />
</#if>
<#if CONFIG_SYS_CLK_PBCLK2_ENABLE == true>
<@SYS_CLK_PERIPHERAL_CLK_ENABLE_INSTANCE SYS_CLK_PBCLKX="OSC_PERIPHERAL_BUS_3" SYS_CLK_PBCLKNUM="3" SYS_CLK_PBDIV=CONFIG_SYS_CLK_PBDIV2 />
<#else>
<@SYS_CLK_PERIPHERAL_CLK_DISABLE_INSTANCE SYS_CLK_PBCLKX="OSC_PERIPHERAL_BUS_3" SYS_CLK_PBCLKNUM="3" />
</#if>
<#if CONFIG_SYS_CLK_PBCLK3_ENABLE == true>
<@SYS_CLK_PERIPHERAL_CLK_ENABLE_INSTANCE SYS_CLK_PBCLKX="OSC_PERIPHERAL_BUS_4" SYS_CLK_PBCLKNUM="4" SYS_CLK_PBDIV=CONFIG_SYS_CLK_PBDIV3 />
<#else>
<@SYS_CLK_PERIPHERAL_CLK_DISABLE_INSTANCE SYS_CLK_PBCLKX="OSC_PERIPHERAL_BUS_4" SYS_CLK_PBCLKNUM="4" />
</#if>
<#if CONFIG_PIC32WK == false>
<#if CONFIG_SYS_CLK_PBCLK4_ENABLE == true>
<@SYS_CLK_PERIPHERAL_CLK_ENABLE_INSTANCE SYS_CLK_PBCLKX="OSC_PERIPHERAL_BUS_5" SYS_CLK_PBCLKNUM="5" SYS_CLK_PBDIV=CONFIG_SYS_CLK_PBDIV4 />
<#else>
<@SYS_CLK_PERIPHERAL_CLK_DISABLE_INSTANCE SYS_CLK_PBCLKX="OSC_PERIPHERAL_BUS_5" SYS_CLK_PBCLKNUM="5" />
</#if>
<#if CONFIG_DS60001361 == true || CONFIG_DS60001402 == true>
<#if CONFIG_SYS_CLK_PBCLK5_ENABLE == true>
<@SYS_CLK_PERIPHERAL_CLK_ENABLE_INSTANCE SYS_CLK_PBCLKX="OSC_PERIPHERAL_BUS_6" SYS_CLK_PBCLKNUM="6" SYS_CLK_PBDIV=CONFIG_SYS_CLK_PBDIV5 />
<#else>
<@SYS_CLK_PERIPHERAL_CLK_DISABLE_INSTANCE SYS_CLK_PBCLKX="OSC_PERIPHERAL_BUS_6" SYS_CLK_PBCLKNUM="6" />
</#if></#if>
<#if CONFIG_SYS_CLK_PBCLK6_ENABLE == true>
<@SYS_CLK_PERIPHERAL_CLK_ENABLE_INSTANCE SYS_CLK_PBCLKX="OSC_PERIPHERAL_BUS_7" SYS_CLK_PBCLKNUM="7" SYS_CLK_PBDIV=CONFIG_SYS_CLK_PBDIV6 />
<#else>
<@SYS_CLK_PERIPHERAL_CLK_DISABLE_INSTANCE SYS_CLK_PBCLKX="OSC_PERIPHERAL_BUS_7"SYS_CLK_PBCLKNUM="7" />
</#if>
<#if CONFIG_DS60001361 == false && CONFIG_DS60001402 == false>
<#if CONFIG_SYS_CLK_PBCLK7_ENABLE == true>
<@SYS_CLK_PERIPHERAL_CLK_ENABLE_INSTANCE SYS_CLK_PBCLKX="OSC_PERIPHERAL_BUS_8" SYS_CLK_PBCLKNUM="8" SYS_CLK_PBDIV=CONFIG_SYS_CLK_PBDIV7 />
<#else>
<@SYS_CLK_PERIPHERAL_CLK_DISABLE_INSTANCE SYS_CLK_PBCLKX="7" SYS_CLK_PBCLKNUM="8" />
</#if></#if></#if> </#if> 
 
<#if CONFIG_HAVE_REFCLOCK == true>    
<#if CONFIG_PIC32MX == true>    
<#if CONFIG_SYS_CLK_REFCLK_ENABLE == true>
<@SYS_CLK_REFCLK_ENABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_1" SYS_CLK_REFCLKNUM="1" 
SYS_CLK_REFCLK_RODIV=CONFIG_SYS_CLK_RODIV
SYS_CLK_REFCLK_SOURCE=CONFIG_SYS_CLK_REFCLK_SOURCE SYS_CLK_REFCLK_ROTRIM=CONFIG_SYS_CLK_ROTRIM
SYS_CLK_REFCLK_ROSEL=CONFIG_SYS_CLK_REFCLK_ROSEL/>
<#else>
<@SYS_CLK_REFCLK_DISABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_1" SYS_CLK_REFCLKNUM="1" />
</#if>
<#if CONFIG_SYS_CLK_REFCLK_OE == true>
<@SYS_CLK_REFCLK_OUTPUT_ENABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_1" SYS_CLK_REFCLKNUM="1" />
<#else>
<@SYS_CLK_REFCLK_OUTPUT_DISABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_1" SYS_CLK_REFCLKNUM="1" />
</#if></#if>

<#if (CONFIG_PIC32MZ == true || CONFIG_PIC32MK == true || CONFIG_PIC32WK == true)>   <#if CONFIG_SYS_CLK_REFCLK0_ENABLE == true>
<@SYS_CLK_REFCLK_ENABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_1" SYS_CLK_REFCLKNUM="1" 
SYS_CLK_REFCLK_RODIV=CONFIG_SYS_CLK_RODIV0
SYS_CLK_REFCLK_SOURCE=CONFIG_SYS_CLK_REFCLK_SOURCE0 SYS_CLK_REFCLK_ROTRIM=CONFIG_SYS_CLK_ROTRIM0
SYS_CLK_REFCLK_ROSEL=CONFIG_SYS_CLK_REFCLK_ROSEL0/>
<#else>
<@SYS_CLK_REFCLK_DISABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_1" SYS_CLK_REFCLKNUM="1" />
</#if>
<#if CONFIG_SYS_CLK_REFCLK0_OE == true>
<@SYS_CLK_REFCLK_OUTPUT_ENABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_1" SYS_CLK_REFCLKNUM="1" />
<#else>
<@SYS_CLK_REFCLK_OUTPUT_DISABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_1" SYS_CLK_REFCLKNUM="1" />
</#if>
<#if CONFIG_SYS_CLK_REFCLK1_ENABLE == true>
<@SYS_CLK_REFCLK_ENABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_2" SYS_CLK_REFCLKNUM="2" 
SYS_CLK_REFCLK_RODIV=CONFIG_SYS_CLK_RODIV1
SYS_CLK_REFCLK_SOURCE=CONFIG_SYS_CLK_REFCLK_SOURCE1 SYS_CLK_REFCLK_ROTRIM=CONFIG_SYS_CLK_ROTRIM1
SYS_CLK_REFCLK_ROSEL=CONFIG_SYS_CLK_REFCLK_ROSEL1/>
<#else>
<@SYS_CLK_REFCLK_DISABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_2" SYS_CLK_REFCLKNUM="2" />
</#if>
<#if CONFIG_SYS_CLK_REFCLK1_OE == true>
<@SYS_CLK_REFCLK_OUTPUT_ENABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_2" SYS_CLK_REFCLKNUM="2" />
<#else>
<@SYS_CLK_REFCLK_OUTPUT_DISABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_2" SYS_CLK_REFCLKNUM="2" />
</#if>
<#if CONFIG_SYS_CLK_REFCLK2_ENABLE == true>
<@SYS_CLK_REFCLK_ENABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_3" SYS_CLK_REFCLKNUM="3" 
SYS_CLK_REFCLK_RODIV=CONFIG_SYS_CLK_RODIV2
SYS_CLK_REFCLK_SOURCE=CONFIG_SYS_CLK_REFCLK_SOURCE2 SYS_CLK_REFCLK_ROTRIM=CONFIG_SYS_CLK_ROTRIM2
SYS_CLK_REFCLK_ROSEL=CONFIG_SYS_CLK_REFCLK_ROSEL2/>
<#else>
<@SYS_CLK_REFCLK_DISABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_3" SYS_CLK_REFCLKNUM="3" />
</#if>
<#if CONFIG_SYS_CLK_REFCLK2_OE == true>
<@SYS_CLK_REFCLK_OUTPUT_ENABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_3" SYS_CLK_REFCLKNUM="3" />
<#else>
<@SYS_CLK_REFCLK_OUTPUT_DISABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_3" SYS_CLK_REFCLKNUM="3" />
</#if>
<#if CONFIG_SYS_CLK_REFCLK3_ENABLE == true>
<@SYS_CLK_REFCLK_ENABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_4" SYS_CLK_REFCLKNUM="4" 
SYS_CLK_REFCLK_RODIV=CONFIG_SYS_CLK_RODIV3
SYS_CLK_REFCLK_SOURCE=CONFIG_SYS_CLK_REFCLK_SOURCE3 SYS_CLK_REFCLK_ROTRIM=CONFIG_SYS_CLK_ROTRIM3
SYS_CLK_REFCLK_ROSEL=CONFIG_SYS_CLK_REFCLK_ROSEL3/>
<#else>
<@SYS_CLK_REFCLK_DISABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_4" SYS_CLK_REFCLKNUM="4" />
</#if>
<#if CONFIG_SYS_CLK_REFCLK3_OE == true>
<@SYS_CLK_REFCLK_OUTPUT_ENABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_4" SYS_CLK_REFCLKNUM="4" />
<#else>
<@SYS_CLK_REFCLK_OUTPUT_DISABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_4" SYS_CLK_REFCLKNUM="4" />
</#if>
<#if CONFIG_HAVE_REFCLOCK5 == true>
<#if CONFIG_SYS_CLK_REFCLK4_ENABLE == true>
<@SYS_CLK_REFCLK_ENABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_5" SYS_CLK_REFCLKNUM="5" 
SYS_CLK_REFCLK_RODIV=CONFIG_SYS_CLK_RODIV4
SYS_CLK_REFCLK_SOURCE=CONFIG_SYS_CLK_REFCLK_SOURCE4 SYS_CLK_REFCLK_ROTRIM=CONFIG_SYS_CLK_ROTRIM4
SYS_CLK_REFCLK_ROSEL=CONFIG_SYS_CLK_REFCLK_ROSEL4/>
<#else>
<@SYS_CLK_REFCLK_DISABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_5" SYS_CLK_REFCLKNUM="5" />
</#if>
<#if CONFIG_SYS_CLK_REFCLK4_OE == true>
<@SYS_CLK_REFCLK_OUTPUT_ENABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_5" SYS_CLK_REFCLKNUM="5" />
<#else>
<@SYS_CLK_REFCLK_OUTPUT_DISABLE_INSTANCE SYS_CLK_REFCLKX="OSC_REFERENCE_5" SYS_CLK_REFCLKNUM="5" />
</#if>
</#if></#if></#if>

    SYS_DEVCON_SystemLock ( );
	
	//clkObject.systemClock = _SYS_CLK_SystemClockRead ();
	
	clkObject.systemClock = SYS_CLK_FREQ;
	
	clkObject.callback=NULL;
}

/******************************************************************************
  Function:
    void SYS_CLK_ClockFailureCallbackRegister ( SYS_CLK_ERROR_HANDLER callback )

  Summary:
    Registers the call back function that will be triggered on a clock failure.

  Description:
    This function registers the call back function that will be triggered on a 
    clock failure.

  Remarks:
    None.
*/

void SYS_CLK_ClockFailureCallbackRegister ( SYS_CLK_ERROR_HANDLER callback )
{
    clkObject.callback = callback;
}

/******************************************************************************
  Function:
    uint32_t SYS_CLK_SystemFrequencySet ( CLK_SOURCES_SYSTEM systemSource,
				uint32_t systemClockHz, bool waitUntilComplete )

  Summary:
    Sets the system clock of the device to the value specified.
    
  Description:
    This function configures the clock multipliers and divisors to achieve requested
    System clock frequency. Initially it checks the difference between the requested
    value and possible value. If it is not within 'SYS_CLK_CONFIG_FREQ_ERROR_LIMIT',
    the registers values will not be changed and a value '0' will be returned to let
    user know that the operation was unsuccessful. If the value requested is acceptable,
    then it writes to the oscillator registers and return with the newly set frequency.
    If the operation is a failure, SYS_CLK_SystemClosestFrequencyGet function will give
    the closest possible frequency. If the closest possible value is acceptable, user
    can reconfigure with that value.

  Remarks:
    None.
*/

uint32_t SYS_CLK_SystemFrequencySet ( CLK_SOURCES_SYSTEM systemSource,
				uint32_t systemClockHz, bool waitUntilComplete )
{
    uint32_t clockClosest = 0;

    if ( _SYS_CLK_SystemClockSet ( systemSource, systemClockHz,
                waitUntilComplete, &clockClosest ) )
    {
        return clkObject.systemClock;
    }
    else 
    {
        /* Update the closest in any case */
        clkObject.systemClosestClock = clockClosest;

        return 0;
    }
}

/******************************************************************************
  Function:
    uint32_t SYS_CLK_SystemFrequencyGet ( void )

  Summary:
    Gets the system clock frequency in Hertz.

  Description:
    This function gets the System clock frequency in Hertz.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    System clock frequency in Hertz.

  Example:
    <code>
    uint32_t sysClockHz;

    sysClockHz = SYS_CLK_SystemFrequencyGet ( );
    </code>

  Remarks:
 */

uint32_t SYS_CLK_SystemFrequencyGet ( void )
{
    return clkObject.systemClock;
}

/******************************************************************************
  Function:
    uint32_t SYS_CLK_PeripheralFrequencySet ( CLK_BUSES_PERIPHERAL peripheralBus,
                CLK_SOURCES_PERIPHERAL peripheralSource, uint32_t peripheralClockHz,
                bool waitUntilComplete )

  Summary:
    Configures the Peripheral clock of the device to the value specified.

  Description:
    This function configures the clock multipliers and divisors to achieve requested
    Peripheral clock frequency. Initially it checks the difference between the requested
    value and possible value. If it is not within 'SYS_CLK_CONFIG_FREQ_ERROR_LIMIT',
    the registers values will not be changed and a value '0' will be returned to 
    let user know that the operation was unsuccessful. If the value requested is
    acceptable, then it writes to the oscillator registers and return with the newly
    set frequency. If the operation is a failure, SYS_CLK_PeripheralClosestFrequencyGet
    function will give the closest possible frequency. If the closest possible value
    is acceptable, user can reconfigure with that value.

  Remarks:
    None.
*/

uint32_t SYS_CLK_PeripheralFrequencySet ( CLK_BUSES_PERIPHERAL peripheralBus,
            CLK_SOURCES_PERIPHERAL peripheralSource, uint32_t peripheralClockHz,
            bool waitUntilComplete )
{
    uint32_t clockClosest = 0;

    if ( _SYS_CLK_PeripheralFrequencySet ( peripheralBus, peripheralClockHz, &clockClosest ) )
    {
        /* System clock update is successful. Update the data structures */
        clkObject.peripheralClock[peripheralBus] = clockClosest;

        /* Update the closest in any case */
        clkObject.peripheralClosestClock[peripheralBus] = clockClosest;

    }
    else
    {
        /* Update the closest in any case */
        clkObject.peripheralClosestClock[peripheralBus] = clockClosest;

        return 0;
    }
    return clockClosest;
}

/******************************************************************************
  Function:
    uint32_t SYS_CLK_PeripheralFrequencyGet ( CLK_BUSES_PERIPHERAL peripheralBus )

  Summary:
    Gets the selected clock peripheral bus frequency in Hertz.

  Description:
    This function gets the selected peripheral bus clock frequency in Hertz.

  Precondition:
    None.

  Parameters:
	peripheralBus - Peripheral clock bus selection. One of the possible value from
				CLK_BUSES_PERIPHERAL enum. For devices that do not have multiple
				clock channels for peripheral clock, CLK_BUS_PERIPHERAL_1 should be
				the selection.

  Returns:
    Clock frequency in Hertz.

  Example:
    <code>
    unsigned long peripheralClockHz;

    peripheralClockHz = SYS_CLK_PeripheralFrequencyGet ( CLK_BUS_PERIPHERAL_5 );
    </code>

  Remarks:
	Most of the devices doesn't have multiple Peripheral clock buses. In that case, 
	pass CLK_USB_PERIPHERAL_1 as the bus number.
 */

uint32_t SYS_CLK_PeripheralFrequencyGet ( CLK_BUSES_PERIPHERAL peripheralBus )
{
	return _SYS_CLK_PeripheralClockRead (peripheralBus, clkObject.systemClock );
}

/******************************************************************************
  Function:
    uint32_t SYS_CLK_ReferenceFrequencySet ( CLK_BUSES_USB usbBus, CLK_SOURCES_USB usbSource,
					uint32_t usbClockHz, bool waitUntilComplete )

  Summary:
    Configures the Reference clock of the device to the value specified.

  Description:
    This function configures the clock multipliers and divisors to achieve requested
    Reference clock frequency. Initially it checks the difference between the requested
    value and possible value. If it is not within 'SYS_CLK_CONFIG_FREQ_ERROR_LIMIT',
    the registers values will not be changed and a value '0' will be returned to let
    user know that the operation was unsuccessful. If the value requested is acceptable,
    then it writes to the oscillator registers and return with the newly set frequency.
    If the operation is a failure, SYS_CLK_USBClosestFrequencyGet function will give
    the closest possible frequency. If the closest possible value is acceptable, user
    can reconfigure with that value.

  Remarks:
    None.
*/

uint32_t SYS_CLK_ReferenceFrequencySet ( CLK_BUSES_REFERENCE referenceBus,
        CLK_SOURCES_REFERENCE referenceSource, uint32_t referenceClockHz,
        bool waitUntilComplete )
{
<#if CONFIG_HAVE_REFCLOCK = true >
    uint32_t clockClosest = 0;

    if ( _SYS_CLK_ReferenceFrequencySet ( referenceBus, referenceSource, referenceClockHz,
                waitUntilComplete, &clockClosest ) )
    {
        /* System clock update is successful. Update the data structures */
        clkObject.referenceClock[referenceBus] = clockClosest;

        /* Update the closest with the calculated value */
        clkObject.referenceClosestClock[referenceBus] = clockClosest;

    }
    else
    {
        /* Update the closest in any case */
        clkObject.referenceClosestClock[referenceBus] = clockClosest;

        return 0;
    }
    return clockClosest;
<#else>
	return 0;
</#if>
}

/******************************************************************************
  Function:
    uint32_t SYS_CLK_ReferenceFrequencyGet ( CLK_BUSES_REFERENCE referenceBus )

  Summary:
    Gets the selected Reference clock bus frequency in Hertz.

  Description:
    This function gets frequency of the selected Reference clock bus in Hertz.

  Precondition:
    None.

  Parameters:
	referenceBus - Reference clock bus selection. One of the possible value from
				CLK_BUSES_REFERENCE enum. For devices that do not have multiple
				clock channels for Reference clock, CLK_BUS_REFERENCE_1 should be
				the selection.

  Returns:
    Clock frequency in Hz.

  Example:
    <code>
    unsigned long sysClockOutputHz;

    sysClockOutputHz = SYS_CLK_ReferenceFrequencyGet ( CLK_BUS_REFERENCE_3 );
    </code>

  Remarks:
    None.
 */

uint32_t SYS_CLK_ReferenceFrequencyGet ( CLK_BUSES_REFERENCE referenceBus )
{
<#if CONFIG_HAVE_REFCLOCK = true >
	return clkObject.referenceClock[referenceBus];
<#else>
	return 0;
</#if>
}

/******************************************************************************
  Function:
    void SYS_CLK_TaskError ( void )

  Summary:
    Informs the user on a clock failure by invoking the registered call back
    function.

  Description:
    This function informs the user on a clock failure by invoking the registered
    call back function. This must be called from the Fail Safe Clock Monitor (FSCM)
    interrupt service routine.
    
  Remarks:
    None.
*/

void SYS_CLK_TaskError ( void )
{
    if (clkObject.callback != NULL)
    {
        clkObject.callback ( clkObject.systemClockSource, clkObject.systemClock );
    } 
}

/******************************************************************************
  Function:
    void SYS_CLK_ReferenceClockSetup ( CLK_BUSES_REFERENCE referenceBus,
                                        SYS_CLK_REFERENCE_SETUP *refSetup )

  Summary:
    Initializes the Reference clock module. 

  Description:
    This function initializes the Reference clock module.
 *
  Remarks:
    None.
*/

void SYS_CLK_ReferenceClockSetup ( CLK_BUSES_REFERENCE referenceBus,
                                        SYS_CLK_REFERENCE_SETUP *refSetup )
{
<#if CONFIG_HAVE_REFCLOCK = true >
    _SYS_CLK_ReferenceClockSetup(referenceBus, refSetup);
</#if>
}

/******************************************************************************
  Function:
    void SYS_CLK_FRCTune ( SYS_CLK_FRC_TUNING_TYPE tuningData )

  Summary:
    Triggers the direct value-based FRC oscillator tuning.

  Description:
    This function tunes the FRC as per the given value. FRC
    tuning functionality has been provided to help customers compensate for
    temperature effects on the FRC frequency over a wide range of temperatures.

  Remarks:
    None.
*/

void SYS_CLK_FRCTune ( SYS_CLK_FRC_TUNING_TYPE tuningData )
{
    PLIB_OSC_FRCTuningSelect(OSC_ID_0, tuningData);
}

/******************************************************************************
  Function:
    void SYS_CLK_SecondaryOscillatorEnable ( void )

  Summary:
    Enables the secondary oscillator.

  Description:
    This function enables the secondary oscillator.

  Remarks:
    For more details refer sys_clk.h.
*/

void SYS_CLK_SecondaryOscillatorEnable ( void )
{
    /* Check for secondary oscillator status */
    if (!PLIB_OSC_SecondaryIsEnabled(OSC_ID_0))
    {    
        /* Unlock and enable secondary oscillator */
        SYS_DEVCON_SystemUnlock();
        
        PLIB_OSC_SecondaryEnable(OSC_ID_0);
        
        SYS_DEVCON_SystemLock();
    }
}

/******************************************************************************
  Function:
    void SYS_CLK_SecondaryOscillatorDisable ( void )

  Summary:
    Disables the secondary oscillator.

  Description:
    This function disables the secondary oscillator.

  Remarks:
    For more details refer sys_clk.h.
*/

void SYS_CLK_SecondaryOscillatorDisable ( void )
{
    /* Check for secondary oscillator status */
    if (PLIB_OSC_SecondaryIsEnabled(OSC_ID_0))
    {    
        /* Unlock and disable secondary oscillator*/
        SYS_DEVCON_SystemUnlock();
        
        PLIB_OSC_SecondaryDisable(OSC_ID_0);
        
        SYS_DEVCON_SystemLock();
    }
}

/******************************************************************************
  Function:
    bool SYS_CLK_SecondaryOscillatorIsEnabled ( void )

  Summary:
    Identifies whether secondary oscillator is enabled or disabled.

  Description:
    This function identifies whether the secondary oscillator is enabled or 
    disabled.
    
  Remarks:
    For more details refer sys_clk.h.
*/

bool SYS_CLK_SecondaryOscillatorIsEnabled ( void )
{
    return (PLIB_OSC_SecondaryIsEnabled(OSC_ID_0));
}
