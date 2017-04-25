/*******************************************************************************
  USB Device Driver Definition

  Company:
    Microchip Technology Inc.

  File Name:
    drv_usb_host.c

  Summary:
    USB Device Driver Implementation

  Description:
    This file implements the Host mode operation of the USB Driver. This file
    should be included in the application if USB Host mode operation is desired.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute Software
only when embedded on a Microchip microcontroller or digital  signal  controller
that is integrated into your product or third party  product  (pursuant  to  the
sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
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

#include "system_config.h"
#include "driver/usb/beta_sw/drv_usb.h"
#include "driver/usb/beta_sw/usbfs/src/drv_usb_local.h"

/*****************************************************
 * Global Variable used as Pool of pipe objects 
 * that is used by all driver instances.
 *****************************************************/
DRV_USB_HOST_PIPE_OBJ gDrvUSBHostPipeObj[DRV_USB_HOST_PIPES_NUMBER];

/******************************************************************************
 * This matrix provides a mapping of the amount of bandwidth left in a frame for
 * a given transfer size. The number in the matrix is the percentage of
 * bandwidth consumer and the index of each entry is the Log2(N) of data payload
 * size. The first entry is for payload size 1, the second for payload size of
 * 2, the third for payload size of 8 and so on.
 ******************************************************************************/
const unsigned int gDrvUSBFSTableBW[4][11] =
{{3, 3, 3, 4, 4, 5, 7, 0, 0,  0,  0},       /* Control Transfers    */
{1, 1, 1, 1, 2, 3, 5, 0, 0,  0,  0},        /* Interrupt Transfers  */
{1, 1, 1, 1, 2, 3, 5, 0, 0,  0,  0},        /* Bulk Transfer        */
{1, 1, 1, 1, 2, 3, 5, 9, 18, 35, 69}};      /* Isochronous Transfer */

const unsigned int gDrvUSBLSTableBW[2][4] ={{26, 27, 28,30},     // control
{11, 11, 12, 14}};   // interrupt

// *****************************************************************************
/* Function:
    void _DRV_USB_SendTokenToAddress
    (
        USB_MODULE_ID usbID,
        uint8_t address,
        USB_PID pid,
        uint8_t endpoint,
        bool isLowSpeed
    )

  Summary:
    Dynamic implementation of _DRV_USB_SendTokenToAddress function

  Description:
    Function programs USB token register with required information for sending
    USB token data

  Remarks:
    This is a local function and should not be called directly by the
    application.
*/

void _DRV_USB_SendTokenToAddress
(
    USB_MODULE_ID usbID,
    uint8_t address,
    USB_PID pid,
    uint8_t endpoint,
    bool isLowSpeed
)
{
    /* Created a function call for this because PLIB function are 
     * inline and this function is being called at several locations */

    PLIB_USB_TokenSend(usbID, pid, endpoint, address, isLowSpeed);

}/* end of _DRV_USB_SendTokenToAddress() */

// *****************************************************************************
/* Function:
    void _DRV_USB_HOST_Initialize
    (
        DRV_USB_OBJ * const pUSBDrvObj,
        const SYS_MODULE_INDEX index
    )

  Summary:
    Dynamic implementation of _DRV_USB_HOST_Initialize function when controller
    is in Host mode.

  Description:
    Function performs the following tasks:
      - Informs the USB module with SOF threshold in bit times
      - Enables VBUS power and initializes the module in HOST mode
      - Resets the BDT table data structure with init value
      - Configures EP0 register for the specific USB module
      - Enables the USB attach interrupt

  Remarks:
    This is a local function and should not be called directly by the
    application.
*/

void _DRV_USB_HOST_Initialize
(
    DRV_USB_OBJ * const pUSBDrvObj,
    const SYS_MODULE_INDEX index
)
{
    /* Start of local variable */
    uint8_t bdtEntryindex = 0;
    /* End of local variable */

    /* Set the SOF threshold value in bit times */
    PLIB_USB_SOFThresholdSet(pUSBDrvObj->usbID, 0x4A);

    /* Enable the VBUSON bit in the OTGCON register. Even if the actual VBUSON
     * pin is not under USB module control, this bit must be set for host
     * operation */
    PLIB_USB_OTG_VBusPowerOn(pUSBDrvObj->usbID);

    /* Select the host mode of operation */
    PLIB_USB_OperatingModeSelect(pUSBDrvObj->usbID, USB_OPMODE_HOST);

    /* Clear up the endpoint 0 BDT entries. Note that host performs all
     * transfers through endpoint 0. */
    for(bdtEntryindex = 0; bdtEntryindex < 4; bdtEntryindex ++)
    {
        /* A full duplex endpoint has 4
         * entries, 2 per EP direction */
        pUSBDrvObj->pBDT[bdtEntryindex].word[0] = 0;
        pUSBDrvObj->pBDT[bdtEntryindex].word[1] = 0;
    }

    /* Initialize the odd even buffer pointers */
    pUSBDrvObj->ep0TxPingPong = USB_BUFFER_EVEN;
    pUSBDrvObj->ep0RxPingPong = USB_BUFFER_EVEN;

    /* Configure endpoint 0 control register for Host operation. */
    PLIB_USB_EP0HostSetup(pUSBDrvObj->usbID);

    

    /* Clear and enable the interrupts */
    _DRV_USB_InterruptSourceClear(pUSBDrvObj->interruptSource);
    _DRV_USB_InterruptSourceEnable(pUSBDrvObj->interruptSource);

}/* end of _DRV_USB_HOST_Initialize() */

// *****************************************************************************
/* Function:
    USB_ERROR DRV_USB_HOST_IRPSubmit
    (
        DRV_USB_HOST_PIPE_HANDLE  hPipe,
        USB_HOST_IRP * pinputIRP
    )

  Summary:
    Dynamic implementation of DRV_USB_HOST_IRPSubmit function when controller
    is in Host mode.

  Description:
    Function performs the following tasks:
      - Validates the pipe object for which IRP has been submitted
      - Adds the IRP to the pipe object data structure

  Remarks:
    See drv_usb.h for usage information.
*/

USB_ERROR DRV_USB_HOST_IRPSubmit
(
    DRV_USB_HOST_PIPE_HANDLE  hPipe,
    USB_HOST_IRP * pInputIRP
)
{
    /* Start of local variables */
    USB_HOST_IRP_LOCAL * pIRPIterator = (USB_HOST_IRP_LOCAL *)NULL;
    bool interruptWasEnabled          = false;
    USB_HOST_IRP_LOCAL * pIRP         = (USB_HOST_IRP_LOCAL *)pInputIRP;
    DRV_USB_HOST_PIPE_OBJ * pPipe     = (DRV_USB_HOST_PIPE_OBJ *)hPipe;
    DRV_USB_OBJ * pUSBDrvObj          = (DRV_USB_OBJ *)NULL;
    /* End of local variables */
    
    pUSBDrvObj = (DRV_USB_OBJ *)(pPipe->hClient);

    /* Assign owner pipe */
    pIRP->pipe = hPipe;

    /* Clear up any temporary state */
    pIRP->tempState = 0;

    /* Control transfer IRPs have to be implemented in states. These sub states
     * are maintained in the tempState member of the IRP. A control transfer IRP
     * must start with the SETUP stage */

    if(pPipe->pipeType == USB_TRANSFER_TYPE_CONTROL)
    {
        /* Then we setup the IRP for setup stage */
        pIRP->tempState = DRV_USB_HOST_IRP_STATE_SETUP_STAGE;
    }

    pIRP->status = USB_HOST_IRP_STATUS_PENDING;

    /* Add the IRP to the pipe. We need to disable the USB interrupt here
     * because the USB interrupt updates the pipe structure asynchronously. */

    if(!(pUSBDrvObj->inInterruptContext))
    {
        /* The mutex protects the interrupt state from manipulation from other
         * thread that want to submit IRPs. If another thread reaches this point
         * it will block waiting on this mutex. Additionally the mutex should be
         * grabbed only if this function is not executing in an interrupt
         * context. A thread can submit an IRP in an event handler is invoked
         * from the ISR. */
        if(OSAL_MUTEX_Lock(&pUSBDrvObj->mutexID, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex lock failed");
            return USB_ERROR_OSAL_FUNCTION;
        }

        /* Disable the interrupt */
        interruptWasEnabled = _DRV_USB_InterruptSourceDisable(pUSBDrvObj->interruptSource);
    }
    
    /* Add the IRP to the queue */
    if(pPipe->irpQueueHead == NULL)
    {
        /* This means that there are no IRPs on this pipe. We can add this IRP
         * directly */

        pIRP->next = NULL;
        pPipe->irpQueueHead = pIRP;
    }
    else
    {
        /* The pipe queue is not empty. Add the IRP to the last IRP in the pipe
         * queue */

        pIRPIterator = pPipe->irpQueueHead;

        /* Find the last IRP in the linked list*/
        while(pIRPIterator->next != NULL)
        {
            pIRPIterator = pIRPIterator->next;
        }

        /* Add the item to the last irp in the linked list */
        pIRPIterator->next = pIRP;
    }

    /* Initialize the hidden members */
    pIRP->next = NULL;
    pIRP->completedBytes = 0;
    pIRP->tempSize = 0;

    if(!(pUSBDrvObj->inInterruptContext))
    {
        /* While exiting the routine, restore the interrupt context and then
         * release the mutex. Any thread that is blocked on this mutex will be
         * able to now manipulate the interrupt and submit the IRP */

        if(interruptWasEnabled)
        {
            _DRV_USB_InterruptSourceEnable(pUSBDrvObj->interruptSource);
        }

        if(OSAL_MUTEX_Unlock(&pUSBDrvObj->mutexID) != OSAL_RESULT_TRUE)
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex unlock failed");
        }
    }

    return USB_ERROR_NONE;

}/* end of DRV_USB_HOST_IRPSubmit() */

// *****************************************************************************
/* Function:
    void DRV_USB_HOST_IRPCancel(USB_HOST_IRP * pinputIRP)

  Summary:
    Dynamic implementation of DRV_USB_HOST_IRPCancel function when controller
    is in Host mode.

  Description:
    Function cancels and IRP

  Remarks:
    See drv_usb.h for usage information.
*/

void DRV_USB_HOST_IRPCancel(USB_HOST_IRP * pInputIRP)
{
    /* Start of local variable */
    USB_HOST_IRP_LOCAL * pIRP          = (USB_HOST_IRP_LOCAL *) pInputIRP;
    DRV_USB_OBJ * pUSBDrvObj           = (DRV_USB_OBJ *)NULL;
    DRV_USB_HOST_PIPE_OBJ * pPipe      = (DRV_USB_HOST_PIPE_OBJ *)NULL;
    USB_HOST_IRP_LOCAL * pIteratorIRP  = (USB_HOST_IRP_LOCAL *)NULL;
    bool interruptWasEnabled           = false;
    bool irpCancel                     = false;
    /* End of local variable */

    if((pIRP == NULL) || (pIRP->pipe == DRV_USB_HOST_PIPE_HANDLE_INVALID))
    {
        /* Pipe or IRP is not valid */
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Invalid pipe");
    }
    else if(pIRP->status <= USB_HOST_IRP_STATUS_COMPLETED_SHORT)
    {
        /* IRP is already completed and currently not in any pipe */
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "IRP is not pending or in progress");
    }
    else
    {
        pPipe = (DRV_USB_HOST_PIPE_OBJ *)pIRP->pipe;
        pUSBDrvObj = (DRV_USB_OBJ *) pPipe->hClient;

        if(!(pUSBDrvObj->inInterruptContext))
        {
            /* Disable the interrupts to prevent asynchronous manipulation of
             * this IRP. In a multi-thread application, this operation should be
             * protected by a mutex. */

            if(OSAL_MUTEX_Lock(&pUSBDrvObj->mutexID, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
            {
                SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex lock failed");
            }

            /* Disable the interrupt. */
            interruptWasEnabled = _DRV_USB_InterruptSourceDisable(pUSBDrvObj->interruptSource);
        }

        /* Search for the IRP in the queue. irpCancel will be true if the IRP to
         * be cancelled was found in the queue. */

        pIteratorIRP = pPipe->irpQueueHead;

        if(pIteratorIRP == pIRP)
        {
            /* Scenario - IRP to be cancelled is 1st IRP in the pipe */
            pPipe->irpQueueHead = pIteratorIRP->next;
            irpCancel = true;
        }
        else
        {
            /* Scenario - IRP to be cancelled is NOT the 1st IRP in the pipe.
             * Start searching with the next IRP in the queue. */
            while(pIteratorIRP != NULL)
            {
                if(pIteratorIRP->next == pIRP)
                {
                    /* IRP to be cancelled has been found. The next and previous
                     * pointers in the doubly linked list need to be manipulated
                     * to removed this IRP from the queue. */
                    pIteratorIRP->next = (pIteratorIRP->next)->next;
                    irpCancel = true;
                    break;
                }
                pIteratorIRP = pIteratorIRP->next;
            }
        }
        
        /* Have we found the IRP in the queue */
        if(irpCancel == true)
        {
            if(pIRP->status == USB_HOST_IRP_STATUS_IN_PROGRESS)
            {
                /* If the irp is already in progress then we set the temporary
                 * state. This will get caught in
                 * _DRV_USB_HOST_ControlXferProcess() and
                 * _DRV_USB_HOST_NonControlIRPProcess() functions. */
                pIRP->tempState = DRV_USB_HOST_IRP_STATE_ABORTED;
            }
            else
            {
                /* If the IRP is not in progress, then we can terminate it
                 * immediately. Invoke the callback. */
                pIRP->status = USB_HOST_IRP_STATUS_ABORTED;
                if(pIRP->callback != NULL)
                {
                    pIRP->callback((USB_HOST_IRP *)pIRP);
                }
            }
        }

        if(pIteratorIRP == NULL)
        {
            /* Either no IRP at all in the Pipe
             * or particular IRP not found
             */
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "IRP not found");
        }

        if(!(pUSBDrvObj->inInterruptContext))
        {
            /* Restore the interrupt status and release the mutex */
            if(interruptWasEnabled)
            {
                _DRV_USB_InterruptSourceEnable(pUSBDrvObj->interruptSource);
            }

            if(OSAL_MUTEX_Unlock(&pUSBDrvObj->mutexID) != OSAL_RESULT_TRUE)
            {
                SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex unlock failed");
            }
        }
    }

}/* end of DRV_USB_HOST_IRPCancel() */

