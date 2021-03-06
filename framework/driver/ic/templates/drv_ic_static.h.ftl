/*******************************************************************************
  IC Driver Interface Declarations for Static Single Instance Driver

  Company:
    Microchip Technology Inc.

  File Name:
    drv_ic_static.h

  Summary:
    IC driver interface declarations for the static single instance driver.

  Description:
    The IC device driver provides a simple interface to manage the IC
    modules on Microchip microcontrollers. This file defines the interface
    Declarations for the IC driver.
    
  Remarks:
    Static interfaces incorporate the driver instance number within the names
    of the routines, eliminating the need for an object ID or object handle.
    
    Static single-open interfaces also eliminate the need for the open handle.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _DRV_IC_STATIC_H
#define _DRV_IC_STATIC_H

#ifdef __cplusplus
    extern "C" {
#endif

<#macro DRV_IC_STATIC_API DRV_INSTANCE>
// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance ${DRV_INSTANCE} for the static driver
// *****************************************************************************
// *****************************************************************************
void DRV_IC${DRV_INSTANCE}_Initialize(void);
void DRV_IC${DRV_INSTANCE}_Start(void);
void DRV_IC${DRV_INSTANCE}_Stop(void);
uint32_t DRV_IC${DRV_INSTANCE}_Capture32BitDataRead(void);
uint16_t DRV_IC${DRV_INSTANCE}_Capture16BitDataRead(void);
bool DRV_IC${DRV_INSTANCE}_BufferIsEmpty(void);
</#macro>
#define DRV_IC_Open(drvIndex, intent) (drvIndex)
#define DRV_IC_Close(handle)

<#if CONFIG_DRV_IC_INST_IDX0 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="0"/>
</#if>
<#if CONFIG_DRV_IC_INST_IDX1 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="1"/>
</#if>
<#if CONFIG_DRV_IC_INST_IDX2 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="2"/>
</#if>
<#if CONFIG_DRV_IC_INST_IDX3 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="3"/>
</#if>
<#if CONFIG_DRV_IC_INST_IDX4 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="4"/>
</#if>
<#if CONFIG_DRV_IC_INST_IDX5 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="5"/>
</#if>
<#if CONFIG_DRV_IC_INST_IDX6 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="6"/>
</#if>
<#if CONFIG_DRV_IC_INST_IDX7 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="7"/>
</#if>
<#if CONFIG_DRV_IC_INST_IDX8 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="8"/>
</#if>
<#if CONFIG_DRV_IC_INST_IDX9 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="9"/>
</#if>
<#if CONFIG_DRV_IC_INST_IDX10 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="10"/>
</#if>
<#if CONFIG_DRV_IC_INST_IDX11 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="11"/>
</#if>
<#if CONFIG_DRV_IC_INST_IDX12 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="12"/>
</#if>
<#if CONFIG_DRV_IC_INST_IDX13 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="13"/>
</#if>
<#if CONFIG_DRV_IC_INST_IDX14 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="14"/>
</#if>
<#if CONFIG_DRV_IC_INST_IDX15 == true>
<@DRV_IC_STATIC_API DRV_INSTANCE="15"/>
</#if>

#ifdef __cplusplus
}
#endif

#endif // #ifndef _DRV_IC_STATIC_H

/*******************************************************************************
 End of File
*/
