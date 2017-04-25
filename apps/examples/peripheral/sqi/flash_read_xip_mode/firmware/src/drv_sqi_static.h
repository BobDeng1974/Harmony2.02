/*******************************************************************************
  SQI Driver Interface Declarations for Static Single Instance Driver

  Company:
    Microchip Technology Inc.

  File Name:
    drv_sqi_static.h

  Summary:
    SQI driver interface declarations for the static single instance driver.

  Description:
    The SQI device driver provides a simple interface to manage the SQI
    modules on Microchip microcontrollers. This file defines the interface
    Declarations for the SQI driver.
    
  Remarks:
    Static interfaces incorporate the driver instance number within the names
    of the routines, eliminating the need for an object ID or object handle.
    
    Static single-open interfaces also eliminate the need for the open handle.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2015 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _DRV_SQI_STATIC_H
#define _DRV_SQI_STATIC_H

// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************
/* Note:  A file that maps the interface definitions above to appropriate static
          implementations (depending on build mode) is included at the bottom of
          this file.
*/
#include <stdbool.h>
#include "system_config.h"
#include "peripheral/sqi/plib_sqi.h"

// *****************************************************************************
// *****************************************************************************
// Section: Enumerations
// *****************************************************************************
// *****************************************************************************
typedef enum {

    DRV_SQI_ID_0 = SQI_ID_0,
    DRV_SQI_NUMBER_OF_MODULES

} DRV_SQI_MODULE_ID;

typedef enum {

    DRV_SQI_XFER_MODE_XIP = SQI_XFER_MODE_XIP,
    DRV_SQI_XFER_MODE_DMA = SQI_XFER_MODE_DMA,
    DRV_SQI_XFER_MODE_PIO = SQI_XFER_MODE_PIO

} DRV_SQI_XFER_MODE;

typedef enum {

    DRV_SQI_DATA_MODE_3 = SQI_DATA_MODE_3,
    DRV_SQI_DATA_MODE_0 = SQI_DATA_MODE_0

} DRV_SQI_DATA_MODE;

typedef enum {

    DRV_SQI_DATA_FORMAT_LSBF = SQI_DATA_FORMAT_LSBF,
    DRV_SQI_DATA_FORMAT_MSBF = SQI_DATA_FORMAT_MSBF

} DRV_SQI_DATA_FORMAT;

typedef enum {

    DRV_SQI_DATA_OEN_QUAD = SQI_DATA_OEN_QUAD,
    DRV_SQI_DATA_OEN_DUAL = SQI_DATA_OEN_DUAL,
    DRV_SQI_DATA_OEN_SINGLE = SQI_DATA_OEN_SINGLE

} DRV_SQI_DATA_OEN;

typedef enum {

    DRV_SQI_CS_OEN_BOTH = SQI_CS_OEN_BOTH,
    DRV_SQI_CS_OEN_1 = SQI_CS_OEN_1,
    DRV_SQI_CS_OEN_0 = SQI_CS_OEN_0,
    DRV_SQI_CS_OEN_NONE = SQI_CS_OEN_NONE

} DRV_SQI_CS_OEN;

typedef enum {

    DRV_SQI_CMD_RECEIVE = SQI_CMD_RECEIVE,
    DRV_SQI_CMD_TRANSMIT = SQI_CMD_TRANSMIT,
    DRV_SQI_CMD_IDLE = SQI_CMD_IDLE

} DRV_SQI_XFER_CMD;

typedef enum {

    DRV_SQI_LANE_QUAD = SQI_LANE_QUAD,
    DRV_SQI_LANE_DUAL = SQI_LANE_DUAL,
    DRV_SQI_LANE_SINGLE = SQI_LANE_SINGLE

} DRV_SQI_LANE_MODE;

typedef enum {

    DRV_SQI_CS_1 = SQI_CS_1,
    DRV_SQI_CS_0 = SQI_CS_0

} DRV_SQI_CS_NUM;

typedef enum {

    DRV_ADDR_BYTES_4 = ADDR_BYTES_4,
    DRV_ADDR_BYTES_3 = ADDR_BYTES_3,
    DRV_ADDR_BYTES_2 = ADDR_BYTES_2,
    DRV_ADDR_BYTES_1 = ADDR_BYTES_1,
    DRV_ADDR_BYTES_0 = ADDR_BYTES_0

} DRV_SQI_ADDR_BYTES;

typedef enum {

    DRV_DUMMY_BYTES_7 = DUMMY_BYTES_7,
    DRV_DUMMY_BYTES_6 = DUMMY_BYTES_6,
    DRV_DUMMY_BYTES_5 = DUMMY_BYTES_5,
    DRV_DUMMY_BYTES_4 = DUMMY_BYTES_4,
    DRV_DUMMY_BYTES_3 = DUMMY_BYTES_3,
    DRV_DUMMY_BYTES_2 = DUMMY_BYTES_2,
    DRV_DUMMY_BYTES_1 = DUMMY_BYTES_1,
    DRV_DUMMY_BYTES_0 = DUMMY_BYTES_0

} DRV_SQI_DUMMY_BYTES;