// *****************************************************************************
/* Function:
    bool _DRV_USB_HOST_ControlXferProcess
    (
        DRV_USB_OBJ * hDriver,
        USB_HOST_IRP_LOCAL * irp,
        DRV_USB_TRANSACTION_RESULT deviceResponse,
        unsigned int deviceResponseSize
    )

  Summary:
    Dynamic implementation of _DRV_USB_HOST_ControlXferProcess internal function
    when controller is in Host mode.

  Description:
    Function is used to send\receive CONTROL transfer token, data and status.
    Function returns true if a token was sent at the time when the it exits.

  Remarks:
    This is a local function and should not be called directly by the
    application.
*/

bool _DRV_USB_HOST_ControlXferProcess
(
    DRV_USB_OBJ * pUSBDrvObj,
    USB_HOST_IRP_LOCAL * pIRP,
    DRV_USB_TRANSACTION_RESULT deviceResponse,
    unsigned int deviceResponseSize
)
{
    /* This function returns true if a token was sent at the time when the
     * function exits */

    /* Start of local variables */
    DRV_USB_BDT_ENTRY * pBDT        = (DRV_USB_BDT_ENTRY *)NULL;
    DRV_USB_HOST_PIPE_OBJ * pipe    = (DRV_USB_HOST_PIPE_OBJ *)pIRP->pipe;
    uint8_t endpoint                = pipe->endpointAndDirection & 0xF;
    uint8_t deviceAddress           = pipe->deviceAddress;
    USB_MODULE_ID usbID             = pUSBDrvObj->usbID;
    bool isLowSpeed                 = (pipe->speed == USB_SPEED_LOW) ?  true : false;
    bool tokenSent                  = false;
    bool endIRP                     = false;
    /* End of local variables */

    if(pIRP->tempState == DRV_USB_HOST_IRP_STATE_ABORTED)
    {
        /* This means the application aborted this IRP.  We just invoke the
         * callback. If this function is being called, it means the
         * pUSBDrvObj->numSWEpEntry is pointing to a Software endpoint object
         * that is managing control transfers. We do not process this IRP any
         * more. The tobeDone flag is set to false and the control IRP is
         * removed from the current pipe. */

        pUSBDrvObj->drvUSBHostSWEp[pUSBDrvObj->numSWEpEntry].tobeDone = false;
        ((pUSBDrvObj->transferGroup
          [pUSBDrvObj->drvUSBHostSWEp[pUSBDrvObj->numSWEpEntry].transferType])
         .currentPipe)->irpQueueHead =
            (pUSBDrvObj->drvUSBHostSWEp[pUSBDrvObj->numSWEpEntry].pIRP)->next;

        /* We must update the pipe to move to the next pipe in the pipe bundle
         * While doing so, check if we have reached the last pipe in the bundle,
         * if so then wrap around to the first pipe in the bundle. */
        if((pUSBDrvObj->transferGroup[USB_TRANSFER_TYPE_CONTROL].currentPipe)
                ->next != NULL)
        {
            /* This is not the last PIPE */
            pUSBDrvObj->transferGroup[USB_TRANSFER_TYPE_CONTROL].currentPipe =
                pUSBDrvObj->transferGroup[USB_TRANSFER_TYPE_CONTROL].
                currentPipe->next;
        }
        else
        {
            /* This is the last PIPE. Move to the head pipe */
            pUSBDrvObj->transferGroup[USB_TRANSFER_TYPE_CONTROL].currentPipe =
                pUSBDrvObj->transferGroup[USB_TRANSFER_TYPE_CONTROL].pipe;
        }

        pIRP->status = USB_HOST_IRP_STATUS_ABORTED;
        if(pIRP->callback != NULL)
        {
            pIRP->callback((USB_HOST_IRP *)pIRP);
        }

        /* Return false indicating that no token was sent in this frame */
        return(false);
    }

    switch(pIRP->tempState)
    {
        case DRV_USB_HOST_IRP_STATE_SETUP_STAGE:

            /* This means we are at the first step in the control transfer. We
             * need to send the Setup Packet. Update the IRP status to indicate
             * that the IRP processing has started */ 

            pIRP->status = USB_HOST_IRP_STATUS_IN_PROGRESS;
            pIRP->completedBytes = 0;

            /* A control transfer pipe is unique in the sense that the pipe is
             * bidirectional. Here we obtain the direction of the pipe based on
             * the direction specified in the setup packet. This is stored in
             * the pipe object itself. */

            if((((uint8_t *)(pIRP->setup))[0] & 0x80) != 0)
            {
                /* Data stage direction is from device to host */
                pipe->endpointAndDirection |= (USB_DATA_DIRECTION_DEVICE_TO_HOST << 7);
            }
            else
            {
                /* Data stage direction is from host to device */
                pipe->endpointAndDirection &= 0xF;
                pipe->endpointAndDirection |= (USB_DATA_DIRECTION_HOST_TO_DEVICE << 7);
            }

            /* Keep track of the transaction */
            pIRP->tempState = DRV_USB_HOST_IRP_STATE_SETUP_TOKEN_SENT;
            pBDT = pUSBDrvObj->pBDT + 2 + pUSBDrvObj->ep0TxPingPong;
            
            /* Configure the BDT Entry for setup packet and Data 0 toggle */
            pBDT->shortWord[1]  = 8;
            pBDT->word[1]       = KVA_TO_PA(pIRP->setup);
            pBDT->byte[0]       = 0x88;
            
            /* The BDT is armed. We can send the Setup Token to the device */
            _DRV_USB_SendTokenToAddress(usbID, deviceAddress, USB_PID_SETUP, endpoint, isLowSpeed);

            /* Set the flag to indicate that a token was sent */
            tokenSent = true;
            break;

        case DRV_USB_HOST_IRP_STATE_SETUP_TOKEN_SENT:
            
            /* This means we sent the Setup token and received the Transaction
             * interrupt. Check the device response to the setup token. It
             * should be always an ACK. */

            if(deviceResponse == USB_TRANSACTION_ACK)
            {
                if((pIRP->data == NULL) || (pIRP->size == 0))
                {
                    /* This means that this is a zero data stage transaction */

                    pIRP->tempState = DRV_USB_HOST_IRP_STATE_HANDSHAKE;
                    pipe->nakCounter = 0;
                    break;
                }

                /* Setup the data toggle for the next stage and go to the next
                 * stage directly.  Switch case fall through is intentional. */

                pipe->dataToggle = USB_BUFFER_DATA1;
                pipe->nakCounter = 0;
                pIRP->tempState = DRV_USB_HOST_IRP_STATE_DATA_STAGE;
            }
            else
            {
                /* Something is seriously wrong with this device. As per the
                 * specification, the device must ACK the Setup packet. We will
                 * end the control transfer immediately. */

                pIRP->tempState = DRV_USB_HOST_IRP_STATE_COMPLETE;
                pIRP->status = USB_HOST_IRP_STATUS_ERROR_UNKNOWN;
                endIRP = true;
                break;
            }
            /* The switch case fall through here is intentional */

        case DRV_USB_HOST_IRP_STATE_DATA_STAGE:

            /* We have reached here because the Setup stage of an ongoing
             * control transfer has completed. We now need to start the data
             * stage. The following function will arm the endpoint in the BDT
             * and will initiate the data stage. */

            _DRV_USB_HOST_ControlSendToken(pIRP, pUSBDrvObj, pipe, endpoint, deviceAddress, usbID, isLowSpeed);
            tokenSent = true;
            break;

        case DRV_USB_HOST_IRP_STATE_DATA_STAGE_SENT:
 
            /* We have reached here because a control transfer data transaction
             * has completed. We need to check the device response. The endIRP
             * flag will be set to true if the IRP has to be terminated. */
            if(deviceResponse == USB_TRANSACTION_NAK)
            {
                /* The device response in a NAK. This means the device is not
                 * ready with the data. Rewind the state to the previous state.
                 * We will retry again on the next SOF. Increment the control
                 * transfer NAK counter on this pipe. If the limit is reached
                 * then we should terminate the control transfer. */

                pIRP->tempState = DRV_USB_HOST_IRP_STATE_DATA_STAGE;
                pipe->nakCounter ++;
                if(pipe->nakCounter >= DRV_USB_HOST_NAK_LIMIT)
                {
                    pIRP->tempState = DRV_USB_HOST_IRP_STATE_COMPLETE;
                    pIRP->status = USB_HOST_IRP_STATUS_ERROR_NAK_TIMEOUT;
                    endIRP = true;
                    pipe->nakCounter = 0;
                }
                break;

            }
            else if (deviceResponse == USB_TRANSACTION_STALL)
            {
                /* The device response is a STALL. We should end the control
                 * transfer. */
                pipe->nakCounter = 0;
                pIRP->status = USB_HOST_IRP_STATUS_ERROR_STALL;
                pIRP->tempState =  DRV_USB_HOST_IRP_STATE_COMPLETE;
                endIRP = true;
                break;
            }
            else if ((deviceResponse == USB_TRANSACTION_DATA0 )
                    ||(deviceResponse == USB_TRANSACTION_DATA1)
                    ||(deviceResponse == USB_TRANSACTION_ACK))
            {
                /* The device has acknowledged the data stage. Update the IRP
                 * with the amount of data received */
                pipe->nakCounter = 0;
                pIRP->completedBytes += deviceResponseSize;
                pIRP->completedBytesInThisFrame += deviceResponseSize;

                if((pipe->endpointAndDirection & 0x80) != 0)
                {
                    /* Data is moving from device to host Check if the data
                     * stage is done */

                    if((deviceResponseSize < pipe->endpointSize) ||(pIRP->completedBytes >= pIRP->size))
                    {
                        /* A host control read transfer is done when the host
                         * has received the amount of data that it was looking
                         * for or when the host receives a less than
                         * maxPacketSize data packet. */

                        /* Reset the nak counter for the next data transaction.
                         * Fall through to the handshake stage. */
                        
                        pIRP->tempState = DRV_USB_HOST_IRP_STATE_HANDSHAKE;
                    }
                    else if((deviceResponseSize == pIRP->tempSize) ||
                            (deviceResponseSize == pipe->endpointSize))
                    {
                        if(pIRP->tempSize > pIRP->completedBytesInThisFrame)
                        {
                            /* More transactions are required in this frame */
                            pipe->dataToggle ^= 0x1;
                            pIRP->tempState = DRV_USB_HOST_IRP_STATE_DATA_STAGE;
                            pIRP->status = USB_HOST_IRP_STATUS_IN_PROGRESS;
                            _DRV_USB_HOST_ControlSendToken(pIRP,pUSBDrvObj,
                                    pipe,endpoint,deviceAddress,usbID,
                                    isLowSpeed);
                            tokenSent = true;
                        }
                        else
                        {
                            /* Whatever planned for this frame has been done */
                            /* Do not Move the IRP Queue head here */
                            /* Do not end the IRP */
                            pIRP->tempState = DRV_USB_HOST_IRP_STATE_DATA_STAGE;
                            pIRP->status = USB_HOST_IRP_STATUS_IN_PROGRESS;
                            pipe->dataToggle ^= 0x1;
                            pipe->nakCounter = 0;
                            endIRP = false;
                            tokenSent = false;
                        }
                        break;
                    }
                }
                else 
                {
                    /* Data is moving from host to device */
                    if(pIRP->completedBytes >= pIRP->size)
                    {
                     /* The write transfer is complete. Fall through to the
                      * handshake stage */   
                        pipe->nakCounter = 0;
                        pIRP->tempState = DRV_USB_HOST_IRP_STATE_HANDSHAKE;
                    }
                    else if((deviceResponseSize == pIRP->tempSize) ||
                            (deviceResponseSize == pipe->endpointSize))
                    {
                        if(pIRP->tempSize > pIRP->completedBytesInThisFrame)
                        {
                            /* More transactions are required in this frame */
                            pipe->dataToggle ^= 0x1;
                            pIRP->tempState = DRV_USB_HOST_IRP_STATE_DATA_STAGE;
                            pIRP->status = USB_HOST_IRP_STATUS_IN_PROGRESS;
                            _DRV_USB_HOST_ControlSendToken(pIRP,pUSBDrvObj,
                                    pipe,endpoint,deviceAddress,usbID,
                                    isLowSpeed);
                            tokenSent = true;
                        }
                        else
                        {
                            /* Whatever planned for this frame has been done */
                            /* Do not Move the IRP Queue head here */
                            /* Do not end the IRP */
                            pIRP->tempState = DRV_USB_HOST_IRP_STATE_DATA_STAGE;
                            pIRP->status = USB_HOST_IRP_STATUS_IN_PROGRESS;
                            pipe->dataToggle ^= 0x1;
                            pipe->nakCounter = 0;
                            endIRP = false;
                            tokenSent = false;
                        }
                        break;
                    }
                }

            }

        case DRV_USB_HOST_IRP_STATE_HANDSHAKE:
            /* Send the Handshake Stage */
            {
                USB_BUFFER_DIRECTION direction;
                USB_BUFFER_PING_PONG pingPong;
                USB_PID pid;

                if((pipe->endpointAndDirection & 0x80) != 0)
                {
                    /* Data is moving from device to host */
                    direction = USB_BUFFER_TX;
                    pingPong = pUSBDrvObj->ep0TxPingPong;
                    pid = USB_PID_OUT;
                }
                else 
                {
                    /* Data is moving from host to device */
                    direction = USB_BUFFER_RX;
                    pingPong = pUSBDrvObj->ep0RxPingPong;
                    pid = USB_PID_IN;
                }
                
                pBDT = pUSBDrvObj->pBDT + (direction << 1) + pingPong;

                /* Configure the BDT Entry for data packet */
                pBDT->shortWord[1]  = 0;
                pBDT->word[1]       = 0;
                pBDT->byte[0]       = 0xC8;

                /* Keep track of the transaction */
                pIRP->tempState = DRV_USB_HOST_IRP_STATE_HANDSHAKE_SENT;

                /* This will cause the Transaction interrupt */
                _DRV_USB_SendTokenToAddress(usbID, deviceAddress,
                        pid, endpoint, isLowSpeed);

                tokenSent = true;
                break;
            }

        case DRV_USB_HOST_IRP_STATE_HANDSHAKE_SENT:
            /* Check the response */
            if((USB_TRANSACTION_ACK == deviceResponse)
                    || (USB_TRANSACTION_DATA1 == deviceResponse))
            {
                /* Transfer is complete */
                pIRP->tempState = DRV_USB_HOST_IRP_STATE_COMPLETE;
                pIRP->status = USB_HOST_IRP_STATUS_COMPLETED;
                if(((pipe->endpointAndDirection & 0x80) != 0)
                        && (pIRP->size > pIRP->completedBytes))
                {
                    /* While moving data from device to host, if we received
                     * less data from the device than expected, then indicate a
                     * short packet and set the irp size to to actual size */ 

                    pIRP->status = USB_HOST_IRP_STATUS_COMPLETED_SHORT;
                    pIRP->size = pIRP->completedBytes;
                }
                endIRP = true;
            }
            else if(USB_TRANSACTION_NAK == deviceResponse)
            {
                pIRP->tempState = DRV_USB_HOST_IRP_STATE_HANDSHAKE;
                pipe->nakCounter ++;
                if(pipe->nakCounter > DRV_USB_HOST_NAK_LIMIT)
                {
                    pIRP->tempState = DRV_USB_HOST_IRP_STATE_COMPLETE;
                    pIRP->status = USB_HOST_IRP_STATUS_ERROR_NAK_TIMEOUT;
                    endIRP = true;
                }
                break;
            }
            else if(USB_TRANSACTION_STALL == deviceResponse)
            {
                pIRP->tempState = DRV_USB_HOST_IRP_STATE_COMPLETE;
                pIRP->status = USB_HOST_IRP_STATUS_ERROR_STALL;
                endIRP = true;
                break;
            }

        case DRV_USB_HOST_IRP_STATE_COMPLETE:
            /* Remove the irp from the from the SW EP object. */
            endIRP = true;
            break;

        default:
            break;
    }

    /* An IRP will end if the handshake stage has completed, or if there was a
     * stall during data or status stage, a NAK time out error or an error in the
     * setup stage. */

    if(endIRP == true)
    {
        pUSBDrvObj->drvUSBHostSWEp[pUSBDrvObj->numSWEpEntry].tobeDone = false;

        /* Updtae the IRP to move to the next IRP in the pipe */
        ((pUSBDrvObj->transferGroup[USB_TRANSFER_TYPE_CONTROL])
         .currentPipe)->irpQueueHead =
            (pUSBDrvObj->drvUSBHostSWEp[pUSBDrvObj->numSWEpEntry].pIRP)
            ->next;

        /* Update the current pipe to point to the next pipe in the bundle */
        if((pUSBDrvObj->transferGroup[USB_TRANSFER_TYPE_CONTROL].currentPipe)
                ->next != NULL)
        {
            /* This is not the last PIPE */
            pUSBDrvObj->transferGroup[USB_TRANSFER_TYPE_CONTROL].currentPipe =
                pUSBDrvObj->transferGroup[USB_TRANSFER_TYPE_CONTROL].
                currentPipe->next;
        }
        else
        {
            /* This is the last PIPE. Move to the head pipe */
            pUSBDrvObj->transferGroup[USB_TRANSFER_TYPE_CONTROL].currentPipe =
                pUSBDrvObj->transferGroup[USB_TRANSFER_TYPE_CONTROL].pipe;
        }

        /* IRP completed. Call the callback */
        if(pIRP->callback != NULL)
        {
            pIRP->callback((USB_HOST_IRP *)pIRP);
        }
    }

    return(tokenSent);

} /* end of _DRV_USB_HOST_ControlXferProcess() */

