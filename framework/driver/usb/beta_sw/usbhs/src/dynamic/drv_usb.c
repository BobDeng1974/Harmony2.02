/*******************************************************************************
  USB Device Driver Core Routines

  Company:
    Microchip Technology Inc.

  File Name:
    drv_usb.c

  Summary:
    USB Device Driver Dynamic Implementation of Core routines

  Description:
    The USB device driver provides a simple interface to manage the USB
    modules on Microchip microcontrollers.  This file Implements the core
    interface routines for the USB driver.

    While building the driver from source, ALWAYS use this file in the build.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip  Technology  Inc.   All  rights  reserved.

Microchip licenses to  you  the  right  to  use,  modify,  copy  and  distribute
Software only when embedded on a Microchip  microcontroller  or  digital  signal
controller  that  is  integrated  into  your  product  or  third  party  product
(pursuant to the  sublicense  terms  in  the  accompanying  license  agreement).

You should refer  to  the  license  agreement  accompanying  this  Software  for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS  WITHOUT  WARRANTY  OF  ANY  KIND,
EITHER EXPRESS  OR  IMPLIED,  INCLUDING  WITHOUT  LIMITATION,  ANY  WARRANTY  OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A  PARTICULAR  PURPOSE.
IN NO EVENT SHALL MICROCHIP OR  ITS  LICENSORS  BE  LIABLE  OR  OBLIGATED  UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,  BREACH  OF  WARRANTY,  OR
OTHER LEGAL  EQUITABLE  THEORY  ANY  DIRECT  OR  INDIRECT  DAMAGES  OR  EXPENSES
INCLUDING BUT NOT LIMITED TO ANY  INCIDENTAL,  SPECIAL,  INDIRECT,  PUNITIVE  OR
CONSEQUENTIAL DAMAGES, LOST  PROFITS  OR  LOST  DATA,  COST  OF  PROCUREMENT  OF
SUBSTITUTE  GOODS,  TECHNOLOGY,  SERVICES,  OR  ANY  CLAIMS  BY  THIRD   PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE  THEREOF),  OR  OTHER  SIMILAR  COSTS.
*******************************************************************************/
//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************

#include "driver/usb/beta_sw/usbhs/src/drv_usb_local.h"
#include "peripheral/ports/plib_ports.h"

/************************************
 * Driver instance object
 ***********************************/

DRV_USB_OBJ gDrvUSBObj[DRV_USB_INSTANCES_NUMBER];

/*********************************
 * Array of endpoint objects. Two 
 * objects per endpoint 
 ********************************/

DRV_USB_DEVICE_ENDPOINT_OBJ gDrvUSBEndpoints [DRV_USB_INSTANCES_NUMBER]
                                            [DRV_USB_ENDPOINTS_NUMBER * 2];

// *****************************************************************************
/* Function:
      SYS_MODULE_OBJ DRV_USB_Initialize( const SYS_MODULE_INDEX index,
                                         const SYS_MODULE_INIT * const init )

  Summary:
    Dynamic impementation of DRV_USB_Initialize system interface function.

  Description:
    This is the dynamic impementation of DRV_USB_Initialize system interface
    function. Function performs the following task:
    - Initializes the neccessary USB module as per the instance init data
    - Updates internal data structure for the particular USB instance
    - Returns the USB instance value as a handle to the system

  Remarks:
    See drv_usb.h for usage information.
*/

