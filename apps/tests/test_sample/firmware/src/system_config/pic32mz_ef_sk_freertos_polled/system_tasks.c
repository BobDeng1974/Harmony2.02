/*******************************************************************************
 System Tasks File

  File Name:
    system_tasks.c

  Summary:
    This file contains source code necessary to maintain system's polled state
    machines.

  Description:
    This file contains source code necessary to maintain system's polled state
    machines.  It implements the "SYS_Tasks" function that calls the individual
    "Tasks" functions for all the MPLAB Harmony modules in the system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    polled in the system.  These handles are passed into the individual module
    "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system_config.h"
#include "system_definitions.h"
#include "app.h"


// *****************************************************************************
// *****************************************************************************
// Section: Local Prototypes
// *****************************************************************************
// *****************************************************************************


 
static void _SYS_Tasks ( void );
static void _TEST_HarnessTasks ( void );
static void _TEST_Tasks0 ( void );
static void _TEST_Tasks1 ( void );
static void _TEST_Library0Instance0Tasks0 ( void );
static void _TEST_Library0Instance1Tasks0 ( void );
static void _APP_Tasks(void);


// *****************************************************************************
// *****************************************************************************
// Section: System "Tasks" Routine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void SYS_Tasks ( void )

  Remarks:
    See prototype in system/common/sys_module.h.
*/

void SYS_Tasks ( void )
{
    /* Create OS Thread for Sys Tasks. */
    xTaskCreate((TaskFunction_t) _SYS_Tasks,
                "Sys Tasks",
                1024, NULL, 7, NULL);

    /* Create OS Thread for TEST Tasks 0. */
    xTaskCreate((TaskFunction_t) _TEST_Tasks0,
                "TEST Tasks 0",
                512, NULL, 4, NULL);

    /* Create OS Thread for TEST Tasks 1. */
    xTaskCreate((TaskFunction_t) _TEST_Tasks1,
                "TEST Tasks 1",
                512, NULL, 3, NULL);

    /* Create OS Thread for TEST Library 0 Instance 0 Tasks 0. */
    xTaskCreate((TaskFunction_t) _TEST_Library0Instance0Tasks0,
                "TEST Library 0 Instance 0 Tasks 0",
                512, NULL, 6, NULL);

    /* Create OS Thread for TEST Library 0 Instance 1 Tasks 0. */
    xTaskCreate((TaskFunction_t) _TEST_Library0Instance1Tasks0,
                "TEST Library 0 Instance 1 Tasks 0",
                512, NULL, 5, NULL);

    /* Create OS Thread for Test Harness. */
    xTaskCreate((TaskFunction_t) _TEST_HarnessTasks,
                "Test Harness",
                1024, NULL, 2, NULL);

    /* Create OS Thread for APP Tasks. */
    xTaskCreate((TaskFunction_t) _APP_Tasks,
                "APP Tasks",
                1024, NULL, 1, NULL);

    /**************
     * Start RTOS * 
     **************/
    vTaskStartScheduler(); /* This function never returns. */
}


/*******************************************************************************
  Function:
    void _SYS_Tasks ( void )

  Summary:
    Maintains state machines of system modules.
*/
static void _SYS_Tasks ( void)
{
    while(1)
    {
        /* Maintain system services */
        SYS_DEVCON_Tasks(sysObj.sysDevcon);

        /* Maintain Device Drivers */

        /* Maintain Middleware */

        /* Task Delay */
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}


/*******************************************************************************
  Function:
    void _TEST_HarnessTasks ( void )

  Summary:
    Maintains state machine of the test harness.
*/

static void _TEST_HarnessTasks ( void )
{
    while(1)
    {
        TEST_HarnessTasks();
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}


/*******************************************************************************
  Function:
    void _TEST_Tasks0 ( void )

  Summary:
    Maintains current test's "Tasks0 state machine.
*/

static void _TEST_Tasks0 ( void )
{
    while(1)
    {
        TEST_Tasks(TEST_TASKS_FUNCTION_0);
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}


/*******************************************************************************
  Function:
    void _TEST_Tasks1 ( void )

  Summary:
    Maintains current test's "Tasks1 state machine.
*/

static void _TEST_Tasks1 ( void )
{
    while(1)
    {
        TEST_Tasks(TEST_TASKS_FUNCTION_1);
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}


/*******************************************************************************
  Function:
    void _TEST_Library0Instance0Tasks0Daemon ( void )

  Summary:
    Maintains state machine of library under test 0 instance 0 tasks
    function 0:  "SAMPLE_Tasks".
*/

static void _TEST_Library0Instance0Tasks0 ( void )
{
    while(1)
    {
        TEST_LibraryTasksPolled(TEST_POS_0, TEST_LUT_INDEX_0, SAMPLE_Tasks);
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}


/*******************************************************************************
  Function:
    void _TEST_Library0Instance1Tasks0Daemon ( void )

  Summary:
    Maintains state machine of library under test 0 instance 1 tasks
    function 0:  "SAMPLE_Tasks".
*/

static void _TEST_Library0Instance1Tasks0 ( void )
{
    while(1)
    {
        TEST_LibraryTasksPolled(TEST_POS_0, TEST_LUT_INDEX_1, SAMPLE_Tasks);
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}


/*******************************************************************************
  Function:
    void _APP_Tasks ( void )

  Summary:
    Maintains state machine of APP.
*/

static void _APP_Tasks(void)
{
    while(1)
    {
        APP_Tasks();
        vTaskDelay(250 / portTICK_PERIOD_MS);
    }
}


/*******************************************************************************
 End of File
 */

