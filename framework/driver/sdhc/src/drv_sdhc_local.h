/*******************************************************************************
  SD Host Controller Driver Local Data Structures

  Company:
    Microchip Technology Inc.

  File Name:
    drv_sdhc_local.h

  Summary:
    SD Host Controller driver local declarations, structures and function prototypes.

  Description:
    This file contains the SD Host Controller driver's local declarations and definitions.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END

#ifndef _DRV_SDHC_LOCAL_H
#define _DRV_SDHC_LOCAL_H


// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "driver/sdhc/drv_sdhc.h"
#include "driver/sdhc/src/drv_sdhc_host.h"
#include "driver/sdhc/src/drv_sdhc_variant_mapping.h"
#include "osal/osal.h"

// *****************************************************************************
// *****************************************************************************
// Section: Helper Macros
// *****************************************************************************
// *****************************************************************************
/* Helper macros for the driver */

// *****************************************************************************
/* SDHC Driver Buffer Handle Macros

  Summary:
    SDHC driver Buffer Handle Macros

  Description:
    Buffer handle related utility macros. SDHC driver buffer handle is a 
    combination of buffer token and the buffer object index. The buffertoken
    is a 16 bit number that is incremented for every new write or erase request
    and is used along with the buffer object index to generate a new buffer 
    handle for every request.

  Remarks:
    None
*/

#define DRV_SDHC_BUF_TOKEN_MAX         (0xFFFF)
#define DRV_SDHC_MAKE_HANDLE(token, index) ((token) << 16 | (index))
#define DRV_SDHC_UPDATE_BUF_TOKEN(token) \
{ \
    (token)++; \
    (token) = ((token) == DRV_SDHC_BUF_TOKEN_MAX) ? 0: (token); \
}

#define DRV_SDHC_COMMAND_STATUS_SUCCESS         0x00
#define DRV_SDHC_COMMAND_STATUS_ERROR           0x01
#define DRV_SDHC_COMMAND_STATUS_TIMEOUT_ERROR   0x02
#define DRV_SDHC_COMMAND_STATUS_CRC_ERROR       0x03 

#define DRV_SDHC_COMMAND_TIMEOUT_ERROR          0x01
#define DRV_SDHC_COMMAND_CRC_ERROR              0x02
#define DRV_SDHC_COMMAND_END_BIT_ERROR          0x04
#define DRV_SDHC_COMMAND_INDEX_ERROR            0x08

// *****************************************************************************
/* SDHC Read/Write/Erase Region Index Numbers

  Summary:
    SDHC Geometry Table Index definitions.

  Description:
    These constants provide SDHC Geometry Table index definitions.

  Remarks:
    None
*/
#define GEOMETRY_TABLE_READ_ENTRY   (0)
#define GEOMETRY_TABLE_WRITE_ENTRY  (1)
#define GEOMETRY_TABLE_ERASE_ENTRY  (2)

// *****************************************************************************
// *****************************************************************************
// Section: SD Host Controller constants
// *****************************************************************************
// *****************************************************************************
/* Constants used by SD card driver */

// *****************************************************************************
/* SD Host Controller connection states

  Summary:
    Lists SD card physical connection states

  Description:
    This enumeration lists different SD card physical connection states.

  Remarks:
    None.
*/

typedef enum
{
    /* SD Host Controller is attached from the system */
    DRV_SDHC_IS_DETACHED,

    /* SD Host Controller is attached to the system */
    DRV_SDHC_IS_ATTACHED

}DRV_SDHC_ATTACH;

// *****************************************************************************
/* SD Host Controller transfer type

  Summary:
    Specifies whether the SD card transfer is read or write.

  Description:
    This enumeration holds constants to specify whether the SD card transfer
    is read or write.

  Remarks:
    None.
*/

typedef enum
{
    /* SD card transfer is read from the card */
    DRV_SDHC_OPERATION_TYPE_READ,

   /* SD card transfer is write to the card */
    DRV_SDHC_OPERATION_TYPE_WRITE,

}DRV_SDHC_OPERATION_TYPE;