SYS_MODULE_OBJ DRV_USB_Initialize 
( 
    const SYS_MODULE_INDEX  drvIndex,
    const SYS_MODULE_INIT * const init
)
{
    /* Start of local variables */
    DRV_USB_OBJ * drvObj;
    USBHS_MODULE_ID  usbID;
    DRV_USB_INIT * usbInit;
    /* End of local variables */

    if(gDrvUSBObj[drvIndex].inUse == true)
    {
        /* Cannot initialize an object that is 
         * already in use. */

        SYS_DEBUG(SYS_ERROR_INFO, "Instance already in use");
        return SYS_MODULE_OBJ_INVALID;
    }

    if( drvIndex >= DRV_USB_INSTANCES_NUMBER)
    {
        SYS_DEBUG(SYS_ERROR_INFO,"Increase the value of DRV_USB_INSTANCES_NUMBER");
        return SYS_MODULE_OBJ_INVALID;
    }

    usbInit     = (DRV_USB_INIT *) init;
    usbID       = usbInit->usbID;

    drvObj = &gDrvUSBObj[drvIndex];

    OSAL_ASSERT(if(OSAL_MUTEX_Create(&drvObj->mutexID)
                == OSAL_RESULT_TRUE), "Mutex create failed");

    /* Populate the driver object with
     * the required data */

    drvObj->inUse   = true;
    drvObj->status  = SYS_STATUS_BUSY; 
    drvObj->usbID   = usbID;            
    drvObj->operationMode  = usbInit->operationMode; 
    drvObj->operationSpeed = usbInit->operationSpeed;

    /* Assign the endpoint table */
    drvObj->endpointTable = &gDrvUSBEndpoints[drvIndex][0];
    drvObj->interruptSource  = usbInit->interruptSource;

    drvObj->isOpened = false;
    drvObj->pEventCallBack = NULL;

    drvObj->interruptSourceUSBDma = usbInit->interruptSourceUSBDma;


    if(drvObj->operationMode == DRV_USB_OPMODE_HOST)
    {
        /* For Host the ID pin needs to be pulle down */
        PLIB_PORTS_ChangeNoticePullDownPerPortEnable( PORTS_ID_0,
                               PORT_CHANNEL_F, PORTS_BIT_POS_3 );
    }
    
    /* Set the starting VBUS level. */
    drvObj->vbusLevel = USBHS_VBUS_SESSION_END;
    drvObj->sessionInvalidEventSent = false;

    /* Set the state to indicate that the delay will be started */
    drvObj->state = DRV_USB_TASK_STATE_STARTING_DELAY;
    
    return ((SYS_MODULE_OBJ)drvIndex); 

} /* end of DRV_USB_Initialize() */

// *****************************************************************************
/* Function:
      void DRV_USB_Tasks(SYS_MODULE_OBJ object)

  Summary:
    Dynamic impementation of DRV_USB_Tasks system interface function.

  Description:
    This is the dynamic impementation of DRV_USB_Tasks system interface
    function.

  Remarks:
    See drv_usb.h for usage information.
*/

