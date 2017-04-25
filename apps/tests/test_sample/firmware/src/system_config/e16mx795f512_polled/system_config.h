/*******************************************************************************
  MPLAB Harmony System Configuration Header

  File Name:
    system_config.h

  Summary:
    Build-time configuration header for the system defined by this MPLAB Harmony
    project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    This configuration header must not define any prototypes or data
    definitions (or include any files that do).  It only provides macro
    definitions for build-time configuration options that are not instantiated
    until used by another MPLAB Harmony module or application.

    Created with MPLAB Harmony Version 2.00
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

#ifndef _SYSTEM_CONFIG_H
#define _SYSTEM_CONFIG_H

/* This is a temporary workaround for an issue with the peripheral library "Exists"
   functions that causes superfluous warnings.  It "nulls" out the definition of
   The PLIB function attribute that causes the warning.  Once that issue has been
   resolved, this definition should be removed. */
#define _PLIB_UNSUPPORTED


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END 

// *****************************************************************************
// *****************************************************************************
// Section: System Service Configuration
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Common System Service Configuration Options
*/
#define SYS_VERSION_STR           "1.07"
#define SYS_VERSION               10700

// *****************************************************************************
/* Clock System Service Configuration Options
*/
#define SYS_CLK_FREQ                        80000000ul
#define SYS_CLK_BUS_PERIPHERAL_1            80000000ul
#define SYS_CLK_UPLL_BEFORE_DIV2_FREQ       7999992ul
#define SYS_CLK_CONFIG_PRIMARY_XTAL         8000000ul
#define SYS_CLK_CONFIG_SECONDARY_XTAL       0ul

/*** Interrupt System Service Configuration ***/
#define SYS_INT                     true

// *****************************************************************************
/* Debug System Service Configuration Options

   Remarks:
    Configures debug print and message macros to execute a software breakpoint
    if the error level is equal or greater SYS_ERROR_ERROR.
*/

#define SYS_DEBUG_PRINT(level, format, ...)  do{if ((level) <= SYS_ERROR_ERROR) SYS_DEBUG_BreakPoint();}while(0)
#define SYS_DEBUG_MESSAGE(level, message)    do{if ((level) <= SYS_ERROR_ERROR) SYS_DEBUG_BreakPoint();}while(0)


// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************


/******************************************************************************
  Sample Library Module Configuration Options

  <editor-fold defaultstate="collapsed"
   desc="Sample Library Module Configuration Options">
*/

#define SAMPLE_MODULE_INSTANCES_NUMBER  2
#define SAMPLE_MODULE_INTERRUPT_MODE    false
#define SAMPLE_MODULE_TIMEOUT           100

#define SAMPLE_MODULE_POWER_STATE_IDX0  SYS_MODULE_POWER_RUN_FULL
#define SAMPLE_MODULE_SOME_DATA_IDX0    42

#define SAMPLE_MODULE_POWER_STATE_IDX1  SYS_MODULE_POWER_RUN_FULL
#define SAMPLE_MODULE_SOME_DATA_IDX1    43
// </editor-fold>

/******************************************************************************
  Test Harness Configuration Options

  <editor-fold defaultstate="collapsed"
   desc="Test Harness Configuration Options">
*/

#define TEST_HARNESS_MAX_NUM_TASKS                      2
#define TEST_HARNESS_MAX_NUM_INSTANCES_PER_LIBRARY      3
#define TEST_HARNESS_MAX_NUM_TASKS_PER_LIBRARY          5

/* Test Timeout Timer configuration Options. */
#define TEST_TIMER_ID                       TMR_ID_1
#define TEST_TIMER_INTERRUPT_SOURCE         INT_SOURCE_TIMER_1
#define TEST_TIMER_CLOCK_SOURCE             TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK
#define TEST_TIMER_CLOCK_PRESCALER          TMR_PRESCALE_VALUE_256
#define TEST_TIMER_INCREMENT_PERIOD         31250
#define TEST_TIMER_MS_PER_INCREMENT         100
#define TEST_TIMER_MS_TIMEOUT               5000
#define TEST_TIMER_INTERRUPT_VECTOR         INT_VECTOR_T1
#define TEST_TIMER_INTERRUPT_PRIORITY       INT_PRIORITY_LEVEL1
#define TEST_TIMER_INTERRUPT_SUBPRIORITY    INT_SUBPRIORITY_LEVEL0

/* Test OSAL Idle Sleep Time Configuration Options. */
#define TEST_IDLE_SLEEP_MS_LIBRARY          5
#define TEST_IDLE_SLEEP_MS                  50
// </editor-fold>

/*******************************************************************************
  Sample Functional Test Configuration Options

  <editor-fold defaultstate="collapsed"
   desc="Sample Functional Test Configuration Options">
*/

#define TEST_SAMPLE_FUNC_LIB_INSTANCES_NUMBER   2
#define TEST_SAMPLE_MAX_ITERATIONS              5
// </editor-fold>


//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END


#endif // _SYSTEM_CONFIG_H
/*******************************************************************************
 End of File
*/

