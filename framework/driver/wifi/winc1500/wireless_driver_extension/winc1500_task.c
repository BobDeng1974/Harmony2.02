/*******************************************************************************
  Winc1500 main task.
  
  File Name:
    winc1500_task.c

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

#include "winc1500_task.h"
#include "driver/include/m2m_wifi.h"
#include "driver/source/nmasic.h"
#include "m2m_ota.h"

#define PACKET_BUFFER_SIZE 1564

WINC1500_INTF *g_winc1500_intf;
static bool s_isSoftAP;
static tstrM2MConnInfo s_connInfo;
static tstrM2mWifiscanResult s_scanResult;
static tstrM2MWPSInfo s_wpsInfo;

sint8 winc1500_init(void)
{
	/* Perform chip reset. */
	nm_reset();
    s_isSoftAP = false;

	return M2M_SUCCESS;
}

sint8 winc1500_deinit(void)
{
    WDRV_GPIO_ChipDisable();
    WDRV_GPIO_ModuleReset();

	return M2M_SUCCESS;
}

void winc1500_scan_result_read(tstrM2mWifiscanResult *result)
{
    memcpy((void *)result, (void *)&s_scanResult, sizeof(tstrM2mWifiscanResult));
}

void winc1500_wps_info_read(tstrM2MWPSInfo *info)
{
    memcpy((void *)info, (void *)&s_wpsInfo, sizeof(tstrM2MWPSInfo));
}

void winc1500_conn_info_read(tstrM2MConnInfo *info)
{
    memcpy((void *)info, (void *)&s_connInfo, sizeof(tstrM2MConnInfo));
}

static void wifi_cb(uint8_t u8MsgType, void *pvMsg)
{
	switch (u8MsgType) {
    case M2M_WIFI_RESP_ETHERNET_RX_PACKET:
   	{
       	int32_t wait = 0;
        TCPIP_MAC_PACKET *p_packet;
        tstrM2mIpPktBuf *frame = (tstrM2mIpPktBuf *)pvMsg;

        winc1500_eth_data_received(frame->u16BufSz, frame->header);
        p_packet = winc1500_get_rx_bufer();
        while (p_packet == NULL) {
            WDRV_TIME_DELAY(10);
            p_packet = winc1500_get_rx_bufer();
            if (++wait > 500) {
                /* Something went wrong */
                WDRV_ASSERT(false, "No Rx Buffer Available");
            }
        }
        m2m_wifi_set_receive_buffer(p_packet, p_packet->pDSeg->segLoad, PACKET_BUFFER_SIZE);
		break;
    }
	case M2M_WIFI_RESP_SCAN_DONE:
        winc1500_scan_completed(0);
        break;
	case M2M_WIFI_RESP_SCAN_RESULT:
        memcpy((void *)&s_scanResult, (void *)pvMsg, sizeof(tstrM2mWifiscanResult));
        WDRV_SemGive(&g_wdrvext_priv.scanResultWait);
        break;
	case M2M_WIFI_RESP_CON_STATE_CHANGED:
	{
		tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged *)pvMsg;

		if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) {
			if (g_winc1500_intf->ethMode) {
				if (s_isSoftAP) {
					int8_t ret;
					ret = m2m_wifi_get_connection_info();
					WDRV_ASSERT(ret == 0, "m2m_wifi_get_connection_info failed");
				} else {
					winc1500_connect_event_received(true, false, NULL);
					WDRV_DBG_INFORM_MESSAGE(("Wi-Fi Connected\r\n"));
				}
			}
		} else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
			if (g_winc1500_intf->ethMode) {
				winc1500_connect_event_received(false, false, NULL);
				if (!s_isSoftAP) {
					WDRV_DBG_INFORM_MESSAGE(("Wi-Fi Disconnected\r\n"));
				}
			}
		}
		break;
	}
	case M2M_WIFI_RESP_CONN_INFO:
		memcpy((void *)&s_connInfo, (void *)pvMsg, sizeof(tstrM2MConnInfo));
		if (s_isSoftAP) {
			winc1500_connect_event_received(true, false, s_connInfo.au8MACAddress);
		} else {
			WDRV_SemGive(&g_wdrvext_priv.connInfoWait);
		}
		break;
	case M2M_WIFI_REQ_DHCP_CONF:
		WDRV_DBG_INFORM_MESSAGE(("Wi-Fi Connected\r\n"));
		WDRV_DBG_INFORM_PRINT(("Wi-Fi IP is %u.%u.%u.%u\r\n",
			((uint8_t *)pvMsg)[0], ((uint8_t *)pvMsg)[1], ((uint8_t *)pvMsg)[2], ((uint8_t *)pvMsg)[3]));
		/* Start OTA Firmware download. */
		m2m_ota_start_update((uint8_t *)g_winc1500_intf->FwServerUrl);
		break;
    case M2M_WIFI_REQ_WPS:
        memcpy((void *)&s_wpsInfo, (void *)pvMsg, sizeof(tstrM2MWPSInfo));
		if (s_wpsInfo.u8AuthType != M2M_WIFI_SEC_INVALID) {
        	WDRV_DBG_INFORM_MESSAGE(("Credentials got off of WPS\r\n"));
        	WDRV_DBG_INFORM_PRINT(("ssid: %s\r\n", s_wpsInfo.au8SSID));
        	WDRV_DBG_INFORM_PRINT(("channel: %d\r\n", s_wpsInfo.u8Ch));
        	WDRV_DBG_INFORM_PRINT(("auth type: %d\r\n", s_wpsInfo.u8AuthType));
			if (s_wpsInfo.u8AuthType != M2M_WIFI_SEC_OPEN)
        		WDRV_DBG_INFORM_PRINT(("psk: %s\r\n", s_wpsInfo.au8PSK));
		}
        winc1500_wps_completed();
        break;
	default:
        WDRV_ASSERT(false, "Invalid Callback ID");
		break;
	}
}