// *****************************************************************************
/* SD Host Controller commands

  Summary:
    Lists different commands supported by the SD card.

  Description:
    This enumeration lists different commands supported by the SD card

  Remarks:
    None.
*/

typedef enum
{
    /* Command code to reset the SD card */
    DRV_SDHC_CMD_GO_IDLE_STATE = 0,

    /* Command code to initialize the SD card */
    DRV_SDHC_CMD_SEND_OP_COND  = 1,

    /* Broadcast command code to get all card IDs */
    DRV_SDHC_CMD_ALL_SEND_CID  = 2,

    /* Command card to respond with its RCA, tells it to go to standby state */
    DRV_SDHC_CMD_SEND_RCA  = 3,

    /* ACMD6 sets the card's bus width between 1-bit and 4-bit, only available when the card is unlocked */
    DRV_SDHC_CMD_SWITCH_FUNCTION = 6,
    /* ACMD6 sets the card's bus width between 1-bit and 4-bit, only available when the card is unlocked */
    DRV_SDHC_CMD_SET_BUS_WIDTH  = 6,

    /* Select/Deselect card message, sends the card to transfer state */
    DRV_SDHC_CMD_SELECT_DESELECT_CARD = 7,

    /* This macro defined the command code to check for sector addressing */
    DRV_SDHC_CMD_SEND_IF_COND  = 8,

    /* Command code to get the Card Specific Data */
    DRV_SDHC_CMD_SEND_CSD      = 9,

    /* Command code to get the Card Information */
    DRV_SDHC_CMD_SEND_CID      = 10,

    /* Command code to stop transmission during a multi-block read */
    DRV_SDHC_CMD_STOP_TRANSMISSION = 12,

    /* Command code to get the card status information */
    DRV_SDHC_CMD_SEND_STATUS       = 13,

    /* Command code to set the block length of the card */
    DRV_SDHC_CMD_SET_BLOCKLEN      = 16,

    /* Command code to read one block from the card */
    DRV_SDHC_CMD_READ_SINGLE_BLOCK  = 17,

    /* Command code to read multiple blocks from the card */
    DRV_SDHC_CMD_READ_MULTI_BLOCK   = 18,

    /* Command code to tell the media how many blocks to pre-erase
     (for faster multi-block writes to follow)
     Note: This is an "application specific" command.  This tells the media how
     many blocks to pre-erase for the subsequent WRITE_MULTI_BLOCK */
    DRV_SDHC_CMD_SET_WR_BLK_ERASE_COUNT =  23,

    /* Command code to write one block to the card */
    DRV_SDHC_CMD_WRITE_SINGLE_BLOCK  = 24,

    /* Command code to write multiple blocks to the card */
    DRV_SDHC_CMD_WRITE_MULTI_BLOCK   = 25,

    /* Command code to set the address of the start of an erase operation */
    DRV_SDHC_CMD_TAG_SECTOR_START    = 32,

    /* Command code to set the address of the end of an erase operation */
    DRV_SDHC_CMD_TAG_SECTOR_END      = 33,

    /* Command code to erase all previously selected blocks */
    DRV_SDHC_CMD_ERASE              =  38,

    /* Command code to initialise an SD card and provide the CSD register value.
    Note: this is an "application specific" command (specific to SD cards)
    and must be preceded by CMD_APP_CMD */
    DRV_SDHC_CMD_SD_SEND_OP_COND     = 41,

    /* Command code to get the SCR register information from the card */
    DRV_SDHC_CMD_READ_SCR            = 51,

    /* Command code to begin application specific command inputs */
    DRV_SDHC_CMD_APP_CMD             = 55,

    /* Command code to get the OCR register information from the card */
    DRV_SDHC_CMD_READ_OCR            = 58,

    /* Command code to disable CRC checking */
    DRV_SDHC_CMD_CRC_ON_OFF          = 59,

} DRV_SDHC_SD_COMMAND;

// *****************************************************************************
/* SD Host Controller type

  Summary:
    Lists different types of SD cards.

  Description:
    This enumeration lists different types of SD cards.

  Remarks:
    None.
*/

