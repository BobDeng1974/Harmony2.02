/*******************************************************************************
  I2C Bit-Bang Interrupt model function definitions file

  Company:
    Microchip Technology Inc.

  File Name:
    drv_i2c_bb.c        

 * Summary:     This is a sample project demonstrating an I2C Master
 *              device simulated in software.  The project consists of an 
 *              initialization function, functions to perform I2C bus operations  
 *              and an Interrupt Service Routine (ISR) that contains the I2C Master 
 *              state machine.  The ISR is responsible for performing the START, 
 *              STOP, RESTART, WRITE byte and READ byte operation.              
 *              This project uses the IO pins of I2C-2 peripheral. If another
 *              I2C module, other that I2C2 is required to be used, this can be
 *              done so by modifying the port definition is i2c_bitbang_isr.h.
 * 
 *              This is developed in accordance with In accordance with the 
 *              I2C Bus Specification and User Manual Revision 6, April 2014.
 * 
 *              The i2c_bitbang_isr.c was tested with SYSCLK running at 200 MHz
 *              and PBCLK 3 that the timer is based on running at 100 MHz 
*******************************************************************************/
/*******************************************************************************
 *                      FEATURES NOT SUPPORTED
 *                 --------------------------------
 *  a. MULTI MASTER
 *  b. 10-BIT ADDRESSING
 *  c. CLOCK SYNCHRONIZATION 
 *  D. BUS ARBITRATION
 *  E. Does not support FM+ (1 Mbit/s) and greater
 * ****************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2015 released Microchip Technology Inc.  All rights reserved.

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

#include <xc.h>
#include "driver/i2c/drv_i2c_bb.h"

// *****************************************************************************
/*
 Upper address limit for a 7-bit address 
 */

#define ADDRESS_7BIT_UPPER_LIMIT                    0xFF



#define ERROR_TIMEOUT_COUNT         2000000

// *****************************************************************************
/* Macro: _DRV_I2C_CLIENT_OBJ(obj,mem)

  Summary:
    Returns the appropriate client member

  Description:
    Either return the static object or returns the indexed dynamic object.
    This macro has variations for dynamic or static driver.
*/

#define _DRV_I2C_CLIENT_OBJ(obj,mem)    obj->mem

void StartI2C(DRV_HANDLE);


// *****************************************************************************
/* Function:
    I2C_Initialize (uint32_t baudrate)

  Input: I2C baud rate
 
  Output: None

  Summary:
    Initializes the TRI, LAT and Open drain enable value for the I2C pins

  Description:
    Initializes the TRI, LAT and Open drain enable value for the I2C pins

  Remarks:
    None.
*/

void DRV_I2C_BB_Initialize(DRV_I2C_OBJ *dObj, DRV_I2C_INIT * i2cInit)
{
    
    PLIB_PORTS_PinClear(PORTS_ID_0, dObj->portSCL, dObj->pinSCL);		//Make SCL LAT value 0
	PLIB_PORTS_PinClear(PORTS_ID_0, dObj->portSDA, dObj->pinSDA);		//Make SDA LAT value 0
        
    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSCL, dObj->pinSCL);			//set SCL_INPUT 
    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA);			
	PLIB_PORTS_PinOpenDrainEnable(PORTS_ID_0, dObj->portSCL, dObj->pinSCL);
	PLIB_PORTS_PinOpenDrainEnable(PORTS_ID_0, dObj->portSDA, dObj->pinSDA);
           
	PLIB_TMR_PrescaleSelect(dObj->tmrSource, TMR_PRESCALE_VALUE_1);
	PLIB_TMR_ClockSourceSelect(dObj->tmrSource, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
	
	// Load the period register
#if defined  __PIC32MZ
	PLIB_TMR_Period16BitSet(dObj->tmrSource, (SYS_CLK_PeripheralFrequencyGet ( CLK_BUS_PERIPHERAL_2 )/(i2cInit->baudRate<<2)));   
#endif    
    
    PLIB_INT_SourceFlagClear(INT_ID_0, dObj->tmrInterruptSource);
    PLIB_INT_SourceEnable(INT_ID_0, dObj->tmrInterruptSource);

    
}