// *****************************************************************************
/* Function:
     void DRV_USB_HOST_PipeClose(DRV_USB_HOST_PIPE_HANDLE pipeHandle)

  Summary:
    Dynamic implementation of DRV_USB_HOST_PipeClose client interface function.

  Description:
    This is the dynamic implementation of DRV_USB_HOST_PipeClose client interface
    function. Function performs the following task:
    - Releases the pipe to be closed from the appropriate pipe type list
    - Aborts all the IRPs on that pipe

  Remarks:
    See drv_usb.h for usage information.
*/

void DRV_USB_HOST_PipeClose
(
    DRV_USB_HOST_PIPE_HANDLE pipeHandle
)
{
    /* Start of local variables */
    bool interruptWasEnabled                    = false;
    DRV_USB_OBJ * pUSBDrvObj                    = (DRV_USB_OBJ *)NULL;
    USB_HOST_IRP_LOCAL * pIRP                   = (USB_HOST_IRP_LOCAL *)NULL;
    DRV_USB_HOST_PIPE_OBJ * pPipe               = (DRV_USB_HOST_PIPE_OBJ *)NULL;
    DRV_USB_HOST_PIPE_OBJ * piteratorPipe       = (DRV_USB_HOST_PIPE_OBJ *)NULL;
    DRV_USB_HOST_TRANSFER_GROUP * pTransferGroup = (DRV_USB_HOST_TRANSFER_GROUP *)NULL ;
    /* End of local variables */
    
    /* Make sure we have a valid pipe */
    if(pipeHandle == DRV_USB_HOST_PIPE_HANDLE_INVALID)
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Invalid pipe handle");
    }
    else
    {
        pPipe = (DRV_USB_HOST_PIPE_OBJ*) pipeHandle;

        /* Make sure that we are working with a pipe in use */
        if(pPipe->inUse != true)
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Pipe is not in use");
            return;
        }

        pUSBDrvObj = (DRV_USB_OBJ *)pPipe->hClient;

        /* Disable the interrupt */
        if(!(pUSBDrvObj->inInterruptContext))
        {
            /* We have to disable the interrupt because the pipe object can be
             * accessed asynchronously from the interrupt service routine. */

            if(OSAL_MUTEX_Lock(&pUSBDrvObj->mutexID, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
            {
                SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex lock failed");
            }

            interruptWasEnabled = _DRV_USB_InterruptSourceDisable(pUSBDrvObj->interruptSource);
        }

        /* Get the transfer group that this pipe belongs to. */
        pTransferGroup = &pUSBDrvObj->transferGroup[pPipe->pipeType];
   
       /* Search for this pipe within this group */ 
        if(pTransferGroup->pipe == pPipe)
        {
            /* First pipe in the transfer group needs to be closed */
            pTransferGroup->pipe = pPipe->next;
        }
        else
        {
            /* Remove this pipe from the linked list */
            piteratorPipe = pTransferGroup->pipe;
            while((piteratorPipe != NULL) && (piteratorPipe->next != pPipe))
            {
                piteratorPipe = piteratorPipe->next;
            }

            /* Make sure we have a valid pipe */
            if(piteratorPipe == NULL)
            {
                SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Illegal pipe handle");
                return;
            }
            piteratorPipe->next = pPipe->next;
        }

        if(pTransferGroup->nPipes != 0)
        {
            /* Reduce the count only if its not zero already */
            pTransferGroup->nPipes --;
        }

        /* Now we invoke the call back for each IRP in this pipe and say that it
         * is aborted.  If the IRP is in progress, then that IRP will be
         * actually aborted on the next SOF This will allow the USB module to
         * complete any transaction that was in progress. */

        pIRP = (USB_HOST_IRP_LOCAL *)pPipe->irpQueueHead;
        while(pIRP != NULL)
        {
            pIRP->pipe = DRV_USB_HOST_PIPE_HANDLE_INVALID;

            if(pIRP->status == USB_HOST_IRP_STATUS_IN_PROGRESS)
            {
                /* If the IRP is in progress, then we set the temp IRP state.
                 * This will be caught in the
                 * _DRV_USB_HOST_NonControlIRPProcess() and
                 * _DRV_USB_HOST_ControlXferProcess() functions */
                pIRP->tempState = DRV_USB_HOST_IRP_STATE_ABORTED;
            }
            else
            {
                /* The IRP is not in progress and can be aborted */
                pIRP->status = USB_HOST_IRP_STATUS_ABORTED;
                if(pIRP->callback != NULL)
                {
                    pIRP->callback((USB_HOST_IRP*)pIRP);
                }
            }
            pIRP = pIRP->next;
        }

        /* Now we return the pipe back to the * driver */

        pPipe->inUse = false;

        /* Restore the interrupts */
        if(!(pUSBDrvObj->inInterruptContext))
        {
            if(interruptWasEnabled)
            {
                _DRV_USB_InterruptSourceEnable(pUSBDrvObj->interruptSource);
            }

            if(OSAL_MUTEX_Unlock(&pUSBDrvObj->mutexID) != OSAL_RESULT_TRUE)
            {
                SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex unlock failed");
            }
        }
    }

}/* end of DRV_USB_HOST_PipeClose()*/

// *****************************************************************************
/* Function:
    DRV_USB_HOST_PIPE_HANDLE DRV_USB_HOST_PipeSetup
    (
        DRV_HANDLE handle,
        uint8_t deviceAddress,
        USB_ENDPOINT endpointAndDirection,
        uint8_t hubAddress,
        uint8_t hubPort,
        USB_TRANSFER_TYPE pipeType,
        uint8_t bInterval,
        uint16_t wMaxPacketSize,
        USB_SPEED speed
    )

  Summary:
    Dynamic implementation of DRV_USB_HOST_PipeSetup client interface function.

  Description:
    This is the dynamic implementation of DRV_USB_HOST_PipeSetup client interface
    function. Function performs the following task:
    - Obtains a free pipe index from global pool
    - Updates the pipe data structure with required information
    - Adds the pipe to the specific transfer object queue based on
      transfer type
    - Returns the pipe address on success

  Remarks:
    See drv_usb.h for usage information.
*/

