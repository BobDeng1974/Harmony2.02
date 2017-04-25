/*******************************************************************************
  Winc1500 main task.
  
  File Name:
    winc1500_task.h

  Summary:

  Description:
   
*******************************************************************************/

//DOM-IGNORE-BEGIN
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

#ifndef WINC1500_TASK_H_INCLUDED
#define WINC1500_TASK_H_INCLUDED

#include <stdbool.h>
#include "nm_common.h"
#include "m2m_types.h"
#include "m2m_hif.h"
#include "m2m_wifi.h"

#ifdef __cplusplus
    extern "C" {
#endif

typedef TCPIP_MAC_PACKET *(*GetRxBufFunc)(void);

typedef struct {
    TaskHandle_t handle;
    OSAL_SEM_HANDLE_TYPE scanResultWait;
    OSAL_SEM_HANDLE_TYPE connInfoWait;
    OSAL_SEM_HANDLE_TYPE eventWait;
    volatile bool deinit_in_progress;
} WINC1500_PRIV;

typedef struct {
    void (*FrameReceived_CB)(uint32_t len, uint8_t const *const frame);
    void (*ConnectEvent_CB)(bool connected, bool isServer, uint8_t const *const client);
    void (*RFReady_CB)(uint8_t const *const addr);
    void (*ScanDone_CB)(uint32_t status);
    void (*InitDone_CB)(void);
    void (*WPSDone_CB)(void);
    uint8_t address[6];
    GetRxBufFunc get_rx_buf;
    bool ethMode;
    uint8_t *FwServerUrl;
} WINC1500_INTF;

typedef struct {
#define CONN_DATA_UNSPECIFIED -1
    uint8_t ssid[32 + 1];
    int16_t ssidLen;
    int8_t secType;
    uint8_t key[64 + 1];
    uint8_t keyLen;
    uint8_t keyIdx;
    uint8_t channel;
    int8_t isSoftAP;
} WINC1500_CONNECT_DATA;

typedef struct {
    bool scanListGetOnce;
    bool scanInProgress;
} WINC1500_SCAN_CONTROL;

#define winc1500_init_completed() ((*g_winc1500_intf->InitDone_CB)())
#define winc1500_rf_ready(mac) ((*g_winc1500_intf->RFReady_CB)(mac))
#define winc1500_wps_completed() ((*g_winc1500_intf->WPSDone_CB)())
#define winc1500_scan_completed(status) ((*g_winc1500_intf->ScanDone_CB)(status))
#define winc1500_eth_data_received(len, frame) ((*g_winc1500_intf->FrameReceived_CB)(len, frame))
#define winc1500_connect_event_received(connected, isServer, client) ((*g_winc1500_intf->ConnectEvent_CB)(connected, isServer, client))
#define winc1500_get_rx_bufer() ((*g_winc1500_intf->get_rx_buf)())
#define winc1500_eth_data_send(frame, len) m2m_wifi_send_ethernet_pkt(frame, len)
#define winc1500_isr(sem) m2m_hif_isr(sem)

void winc1500_task(uint32_t pContext);
int8_t winc1500_connect(WINC1500_CONNECT_DATA *data);
void winc1500_scan_result_read(tstrM2mWifiscanResult *result);
void winc1500_wps_info_read(tstrM2MWPSInfo *info);
void winc1500_conn_info_read(tstrM2MConnInfo *info);
sint8 winc1500_init(void);
sint8 winc1500_deinit(void);
void winc1500_fw_update(uint32_t pContext);

extern WINC1500_INTF *g_winc1500_intf;
extern WINC1500_PRIV g_wdrvext_priv;

#ifdef __cplusplus
}
#endif

#endif /* WINC1500_TASK_H_INCLUDED*/