typedef enum
{
    /* Normal SD Host Controller */
    DRV_SDHC_MODE_NORMAL,

    /* SDHC type Card */
    DRV_SDHC_MODE_HC

}DRV_SDHC_TYPE;


// *****************************************************************************
/* SD Host Controller initialization stages

  Summary:
    Lists various stages while initializing the SD card.

  Description:
    This enumeration lists various stages while initializing the SD card.

  Remarks:
    None.
*/

typedef enum
{
    DRV_SDHC_INIT_RESET_CARD = 0,
    DRV_SDHC_INIT_RESET_DELAY,
    DRV_SDHC_INIT_CHK_IFACE_CONDITION,
    DRV_SDHC_INIT_SEND_APP_CMD,
    DRV_SDHC_INIT_SEND_ACMD41,
    DRV_SDHC_INIT_ALL_SEND_CID,
    DRV_SDHC_INIT_PUBLISH_RCA,
    DRV_SDHC_INIT_READ_CSD,
    DRV_SDHC_INIT_CHANGE_CLK_FREQ,
    DRV_SDHC_INIT_SELECT_CARD,
    DRV_SDHC_INIT_CHK_CARD_STATE,
    DRV_SDHC_INIT_PRE_SCR_STATE,
    DRV_SDHC_INIT_SEND_SCR,
    DRV_SDHC_INIT_PARSE_SCR_DATA,
    DRV_SDHC_INIT_SET_BUS_WIDTH,
    DRV_SDHC_INIT_CARD_VER_CHECK,
    DRV_SDHC_INIT_PRE_SWITCH_CMD,
    DRV_SDHC_INIT_SWITCH_CMD,
    DRV_SDHC_INIT_SWITCH_STATUS,
    DRV_SDHC_INIT_SET_HS_FREQ,
    DRV_SDHC_INIT_SET_BLOCK_LENGTH,
    DRV_SDHC_INIT_DESELECT_CARD,
    DRV_SDHC_INIT_DONE,
    DRV_SDHC_INIT_ERROR
} DRV_SDHC_INIT_STATES;

typedef enum
{
    DRV_SDHC_TASK_WAIT_FOR_DEVICE_ATTACH = 0,
    DRV_SDHC_TASK_MEDIA_INIT,
    DRV_SDHC_TASK_PROCESS_QUEUE,
    DRV_SDHC_TASK_SELECT_CARD,
    DRV_SDHC_TASK_SETUP_XFER,
    DRV_SDHC_TASK_XFER_COMMAND,
    DRV_SDHC_TASK_XFER_STATUS,
    DRV_SDHC_TASK_SEND_STOP_TRANS_CMD,
    DRV_SDHC_TASK_CHECK_CARD_STATUS,
    DRV_SDHC_TASK_DESELECT_CARD,
    DRV_SDHC_TASK_ERROR,
    DRV_SDHC_TASK_TRANSFER_COMPLETE,

} DRV_SDHC_TASK_STATES;

typedef enum
{
    DRV_SDHC_CMD_LINE_STATE_CHECK = 0,
    DRV_SDHC_CMD_FRAME_AND_SEND_CMD,
    DRV_SDHC_CMD_CHECK_TRANSFER_COMPLETE,
    DRV_SDHC_CMD_EXEC_IS_COMPLETE 
} DRV_SDHC_COMMAND_STATES;

typedef enum
{
    /* Set the clock divider value. */
    DRV_SDHC_CLOCK_SET_DIVIDER = 0,
    
    /* Wait for the internal clock stable bit to be set. */
    DRV_SDHC_CLOCK_PRE_ENABLE_DELAY,
    
    /* Enable the clock. */
    DRV_SDHC_CLOCK_ENABLE,
    
    /* Delay post clock enable. */
    DRV_SDHC_CLOCK_POST_ENABLE_DELAY,

    /* Clock set is complete. */
    DRV_SDHC_CLOCK_SET_COMPLETE

} DRV_SDHC_CLOCK_STATES;

// *****************************************************************************
/* SD Host Controller Driver Client Object

  Summary:
    Defines the object required for the maintenance of the software clients

  Description:
    This defines the object required for the maintenance of the software
    clients instance. This object exists once per client instance.

  Remarks:
    None
*/

