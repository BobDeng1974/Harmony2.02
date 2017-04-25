/*******************************************************************************
  Wi-Fi MAC interface functions

  File Name:
    wdrv_winc1500_main.h

  Summary:
    Wi-Fi specific MAC function prototypes called by TCP/IP stack.

  Description:
    Wi-Fi specific MAC function prototypes called by TCP/IP stack.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2015 released Microchip Technology Inc. All rights reserved.

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

#ifndef _WDRV_WINC1500_MAIN_H
#define _WDRV_WINC1500_MAIN_H

#include "wdrv_winc1500_api.h"

#if !defined(TCPIP_STACK_USE_EVENT_NOTIFICATION)
#error "TCPIP_STACK_USE_EVENT_NOTIFICATION must be defined for WINC1500 Wi-Fi driver"
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************
#define WDRV_MAX_CLIENT_TABLE_SLOTS 10

// *****************************************************************************
/*  Wi-Fi PS-Poll Listen Interval default settings

  Summary:
    Default values for Wi-Fi PS PS-Poll Listen Interval settings

  Description
    These defines identify various default Wi-Fi PS-Poll settings that can
    be used in the WDRV_PS_POLL_CONTEXT structure.
*/
#define WDRV_DEFAULT_PS_LISTEN_INTERVAL ((uint16_t)1) // 100 ms multiplier, e.g. 1 * 100 ms = 100 ms
#define WDRV_DEFAULT_PS_DTIM_INTERVAL ((uint16_t)2) // number of beacon periods
#define WDRV_DEFAULT_PS_DTIM_ENABLED true // DTIM wake-up enabled (normally the case)

typedef struct
{
    uint8_t trafficEvents;
    uint16_t trafficEventInfo;
} WDRV_WINC1500_USREV_DCPT;

// stack internal notification
typedef struct
{
    bool                     mrfEnabledEvents; // group enabled notification events
    volatile TCPIP_MAC_EVENT mrfPendingEvents; // group notification events that are set, waiting to be re-acknowledged
    TCPIP_MAC_EventF         mrfNotifyFnc; // group notification handler
    const void              *mrfNotifyParam; // notification parameter
} WDRV_WINC1500_EVGROUP_DCPT; // event descriptor

typedef struct {
    uint8_t addr[6];
    uint32_t timeStamp;
} MAC_ADDR;

typedef struct 
{
    MAC_ADDR mac[WDRV_MAX_CLIENT_TABLE_SLOTS];
    uint16_t bitMap;
    uint32_t seqNum;
    uint16_t updated;
} WDRV_CLIENT_CACHE;

typedef struct {
    uint8_t macAddr[6];
    bool isDriverOpen;
    bool updateMacAddressRequired;
    bool isScanDone;
    bool initConn;
    bool isDisconnectRequested;
    OSAL_SEM_HANDLE_TYPE disconnectDoneSync;
    WDRV_CLIENT_CACHE clientCache;
    bool isFwUpgradeRequested;
    uint8_t FwServerUrl[128];
} WDRV_WINC1500_PRIV;

/*************************************************************************
  Summary:
    Selection of WPS Authorization types

  Description:
    Wi-Fi WPS authorization types

    This enumeration identifies the WPS authorization types
*/
typedef enum
{
    WDRV_WPS_AUTH_OPEN     = 0x01,
    WDRV_WPS_AUTH_WPA_PSK  = 0x02,
    WDRV_WPS_AUTH_SHARED   = 0x04,
    WDRV_WPS_AUTH_WPA      = 0x08,
    WDRV_WPS_AUTH_WPA2     = 0x10,
    WDRV_WPS_AUTH_WPA2_PSK = 0x20
} WDRV_WPS_AUTH_TYPES;

/************************************************************
ding types

  Description:
    Wi-Fi WPS encoding types

    This enumeration identifies the WPS encoding types
*/
typedef enum
{
    WDRV_WPS_ENC_NONE = 0x01,
    WDRV_WPS_ENC_WEP  = 0x02,
    WDRV_WPS_ENC_TKIP = 0x04,
    WDRV_ENC_AES      = 0x08
} WDRV_WPS_ENCODE_TYPES;

