/*******************************************************************************
 System Tasks File

  File Name:
    rtos_hooks.c

  Summary:
    This file contains source code necessary for rtos hooks

  Description:

  Remarks:
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

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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
<#if (CONFIG_3RDPARTY_RTOS_USED == "FreeRTOS") || (CONFIG_3RDPARTY_RTOS_USED == "OpenRTOS_V8.x.x")>
#include "FreeRTOS.h"
#include "task.h"
</#if>

<#if CONFIG_FREERTOS_STACK_OVERFLOW_CHECK_METHOD_1 || CONFIG_FREERTOS_STACK_OVERFLOW_CHECK_METHOD_2>
/*
*********************************************************************************************************
*                                          vApplicationStackOverflowHook()
*
* Description : Hook function called by FreeRTOS if a stack overflow happens.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : APP_StateReset()
*
* Note(s)     : none.
*********************************************************************************************************
*/
void vApplicationStackOverflowHook( TaskHandle_t pxTask, signed char *pcTaskName )
{
   ( void ) pcTaskName;
   ( void ) pxTask;

   /* Run time task stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook	function is
   called if a task stack overflow is detected.  Note the system/interrupt
   stack is not checked. */
   taskDISABLE_INTERRUPTS();
   for( ;; );
}
</#if>

<#if CONFIG_FREERTOS_USE_MALLOC_FAILED_HOOK>
/*
*********************************************************************************************************
*                                     vApplicationMallocFailedHook()
*
* Description : vApplicationMallocFailedHook() will only be called if
*               configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.
*               It is a hook function that will get called if a call to
*               pvPortMalloc() fails.  pvPortMalloc() is called internally by
*               the kernel whenever a task, queue, timer or semaphore is
*               created.  It is also called by various parts of the demo
*               application.  If heap_1.c or heap_2.c are used, then the size of
*               the heap available to pvPortMalloc() is defined by
*               configTOTAL_HEAP_SIZE in FreeRTOSConfig.h, and the
*               xPortGetFreeHeapSize() API function can be used to query the
*               size of free heap space that remains (although it does not
*               provide information on how the remaining heap might be
*               fragmented).
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : APP_StateReset()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void vApplicationMallocFailedHook( void )
{
   /* vApplicationMallocFailedHook() will only be called if
      configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
      function that will get called if a call to pvPortMalloc() fails.
      pvPortMalloc() is called internally by the kernel whenever a task, queue,
      timer or semaphore is created.  It is also called by various parts of the
      demo application.  If heap_1.c or heap_2.c are used, then the size of the
      heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
      FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
      to query the size of free heap space that remains (although it does not
      provide information on how the remaining heap might be fragmented). */
   taskDISABLE_INTERRUPTS();
   for( ;; );
}
</#if>

<#if CONFIG_FREERTOS_IDLE_HOOK>
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function  then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}

/*-----------------------------------------------------------*/
</#if>

<#if CONFIG_FREERTOS_TICK_HOOK>
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This function will be called by each tick interrupt if
	configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
	added here, but the tick hook is called from an interrupt context, so
	code must not attempt to block, and only the interrupt safe FreeRTOS API
	functions can be used (those that end in FromISR()). */
}

/*-----------------------------------------------------------*/
</#if>

<#if CONFIG_FREERTOS_TICK_HOOK>
/*-----------------------------------------------------------*/

/* Error Handler */
void vAssertCalled( const char * pcFile, unsigned long ulLine )
{
   volatile unsigned long ul = 0;

   ( void ) pcFile;
   ( void ) ulLine;

   taskENTER_CRITICAL();
   {
      /* Set ul to a non-zero value using the debugger to step out of this
         function. */
      while( ul == 0 )
      {
         portNOP();
      }
   }
   taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/
</#if>

<#if CONFIG_FREERTOS_STATIC_ALLOC>
/*-----------------------------------------------------------*/
/* The application must provide an implementation of vApplicationGetIdleTaskMemory() 
  to provide the memory that is used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xIdleTaskTCB;
static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];//user can set this size as needed

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;//user can set this size as needed
}
/*-----------------------------------------------------------*/
</#if>

<#if CONFIG_FREERTOS_STATIC_ALLOC && CONFIG_FREERTOS_USE_TIMERS >
/*-----------------------------------------------------------*/
/* The application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];//user can set this size as needed

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;//user can set this size as needed
}
/*-----------------------------------------------------------*/
</#if>

<#if CONFIG_FREERTOS_DAEMON_TASK_STARTUP_HOOK >
/*-----------------------------------------------------------*/

/* Application Daemon Task Startup hook */
void vApplicationDaemonTaskStartupHook( void )
{

 /* For this function to get called, the macro configUSE_DAEMON_TASK_STARTUP_HOOK has 
  to be set to 1 in FreeRTOSConfig.h. This gets executed once when the RTOS daemon task 
  (which used to be called the timer service task) starts running.  This is useful 
  if the application includes initialisation code that would benefit from executing 
  after the scheduler has been started.*/

  //user code can be added here
}
/*-----------------------------------------------------------*/
</#if>

/*******************************************************************************
 End of File
 */

 