DRV_I2C_BUFFER_HANDLE DRV_I2C_MasterBufferWriteXE(DRV_HANDLE handle, uint16_t deviceaddress, uint8_t* txBuffer, uint16_t txbuflen)
{
    
    DRV_I2C_BUFFER_OBJECT   *i2cDataObj;
    DRV_I2C_OBJ             *dObj = ((DRV_I2C_CLIENT_OBJ *) handle)->driverObject;
    
    bool queueEmptyTest = false;
    
    queueEmptyTest = _DRV_I2C_IsQueueEmpty(dObj);
    
        /* Get a slot in the queue */
    i2cDataObj = _DRV_I2C_QueueSlotGet ( dObj );
    
    
    if (i2cDataObj != NULL)
    {
        i2cDataObj->i2cPerph            = DRV_I2C_BIT_BANG;
        i2cDataObj->clientHandle        = handle;
        if (deviceaddress > ADDRESS_7BIT_UPPER_LIMIT )
        {
            i2cDataObj->slaveaddresshighbyte = (uint8_t)((deviceaddress & 0xFF00)>>8);
            i2cDataObj->slaveaddresslowbyte  = (uint8_t)(deviceaddress & 0x00FF);
        }
        else
        {
            i2cDataObj->slaveaddresshighbyte = (uint8_t)(deviceaddress & 0x00FF);
            i2cDataObj->slaveaddresslowbyte  = 0;
        }
        i2cDataObj->operation           = DRV_I2C_OP_WRITE;
        i2cDataObj->txBuffer            = txBuffer;
        i2cDataObj->rxBuffer            = NULL;
        i2cDataObj->transferSize        = txbuflen;
        i2cDataObj->readtransferSize    = 0;
        i2cDataObj->actualtransfersize  = 0;
        i2cDataObj->status              = DRV_I2C_BUFFER_EVENT_PENDING;
        i2cDataObj->context             = 0x00;
        
        
        _DRV_I2C_QueuePush( dObj, i2cDataObj);
        

        /*  initiate START condition only if I2C bit-bang 
            is not active, i.e. timer is not running, TMRx = 0  */

        if (queueEmptyTest)
        {
            StartI2C((DRV_HANDLE)handle);
            dObj->I2CSWCounter        = 9;
        }
        
        return (DRV_I2C_BUFFER_HANDLE)i2cDataObj;
    }
    else 
        return (DRV_I2C_BUFFER_HANDLE)NULL;
    

}

DRV_I2C_BUFFER_HANDLE DRV_I2C_MasterBufferWrite(DRV_HANDLE handle, uint8_t* deviceaddress, uint8_t* txBuffer, uint16_t txbuflen)
{
    
    DRV_I2C_BUFFER_OBJECT   *i2cDataObj;
    DRV_I2C_OBJ             *dObj = ((DRV_I2C_CLIENT_OBJ *) handle)->driverObject;
    
    bool queueEmptyTest = false;
    
    queueEmptyTest = _DRV_I2C_IsQueueEmpty(dObj);
    
        /* Get a slot in the queue */
    i2cDataObj = _DRV_I2C_QueueSlotGet ( dObj );
    
    
    if (i2cDataObj != NULL)
    {
        i2cDataObj->i2cPerph                = DRV_I2C_BIT_BANG;
        i2cDataObj->clientHandle            = handle;
        i2cDataObj->slaveaddresshighbyte    = *(deviceaddress);
        i2cDataObj->slaveaddresslowbyte     = 0x00;
        i2cDataObj->operation               = DRV_I2C_OP_WRITE;
        i2cDataObj->txBuffer                = txBuffer;
        i2cDataObj->rxBuffer                = NULL;
        i2cDataObj->transferSize            = txbuflen;
        i2cDataObj->readtransferSize        = 0;
        i2cDataObj->actualtransfersize      = 0;
        i2cDataObj->status                  = DRV_I2C_BUFFER_EVENT_PENDING;
        i2cDataObj->context                 = 0x00;
        
        _DRV_I2C_QueuePush( dObj, i2cDataObj);
        

        /*  initiate START condition only if I2C bit-bang 
            is not active, i.e. timer is not running, TMRx = 0  */

        if (queueEmptyTest)
        {
            StartI2C((DRV_HANDLE)handle);
            dObj->I2CSWCounter        = 9;
        }
        
        return (DRV_I2C_BUFFER_HANDLE)i2cDataObj;
    }
    else 
        return (DRV_I2C_BUFFER_HANDLE)NULL;
    

}

