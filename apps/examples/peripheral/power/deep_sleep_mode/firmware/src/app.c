/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

unsigned int i = 0;

uint32_t count;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_CHECK;
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( appData.state )
    {
        case APP_STATE_CHECK:
        {
            /* Check if the device was in Deep Sleep mode */
            if(PLIB_POWER_DeepSleepModeHasOccurred(POWER_ID_0))
            {
                //Clear the deep sleep status
                PLIB_POWER_DeepSleepStatusClear(POWER_ID_0);
                
                /* Release the I/O pins for the application control. */
                PLIB_DEVCON_SystemUnlock(DEVCON_ID_0);
                    PLIB_POWER_DeepSleepPortPinsStateRelease(POWER_ID_0);    
                PLIB_DEVCON_SystemLock(DEVCON_ID_0);
                
                if((PLIB_POWER_DeepSleepEventStatusGet(POWER_ID_0)& DEEP_SLEEP_EVENT_WDT_TIMEOUT))
                {
                    /* DSWDT timeout event has caused wake up, clear the status flag. */
                    PLIB_POWER_DeepSleepEventStatusClear(POWER_ID_0, DEEP_SLEEP_EVENT_WDT_TIMEOUT);
                    /* Read the count value from Deep sleep storage register. */
                    count = PLIB_POWER_DeepSleepGPRRead(POWER_ID_0, DEEP_SLEEP_GPR_0);
                    /* Resume the count on LEDs. */
                    appData.state = APP_STATE_OUTPUT_ON_LEDS;                    
                }
                else
                {
                    /* Device didn't wake up because of DSWDT timeout event. */
                    appData.state = APP_STATE_ERROR_WAKEUP_EVENT;
                }
            }
            
            else
            {
                /* LEDs count from '0' if the device was not in Deep Sleep mode. */
                count = 0;
                appData.state = APP_STATE_OUTPUT_ON_LEDS;
            }
            break;            
        }
        
        case APP_STATE_OUTPUT_ON_LEDS:
        {
            /* LEDs operation */
            if(count&0x001)
            {
                BSP_LEDOn(BSP_LED_1);
            }
            else
            {
                BSP_LEDOff(BSP_LED_1);                
            }
            if(count&0x002)
            {
                BSP_LEDOn(BSP_LED_2);
            }
            else
            {
                BSP_LEDOff(BSP_LED_2);                
            }            
            if(count&0x004)
            {
                BSP_LEDOn(BSP_LED_3);
            }
            else
            {
                BSP_LEDOff(BSP_LED_3);                
            }
            
            /* Reset the delay variable. */
            i = 0; 
            /* Put the application into delay state*/
            appData.state = APP_STATE_COUNT_DELAY;

           
            break;       
        }        
        case APP_STATE_COUNT_DELAY:
        {
            /*Poll on the SWITCH 2 press */
            if(0 == BSP_SwitchStateGet(BSP_SWITCH_2))
            {
                /* Enter Deep Sleep in the next cycle of the app task*/
                appData.state = APP_STATE_ENTER_DEEP_SLEEP;
            }
            else
            {
                /* Keep incrementing the delay variable if it's less than the blink delay */
                if (i < APP_LED_BLINK_DELAY)
                {
                    /* Increment count. */
                    i++;
                }
                /* update the count value after the delay*/
                else
                {
                    if(count < 7)
                    {
                        count++;
                    }
                    else
                    {
                        count = 0;
                    }
                    /* Update the LED states */
                    appData.state = APP_STATE_OUTPUT_ON_LEDS;
                }
            }
            break;
        }
        
        /* On SWITCH 2 press enter Deep Sleep Mode */
        case APP_STATE_ENTER_DEEP_SLEEP:
        {
            /* Deep Sleep setup */
            PLIB_DEVCON_SystemUnlock(DEVCON_ID_0);
                /* Save the binary count value to resume after the wakeup */
                PLIB_POWER_DeepSleepGPRWrite(POWER_ID_0, DEEP_SLEEP_GPR_0, count);
                /* Enable Deep Sleep Mode */
                PLIB_POWER_DeepSleepModeEnable(POWER_ID_0);
                /* Enable sleep/deep_sleep after wait */
                PLIB_OSC_OnWaitActionSet(OSC_ID_0, OSC_ON_WAIT_SLEEP);
            PLIB_DEVCON_SystemLock(DEVCON_ID_0);

            /* Device enters into deep sleep mode after wait instruction */
            _wait();

            /* POR didn't occur after the wake up and system resumed.
             * So, the device entered Sleep/Idle instead of Deep Sleep */ 
            appData.state = APP_STATE_ERROR;            
            break;
        }

        case APP_STATE_ERROR:
        {
            /* Device was in Sleep/Idle instead of Deep Sleep */
            BSP_LEDOn(BSP_LED_1);
            appData.state = APP_STATE_FAILURE;
            break;
        }
        
        case APP_STATE_ERROR_WAKEUP_EVENT:
        {
            /* Deep Sleep wake up source was not DSWDT */
            BSP_LEDOn(BSP_LED_2);
            appData.state = APP_STATE_FAILURE;
            break;
        }          

        case APP_STATE_FAILURE:
        {
            /* Reset the counter */
            count = 0;
            
            /* Stay here forever */
            break;
        }        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}
 

/*******************************************************************************
 End of File
 */
