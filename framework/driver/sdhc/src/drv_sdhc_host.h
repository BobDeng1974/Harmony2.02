/*******************************************************************************
  SD Host Controller Driver Interface

  Company:
    Microchip Technology Inc.

  File Name:
    drv_sdhc_host.h

  Summary:
    SD Host Controller Driver System Host Definitions

  Description:
    The SD Host Controller driver provides a simple interface to manage the SD 
    Host Controller peripheral.  This file defines the interface definitions 
    and prototypes for the SD Host Controller driver.
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

#ifndef _DRV_SDHC_HOST_H
#define _DRV_SDHC_HOST_H

#include "system_definitions.h"

/* SD Host Controller Spec version. */
#define SDHOST_HOST_SPEC_VER_1              0
#define SDHOST_HOST_SPEC_VER_2              1
#define SDHOST_HOST_SPEC_VER_3	            2

#define SDHOST_CLOCK_FREQ_400_KHZ           (400000)
#define SDHOST_CLOCK_FREQ_DS_25_MHZ         (25000000)
#define SDHOST_CLOCK_FREQ_HS_50_MHZ         (50000000)

typedef enum
{
    SDHOST_RESET_ALL = 0x01, 
    SDHOST_RESET_CMD = 0x02,
    SDHOST_RESET_DAT = 0x04    
} SDHOST_RESET_TYPE;

typedef enum
{
    SDHOST_BUS_WIDTH_1_BIT = 0,
    SDHOST_BUS_WIDTH_4_BIT,
} SDHOST_BUS_WIDTH;

typedef enum
{
    SDHOST_SPEED_MODE_NORMAL = 0,
    SDHOST_SPEED_MODE_HIGH
} SDHOST_SPEED_MODE;

typedef enum
{
    SDHOST_READ_RESP_REG_0 = 0,
    SDHOST_READ_RESP_REG_1,
    SDHOST_READ_RESP_REG_2,
    SDHOST_READ_RESP_REG_3,
    SDHOST_READ_RESP_REG_ALL
} SDHOST_READ_RESPONSE_REG;

typedef enum SDHOST_CMD_RESP_TYPE
{
    SDHOST_CMD_RESP_NONE,   /*!< no response type */
    SDHOST_CMD_RESP_R1,     /*!< normal response command */
    SDHOST_CMD_RESP_R1B,    /*!< normal with busy signal */
    SDHOST_CMD_RESP_R2,     /*!< CID, CSD register */
    SDHOST_CMD_RESP_R3,     /*!< OCR register */
    SDHOST_CMD_RESP_R4,     /*!< */
    SDHOST_CMD_RESP_R5,     /*!< */
    SDHOST_CMD_RESP_R6,     /*!< Published RCA response  */
    SDHOST_CMD_RESP_R7      /*!< Card interface condition  */
      
} SDHOST_CMD_RESP_TYPE;


typedef struct
{
    uint8_t isAttached;
    uint8_t busWidth;

    uint16_t rca;

    uint8_t *scr;
    uint8_t *cid;
    uint8_t *csd;
    uint8_t *ocr;
    uint8_t *switchStatus;

    uint8_t cmd6Mode;
    uint8_t voltWindow;
    /* HC or Normal card. */
    uint8_t cardType;
    /* Capacity of the card in number of blocks. */
    uint32_t discCapacity;

    uint8_t cardVer;
    uint8_t writeProtected;
    uint8_t locked;

    /* Variables to track the command/data status. */
    uint8_t dataCompleted;
    uint8_t commandCompleted;
    uint8_t waitForCmdResp;
    uint8_t waitForData;
    uint8_t isDataPresent;
    uint8_t commandError;
    uint8_t errorFlag;

} SDHOST_CARD_CTXT;

void sdhostResetError
(
    SDHOST_RESET_TYPE resetType
);

void sdhostSetBusWidth
(
    SDHOST_BUS_WIDTH busWidth
);

void sdhostSetSpeedMode
(
    SDHOST_SPEED_MODE speedMode
);

void sdhostSetupDma
(
    uint8_t *buffer,
    uint16_t numBytes
);

void sdhostSetBlockSize
(
    uint16_t blockSize
);

void sdhostSetBlockCount
(
    uint16_t numBlocks
);

bool sdhostIsCardAttached
(
    void
);

void sdhostSetClock
(
    uint32_t clock
);

void sdhostClockEnable
(
    void
);

void sdhostClockDisable
(
    void
);

void sdhostInterruptHandler
(
    SDHOST_CARD_CTXT *cardCtxt
);

bool sdhostIsCmdLineBusy
(
    void
);

bool sdhostIsDat0LineBusy
(
    void
);

void sdhostReadResponse
(
    SDHOST_READ_RESPONSE_REG respReg,
    uint32_t *response
);

void sdhostSendCommand
(
    uint8_t opCode, 
    uint8_t respType,
    uint8_t dataPresent,
    uint32_t argument
);

bool sdhostIsWriteProtected
(
    void
);

bool sdhostInit
(
    SDHOST_CARD_CTXT **cardCtxt
);

#endif