DRV_USB_HOST_PIPE_HANDLE DRV_USB_HOST_PipeSetup 
(
    DRV_HANDLE handle,
    uint8_t deviceAddress, 
    USB_ENDPOINT endpointAndDirection,
    uint8_t hubAddress,
    uint8_t hubPort,
    USB_TRANSFER_TYPE pipeType, 
    uint8_t bInterval, 
    uint16_t wMaxPacketSize,
    USB_SPEED speed
)
{
    /* Start of local variable */
    DRV_USB_HOST_PIPE_OBJ * pPipe          = (DRV_USB_HOST_PIPE_OBJ *)NULL;
    DRV_USB_HOST_PIPE_OBJ * piteratorPipe  = (DRV_USB_HOST_PIPE_OBJ *)NULL;
    DRV_USB_OBJ * pUSBDrvObj               = (DRV_USB_OBJ *)handle;
    DRV_USB_HOST_PIPE_HANDLE returnValue   = DRV_USB_HOST_PIPE_HANDLE_INVALID;
    DRV_USB_HOST_TRANSFER_GROUP * pTransferGroup = (DRV_USB_HOST_TRANSFER_GROUP *)NULL;
    unsigned int transferTypeLocal         = 0;
    uint8_t pipeCount                      = 0;
    uint8_t bitSetCount                    = 0;
    /* End of local variable */

    /* Check if the handle is valid */
    if((handle == DRV_HANDLE_INVALID) || (!(pUSBDrvObj->isOpened)))
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Bad Client or client closed");
    }
    else
    {
        /* We need to grab a mutex as the pipe pool is a global object */
        if(OSAL_MUTEX_Lock(&pUSBDrvObj->mutexID, OSAL_WAIT_FOREVER) != OSAL_RESULT_TRUE)
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex lock failed");
            return DRV_USB_HOST_PIPE_HANDLE_INVALID;
        }

        /* Search for a free pipe object */
        for(pipeCount = 0; pipeCount < DRV_USB_HOST_PIPES_NUMBER; pipeCount++)
        {
            /* Check for free pipe object */

            if(gDrvUSBHostPipeObj[pipeCount].inUse == false)
            {
                /* We found a pipe object that we can use.  Go and grab that
                 * one.
                 */
                gDrvUSBHostPipeObj[pipeCount].inUse = true;
                /* Release the mutex if pipe found */

                if(OSAL_MUTEX_Unlock(&pUSBDrvObj->mutexID) != OSAL_RESULT_TRUE)
                {
                    gDrvUSBHostPipeObj[pipeCount].inUse = false;
                    SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex unlock failed");
                    return DRV_USB_HOST_PIPE_HANDLE_INVALID;
                }

                /* Initialize the pipe object */
                pPipe = &gDrvUSBHostPipeObj[pipeCount];

                pPipe->deviceAddress = deviceAddress;
                pPipe->irpQueueHead  = NULL;
                pPipe->bInterval     = bInterval;
                pPipe->speed         = speed;
                pPipe->pipeType      = pipeType;
                pPipe->hClient       = handle;
                pPipe->endpointSize  = wMaxPacketSize;
                pPipe->intervalCounter = bInterval;
                pPipe->dataToggle = USB_BUFFER_DATA0;

                pPipe->endpointAndDirection   = endpointAndDirection;

                /* This pipe should now be added to the pipe bundle. The mapping
                 * from the transfer type to the way the pipe bundles are
                 * organized is not a one to one mapping. We translate the pipe
                 * type to a local type. */

                switch(pPipe->pipeType)
                {
                    case USB_TRANSFER_TYPE_CONTROL:
                        transferTypeLocal = USB_TRANSFER_TYPE_LOCAL_CONTROL;
                        break;
                    case USB_TRANSFER_TYPE_ISOCHRONOUS:
                        transferTypeLocal = USB_TRANSFER_TYPE_LOCAL_ISOC;
                        break;
                    case USB_TRANSFER_TYPE_BULK:
                        transferTypeLocal = USB_TRANSFER_TYPE_LOCAL_BULK;
                        break;
                    case USB_TRANSFER_TYPE_INTERRUPT:
                        transferTypeLocal = USB_TRANSFER_TYPE_LOCAL_INTERRUPT;
                        break;
                    default:
                        return returnValue;
                }

                /* In a case where the max packet size is a multiple of 2, find
                 * calculate the log2n. */
                if((wMaxPacketSize <= 512) && (wMaxPacketSize != 0))
                {
                    for(bitSetCount = 0; bitSetCount < 10; bitSetCount++)
                    {
                        if((wMaxPacketSize & 0x00000001) == 0x00000001)
                        {
                            break;
                        }
                        wMaxPacketSize = wMaxPacketSize >> 1;
                    }
                }
                else if((wMaxPacketSize != 0))
                {
                    /* This means the max packet size is greater than 512. This
                     * is possible for Isochronous transfers */

                    bitSetCount = 10;
                }

                /* The bandwidth required per transaction is calculated up front
                 * so that we dont have to calculate this in the interrupt
                 * context when the transaction is in progress */
                if(bitSetCount != 10)
                {
                    if(pPipe->speed == USB_SPEED_LOW)
                    {
                        if((pPipe->pipeType == USB_TRANSFER_TYPE_INTERRUPT) ||
                                (pPipe->pipeType == USB_TRANSFER_TYPE_CONTROL))
                        {
                            pPipe->bwPerTransaction = gDrvUSBLSTableBW[transferTypeLocal][bitSetCount];
                        }
                        else
                        {
                            /* Only control and interrupt pipe can exist in
                               low speed */
                            gDrvUSBHostPipeObj[pipeCount].inUse = false;
                            return DRV_USB_HOST_PIPE_HANDLE_INVALID;
                        }
                    }
                    else
                    {
                        pPipe->bwPerTransaction = gDrvUSBFSTableBW[transferTypeLocal][bitSetCount];
                    }
                }
                else if(bitSetCount == 10 &&
                        pPipe->pipeType == USB_TRANSFER_TYPE_ISOCHRONOUS &&
                        pPipe->speed == USB_SPEED_FULL)
                {
                    /* Bandwidth for Isochronous tranfers */
                    pPipe->bwPerTransaction = gDrvUSBFSTableBW[transferTypeLocal][bitSetCount];
                }
                else
                {
                    /* Error */
                    return returnValue;
                }

                /* This pipe should be added to the respective transfer group */

                pTransferGroup = &(pUSBDrvObj->transferGroup[pipeType]);

                if(pTransferGroup->pipe == NULL)
                {
                    /* This if the first pipe to be setup */
                    pTransferGroup->pipe = pPipe;
                    pTransferGroup->currentPipe = pPipe;
                }
                else
                {
                    /* This is NOT the first pipe. Find
                     * the last pipe in the linked list */
                    piteratorPipe = pTransferGroup->pipe;
                    while(piteratorPipe->next != NULL)
                    {
                        /* This is not the last pipe in
                         * this transfer group */
                        piteratorPipe = piteratorPipe->next;
                    }
                    piteratorPipe->next = pPipe;
                }
                pPipe->next = NULL;
                /* Update the pipe count in the transfer group */
                pTransferGroup->nPipes ++;
                returnValue = (DRV_USB_HOST_PIPE_HANDLE)pPipe;
                break;
            }/* end of pipe object found */

        } /* end of for loop() */
    }

    if(pipeCount == DRV_USB_HOST_PIPES_NUMBER)
    {
        /* Release the mutex if pipe not found */
        if(OSAL_MUTEX_Unlock(&pUSBDrvObj->mutexID) != OSAL_RESULT_TRUE)
        {
            SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Mutex unlock failed");
        }
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Could not find a free pipe object");
    }

    /* Return the handle */
    return returnValue;

}/* end of DRV_USB_HOST_PipeSetup() */

// *****************************************************************************
/* Function:
    void _DRV_USB_HOST_ControlSendToken
    (
        USB_HOST_IRP_LOCAL * pIRP,
        DRV_USB_OBJ *pUSBDrvObj,
        DRV_USB_HOST_PIPE_OBJ *pipe,
        bool isLowSpeed
    )

  Summary:
    Dynamic implementation of _DRV_USB_HOST_ControlSendToken internal
    function.

  Description:
    This is the dynamic implementation of _DRV_USB_HOST_ControlSendToken
    function. Function sends token for CONTROL transfer data phase.

  Remarks:
    This is a local function and should not be called directly by the
    application.

*/

void _DRV_USB_HOST_ControlSendToken
(
    USB_HOST_IRP_LOCAL * pIRP,
    DRV_USB_OBJ *pUSBDrvObj,
    DRV_USB_HOST_PIPE_OBJ *pipe,
    uint8_t endpoint,
    uint8_t deviceAddress,
    USB_MODULE_ID usbID,
    bool isLowSpeed
)
{
    /* Start of local variable */
    USB_BUFFER_DIRECTION direction;
    USB_BUFFER_PING_PONG pingPong;
    USB_PID pid;
    unsigned int size;
    DRV_USB_BDT_ENTRY * pBDT        = (DRV_USB_BDT_ENTRY *)NULL;
    /* End of local variable */

    if((pipe->endpointAndDirection & 0x80)  != 0)
    {
        /* Direction is device to host */

        direction = USB_BUFFER_RX;
        pingPong = pUSBDrvObj->ep0RxPingPong;
        pid = USB_PID_IN;
    }
    else
    {
        /* Direction is host to device */
        direction = USB_BUFFER_TX;
        pingPong = pUSBDrvObj->ep0TxPingPong;
        pid = USB_PID_OUT;
    }

    if((pIRP->tempSize - pIRP->completedBytesInThisFrame) >= pipe->endpointSize)
    {
        /* This means we have to break
         * up the transfer into transactions */
        size = pipe->endpointSize;
    }
    else
    {
        /* Data size is less than endpoint size */
        size = pIRP->tempSize;
    }

    /* Keep track of the transaction */
    pIRP->tempState = DRV_USB_HOST_IRP_STATE_DATA_STAGE_SENT;

    pBDT = pUSBDrvObj->pBDT + (direction << 1) + pingPong;

    /* Configure the BDT Entry for data packet */
    pBDT->shortWord[1]  = size;
    pBDT->word[1]       = KVA_TO_PA(pIRP->data + pIRP->completedBytes);
    pBDT->byte[0]       = 0x88 | (pipe->dataToggle << 6);

    /* This will cause the Transaction interrupt */
    _DRV_USB_SendTokenToAddress(usbID, deviceAddress, pid, endpoint, isLowSpeed);

}/* end of _DRV_USB_HOST_ControlSendToken() */

// *****************************************************************************
/* Function:
    void _DRV_USB_HOST_NonControlSendToken
    (
        USB_HOST_IRP_LOCAL * pIRP,
        DRV_USB_OBJ *pUSBDrvObj,
        DRV_USB_HOST_PIPE_OBJ *pipe,
        bool isLowSpeed
    )
  
  Summary:
    Dynamic implementation of _DRV_USB_HOST_NonControlSendToken internal
    function.

  Description:
    This is the dynamic implementation of _DRV_USB_HOST_NonControlSendToken
    function. Function sends token for NON CONTROL transfer.

  Remarks:
    This is a local function and should not be called directly by the
    application.
*/

void _DRV_USB_HOST_NonControlSendToken
(
    USB_HOST_IRP_LOCAL * pIRP,
    DRV_USB_OBJ *pUSBDrvObj,
    DRV_USB_HOST_PIPE_OBJ *pipe,
    bool isLowSpeed
)
{
    /* Start of local variable */
    int direction = 0;
    int size;
    USB_PID pid;
    USB_MODULE_ID usbID;
    DRV_USB_BDT_ENTRY * pBDT   = (DRV_USB_BDT_ENTRY *)NULL;
    USB_BUFFER_PING_PONG pingpong;
    uint8_t endpoint;
    uint8_t deviceAddress;
    /* End of local variable */


    pBDT        = pUSBDrvObj->pBDT;
    usbID       = pUSBDrvObj->usbID;

    endpoint    = pipe->endpointAndDirection & 0xF;
    deviceAddress   = pipe->deviceAddress;


    pIRP->status = USB_HOST_IRP_STATUS_IN_PROGRESS;
    if((pipe->endpointAndDirection & 0x80) != 0)
    {
        /* Data is moving from device to host */
        direction = USB_BUFFER_RX;
        pingpong = pUSBDrvObj->ep0RxPingPong;
        pid = USB_PID_IN;
    }
    else
    {
        /* Data is moving from host to device */
        direction = USB_BUFFER_TX;
        pingpong = pUSBDrvObj->ep0TxPingPong;
        pid = USB_PID_OUT;
    }

    if((pIRP->tempSize - pIRP->completedBytesInThisFrame) >= pipe->endpointSize)
    {
        size = pipe->endpointSize;
    }
    else
    {
        size = pIRP->tempSize;
    }

    pBDT = pUSBDrvObj->pBDT + (direction << 1) + pingpong;

    /*Configure the BDT Entry for data packet */
    pBDT->shortWord[1] = size;
    pBDT->word[1] = KVA_TO_PA(pIRP->data + pIRP->completedBytes);
    pBDT->byte[0] = 0x88 | (pipe->dataToggle << 6);

    /* This will cause a transaction interrupt */
    _DRV_USB_SendTokenToAddress(usbID, deviceAddress, pid, endpoint, isLowSpeed);

}/* end of _DRV_USB_HOST_NonControlSendToken() */

