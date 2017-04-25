/*******************************************************************************
 MC Debug File

  File Name:
    mc_debug.c

  Summary:
    Contains all the RTDM debug related functions 

  Description:
    This file contains the source code for all the RTDM debug functions used by 
    the mc_app
    

  
  Remarks:
    None.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

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


    DMCIFLAGS DMCIFlags;
	// Buffer to store the data samples for the DMCI data viewer 
	// Graph1, Graph2, Graph3 and Graph4
    int RecorderBuffer1[DATA_BUFFER_SIZE] __attribute__ ((aligned));
    int RecorderBuffer2[DATA_BUFFER_SIZE] __attribute__ ((aligned));
    int RecorderBuffer3[DATA_BUFFER_SIZE] __attribute__ ((aligned));
    int RecorderBuffer4[DATA_BUFFER_SIZE] __attribute__ ((aligned));
    
    int * PtrRecBuffer1 = &RecorderBuffer1[0];	//Tail pointer for the DMCI Graph1
    int * PtrRecBuffer2 = &RecorderBuffer2[0];	//Tail pointer for the DMCI Graph2
    int * PtrRecBuffer3 = &RecorderBuffer3[0];	//Tail pointer for the DMCI Graph3
    int * PtrRecBuffer4 = &RecorderBuffer4[0];	//Tail pointer for the DMCI Graph4
    int * RecBuffUpperLimit = RecorderBuffer4 + DATA_BUFFER_SIZE -1;	//Buffer Recorder Upper Limit
    int	SnapCount = 0;
    int SnapShotDelayCnt = 0;
    signed short int SnapShotDelay = SNAPDELAY;
	int SpeedReference = 32767;




// *****************************************************************************
// *****************************************************************************
// Section: RTDM Debug Functions
// *****************************************************************************
// *****************************************************************************
    
/******************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/******************************************************************************/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/******************************************************************************/
/* Function name: DBG_Init                                                    */
/* Function parameters: None                                                  */
/* Function return: None                                                      */
/* Description: Initialize the Debugger functionality                         */
/******************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void APP_MC_DBG_Init(void)
{
    /* call RTDM specific if defined */
    

	RTDM_Start();	//RTDM start function
					// Overview: 
					// Here is where the RTDM code initilizes the UART to be used to
					// exchange data wiht the host PC
					// Note:	
					// Some processors may have 2 UART modules, that is why it is required to
					// specify wich UART module is going to be used by RTDM	
					
    DMCIFlags.Recorder =1;



}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/******************************************************************************/
/* Function name: DBG_SyncComm                                                */
/* Function parameters: None                                                  */
/* Function return: None                                                      */
/* Description: Sychronize the communication between the debugger funct       */
/* running on the embedded to the host                                        */
/******************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void APP_MC_DBG_SyncComm(void)
{


	RTDM_ProcessMsgs();	//RTDM start function


}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/******************************************************************************/
/* Function name: DBG_SnapUpdate                                              */
/* Function parameters: None                                                  */
/* Function return: None                                                      */
/* Description: Snap the values sent to host for debug purposes               */
/* update the internal debbuger variables (snap buffers) at certain timing    */
/******************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void APP_MC_DBG_SnapUpdate(void)
{
  
               


    	if(DMCIFlags.Recorder)
    	{
    		if(SnapShotDelayCnt++ >= SnapShotDelay)
    		{
    			SnapShotDelayCnt = 0;

                *PtrRecBuffer1++ 	= SNAP1;
        		*PtrRecBuffer2++	= SNAP2;
    			*PtrRecBuffer3++	= SNAP3;
    			*PtrRecBuffer4++	= SNAP4;
    			
    			if(PtrRecBuffer4 > RecBuffUpperLimit)
    			{
    				
                    PtrRecBuffer1 = RecorderBuffer1;
    				PtrRecBuffer2 = RecorderBuffer2;
    		        PtrRecBuffer3 = RecorderBuffer3;
    		        PtrRecBuffer4 = RecorderBuffer4;
    		        DMCIFlags.Recorder = 0;
    		    }   
    		}
    	}


}
/* *****************************************************************************
 End of File
 */