int8_t winc1500_connect(WINC1500_CONNECT_DATA *data)
{
    int8_t ret;
    tstrM2MAPConfig strM2MAPConfig;

    if (data->isSoftAP) {
        s_isSoftAP = true;
        memset(&strM2MAPConfig, 0, sizeof(tstrM2MAPConfig));
        strcpy((char *)&strM2MAPConfig.au8SSID, (char *)data->ssid);
        strM2MAPConfig.u8ListenChannel = data->channel;
        strM2MAPConfig.u8SecType = data->secType;
		if (strM2MAPConfig.u8SecType == M2M_WIFI_SEC_WEP) {
			strcpy((char *)&strM2MAPConfig.au8WepKey, (char *)data->key);
			strM2MAPConfig.u8KeySz = data->keyLen;
			strM2MAPConfig.u8KeyIndx = data->keyIdx;
		} else if (strM2MAPConfig.u8SecType == M2M_WIFI_SEC_WPA_PSK) {
			strcpy((char *)&strM2MAPConfig.au8Key, (char *)data->key);
			strM2MAPConfig.u8KeySz = data->keyLen;
		}

		/*
		 * In Ethernet mode, this IP address does not take effect.
		 * But a dummy IP address needs to be set here.
		 * Otherwise it does not pass the parameter validity check.
		 */
        strM2MAPConfig.au8DHCPServerIP[0] = 192;
        strM2MAPConfig.au8DHCPServerIP[1] = 168;
        strM2MAPConfig.au8DHCPServerIP[2] = 1;
        strM2MAPConfig.au8DHCPServerIP[3] = 1;

        /* Bring up AP mode with parameters structure. */
        ret = m2m_wifi_enable_ap(&strM2MAPConfig);
		WDRV_ASSERT(ret == WDRV_SUCCESS, "main: m2m_wifi_enable_ap error");
        winc1500_connect_event_received(true, true, NULL);
        WDRV_DBG_INFORM_PRINT(("Soft AP is enabled, SSID: %s\r\n", (char *)data->ssid));
    } else {
    	s_isSoftAP = false;
        if (data->secType == M2M_WIFI_SEC_WEP) {
            tstrM2mWifiWepParams wep;

            wep.u8KeyIndx = data->keyIdx;
            wep.u8KeySz = strlen((char *)(data->key));
            memcpy((void *)wep.au8WepKey, (void *)data->key, wep.u8KeySz);
            wep.au8WepKey[wep.u8KeySz] = '\0';
            wep.u8KeySz++;
            ret = m2m_wifi_connect((char *)data->ssid, data->ssidLen, data->secType, &wep, data->channel);
        } else {
            ret = m2m_wifi_connect((char *)data->ssid, data->ssidLen, data->secType, data->key, data->channel);
        }
    }

    return ret;
}

/**
 * \brief OTA notify callback.
 *
 * OTA notify callback typedef.
 */
static void OtaNotifCb(tstrOtaUpdateInfo *pv)
{
	WDRV_DBG_INFORM_PRINT(("OtaNotifCb\r\n"));
}