// *****************************************************************************
/* Function:
    bool _DRV_USB_HOST_NonControlIRPProcess
    (
        DRV_USB_OBJ * pUSBDrvObj,
        USB_HOST_IRP_LOCAL * pIRP, 
        DRV_USB_TRANSACTION_RESULT lastTransactionResult,
        int lastTransactionsize
    )

  Summary:
    Dynamic implementation of _DRV_USB_HOST_NonControlIRPProcess internal
    function.

  Description:
    This is the dynamic implementation of _DRV_USB_HOST_NonControlIRPProcess
    function. Function sends token for NON CONTROL transfer.

  Remarks:
    This is a local function and should not be called directly by the
    application.
    
*/

bool _DRV_USB_HOST_NonControlIRPProcess
(
    DRV_USB_OBJ * pUSBDrvObj,
    USB_HOST_IRP_LOCAL * pIRP, 
    DRV_USB_TRANSACTION_RESULT lastTransactionResult,
    int lastTransactionsize
)
{
    /* Start of local variable */
    bool endIRP;
    bool isLowSpeed;
    DRV_USB_HOST_PIPE_OBJ   * pipe   = (DRV_USB_HOST_PIPE_OBJ *)NULL;
    bool tokenSent                   = false;
    /* End of local variable */    

    if(pIRP->tempState == DRV_USB_HOST_IRP_STATE_ABORTED)
    {
        /* This means that this IRP was aborted
         * by the application while it was in 
         * progress. Terminate it now. */
        pUSBDrvObj->drvUSBHostSWEp[pUSBDrvObj->numSWEpEntry].tobeDone = false;
        ((pUSBDrvObj->transferGroup
          [pUSBDrvObj->drvUSBHostSWEp[pUSBDrvObj->numSWEpEntry].
          transferType])
         .currentPipe)->irpQueueHead =
            (pUSBDrvObj->drvUSBHostSWEp[pUSBDrvObj->numSWEpEntry].pIRP)->next;

        pIRP->status = USB_HOST_IRP_STATUS_ABORTED;
        if(pIRP->callback != NULL)
        {
            pIRP->callback((USB_HOST_IRP*)pIRP);
        }
        return false;
    }

    pipe        = (DRV_USB_HOST_PIPE_OBJ *)pIRP->pipe;
    isLowSpeed 	= (pipe->speed == USB_SPEED_LOW) ? true : false;

    if(lastTransactionResult == 0)
    {
        /* This means that a token need to be sent */
        _DRV_USB_HOST_NonControlSendToken(pIRP,pUSBDrvObj,pipe,isLowSpeed);
        if(pipe->pipeType == USB_TRANSFER_TYPE_ISOCHRONOUS)
        {
            /* Remove the irp from the from the SW EP object. */
            pUSBDrvObj->drvUSBHostSWEp[pUSBDrvObj->numSWEpEntry].tobeDone
                = false;

            ((DRV_USB_HOST_PIPE_OBJ *)(pUSBDrvObj->drvUSBHostSWEp
                [pUSBDrvObj->numSWEpEntry].pIRP->pipe))->irpQueueHead =
                (pUSBDrvObj->drvUSBHostSWEp[pUSBDrvObj->numSWEpEntry].pIRP)
                ->next;

            if(pIRP->callback != NULL)
            {
                pIRP->callback((USB_HOST_IRP *)pIRP);
            }
            tokenSent = false;
        }
        else
        {
            tokenSent = true;
        }
    }
    else
    {
        /* This means this function was called from the TRNIF
         * interrupt after the token was sent. Check the 
         * transaction result */
        endIRP = false;
        tokenSent = false;
        switch(lastTransactionResult)
        {
            case USB_TRANSACTION_ACK:
            case USB_TRANSACTION_DATA0:
            case USB_TRANSACTION_DATA1:    
                pIRP->completedBytes += lastTransactionsize;
                pIRP->completedBytesInThisFrame += lastTransactionsize;
                pipe->dataToggle ^= 0x1;
                pipe->nakCounter = 0;
                if((lastTransactionsize < pipe->endpointSize) ||
                        (pIRP->size <= pIRP->completedBytes))
                {
                    /* We received data less than endpoint size.
                     * So we end the transfer */
                    if(pIRP->size < pIRP->completedBytes)
                    {
                        pIRP->status = USB_HOST_IRP_STATUS_COMPLETED_SHORT;
                    }
                    else
                    {
                        pIRP->status = USB_HOST_IRP_STATUS_COMPLETED;
                    }
                    endIRP = true;
                }
                else if((lastTransactionsize == pIRP->tempSize) ||
                        (lastTransactionsize == pipe->endpointSize))
                {
                    if(pIRP->tempSize > pIRP->completedBytesInThisFrame)
                    {
                        /* Some more transactions are required in this frame */
                        pIRP->status = USB_HOST_IRP_STATUS_IN_PROGRESS;
                        _DRV_USB_HOST_NonControlSendToken(pIRP,pUSBDrvObj,
                                pipe,isLowSpeed);
                        tokenSent = true;
                    }
                    else
                    {
                        /* Whatever planned for this frame has been done */
                        /* Do not Move the IRP Queue head here */

                        /* Do not end the IRP */
                        endIRP = false;
                        tokenSent = false;
                    }
                }
                break;
            case USB_TRANSACTION_STALL:
                /* The token was stalled. We end the IRP */
                pipe->nakCounter = 0;
				pipe->dataToggle = USB_BUFFER_DATA0;
                pIRP->status = USB_HOST_IRP_STATUS_ERROR_STALL;
                endIRP = true;
                break;
            case USB_TRANSACTION_NAK:
                /* For non - control transfer we don't implement a 
                 * NAK time out.Do not do anything here */
                endIRP = false;
                break;
            default:
                break;
        }

        if(endIRP == true)
        {
            /* Remove the irp from the from the SW EP object. */
            pUSBDrvObj->drvUSBHostSWEp[pUSBDrvObj->numSWEpEntry].tobeDone
                = false;

            ((DRV_USB_HOST_PIPE_OBJ *)(pUSBDrvObj->drvUSBHostSWEp
                [pUSBDrvObj->numSWEpEntry].pIRP->pipe))->irpQueueHead =
                (pUSBDrvObj->drvUSBHostSWEp[pUSBDrvObj->numSWEpEntry].pIRP)
                ->next;
            /* Update the size field with actual size received\transmitted */
            pIRP->size = pIRP->completedBytes;

            if(pIRP->callback != NULL)
            {
                pIRP->callback((USB_HOST_IRP *)pIRP);
            }

        }
    }

    return tokenSent;

}/* end of _DRV_USB_HOST_NonControlIRPProcess() */

// *****************************************************************************
/* Function:
    void _DRV_USB_HOST_CalculateControlBW
    (
        DRV_USB_OBJ * pUSBDrvObj,
        DRV_USB_HOST_TRANSFER_GROUP * pTransferGroup,
        USB_HOST_IRP_LOCAL * pControlIRP
    )

  Summary:
    Dynamic implementation of _DRV_USB_HOST_CalculateControlBW internal
    function.

  Description:
    This is the dynamic implementation of _DRV_USB_HOST_CalculateControlBW
    function. Function performs the following task:
    - Obtains the bandwidth requirement for the transfer based on pipe
      and IRP size
    - Calculates the number of transactions that can be done and updates data
      structure accordingly
    - Packs the IRP for processing it in this frame.

  Remarks:
    This is a local function and should not be called directly by the
    application.

*/

void _DRV_USB_HOST_CalculateControlBW
(
    DRV_USB_OBJ * pUSBDrvObj,
    DRV_USB_HOST_TRANSFER_GROUP * pTransferGroup,
    USB_HOST_IRP_LOCAL * pControlIRP
)
{
    /* Start of local variable */
    unsigned int bwAvailable             = 0;
    unsigned int bwPerTransaction        = 0;
    unsigned int nTransactions         = 0;
    unsigned int nPossibleTransactions = 0;
    DRV_USB_HOST_PIPE_OBJ * pPipe        = (DRV_USB_HOST_PIPE_OBJ *)pControlIRP->pipe;
    /* End of local variable */

    /* Checks the BW available out of the max possible for CONTROL transfer */
    if(pPipe->speed == USB_SPEED_LOW)
    {
        bwAvailable = (DRV_USB_MAX_CONTROL_BANDWIDTH_LOW_SPEED -
                pUSBDrvObj->globalBWConsumed);
    }
    else
    {
        bwAvailable = (DRV_USB_MAX_CONTROL_BANDWIDTH_FULL_SPEED -
                pUSBDrvObj->globalBWConsumed);
    }
    bwPerTransaction = pPipe->bwPerTransaction;

    /* Check if atleast 1 transaction is possible */
    if(bwPerTransaction <= bwAvailable)
    {
        /* Atleast 1 transaction is possible */
        nTransactions = (pControlIRP->size - pControlIRP->completedBytes)/ pPipe->endpointSize;
        if(nTransactions == 0)
        {
            nTransactions = 1;
        }
        else if((pControlIRP->size - pControlIRP->completedBytes) %
                (pPipe->endpointSize)
                != 0)
        {
            nTransactions++;
        }

        nPossibleTransactions = bwAvailable/bwPerTransaction;
        
        if(nPossibleTransactions < nTransactions)
        {
            nTransactions = nPossibleTransactions;
        }
        /* Increment the global bandwidth */
        pUSBDrvObj->globalBWConsumed = pUSBDrvObj->globalBWConsumed + (nTransactions * bwPerTransaction);
        pControlIRP->tempSize = nTransactions * pPipe->endpointSize;

        /* Based on the above calculation, the size of the data to be
         * transmitted\received will be always multiple of endpoint size.  But
         * if this size is more than the actual size, then we should consider
         * the actual data size remaining.
         */
        if((pControlIRP->size - pControlIRP->completedBytes) < pControlIRP->tempSize)
        {
            pControlIRP->tempSize = pControlIRP->size - pControlIRP->completedBytes;
        }

        /* Reset the IRP completed bytes in this frame field */
        pControlIRP->completedBytesInThisFrame = 0;

        /* Now that we have an IRP to be processed, update the global data
         * structure
         */
        pUSBDrvObj->drvUSBHostSWEp[0].tobeDone = true;
        pUSBDrvObj->drvUSBHostSWEp[0].transferType = USB_TRANSFER_TYPE_CONTROL;
        pUSBDrvObj->drvUSBHostSWEp[0].pIRP = pControlIRP;
    }

}/* end of _DRV_USB_HOST_CalculateControlBW() */

// *****************************************************************************
/* Function:
    bool _DRV_USB_HOST_CalculateNonControlBW
    (
        DRV_USB_OBJ * pUSBDrvObj,
        DRV_USB_HOST_TRANSFER_GROUP * pTransferGroup,
        USB_HOST_IRP_LOCAL * ptransferIRP,
        USB_TRANSFER_TYPE transferType,
        uint8_t numSWEpEntry
    )

  Summary:
    Dynamic implementation of _DRV_USB_HOST_CalculateNonControlBW internal
    function.

  Description:
    This is the dynamic implementation of _DRV_USB_HOST_CalculateNonControlBW
    function. Function performs the following task:
    - Obtains the bandwidth requirement for the transfer based on pipe
      and IRP size
    - Calculates the number of transactions that can be done and updates data
      structure accordingly
    - Packs the IRP for processing it in this frame.

  Remarks:
    This is a local function and should not be called directly by the
    application.
*/

