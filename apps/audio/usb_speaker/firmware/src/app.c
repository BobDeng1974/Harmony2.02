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


uint32_t Debug_var;
DRV_I2S_DATA16 APP_MAKE_BUFFER_DMA_READY rxBuffer[APP_QUEUING_DEPTH][APP_NO_OF_SAMPLES_IN_A_USB_FRAME];


APP_DATA appData =
{
    /* Device Layer Handle  */
    .usbDevHandle = -1,

    /* USB Audio Instance index for this app object 0*/
    .audioInstance = 0,

     /* app state */
    .state = APP_STATE_INIT,

    /* device configured status */
    .isConfigured = false,

    /* Initialize active interface setting to 0. */
    .activeInterfaceAlternateSetting = APP_USB_SPEAKER_PLAYBACK_NONE,

    /* DAC is not muted initially */
    .dacMute = false,

    .codecClient.context = (uintptr_t)0,
    .codecClient.bufferHandler = (DRV_CODEC_BUFFER_EVENT_HANDLER) APP_CODECBufferEventHandler,
    .codecClient.bufferSize = sizeof(rxBuffer[0]),
    /* No Audio control in progress.*/
    .currentAudioControl = APP_USB_CONTROL_NONE
};


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************
void APP_USBDeviceEventHandler( USB_DEVICE_EVENT event, void * pEventData, uintptr_t context )
{
    volatile USB_DEVICE_EVENT_DATA_CONFIGURED* configuredEventData;
    switch( event )
    {
        case USB_DEVICE_EVENT_RESET:
            break;

        case USB_DEVICE_EVENT_DECONFIGURED:
            // USB device is reset or device is de-configured.
            // This means that USB device layer is about to de-initialize
            // all function drivers. So close handles to previously opened
            // function drivers.

            // Also turn ON LEDs to indicate reset/de-configured state.
            /* Switch on red and orange, switch off green */
            APP_LED1_ON();
            APP_LED2_ON();
            APP_LED3_ON();
            APP_LED4_ON();
            APP_LED5_OFF();

            break;

        case USB_DEVICE_EVENT_CONFIGURED:
            /* check the configuration */
            configuredEventData = (USB_DEVICE_EVENT_DATA_CONFIGURED *)pEventData;
            if(configuredEventData->configurationValue == 1)
            {
                /* the device is in configured state */
                /* Switch on green and switch off red and orange */
                APP_LED1_OFF();
                APP_LED2_OFF();
                APP_LED3_OFF();
                APP_LED4_OFF();
                APP_LED5_ON();

                USB_DEVICE_AUDIO_EventHandlerSet
                (
                    0,
                    APP_USBDeviceAudioEventHandler ,
                    (uintptr_t)NULL
                );
                /* mark that set configuration is complete */
                appData.isConfigured = true;
            }
            break;

        case USB_DEVICE_EVENT_SUSPENDED:
            /* Switch on green and orange, switch off red */

            APP_LED1_OFF();
            APP_LED2_OFF();
            APP_LED3_OFF();
            APP_LED4_ON();
            APP_LED5_ON();

            break;

        case USB_DEVICE_EVENT_RESUMED:
        case USB_DEVICE_EVENT_POWER_DETECTED:
            /* VBUS was detected. Notify USB stack about the event */
            USB_DEVICE_Attach (appData.usbDevHandle);
            break;
        case USB_DEVICE_EVENT_POWER_REMOVED:
            /* VBUS was removed. Notify USB stack about the event*/
            USB_DEVICE_Detach (appData.usbDevHandle);
        case USB_DEVICE_EVENT_ERROR:
        default:
            break;
    }
}