typedef struct _DRV_SDHC_CLIENT_OBJ_STRUCT
{
    /* Hardware instance index associated with the client */
    void *driverObj;

    /* Flag to indicate in use  */
    bool inUse;

    /* The intent with which the client was opened */
    DRV_IO_INTENT intent;

    /* Client specific event handler */
    DRV_SDHC_EVENT_HANDLER eventHandler;

    /* Client specific context */
    uintptr_t context;

} DRV_SDHC_CLIENT_OBJ;


typedef struct DRV_SDHC_BUFFER_OBJ
{
    /* True if object is allocated */
    bool inUse;

    /* Client that owns this buffer */
    DRV_SDHC_CLIENT_OBJ *hClient;

    /* Present status of this command */
    DRV_SDHC_COMMAND_STATUS status;

    /* Current command handle of this buffer object */
    DRV_SDHC_COMMAND_HANDLE commandHandle;

    /* Pointer to the source/destination buffer */
    uint8_t *buffer;

    /* Start address of the operation. */
    uint32_t blockStart;

    /* Number of blocks */
    uint32_t nBlocks;

    /* Op code associated with the buffer object. */
    uint8_t opCode;

    /* Operation type - read/write */
    DRV_SDHC_OPERATION_TYPE opType;

    /* Pointer to the next buffer in the queue */
    struct DRV_SDHC_BUFFER_OBJ* next;

    /* Pointer to the previous buffer in the queue */
    struct DRV_SDHC_BUFFER_OBJ* previous;

} DRV_SDHC_BUFFER_OBJ;


// *****************************************************************************
/* SD Host Controller Driver Hardware Instance Object

  Summary:
    Defines the object required for the maintenance of the hardware instance

  Description:
    This defines the object required for the maintenance of the hardware
    instance. This object exists once per hardware instance of the peripheral.

  Remarks:
    None
*/

typedef struct _DRV_SDHC_OBJ_STRUCT
{
    /* Index of the driver */
    SYS_MODULE_INDEX drvIndex;

    /* The status of the driver */
    SYS_STATUS status;

    /* Flag to indicate in use  */
    bool inUse;

    /* Flag to indicate if the driver is used in exclusive mode of operation */
    bool isExclusive;

    /* Whether card detect should be used for detecting the presence/absence of
     * the card. */
    bool cardDetectEnable;

    /* Whether the write protect pin should be used to check if the card is
     * write protected. */
    bool writeProtectEnable;

    /* Number of clients possible with the hardware instance */
    uint8_t numClients;

    /* Sent command status. */
    uint8_t commandStatus;
    
    /* Variable used to track the number of trials of a particular operation.
     * */
    uint16_t trials;

    /* Status of the device */
    SYS_FS_MEDIA_STATUS mediaState;

    /* System Timer Handle */
    SYS_TMR_HANDLE tmrHandle;

    /* Pointer to the card context. */
    SDHOST_CARD_CTXT *cardCtxt;

    /* Speed mode - Default Speed or High Speed mode of operation. */
    DRV_SDHC_SPEED_MODE speedMode;

    /* Bus width to be used for the card. */
    DRV_SDHC_BUS_WIDTH busWidth;

    /* This variable holds the current state of the DRV_SDHC_Tasks */
    DRV_SDHC_TASK_STATES taskState;

    /* Different stages in media initialization */
    DRV_SDHC_INIT_STATES initState;
    DRV_SDHC_INIT_STATES nextInitState;
    
    /* Different states in sending a command */
    DRV_SDHC_COMMAND_STATES cmdState;

    /* Different states in setting up the clock */
    DRV_SDHC_CLOCK_STATES clockState;

    /* Queue of buffer objects. */
    DRV_SDHC_BUFFER_OBJ *queue;

    /* Pointer to the current buffer object. */
    DRV_SDHC_BUFFER_OBJ *currentBufObj;

    /* Mutex */
    OSAL_MUTEX_DECLARE(mutex);
    
} DRV_SDHC_OBJ;

#endif //#ifndef _DRV_SDHC_LOCAL_H

/*******************************************************************************
 End of File
*/