void DRV_USB_Tasks(SYS_MODULE_OBJ object)
{
    /* Start of local variables */
    DRV_USB_OBJ * hDriver; 
    hDriver = &gDrvUSBObj[object];
    USBHS_MODULE_ID usbID = hDriver->usbID;
    /* End of local variables */

    if(hDriver->status <= SYS_STATUS_UNINITIALIZED)
    {
        /* Driver is not intialized */
        return;
    }

    /* Check the tasks state and maintain */
    switch(hDriver->state)
    {
        case DRV_USB_TASK_STATE_STARTING_DELAY:

            /* Start the delay here */
            hDriver->timerHandle = SYS_TMR_DelayMS(3000);
            if(hDriver->timerHandle != SYS_TMR_HANDLE_INVALID)
            {
                /* Reset the PHY. This is a workaround
                 * for an errata */
                PLIB_USBHS_SoftResetEnable(usbID);

                /* Delay has started. Move to the next state */
                hDriver->state = DRV_USB_TASK_STATE_WAITING_FOR_DELAY_COMPLETE;
            }

            break;

        case DRV_USB_TASK_STATE_WAITING_FOR_DELAY_COMPLETE:

            /* Check if the delay is complete */
            if(SYS_TMR_DelayStatusGet(hDriver->timerHandle)) 
            {
                /* This means the delay is complete. Clear the Soft Reset  */
                PLIB_USBHS_SoftResetDisable(usbID);

                /* Setup the USB Module based on the selected
                 * mode */

                switch(hDriver->operationMode)
                {
                    case DRV_USB_OPMODE_DEVICE:
                        _DRV_USB_DEVICE_INIT(hDriver, object);
                        break;
                    case DRV_USB_OPMODE_HOST:
                        _DRV_USB_HOST_INIT(hDriver, object);
                        break;
                    case DRV_USB_OPMODE_OTG:
                        break;
                    default:
                        SYS_DEBUG(SYS_ERROR_INFO, "What mode are you trying?");
                        break;
                }

                /* Clear and enable the interrupts */
                _DRV_USB_InterruptSourceClear(hDriver->interruptSource);
                _DRV_USB_InterruptSourceEnable(hDriver->interruptSource);
                
                _DRV_USB_InterruptSourceClear(hDriver->interruptSourceUSBDma);
                _DRV_USB_InterruptSourceEnable(hDriver->interruptSourceUSBDma);


                /* Indicate that the object is ready and change the state to running
                 * */

                hDriver->status = SYS_STATUS_READY;
                hDriver->state = DRV_USB_TASK_STATE_RUNNING;
            }

            break;

        case DRV_USB_TASK_STATE_RUNNING:
            /* The module is in a running state. In the polling mode the 
             * driver ISR tasks and DMA ISR tasks are called here. We also
             * check for the VBUS level and generate events if a client 
             * event handler is registered. */

            if(hDriver->pEventCallBack != NULL && hDriver->operationMode == DRV_USB_OPMODE_DEVICE)
            {
                /* We have a valid client call back function. Check if
                 VBUS level has changed */
                USBHS_VBUS_LEVEL vbusLevel = PLIB_USBHS_VBUSLevelGet(hDriver->usbID);
                if(hDriver->vbusLevel != vbusLevel)
                {
                    /* This means there was a change in the level */
                    if(vbusLevel == USBHS_VBUS_VALID)
                    {
                        /* We have a valid VBUS level */
                        hDriver->pEventCallBack(hDriver->hClientArg, DRV_USB_EVENT_DEVICE_SESSION_VALID, NULL);
                        
                        /* We should be ready for send session invalid event
                         * to the application when they happen.*/
                        hDriver->sessionInvalidEventSent = false;

                    }
                    else
                    {
                        /* Any thing other than valid is considered invalid.
                         * This event may occur multiple times, but we send
                         * it only once. */
                        if(!hDriver->sessionInvalidEventSent)
                        {
                            hDriver->pEventCallBack(hDriver->hClientArg, DRV_USB_EVENT_DEVICE_SESSION_INVALID, NULL);
                            hDriver->sessionInvalidEventSent = true;
                        }
                    }

                    hDriver->vbusLevel = vbusLevel;
                }
            }
            _DRV_USB_Tasks_ISR(object);
            _DRV_USB_Tasks_ISR_USBDMA(object);
            break;
    }
}/* end of DRV_USB_Tasks() */

// *****************************************************************************
/* Function:
    void DRV_USB_Deinitialize( const SYS_MODULE_OBJ object )

  Summary:
    Dynamic impementation of DRV_USB_Deinitialize system interface function.

  Description:
    This is the dynamic impementation of DRV_USB_Deinitialize system interface
    function.

  Remarks:
    See drv_usb.h for usage information.
*/