void APP_USBDeviceAudioEventHandler
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    USB_DEVICE_AUDIO_EVENT event ,
    void * pData,
    uintptr_t context
)
{
    volatile USB_DEVICE_AUDIO_EVENT_DATA_INTERFACE_SETTING_CHANGED *interfaceInfo;
    volatile USB_DEVICE_AUDIO_EVENT_DATA_READ_COMPLETE *readEventData;
    uint8_t entityID;
    uint8_t controlSelector;

    if ( iAudio == 0 )
    {
        switch (event)
        {
            case USB_DEVICE_AUDIO_EVENT_INTERFACE_SETTING_CHANGED:
                /* We have received a request from USB host to change the Interface-
                   Alternate setting.*/
                interfaceInfo = (USB_DEVICE_AUDIO_EVENT_DATA_INTERFACE_SETTING_CHANGED *)pData;
                appData.activeInterfaceAlternateSetting = interfaceInfo->interfaceAlternateSetting;
                appData.state = APP_USB_INTERFACE_ALTERNATE_SETTING_RCVD;
            break;

            case USB_DEVICE_AUDIO_EVENT_READ_COMPLETE:
                readEventData = (USB_DEVICE_AUDIO_EVENT_DATA_READ_COMPLETE *)pData;
                //We have received an audio frame from the Host.
                //Now send this audio frame to Audio Codec for Playback.

                    if(readEventData->handle == appData.readTransferHandle1)
                    {
                        appData.isReadComplete1 = true;
                    }
                    else if(readEventData->handle == appData.readTransferHandle2)
                    {
                        appData.isReadComplete2 = true;
                    }
                    else
                    {
                        
                    }
                    appData.state = APP_PROCESS_DATA;
            break;

            case USB_DEVICE_AUDIO_EVENT_WRITE_COMPLETE:
            break;


            case USB_DEVICE_AUDIO_EVENT_CONTROL_SET_CUR:
                entityID = ((USB_AUDIO_CONTROL_INTERFACE_REQUEST*)pData)->entityID;
                if (entityID == APP_ID_FEATURE_UNIT)
                {
                   controlSelector = ((USB_AUDIO_FEATURE_UNIT_CONTROL_REQUEST*)pData)->controlSelector;
                   if (controlSelector == USB_AUDIO_MUTE_CONTROL)
                   {
                       //A control write transfer received from Host. Now receive data from Host.
                       USB_DEVICE_ControlReceive(appData.usbDevHandle, (void *) &(appData.dacMute), 1 );
                       appData.currentAudioControl = APP_USB_AUDIO_MUTE_CONTROL;
                   }
                }
                break;
            case USB_DEVICE_AUDIO_EVENT_CONTROL_GET_CUR:
                entityID = ((USB_AUDIO_CONTROL_INTERFACE_REQUEST*)pData)->entityID;
                if (entityID == APP_ID_FEATURE_UNIT)
                {
                   controlSelector = ((USB_AUDIO_FEATURE_UNIT_CONTROL_REQUEST*)pData)->controlSelector;
                   if (controlSelector == USB_AUDIO_MUTE_CONTROL)
                   {
                       /*Handle Get request*/
                       USB_DEVICE_ControlSend(appData.usbDevHandle, (void *)&(appData.dacMute), 1 );
                   }
                }
                break;
            case USB_DEVICE_AUDIO_EVENT_CONTROL_SET_MIN:
            case USB_DEVICE_AUDIO_EVENT_CONTROL_GET_MIN:
            case USB_DEVICE_AUDIO_EVENT_CONTROL_SET_MAX:
            case USB_DEVICE_AUDIO_EVENT_CONTROL_GET_MAX:
            case USB_DEVICE_AUDIO_EVENT_CONTROL_SET_RES:
            case USB_DEVICE_AUDIO_EVENT_CONTROL_GET_RES:
            case USB_DEVICE_AUDIO_EVENT_ENTITY_GET_MEM:
                /* Stall request */
                USB_DEVICE_ControlStatus (appData.usbDevHandle, USB_DEVICE_CONTROL_STATUS_ERROR);
            break;
            case USB_DEVICE_AUDIO_EVENT_CONTROL_TRANSFER_DATA_RECEIVED:
                USB_DEVICE_ControlStatus(appData.usbDevHandle, USB_DEVICE_CONTROL_STATUS_OK );
                if (appData.currentAudioControl == APP_USB_AUDIO_MUTE_CONTROL)
                {
                    appData.state = APP_MUTE_AUDIO_PLAYBACK;
                    appData.currentAudioControl = APP_USB_CONTROL_NONE;
                    //Handle Mute Control Here.
                }
            break;
            case  USB_DEVICE_AUDIO_EVENT_CONTROL_TRANSFER_DATA_SENT:
            break;
            default:
                SYS_ASSERT ( false , "Invalid callback" );
            break;
        } //end of switch ( callback )
    }//end of if  if ( iAudio == 0 )
}//end of function APP_AudioEventCallback

