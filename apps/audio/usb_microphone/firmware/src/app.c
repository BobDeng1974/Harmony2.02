/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c for usb_microphone

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
#if defined( ENABLE_SYS_LOG )
  #include "application/sys_log/sys_log.h"
#endif
#include "library/sys_log/sys_log_define.h"

//=============================================================================
//DEBUG
//
//DEBUG_TONE_INJECT:  Send tone buffer 
//DEBUG_LOOPBACK:     Loopback data to the CODEC DAC.
//
//  LOGIC TABLE
//  TONE | LOOPBACK |
//  0    | 0        | Normal Operation (CODEC Read)
//  0    | 1        | Loopback Mic data/No USB Tx (CODEC RW)
//  1    | 0        | USB Tx Sine tone (CODEC Read)
//  1    | 1        | ---------------- /Loopback Sin Tone (CODEC RW)
//
//NOTE:  The only mode that works correctly is Normal operation 4/15/16
#undef DEBUG_TONE_INJECT
#undef DEBUG_LOOPBACK  

#if defined(DEBUG_TONE_INJECT)
uint32_t Debug_var;

//Stereo sine test tone 
//NOTE:  USB requires 32 sample(stereo) frame buffers. 

//uint16_t scaleQ1d15 = 0x4000; //Scale multiplier .5
uint16_t scaleQ1d15 = 0x2000; //Scale multiplier .25

//Sin Tone Table
//NOTE:  DRV_I2S_DATA16 has .left and .right members, each uint16_t
//       format of initializer:
//           { { valLeft0, valRight0 }, { ... }, ... {valLeftN, valRightN}, }
//       Only using 1 channel of the tone data.
DRV_I2S_DATA16 sinToneQ1d15[]=
{
//Two cycles of sine tone (16 samples/cycle).
//NOTE:  This matches the size of the USB Audio Buffer.
//NOTE:  3000Hz stereo tone has 16/17 samples at 48Khz
#include "tone_1000Hz_2Cy_16bit_16Khz.txt"    
};

uint16_t sinSampleCount = sizeof(sinToneQ1d15)/sizeof(DRV_I2S_DATA16); //32
#define TONE_SAMPLES_PER_CYCLE 16  //Samples are 16bit stereo
#define TONE_NUMBER_OF_CYCLES   2
#define TONE_BUFFER_SIZE_BYTES  (TONE_SAMPLES_PER_CYCLE*2)
#endif //DEBUG_TONE_INJECT
//END DEBUG
//=============================================================================


//CODEC read data (mic data) buffer. 
//--ping-pong (2) buffers/32 16bit stereo samples {leftData, rightData}
//--Q1.15 data/2channels
//
// DRV_I2S_DATA16 { .leftData .rightData } uint16_t each channel
//
// NOTE: CODEC set as mono --> despite SPI_AUDIO_TRANSMIT_STEREO MHC selection
//       Data received as mono at 16Khz
//
// NOTE: Cache coherency and 16 byte alignment required for MZ processor,
//       -->as the cache page size on PIC32MZ is 16 bytes.
//       You don’t want to run into an issue where linker allocates the data 
//       structure in the same page as another data structure and then a line 
//       flush causes coherency issues.
#define APP_USB_FRAMESIZE_SAMPLES 16//Make the same size  TONE_SAMPLES_PER_CYCLE
#define APP_USB_FRAMESIZE_BYTES  APP_USB_FRAMESIZE_SAMPLES*4 //stereo samples --> mono
//DRV_I2S_DATA16 APP_MAKE_BUFFER_DMA_READY  
//    rxBuffer[APP_QUEUING_DEPTH][APP_USB_FRAMESIZE_SAMPLES]; //16x2 samples
DRV_I2S_DATA16 APP_MAKE_BUFFER_DMA_READY 
    __attribute__((coherent)) __attribute__((aligned(16))) 
    rxBuffer[APP_QUEUING_DEPTH][APP_USB_FRAMESIZE_SAMPLES];

//USB Tx Buffer for Mono Sine Tone data
//--Q1.15 data/1channel
//NOTE:  Make the APP_USB_FRAMESIZE_BYTES the same as the TONE_BUFFER_SIZE_BYTES
int16_t 
    __attribute__((coherent)) __attribute__((aligned(16))) 
    usbTxBuffer1[APP_USB_FRAMESIZE_SAMPLES];  //16
int16_t 
    __attribute__((coherent)) __attribute__((aligned(16))) 
    usbTxBuffer2[APP_USB_FRAMESIZE_SAMPLES];  //16

uint32_t usbWriteError=0;

