<#--
/*******************************************************************************
Copyright (c) 2014 released Microchip Technology Inc.  All rights reserved.

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
<#--<#if !(GFX_TASKS?has_content)>
<#assign GFX_TASKS = "TASK_CALL_NO_RTOS">
</#if>
<#if (GFX_TASKS == "PROTO") && (CONFIG_GFX_RTOS == "Standalone")>
<#if CONFIG_3RDPARTY_RTOS_USED == "ThreadX">
void _GFX_Tasks(ULONG thread_input);
<#else>
void _GFX_Tasks(void);
</#if>
</#if>
<#if GFX_TASKS == "CREATE_TASK">
<#if CONFIG_GFX_RTOS == "Standalone">

    /* Create task for gfx state machine*/
<@RTOS_TASK_CREATE RTOS_NAME=CONFIG_3RDPARTY_RTOS_USED TASK_FUNC_NAME="_GFX_Tasks" TASK_NAME="GFX Tasks" TASK_PRI=CONFIG_GFX_RTOS_TASK_PRIORITY TASK_STK_SZ=CONFIG_GFX_RTOS_TASK_SIZE/>	
 </#if>
 </#if>
<#if (GFX_TASKS == "TASK_CALL_NO_RTOS") || (GFX_TASKS == "TASK_CALL" && CONFIG_GFX_RTOS != "Standalone")>
    GFX_Tasks(sysObj.gfxObject0);
    <#if (CONFIG_GFX_INST_1 = true)>
    GFX_Tasks(sysObj.gfxObject1);
    </#if>
    <#if (CONFIG_GFX_INST_2 = true)>
    GFX_Tasks(sysObj.gfxObject2);
    </#if>
 </#if>
 <#if GFX_TASKS == "LOCAL_FUNCTION">
 <#if CONFIG_GFX_RTOS == "Standalone">
<#if CONFIG_3RDPARTY_RTOS_USED == "ThreadX">
void _GFX_Tasks(ULONG thread_input)
<#else>
void _GFX_Tasks(void)
</#if>
{
<#if CONFIG_3RDPARTY_RTOS_USED == "uC/OS-III">
    OS_ERR os_err;
	
</#if> 
    while(1)
    {
        GFX_Tasks(sysObj.gfxObject0);
<@RTOS_TASK_DELAY RTOS_NAME=CONFIG_3RDPARTY_RTOS_USED TASK_DELAY=CONFIG_GFX_RTOS_DELAY/>		
    }
}
 </#if>
 </#if>-->

<#if CONFIG_GFXE_CONTEXT_0_ENABLED = true>
	// update graphics context 0
	GFX_Set(GFXF_CONTEXT_ACTIVE, (void*)sysObj.gfxContext0);
	GFX_Update();
	
</#if>
 
<#--
/*******************************************************************************
 End of File
*/
-->
