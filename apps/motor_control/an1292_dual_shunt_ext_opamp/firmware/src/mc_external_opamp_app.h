/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    mc_external_opamp_app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
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
//DOM-IGNORE-END

#ifndef _MC_EXTERNAL_OPAMP_APP_H
#define _MC_EXTERNAL_OPAMP_APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "classb/classb.h"
#include <math.h>
#include "peripheral/int/plib_int.h"
#include "peripheral/cdac/plib_cdac.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END 

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
typedef enum
{
	/* Application's state machine's initial state. */
	MC_EXTERNAL_OPAMP_APP_CLASSB_STATE_INIT=0,
	MC_EXTERNAL_OPAMP_APP_CLASSB_STATE_FLASH_CRC_TEST,
    MC_EXTERNAL_OPAMP_APP_CLASSB_STATE_CHECKER_BOARD_RAM_TEST,
    MC_EXTERNAL_OPAMP_APP_CLASSB_STATE_RAM_MARCHB_TEST,
    MC_EXTERNAL_OPAMP_APP_CLASSB_STATE_RAM_MARCHC_TEST,
    MC_EXTERNAL_OPAMP_APP_CLASSB_STATE_RAM_MARCHC_STACK_TEST,
    MC_EXTERNAL_OPAMP_APP_CLASSB_STATE_CLOCK_TEST,
    MC_EXTERNAL_OPAMP_APP_CLASSB_STATE_CPU_PC_TEST,
    MC_EXTERNAL_OPAMP_APP_CLASSB_STATE_CPU_REGISTERS_TEST,
    MC_EXTERNAL_OPAMP_APP_CLASSB_STATE_TEST_PASS,
    MC_EXTERNAL_OPAMP_APP_CLASSB_STATE_TEST_FAIL,
} MC_EXTERNAL_OPAMP_APP_CLASSB_STATES;

typedef struct 
{
    float   PWMPeriod;

    float   Vr1;
    float   Vr2;
    float   Vr3;
    float   Vr4;
    float   Vr5;
    float   Vr6;
} tSVGenParm;

typedef struct 
{
    float   qVelRef;    						// Reference velocity
    float   qVdRef;     						// Vd flux reference value
    float   qVqRef;     						// Vq torque reference value
	float	qRefRamp;							// Ramp for speed reference value
	float   qDiff;								// Speed of the ramp
} tCtrlParm;

typedef struct 
{
    float   RevAngle;
    float   Angle;
    float   Sin;
    float   Cos;
    float   Ia;
    float   Ib;
    float   Ialpha;
    float   Ibeta;
    float   Id;
    float   Iq;
    float   Vd;
    float   FW_Vd;
    float   Vq;
    float   FW_Vq;
    float   Valpha;
    float   Vbeta;
    float   V1;
    float   V2;
    float   V3;
    float   DCBusVoltage;
    float   halfDCBusVoltage;   
} tParkParm;

typedef struct 
{
    float   RevAngle;
    float   Angle;
    float   Sin;
    float   Cos;
} tSincosParm;

union  SYSTEM_STATUS_UNION 
{
    struct
    {
        unsigned RunMotor:1;  					/* run motor indication */
        unsigned OpenLoop:1;  					/* open loop/clsd loop indication */
        unsigned Btn1Pressed:1; 				/* btn 1 pressed indication */
        unsigned Btn2Pressed:1; 				/* btn 2 pressed indication */
        unsigned ChangeMode:1; 					/* mode changed indication - from open to clsd loop */
        unsigned ChangeSpeed:1; 				/* speed doubled indication */
        unsigned Btn2Debounce:1;
        unsigned ClassBPass:1;
        unsigned    :8;
    }bit;
    
	unsigned short Word;
}MC_EXTERNAL_OPAMP_APP_MC_CONTROL ;        						// general flags

typedef struct 
{
    float   qdSum;          
    float   qKp;
    float   qKi;
    float   qKc;
    float   qOutMax;
    float   qOutMin;
    float   qInRef; 
    float   qInMeas;
    float   qOut;
    float   qErr;
} tPIParm;