/**
 * \brief Callback to get the OTA update event.
 *
 * \param[in] u8OtaUpdateStatusType type of OTA update status notification. Possible types are:
 * - [DL_STATUS](@ref DL_STATUS)
 * - [SW_STATUS](@ref SW_STATUS)
 * - [RB_STATUS](@ref RB_STATUS)
 * \param[in] u8OtaUpdateStatus type of OTA update status detail. Possible types are:
 * - [OTA_STATUS_SUCSESS](@ref OTA_STATUS_SUCSESS)
 * - [OTA_STATUS_FAIL](@ref OTA_STATUS_FAIL)
 * - [OTA_STATUS_INVAILD_ARG](@ref OTA_STATUS_INVAILD_ARG)
 * - [OTA_STATUS_INVAILD_RB_IMAGE](@ref OTA_STATUS_INVAILD_RB_IMAGE)
 * - [OTA_STATUS_INVAILD_FLASH_SIZE](@ref OTA_STATUS_INVAILD_FLASH_SIZE)
 * - [OTA_STATUS_AlREADY_ENABLED](@ref OTA_STATUS_AlREADY_ENABLED)
 * - [OTA_STATUS_UPDATE_INPROGRESS](@ref OTA_STATUS_UPDATE_INPROGRESS)
 */
static void OtaUpdateCb(uint8_t u8OtaUpdateStatusType, uint8_t u8OtaUpdateStatus)
{
	WDRV_DBG_INFORM_PRINT(("OtaUpdateCb: UpdateStatusType = %d, UpdateStatus = %d\r\n", u8OtaUpdateStatusType, u8OtaUpdateStatus));
	if (u8OtaUpdateStatusType == DL_STATUS) {
		if (u8OtaUpdateStatus == OTA_STATUS_SUCSESS) {
			/* Start Host Controller OTA HERE ... Before switching ... */
			WDRV_DBG_INFORM_PRINT(("OtaUpdateCb: m2m_ota_switch_firmware starts\r\n"));
			m2m_ota_switch_firmware();
		} else {
			WDRV_DBG_INFORM_PRINT(("OtaUpdateCb: OTA FAILED, UpdateStatus = %d\r\n", u8OtaUpdateStatus));
		}
	} else if (u8OtaUpdateStatusType == SW_STATUS) {
		if (u8OtaUpdateStatus == OTA_STATUS_SUCSESS) {
			WDRV_DBG_INFORM_PRINT(("OtaUpdateCb: OTA complete, please reset your board\r\n"));
			/* system_reset(); */
		}
	}
}

/**
 * \brief winc1500 task.
 *
 * winc1500 driver entry point.
 */
void winc1500_task(uint32_t pContext)
{
    tstrWifiInitParam param;
    uint8 mac[6];
    int8_t ret;

    g_winc1500_intf = (WINC1500_INTF *)pContext;

    winc1500_init();
    /* Initialize Wi-Fi parameters structure. */
    memset((uint8_t *)&param, 0, sizeof(tstrWifiInitParam));
    /* Initialize Wi-Fi driver with data and status callback. */
    param.pfAppWifiCb = wifi_cb;
    param.strEthInitParam.u8EthernetEnable = g_winc1500_intf->ethMode;
    ret = m2m_wifi_init(&param);
    if (M2M_SUCCESS != ret) {
        WDRV_ASSERT(false, "main: m2m_wifi_init call error");
    }

    if (g_winc1500_intf->ethMode) {
        TCPIP_MAC_PACKET *p_packet = winc1500_get_rx_bufer();
        if (p_packet == NULL) {
            WDRV_ASSERT(false, "No Rx Buffer Available");
            return;
        }
        m2m_wifi_set_receive_buffer(p_packet, p_packet->pDSeg->segLoad, PACKET_BUFFER_SIZE);
    } else {
        /* Init ota function. */
	    m2m_ota_init(OtaUpdateCb, OtaNotifCb);
    }

    m2m_wifi_get_mac_address(mac);
    winc1500_rf_ready(mac);
    winc1500_init_completed();

    while (true) {
        ret = m2m_wifi_handle_events(&g_wdrvext_priv.eventWait);
        if (ret != M2M_SUCCESS) {
            WDRV_ASSERT(false, "Failed to handle m2m events");
            break;
        }
        if (g_wdrvext_priv.deinit_in_progress)
            break;
    }

    m2m_wifi_deinit(NULL);
    winc1500_deinit();
    g_wdrvext_priv.deinit_in_progress = false;
    while (true)
        WDRV_TIME_DELAY(10);
}
