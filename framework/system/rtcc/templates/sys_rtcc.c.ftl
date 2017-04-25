<#--
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
 -->
// <editor-fold defaultstate="collapsed" desc="SYS_RTCC Initialization Data">
// *****************************************************************************
/* Real Time Clock Calendar Initialization Data
*/

const SYS_RTCC_INIT sysRtccInit =
{
    .moduleInit = {0},
<#if CONFIG_SYS_RTCC_OUTPUT_ENABLE == true>
    .outputEnabled = true,
    .outputSelect  = ${CONFIG_SYS_RTCC_OUTPUT_SELECT},
<#else>
    .outputEnabled = false,
</#if>

    .rtccTime = 0x${CONFIG_SYS_RTCC_TIME_SET}00,
    .rtccDate = 0x${CONFIG_SYS_RTCC_DATE_SET}0${CONFIG_SYS_RTCC_DAY_SET},

    .alarmTime = 0x${CONFIG_SYS_RTCC_ALARM_TIME_SET}00,
    .alarmDate = 0x00${CONFIG_SYS_RTCC_ALARM_DATE_SET}0${CONFIG_SYS_RTCC_ALARM_DAY_SET},
    .alarmMask = ${CONFIG_SYS_RTCC_ALARM_MASK_CONFIGURATION},
    .alarmRepeatForever = ${CONFIG_SYS_RTCC_ALARM_REPEAT_FOREVER?c},
<#if CONFIG_SYS_RTCC_ALARM_REPEAT_FOREVER == false>
    .alarmRepeatCount = ${CONFIG_SYS_RTCC_ALARM_REPEAT_COUNT},
</#if>
<#if CONFIG_HAVE_RTCC_WITH_CLOCKSELECT == true>
    .clockSource =  ${CONFIG_SYS_RTCC_CLOCK_SOURCE},
</#if>
<#if CONFIG_SYS_RTCC_INTERRUPT_MODE == true>

    .interruptUsed          = ${CONFIG_SYS_RTCC_INTERRUPT_MODE?c},
    .interruptVector        = ${CONFIG_SYS_RTCC_ISR_VECTOR},
    .interruptSource        = ${CONFIG_SYS_RTCC_INT_SOURCE},
    .interruptPriority      = ${CONFIG_SYS_RTCC_INT_PRIORITY},
    .interruptSubpriority   = ${CONFIG_SYS_RTCC_INT_SUBPRIORITY},
</#if>
};
// </editor-fold>
<#--
/*******************************************************************************
 End of File
*/
-->