APP_DATA appData =
{


    // Device Layer Handle
    .usbDevHandle = -1,

    // USB Audio Instance index for this app object 0
    .audioInstance = 0,

     /* app state */
    .state = APP_STATE_INIT,

    /* device configured status */
    .isConfigured = false,

    /* Initialize active interface setting to 0. */
    .activeInterfaceAlternateSetting = APP_USB_SPEAKER_PLAYBACK_NONE,

    // Initialize active USB interface setting 
    // --Holds active value of USB Audio Streaming Interface Alternate setting.
    // Every USB Audio Streaming should have 1 or more Alternate settings.
    // Alternate setting Zero (or Default Alternate setting) never has any
    // data payload. An audio streaming can have multiple number of alternate
    // settings each having it own sampling rate, bandwidth etc. 
    //--Set by the APP_USBDeviceAudioEventHandler() 
    //.activeInterfaceAlternateSetting    = APP_USB_SPEAKER_PLAYBACK_NONE;
    //.activeInterfaceAlternateSettingMic = APP_USB_MIC_RECORD_MONO_16KHZ;

    // Holds current value of Audio Control Mute settings. A value True indicates
    // audio is currently muted. */
    .dacMute = false,

    //NULL to start
    //.codecClient.handle          = 0,
    //.codecClient.context         = (uintptr_t)0,
    //.codecClient.txbufferObject1 = (uint8_t *) 0,
    //.codecClient.txbufferObject2 = (uint8_t *) 0,
    .codecClient.context = (uintptr_t)0,
    .codecClient.bufferHandler = (DRV_CODEC_BUFFER_EVENT_HANDLER) APP_CODECBufferEventHandler,
    .codecClient.bufferSize = sizeof(rxBuffer[0]),
    
    //Initialize Mic Settings
    .midCtrl  = 0x0F,
    .midMax   = 0x3F,
    .midMin   = 0xF0,
    .midRes   = 0x04,
    .autoGain = true,

    // This is to indicate which Audio Control Transfer is currently
    // in progress. */
    // --No Audio control in progress.
    .currentAudioControl = APP_USB_CONTROL_NONE,

            
    //CODEC Read Buffer Available after USB write
    .isReadBufHandleAvailable1 = false,
    .isReadBufHandleAvailable2 = false,
            
    //CODEC Read Buffer Handle
    .readBufHandle1 = DRV_CODEC_BUFFER_HANDLE_INVALID,
    .readBufHandle2 = DRV_CODEC_BUFFER_HANDLE_INVALID,

    .ping1Pong2 = true,

}; //End appData initialization 

uint8_t muteonflag = 0;


//APP_MIC_DATA appMicData=
//{
//    .state = APP_MIC_STATE_INIT,
//};


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

//=============================================================================
// APP_USBDeviceEventHandler()
//=============================================================================
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

} // End APP_USBDeviceEventHandler()


