/*******************************************************************************
  Universal Audio Decoders Demo

  Company:
    Microchip Technology Inc.

  File Name:
    decoder.c

  Summary:
   Contains the functional implementation of decoder functions.

  Description:
   This file contains the functional implementation of decoder functions.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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
OTHER LEGAL EQUITABLE THEORY ANY DIR-*9ECT OR INDIRECT DAMAGES OR EXPENSES
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

#define DECODER_C
#include "decoder.h"
#include "app.h"

////////////////////////////////////////////////////////////////////////////////
//APP_AUDIOPLAYER appData ;
static DECODER_TYPE decoderType;
uint8_t frameHeader[WAV_HEADER_SIZE]; // 44 bytes
uint8_t decoderHeap[AACDECODER_STATE_SIZE]; 
uint32_t decoderBitrate;
uint32_t decoderSamplerate;
int sampling_frequency;
const static char __attribute__((unused)) *unknown = "UNKNOWN";

/*********************STATIC FUNCTIONS DECLARATION*****************************/
static void DECODE_ConfigureAudioTransmitMode(bool stereo);


////////////////////////////////////////////////////////////////////////////////
void DECODER_Initialize ( uint8_t type )
{
    
   
    decoderType = DECODER_TYPE_UNKNOWN;
    APP_AUDIOPLAYER __attribute__((unused)) *appDataPtr = APP_GetAppDataInstance();
    switch ( type )
    {
#ifdef MP3_DECODER_ENABLED
        case APP_DECODER_MP3:
            appDataPtr->currentStreamType = APP_STREAM_MP3;
            decoderType = DECODER_TYPE_MP3;
            APP_BSP_LEDOff(APP_USB_LED_1);
            APP_BSP_LEDOff(APP_USB_LED_2);
            APP_BSP_LEDOn(APP_USB_LED_3);
            appDataPtr->updatePlaytimeFunc = MP3_UpdatePlaytime;
            if ( MP3_Initialize ( decoderHeap, MP3_DECODER_HEAP_SIZE, appDataPtr->fileHandle) != true )
            {
               DECODER_EventHandler ( DECODER_INITIALIZATION_ERROR, 0 );
            }
            DECODE_ConfigureAudioTransmitMode((MP3_GetChannels()==2));
            break;
#endif
            
#ifdef AAC_DECODER_ENABLED
        case APP_DECODER_AAC:
            appDataPtr->currentStreamType = APP_STREAM_AAC;
            decoderType = DECODER_TYPE_AAC;
            APP_BSP_LEDOff(APP_USB_LED_1);
            APP_BSP_LEDOn(APP_USB_LED_2);
            APP_BSP_LEDOff(APP_USB_LED_3);

            appDataPtr->readBytes = AAC_FRAME_HEADER_SIZE;
            appDataPtr->readbyte_flag = true;
            AAC_Initialize ( decoderHeap, AACDECODER_STATE_SIZE,frameHeader, appDataPtr->fileHandle);
            sampling_frequency = AAC_GetSamplingFrequency(frameHeader);
            DECODER_EventHandler ( DECODER_EVENT_SAMPLERATE, sampling_frequency );
            DECODER_EventHandler ( DECODER_EVENT_TAG_TITLE, (uint32_t)appDataPtr->fileStatus.lfname );
            if(SYS_FS_FileSeek( appDataPtr->fileHandle, 0, SYS_FS_SEEK_SET ) == -1)
            {
                Nop();
            }
            else
            {
                /* Check for End of file */
                 Nop();
            }
            DECODE_ConfigureAudioTransmitMode((AAC_GetChannels()==2));
            break;
#endif
            

#ifdef WMA_DECODER_ENABLED
        case APP_DECODER_WMA:
            appDataPtr->currentStreamType = APP_STREAM_WMA;
            decoderType = DECODER_TYPE_WMA;
            APP_BSP_LEDOff(APP_USB_LED_1);
            APP_BSP_LEDOn(APP_USB_LED_2);
            APP_BSP_LEDOn(APP_USB_LED_3);

            WMA_Initialize (appDataPtr->fileHandle, DECODER_MAX_INPUT_BUFFER_SIZE);

            DECODE_ConfigureAudioTransmitMode((WMA_GetChannels()==2));
            sampling_frequency = WMA_SamplingFrequency_Get();
            decoderBitrate = WMA_BitRate_Get()/1000;
            DECODER_EventHandler ( DECODER_EVENT_SAMPLERATE, sampling_frequency );
            DECODER_EventHandler ( DECODER_EVENT_BITRATE, decoderBitrate );
            DECODER_EventHandler ( DECODER_EVENT_TAG_TITLE, (uint32_t)appDataPtr->fileStatus.lfname );
            if(SYS_FS_FileSeek( appDataPtr->fileHandle, WMA_GetHeaderPacketOffset(), SYS_FS_SEEK_SET ) == -1)
            {
                Nop();
            }
            else
            {
               /* Check for End of file */
                Nop();
            }
            break;
#endif
            
            
#ifdef WAV_STREAMING_ENABLED
        case APP_DECODER_WAV:
            appDataPtr->currentStreamType = APP_STREAM_WAV;
            appDataPtr->updatePlaytimeFunc = WAV_UpdatePlaytime;
            decoderType = DECODER_TYPE_WAV;
            APP_BSP_LEDOn(APP_USB_LED_1);
            APP_BSP_LEDOff(APP_USB_LED_2);
            APP_BSP_LEDOff(APP_USB_LED_3);
            DISK_ReadCurrentFile(frameHeader, WAV_HEADER_SIZE);
            
            appDataPtr->readBytes = WAV_INPUT_BUFFER_SIZE;
            appDataPtr->readbyte_flag = true;
            WAV_Initialize_N (frameHeader, appDataPtr->fileHandle);
//            sampling_frequency = 
            DECODER_EventHandler ( DECODER_EVENT_SAMPLERATE, WAV_GetSampleRate());
            DECODER_EventHandler ( DECODER_EVENT_BITRATE, WAV_GetBitRate());
            DECODER_EventHandler ( DECODER_EVENT_TRACK_TIME, WAV_GetDuration());

            DECODE_ConfigureAudioTransmitMode((WAV_GetChannels()==2));
            DECODER_EventHandler ( DECODER_EVENT_TAG_TITLE, (uint32_t)appDataPtr->fileStatus.lfname );
            DECODER_EventHandler ( DECODER_EVENT_TAG_ARTIST, (uint32_t)unknown );
            DECODER_EventHandler ( DECODER_EVENT_TAG_ALBUM, (uint32_t)unknown );
            // for RW function, move to end of previous song
            DECODER_EventHandler ( DECODER_EVENT_STREAM_START, 0 );
            
            break;
#endif
            
#ifdef OGG_SPEEX_DECODER_ENABLED
        case APP_DECODER_SPEEX:
            appDataPtr->currentStreamType = APP_STREAM_SPEEX;
            APP_ERROR_MSG res = SPEEX_Initialize(appDataPtr->fileHandle);
            if(res == APP_SUCCESS)
            {
                DECODE_ConfigureAudioTransmitMode((SPEEX_GetChannels()==2));
                sampling_frequency = SPEEX_GetSamplingRate();
                DECODER_EventHandler ( DECODER_EVENT_SAMPLERATE, sampling_frequency );
                decoderBitrate = SPEEX_GetBitrate()/1000;
                DECODER_EventHandler ( DECODER_EVENT_BITRATE, decoderBitrate );
                
                DECODER_EventHandler ( DECODER_EVENT_TAG_TITLE, (uint32_t)appDataPtr->fileStatus.lfname);
                
            }
            decoderType = DECODER_TYPE_SPEEX;
            break;
#endif
            
#ifdef ADPCM_STREAMING_ENABLED
        case APP_DECODER_ADPCM:
            appDataPtr->currentStreamType = APP_STREAM_ADPCM;
            DISK_ReadCurrentFile(frameHeader, ADPCM_HEADER_SIZE);
            
            appDataPtr->readbyte_flag = true;
            appDataPtr->readBytes = ADPCM_INPUT_BUFFER_SIZE;
            ADPCM_Initialize(frameHeader);
            
            sampling_frequency = ADPCM_HdrGetSamplesPerSec();
            
            DECODER_EventHandler ( DECODER_EVENT_SAMPLERATE, sampling_frequency );
            DECODER_EventHandler ( DECODER_EVENT_TAG_TITLE, (uint32_t)appDataPtr->fileStatus.lfname );
            
            DECODE_ConfigureAudioTransmitMode((ADPCM_GetChannels()==2));
            decoderType = DECODER_TYPE_ADPCM;
            break;
#endif
            
#ifdef OGG_OPUS_DECODER_ENABLED
        case APP_DECODER_OPUS:
            appDataPtr->currentStreamType = APP_STREAM_OPUS;
            APP_ERROR_MSG ret = OPUS_Initialize(appDataPtr->fileHandle);
            if(ret == APP_SUCCESS)
            {
                sampling_frequency = OPUS_GetSamplingRate();
                DECODER_EventHandler ( DECODER_EVENT_SAMPLERATE, sampling_frequency );
                DECODER_EventHandler ( DECODER_EVENT_TAG_TITLE, (uint32_t)appDataPtr->fileStatus.lfname );
            }
            DECODE_ConfigureAudioTransmitMode((OPUS_GetChannels()==2));
            decoderType = DECODER_TYPE_OPUS;
            break;
#endif
            
        case APP_DECODER_UNKNOWN:
            break;
        default:
            break;
       
    }
}