/******************************************************
 * Application Initialize. It is
 * called from the SYS_Initialized() function.
 ******************************************************/
void APP_Initialize (void)
{
    appData.isReadComplete1 = false;
    appData.isReadComplete2 = false;

    appData.readTransferHandle1 = USB_DEVICE_AUDIO_TRANSFER_HANDLE_INVALID;
    appData.readTransferHandle2 = USB_DEVICE_AUDIO_TRANSFER_HANDLE_INVALID;

    appData.codecClient.txbufferObject1 = (uint8_t *) rxBuffer[0];
    appData.codecClient.txbufferObject2 = (uint8_t *) rxBuffer[1];

    appData.codecClient.iswriteBufHandleAvailable1 = false;
    appData.codecClient.iswriteBufHandleAvailable2 = false;
}

/**********************************************************
 * Application tasks routine. This function implements the
 * application state machine.
 ***********************************************************/
USB_DEVICE_AUDIO_RESULT audioErr1;
void APP_Tasks (void )
{
    switch(appData.state)
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        /* Open the device layer */
            appData.usbDevHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0,
                    DRV_IO_INTENT_READWRITE );

            if(appData.usbDevHandle != USB_DEVICE_HANDLE_INVALID)
            {
                /* Register a callback with device layer to get event notification (for end point 0) */
                USB_DEVICE_EventHandlerSet(appData.usbDevHandle, APP_USBDeviceEventHandler, 0);

                appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
            }
            else
            {
                /* The Device Layer is not ready to be opened. We should try
                 * again later. */
            }

        case APP_STATE_WAIT_FOR_CONFIGURATION:
            //Check if Host has configured the Device.
            if (appData.isConfigured == true)
            {
                appData.state = APP_STATE_CODEC_OPEN;
            }
            break;

        case APP_STATE_CODEC_OPEN:
        {
            SYS_STATUS codecStatus;
            codecStatus = DRV_CODEC_Status(sysObjdrvCodec0);
            if (SYS_STATUS_READY == codecStatus)
            {
                // This means the driver can now be be opened.
                /* A client opens the driver object to get an Handle */
                appData.codecClient.handle = DRV_CODEC_Open(DRV_CODEC_INDEX_0, DRV_IO_INTENT_WRITE | DRV_IO_INTENT_EXCLUSIVE);
                if(appData.codecClient.handle != DRV_HANDLE_INVALID)
                {
                    appData.state = APP_STATE_CODEC_SET_BUFFER_HANDLER;
                }
                else
                {
                    SYS_DEBUG(0, "Find out whats wrong \r\n");
                }
            }
            else
            {
                /* Wait for CODEC to Initialize */
                ;
            }
        }
        break;

       case APP_SUBMIT_INITIAL_READ_REQUEST:
            if (appData.activeInterfaceAlternateSetting == APP_USB_SPEAKER_PLAYBACK_STEREO_48KHZ)
            {
                audioErr1 = USB_DEVICE_AUDIO_Read ( USB_DEVICE_INDEX_0 , &appData.readTransferHandle1, 1 , rxBuffer[0], 192 );
                audioErr1 = USB_DEVICE_AUDIO_Read ( USB_DEVICE_INDEX_0 , &appData.readTransferHandle2, 1 , rxBuffer[1], 192 );
                appData.state = APP_PROCESS_DATA;
            }
            else
            {
            }
        break;

       case APP_PROCESS_DATA:
       {
            DRV_CODEC_MuteOff(appData.codecClient.handle);
            /* Submit write to the CODEC driver */
            if(appData.isReadComplete1 == true)
            {
                appData.isReadComplete1 = false;
                appData.codecClient.writeBufHandle1 = DRV_CODEC_BUFFER_HANDLE_INVALID;
                DRV_CODEC_BufferAddWrite(appData.codecClient.handle, &appData.codecClient.writeBufHandle1,
                appData.codecClient.txbufferObject1, appData.codecClient.bufferSize);
            }
            else if(appData.isReadComplete2 == true)
            {
                appData.isReadComplete2 = false;
                appData.codecClient.writeBufHandle2 = DRV_CODEC_BUFFER_HANDLE_INVALID;
                DRV_CODEC_BufferAddWrite(appData.codecClient.handle, &appData.codecClient.writeBufHandle2,
                appData.codecClient.txbufferObject2, appData.codecClient.bufferSize);
            }
            else
            {
                ;
            }

            /* Submit a read request from USB */
            if (appData.codecClient.iswriteBufHandleAvailable1 == true)
            {
                appData.codecClient.iswriteBufHandleAvailable1 = false;
                appData.readTransferHandle1 = USB_DEVICE_AUDIO_TRANSFER_HANDLE_INVALID;
                audioErr1 = USB_DEVICE_AUDIO_Read ( USB_DEVICE_INDEX_0 , &appData.readTransferHandle1, 1 , rxBuffer[0], 192 );
            }
            else if(appData.codecClient.iswriteBufHandleAvailable2 == true)
            {
                appData.codecClient.iswriteBufHandleAvailable2 = false;
                appData.readTransferHandle2 = USB_DEVICE_AUDIO_TRANSFER_HANDLE_INVALID;
                audioErr1 = USB_DEVICE_AUDIO_Read ( USB_DEVICE_INDEX_0 , &appData.readTransferHandle2, 1 , rxBuffer[1], 192 );
            }
            else
            {
                ;
            }
       }

       break;

        /* Set a handler for the audio buffer completion event */
        case APP_STATE_CODEC_SET_BUFFER_HANDLER:
        {
            DRV_CODEC_BufferEventHandlerSet(appData.codecClient.handle,
                    appData.codecClient.bufferHandler,
                    appData.codecClient.context);
            appData.state = APP_IDLE;
        }
        break;

        case APP_MUTE_AUDIO_PLAYBACK:
        {
            if (appData.activeInterfaceAlternateSetting == 0)
            {
                DRV_CODEC_MuteOn(appData.codecClient.handle);
                appData.state = APP_IDLE;
            }
            else if (appData.activeInterfaceAlternateSetting == 1)
            {
                DRV_CODEC_MuteOff(appData.codecClient.handle);
                appData.state = APP_SUBMIT_INITIAL_READ_REQUEST;
            }
        }
        break;

        case APP_USB_INTERFACE_ALTERNATE_SETTING_RCVD:
        {
           SYS_STATUS codecStatus;

           if (appData.activeInterfaceAlternateSetting == APP_USB_SPEAKER_PLAYBACK_NONE)
            {
               codecStatus = DRV_CODEC_Status(sysObjdrvCodec0);
               if (SYS_STATUS_READY == codecStatus)
	       {
                   DRV_CODEC_MuteOn(appData.codecClient.handle);
                   appData.state = APP_IDLE;
	       }
            }
            else if(appData.activeInterfaceAlternateSetting == APP_USB_SPEAKER_PLAYBACK_STEREO_48KHZ)
            {
               codecStatus = DRV_CODEC_Status(sysObjdrvCodec0);
               if (SYS_STATUS_READY == codecStatus)
               {
                   DRV_CODEC_MuteOff(appData.codecClient.handle);
                   appData.state =  APP_SUBMIT_INITIAL_READ_REQUEST;
               }
            }
        }
        break;

        case APP_IDLE:
        {
            if (appData.activeInterfaceAlternateSetting == APP_USB_SPEAKER_PLAYBACK_NONE)
            {
                DRV_CODEC_MuteOn(appData.codecClient.handle);
            }
        }
        break;

        case APP_STATE_ERROR:
        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

/**********************************************************
 * Application CODEC buffer Event handler.
 * This function is called back by the CODEC driver when
 * a CODEC data buffer TX completes.
 ***********************************************************/
void APP_CODECBufferEventHandler(DRV_CODEC_BUFFER_EVENT event,
        DRV_CODEC_BUFFER_HANDLE handle, uintptr_t context )
{
    switch(event)
    {
        case DRV_CODEC_BUFFER_EVENT_COMPLETE:
        {
            if(appData.codecClient.writeBufHandle1 == handle)
            {
                appData.codecClient.iswriteBufHandleAvailable1 = true;
            }
            else if(appData.codecClient.writeBufHandle2 == handle)
            {
                appData.codecClient.iswriteBufHandleAvailable2 = true;
            }
            else
            {

            }
            appData.state = APP_PROCESS_DATA;
        }
        break;
        case DRV_CODEC_BUFFER_EVENT_ERROR:
        {
        } break;

        case DRV_CODEC_BUFFER_EVENT_ABORT:
        {
        } break;

    }
}

/*******************************************************************************
 End of File
 */