typedef struct 
{
    float	qDeltaT;      						// Integration constant
    float   qRho;    	    					// angle of estimation
    float   qRhoStateVar; 						// internal variable for angle
    float   qOmegaMr;     						// primary speed estimation
    float   qLastIalpha;  						// last value for Ialpha
    float   qLastIbeta;   						// last value for Ibeta
    float   qDIalpha;     						// difference Ialpha
    float   qDIbeta;      						// difference Ibeta
	float	qEsa;								// BEMF alpha
	float	qEsb;								// BEMF beta
	float	qEsd;								// BEMF d
	float	qEsq;								// BEMF q
    float	qVIndalpha;   						// dI*Ls/dt alpha
	float	qVIndbeta;    						// dI*Ls/dt beta
	float	qEsdf;        						// BEMF d filtered
	float	qEsqf;        						// BEMF q filtered
	float	qKfilterEsdq; 						// filter constant for d-q BEMF
	float   qVelEstim; 							// Estimated speed 
	float   qVelEstimFilterK; 					// Filter Konstant for Estimated speed 
    float   qLastValpha;  						// Value from last control step Ialpha 
    float   qLastVbeta;   						// Value from last control step Ibeta
	float   RhoOffset;            				// estima angle init offset
} tEstimParm;

typedef struct 
{
	float	qRs;								// Rs value - stator resistance
	float	qLsDt;								// Ls/dt value - stator inductand / dt - variable with speed
   	float	qInvKFi;	    					// InvKfi constant value ( InvKfi = Omega/BEMF )
} tMotorEstimParm;

#define     PBCLK_PWM                                           (SYS_CLK_FREQ/1)
//===============================================================
#define     PWM_FREQ                                            20000
#define     PWM_RELOAD_EDGE                                     ((PBCLK_PWM/PWM_FREQ)-1)
#define     PWM_RELOAD_CENTER                                   (((PBCLK_PWM/PWM_FREQ)/2)-1)
#define     DEADTIME_SEC                                        (float)0.000001
#define     DEADTIME_REG                                        DEADTIME_SEC*SYS_CLK_FREQ
#define     PWM_IOCON_CONFIG                                    0x007DC000    
//===============================================================
// Following parameters for MCLV-2 board
// Gain of opamp = 15
// shunt resistor = 0.025 ohms
// DC offset = 1.65V
// max current = x
// (x * 0.025 * 15) + 1.65V = 3.3V
// x = 4.4Amps
#define     MAX_CURRENT                                         (float)(4.4)
#define     OCP                                                 (float)(4.4)
#define     VREF_DAC_VALUE                                      (int) 1900
#define     ADC_CURRENT_SCALE                                   (float)(MAX_CURRENT/(float)2048)

#define     CURRENT_LIMIT_CMP_REF                               (int)(((float)2048*(OCP/MAX_CURRENT))+VREF_DAC_VALUE)
#define     MOTOR_PER_PHASE_RESISTANCE                          ((float)2.10)
#define     MOTOR_PER_PHASE_INDUCTANCE                          ((float)0.00192)
#define     MOTOR_BACK_EMF_CONSTANT_Vpeak_Line_Line_KRPM_MECH   (float)7.24
#define     NOPOLESPAIRS                                        5
#define     MAX_ADC_COUNT                                       (float)4095     // for 12-bit ADC
#define     MAX_ADC_INPUT_VOLTAGE                               (float)3.3      // volts


#define     DCBUS_SENSE_TOP_RESISTOR                            (float)30.0
#define     DCBUS_SENSE_BOTTOM_RESISTOR                         (float)2.0
#define     DCBUS_SENSE_RATIO                                   (float)(DCBUS_SENSE_BOTTOM_RESISTOR/(DCBUS_SENSE_BOTTOM_RESISTOR + DCBUS_SENSE_TOP_RESISTOR))
#define     VOLTAGE_ADC_TO_PHY_RATIO                            (float)(MAX_ADC_INPUT_VOLTAGE/(MAX_ADC_COUNT * DCBUS_SENSE_RATIO))
#define     BTN1                                                (PORTGbits.RG1) // BTN_1 -> Start Switch
#define     BTN2                                                (PORTCbits.RC7) // BTN_2   

#define     SINGLE_ELEC_ROT_RADS_PER_SEC                        (float)(2*M_PI)

#define     MAX_DUTY                                            (PWM_RELOAD_CENTER)
#define     LOOPTIME_SEC                                        (float)0.00005           // PWM Period - 50 uSec, 20Khz PWM

#define     LOCK_TIME_IN_SEC                                     2
#define     LOCK_COUNT_FOR_LOCK_TIME                            (unsigned int)((float)LOCK_TIME_IN_SEC/(float)LOOPTIME_SEC)
#define     END_SPEED_RPM                                       500 // Value in RPM

#define     END_SPEED_RPS                                       ((float)END_SPEED_RPM/60)