bool DECODER_Decode ( uint8_t *input, uint16_t inSize, uint16_t *read, int16_t *output, uint16_t *written )
{
    *read = 0;
    *written = 0;
    APP_ERROR_MSG res;
    switch ( decoderType )
    {
        case DECODER_TYPE_MP3:
           if(MP3_Decode ( input, inSize, read, (uint8_t *)output, written )) //(uint8_t *)appData.audioOutputptr
           {
               return true;
           }
           else
           {
                APP_BSP_LEDOn(APP_USB_LED_1);
                APP_BSP_LEDOn(APP_USB_LED_2);
                APP_BSP_LEDOn(APP_USB_LED_3);
               return false;
           }

           break;

        case DECODER_TYPE_AAC:
            if (AAC_Decoder(input, inSize,read,output,written)==true)
            {
               return true;
            }
            else
            {
                APP_BSP_LEDOn(APP_USB_LED_1);
                APP_BSP_LEDOn(APP_USB_LED_2);
                APP_BSP_LEDOn(APP_USB_LED_3);
                return false;
            }
            break;

        case DECODER_TYPE_WMA:
            if (WMA_Decoder(input, inSize,read,output,written)==true)
            {
               return true;
            }
            else
            {
                APP_BSP_LEDOn(APP_USB_LED_1);
                APP_BSP_LEDOn(APP_USB_LED_2);
                APP_BSP_LEDOn(APP_USB_LED_3);
                 return false;
            }
            break;

        case DECODER_TYPE_WAV:
            if( WAV_Decoder (input,inSize,read,output,written)==true)
            {
                return true;
            }
            else
                return false;
            break;
            
        case DECODER_TYPE_SPEEX: // ogg-speex
            res = SPEEX_Decoder (input,inSize,read,output,written);
            if(res == APP_SUCCESS){
                return true;
            }else if(res == APP_STREAM_END){
                return true;
            }
            else{
                return false;
            }
            break;

        case DECODER_TYPE_ADPCM:
            if(ADPCM_Decoder(input,inSize,read,output,written)){
                return true;
            }else{
                return false;
            }
            break;
            
        case DECODER_TYPE_OPUS:
            if(OPUS_Decoder(input, inSize, read, output, written, DECODER_MAX_OUTPUT_BUFFER_SIZE)==1){
                return true;
            }else{
                return false;
            }
            break;
        // Tobe added	
        /*
        case DECODER_TYPE_FLAC:            
            return FLAC_Decoder(input, inSize, read, (uint8_t *)output, written);
        */          
        case DECODER_TYPE_UNKNOWN:
            break;
    }

    return ( true );
}