void DRV_USB_Deinitialize 
( 
    const SYS_MODULE_INDEX  object
)
{
    /* Start of local variables */
    DRV_USB_OBJ * drvObj;
    USBHS_MODULE_ID  usbID;
    bool returnValue = false;
    /* End of local variables */

    if(object == SYS_MODULE_OBJ_INVALID)
    {
	/* Invalid object */
        SYS_DEBUG(SYS_ERROR_INFO, "Invalid object");
	return ;
    }
    
    if( object >= DRV_USB_INSTANCES_NUMBER)
    {
        SYS_DEBUG(SYS_ERROR_INFO,"Invalid driver Index");
        return  ;
    }

    if(gDrvUSBObj[object].inUse == false)
    {
        /* Cannot deinitialize an object that is 
         * not already in use. */
        SYS_DEBUG(SYS_ERROR_INFO, "Instance not in use");
        return  ;
    }

    drvObj = &gDrvUSBObj[object]; 
    usbID  = drvObj->usbID;

    /* Populate the driver object with
     * the required data */

    drvObj->inUse   = false;
    drvObj->status  = SYS_STATUS_UNINITIALIZED; 

    /* Clear and disable the interrupts */

    /* Assigning to a value has been implemented to remove compiler
       warning in polling mode.
     */
    returnValue = _DRV_USB_InterruptSourceDisable(drvObj->interruptSource);
    _DRV_USB_InterruptSourceClear(drvObj->interruptSource);

    drvObj->isOpened = false;
    drvObj->pEventCallBack = NULL;

    /* Delete the mutex */
    OSAL_ASSERT(if(OSAL_MUTEX_Delete(&drvObj->mutexID)
                == OSAL_RESULT_TRUE), "Mutex delete failed");

    return;

} /* end of DRV_USB_Deinitialize() */

// *****************************************************************************
/* Function:
    SYS_STATUS DRV_USB_Status( const SYS_MODULE_OBJ object )

  Summary:
    Dynamic impementation of DRV_USB_Status system interface function.

  Description:
    This is the dynamic impementation of DRV_USB_Status system interface
    function.

  Remarks:
    See drv_usb.h for usage information.
*/

SYS_STATUS DRV_USB_Status ( SYS_MODULE_OBJ object )
{
    if(object == SYS_MODULE_OBJ_INVALID)
    {
        SYS_DEBUG(SYS_ERROR_INFO, "System Module Object is invalid");
        return SYS_STATUS_ERROR;
    }
    
    /* Return the status of the driver object */
    return(gDrvUSBObj[object].status);
}/* end of DRV_USB_Status() */


DRV_HANDLE DRV_USB_Open
(
    const SYS_MODULE_INDEX iDriver,
    const DRV_IO_INTENT    ioIntent 
)
{
    /* Start of local variables */
    DRV_USB_OBJ * drvObj;
    /* End of local variables */

    /* The iDriver value should be valid. It should be
     * less the number of driver object instances. 
     */

    if(iDriver >= DRV_USB_INSTANCES_NUMBER)
    {
        SYS_DEBUG(SYS_ERROR_INFO, "Bad Driver Index");
        return DRV_HANDLE_INVALID;
    }

    drvObj = &gDrvUSBObj[iDriver];

    if(drvObj->status != SYS_STATUS_READY)
    {
        /* The USB module should be ready */

        SYS_DEBUG(SYS_ERROR_INFO, "Was the driver initialized?");
        return DRV_HANDLE_INVALID;
    }

    if(ioIntent != (DRV_IO_INTENT_EXCLUSIVE|DRV_IO_INTENT_NONBLOCKING
                |DRV_IO_INTENT_READWRITE))
    {
        /* The driver only supports this mode */

        SYS_DEBUG(SYS_ERROR_INFO, "IO intent mode not supported");
        return DRV_HANDLE_INVALID;
    }

    if(drvObj->isOpened)
    {
        /* Driver supports exclusive open only */
        SYS_DEBUG(SYS_ERROR_INFO, "Driver already opened once. Cannot open again");
        return DRV_HANDLE_INVALID;
    }
  
    /* Clear prior value */
    drvObj->pEventCallBack = NULL;

    /* Store the handle in the driver object
     * client table and update the number of
     * clients*/

    drvObj->isOpened = true;

    /* Return the client object */

    return ( ( DRV_HANDLE ) drvObj );
}/* end of DRV_USB_Open() */

// *****************************************************************************
/* Function:
    void DRV_USB_Close( DRV_HANDLE client )

  Summary:
    Dynamic impementation of DRV_USB_Close client interface function.

  Description:
    This is the dynamic impementation of DRV_USB_Close client interface
    function.

  Remarks:
    See drv_usb.h for usage information.
*/