// In 1 second, the motor maked "END_SPEED_RPS" mechanical rotations
#define     RAMP_TIME_IN_SEC                                     3
#define     END_SPEED_RADS_PER_SEC_MECH                         (float)(END_SPEED_RPS * SINGLE_ELEC_ROT_RADS_PER_SEC)
#define     END_SPEED_RADS_PER_SEC_ELEC                         (float)(END_SPEED_RADS_PER_SEC_MECH * NOPOLESPAIRS)
#define     END_SPEED_RADS_PER_SEC_ELEC_IN_LOOPTIME             (float)(END_SPEED_RADS_PER_SEC_ELEC * LOOPTIME_SEC)
#define     OPENLOOP_RAMPSPEED_INCREASERATE                     (float)(END_SPEED_RADS_PER_SEC_ELEC_IN_LOOPTIME/(RAMP_TIME_IN_SEC/LOOPTIME_SEC))

/* end speed conveted to fit the startup ramp */
#define     Q_CURRENT_REF_OPENLOOP           1.8

/* Nominal speed of the motor in RPM */
#define     NOMINAL_SPEED_RPM                                   (float)2800 // Value in RPM
#define     NOMINAL_SPEED_RAD_PER_SEC_ELEC                      (float)(((NOMINAL_SPEED_RPM/60)*2*M_PI)*NOPOLESPAIRS) // Value in RPM
   
#define     MOTOR_BACK_EMF_CONSTANT_Vpeak_PHASE_RPM_MECH        (float)((MOTOR_BACK_EMF_CONSTANT_Vpeak_Line_Line_KRPM_MECH/1.732)/1000)
#define     MOTOR_BACK_EMF_CONSTANT_Vpeak_PHASE_RPS_MECH        (float)(MOTOR_BACK_EMF_CONSTANT_Vpeak_PHASE_RPM_MECH * 60)
#define     MOTOR_BACK_EMF_CONSTANT_Vpeak_PHASE_RAD_PER_SEC_MECH (float)(MOTOR_BACK_EMF_CONSTANT_Vpeak_PHASE_RPS_MECH/(2*M_PI))
#define     MOTOR_BACK_EMF_CONSTANT_Vpeak_PHASE_RAD_PER_SEC_ELEC (float)(MOTOR_BACK_EMF_CONSTANT_Vpeak_PHASE_RAD_PER_SEC_MECH/NOPOLESPAIRS)

/* PI controllers tuning values - */
//******** D Control Loop Coefficients *******
#define     D_CURRCNTR_PTERM                                    (0.05/MAX_CURRENT)
#define     D_CURRCNTR_ITERM                                    (0.00004 /MAX_CURRENT)
#define     D_CURRCNTR_CTERM                                    (0.999/MAX_CURRENT)
#define     D_CURRCNTR_OUTMAX                                    0.999

//******** Q Control Loop Coefficients *******
#define     Q_CURRCNTR_PTERM                                    (0.05/MAX_CURRENT)
#define     Q_CURRCNTR_ITERM                                    (0.00004 /MAX_CURRENT)
#define     Q_CURRCNTR_CTERM                                    (0.999/MAX_CURRENT)
#define     Q_CURRCNTR_OUTMAX                                    0.999

//*** Velocity Control Loop Coefficients *****
#define     SPEEDCNTR_PTERM                                     (2.5 * (M_PI/30))
#define     SPEEDCNTR_ITERM                                     (0.018 * (M_PI/30))//0.005
#define     SPEEDCNTR_CTERM                                      0.5
#define     SPEEDCNTR_OUTMAX                                     6

#define     KFILTER_ESDQ                                        (float)((float)1200/(float)32767)
#define     KFILTER_VELESTIM                                    (float)((float)(2*374)/(float)32767)
#define     INITOFFSET_TRANS_OPEN_CLSD                          (float)((float)0x2000/(float)32767)

#define     FW_SPEED_RPM                                        (float)5000
#define     FW_SPEED_RAD_PER_SEC_ELEC                           (float)(((FW_SPEED_RPM/60)*2*M_PI)*NOPOLESPAIRS)
#define     SPEED_COMMAND_RAMP_UP_TIME                          (float)25.0 // seconds
#define     MAX_FW_NEGATIVE_ID_REF                              (float)(-1.6)

#define     POT_ADC_COUNT_FW_SPEED_RATIO                        (float)(FW_SPEED_RAD_PER_SEC_ELEC/MAX_ADC_COUNT)