bool _DRV_USB_HOST_CalculateNonControlBW
(
    DRV_USB_OBJ * pUSBDrvObj,
    DRV_USB_HOST_TRANSFER_GROUP * pTransferGroup,
    USB_HOST_IRP_LOCAL * ptransferIRP,
    USB_TRANSFER_TYPE transferType,
    uint8_t numSWEpEntry
)
{
    /* Start of local variable */
    unsigned int bwAvailable             = 0;
    unsigned int bwPerTransaction        = 0;
    unsigned int nTransactions         = 0;
    unsigned int nPossibleTransactions = 0;
    DRV_USB_HOST_PIPE_OBJ * pPipe        =
        (DRV_USB_HOST_PIPE_OBJ *)ptransferIRP->pipe;
    bool irpPacked                       = false;

    /* End of local variable */

    /* Calculate the BW available in this frame */
    bwAvailable =
        (DRV_USB_MAX_BANDWIDTH_PER_FRAME - pUSBDrvObj->globalBWConsumed);
    bwPerTransaction = pPipe->bwPerTransaction;

    /* Check if at least 1 transaction is possible */
    if(bwPerTransaction <= bwAvailable)
    {
        /* At least 1 transaction is possible */
        nTransactions = (ptransferIRP->size - ptransferIRP->completedBytes)/
            pPipe->endpointSize;
        if(nTransactions == 0)
        {
            nTransactions = 1;
        }
        else if((ptransferIRP->size - ptransferIRP->completedBytes) %
                (pPipe->endpointSize)
                != 0)
        {
            nTransactions++;
        }
        nPossibleTransactions =
            bwAvailable/bwPerTransaction;
        if(nPossibleTransactions < nTransactions)
        {
            nTransactions = nPossibleTransactions;
        }
        /* Increment the global bandwidth */
        pUSBDrvObj->globalBWConsumed =
            pUSBDrvObj->globalBWConsumed +
            (nTransactions * bwPerTransaction);
        ptransferIRP->tempSize =
            nTransactions * pPipe->endpointSize;

        /* Based on the above calculation, the size of the data to be
         * transmitted\received will be always multiple of endpoint size.
         * But if this size is more than the actual size, then we should
         * consider the actual data size remaining.
         */
        if((ptransferIRP->size - ptransferIRP->completedBytes) <
                ptransferIRP->tempSize)
        {
            ptransferIRP->tempSize =
                ptransferIRP->size - ptransferIRP->completedBytes;
        }

        /* Reset the IRP completed bytes in this frame field */
        ptransferIRP->completedBytesInThisFrame = 0;

        /* Now that we have an IRP to be processed,
         * update the global data structure
         */
        pUSBDrvObj->drvUSBHostSWEp[numSWEpEntry].tobeDone = true;
        pUSBDrvObj->drvUSBHostSWEp[numSWEpEntry].transferType = transferType;
        pUSBDrvObj->drvUSBHostSWEp[numSWEpEntry].pIRP = ptransferIRP;
        irpPacked = true;
    }
    return irpPacked;

}/* end of _DRV_USB_HOST_CalculateControlBW() */

// *****************************************************************************
/* Function:
    bool _DRV_USB_HOST_TransferSchedule
    (
        DRV_USB_OBJ * pUSBDrvObj,
        DRV_USB_TRANSACTION_RESULT lastResult,
        unsigned int transactionSize,
        bool frameExpiry
    )

  Summary:
    Dynamic implementation of _DRV_USB_HOST_TransferSchedule internal function.

  Description:
    This is the dynamic implementation of _DRV_USB_HOST_TransferSchedule
    function. Function performs the following task:
    - Prepares the SW EP buffer with the transfer details that will be
      processed in the frame
    - Processes the SW EP buffer object that can be done in frame

  Remarks:
    This is a local function and should not be called directly by the
    application.
*/

bool _DRV_USB_HOST_TransferSchedule
(
    DRV_USB_OBJ * pUSBDrvObj,
    DRV_USB_TRANSACTION_RESULT lastResult,
    unsigned int transactionSize,
    bool frameExpiry
)
{
    /* Start of local variable */
    DRV_USB_HOST_TRANSFER_GROUP * pTransferGroup = (DRV_USB_HOST_TRANSFER_GROUP *)NULL;
    DRV_USB_HOST_PIPE_OBJ * piteratorPipe        = (DRV_USB_HOST_PIPE_OBJ *)NULL;
    USB_HOST_IRP_LOCAL * pControlIRP             = (USB_HOST_IRP_LOCAL *)NULL;
    USB_HOST_IRP_LOCAL * pbulkIRP                = (USB_HOST_IRP_LOCAL *)NULL;
    USB_HOST_IRP_LOCAL * pinterruptIRP           = (USB_HOST_IRP_LOCAL *)NULL;
    USB_HOST_IRP_LOCAL * pisochronousIRP         = (USB_HOST_IRP_LOCAL *)NULL;
    uint8_t numSWEpEntry                         = 0;
    uint8_t numIRPProcess                        = 0;
    bool tokenSent                               = false;
    bool irpPacked                               = false;
    /* End of local variable */

    if(lastResult == 0)
    {
        /* This means that a transfer has completed and we are not continuing a
         * transfer. */

        if(frameExpiry)
        {
            /* This means the frame duration has completed. This will only
             * happen when this function is called from a SOF event. Clear all
             * the NON CONTROL IRPs which may be still there from the previous
             * frame even if they not completed. A control transfer that was in
             * progress will be allowed to continue. Note how the numSWEpEntry
             * index in the loop below starts with 1 and 0. 0 index is always
             * allocated for control transfers. */

            for(numSWEpEntry = 1; numSWEpEntry < _DRV_USB_SW_EP_NUMBER; numSWEpEntry++)
            {
                /* Clearing the tobeDone flags will indicate that all the
                 * transfers scheduled on these software endpoints needs to be
                 * re-scheduled. */
                pUSBDrvObj->drvUSBHostSWEp[numSWEpEntry].tobeDone = false;
            }

            /* Reset the frame bandwidth consumed number */
            pUSBDrvObj->globalBWConsumed = 0;
            numSWEpEntry = 0;

            /* Process the Control pipes first */
            pTransferGroup = &pUSBDrvObj->transferGroup[USB_TRANSFER_TYPE_CONTROL];

            /* Current pipe (the pipe that was processed last) will be head
             * pipe.  After that it will rotate through the Control pipe linked
             * list */

            if(pTransferGroup->pipe != NULL)
            {
                if(pUSBDrvObj->drvUSBHostSWEp[0].tobeDone == true)
                {
                    /* Transfer continuation from last frame. We only need to
                     * update the bandwidth based on the control transfer
                     * packet size. */
                    pTransferGroup->currentIRP = (pTransferGroup->currentPipe)->irpQueueHead;
                    pControlIRP = pTransferGroup->currentIRP;
                    _DRV_USB_HOST_CalculateControlBW(pUSBDrvObj, pTransferGroup, pControlIRP);
                }
                else
                {
                    /* Fresh Transfer starting this frame */
                }

                /* Search for a control transfer to schedule till we have an IRP
                 * to process or till we have run out of control transfer pipes
                 * */

                while(pUSBDrvObj->drvUSBHostSWEp[0].tobeDone == false)
                {
                    /* Fresh Transfer starting this frame */
                    pTransferGroup->currentIRP = (pTransferGroup->currentPipe)->irpQueueHead;
                    pControlIRP = pTransferGroup->currentIRP;

                    if((pControlIRP != NULL) && (numIRPProcess < DRV_USB_HOST_IRP_PER_FRAME_NUMBER))
                    {
                        _DRV_USB_HOST_CalculateControlBW(pUSBDrvObj, pTransferGroup, pControlIRP);
                    }

                    if(pUSBDrvObj->drvUSBHostSWEp[0].tobeDone == false)
                    {
                        /* There was no CONTROL IRP in the last pipe.  */
                        if((pTransferGroup->currentPipe)->next != NULL)
                        {
                            /* This is not the last PIPE */
                            pTransferGroup->currentPipe = (pTransferGroup->currentPipe)->next;
                        }
                        else
                        {
                            /* This is the last PIPE. Move to the head pipe */
                            pTransferGroup->currentPipe = pTransferGroup->pipe;
                            break;
                        }
                    }
                }/* end of while() */
                if(pUSBDrvObj->drvUSBHostSWEp[0].tobeDone == true)
                {
                    numIRPProcess++;
                }
            }/* end of if(CONTROL PIPE present)*/

            /* Set it to 1 as isochronous may not be there in the frame */
            numSWEpEntry = 1;

            pTransferGroup =
                &pUSBDrvObj->transferGroup[USB_TRANSFER_TYPE_ISOCHRONOUS];
            piteratorPipe = pTransferGroup->pipe;

            if(piteratorPipe != NULL)
            {
                /* Decrement the interval counter for all isochronous pipes */
                do
                {
                    if(piteratorPipe->intervalCounter != 0)
                    {
                        piteratorPipe->intervalCounter--;
                    }
                    else
                    {
                        /* Reinitialize the counter on expiry */
                        piteratorPipe->intervalCounter =
                            piteratorPipe->bInterval;
                    }
                    piteratorPipe = piteratorPipe->next;

                } while(piteratorPipe != NULL);


                pTransferGroup->currentIRP =
                    pTransferGroup->currentPipe->irpQueueHead;
                pisochronousIRP = pTransferGroup->currentIRP;
                piteratorPipe = pTransferGroup->currentPipe;

                while((numSWEpEntry < _DRV_USB_SW_EP_NUMBER) &&
                        (numIRPProcess < DRV_USB_HOST_IRP_PER_FRAME_NUMBER))
                {
                    irpPacked = false;
                    /* Check for IRP with an expired interval */
                    if((pisochronousIRP != NULL) &&
                            (piteratorPipe->intervalCounter == 0))
                    {
                        /* Check BW and pack IRP */
                        irpPacked =
                            _DRV_USB_HOST_CalculateNonControlBW(pUSBDrvObj,
                                    pTransferGroup,pisochronousIRP,
                                    USB_TRANSFER_TYPE_ISOCHRONOUS,numSWEpEntry);
                        if(irpPacked == true)
                        {
                            pTransferGroup->currentPipe = piteratorPipe;
                            /* Increment the IRP counter */
                            numIRPProcess++;
                            /* Increment SWEP index */
                            numSWEpEntry++;
                            /*
                             * IRP has been packed for this frame.
                             * Now move Current Pipe to next pipe, so that
                             * in the next frame the processing will start
                             * from this pipe.
                             */
                            if(pTransferGroup->currentPipe->next != NULL)
                            {
                                pTransferGroup->currentPipe =
                                    pTransferGroup->currentPipe->next;
                            }
                            else
                            {
                                /*
                                 * This is the last pipe in the list
                                 * Rotate back to the head pipe.
                                 */
                                pTransferGroup->currentPipe =
                                    pTransferGroup->pipe;
                            }
                        }/* end of(if IRP PACKED)*/
                    }
                    /*
                     * irpPacked will be false in below scenarios:
                     *     - there is no IRP to be processed in the pipe
                     *     - irp from the pipe cannot be processed due to
                     *       BW availability issue
                     */
                    if(irpPacked == false)
                    {
                        /* Move to the next pipe.
                         * Note: Current pipe has NOT been moved.
                         * It will be moved only if IRP has been packed
                         * from the pipe.
                         */
                        piteratorPipe = piteratorPipe->next;
                        if(piteratorPipe == NULL)
                        {
                            /* End of pipe. Move to head pipe */
                            piteratorPipe = pTransferGroup->pipe;
                            pTransferGroup->currentPipe = piteratorPipe;
                        }
                    }
                    else
                    {
                        /* No need to move ahead here. Already done before */
                        piteratorPipe = pTransferGroup->currentPipe;
                    }
                    if(piteratorPipe == pTransferGroup->pipe)
                    {
                        /* Reached the beginning of the ISOC pipe */
                        break;
                    }
                    pisochronousIRP = piteratorPipe->irpQueueHead;
                }/* end of while() */
            }/* end of if(ISOCHRONOUS PIPE present) */

            pTransferGroup =
                &pUSBDrvObj->transferGroup[USB_TRANSFER_TYPE_INTERRUPT];
            piteratorPipe = pTransferGroup->pipe;

            if(piteratorPipe != NULL)
            {
                /* Decrement the interval counter for all isochronous pipes */
                do
                {
                    if(piteratorPipe->intervalCounter != 0)
                    {
                        piteratorPipe->intervalCounter--;
                    }
                    else
                    {
                        /* Reinitialize the counter on expiry */
                        piteratorPipe->intervalCounter =
                            piteratorPipe->bInterval;
                    }
                    piteratorPipe = piteratorPipe->next;

                } while(piteratorPipe != NULL);


                pTransferGroup->currentIRP =
                    pTransferGroup->currentPipe->irpQueueHead;
                pinterruptIRP = pTransferGroup->currentIRP;
                piteratorPipe = pTransferGroup->currentPipe;

                while((numSWEpEntry < _DRV_USB_SW_EP_NUMBER) &&
                        (numIRPProcess < DRV_USB_HOST_IRP_PER_FRAME_NUMBER))
                {
                    irpPacked = false;
                    /* Check for IRP with an expired interval */
                    if((pinterruptIRP != NULL) &&
                            (piteratorPipe->intervalCounter == 0))
                    {
                        /* Check BW and pack IRP */
                        irpPacked =
                            _DRV_USB_HOST_CalculateNonControlBW(pUSBDrvObj,
                                    pTransferGroup,pinterruptIRP,
                                    USB_TRANSFER_TYPE_INTERRUPT,numSWEpEntry);
                        if(irpPacked == true)
                        {
                            pTransferGroup->currentPipe = piteratorPipe;
                            /* Increment the IRP counter */
                            numIRPProcess++;
                            /* Increment SWEP index */
                            numSWEpEntry++;
                            /*
                             * IRP has been packed for this frame.
                             * Now move Current Pipe to next pipe, so that
                             * in the next frame the processing will start
                             * from this pipe.
                             */
                            if(pTransferGroup->currentPipe->next != NULL)
                            {
                                pTransferGroup->currentPipe =
                                    pTransferGroup->currentPipe->next;
                            }
                            else
                            {
                                /*
                                 * This is the last pipe in the list
                                 * Rotate back to the head pipe.
                                 */
                                pTransferGroup->currentPipe =
                                    pTransferGroup->pipe;
                            }
                        }/* end of(if IRP PACKED)*/
                    }
                    /*
                     * irpPacked will be false in below scenarios:
                     *     - there is no IRP to be processed in the pipe
                     *     - irp from the pipe cannot be processed due to
                     *       BW availability issue
                     */
                    if(irpPacked == false)
                    {
                        /* Move to the next pipe.
                         * Note: Current pipe has NOT been moved.
                         * It will be moved only if IRP has been packed
                         * from the pipe.
                         */
                        piteratorPipe = piteratorPipe->next;
                        if(piteratorPipe == NULL)
                        {
                            /* End of pipe. Move to head pipe */
                            piteratorPipe = pTransferGroup->pipe;
                            pTransferGroup->currentPipe = piteratorPipe;
                        }
                    }
                    else
                    {
                        /* No need to move ahead here. Already done before */
                        piteratorPipe = pTransferGroup->currentPipe;
                    }
                    if(piteratorPipe == pTransferGroup->pipe)
                    {
                        /* Reached the beginning of the ISOC pipe */
                        break;
                    }
                    pinterruptIRP = piteratorPipe->irpQueueHead;
                }/* end of while() */
            }/* end of if(INTERRUPT PIPE present) */

            /* SW EP processing for BULK transfer */
            pTransferGroup = &pUSBDrvObj->transferGroup[USB_TRANSFER_TYPE_BULK];
            if(pTransferGroup->pipe != NULL)
            {
                pTransferGroup->currentIRP =
                    pTransferGroup->currentPipe->irpQueueHead;
                pbulkIRP = pTransferGroup->currentIRP;
                piteratorPipe = pTransferGroup->currentPipe;

                while((numSWEpEntry < _DRV_USB_SW_EP_NUMBER) &&
                        (numIRPProcess < DRV_USB_HOST_IRP_PER_FRAME_NUMBER))
                {
                    irpPacked = false;
                    if(pbulkIRP != NULL)
                    {
                        /* Check BW and pack IRP */
                        irpPacked =
                            _DRV_USB_HOST_CalculateNonControlBW(pUSBDrvObj,
                                    pTransferGroup,pbulkIRP,USB_TRANSFER_TYPE_BULK,
                                    numSWEpEntry);
                        if(irpPacked == true)
                        {
                            pTransferGroup->currentPipe = piteratorPipe;
                            /* Increment the IRP counter */
                            numIRPProcess++;
                            /* Increment SWEP index */
                            numSWEpEntry++;
                            /*
                             * IRP has been packed for this frame.
                             * Now move Current Pipe to next pipe, so that
                             * in the next frame the processing will start
                             * from this pipe.
                             */
                            if(pTransferGroup->currentPipe->next != NULL)
                            {
                                pTransferGroup->currentPipe =
                                    pTransferGroup->currentPipe->next;
                            }
                            else
                            {
                                /*
                                 * This is the last pipe in the list
                                 * Rotate back to the head pipe.
                                 */
                                pTransferGroup->currentPipe =
                                    pTransferGroup->pipe;
                            }
                        }
                    }
                    /*
                     * irpPacked will be false in below scenarios:
                     *     - there is no IRP to be processed in the pipe
                     *     - irp from the pipe cannot be processed due to
                     *       BW availability issue 
                     */
                    if(irpPacked == false)
                    {
                        /* Move to the next pipe. 
                         * Note: Current pipe has NOT been moved.
                         * It will be moved only if IRP has been packed
                         * from the pipe.
                         */
                        piteratorPipe = piteratorPipe->next;
                        if(piteratorPipe == NULL)
                        {
                            /* End of pipe. Move to head pipe */
                            piteratorPipe = pTransferGroup->pipe;
                            pTransferGroup->currentPipe = piteratorPipe;
                        }
                    }
                    else
                    {
                        /* No need to move ahead here. Already done before */
                        piteratorPipe = pTransferGroup->currentPipe;
                    }
                    if(piteratorPipe == pTransferGroup->pipe)
                    {
                        /* Reached the beginning of the BULK pipe */
                        break;
                    }
                    pbulkIRP = piteratorPipe->irpQueueHead;
                }/* end of while() */
            }/* if(BULK PIPE present) */
            numSWEpEntry = 0;
        }/* end of if(FRAME EXPIRY)*/
        else
        {
            if((pUSBDrvObj->numSWEpEntry + 1) < _DRV_USB_SW_EP_NUMBER)
            {
                numSWEpEntry = pUSBDrvObj->numSWEpEntry + 1;
            }
            else
            {
                return false;
            }
        }

        /* Call appropriate transfer function to process */
        for(;numSWEpEntry < _DRV_USB_SW_EP_NUMBER;
                numSWEpEntry++)
        {
            if((pUSBDrvObj->drvUSBHostSWEp[numSWEpEntry].tobeDone) == true)
            {
                if(pUSBDrvObj->drvUSBHostSWEp[numSWEpEntry].transferType
                        == USB_TRANSFER_TYPE_CONTROL) 
                {
                    /* Control transfer */
                    pUSBDrvObj->numSWEpEntry = numSWEpEntry;
                    tokenSent = _DRV_USB_HOST_ControlXferProcess(
                            pUSBDrvObj,
                            pUSBDrvObj->drvUSBHostSWEp[numSWEpEntry].pIRP,
                            (DRV_USB_TRANSACTION_RESULT) 0,
                            0
                            );

                }
                else if((pUSBDrvObj->drvUSBHostSWEp[numSWEpEntry].transferType
                            == USB_TRANSFER_TYPE_ISOCHRONOUS) ||
                        (pUSBDrvObj->drvUSBHostSWEp[numSWEpEntry].transferType
                         == USB_TRANSFER_TYPE_INTERRUPT) ||
                        (pUSBDrvObj->drvUSBHostSWEp[numSWEpEntry].transferType
                         == USB_TRANSFER_TYPE_BULK))
                {
                    if((pUSBDrvObj->drvUSBHostSWEp[numSWEpEntry].tobeDone
                                == true))
                    {
                        pUSBDrvObj->numSWEpEntry = numSWEpEntry;
                        tokenSent = _DRV_USB_HOST_NonControlIRPProcess(
                                pUSBDrvObj,
                                pUSBDrvObj->drvUSBHostSWEp[numSWEpEntry].pIRP,
                                (DRV_USB_TRANSACTION_RESULT) 0,
                                0
                                );
                    }
                }
                else
                {
                    SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "error IRP schedule");
                }
                break;	
            }/* end of if(tobedone)*/
        }/* end of for() loop */
    }/* end of if(last transaction is 0)*/
    else
    {
        if(pUSBDrvObj->numSWEpEntry == 0)
        {
            /* The last scheduled in this frame was CONTROL */
            /* Control transfer */
            tokenSent = _DRV_USB_HOST_ControlXferProcess(
                    pUSBDrvObj,
                    pUSBDrvObj->drvUSBHostSWEp[pUSBDrvObj->numSWEpEntry].pIRP,
                    (DRV_USB_TRANSACTION_RESULT) lastResult,
                    transactionSize
                    );
        }
        else
        {
            if((pUSBDrvObj->drvUSBHostSWEp[pUSBDrvObj->numSWEpEntry].tobeDone
                        == true))
            {
                /* Last scheduled was Isochronous, interrupt or BULK transfer */
                tokenSent = _DRV_USB_HOST_NonControlIRPProcess(
                        pUSBDrvObj,
                        pUSBDrvObj->drvUSBHostSWEp[pUSBDrvObj->numSWEpEntry].pIRP,
                        (DRV_USB_TRANSACTION_RESULT) lastResult,
                        transactionSize
                        );
            }
        }
    }

    return tokenSent;

}/* end of _DRV_USB_HOST_TransferSchedule()*/