DRV_I2C_BUFFER_HANDLE DRV_I2C_MasterBufferReadXE(DRV_HANDLE handle, uint16_t deviceaddress, uint8_t* rxBuffer, uint16_t rxbuflen)
{
    
    DRV_I2C_BUFFER_OBJECT   *i2cDataObj;
    DRV_I2C_OBJ             *dObj = ((DRV_I2C_CLIENT_OBJ *) handle)->driverObject;
    
    bool queueEmptyTest = false;
    
    queueEmptyTest = _DRV_I2C_IsQueueEmpty(dObj);

        /* Get a slot in the queue */
    i2cDataObj = _DRV_I2C_QueueSlotGet ( dObj );
    

    if (i2cDataObj != NULL)
    {
        /* Fill the data directly to the queue. Set the inUse flag only at the end */
        i2cDataObj->i2cPerph            = DRV_I2C_BIT_BANG;
        i2cDataObj->clientHandle        = handle;
        if (deviceaddress > ADDRESS_7BIT_UPPER_LIMIT )
        {
            i2cDataObj->slaveaddresshighbyte = (uint8_t)((deviceaddress & 0xFF00)>>8);
            i2cDataObj->slaveaddresslowbyte  = (uint8_t)(deviceaddress & 0x00FF);
        }
        else
        {
            i2cDataObj->slaveaddresshighbyte = (uint8_t)(deviceaddress & 0x00FF);
            i2cDataObj->slaveaddresslowbyte  = 0;
        }
        i2cDataObj->operation           = DRV_I2C_OP_READ;
        i2cDataObj->txBuffer            = NULL;
        i2cDataObj->rxBuffer            = rxBuffer;
        i2cDataObj->transferSize        = 0;
        i2cDataObj->readtransferSize    = rxbuflen;
        i2cDataObj->actualtransfersize  = 0;
        i2cDataObj->status              = DRV_I2C_BUFFER_EVENT_PENDING;
        i2cDataObj->context             = 0x00;
        
        _DRV_I2C_QueuePush( dObj, i2cDataObj);   
                   
    
        /*  initiate START condition only if I2C bit-bang 
            is not active, i.e. timer is not running, TMRx = 0  */
        if (queueEmptyTest)
        {
            StartI2C((DRV_HANDLE)handle);
            dObj->I2CSWCounter        = 9;
        }
        
        return (DRV_I2C_BUFFER_HANDLE)i2cDataObj;
    }
    else 
        return (DRV_I2C_BUFFER_HANDLE)NULL;
    
}

DRV_I2C_BUFFER_HANDLE DRV_I2C_MasterBufferRead(DRV_HANDLE handle, uint8_t* deviceaddress, uint8_t* rxBuffer, uint16_t rxbuflen)
{
    
    DRV_I2C_BUFFER_OBJECT   *i2cDataObj;
    DRV_I2C_OBJ             *dObj = ((DRV_I2C_CLIENT_OBJ *) handle)->driverObject;
    
    bool queueEmptyTest = false;
    
    queueEmptyTest = _DRV_I2C_IsQueueEmpty(dObj);

        /* Get a slot in the queue */
    i2cDataObj = _DRV_I2C_QueueSlotGet ( dObj );
    

    if (i2cDataObj != NULL)
    {
        /* Fill the data directly to the queue. Set the inUse flag only at the end */
        i2cDataObj->i2cPerph                = DRV_I2C_BIT_BANG;
        i2cDataObj->clientHandle            = handle;
        i2cDataObj->slaveaddresshighbyte    = *(deviceaddress);
        i2cDataObj->slaveaddresslowbyte     = 0x00;
        i2cDataObj->operation               = DRV_I2C_OP_READ;
        i2cDataObj->txBuffer                = NULL;
        i2cDataObj->rxBuffer                = rxBuffer;
        i2cDataObj->transferSize            = 0;
        i2cDataObj->readtransferSize        = rxbuflen;
        i2cDataObj->actualtransfersize      = 0;
        i2cDataObj->status                  = DRV_I2C_BUFFER_EVENT_PENDING;
        i2cDataObj->context                 = 0x00;
        
        _DRV_I2C_QueuePush( dObj, i2cDataObj);   
                   
    
        /*  initiate START condition only if I2C bit-bang 
            is not active, i.e. timer is not running, TMRx = 0  */
        if (queueEmptyTest)
        {
            StartI2C((DRV_HANDLE)handle);
            dObj->I2CSWCounter        = 9;
        }
        
        return (DRV_I2C_BUFFER_HANDLE)i2cDataObj;
    }
    else 
        return (DRV_I2C_BUFFER_HANDLE)NULL;
    
}

