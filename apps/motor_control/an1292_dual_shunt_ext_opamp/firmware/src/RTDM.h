/*******************************************************************************
  RTDM Header File

  Company:
    Microchip Technology Inc.

  File Name:
    RTDM.h

  Summary:
    This header file provides prototypes and definitions for the RTDM application.

  Description:
    This header file provides function prototypes and data type definitions for
    the RTDM protocol which communicates with the DMCI plug-in.
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


#ifndef _RTDM_Functions_H    /* Guard against multiple inclusion */
#define _RTDM_Functions_H

#define RTDM_UART_V2
/************************************** RTDM DEFINITIONS  ***************************************/
#define RTDM_FCY	 	60000000	//This define has to be the system operating freq, this 
									//value is used to calculate the value of the BRG register
#define RTDM_BAUDRATE	57600		//This is the desired baudrate for the UART module to be 
									//used by RTDM
#define RTDM_UART			2		// This is the UART module to be used by RTDM. It has only
									// two possible values: 1 or 2
									// For dsPIC33E and PIC24E, values 3 and 4 are also supported
#define RTDM_UART_PRIORITY	4		//This the UART RX interrupt priority assigned to receive
									// the RTDM messages
#define RTDM_RXBUFFERSIZE	32		// This is the buffer size used by RTDM to handle messaages 
#define RTDM_MAX_XMIT_LEN   0x1000	//This the size in bytes of the max num of bytes allowed in 
									//the RTDM protocol Frame
#define RTDM_POLLING		YES		// This defines the mode that RTDM will be operating in 
									//user's application. If it is YES then the user should place the 
									//RTDM_ProcessMsgs()	function in the main loop. 
									//In order to make sure that the messages are being preoccessed
									// it is recommended that the main loop always polls this 
									//function as fast as possible						
#define RTDM_MIN_CODE_SIZE	YES		//When defined causes the RTDM library to build  without 
									//including a pre-calculated polynomial  table for the CRC algorythim. 
									//This saves 768  bytes of code space. 
/*************************************************************************************************/		
    
   
    
    
    /* static snapshots can be taken activating the SNAPSHOT definition */
/* this feature is available only in DEBUG mode of the project */
/* load DMCI GUI from MPLAB - Tools tab 
Please consult DMCI help by pressing Help button on DMCI window for a
complete description of DMCI tool.
Using dedicated open button in DMCI window load dmci_snapshot.dmci 
setup file from the AN1292 project’s folder.
It contains in the Dynamic data view tab the proper variables setup */
/* static snapshots are captured running the code, and, when halt button
from the Debug toolbar is pressed, the DMCI graph windows are updated with
the captured data */
/* consult debug.c API for calling the specific SNAPSHOT debug functions:
   DBG_Init(void)	- debug initialization
   DBG_SnapStart(void) - start of SNAPSHOT trigger
   DBG_SnapUpdate(void) - SNAPSHOT variables update 
   These functions are called in pmsm.c */
/* 
For captured data setup please check: 
"DEFINITIONS FOR SNAP and RTDM captured variables"
section in this file 
*/
/* to enable static snapshot, define the following line */  
#define SNAPSHOT

/* undefine the line below for RTDM control demo */
//************** Real Time Data Monitor, RTDM *******************

#define RTDM		// This definition enabled Real Time Data Monitor, UART interrupts
					// to handle RTDM protocol, and array declarations for buffering
					// information in real time

#undef DMCI_DEMO	// Define this if a demo with DMCI is done. Start/stop of motor
					// and speed variation is done with DMCI instead of push button
					// and POT. Undefine "DMCI_DEMO" is user requires operating
					// this application with no DMCI
/* Real Time Debug Monitor enable - if activated, RTDM will allow real time
 control and monitoring of the embedded side from host DMCI interface */