// *****************************************************************************
/* Function:
    void _DRV_USB_HOST_Tasks_ISR(DRV_USB_OBJ * pUSBDrvObj)

  Summary:
    Dynamic implementation of _DRV_USB_HOST_Tasks_ISR function.

  Description:
    This is the dynamic implementation of _DRV_USB_HOST_Tasks_ISR
    internal function. Function is an interrupt handler which does
    necessary processing based on the interrupt.

  Remarks:

*/

void _DRV_USB_HOST_Tasks_ISR(DRV_USB_OBJ * pUSBDrvObj)
{
    /* Start of local variables */
    void                    *peventData = NULL;
    DRV_USB_BDT_ENTRY       *pBDTEntry = (DRV_USB_BDT_ENTRY *) NULL;
    bool                    bDoEventCallBack = false;;
    bool                    tokenWasSent = false;
    uint8_t                 lastEndpoint = 0;
    uint8_t                 swEpCount = 0;
    unsigned int            transactionSize = 0;
    USB_MODULE_ID           usbID;
    DRV_USB_EVENT           eventType = 0;
    USB_INTERRUPTS          usbInterrupts = 0;
    USB_INTERRUPTS          enabledUSBInterrupts = 0;
    USB_INTERRUPTS          clearUSBInterrupts = 0;
    USB_PING_PONG_STATE     lastPingPong = 0;
    USB_BUFFER_DIRECTION    lastDirection = 0;
    DRV_USB_TRANSACTION_RESULT  transactionResult = 0;
    /* End of local variables */

    usbID = pUSBDrvObj->usbID;

    usbInterrupts = PLIB_USB_InterruptFlagAllGet(usbID);

    enabledUSBInterrupts = PLIB_USB_InterruptEnableGet(usbID);

    /* Check if an error has occurred */
    if (( usbInterrupts & USB_INT_ERROR ) &&
            (enabledUSBInterrupts & USB_INT_ERROR))
    { 
        USB_ERROR_INTERRUPTS errorType;

        eventType = DRV_USB_EVENT_ERROR;
        bDoEventCallBack = true;

        errorType = PLIB_USB_ErrorInterruptFlagAllGet(usbID); 

        /* Clear the errors */
        PLIB_USB_ErrorInterruptFlagClear( usbID, errorType ); 

        /* Clear the error flag */
        PLIB_USB_InterruptFlagClear( usbID, USB_INT_ERROR ); 

        /* Set the event data */

    }


    else if (( usbInterrupts & USB_INT_SOF ) &&
            (enabledUSBInterrupts & USB_INT_SOF))
    { 
        /* SOF threshold reached by Host. Call the
         * transaction scheduler so that we schedule
         * the next set of transfers */

        bDoEventCallBack = true;
        eventType = DRV_USB_EVENT_SOF_DETECT;
        clearUSBInterrupts = USB_INT_SOF;

        /* Call the transfer scheduler */
        _DRV_USB_HOST_TransferSchedule(pUSBDrvObj,
                (DRV_USB_TRANSACTION_RESULT)0,
                (unsigned int)0,
                true);
    }

    else if ((usbInterrupts & USB_INT_STALL) &&
            (enabledUSBInterrupts & USB_INT_STALL))
    {
        /* The device stalled the request. At this 
         * point we don't know yet what to do with this
         * interrupt. Clearing the flag for now */
        clearUSBInterrupts = USB_INT_STALL;
    }

    else if((usbInterrupts & USB_INT_RESUME) &&
            (enabledUSBInterrupts & USB_INT_RESUME))
    {
        /* Device sent resume signalling to the
         * host */

        bDoEventCallBack = true;
        eventType = DRV_USB_EVENT_RESUME_DETECT;
        clearUSBInterrupts = USB_INT_RESUME;
    }

    else if ((usbInterrupts & USB_INT_IDLE_DETECT)
            && (enabledUSBInterrupts & USB_INT_IDLE_DETECT))
    {
        bDoEventCallBack = true;
        eventType = DRV_USB_EVENT_IDLE_DETECT;
        clearUSBInterrupts = USB_INT_IDLE_DETECT;
    }

    else if ((usbInterrupts & USB_INT_ATTACH) && 
            (enabledUSBInterrupts & USB_INT_ATTACH))
    {
        /* Host got a device attach */
        bDoEventCallBack = true;
        eventType = DRV_USB_EVENT_HOST_ATTACH;
        clearUSBInterrupts = USB_INT_ATTACH;

        /* The attach interrupt is persistent.
         * Clearing it will not have any effect
         * It must be disabled and enabled
         * again when a detach is received */

        PLIB_USB_InterruptDisable(usbID, USB_INT_ATTACH);

        /* We also clear and enable the detach interrupt */
        PLIB_USB_InterruptFlagClear(usbID, USB_INT_HOST_DETACH);
        PLIB_USB_InterruptEnable(usbID, USB_INT_HOST_DETACH);

        /* Check if the device speed is low speed and update the driver
         * structure */

        /* Enable the transaction interrupt */
        PLIB_USB_InterruptEnable(usbID, USB_INT_TOKEN_DONE);

    }
    else if((usbInterrupts & USB_INT_HOST_DETACH)
            && (enabledUSBInterrupts & USB_INT_HOST_DETACH))
    {
        /* Host got a device detach */

        bDoEventCallBack = true;
        eventType = DRV_USB_EVENT_HOST_DETACH;
        clearUSBInterrupts = USB_INT_HOST_DETACH;

        /* The detach interrupt is persistent.  Clearing it will not have any
         * effect It must be disabled and enabled again when a attach is
         * received */

        PLIB_USB_InterruptDisable(usbID, USB_INT_HOST_DETACH);

        /* We disable the token done interrupt. This will prevent the control
         * transfer process and the non control transfer process from getting a
         * null irp to process. We then clear the interrupt. To clear the token
         * interrupt, the stat register should be read once. */

        PLIB_USB_InterruptDisable(usbID, USB_INT_TOKEN_DONE);
        PLIB_USB_LastTransactionDetailsGet(usbID, &lastDirection,
                &lastPingPong, &lastEndpoint );
        PLIB_USB_InterruptFlagClear(usbID, USB_INT_TOKEN_DONE);

        /* Clear up all the endpoint 0 BDT entries.*/
        pUSBDrvObj->pBDT[0].word[0] = 0x0;
        pUSBDrvObj->pBDT[0].word[1] = 0x0;
        pUSBDrvObj->pBDT[1].word[0] = 0x0;
        pUSBDrvObj->pBDT[1].word[1] = 0x0;
        pUSBDrvObj->pBDT[2].word[0] = 0x0;
        pUSBDrvObj->pBDT[2].word[1] = 0x0;
        pUSBDrvObj->pBDT[3].word[0] = 0x0;
        pUSBDrvObj->pBDT[3].word[1] = 0x0;

        /* Un-initialize the SWEP data structure */
        for(swEpCount = 0; swEpCount < _DRV_USB_SW_EP_NUMBER; swEpCount++)
        {
            pUSBDrvObj->drvUSBHostSWEp[swEpCount].tobeDone = false;
        }

        /* We also clear and enable the attach interrupt */
        PLIB_USB_InterruptFlagClear(usbID, USB_INT_ATTACH);
        PLIB_USB_InterruptEnable(usbID, USB_INT_ATTACH);

    }


    /* Send all the above events to all the clients */
    if(bDoEventCallBack)
    {
        /* Clear the flag for the next time */

        bDoEventCallBack = false;

        /* The driver events are passed only to client 0 which is the host
         * layer. Check if the client has a valid callback */

        if(pUSBDrvObj->pEventCallBack != NULL)
        {
            /**************************************************************
             * Client call back. Since the HCD can have only one client, we
             * will not loop through a table of client. Client 0 is the host
             * layer.
             ***************************************************************/

            pUSBDrvObj->pEventCallBack(pUSBDrvObj->hClientArg, eventType,  peventData);
        }
    }

    /* Clear interrupts flags */
    PLIB_USB_InterruptFlagClear( usbID, clearUSBInterrupts );

    /* Now check if the token was completed */
    if(PLIB_USB_InterruptFlagGet(usbID, USB_INT_TOKEN_DONE) 
            && ((enabledUSBInterrupts & USB_INT_TOKEN_DONE) != 0))
    {
        /* Get the last transaction status */
        PLIB_USB_LastTransactionDetailsGet(usbID, &lastDirection, &lastPingPong, &lastEndpoint );

        /* Clear the flag */
        PLIB_USB_InterruptFlagClear(usbID,USB_INT_TOKEN_DONE);

        /* Get the result of the last transaction */

        pBDTEntry = pUSBDrvObj->pBDT + (lastDirection << 1) + lastPingPong;
        transactionResult = (pBDTEntry->byte[0] & 0x3C) >> 2;
        transactionSize = pBDTEntry->shortWord[1];

        if(lastDirection == USB_BUFFER_RX)
        {
            /* Update the RX ping pong buffer indicator */
            pUSBDrvObj->ep0RxPingPong ^= 0x1;
        }
        else
        {
            /* Update the even ping pong buffer indicator */
            pUSBDrvObj->ep0TxPingPong ^= 0x1;
        }

        /* The _DRV_USB_HOST_TransferSchedule function will check for the
         * available bandwidth in this frame and will update the current
         * transfer. The return value will be true if the function sent a token.
         * */
        tokenWasSent = _DRV_USB_HOST_TransferSchedule(pUSBDrvObj, transactionResult, transactionSize, false);

        if(tokenWasSent == false)
        {
            /* This means the transfer that caused this interrupt is completed.
             * We call the _DRV_USB_HOST_TransferSchedule() function with last
             * transaction result and lastTransactionsize as 0. This lets the
             * function know that it must try to schedule a new transfer.
             * Note: No more than 1 IRP when isochronous IRP is present in 1 frame */

            _DRV_USB_HOST_TransferSchedule(pUSBDrvObj, (DRV_USB_TRANSACTION_RESULT)0, (unsigned int)0, false);
        }
    }
}/* end of _DRV_USB_HOST_Tasks_ISR() */