// This is the function returns the audio size in file, 
// which means it doesn't contain the header size or meta data.
uint32_t DECODER_GetCurrentValidAudioSize(){
    // add other decoder cases later

    uint32_t ret = 0;
    switch(decoderType){
        case DECODER_TYPE_WAV:
            ret = WAV_GetAudioSize();
            break;
        case DECODER_TYPE_MP3:
            ret = MP3_GetAudioSize();
            break;
        case DECODER_TYPE_AAC:
            break;
        case DECODER_TYPE_WMA:
            break;
        /* Tobe added
        case DECODER_TYPE_FLAC:
            break;
        */
         default:
            ret = 0;
            break;
    }
    return ret;
}

void DECODER_Cleanup()
{
    switch ( decoderType )
    {
        case DECODER_TYPE_WMA:
            WMA_FreeMemory();
            break;
        case DECODER_TYPE_SPEEX:
            SPEEX_Cleanup();
            break;
        case DECODER_TYPE_OPUS:
            OPUS_Cleanup();
            break;
// Tobe added
/*
        case DECODER_TYPE_FLAC:
            FLAC_Cleanup();
            break;
*/ 
       default:
            break;
    }
}

/////////////////////////////////////////////////////////////
uint32_t GetDecodeBitRate(void)
{
    return ( (uint32_t) decoderBitrate );
}

/////////////////////////////////////////////////////////////
uint32_t GetDecodeSamplingRate ( void )
{
    return ( (uint32_t) decoderSamplerate );
}


static void __attribute__((unused)) DECODE_ConfigureAudioTransmitMode(bool stereo)
{
    if(stereo){
        if(!APP_GetSpiAudioMode()){
            PLIB_SPI_AudioTransmitModeSelect(DRV_I2S_PERIPHERAL_ID_IDX0, 
                                                SPI_AUDIO_TRANSMIT_STEREO);
            APP_SetSpiAudioMode(stereo);
        }// if current SPI audio mode is mono, reconfigure SPI
    }else{
        if(APP_GetSpiAudioMode()){
            PLIB_SPI_AudioTransmitModeSelect(DRV_I2S_PERIPHERAL_ID_IDX0, 
                                                SPI_AUDIO_TRANSMIT_MONO);
            APP_SetSpiAudioMode(stereo);
        }// if current SPI audio is stereo
    }
    
}