typedef enum {

    DRV_MODE_BYTES_3 = MODE_BYTES_3,
    DRV_MODE_BYTES_2 = MODE_BYTES_2,
    DRV_MODE_BYTES_1 = MODE_BYTES_1,
    DRV_MODE_BYTES_0 = MODE_BYTES_0

} DRV_SQI_MODE_BYTES;

typedef enum {

    DRV_SQI_DMAERROR = 11,
    DRV_SQI_PKTCOMP = SQI_PKTCOMP,
    DRV_SQI_BDDONE = SQI_BDDONE,
    DRV_SQI_CONTHR = SQI_CONTHR,
    DRV_SQI_CONEMPTY = SQI_CONEMPTY,
    DRV_SQI_CONFULL = SQI_CONFULL,
    DRV_SQI_RXTHR = SQI_RXTHR,
    DRV_SQI_RXEMPTY = SQI_RXEMPTY,
    DRV_SQI_RXFULL = SQI_RXFULL,
    DRV_SQI_TXTHR = SQI_TXTHR,
    DRV_SQI_TXEMPTY = SQI_TXEMPTY,
    DRV_SQI_TXFULL = SQI_TXFULL

} DRV_SQI_INTERRUPTS;

typedef enum {

    DRV_BD_STATE_DISABLED = BD_STATE_DISABLED,
    DRV_BD_STATE_DONE = BD_STATE_DONE,
    DRV_BD_STATE_PROCESSING_DATA = BD_STATE_PROCESSING_DATA,
    DRV_BD_STATE_BEING_FETCHED = BD_STATE_BEING_FETCHED,
    DRV_BD_STATE_FETCH_REQ_PENDING = BD_STATE_FETCH_REQ_PENDING,
    DRV_BD_STATE_IDLE = BD_STATE_IDLE

} DRV_SQI_BD_STATE;

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
#define MAX_WRITE_BUF_DEPTH                 8
#define MAX_READ_BUF_DEPTH                  8
#define XIP_UNCACHED_ADDR_MASK              0xF0000000
#define XIP_CACHED_ADDR_MASK                0xD0000000
#define SQI_NUM_BUFFER_DESC                 256

//Flash Commands
#define FLASH_NOP                           0x00
#define FLASH_RSTEN							0x66
#define FLASH_RST							0x99
#define FLASH_EQIO                          0x38
#define FLASH_WEN                           0x06
#define FLASH_UNPROTECT_GLOBAL              0x98
#define FLASH_QJID                          0xAF
#define FLASH_ERASE                         0xC7
#define FLASH_PAGE_WRITE                    0x02
#define FLASH_FAST_READ                     0x0B
#define FLASH_RDSR							0x05
#define FLASH_BUSY							0x01
#define FLASH_READY							0x00
#define FLASH_BUSY_MASK                     0x08
#define FLASH_BUSY_MASK_DUPLICATE			0x01

#define FLASH_PAGE_SIZE                     256
//Flash device ID
#define FLASH_JEDECID_B					    0x4226BF

// *****************************************************************************
/* SQI DMA descriptor

  Summary:
    Holds DMA descriptor data

  Description:
    This structure holds the DMA descriptor data.

  Remarks:
    None.
 */
typedef struct
{
    // Buffer Descriptor Control Word
    unsigned int BDCon;

    // Buffer Descriptor Status Word - reserved.
    unsigned int BDStat;

    // Buffer Address.
    unsigned int *BDAddr;

    // Next Buffer Descriptor Address Pointer
    struct sqiDMADesc *nextBDAddr;

} sqiDMADesc;

// *****************************************************************************
/* USART Client-Specific Driver Status

  Summary:
    Defines the client-specific status of the USART driver.

  Description:
    This enumeration defines the client-specific status codes of the USART
    driver.

  Remarks:
    Returned by the DRV_USART_ClientStatus function.
*/

typedef enum
{
    /* An error has occurred.*/
    SQI_STATUS_FAILURE = 0,

    /* No errors occurred*/
    SQI_STATUS_SUCCESS = 1,

} SQI_STATUS;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for SQI Static Driver
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    void DRV_SQI_Initialize(void);

  Summary:
    Initializes Serial Quad Interface (SQI) module.
    <p><b>Implementation:</b> Static</p>

  Description:
	This routine is used to initialize SQI module by setting configuration 
	words and clock services.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    DRV_SQI_Initialize();
    </code>

  Remarks:
    None.
*/
void DRV_SQI_Initialize(void);