void DRV_USB_Close( DRV_HANDLE client )
{
    /* Start of local variables */
    DRV_USB_OBJ * hDriver;
    /* end of local variables */

    if(client == DRV_HANDLE_INVALID)
    {
        SYS_DEBUG(SYS_ERROR_INFO, "Bad Client Handle");
        return;
    }

    hDriver = (DRV_USB_OBJ *) client;
    
    if(!(hDriver->isOpened))
    {
        SYS_DEBUG(SYS_ERROR_INFO, "Invalid client handle");
        return;
    }
    /* Give back the client */
    hDriver->isOpened = false;
    hDriver->pEventCallBack = NULL;
}/* end of DRV_USB_Close() */

// *****************************************************************************
/* Function:
    DRV_HANDLE DRV_USB_Tasks_ISR( SYS_MODULE_OBJ object )

  Summary:
    Dynamic impementation of DRV_USB_Tasks_ISR system interface function.

  Description:
    This is the dynamic impementation of DRV_USB_Tasks_ISR system interface
    function.

  Remarks:
    See drv_usb.h for usage information.
*/

void DRV_USB_Tasks_ISR( SYS_MODULE_OBJ object )
{
    /* Start of local variables */
    DRV_USB_OBJ * 	hDriver;
    /* end of local variables */

    hDriver = &gDrvUSBObj[object];
    hDriver->isInInterruptContext = true;

	switch(hDriver->operationMode)
	{
        case DRV_USB_OPMODE_DEVICE:
            _DRV_USB_DEVICE_TASKS_ISR(hDriver);
            break;
        case DRV_USB_OPMODE_HOST:
            _DRV_USB_HOST_TASKS_ISR(hDriver);
            break;
        case DRV_USB_OPMODE_OTG:
            break;
        default:
            SYS_DEBUG(SYS_ERROR_INFO, "What mode are you trying?");
            break;
	}	
  
    /* Clear the interrupt */
    _DRV_USB_InterruptSourceClear(hDriver->interruptSource);
    hDriver->isInInterruptContext = false;
}/* end of DRV_USB_Tasks_ISR() */

void DRV_USB_Tasks_ISR_USBDMA
(
    SYS_MODULE_OBJ object
)
{
    /* Start of local variables */
    DRV_USB_OBJ * 	hDriver;
    /* end of local variables */

    hDriver = &gDrvUSBObj[object];
    hDriver->isInInterruptContextUSBDMA = true;

	switch(hDriver->operationMode)
	{
        case DRV_USB_OPMODE_DEVICE:
            _DRV_USB_DEVICE_TASKS_ISR_USBDMA(hDriver);
            break;
        case DRV_USB_OPMODE_HOST:
            _DRV_USB_HOST_TASKS_ISR_USBDMA(hDriver);
            break;
        case DRV_USB_OPMODE_OTG:
            break;
        default:
            SYS_DEBUG(SYS_ERROR_INFO, "What mode are you trying?");
            break;
	}
        
    /* Clear the interrupt */
    hDriver->isInInterruptContextUSBDMA = false;
    _DRV_USB_InterruptSourceClear(hDriver->interruptSourceUSBDma);

}/* end of DRV_USB_Tasks_ISR()*/


void DRV_USB_ResumeControl(DRV_HANDLE hClient, bool control)
{
    /* Start of local variables */
    DRV_USB_OBJ * hDriver;
    USBHS_MODULE_ID usbID;
    /* end of local variables */

    if((hClient == DRV_HANDLE_INVALID))
    {
        SYS_DEBUG(SYS_ERROR_INFO, "Invalid client");
    }

    hDriver = (DRV_USB_OBJ *)hClient;
    usbID = hDriver->usbID;

    if(control)
    {
        PLIB_USBHS_ResumeEnable(usbID);
    }
    else
    {
        PLIB_USBHS_ResumeDisable(usbID);
    }
}/* end of DRV_USB_ResumeControl() */