// *****************************************************************************
/* Function:
    void DRV_USB_HOST_BusResetControl
    (
        DRV_HANDLE handle,
        bool control
    )

  Summary:
    Dynamic implementation of DRV_USB_HOST_BusResetControl function.

  Description:
    This is the dynamic implementation of DRV_USB_HOST_BusResetControl
    internal function. Function is used to enable or disable USB BUS RESET
    signal.

  Remarks:
    Refer to drv_usb.h for usage information.
*/

void DRV_USB_HOST_BusResetControl(DRV_HANDLE handle, bool control)
{
    /* Start of local variables */
    DRV_USB_OBJ * pUSBDrvObj = (DRV_USB_OBJ *)handle;
    /* End of local variables */
    
    /* If control is true, then enable reset */
    if(control == true)
    {
        PLIB_USB_ResetSignalEnable(pUSBDrvObj->usbID);
        /* After the reset is activated, we can find out if the J state is
         * active, which means that the D- line is pulled up and hence this a
         * low speed device.
         */
        if(!PLIB_USB_JStateIsActive(pUSBDrvObj->usbID))
        {
            /* This means that low speed device was attached. All tokens should
             * be executed at low speed. Also enable direct connection to LS
             * speed bit in the EP0 control register.  */

            pUSBDrvObj->deviceSpeed = USB_SPEED_LOW;
            PLIB_USB_TokenSpeedSelect(pUSBDrvObj->usbID, USB_LOWSPEED_TOKENS);
            PLIB_USB_EP0LSDirectConnectEnable(pUSBDrvObj->usbID);
        }
        else
        {
            pUSBDrvObj->deviceSpeed = USB_SPEED_FULL;
            PLIB_USB_TokenSpeedSelect(pUSBDrvObj->usbID, USB_FULLSPEED_TOKENS);
            PLIB_USB_EP0LSDirectConnectDisable(pUSBDrvObj->usbID);
        }
    }
    else
    {
        PLIB_USB_ResetSignalDisable(pUSBDrvObj->usbID);
    }

}/* end of DRV_USB_HOST_BusResetControl() */

// *****************************************************************************
/* Function:
    USB_SPEED DRV_USB_HOST_DeviceCurrentSpeedGet(DRV_HANDLE handle)

  Summary:
    Dynamic implementation of DRV_USB_HOST_DeviceCurrentSpeedGet function.

  Description:
    This is the dynamic implementation of DRV_USB_HOST_DeviceCurrentSpeedGet
    client interface function. Function returns the usb speed on success.

  Remarks:
    Refer to drv_usb.h for usage information.
*/

USB_SPEED DRV_USB_HOST_DeviceCurrentSpeedGet(DRV_HANDLE handle)
{
    /* Start of local variables */
    DRV_USB_OBJ * pUSBDrvObj = (DRV_USB_OBJ *)handle;
    USB_SPEED returnValue = USB_SPEED_ERROR;
    /* End of local variables */

    /* Check if the handle is valid or opened */
    if((handle == DRV_HANDLE_INVALID) || (!(pUSBDrvObj->isOpened)))
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Bad Client or client closed");
    }
    else
    {
        /* Map the USB HW instance from client
         * and get the device speed
         */
        returnValue = pUSBDrvObj->deviceSpeed;
    }
    
    return returnValue;

}/* end of DRV_USB_HOST_DeviceCurrentSpeedGet() */

// *****************************************************************************
/* Function:
    void DRV_USB_HOST_OperationEnable(DRV_HANDLE handle, bool enable)


  Summary:
    Dynamic implementation of DRV_USB_HOST_OperationEnable function.

  Description:
    This is the dynamic implementation of DRV_USB_HOST_OperationEnable client
    interface function. Function enables\disables the USB Host operation as per
    enable value 1 and 0 respectively.

  Remarks:
    Refer to drv_usb.h for usage information.

*/

void DRV_USB_HOST_OperationEnable(DRV_HANDLE handle, bool enable)
{
    /* Start of local variable */
    DRV_USB_OBJ * pUSBDrvObj = (DRV_USB_OBJ *)handle;
    /* End of local variable */

    /* Check if the handle is valid or opened */
    if((handle == DRV_HANDLE_INVALID) ||
            (!(pUSBDrvObj->isOpened)))
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Bad Client or client closed");
    }
    else
    {
        if(true == enable)
        {
            /* Interrupt flag cleared on the safer side */
            SYS_INT_SourceStatusClear(pUSBDrvObj->interruptSource);

            if(DRV_USB_INTERRUPT_MODE)
            {
                /* If interrupt mode is set then enable interrupts
                 * Interrupt priority will be set by the application
                 */
                SYS_INT_SourceEnable(pUSBDrvObj->interruptSource);
            }
            /* Enable the attach interrupt */
            PLIB_USB_InterruptEnable(pUSBDrvObj->usbID, USB_INT_ATTACH);

            pUSBDrvObj->driverFlags |= DRV_USB_FLAG_HOST_MODE_ENABLED;
            /* Enable the USB module */
            PLIB_USB_Enable(pUSBDrvObj->usbID);
        }
        else
        {
            SYS_INT_SourceStatusClear(pUSBDrvObj->interruptSource);
            pUSBDrvObj->driverFlags &= ~DRV_USB_FLAG_HOST_MODE_ENABLED;
            /* Disable the USB module */
            PLIB_USB_Disable(pUSBDrvObj->usbID);
        }
    }

}/* end of DRV_USB_HOST_OperationEnable() */

// *****************************************************************************
/* Function:
    void DRV_USB_HOST_OperationEnable(DRV_HANDLE handle, bool enable)

  Summary:
    Dynamic implementation of DRV_USB_HOST_OperationIsEnabled function.

  Description:
    This is the dynamic implementation of DRV_USB_HOST_OperationIsEnabled
    client interface function. Function returns true or false based on
    USB Host module is enabled or not respectively.

  Remarks:
    Refer to drv_usb.h for usage information.

*/

bool DRV_USB_HOST_OperationIsEnabled(DRV_HANDLE handle)
{
    /* Start of local variable */
    DRV_USB_OBJ * pUSBDrvObj = (DRV_USB_OBJ *)handle;
    bool returnValue = false;
    /* End of local variable */

    /* Check if the handle is valid or opened */
    if((handle == DRV_HANDLE_INVALID) || (!(pUSBDrvObj->isOpened)))
    {
        SYS_DEBUG_MESSAGE(SYS_ERROR_INFO, "Bad Client or client closed");
    }
    else
    {
        returnValue = (pUSBDrvObj->driverFlags & DRV_USB_FLAG_HOST_MODE_ENABLED) ? true : false;
    }

    return returnValue;

}/* end of DRV_USB_HOST_OperationIsEnabled() */