// *****************************************************************************
/* Function:
    void DRV_SQI_Flash_Initialize(void);

  Summary:
    Initializes external quad flash.
    <p><b>Implementation:</b> Static</p>

  Description:
	This routine is used to initialize external quad flash by unprotecting it for
	ERASE/READ/WRITE operations

  Precondition:
    DRV_SQI_Initialize should be called before using this function.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    DRV_SQI_Flash_Initialize();
    </code>

  Remarks:
    DRV_SQI_Initialize function calls this before exiting.
*/
void DRV_SQI_Flash_Initialize(void);

// *****************************************************************************
/* Function:
    void DRV_SQI_Flash_Erase(void);

  Summary:
    Erase external quad flash.
    <p><b>Implementation:</b> Static</p>

  Description:
	This routine when called will issue commands to erase the external flash.

  Precondition:
    DRV_SQI_Initialize should be called before using this function.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    DRV_SQI_Flash_Erase();
    </code>

  Remarks:
    None.
*/
void DRV_SQI_Flash_Erase (void);

// *****************************************************************************
/* Function:
    int DRV_SQI_Flash_ID_Check(void);

  Summary:
    Read external flash ID.
    <p><b>Implementation:</b> Static</p>

  Description:
	This routine when called will issue commands to read the external flash ID,
	checks against expected value and returns true/false.

  Precondition:
    DRV_SQI_Initialize should be called before using this function.

  Parameters:
    None.

  Returns:
    SQI_STATUS (bool).

  Example:
    <code>
    bool IDReadStatus = DRV_SQI_Flash_ID_Check();

	if ( sqiStatus !=  true)
        appData.state = APP_STATE_CURRENT;
    else
        appData.state = APP_STATE_NEXT;

    </code>

  Remarks:
    None.
*/
SQI_STATUS DRV_SQI_Flash_ID_Check (void);

// *****************************************************************************
/* Function:
    void DRV_SQI_PIO_PageWrite (uint32_t flashAddress, uint8_t* writeBuffer);

  Summary:
    Write external flash page.
    <p><b>Implementation:</b> Static</p>

  Description:
	This routine when called will issue commands to write external flash page.

  Precondition:
    DRV_SQI_Initialize should be called before using this function.

  Parameters:
    flashAddress - Page address in flash.
	writeBuffer  - Pointer to data to be written

  Returns:
    None.

  Example:
    <code>
    DRV_SQI_PIO_PageWrite (FLASH_PAGE_ADDRESS, writeBuffer);
    </code>

  Remarks:
    None.
*/
void DRV_SQI_PIO_PageWrite (uint32_t flashAddress, uint8_t* writeBuffer);

// *****************************************************************************
/* Function:
   void DRV_SQI_XIP_Read(uint32_t flashAddress, uint32_t readSize, uint8_t* readBuffer);

  Summary:
    Read external flash using XIP mode.
    <p><b>Implementation:</b> Static</p>

  Description:
	This routine when called will issue commands to read external flash using XIP mode.

  Precondition:
    DRV_SQI_Initialize should be called before using this function.

  Parameters:
    flashAddress - Page address in flash
	readSize     - Size of data to be read	
	readBuffer   - Pointer to data to be read

  Returns:
    None.

  Example:
    <code>
    DRV_SQI_XIP_Read(FLASH_ADDRESS, FLASH_READ_COUNT, readBuffer);
    </code>

  Remarks:
    None.
*/
void DRV_SQI_XIP_Read (uint32_t flashAddress, uint32_t readSize, uint8_t* readBuffer);

// *****************************************************************************
/* Function:
   uint8_t DRV_SQI_FlashIsBusy(void);

  Summary:
    Check external flash status.
    <p><b>Implementation:</b> Static</p>

  Description:
	This routine when called will check the external flash status through
	DRV_SQI_FlashReadStatus() function and checks the availability.

  Precondition:
    DRV_SQI_Initialize should be called before using this function.

  Parameters:
    None.

  Returns:
    READY/BUSY status.

  Example:
    <code>
    readStatus = DRV_SQI_FlashIsBusy();
    </code>

  Remarks:
    None.
*/
uint8_t DRV_SQI_FlashIsBusy(void);

// *****************************************************************************
/* Function:
   uint8_t DRV_SQI_FlashReadStatus(void);

  Summary:
    Read external flash status.
    <p><b>Implementation:</b> Static</p>

  Description:
	This routine when called will issue commands to read external flash status.

  Precondition:
    DRV_SQI_Initialize should be called before using this function.

  Parameters:
    None.

  Returns:
    STATUS register value.

  Example:
    <code>
    statusRegisterValue = DRV_SQI_FlashReadStatus();
    </code>

  Remarks:
    None.
*/
uint8_t DRV_SQI_FlashReadStatus(void);

#endif // #ifndef _DRV_SQI_STATIC_H

/*******************************************************************************
 End of File
*/