// *****************************************************************************
/* Function:
    bool DRV_USB_HOST_Resume(DRV_HANDLE handle)

  Summary:
    Dynamic implementation of DRV_USB_HOST_Resume
    client interface function.

  Description:
    This is the dynamic implementation of DRV_USB_HOST_Resume client
    interface function. Function resumes a suspended BUS.

  Remarks:
    See drv_usb.h for usage information.
*/

bool DRV_USB_HOST_Resume
(
    DRV_HANDLE handle
)
{
    /* Start of local variable */
    DRV_USB_OBJ * pusbdrvObj = (DRV_USB_OBJ *)NULL;
    bool returnValue = false;
    /* End of local variable */
    
    /* Check if the handle is valid */
    if((handle == DRV_HANDLE_INVALID))
    {
        SYS_DEBUG(SYS_ERROR_INFO, "Bad Client or client closed");
    }
    else
    {
        pusbdrvObj = (DRV_USB_OBJ *)handle;

        PLIB_USBHS_ResumeEnable(pusbdrvObj->usbID);
        returnValue = true;
    }
    return returnValue;

}/* end of DRV_USB_HOST_Resume() */

// *****************************************************************************
/* Function:
    bool DRV_USB_HOST_Suspend(DRV_HANDLE handle)

  Summary:
    Dynamic implementation of DRV_USB_HOST_Suspend
    client interface function.

  Description:
    This is the dynamic implementation of DRV_USB_HOST_Suspend client
    interface function. Function suspends USB BUS.

  Remarks:
    See drv_usb.h for usage information.
*/

bool DRV_USB_HOST_Suspend
(
    DRV_HANDLE handle
)
{	
    /* Start of local variable */
    DRV_USB_OBJ * pusbdrvObj = (DRV_USB_OBJ *)NULL;
    bool returnValue = false;
    /* End of local variable */

    /* Check if the handle is valid */
    if((handle == DRV_HANDLE_INVALID))
    {
        SYS_DEBUG(SYS_ERROR_INFO, "Bad Client or client closed");
    }
    else
    {
        pusbdrvObj = (DRV_USB_OBJ *)handle;

        /* Suspend the bus */
        PLIB_USBHS_SuspendEnable(pusbdrvObj->usbID);
        returnValue = true;
    }
    return returnValue;

}/* end of DRV_USB_HOST_Suspend() */

// *****************************************************************************
/* Function:
    void DRV_USB_ClientEventCallBackSet(DRV_HANDLE   handle,
                                        uintptr_t    hReferenceData,
                                        DRV_USB_EVENT_CALLBACK eventCallBack)

  Summary:
    Dynamic impementation of DRV_USB_ClientEventCallBackSet client
    interface function.

  Description:
    This is the dynamic impementation of DRV_USB_ClientEventCallBackSet
    client interface function.

  Remarks:
    See drv_usb.h for usage information.
*/

void DRV_USB_ClientEventCallBackSet
( 
    DRV_HANDLE   client          ,
    uintptr_t    hReferenceData ,
    DRV_USB_EVENT_CALLBACK eventCallBack 
)
{
    /* Start of local variable */
    DRV_USB_OBJ * pusbDrvObj;
    /* end of local variable */
    
    if(client == DRV_HANDLE_INVALID)
    {
        SYS_DEBUG(SYS_ERROR_INFO, "Bad Client Handle");
        return;
    }

    pusbDrvObj = (DRV_USB_OBJ *) client;
    
    if(!pusbDrvObj->isOpened)
    {
        SYS_DEBUG(SYS_ERROR_INFO, "Invalid client handle");
        return;
    }

    /* Assign event call back and reference data */
    pusbDrvObj->hClientArg = hReferenceData;
    pusbDrvObj->pEventCallBack = eventCallBack;
   
    return;
    
}/* end of DRV_USB_ClientEventCallBackSet() */
