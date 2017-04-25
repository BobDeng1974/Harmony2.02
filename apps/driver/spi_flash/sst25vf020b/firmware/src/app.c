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
uint8_t dataBuffer1[4096];
uint8_t dataBuffer2[4100];

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

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

void APP_SST25VF020BEventHandler
(
    DRV_SST25VF020B_BLOCK_EVENT event,
    DRV_SST25VF020B_BLOCK_COMMAND_HANDLE handle,
    uintptr_t context
)
{
    switch(event)
    {
        case DRV_SST25VF020B_EVENT_BLOCK_COMMAND_COMPLETE:
            {
                /* Update the eventMap depending on the command completed. */
                if (handle == appData.commandHandle[0])
                {
                    appData.eventMap |= 0x01 << 0;
                }

                if (handle == appData.commandHandle[1])
                {
                    appData.eventMap |= 0x01 << 1;
                }

                if (handle == appData.commandHandle[2])
                {
                    appData.eventMap |= 0x01 << 2;
                }

                break;
            }

        case DRV_SST25VF020B_EVENT_BLOCK_COMMAND_ERROR:
            {
                /* Set the MSB of eventMap to indicate that there has been an error. */
                appData.eventMap |= 0x01 << 7;
                break;
            }

        default:
            {
                break;
            }
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/* This function fills up the source buffer with data pattern to be written
 * onto the SPI Flash. */
void APP_PreFillData (void)
{
    uint16_t i = 0;

    for (i = 0; i < 4096; i++)
    {
        appData.sourceBuffer[i]= i + 1;
    }
}

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
    appData.state = APP_OPEN_SPI_FLASH_DRIVER;
    appData.sourceBuffer = &dataBuffer1[0];
    appData.targetBuffer = &dataBuffer2[0];
    appData.eventMap = 0;

    APP_PreFillData ();
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    uint16_t index = 0;

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_OPEN_SPI_FLASH_DRIVER:
        {
            appData.driverHandle = DRV_SST25VF020B_Open(DRV_SST25VF020B_INDEX_0, DRV_IO_INTENT_READWRITE | DRV_IO_INTENT_NONBLOCKING);
            if (appData.driverHandle != DRV_HANDLE_INVALID)
            {
                /* Driver open was successful. Register a event handler
                 * function with the driver. */
                DRV_SST25VF020B_BlockEventHandlerSet (appData.driverHandle, APP_SST25VF020BEventHandler, NULL);

                appData.state = APP_START_BLOCK_REQUESTS;
            }
            else
            {
                /* Stay in the same state until a valid driver handle is returned. */
            }
        
            break;
        }

        case APP_START_BLOCK_REQUESTS:
        {
            /* Queue a erase operation to erase 2 sectors(Each sector is 4KB
             * long) of memory starting from address 0. */
            DRV_SST25VF020B_BlockErase (appData.driverHandle, &appData.commandHandle[0], 0, 2);

            if (appData.commandHandle[0] == DRV_SST25VF020B_BLOCK_COMMAND_HANDLE_INVALID)
            {
                /* Failed to queue the erase operation. */
                appData.state = APP_ERROR;
                break;
            }

            /* Write 4096 bytes of data starting at address 2500. */
            DRV_SST25VF020B_BlockWrite (appData.driverHandle, &appData.commandHandle[1], &appData.sourceBuffer[0], 2500, 4096);
            if (appData.commandHandle[1] == DRV_SST25VF020B_BLOCK_COMMAND_HANDLE_INVALID)
            {
                /* Failed to queue the write operation. */
                appData.state = APP_ERROR;
                break;
            }

            /* Read 4098 bytes of data starting at address 2498. */
            DRV_SST25VF020B_BlockRead (appData.driverHandle, &appData.commandHandle[2], &appData.targetBuffer[2], 2498, 4098);
            if (appData.commandHandle[2] == DRV_SST25VF020B_BLOCK_COMMAND_HANDLE_INVALID)
            {
                /* Failed to queue the read operation. */
                appData.state = APP_ERROR;
                break;
            }

            appData.state = APP_WAIT_FOR_COMMAND_COMPLETE;

            break;
        }

        case APP_WAIT_FOR_COMMAND_COMPLETE:
        {
            if (appData.eventMap == 0x7)
            {
                /* All the queued commands have been executed successfully.
                 * Verify the read data. */
                appData.state = APP_VERIFY_DATA;
            }
            else if (appData.eventMap & 0x80)
            {
                /* There was an error while processing the queued commands. */
                appData.state = APP_ERROR;
            }

            break;
        }

        case APP_VERIFY_DATA:
        {
            /* Verify the read data with that of the written data. */
            if ((appData.targetBuffer[0] == 0) && (appData.targetBuffer[1] == 0) && (appData.targetBuffer[2] == 0xFF) && (appData.targetBuffer[3] == 0xFF))
            {
                appData.state = APP_SUCCESS;

                for (index = 0; index < 4096; index++)
                {
                    if(appData.sourceBuffer[index] != appData.targetBuffer[index + 4])
                    {
                        appData.state = APP_ERROR;
                        break;
                    }
                }
            }
            else
            {
                appData.state = APP_ERROR;
            }
            break;
        }

        case APP_SUCCESS:
        {
            BSP_LEDOn(BSP_LED_8);
            BSP_LEDOn(BSP_LED_9);
            appData.state = APP_IDLE;
            break;
        }

        case APP_ERROR:
        {
            BSP_LEDOn(BSP_LED_5);
            BSP_LEDOn(BSP_LED_6);
            appData.state = APP_IDLE;
            break;
        }

        case APP_IDLE:
        default:
        {
            break;
        }
    }
}
 
/*******************************************************************************
 End of File
 */