/*
IMPORTANT:
___________________--__________--_____________________________________
Communication between the host computer and the target device (dsPIC33EP)
may fail due to noisy environment, real time specificity of the system 
or other unpredictable causes. 
Since the host computer is used to completely control the target device,
in such failure cases, use the RESET button on MCHV module to stop the 
execution and stop the motor.
___________________--__________--_____________________________________

Short usage guide 
(please consult the http://ww1.microchip.com/downloads/en/DeviceDoc/70567A.pdf
for detailed information on RTDM and its usage):
Open DMCI- Data Monitor and Control Interface window from the 
MPLAB’s Tools tab. Using afferent open pictogram, load dmci_rtdm.dmci
setup file from the AN1292 project’s folder. Within the DMCI window’s
frame, the following controls are available:
1/Boolean DMCIFlags.StartStop – used for start/stop  the motor
2/ Slider SpeedReference – used for reference speed modification
3/ Boolean DMCIFlags.Recorder – used for triggering a new sample of 
measured variables
4/ Slider SnapShotDelay – used for sample rate modification of 
the measured variables
5/ Graph 1-4 – Graphs of the measured variables: A phase current, 
q-axis current, estimated speed, estimated angle 
Running the application note software will connect the target
MCHV board to the host DMCI application as specified in above indicated 
User’s Guide.  
Suggested usage guide: 
1/ Run the program using Run button in Dynamic Data Input DMCI child window
– allow few seconds for communication protocol to be established without
issuing any other command
2/ Run DMCI tab – Remote communication menu, which should indicate 
connection status as DETECTED (if it doesn’t, please refer to the 
above indicated User guide for troubleshooting). Close the DMCI Remote 
Communication Properties window by pressing OK acknowledging the 
detected communication.
3/ Press Run Time Update button in Dynamic Data Input DMCI child window – 
this will update the host DMCI GUI with the initial setup already existing 
on target device
4/ Adjust the speed reference using the afferent Slider SpeedReference 
to a value of roughly 5000 (please note that both positive and negative 
speed references can be set, so bidirectional functioning is selected 
by default with DMCI_DEMO)
5/ Press Start/Stop button, switching it from OFF state to ON state 
using afferent Boolean DMCIFlags.StartStop button in Dynamic Data Input 
DMCI child window –  immediately the motor will start running
6/ Press Boolean DMCIFlags.Recorder in in Dynamic Data Input DMCI child 
window in order to trigger a sample of the measured variables(the button 
should be in ON state)
7/ Press Run Time Update button in Dynamic Data Input DMCI child window 
– this will update the host DMCI GUI with the snapped data in target device.
8/ Use Automated Event Control button to have steps 6/, 7/ executed 
automatically at 1 second period 
9/ Vary the reference speed, vary the snap shot delay, etc.
10/ Press Start/Stop button, switching it from ON state to OFF state 
using afferent Boolean DMCIFlags.StartStop button in Dynamic Data Input 
DMCI child window –  immediately the motor will stop running
*/
/* consult debug.c API for calling the specific RTDM functions:
   DBG_Init(void)	- RTDM initialization
   DBG_SyncComm(void) - RTDM syncrho target and host in pooling mode
   DBG_SnapUpdate(void) - RTDM variables update 
   These functions are called in pmsm.c */
/* 
For captured data setup please check: 
"DEFINITIONS FOR SNAP and RTDM captured variables"
section in this file 
*/

    
/****************************************************/
/* DEFINITIONS FOR SNAP and RTDM captured variables */
/****************************************************/


     
    #define DATA_BUFFER_SIZE 50  //Size in 16-bit Words of the snap */
                                  // the value depends on the dsPIC mem
    #define SNAPDELAY	5 // In number of PWM Interrupts
    #define	SNAP1		ParkParm.Ia*1000 //EstimParm.qEsdf*100//ParkParm.Ia*1000 //Current in mA
    #define	SNAP2		EstimParm.qVelEstim//SVGenParm.Vr2*1000//ParkParm.Ib*1000 //Current in mA
    #define SNAP3		ParkParm.Vq*1000
    #define SNAP4		CtrlParm.qVelRef //EstimParm.qRho*57.28//ParkParm.Vq*1000//ParkParm.Angle*57.28 //EstimParm.qRho*57.28 // Converting angle from radians to degrees => 360/2*PI = 57.28
/****************************************************/			
		
 #if defined RTDM_FCY
	#if defined RTDM_BAUDRATE
	 #define RTDM_BRG	(RTDM_FCY/(16*RTDM_BAUDRATE))-1
	#else
	  #error Cannot calculate BRG value. Please define RTDM_BAUDRATE in RTDMUSER.h file
	#endif
 #else
	 #error Cannot calculate RTDM_BRG value. Please define RTDM_FCY in RTDMUSER.h file
 #endif

 #define RTDM_BAUDRATE_ACTUAL	(RTDM_FCY/(16*(RTDM_BRG+1)))
 #define RTDM_BAUD_ERROR		((RTDM_BAUDRATE_ACTUAL > RTDM_BAUDRATE) ? RTDM_BAUDRATE_ACTUAL - RTDM_BAUDRATE : RTDM_BAUDRATE - RTDM_BAUDRATE_ACTUAL)
 #define RTDM_BAUD_ERROR_PERCENT	(((RTDM_BAUD_ERROR*100)+(RTDM_BAUDRATE/2))/RTDM_BAUDRATE)

 #if	(RTDM_BAUD_ERROR_PERCENT > 1)
	 #error The value loaded to the BRG register produces a baud rate error higher than 2%
 #endif


/**********************  RTDM FUNCTIONS **************************/
int RTDM_ProcessMsgs();
int RTDM_Close();
int RTDM_Start();
unsigned int RTDM_CumulativeCrc16 (unsigned char *buf, unsigned int u16Length, unsigned int u16CRC);
#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