//=============================================================================
// APP_USBDeviceAudioEventHandler()
//=============================================================================
void APP_USBDeviceAudioEventHandler
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    USB_DEVICE_AUDIO_EVENT event ,
    void * pData,
    uintptr_t context
)
{
    volatile USB_DEVICE_AUDIO_EVENT_DATA_INTERFACE_SETTING_CHANGED *interfaceInfo;
    //volatile USB_DEVICE_AUDIO_EVENT_DATA_READ_COMPLETE *readEventData;
    USB_DEVICE_AUDIO_EVENT_DATA_WRITE_COMPLETE *writeEventData;
    uint8_t entityID;
    uint8_t controlSelector;
    //volatile uint8_t index;

    if ( iAudio == 0 )
    {
        switch (event)
        {
            case USB_DEVICE_AUDIO_EVENT_INTERFACE_SETTING_CHANGED:

                /* We have received a request from USB host to change the Interface-
                   Alternate setting.*/
                interfaceInfo = (USB_DEVICE_AUDIO_EVENT_DATA_INTERFACE_SETTING_CHANGED *)pData;
                appData.activeInterface = interfaceInfo->interfaceNumber;
                if(appData.activeInterface == 1)
                {
                    appData.activeInterfaceAlternateSettingMic = interfaceInfo->interfaceAlternateSetting;
                    appData.state = APP_MIC_USB_INTERFACE_ALTERNATE_SETTING_RCVD;
                    //LATHINV = 0x0002;
                }

                  //TODO:  Other activeInterfaceAlternateSettings

            break;

            case USB_DEVICE_AUDIO_EVENT_READ_COMPLETE:

                  //TODO:  Implement the read complete for microphone

                //readEventData = (USB_DEVICE_AUDIO_EVENT_DATA_READ_COMPLETE *)pData;
                ////We have received an audio frame from the Host.
                ////Now send this audio frame to Audio Codec for Playback.
                //
                //if(readEventData->handle == appData.readTransferHandle1)
                //{
                //    appData.isReadComplete1 = true;
                //}
                //else if(readEventData->handle == appData.readTransferHandle2)
                //{
                //    appData.isReadComplete2 = true;
                //}
                //else
                //{
                //                        
                //}
                //    appData.state = APP_PROCESS_DATA;
                
            break;

            case USB_DEVICE_AUDIO_EVENT_WRITE_COMPLETE:
                writeEventData = (USB_DEVICE_AUDIO_EVENT_DATA_WRITE_COMPLETE *)pData;
                //Audio frame was written to the Host.
                //Now get next frame from Audio Codec.
                if (writeEventData->handle == appData.writeTransferHandle1)
                {
                    //if(appMicData.state == APP_IDLE)
                    //    appMicData.state = APP_MIC_READ_DATA_FROM_CODEC;
                    //else
                    //   appMicData.state = APP_STATE_ERROR;
                    appData.isReadBufHandleAvailable1 = true;
                    appData.state = APP_PROCESS_DATA;
                    
                }
                else if(writeEventData->handle == appData.writeTransferHandle2)
                {
                    appData.isReadBufHandleAvailable2 = true;
                    appData.state = APP_PROCESS_DATA;
                }
                else
                {
                }
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
                if (entityID == APP_ID_FEATURE_UNIT_MIC)
                {
                   controlSelector = ((USB_AUDIO_FEATURE_UNIT_CONTROL_REQUEST*)pData)->controlSelector;
                   if (controlSelector == USB_AUDIO_MID_CONTROL)
                   {
                       /*Handle Get request*/
                       USB_DEVICE_ControlSend(appData.usbDevHandle, (void *)&(appData.midCtrl), 1 );
                   }
                   if (controlSelector == USB_AUDIO_AUTOMATIC_GAIN_CONTROL)
                   {
                       /*Handle Get request*/
                       USB_DEVICE_ControlSend(appData.usbDevHandle,(void *)&(appData.autoGain), 1 );
                   }
                }
                break;

            case USB_DEVICE_AUDIO_EVENT_CONTROL_SET_MIN:
            case USB_DEVICE_AUDIO_EVENT_CONTROL_GET_MIN:
                entityID = ((USB_AUDIO_CONTROL_INTERFACE_REQUEST*)pData)->entityID;
                if (entityID == APP_ID_FEATURE_UNIT_MIC)
                {
                   controlSelector = ((USB_AUDIO_FEATURE_UNIT_CONTROL_REQUEST*)pData)->controlSelector;
                   if (controlSelector == USB_AUDIO_MID_CONTROL)
                   {
                       /*Handle Get request*/
                       USB_DEVICE_ControlSend(appData.usbDevHandle, (void *)&(appData.midMin), 1 );
                   }
                }
                break;

            case USB_DEVICE_AUDIO_EVENT_CONTROL_SET_MAX:
            case USB_DEVICE_AUDIO_EVENT_CONTROL_GET_MAX:
                entityID = ((USB_AUDIO_CONTROL_INTERFACE_REQUEST*)pData)->entityID;
                if (entityID == APP_ID_FEATURE_UNIT_MIC)
                {
                   controlSelector = ((USB_AUDIO_FEATURE_UNIT_CONTROL_REQUEST*)pData)->controlSelector;
                   if (controlSelector == USB_AUDIO_MID_CONTROL)
                   {
                       /*Handle Get request*/
                       USB_DEVICE_ControlSend(appData.usbDevHandle, (void *)&(appData.midMax), 1 );
                   }
                }
                break;

            case USB_DEVICE_AUDIO_EVENT_CONTROL_SET_RES:
            case USB_DEVICE_AUDIO_EVENT_CONTROL_GET_RES:
                entityID = ((USB_AUDIO_CONTROL_INTERFACE_REQUEST*)pData)->entityID;
                if (entityID == APP_ID_FEATURE_UNIT_MIC)
                {
                   controlSelector = ((USB_AUDIO_FEATURE_UNIT_CONTROL_REQUEST*)pData)->controlSelector;
                   if (controlSelector == USB_AUDIO_MID_CONTROL)
                   {
                       /*Handle Get request*/
                       USB_DEVICE_ControlSend(appData.usbDevHandle, (void *)&(appData.midRes), 1 );
                   }
                }
                break;

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

} // APP_USBDeviceAudioEventHandler()


//=============================================================================
// APP_Initialize()
//
// APP Initialize. It is last item called from the MH 
// generated SYS_Initialize() function (called main() before the polling loop)
//=============================================================================
void APP_Initialize()
{
    #if defined( ENABLE_SYS_LOG )    
    SYS_LOG_Init();
    SYS_LOG("----------------------------------------");
    SYS_LOG("- Starting:");
    SYS_LOG("----------------------------------------");
    #endif

    //Codec Read Complete
    appData.isReadComplete1 = false;  //USB Data to Tx
    appData.isReadComplete2 = false;
    
    /* Write Transfer Handle */
    appData.isWriteComplete = false;

    appData.readBufHandle1 = DRV_CODEC_BUFFER_HANDLE_INVALID;
    appData.readBufHandle2 = DRV_CODEC_BUFFER_HANDLE_INVALID;

    /* Write transfer handle */
    //appData.writeTransferHandle = USB_DEVICE_AUDIO_TRANSFER_HANDLE_INVALID,
            
    //appData.activeInterfaceAlternateSettingMic = APP_USB_MIC_RECORD_NONE,
    
    //Stereo Codec Buffer
    appData.codecClient.txbufferObject1 = (uint8_t *) rxBuffer[0];
    appData.codecClient.txbufferObject2 = (uint8_t *) rxBuffer[1];
    appData.codecClient.bufferSize      = sizeof(rxBuffer[0]);
    appData.ping1Pong2 = true;  //codec read buffer 1

    //DEBUG
    #if defined(DEBUG_TONE_INJECT)

    //Tone Buffer for stereo
    //--Scaled Stereo and Mono
    int i;
    int16_t valueQ1d15;
    for (i=0; i<(TONE_SAMPLES_PER_CYCLE*TONE_NUMBER_OF_CYCLES); i++)
    {
         //Scaled stereo values
        valueQ1d15 = sinToneQ1d15[i].leftData;
        sinToneQ1d15[i].leftData  = (valueQ1d15 ); 
        sinToneQ1d15[i].rightData = (valueQ1d15 ); 
    }

    //Tone buffer for USB Tx
    for (i=0; i<TONE_SAMPLES_PER_CYCLE; i++)
    {
        //Scaled Mono values
         usbTxBuffer1[i] = sinToneQ1d15[i].rightData;
         usbTxBuffer2[i] = sinToneQ1d15[TONE_SAMPLES_PER_CYCLE+i].rightData;
    }

    #endif //DEBUG_TONE_INJECT

    appData.isReadBufHandleAvailable1 = false;
    appData.isReadBufHandleAvailable2 = false;

} //End APP_Initialize()


//=============================================================================
// APP_Tasks()
// 
// Application tasks routine.  Last item executed in MH generated SYS_Tasks() 
// in the main() polling loop.
//=============================================================================
void APP_Tasks()
{
    USB_DEVICE_AUDIO_RESULT audioErr;

    switch(appData.state)
    {

        //----------------------------------------------------------------------
        // Application's initial state. 
        //----------------------------------------------------------------------
        case APP_STATE_INIT:
        {
            /* Open the USB device layer  as R/W */
            appData.usbDevHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0,
                                                    DRV_IO_INTENT_READWRITE );

            if(appData.usbDevHandle != USB_DEVICE_HANDLE_INVALID)
            {
                /* Register a callback with device layer to get event 
                 * notification (for end point 0) */
                USB_DEVICE_EventHandlerSet(appData.usbDevHandle, 
                                           APP_USBDeviceEventHandler, 0);

                appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
                //GFX_MENU_DRAW();
            }
            else
            {
                // The Device Layer is not ready to be opened. We should try
                // again later.
            }
        } //End APP_STATE_INIT
            
        //----------------------------------------------------------------------
        // Wait for USB to be configured
        //----------------------------------------------------------------------
        case APP_STATE_WAIT_FOR_CONFIGURATION:
        {
            //Check if Host has configured the Device.
            if (appData.isConfigured == true)
            {
                appData.state = APP_STATE_CODEC_OPEN;
            }
        } //End APP_STATE_WAIT_FOR_CONFIGURATION
        break;

        //----------------------------------------------------------------------
        // Open CODEC for Mic Data Read
        //----------------------------------------------------------------------
        case APP_STATE_CODEC_OPEN:
        {
            //Open the codec client
            SYS_STATUS codecStatus;
            codecStatus = DRV_CODEC_Status(sysObjdrvCodec0);
            if (SYS_STATUS_READY == codecStatus)
            {
                #ifdef DEBUG_LOOPBACK
                //Read at the same time as write from the ping-pong buffers
                appData.codecClient.handle = 
                   DRV_CODEC_Open(DRV_CODEC_INDEX_0, 
                                  DRV_IO_INTENT_READWRITE | DRV_IO_INTENT_EXCLUSIVE);

                #else //NO DEBUG_LOOPBACK
                // This means the driver can now be be opened.
                /* A client opens the driver object to get an Handle */
                appData.codecClient.handle = 
                                    DRV_CODEC_Open(DRV_CODEC_INDEX_0, 
                                                   DRV_IO_INTENT_READ); 

                #endif //DEBUG_LOOPBACK

                //TODO:  Determine the current USB TX rate/mode (16Khz mono read),
                //       i.e. starting in record mode.  Switch to playback mode
                //       after recording and determine the playback rate for the 
                //       CODEC. 
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
        } //ENDcase APP_STATE_CODEC_OPEN:
        break;

        //----------------------------------------------------------------------
        // Set a handler for the audio buffer completion event 
        //----------------------------------------------------------------------
        case APP_STATE_CODEC_SET_BUFFER_HANDLER:
        {
            DRV_CODEC_BufferEventHandlerSet(appData.codecClient.handle,
                                            appData.codecClient.bufferHandler,
                                            appData.codecClient.context);
            appData.state = APP_IDLE;

            //Enable the mic input data I2S pin.
            PLIB_SPI_PinEnable(SPI_ID_1, SPI_PIN_DATA_IN);      

        } //END APP_STATE_CODEC_SET_BUFFER_HANDLER
        break;

        //----------------------------------------------------------------------
        //Initial Read from codec ADC (mic data) via I2S
        //-->Initiated from USB interface setting: 
        //          case APP_MUTE_AUDIO_PLAYBACK:
        //          case APP_MIC_USB_INTERFACE_ALTERNATE_SETTING_RCVD:
        //
        //--Initial Codec mic buffer reads 
        //----------------------------------------------------------------------
        case APP_SUBMIT_INITIAL_READ_REQUEST:
        {
            if (appData.activeInterfaceAlternateSettingMic == 
            APP_USB_MIC_RECORD_MONO_16KHZ)
            {

                #if defined(DEBUG_LOOPBACK) && defined(DEBUG_TONE_INJECT) 

                //Initiate the first Read Request to rxBuffer 0 
                //inject tone to CODEC output/No USB
                DRV_CODEC_MuteOff(appData.codecClient.handle);
                DRV_CODEC_BufferAddWriteRead(appData.codecClient.handle, 
                                            &appData.codecClient.readBufHandle1,
                                            usbTxBuffer1,
                                            appData.codecClient.txbufferObject1, //rcv
                                            //appData.codecClient.bufferSize);
                                            TONE_BUFFER_SIZE_BYTES);
                appData.isReadComplete1 = false;
                appData.isReadComplete2 = false;
                //appData.isReadBufHandleAvailable1 = true;
                //appData.isReadBufHandleAvailable2 = true;

                #elif defined(DEBUG_LOOPBACK) && !defined(DEBUG_TONE_INJECT) 
                //MIC Data Loopback/No USB
                DRV_CODEC_MuteOff(appData.codecClient.handle);
                DRV_CODEC_BufferAddWriteRead(appData.codecClient.handle, 
                                            &appData.codecClient.readBufHandle1,
                                            appData.codecClient.txbufferObject2, //tx 0's
                                            appData.codecClient.txbufferObject1, //rcv
                                            appData.codecClient.bufferSize);

                appData.isReadComplete1 = false;
                appData.isReadComplete2 = false;
                //appData.isReadBufHandleAvailable1 = true;
                //appData.isReadBufHandleAvailable2 = true;

                #else 
                //USB Mic Data Read/Possibly USB ignores this data(!DEBUG_LOOPBACK)

                //Mic Data
                //--Start by queueing the fill of both ping-pong buffers (rxBuffer[<0,1>])
                DRV_CODEC_BufferAddRead(appData.codecClient.handle, 
                                        &appData.codecClient.readBufHandle1,
                                        appData.codecClient.txbufferObject1, 
                                        appData.codecClient.bufferSize);

                DRV_CODEC_BufferAddRead(appData.codecClient.handle, 
                                        &appData.codecClient.readBufHandle2,
                                        appData.codecClient.txbufferObject2, 
                                        appData.codecClient.bufferSize);
                
                #endif //DEBUG_LOOPBACK

                appData.state = APP_PROCESS_DATA;

            }
            else
            {
               asm("nop");
            }

        } //END case APP_SUBMIT_INITIAL_READ_REQUEST:
        break;

        //----------------------------------------------------------------------
        //Process the data as the MIC rxBuffer fills to send to USB. 
        //
        //Initiated from states:
        //    APP_Tasks Initiale read State--
        //       case APP_SUBMIT_INITIAL_READ_REQUEST
        //
        //    APP_CODECBufferEventHandler Buffer Complete Event
        //       case DRV_CODEC_BUFFER_EVENT_COMPLETE
        //       --> Mic data to buffer complete 
        //           (isReadComplete<1,2>)
        //
        //    APP_USBDeviceAudioEventHandler Events--
        //       case USB_DEVICE_AUDIO_EVENT_WRITE_COMPLETE
        //       --> USB buffer read complete 
        //           (isReadBufHandleAvailable<1,2>)
        //
        //       case USB_DEVICE_AUDIO_EVENT_READ_COMPLETE: --Commented out--
        //
        //
        //--Codec or USB Read or Read/Write event has completed
        //----------------------------------------------------------------------
        case APP_PROCESS_DATA: 
        {
            //Wait for the the CODEC read (read/write) to complete
            
            audioErr = 0;
            if(appData.isReadComplete1 == true)
            {
                //Read(Mic) Buffer 1 Complete
                //Buffer 1 Codec read has completed
                appData.isReadComplete1 = false; 

                #if defined(DEBUG_TONE_INJECT) && !defined(DEBUG_LOOPBACK)
                //Send test tone audio to USB
                audioErr = USB_DEVICE_AUDIO_Write(USB_DEVICE_INDEX_0 , 
                                                  &appData.writeTransferHandle1, 
                                                  1 , usbTxBuffer1,  //16Khz 1000Hz Mono 
                                                  TONE_BUFFER_SIZE_BYTES);
                #else //MIC data

                #if defined(DEBUG_LOOPBACK) && !defined (DEBUG_TONE_INJECT)
                //Loopback Mic Data/No USB operation
                //USB not used (buffer always available to CODEC)
                //appData.isReadBufHandleAvailable1 = true;
                appData.isReadBufHandleAvailable2 = true; //for ping/pong operation

                #elif defined(DEBUG_LOOPBACK) && defined(DEBUG_TONE_INJECT)
                //Loopback Tone Data/No USB Operation
                //USB not used (buffer always available to CODEC)
                appData.isReadBufHandleAvailable2 = true; //for ping/pong operation
                #else //USB TX MIC DATA

                /* Write CODEC data to USB from rxBuffer[0]*/
                audioErr = USB_DEVICE_AUDIO_Write(USB_DEVICE_INDEX_0, 
                                                  &appData.writeTransferHandle1, 
                                                  1 , rxBuffer[0],  //16Khz Mono
                                                  APP_USB_FRAMESIZE_SAMPLES*4);
                if (audioErr != USB_DEVICE_AUDIO_RESULT_OK)
                {
                    usbWriteError++;
                }
                #endif //DEBUG_LOOPBACK

                #endif //DEBUG_TONE_INJECT

            }
            else if(appData.isReadComplete2 == true)
            {
                // Send CODEC data to USB from rxBuffer[1]

                //Buffer 2 Codec read has completed
                appData.isReadComplete2 = false; 

                #if !defined(DEBUG_LOOPBACK) && defined(DEBUG_TONE_INJECT) 
                //Send test tone audio to USB
                //--preset data
                audioErr = USB_DEVICE_AUDIO_Write(USB_DEVICE_INDEX_0, 
                                                  &appData.writeTransferHandle2, 
                                                  //1 , rxBuffer[1], //16Khz Mono
                                                  1 , usbTxBuffer2, 
                                                  APP_USB_FRAMESIZE_BYTES );
                #else //MIC data

                #if defined(DEBUG_LOOPBACK) && !defined (DEBUG_TONE_INJECT)
                //Loopback Mic Data/No USB operation
                //USB not used (buffer always available to CODEC)
                appData.isReadBufHandleAvailable1 = true;
                //appData.isReadBufHandleAvailable2 = true; //For ping/pong operation

                #elif defined(DEBUG_LOOPBACK) && defined(DEBUG_TONE_INJECT)
                //Loopback Tone Data/No USB operation
                //USB not used (buffer always available to CODEC)
                appData.isReadBufHandleAvailable1 = true; //For ping/pong operation
                //appData.isReadBufHandleAvailable2 = true;

                #else
                //USB Mic Record
                audioErr = USB_DEVICE_AUDIO_Write(USB_DEVICE_INDEX_0, 
                                                  &appData.writeTransferHandle2, 
                                                  1 , rxBuffer[1], 
                                                  APP_USB_FRAMESIZE_SAMPLES*4);


                #endif //DEBUG_LOOPBACK

                #endif //DEBUG_TONE_INJECT

                if (audioErr != USB_DEVICE_AUDIO_RESULT_OK)
                {
                    usbWriteError++;
                }


            }
            else
            {
               ;
            }

            //Check USB complete Tx buffer 1 and 
            //CODEC complete RX2/TX1
            if (appData.isReadBufHandleAvailable1) //USB tx buffer 1 complete
                   //&& appData.ping1Pong2)         //CODEC rx buffer 2 complete
            {

                #if defined(DEBUG_LOOPBACK) && defined(DEBUG_TONE_INJECT) 
                //Loopback Sin Tone
                DRV_CODEC_MuteOff(appData.codecClient.handle);
                DRV_CODEC_BufferAddWriteRead(appData.codecClient.handle, 
                                             &appData.codecClient.readBufHandle1,
                                             usbTxBuffer1, //sin out
                                             appData.codecClient.txbufferObject1, //Mic in
                                             TONE_BUFFER_SIZE_BYTES);
                appData.isReadBufHandleAvailable1 = false;
                appData.readBufHandle1 = DRV_CODEC_BUFFER_HANDLE_INVALID;
                #elif defined (DEBUG_LOOPBACK) && !defined(DEBUG_TONE_INJECT)
                //Loopback Mic Data
                //--Read rxBuffer[0]/Loopback rxBuffer[1]
                DRV_CODEC_MuteOff(appData.codecClient.handle);
                DRV_CODEC_BufferAddWriteRead(appData.codecClient.handle, 
                                             &appData.codecClient.readBufHandle1,
                                             appData.codecClient.txbufferObject2, //mic out
                                             appData.codecClient.txbufferObject1, //Mic in
                                             appData.codecClient.bufferSize);
                appData.isReadBufHandleAvailable1 = false;
                appData.readBufHandle1 = DRV_CODEC_BUFFER_HANDLE_INVALID;

                #else //USB MIC Data

                /* CODEC read or readWrite to available buffer*/
                //Buffer 1 USB Tx has completed
                appData.isReadBufHandleAvailable1 = false;
                appData.readBufHandle1 = DRV_CODEC_BUFFER_HANDLE_INVALID;

                /* CODEC read or readWrite to available buffer*/
                //Read MIC data to rxBuffer[0] (Buffer 1)
                DRV_CODEC_BufferAddRead(appData.codecClient.handle, 
                                        &appData.codecClient.readBufHandle1,
                                        appData.codecClient.txbufferObject1, 
                                        appData.codecClient.bufferSize);

                #endif //DEBUG_LOOPBACK

                //Next Codec Rx is to buffer 2
                //Codec Rx Buffer 2(Tx Buffer 1), while USB Tx Buffer 1
                appData.ping1Pong2 = false; 

            } //USB TX1 Complete/Ping1 Codec Read Complete

            // Check USB complete Tx buffer 2 and 
            // CODEC complete TX buffer 1
            if (appData.isReadBufHandleAvailable2)  //USB TX buffer 2 complete
                    //&& !appData.ping1Pong2)        //Codec RX buffer 1 complete
            {

                #if defined(DEBUG_LOOPBACK) && defined(DEBUG_TONE_INJECT) 
                //Loopback Sine Tone
                DRV_CODEC_MuteOff(appData.codecClient.handle);
                DRV_CODEC_BufferAddWriteRead(appData.codecClient.handle, 
                                             &appData.codecClient.readBufHandle2,
                                             usbTxBuffer2,
                                             appData.codecClient.txbufferObject2, //mic in 
                                             TONE_BUFFER_SIZE_BYTES);
                appData.isReadBufHandleAvailable2 = false;
                appData.readBufHandle2 = DRV_CODEC_BUFFER_HANDLE_INVALID;
                #elif defined(DEBUG_LOOPBACK) && !defined(DEBUG_TONE_INJECT) 
                //Loopback Mic Data
                //--Read Mic Data rxBuffer[1]/Loopback rxBuffer[0]
                DRV_CODEC_MuteOff(appData.codecClient.handle);
                DRV_CODEC_BufferAddWriteRead(appData.codecClient.handle, 
                                             &appData.codecClient.readBufHandle2,
                                             appData.codecClient.txbufferObject1, //mic out
                                             appData.codecClient.txbufferObject2, //mic in 
                                             appData.codecClient.bufferSize);
                appData.isReadBufHandleAvailable2 = false;
                appData.readBufHandle2 = DRV_CODEC_BUFFER_HANDLE_INVALID;

                #else //USB MIC DATA

                /* CODEC read or readWrite to available buffer*/
                //Buffer 2 USB Tx has completed
                appData.isReadBufHandleAvailable2 = false;
                appData.readBufHandle2 = DRV_CODEC_BUFFER_HANDLE_INVALID;

                //Read MIC data to rxBuffer[1] (Buffer 2)
                DRV_CODEC_BufferAddRead(appData.codecClient.handle, 
                                        &appData.codecClient.readBufHandle2,
                                        appData.codecClient.txbufferObject2, 
                                        appData.codecClient.bufferSize);

                #endif //DEBUG_LOOPBACK

                //Next Codec Rx is to buffer 1
                //Codec Rx Buffer 1(Tx Buffer 2), while USB Tx Buffer 2
                appData.ping1Pong2 = true; 

            } //USB TX2 Complete/Pong2 Codec Read Complete
            else
            {
                asm("nop");
            }

        } //case APP_PROCESS_DATA: 
        break;


        //----------------------------------------------------------------------
        // Mute the Audio Codec which USB interface changes.
        //
        // Initiated from :
        //   APP_USBDeviceAudioEventHandler())
        //   --Event: USB_DEVICE_AUDIO_EVENT_CONTROL_TRANSFER_DATA_RECEIVED:
        // 
        // Goes to:
        //    APP_SUBMIT_INITIAL_READ_REQUEST while changing the codec interface.
        //    APP_IDLE when complete
        //----------------------------------------------------------------------
        case APP_MUTE_AUDIO_PLAYBACK:
        {
            if (appData.activeInterfaceAlternateSetting == 0)
            {
                //Mute until USB interface set.
                DRV_CODEC_MuteOn(appData.codecClient.handle);
                appData.state = APP_IDLE;
            }
            else if (appData.activeInterfaceAlternateSetting == 1)
            {
                #ifdef DEBUG_LOOPBACK
                //Allow MIC Loopback to CODEC DAC
                DRV_CODEC_MuteOff(appData.codecClient.handle);
                #else
                DRV_CODEC_MuteOff(appData.codecClient.handle);
                #endif
                appData.state = APP_SUBMIT_INITIAL_READ_REQUEST;
            }
        } //End APP_MUTE_AUDIO_PLAYBACK
        break;

        //----------------------------------------------------------------------
        // Set the Mic interface Record configuraton APP_USB_RECORD_MONO_16KHZ
        // 
        //
        // Initiated by:
        //    APP_USBDeviceAudioEventHandler())
        //    --Event: USB_DEVICE_AUDIO_EVENT_INTERFACE_SETTING_CHANGED:
        //
        // Goes to:
        //    APP_SUBMIT_INITIAL_READ_REQUEST - start mic recording
        //    APP_IDLE when complete
        //----------------------------------------------------------------------
        case APP_MIC_USB_INTERFACE_ALTERNATE_SETTING_RCVD:
        {
           if (appData.activeInterfaceAlternateSettingMic == APP_USB_MIC_RECORD_NONE)
            {
            //Initialize and idle
                DRV_CODEC_MuteOn(appData.codecClient.handle);
                
                appData.isReadComplete1 = false;
                appData.isReadComplete2 = false;

                /* Write Transfer Handle */
                appData.isWriteComplete = false,

                appData.readBufHandle1 = DRV_CODEC_BUFFER_HANDLE_INVALID;
                appData.readBufHandle2 = DRV_CODEC_BUFFER_HANDLE_INVALID;
                
                appData.isReadBufHandleAvailable1 = false;
                appData.isReadBufHandleAvailable2 = false;
                
                appData.state = APP_IDLE;
            }
            else if(appData.activeInterfaceAlternateSettingMic == 
                    APP_USB_MIC_RECORD_MONO_16KHZ)
            {
                #ifdef DEBUG_LOOPBACK
                //Allow MIC Loopback to CODEC DAC
                DRV_CODEC_MuteOff(appData.codecClient.handle);
                #else
                DRV_CODEC_MuteOff(appData.codecClient.handle);
                #endif
                //DRV_CODEC_MicrophoneTypeSet (appData.codecClient.handle, DRV_CODEC_MICROPHONE_TYPE_EXTERNAL);
                // check the schematics to see which MIC input channel is available
                DRV_CODEC_MicrophoneSoundSet(appData.codecClient.handle, MONO_RIGHT_CHANNEL);
                appData.state =  APP_SUBMIT_INITIAL_READ_REQUEST;
            }
        } //END APP_MIC_USB_INTERFACE_ALTERNATE_SETTING_RCVD
        break;

        //----------------------------------------------------------------------
        //  Do Nothing.
        //----------------------------------------------------------------------
        case APP_IDLE:
        {
            if (appData.activeInterfaceAlternateSetting == APP_USB_SPEAKER_PLAYBACK_NONE)
            {
                if(muteonflag==0)
                {
                    DRV_CODEC_MuteOn(appData.codecClient.handle);
                    muteonflag = 1;
                }
            }
        } //END APP_IDLE
        break;

        //----------------------------------------------------------------------
        //  Error/Fault/Default
        //----------------------------------------------------------------------
        case APP_STATE_ERROR:
        /* The default state should never be executed. */

        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }

    } //End switch(appData.state)

} //End APP_Tasks()


//=============================================================================
// APP_CODECBufferEventHandler()
//
// Application CODEC buffer Event handler.  This function is called back by 
// the CODEC driver when a CODEC mic data buffer is received.
//
//=============================================================================
void APP_CODECBufferEventHandler(DRV_CODEC_BUFFER_EVENT event,
        DRV_CODEC_BUFFER_HANDLE handle, uintptr_t context )
{
    switch(event)
    {
        case DRV_CODEC_BUFFER_EVENT_COMPLETE:
        {
            //uint8_t index;

            if(appData.codecClient.readBufHandle1 == handle)
            {
                //Ready to TX USB buffer 1
        //--buffer 1 not available until USB TX completes
        //  (appData.isReadBufHandleAvailable1)
                appData.isReadComplete1 = true;
            }
            else if(appData.codecClient.readBufHandle2 == handle)
            {
                //Ready to TX USB buffer 2
        //--buffer 2 not available until USB TX completes
        //  (appData.isReadBufHandleAvailable2)
                appData.isReadComplete2 = true;
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
} //End APP_CODECBufferEventHandler()

/*******************************************************************************
 End of File
 */