// *****************************************************************************
/*  Deauthorization/Disassociate Reason Codes

  Summary:
    Selection of different codes when a deauthorization or disassociation event has occurred.

  Description
    This enumeration identifies the reason codes for a connection lost due to a
    deauthorization or disassociation from the AP.
*/
typedef enum
{
    WDRV_UNSPECIFIED                    = 1,
    WDRV_REASON_PREV_AUTH_NOT_VALID     = 2,
    WDRV_DEAUTH_LEAVING                 = 3,
    WDRV_DISASSOC_DUE_TO_INACTIVITY     = 4,
    WDRV_DISASSOC_AP_BUSY               = 5,
    WDRV_CLASS2_FRAME_FROM_NONAUTH_STA  = 6,
    WDRV_CLASS3_FRAME_FROM_NONASSOC_STA = 7,
    WDRV_DISASSOC_STA_HAS_LEFT          = 8,
    WDRV_STA_REQ_ASSOC_WITHOUT_AUTH     = 9,
    WDRV_INVALID_IE                     = 13,
    WDRV_MIC_FAILURE                    = 14,
    WDRV_4WAY_HANDSHAKE_TIMEOUT         = 15,
    WDRV_GROUP_KEY_HANDSHAKE_TIMEOUT    = 16,
    WDRV_IE_DIFFERENT                   = 17,
    WDRV_INVALID_GROUP_CIPHER           = 18,
    WDRV_INVALID_PAIRWISE_CIPHER        = 19,
    WDRV_INVALID_AKMP                   = 20,
    WDRV_UNSUPP_RSN_VERSION             = 21,
    WDRV_INVALID_RSN_IE_CAP             = 22,
    WDRV_IEEE8021X_FAILED               = 23,
    WDRV_CIPHER_SUITE_REJECTED          = 24
} WDRV_REASON_CODES;

/***********************************************************
  Summary:
    Wi-Fi Power-Saving states

  Description:
    Wi-Fi Power-Saving states

    This enumeration identifies Wi-Fi Power-Saving states. See
    WDRV_PsPollEnable().
*/
typedef enum
{
    WDRV_PS_SLEEP,
    WDRV_PS_ACTIVE
} WDRV_POWER_SAVE_STATES;

/***********************************************************
  Summary:
    Wi-Fi Connection states

  Description:
    Wi-Fi Connection States

    This enumeration identifies Wi-Fi Connection states. See
    WDRV_CLI_ConnectionStateGet().
 */
typedef enum
{
    /* No Wi-Fi connection exists */
    WDRV_CONNECTION_STATE_NOT_CONNECTED = 1,

    /* Wi-Fi connection in progress */
    WDRV_CONNECTION_STATE_IN_PROGRESS = 2,

    /* Wi-Fi connected in infrastructure mode */
    WDRV_CONNECTION_STATE_CONNECTED = 3
} WDRV_CONNECTION_STATES;

void WDRV_PendingEventProcess(void);
bool isEventPending(void);

void WDRV_GPIO_OutLow_PIC32MZ_ESK(uint32_t channel, uint32_t bit_pos);
void WDRV_GPIO_OutLow_PIC32MX_EXP16(uint32_t channel, uint32_t bit_pos);
void WDRV_GPIO_OutLow_Custom_Board(uint32_t channel, uint32_t bit_pos);
void WDRV_GPIO_OutHigh_PIC32MZ_ESK(uint32_t channel, uint32_t bit_pos);
void WDRV_GPIO_OutHigh_PIC32MX_EXP16(uint32_t channel, uint32_t bit_pos);
void WDRV_GPIO_OutHigh_Custom_Board(uint32_t channel, uint32_t bit_pos);

TCPIP_MAC_RES WDRV_WINC1500_MulticastFilterSet(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_ADDR *DestMACAddr);
bool isMacInitialized(void);

void WDRV_DataCacheClean(unsigned char *address, uint32_t size);
bool ClientCacheUpdated(bool *connected, uint8_t *mac);

bool isLinkUp();
void WDRV_TrafficEventInit(TCPIP_MAC_EventF eventF, const void *eventParam);
void WDRV_TrafficEventDeinit(void);
void WDRV_TrafficEventReq(uint16_t event, uint16_t eventInfo);
bool WDRV_TrafficEventMask(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_EVENT macEvents, bool enable);
bool WDRV_TrafficEventAck(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_EVENT macEvents);
TCPIP_MAC_EVENT WDRV_TrafficEventGet(TCPIP_MAC_HANDLE hMac);
void WDRV_AllEventClear(void);
void WDRV_EventSet(uint8_t event);
bool WDRV_CONFIG_DataLoad(void);
void WDRV_CONFIG_DataSave(void);
void WDRV_CONFIG_DataDelete(void);
void ConnectEventCB(bool connected, bool isServer, uint8_t const *const client);
void WDRV_Connect(void);
void WDRV_Disconnect(void);
WDRV_CONNECTION_STATES WDRV_ConnectionStatus_Get(void);
void WPSDoneCB(void);

extern WDRV_SCAN_STATUS g_scanStatus;
extern WDRV_SCAN_RESULT g_scanResults[];
extern WDRV_WINC1500_PRIV g_wdrv_priv;

#endif /* _WDRV_WINC1500_MAIN_H */

// DOM-IGNORE-END
