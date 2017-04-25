/*******************************************************************************
FLAC Decoder Library Interface File

  Company:
    Microchip Technology Inc.

  File Name:
    flac.h

  Summary:
    FLAC Decoder support API.

  Description:
    This header file consists of support function declarations.

*******************************************************************************/
// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2014 released Microchip Technology Inc.  All rights reserved.
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
//DOM-IGNORE-BEGIN
#ifdef __cplusplus
extern "C" {
#endif
//DOM-IGNORE-END
#include "system/fs/sys_fs.h"
    
typedef bool (*DecoderEventHandlerCB)(uint32_t event, uint32_t data);

// *****************************************************************************
/* Function isFLACdecoder_enabled:

        bool isFLACdecoder_enabled();

  Summary:
    Return a boolean if the FLAC decoder is included or not.

  Description:
    Return a boolean if the FLAC decoder is included or not.
            

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    This function returns a boolean value.
	- 0 - FLAC decoder is not enabled.
    - 1 - FLAC decoder is enabled.

  Example:
    <code>
	bool flac_enabled = isFLACdecoder_enabled();
    </code>

  Remarks:
    None.
*/

bool isFLACdecoder_enabled();

// *****************************************************************************
/* Function FLAC_Initialize:

        bool FLAC_Initialize (SYS_FS_HANDLE fhandle, char *file);

  Summary:
    An abstraction function on FLAC decoder library, initialize necessary FLAC decoder state variables.

  Description:
    This function provides decoder initialize function to audio applications.
	
  Precondition:
    A FLAC audio file.

  Parameters:
    fhandle	- file handle to a FLAC audio file
    file	- file name of the FLAC audio file (not required)(deprecated)

  Returns:
    This function returns a boolean value.
	- 0 - FLAC decoder initialization failed.
    - 1 - FLAC decoder initialization succeed.

  Example:
    <code>
	bool flac_init_ret = bool FLAC_Initialize (flacHandle, filename);
    </code>

  Remarks:
    None.
*/
bool FLAC_Initialize (SYS_FS_HANDLE fhandle, char *file);

// *****************************************************************************
/* Function FLAC_RegisterDecoderEventHandlerCallback:

       void FLAC_RegisterDecoderEventHandlerCallback(DecoderEventHandlerCB fptr);

  Summary:
    Register a decoder event handler function to FLAC decoder.

  Description:
    This function registers a event handler function for propagating FLAC decoding information 
	to a upper level.
	
  Precondition:
    None.

  Parameters:
    fptr	- event handler function pointer.

  Returns:
    None.

  Example:
    <code>
		FLAC_RegisterDecoderEventHandlerCallback(fptr);
    </code>

  Remarks:
    None.
*/
void FLAC_RegisterDecoderEventHandlerCallback(DecoderEventHandlerCB fptr);

// *****************************************************************************
/* Function FLAC_Decoder:

       bool FLAC_Decoder(uint8_t *input, uint16_t inSize, uint16_t *read, uint8_t *output, uint16_t *written);

  Summary:
    An abstraction function on FLAC decoder library, 
	this function decodes a chuck of input data and returns the decoded data.

  Description:
    This function decodes input buffer then returns decoded data, 
	it provides a abstraction interface to use FLAC decode functions from library.
	
  Precondition:
	FLAC_Initialize function must be called before this function.

  Parameters:
    input	- input buffer pointer which holds FLAC data
	inSize  - input buffer size
	read    - size of input buffer that is read by this function.
	output  - output buffer pointer which holds decoded data.
	written - size of decoded data.

  Returns:
	This function returns a boolean value.
	- 0 - FLAC decoder decodes failed.
    - 1 - FLAC decoder decodes succeed.

  Example:
    <code>
		SYS_FS_FileRead(fptr, input, inSize);
		FLAC_Decoder(input, inSize, read, output, written);
    </code>

  Remarks:
    None.
*/
bool FLAC_Decoder( uint8_t *input, uint16_t inSize, uint16_t *read, uint8_t *output, uint16_t *written );

// *****************************************************************************
/* Function FLAC_GetChannels:

       uint8_t FLAC_GetChannels();

  Summary:
    Returns number of channel of the FLAC file.

  Description:
    This function returns audio channel number of the FLAC file.
	
  Precondition:
	FLAC_Initialize function must be called before this function.

  Parameters:
    None.

  Returns:
	Number of audio channels

  Example:
    <code>
		num_channel = FLAC_GetChannels();
    </code>

  Remarks:
    None.
*/
uint8_t FLAC_GetChannels();

// *****************************************************************************
/* Function FLAC_GetBitRate:

       int32_t FLAC_GetBitRate();

  Summary:
    Returns bit rate of the FLAC audio file.

  Description:
    This function returns bit rate of the FLAC audio file.
	
  Precondition:
	FLAC_Initialize function must be called before this function.

  Parameters:
    None.

  Returns:
	Bit rate of the FLAC audio file.

  Example:
    <code>
		bitrate = FLAC_GetBitRate();
    </code>

  Remarks:
    None.
*/
int32_t FLAC_GetBitRate();

// *****************************************************************************
/* Function FLAC_GetSamplingRate:

       int32_t FLAC_GetSamplingRate();

  Summary:
    Returns sample rate of the FLAC audio file.

  Description:
    This function returns sample rate of the FLAC audio file.
	
  Precondition:
	FLAC_Initialize function must be called before this function.

  Parameters:
    None.

  Returns:
	Sample rate of the FLAC audio file.

  Example:
    <code>
		samplerate = FLAC_GetSamplingRate();
    </code>

  Remarks:
    None.
*/
int32_t FLAC_GetSamplingRate();

// *****************************************************************************
/* Function FLAC_GetBlockSize:

       int32_t FLAC_GetBlockSize();

  Summary:
    Returns size of next packet to be decoded.

  Description:
    This function returns size of next packet to be decoded.
	
  Precondition:
	FLAC_Initialize function must be called before this function.

  Parameters:
    None.

  Returns:
	Size of next packet to be decoded.

  Example:
    <code>
		blocksize = FLAC_GetBlockSize();
		SYS_FS_FileRead(fptr, input, blocksize);
    </code>

  Remarks:
    None.
*/
int32_t FLAC_GetBlockSize();

// *****************************************************************************
/* Function FLAC_Cleanup:

       void FLAC_Cleanup();

  Summary:
    A clean up function for deallocating memory resources of a FLAC decoder.

  Description:
    This function must be called after a FLAC audio file is decoded to free the memory resources.
	
  Precondition:
	FLAC_Initialize function must be called before this function.

  Parameters:
    None.

  Returns:
	Size of next packet to be decoded.

  Example:
    <code>
		blocksize = FLAC_GetBlockSize();
		SYS_FS_FileRead(fptr, input, blocksize);
    </code>

  Remarks:
    None.
*/
void FLAC_Cleanup();
#ifdef __cplusplus
}
#endif