extern  	tPIParm     										PIParmQ;        /* parms for PI controlers */
extern  	tPIParm     										PIParmD;        /* parms for PI controlers */
extern 		tParkParm											ParkParm;
extern 		tSincosParm											SincosParm;
extern 		tSVGenParm 											SVGenParm;    
extern 		float 												dPWM1, dPWM2, dPWM3;
extern 		tCtrlParm 											CtrlParm;

typedef 	signed int 											int32_t;
#define 	TOTAL_SINE_TABLE_ANGLE      						(2*M_PI)
#define 	TABLE_SIZE      									256
#define 	ANGLE_STEP      									(float)((float)TOTAL_SINE_TABLE_ANGLE/(float)TABLE_SIZE)

extern 		const float 										sineTable[TABLE_SIZE];
extern 		const float 										cosineTable[TABLE_SIZE];

extern 		tEstimParm 											EstimParm;
extern 		tMotorEstimParm 									MotorEstimParm;

typedef enum
{
	/* Application's state machine's initial state. */
	MC_EXTERNAL_OPAMP_APP_MC_STATE_INIT=0,
	MC_EXTERNAL_OPAMP_APP_MC_STATE_NOP,
    MC_EXTERNAL_OPAMP_APP_MC_STATE_STOP,
} MC_EXTERNAL_OPAMP_APP_MC_STATES;

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
	/* Application's state machine's initial state. */
	MC_EXTERNAL_OPAMP_APP_STATE_INIT=0,
	MC_EXTERNAL_OPAMP_APP_STATE_SERVICE_TASKS,

	/* TODO: Define states used by the application state machine. */


} MC_EXTERNAL_OPAMP_APP_STATES;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    MC_EXTERNAL_OPAMP_APP_STATES state;

    /* TODO: Define any additional data used by the application. */
	MC_EXTERNAL_OPAMP_APP_CLASSB_STATES classBState;
	MC_EXTERNAL_OPAMP_APP_MC_STATES mcState;

} MC_EXTERNAL_OPAMP_APP_DATA;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/
	
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void MC_EXTERNAL_OPAMP_APP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the 
    application in its initial state and prepares it to run so that its 
    APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    MC_EXTERNAL_OPAMP_APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void MC_EXTERNAL_OPAMP_APP_Initialize ( void );


/*******************************************************************************
  Function:
    void MC_EXTERNAL_OPAMP_APP_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    MC_EXTERNAL_OPAMP_APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void MC_EXTERNAL_OPAMP_APP_Tasks( void );

/* MC Core Routines */
void MC_EXTERNAL_OPAMP_APP_MC_InvPark(void);
void MC_EXTERNAL_OPAMP_APP_MC_CalcRefVec(void);
void MC_EXTERNAL_OPAMP_APP_MC_Clarke(void);
void MC_EXTERNAL_OPAMP_APP_MC_Park(void);
void MC_EXTERNAL_OPAMP_APP_MC_CalcSVGen( void );
void MC_EXTERNAL_OPAMP_APP_MC_InitControlParameters(void);
void MC_EXTERNAL_OPAMP_APP_MC_InitPI( tPIParm *pParm);
void MC_EXTERNAL_OPAMP_APP_MC_CalcPI( tPIParm *pParm);
void MC_EXTERNAL_OPAMP_APP_MC_SinCos(void);
void MC_EXTERNAL_OPAMP_APP_MC_CalculateParkAngle(void);
void MC_EXTERNAL_OPAMP_APP_MC_DoControl( void );

/*MC PLL Estimator Routines */
void MC_EXTERNAL_OPAMP_APP_MC_Estim(void);
void MC_EXTERNAL_OPAMP_APP_MC_InitEstimParm(void);

/* MC Debug Routines */
void MC_EXTERNAL_OPAMP_APP_MC_DBG_Init(void);
void MC_EXTERNAL_OPAMP_APP_MC_DBG_SyncComm(void);
void MC_EXTERNAL_OPAMP_APP_MC_DBG_SnapUpdate(void);
void MC_EXTERNAL_OPAMP_APP_MC_DBG_IDLECounter(void);

/* MC Peripheral Init Routines */
void MC_EXTERNAL_OPAMP_APP_PWM_Initialize(void);
void MC_EXTERNAL_OPAMP_APP_PWM_Enable(void);
void MC_EXTERNAL_OPAMP_APP_PWM_Disable(void);
void MC_EXTERNAL_OPAMP_APP_DAC_Initialize(void);

#endif /* _MC_EXTERNAL_OPAMP_APP_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