DRV_I2C_BUFFER_HANDLE DRV_I2C_MasterBufferWriteReadXE(DRV_HANDLE handle, uint16_t deviceaddress, uint8_t* txBuffer, uint16_t txbuflen, uint8_t* rxBuffer, uint16_t rxbuflen)
{
    
    DRV_I2C_BUFFER_OBJECT   *i2cDataObj;
    DRV_I2C_OBJ             *dObj = ((DRV_I2C_CLIENT_OBJ *) handle)->driverObject;
    
    bool queueEmptyTest = false;
    
    queueEmptyTest = _DRV_I2C_IsQueueEmpty(dObj);
    
        /* Get a slot in the queue */
    i2cDataObj = _DRV_I2C_QueueSlotGet ( dObj );
    
    if (i2cDataObj != NULL)
    {
        i2cDataObj->i2cPerph            = DRV_I2C_BIT_BANG;
        i2cDataObj->clientHandle        = handle;
        if (deviceaddress > ADDRESS_7BIT_UPPER_LIMIT )
        {
            i2cDataObj->slaveaddresshighbyte = (uint8_t)((deviceaddress & 0xFF00)>>8);
            i2cDataObj->slaveaddresslowbyte  = (uint8_t)(deviceaddress & 0x00FF);
        }
        else
        {
            i2cDataObj->slaveaddresshighbyte = (uint8_t)(deviceaddress & 0x00FF);
            i2cDataObj->slaveaddresslowbyte  = 0;
        }
        i2cDataObj->operation           = DRV_I2C_OP_WRITE_READ;
        i2cDataObj->txBuffer            = txBuffer;
        i2cDataObj->rxBuffer            = rxBuffer;
        i2cDataObj->transferSize        = txbuflen;
        i2cDataObj->readtransferSize    = rxbuflen;
        i2cDataObj->actualtransfersize  = 0;
        i2cDataObj->status              = DRV_I2C_BUFFER_EVENT_PENDING;
        i2cDataObj->context             = 0x00;
        
        _DRV_I2C_QueuePush( dObj, i2cDataObj);
                              
        if (queueEmptyTest)
        {
            StartI2C((DRV_HANDLE)handle);
            dObj->I2CSWCounter        = 9;
        }
        
        return (DRV_I2C_BUFFER_HANDLE)i2cDataObj;
    }
    else 
        return (DRV_I2C_BUFFER_HANDLE)NULL;
    
}

DRV_I2C_BUFFER_HANDLE DRV_I2C_MasterBufferWriteRead(DRV_HANDLE handle, uint8_t* deviceaddress, uint8_t* txBuffer, uint16_t txbuflen, uint8_t* rxBuffer, uint16_t rxbuflen)
{
    
    DRV_I2C_BUFFER_OBJECT   *i2cDataObj;
    DRV_I2C_OBJ             *dObj = ((DRV_I2C_CLIENT_OBJ *) handle)->driverObject;
    
    bool queueEmptyTest = false;
    
    queueEmptyTest = _DRV_I2C_IsQueueEmpty(dObj);
    
        /* Get a slot in the queue */
    i2cDataObj = _DRV_I2C_QueueSlotGet ( dObj );
    
    if (i2cDataObj != NULL)
    {
        i2cDataObj->i2cPerph                = DRV_I2C_BIT_BANG;
        i2cDataObj->clientHandle            = handle;
        i2cDataObj->slaveaddresshighbyte    = *(deviceaddress);
        i2cDataObj->slaveaddresslowbyte     = 0x00;
        i2cDataObj->operation               = DRV_I2C_OP_WRITE_READ;
        i2cDataObj->txBuffer                = txBuffer;
        i2cDataObj->rxBuffer                = rxBuffer;
        i2cDataObj->transferSize            = txbuflen;
        i2cDataObj->readtransferSize        = rxbuflen;
        i2cDataObj->actualtransfersize      = 0;
        i2cDataObj->status                  = DRV_I2C_BUFFER_EVENT_PENDING;
        i2cDataObj->context                 = 0x00;
        
        _DRV_I2C_QueuePush( dObj, i2cDataObj);
                              
        if (queueEmptyTest)
        {
            StartI2C((DRV_HANDLE)handle);
            dObj->I2CSWCounter        = 9;
        }
        
        return (DRV_I2C_BUFFER_HANDLE)i2cDataObj;
    }
    else 
        return (DRV_I2C_BUFFER_HANDLE)NULL;
    
}

//bool DRV_I2C_MasterACKStatus(void)
//{
//    return I2CACKStatus;
//}

// *****************************************************************************
/* Function:
    void StartI2C(void)

  Input: None
 
  Output: None

  Summary:
    Generates START condition on I2C bus

  Description:
    Initiate a START condition on I2C bus. 

  Remarks:
    Check for BUS IDLE before setting a START condition
*/

