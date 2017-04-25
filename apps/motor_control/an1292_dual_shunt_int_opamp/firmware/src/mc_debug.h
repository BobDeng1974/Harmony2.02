/*******************************************************************************
  MC Debug Header File

  Company:
    Microchip Technology Inc.

  File Name:
   mc_debug.h

  Summary:
    This header file provides prototypes and definitions for the MC debug functions.

  Description:
  This header file provides function prototypes and data type definitions for
  the MC Debug functions which use RTDM protocol to communicate with DMCI plugin.
*******************************************************************************/

//DOM-IGNORE-BEGIN
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
#include "system_config.h"
#include "system_definitions.h"
#include "RTDM.h"

#ifndef _MC_Debug_H    /* Guard against multiple inclusion */
#define _MC_Debug_H


    typedef struct DMCIFlags{
    		    unsigned Recorder : 1;	// Flag needs to be set to start buffering data
				unsigned StartStop : 1;
    			unsigned unused : 14;  
    } DMCIFLAGS;
extern    DMCIFLAGS DMCIFlags;
extern int SpeedReference;
extern signed short int SnapShotDelay;
extern    int RecorderBuffer1[DATA_BUFFER_SIZE] __attribute__ ((aligned));
extern    int RecorderBuffer2[DATA_BUFFER_SIZE] __attribute__ ((aligned));
extern    int RecorderBuffer3[DATA_BUFFER_SIZE] __attribute__ ((aligned));
extern    int RecorderBuffer4[DATA_BUFFER_SIZE] __attribute__ ((aligned));






void APP_MC_DBG_Init(void);
void APP_MC_DBG_SyncComm(void);
void APP_MC_DBG_SnapStart(void);
void APP_MC_DBG_SnapUpdate(void);
void APP_MC_DBG_IDLECounter(void);

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
