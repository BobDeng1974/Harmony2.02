/*******************************************************************************
  MPLAB Harmony Graphics Composer Generated Implementation File

  File Name:
    libaria_harmony.c

  Summary:
    Build-time generated implementation from the MPLAB Harmony
    Graphics Composer.

  Description:
    Build-time generated implementation from the MPLAB Harmony
    Graphics Composer.

    Created with MPLAB Harmony Version ${CONFIG_MPLAB_HARMONY_VERSION_STRING}
*******************************************************************************/
// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

#include "gfx/libaria/libaria_harmony.h"
#include "gfx/libaria/libaria_init.h"

#include "gfx/libaria/libaria.h"

<#if CONFIG_LIBARIA_GENERATE_TOUCH?? && CONFIG_LIBARIA_GENERATE_TOUCH == true>
</#if>

/*** libaria Object Global ***/
libaria_objects libariaObj;
static LIBARIA_STATES libariaState;

<#if CONFIG_LIBARIA_GENERATE_TOUCH?? && CONFIG_LIBARIA_GENERATE_TOUCH == true>
/*** Message System Service Globals ***/
SYS_MSG_INSTANCE iSysMsg = SYS_MSG_0;
SYS_OBJ_HANDLE hSysMsg, hMsgType, hMailbox;

void LibAria_TouchMessageCallback(SYS_MSG_OBJECT *pMsg);

</#if>
<#if CONFIG_LIBARIA_MEMORY_INTERFACE?? && CONFIG_LIBARIA_MEMORY_INTERFACE == true>
GFXU_MemoryIntf memIntf;

static GFX_Result LibAria_MemoryReadRequest(GFXU_ExternalAssetReader* reader,
                                            uint32_t location_id,
                                            void* address,
                                            uint32_t readSize,
                                            uint8_t* destBuffer,
                                            GFXU_MemoryReadRequestCallback_FnPtr cb);

<#if CONFIG_LIBARIA_MEMORY_INTERFACE_FUNCTION?? && CONFIG_LIBARIA_MEMORY_INTERFACE_FUNCTION?has_content>
GFX_Result ${CONFIG_LIBARIA_MEMORY_INTERFACE_FUNCTION}(GFXU_ExternalAssetReader* reader,
        uint32_t location_id,
		void* address,
		uint32_t readSize,
		uint8_t* destBuffer,
		GFXU_MemoryReadRequestCallback_FnPtr cb);											
</#if>
		
</#if>
int32_t LibAria_Initialize(void) 
{
	if(laInitialize() == LA_FAILURE)
		return -1;
		
<#if CONFIG_LIBARIA_MEMORY_INTERFACE?? && CONFIG_LIBARIA_MEMORY_INTERFACE == true>
	memIntf.heap.malloc = &malloc;
	memIntf.heap.coherent_alloc = &__pic32_alloc_coherent;
	memIntf.heap.calloc = &calloc;
	memIntf.heap.free = &free;
	memIntf.heap.coherent_free = &__pic32_free_coherent;
	memIntf.heap.memcpy = &memcpy;
	memIntf.heap.memset = &memset;
	memIntf.heap.realloc = &realloc;
	memIntf.read = &LibAria_MemoryReadRequest;
	
	libariaObj.context = laContext_Create(0, 0, 0, <#if CONFIG_LIBARIA_CONTEXT_COLOR_MODE??>${CONFIG_LIBARIA_CONTEXT_COLOR_MODE}<#else>${CONFIG_DRV_GFX_DISPLAY_COLORS}</#if>, &memIntf);

<#else>
	libariaObj.context = laContext_Create(0, 0, 0, <#if CONFIG_LIBARIA_CONTEXT_COLOR_MODE??>${CONFIG_LIBARIA_CONTEXT_COLOR_MODE}<#else>${CONFIG_DRV_GFX_DISPLAY_COLORS}</#if>, NULL);

</#if>	
	if(libariaObj.context == NULL)
		return -1;
	
	laContext_SetActive(libariaObj.context);
	
	libaria_initialize();

<#if CONFIG_LIBARIA_GENERATE_TOUCH?? && CONFIG_LIBARIA_GENERATE_TOUCH == true>	
	hMsgType = SYS_MSG_TypeCreate(SYS_MSG_0, TYPE_TOUCHSCREEN , 0);
    hMailbox = SYS_MSG_MailboxOpen(SYS_MSG_0, (SYS_MSG_RECEIVE_CALLBACK) &LibAria_TouchMessageCallback );
    SYS_MSG_MailboxMsgAdd( hMailbox, hMsgType);
	
</#if>
	libariaState = LIBARIA_STATE_RUNNING;
	
	return 0;
}

void LibAria_Tasks(void)
{
    switch(libariaState)
    {
        case LIBARIA_STATE_RUNNING:
		{
			laContext_SetActive(libariaObj.context);
			laUpdate(0);
            
			break;
		}
        
		default:
		{
            break;
		}
    }
}

<#if CONFIG_LIBARIA_GENERATE_TOUCH?? && CONFIG_LIBARIA_GENERATE_TOUCH == true>	
void LibAria_TouchMessageCallback(SYS_MSG_OBJECT *pMsg)
{	
	if(pMsg->nMessageTypeID == TYPE_TOUCHSCREEN)
	{
		if(pMsg->param0 == EVENT_PRESS)
		{
			laInput_InjectTouchDown(0, pMsg->param1, pMsg->param2);
		}
		else if(pMsg->param0 == EVENT_RELEASE)
		{
			laInput_InjectTouchUp(0, pMsg->param1, pMsg->param2);
		}
		else if(pMsg->param0 == EVENT_MOVE)
		{
			laInput_InjectTouchMoved(0, pMsg->param1, pMsg->param2);
		}
	}
	else if(pMsg->nMessageTypeID == TYPE_KEYBOARD)
	{
	
	}
	else if(pMsg->nMessageTypeID == TYPE_MOUSE)
	{
	
	}
}

</#if>
<#if CONFIG_LIBARIA_MEMORY_INTERFACE?? && CONFIG_LIBARIA_MEMORY_INTERFACE == true>
static GFX_Result LibAria_MemoryReadRequest(GFXU_ExternalAssetReader* reader,
                                            uint32_t location_id,
                                            void* address,
                                            uint32_t readSize,
                                            uint8_t* destBuffer,
                                            GFXU_MemoryReadRequestCallback_FnPtr cb)
{
<#if CONFIG_LIBARIA_MEMORY_INTERFACE_FUNCTION?? && CONFIG_LIBARIA_MEMORY_INTERFACE_FUNCTION?has_content>
	return ${CONFIG_LIBARIA_MEMORY_INTERFACE_FUNCTION}(reader, location_id, address, readSize, destBuffer, cb);
<#else>
    return GFX_FAILURE;
</#if>
}
</#if>
<#--
/*******************************************************************************
 End of File
*/
-->