void StartI2C(DRV_HANDLE handle)
{
    DRV_I2C_OBJ             *dObj = ((DRV_I2C_CLIENT_OBJ *) handle)->driverObject;
    
    /* send START command only if SCL and SDA are pulled high */
    if ((PLIB_PORTS_PinGet(PORTS_ID_0, dObj->portSCL, dObj->pinSCL) == HIGH) && 
                    (PLIB_PORTS_PinGet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA) == HIGH))
    {
        dObj->i2cState = I2C_SDA_LOW_START;
        PLIB_TMR_Counter16BitClear(dObj->tmrSource);
        PLIB_TMR_Start(dObj->tmrSource);
        
        dObj->I2CNACKOut = false;
        dObj->I2CACKStatus = false;

        dObj->errorTimeOut = ERROR_TIMEOUT_COUNT;
        dObj->ACKSTATUS_M  = false;
    }
}


// *****************************************************************************
/* Function:
    bool IsByteAcked(void)

  Input: None
 
  Output: status of ACK or ACK after sending a byte

  Summary:
    Checks the status of ACK or NACK of a byte

  Description:
    Checks the status of ACK or NACK and return true if ACK; false if NACK

  Remarks:
    None
*/

//inline bool IsByteAcked(void)
//{
    //if (I2CACKStatus == 0)
    //    return true;     
    //else              
    //    return false;    
//}

inline void DRV_I2C_BB_Tasks ( SYS_MODULE_OBJ object )
{            
    DRV_I2C_OBJ             *dObj           = (DRV_I2C_OBJ*)object;
    
    DRV_I2C_BUFFER_OBJECT   *lBufferObj     = dObj->taskLObj;
    
    switch (dObj->i2cState)
    {        
        case I2C_SDA_LOW_START:                     //1/2 BRG time has expired after SDA and SCL high
            PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA);
                                                    //pull SDA low
            dObj->i2cState = I2C_SDA_LOW_START_CHECK;     //set FSM to transition to set SCL LOW
            break;
        case I2C_SDA_LOW_START_CHECK:               //1/2 BRG time has expired after SCL is low
            dObj->i2cState = I2C_SCL_LOW_START;           //set FSM to transition to set SCL_LOW
            break;
        case I2C_SCL_LOW_START:                     //1/2 BRG time has expired after I2C_SDA_LOW_START 
            PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, dObj->portSCL, dObj->pinSCL);
                                                    //set SCL to low
            dObj->i2cState =  I2C_SCL_LOW_START_CHECK;    //set FSM to check on SCL_LOW
            break;
        case I2C_SCL_LOW_START_CHECK:
            if (lBufferObj)
            {
                if ( (lBufferObj->operation == DRV_I2C_OP_WRITE_READ) &&
                       (lBufferObj->actualtransfersize > 0) &&
                         ( lBufferObj->readtransferSize > 0) )
                    lBufferObj->operation  = DRV_I2C_OP_READ;
                else
                    dObj->taskLObj = _DRV_I2C_QueuePop(dObj);
                    lBufferObj     = dObj->taskLObj;
            }
            else
            {
                dObj->taskLObj = _DRV_I2C_QueuePop(dObj);
                lBufferObj     = dObj->taskLObj;
            }
