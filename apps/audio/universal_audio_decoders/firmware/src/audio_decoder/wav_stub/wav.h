/*******************************************************************************
  Universal Audio Decoders Demo

  Company:
    Microchip Technology Inc.

  File Name:
    wav.h

  Summary:
    Contains the wav decoder specific defintions and function prototypes.

  Description:
    This file contains the wav decoder specific defintions and function
    prototypes.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2012 released Microchip Technology Inc.  All rights reserved.

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

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef WAV_H

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
//DOM-IGNORE-END


#define	WAV_H
#define WAVE_FORMAT_PCM    0x0001
#define WAVE_FORMAT_ALAW   0x0006
#define WAVE_FORMAT_MULAW  0x0007
#define WAV_HEADER_SIZE 44
//#define WAV_HEAP_SIZE  1024
//#define WAV_INPUT_BUFFER_SIZE        ((2544*4)) //working perfectly
#define WAV_INPUT_BUFFER_SIZE        ((1152*6))
#define WAV_OUTPUT_BUFFER_SIZE       WAV_INPUT_BUFFER_SIZE



//typedef struct {
//    int format;
//    int filesize;
//    int filetype;
//    int frmtchunk_marker;
//    int dataLen;
//    short type_frmt;
//    short numOfChan;
//    int samplesPerSec;
//    int bytesPerSec;
//    short blockAlign;
//    short bitsPerSample;
//    unsigned char *extra;
//    unsigned int extralen;        
//} WAVEHEADER;

typedef struct {
    int format;
    int filesize;
    int filetype;
    int frmtchunk_marker;
    int dataLen;
    short type_frmt;
    short numOfChan;
    int samplesPerSec;
    int bytesPerSec;
    short blockAlign;
    short bitsPerSample;
    int *extra;
    unsigned int extralen;        
} WAVHEADER;

//typedef struct {
//
//    uint8_t *WAVHeaderBuf;
//    uint8_t *WAVDataBuf;
//
//}WAV_DECODER_HEAP;
void WAV_Initialize(uint8_t *input);

bool WAV_Decoder(uint8_t *input, uint16_t inSize, uint16_t *read, int16_t *output, uint16_t *written);
int WAV_HdrGetSamplesPerSec(void);
int WAV_HdrGetBytesPerSec(void);
int WAV_HdrGetDataLen(void);
unsigned int WAV_HdrGetFileSize(void);
bool isWAVdecoder_enabled();

#ifdef __cplusplus
}
#endif

#endif	/* WAV_H */

