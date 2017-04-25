/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
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

#include "system/common/sys_common.h"
#include "mc_internal_opamp_app.h"
#include "mc_rtdm_app.h"
#include "system_definitions.h"
MC_INTERNAL_OPAMP_APP_DATA mc_internal_opamp_appData;
short phaseCurrentA;
short phaseCurrentB;
short potReading;
int dutyCycleA;
int dutyCycleB;
int dutyCycleC;
// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************


void __ISR(_ADC_DATA0_VECTOR, ipl3AUTO) _IntHandlerDrvAdc(void)
{
 
    phaseCurrentA = ADCDATA0; // Phase Current A is connected to AN24 on ADC0

    phaseCurrentB = ADCDATA4;// Phase Current B is connected to AN9 on ADC4
    potReading = ADCDATA15;   // Speed Potentiometer is connected to AN15 on ADC7  
    ParkParm.DCBusVoltage = (float)ADCDATA10 * VOLTAGE_ADC_TO_PHY_RATIO; // Reads and translates to actual bus voltage
    ParkParm.halfDCBusVoltage = (float)(ParkParm.DCBusVoltage/2); 

    
    phaseCurrentA = (phaseCurrentA - 2048); // ground is 2048, hence removing the offset
    phaseCurrentB = (phaseCurrentB - 2048);

    ParkParm.Ia = (float)phaseCurrentA*ADC_CURRENT_SCALE * (-1); 
    ParkParm.Ib = (float)phaseCurrentB*ADC_CURRENT_SCALE * (-1);
    
    MC_INTERNAL_OPAMP_APP_MC_Clarke();
   
    MC_INTERNAL_OPAMP_APP_MC_Park();
    
    MC_INTERNAL_OPAMP_APP_MC_Estim();
       
    // Calculate control values
    MC_INTERNAL_OPAMP_APP_MC_DoControl();
  

    MC_INTERNAL_OPAMP_APP_MC_CalculateParkAngle();

    /* if open loop */
    if(MC_INTERNAL_OPAMP_APP_MC_CONTROL.bit.OpenLoop == 1)
    {
        if(MC_INTERNAL_OPAMP_APP_MC_CONTROL.bit.Btn2Pressed == 0)
        {
        /* the angle is given by parkparm */
        SincosParm.Angle = ParkParm.Angle;
        }
        else
        {
           /* the angle is given by parkparm */
        SincosParm.Angle = ParkParm.RevAngle;  
        }
    } 
    else
    {
        /* if closed loop, angle generated by estim */
        SincosParm.Angle = EstimParm.qRho;
    }
    MC_INTERNAL_OPAMP_APP_MC_SinCos();
    ParkParm.Sin = SincosParm.Sin;
    ParkParm.Cos = SincosParm.Cos;
    

 
    MC_INTERNAL_OPAMP_APP_MC_InvPark();

    MC_INTERNAL_OPAMP_APP_MC_CalcRefVec();
  
     
    MC_INTERNAL_OPAMP_APP_MC_CalcSVGen();

    
    PDC1 = (unsigned int)dPWM1;
    PDC2 = (unsigned int)dPWM2;
    PDC3 = (unsigned int)dPWM3;
       
 
    IFS3bits.AD1D0IF = 0;  
MC_INTERNAL_OPAMP_APP_MC_CONTROL.bit.Btn2Debounce = 1;

/* Clear ADC Interrupt Flag */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_ADC_1_DATA0);
}


void __ISR(_PWM1_VECTOR, ipl4AUTO) _IntHandlerPWM_1_Instance0(void)
{
    PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G,PORTS_BIT_POS_15); // LED D2 Turns ON upon PWM Fault
    mc_internal_opamp_appData.state = MC_INTERNAL_OPAMP_APP_MC_STATE_STOP;
    
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_PWM1);
}



/*******************************************************************************
 End of File
*/