//            I2CSWData       =  *(lBufferObj->slaveaddress);
            dObj->I2CSWData       =  (lBufferObj->slaveaddresshighbyte);
            if (lBufferObj->operation == DRV_I2C_OP_READ)
                dObj->I2CSWData       |=  0x01;
            dObj->i2cState        = I2C_SCL_LOW_DATA_CHECK;
            break;
        case I2C_SDA_HIGH_RESTART:                      //1 BRG time has expired after sending data byte  
            PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA); 
                                                        //set SDA to high
            dObj->errorTimeOut = ERROR_TIMEOUT_COUNT;         
            dObj->i2cState    = I2C_SDA_HIGH_RESTART_CHECK;   //set FSM to set SCL high
            break;
        case I2C_SDA_HIGH_RESTART_CHECK:
            if (PLIB_PORTS_PinGet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA) == INPUT)
            {
            	dObj->i2cState    = I2C_SCL_HIGH_RESTART;
            }
            else
            {
                if  (!(dObj->errorTimeOut--))                 //decrement error counter                 
                {                    
                    lBufferObj->status = DRV_I2C_BUFFER_EVENT_ERROR;    //i2c error flag
                    PLIB_TMR_Stop(dObj->tmrSource);     //stop and clear Timer           
                    PLIB_TMR_Counter16BitClear(dObj->tmrSource);
                    dObj->errorTimeOut = ERROR_TIMEOUT_COUNT; //reset error counter
                }
                else
                {
                    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA);
                }
            }
            break;
        case I2C_SCL_HIGH_RESTART:                          //after 1 BRG time has expired after I2C_SDA_HIGH_RESTART
            PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSCL, dObj->pinSCL); 
                                                            //set SCL high
            dObj->errorTimeOut = ERROR_TIMEOUT_COUNT;    
            dObj->i2cState    = I2C_SCL_HIGH_RESTART_CHECK;       //set FSM to do procedure for normal START
            break;
        case I2C_SCL_HIGH_RESTART_CHECK:
            if (PLIB_PORTS_PinGet(PORTS_ID_0, dObj->portSCL, dObj->pinSCL) == INPUT)
            {
            	dObj->i2cState = I2C_SDA_LOW_START;
            }
            else
            {
                if  (!(dObj->errorTimeOut--))                 //decrement error counter                 
                {                    
                    lBufferObj->status = DRV_I2C_BUFFER_EVENT_ERROR;    //i2c error flag
                    PLIB_TMR_Stop(dObj->tmrSource);     //stop and clear Timer           
                    PLIB_TMR_Counter16BitClear(dObj->tmrSource);
                    dObj->errorTimeOut = ERROR_TIMEOUT_COUNT; //reset error counter
                }
                else
                {
                    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSCL, dObj->pinSCL);
                }
            }
            break;
        case I2C_SCL_LOW_DATA_CHECK:                //set LOW DATA CHECK
            PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, dObj->portSCL, dObj->pinSCL);			
                                                    //SCL pulled low immediately allowing Slave to change data here on read
            dObj->i2cState = I2C_SCL_LOW_DATA;                    
            break;
        case I2C_SCL_LOW_DATA:                      //state of low period of clock during data transfer
            if (dObj->I2CSWCounter > 1)                   //check until the low slow side of 7th clock and before rising edge of 8th clock
            {
                if ((bool) (dObj->I2CSWData & 0x80))      //if bit to be shifted out is 0
                    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA);   //then keep SDA as input
                else
                    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA);  //else keep SDA as output
            }
            else if (dObj->I2CSWCounter == 1)
            {
                dObj->_i2c_bit_written = 0;               //on the 9th clock clear the value of bit written
                if (lBufferObj->operation == DRV_I2C_OP_READ)
                {
                    if (dObj->I2CNACKOut == 0x00)         //set SDA to high allow slave to ACK or NACK
                    {
                      PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA);			  
                                                    //WRITE operation; On low side of 8th clock and before rising edge 9th clock
                	}   
                    else if (dObj->I2CNACKOut == 0x01)       
                    {
                        PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA);   //then keep SDA as input
                        dObj->I2CNACKOut     = 0x00;
                    }
                    else
                    {
                        PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA);   //then keep SDA as input
                    }
                }   
                else    
                {
                    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA);
            	}
            }
            if (dObj->I2CSWCounter == 0)                  //if CLK count is 0, ie after all the nine clocks have been sent
            {    
                /* if # of bytes to write is greater than 0 and operation is WRITE to slave */
//                if ( (lBufferObj->transferSize) && (I2CACKStatus == M_ACK) && 
//                        ((lBufferObj->operation == DRV_I2C_OP_WRITE) || (lBufferObj->operation == DRV_I2C_OP_WRITE_READ)) )
                if ( (lBufferObj->transferSize) && ((dObj->I2CACKStatus == M_ACK) || (lBufferObj->transmitForced)) && 
                        ((lBufferObj->operation == DRV_I2C_OP_WRITE) || (lBufferObj->operation == DRV_I2C_OP_WRITE_READ)) )
                {                                           //if # of bytes to be tx'ed > 0 && previous byte was ACKed then continue to write
                    dObj->I2CSWData   = *lBufferObj->txBuffer++;
                    dObj->i2cState    = I2C_SCL_LOW_DATA;
                    dObj->I2CSWCounter    = 9;
                    lBufferObj->actualtransfersize++;
                    lBufferObj->transferSize--;
                }      
                /* if the # of bytes to read is greater than 0 and operation is READ from slave */
                else if ( (lBufferObj->readtransferSize) && (lBufferObj->operation == DRV_I2C_OP_READ) )
                {                                           //if # of bytes to be rxed > 0, then perform read
                    dObj->I2CSWData   = 0xFF;
                    dObj->i2cState    = I2C_SCL_LOW_DATA;
                    dObj->I2CSWCounter    = 9;
                    lBufferObj->actualtransfersize++;
                    lBufferObj->readtransferSize--;
                    if (lBufferObj->readtransferSize == 0)  //if last byte being read, then send NACK
                    {
                        dObj->I2CNACKOut = 0x01;
                    }
                    else                                    //if more bytes are to be read then send ACK
                        dObj->I2CNACKOut = 0;                     
                }
                /* if # of bytes to write is 0 but # of bytes to read is greater than 0 then its an Write-Restart-Read Operation */
                else if ( (!lBufferObj->transferSize) && (lBufferObj->readtransferSize) && (lBufferObj->operation == DRV_I2C_OP_WRITE_READ) )
                {                                           //if write is complete and read is still pending
                    lBufferObj->operation = DRV_I2C_OP_WRITE_READ;
                    dObj->i2cState = I2C_SDA_HIGH_RESTART;                         
                    dObj->I2CSWCounter        = 9;
                }
                else
                {
                    dObj->i2cState    = I2C_SCL_SDA_LOW_STOP;
            	}
            }
            else
            {
                dObj->i2cState = I2C_SCL_HIGH_DATA;       //if clock count is not 0
                dObj->I2CSWCounter--;                     //decrement clock counter
                dObj->I2CSWData <<= 1;                    //shift data byte
            }
            break;    
        case I2C_SCL_HIGH_DATA:                     //1 BRG time has expired after SCL is low          
            if ( (dObj->_i2c_bit_written == 1) && (lBufferObj->operation == DRV_I2C_OP_WRITE) )  
            {
                /* check the value of bit that is just written onto the bus */
                if ((bool)(PLIB_PORTS_PinGet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA)) == (bool)dObj->_i2c_bit_written)  
                {                                       //then read SDA PORT back and check value is indeed a 1            
                    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSCL, dObj->pinSCL);  
                                                        //if so value written with collision and then set SCL high
                    dObj->i2cState = I2C_SCL_HIGH_DATA_CHECK; //set FSM to check for data validity 
                }
                else                                    //if data bit written is '1' 
                {                                       //but reading PORT back doesn't show '1' then its a BUS COLLISION
                    lBufferObj->status = DRV_I2C_BUFFER_EVENT_ERROR;    //i2c error flag
                    PLIB_TMR_Stop(dObj->tmrSource);     //stop and clear Timer           
                    PLIB_TMR_Counter16BitClear(dObj->tmrSource);
                    dObj->errorTimeOut = ERROR_TIMEOUT_COUNT; //reset error counter
                    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSCL, dObj->pinSCL);  
                                                        //set SCL high after setting error condition
                }
            }
            else
            {
                PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSCL, dObj->pinSCL);  
                                                        //set SCL high
                dObj->i2cState = I2C_SCL_HIGH_DATA_CHECK;     //set FSM to generate low side of clock 
            }
            break;
        case I2C_SCL_HIGH_DATA_CHECK:               //initial state where SCL is set to LOW
            if (PLIB_PORTS_PinGet(PORTS_ID_0, dObj->portSCL, dObj->pinSCL) == INPUT)
            {
                /* sample SDA line only after sending the address+RW=1 
                   lBufferObj->actualtransfersize is only during a read byte */
                if ((lBufferObj->operation == DRV_I2C_OP_READ) && (dObj->I2CSWCounter > 0) && (lBufferObj->actualtransfersize > 0))
                {                                       //READ operation; On high side of clocks from 1 to 8
                    dObj->I2CReadData <<= 1;                  //shift previously read data       
                    dObj->I2CReadData |= PLIB_PORTS_PinGet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA); 
                                                        //read SDA to get the bit send by slave
                }
                if (dObj->I2CSWCounter == 0)                  //at SCL high on the 9th clock
                {
                    dObj->I2CACKStatus = PLIB_PORTS_PinGet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA);
                                                        //read port value of SDA to check for ACK
                    if ( (lBufferObj->operation == DRV_I2C_OP_READ) && (lBufferObj->actualtransfersize > 0) )
                        *lBufferObj->rxBuffer++ = dObj->I2CReadData;
                }
                dObj->i2cState = I2C_SCL_LOW_DATA_CHECK;      //
                dObj->errorTimeOut = ERROR_TIMEOUT_COUNT;
            }
            else
            {                                           //if slave has CLOCK STRETCHED wait in the same state
                if  (!(dObj->errorTimeOut--))                 //decrement error counter                 
                {                    
                    lBufferObj->status = DRV_I2C_BUFFER_EVENT_ERROR;    //i2c error flag
                    PLIB_TMR_Stop(dObj->tmrSource);     //stop and clear Timer           
                    PLIB_TMR_Counter16BitClear(dObj->tmrSource);
                    dObj->errorTimeOut = ERROR_TIMEOUT_COUNT; //reset error counter
                }
            }
            break;
        case I2C_SCL_SDA_LOW_STOP:                  
            PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, dObj->portSCL, dObj->pinSCL);  //Keep SCL Low
            PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA);  //Keep SCL Low
            dObj->i2cState =  I2C_SCL_SDA_LOW_STOP_CHECK;
            break;
        case I2C_SCL_SDA_LOW_STOP_CHECK:
            dObj->i2cState = I2C_SCL_HIGH_STOP;
            break;
        case I2C_SCL_HIGH_STOP:                     //1 BRG time has expired after SCL and SDA low             
            PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSCL, dObj->pinSCL);   
                                                    //set SCL high
            dObj->i2cState    = I2C_SCL_HIGH_STOP_CHECK;  //set FSM state to generate HIGH SDA
            dObj->errorTimeOut = ERROR_TIMEOUT_COUNT; //reset error counter
            break;
        case I2C_SCL_HIGH_STOP_CHECK:
            if (PLIB_PORTS_PinGet(PORTS_ID_0, dObj->portSCL, dObj->pinSCL) == INPUT)
            {
            dObj->i2cState = I2C_SDA_HIGH_STOP;
            }
            else
            {
                if  (!(dObj->errorTimeOut--))                 //decrement error counter                 
                {                    
                    lBufferObj->status = DRV_I2C_BUFFER_EVENT_ERROR;    //i2c error flag
                    PLIB_TMR_Stop(dObj->tmrSource);     //stop and clear Timer           
                    PLIB_TMR_Counter16BitClear(dObj->tmrSource);
                    dObj->errorTimeOut = ERROR_TIMEOUT_COUNT; //reset error counter
                }
                else
                {
                    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSCL, dObj->pinSCL);
                }
            }
            break;
        case I2C_SDA_HIGH_STOP:                     //1 BRG time has expired after I2C_SCL_HIGH_STOP
            PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, dObj->portSDA, dObj->pinSDA);   
                                                    //set SDA to high
            dObj->i2cState    = I2C_SDA_HIGH_STOP_CHECK;     
            break;
        case I2C_SDA_HIGH_STOP_CHECK:
            //BB_I2C_SIG2_SET();
            if( lBufferObj->transferSize )
            {
                _DRV_I2C_CLIENT_OBJ(lBufferObj, status) = DRV_I2C_BUFFER_EVENT_ERROR;

            }
            else
            {
                _DRV_I2C_CLIENT_OBJ(lBufferObj, status) = DRV_I2C_BUFFER_EVENT_COMPLETE;

            } 
            lBufferObj->inUse = false;
            
            /* Have a check here because DRV_I2C_ClientSetup function call is optional */
            if ( _DRV_I2C_CLIENT_OBJ(((DRV_I2C_CLIENT_OBJ *)lBufferObj->clientHandle), callback) != NULL )
            {
                dObj->interruptNestingCount++;
                
                /* Give an indication to the higher layer upon successful transmission */
                _DRV_I2C_CLIENT_OBJ(((DRV_I2C_CLIENT_OBJ *)lBufferObj->clientHandle), callback)
                        ( _DRV_I2C_CLIENT_OBJ(lBufferObj, status), (DRV_I2C_BUFFER_HANDLE)lBufferObj, 0x00 );
                
                dObj->interruptNestingCount--;
            }
//            if ( (dObj->queueHead == NULL) &&  (lBufferObj->status == DRV_I2C_BUFFER_EVENT_COMPLETE) )        
            if ( (lBufferObj->status == DRV_I2C_BUFFER_EVENT_COMPLETE) || (lBufferObj->status == DRV_I2C_BUFFER_EVENT_ERROR) )
            {                
                _DRV_I2C_Advance_Queue(dObj);
                
                if ((_DRV_I2C_IsQueueEmpty(dObj) == true))
                {
                    PLIB_TMR_Stop(dObj->tmrSource);     //stop and clear Timer          
                    PLIB_TMR_Counter16BitClear(dObj->tmrSource);
                    Nop();
                }
                else
                {
                    dObj->i2cState = I2C_SDA_LOW_START;
                    dObj->I2CSWCounter = 9;
                }
            }
            break;
        default:
            break;
    }
       
}



