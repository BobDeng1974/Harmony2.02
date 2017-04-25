/*** Wi-Fi Driver Configuration ***/
<#if CONFIG_DRV_WIFI_INTERRUPT_SYSTEM_SERVICE == "External Interrupt">
 <#if CONFIG_EXT_INT_INST_IDX0_USED_BY_DRV_WIFI>
#define MRF_INT_SOURCE ${CONFIG_EXT_INT_INTERRUPT_SOURCE_IDX0}
#define MRF_INT_VECTOR ${CONFIG_EXT_INT_INTERRUPT_VECTOR_IDX0}
 <#elseif CONFIG_EXT_INT_INST_IDX1_USED_BY_DRV_WIFI>
#define MRF_INT_SOURCE ${CONFIG_EXT_INT_INTERRUPT_SOURCE_IDX1}
#define MRF_INT_VECTOR ${CONFIG_EXT_INT_INTERRUPT_VECTOR_IDX1}
 <#elseif CONFIG_EXT_INT_INST_IDX2_USED_BY_DRV_WIFI>
#define MRF_INT_SOURCE ${CONFIG_EXT_INT_INTERRUPT_SOURCE_IDX2}
#define MRF_INT_VECTOR ${CONFIG_EXT_INT_INTERRUPT_VECTOR_IDX2}
 <#elseif CONFIG_EXT_INT_INST_IDX3_USED_BY_DRV_WIFI>
#define MRF_INT_SOURCE ${CONFIG_EXT_INT_INTERRUPT_SOURCE_IDX3}
#define MRF_INT_VECTOR ${CONFIG_EXT_INT_INTERRUPT_VECTOR_IDX3}
 <#elseif CONFIG_EXT_INT_INST_IDX4_USED_BY_DRV_WIFI>
#define MRF_INT_SOURCE ${CONFIG_EXT_INT_INTERRUPT_SOURCE_IDX4}
#define MRF_INT_VECTOR ${CONFIG_EXT_INT_INTERRUPT_VECTOR_IDX4}
 <#else>
#error "Please select an external interrupt instance for Wi-Fi driver."
 </#if><#-- Wi-Fi Driver External Interrupt Instance -->
<#elseif CONFIG_DRV_WIFI_INTERRUPT_SYSTEM_SERVICE == "Change Notification">
#define MRF_INT_SOURCE INT_SOURCE_CHANGE_NOTICE
#define MRF_INT_VECTOR INT_VECTOR_CN
</#if><#-- CONFIG_DRV_WIFI_INTERRUPT_SYSTEM_SERVICE -->

<#if CONFIG_DRV_WIFI_SPI_INSTANCE_INDEX == '0'>
#define DRV_WIFI_SPI_INDEX 0
#define DRV_WIFI_SPI_INSTANCE sysObj.spiObjectIdx0
<#elseif CONFIG_DRV_WIFI_SPI_INSTANCE_INDEX == '1'>
#define DRV_WIFI_SPI_INDEX 1
#define DRV_WIFI_SPI_INSTANCE sysObj.spiObjectIdx1
<#elseif CONFIG_DRV_WIFI_SPI_INSTANCE_INDEX == '2'>
#define DRV_WIFI_SPI_INDEX 2
#define DRV_WIFI_SPI_INSTANCE sysObj.spiObjectIdx2
<#elseif CONFIG_DRV_WIFI_SPI_INSTANCE_INDEX == '3'>
#define DRV_WIFI_SPI_INDEX 3
#define DRV_WIFI_SPI_INSTANCE sysObj.spiObjectIdx3
<#elseif CONFIG_DRV_WIFI_SPI_INSTANCE_INDEX == '4'>
#define DRV_WIFI_SPI_INDEX 4
#define DRV_WIFI_SPI_INSTANCE sysObj.spiObjectIdx4
<#elseif CONFIG_DRV_WIFI_SPI_INSTANCE_INDEX == '5'>
#define DRV_WIFI_SPI_INDEX 5
#define DRV_WIFI_SPI_INSTANCE sysObj.spiObjectIdx5
</#if><#-- CONFIG_DRV_WIFI_SPI_INSTANCE_INDEX -->
<#if CONFIG_DRV_WIFI_USE_SPI_DMA == true>

#define DRV_WIFI_USE_SPI_DMA
</#if><#-- CONFIG_DRV_WIFI_USE_SPI_DMA -->
<#if CONFIG_DRV_WIFI_STORE_CONFIG_IN_NVM>

#define DRV_WIFI_NVM_SPACE_ENABLE
#define DRV_WIFI_NVM_SPACE_ADDR (${CONFIG_DRV_WIFI_NVM_START_ADDRESS} * 1024)
</#if><#-- CONFIG_DRV_WIFI_STORE_CONFIG_IN_NVM -->
<#if CONFIG_3RDPARTY_RTOS_USED == "FreeRTOS">

#define DRV_WIFI_USE_FREERTOS

#define DRV_WIFI_RTOS_INIT_TASK_SIZE ${CONFIG_MRF24WG_RTOS_INIT_TASK_SIZE}u
#define DRV_WIFI_RTOS_INIT_TASK_PRIORITY ${CONFIG_MRF24WG_RTOS_INIT_TASK_PRIORITY}u
#define DRV_WIFI_RTOS_DEFERRED_ISR_SIZE ${CONFIG_MRF24WG_RTOS_DEFERRED_ISR_SIZE}u
#define DRV_WIFI_RTOS_DEFERRED_ISR_PRIORITY ${CONFIG_MRF24WG_RTOS_DEFERRED_ISR_PRIORITY}u
#define DRV_WIFI_RTOS_MAC_TASK_SIZE ${CONFIG_MRF24WG_RTOS_MAC_TASK_SIZE}u
#define DRV_WIFI_RTOS_MAC_TASK_PRIORITY ${CONFIG_MRF24WG_RTOS_MAC_TASK_PRIORITY}u
</#if><#-- CONFIG_3RDPARTY_RTOS_USED -->

// I/O mappings for general control pins, including CS, HIBERNATE, INTERRUPT and RESET.
#define WF_CS_PORT_CHANNEL          PORT_CHANNEL_${CONFIG_MRF24WG_CS_PORT_CHANNEL}
#define WF_CS_BIT_POS               ${CONFIG_MRF24WG_CS_BIT_POS}

#define WF_HIBERNATE_PORT_CHANNEL   PORT_CHANNEL_${CONFIG_MRF24WG_HIBERNATE_PORT_CHANNEL}
#define WF_HIBERNATE_BIT_POS        ${CONFIG_MRF24WG_HIBERNATE_BIT_POS}

#define WF_INT_PORT_CHANNEL         PORT_CHANNEL_${CONFIG_MRF24WG_INT_PORT_CHANNEL}
#define WF_INT_BIT_POS              ${CONFIG_MRF24WG_INT_BIT_POS}

#define WF_RESET_PORT_CHANNEL       PORT_CHANNEL_${CONFIG_MRF24WG_RESET_PORT_CHANNEL}
#define WF_RESET_BIT_POS            ${CONFIG_MRF24WG_RESET_BIT_POS}
<#if CONFIG_BSP_PIC32MX_ETH_SK == true>

#define MRF24W_USE_CN_INT

// When CN9 (Pin G7) is used as external interrupt, it is sometimes better to use another GPIO (Pin E0) to read CN9's value.
// In this case, a jumper wire is needed to connect Pin E0 and Pin G7.
//#define WF_VERIFY_EINT_BY_ANOTHER_GPIO
#if defined(WF_VERIFY_EINT_BY_ANOTHER_GPIO)
// Use Pin E0. Please also make sure that Pin E0 and Pin G7 are connected (by a jumper wire).
#define WF_INT_PORT_CHANNEL_READ    PORT_CHANNEL_E
#define WF_INT_BIT_POS_READ         0
#else
// Still directly read Pin G7's value.
#define WF_INT_PORT_CHANNEL_READ    PORT_CHANNEL_G
#define WF_INT_BIT_POS_READ         7
#endif
</#if><#-- CONFIG_BSP_PIC32MX_ETH_SK -->

<#if CONFIG_MRF24WG_NETWORK_TYPE == "Infrastructure">
#define DRV_WIFI_DEFAULT_NETWORK_TYPE       DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE
#define DRV_WIFI_DEFAULT_CHANNEL_LIST       {} /* Channel list in domain - use default in module */
#define DRV_WIFI_DEFAULT_LIST_RETRY_COUNT   (DRV_WIFI_RETRY_FOREVER) /* Number (1..255) of times to try to connect to AP when using Infrastructure network type */
<#if CONFIG_MRF24WG_INFRASTRUCTURE_SECURITY_MODE == "WPS Push Button">
#define DRV_WIFI_DEFAULT_SSID               ""
<#else>
#define DRV_WIFI_DEFAULT_SSID               "${CONFIG_MRF24WG_SSID}"
</#if>

<#if CONFIG_MRF24WG_INFRASTRUCTURE_SECURITY_MODE == "Open">
#define DRV_WIFI_DEFAULT_SECURITY_MODE      DRV_WIFI_SECURITY_OPEN
#define DRV_WIFI_DEFAULT_WEP_PHRASE         "WEP Phrase" // default WEP passphrase
#define DRV_WIFI_DEFAULT_WEP_KEY_40         "5AFB6C8E77" // default WEP40 key
#define DRV_WIFI_DEFAULT_WEP_KEY_104        "90E96780C739409DA50034FCAA" // default WEP104 key
#define DRV_WIFI_DEFAULT_PSK_PHRASE         "Microchip 802.11 Secret PSK Password" // default WPA passphrase
#define DRV_WIFI_DEFAULT_WPS_PIN            "12390212" // default WPS PIN
<#elseif CONFIG_MRF24WG_INFRASTRUCTURE_SECURITY_MODE == "WEP-40 (64-bit)">
#define DRV_WIFI_DEFAULT_SECURITY_MODE      DRV_WIFI_SECURITY_WEP_40
#define DRV_WIFI_DEFAULT_WEP_PHRASE         "${CONFIG_MRF24WG_WEP_PASS_PHRASE}" // customized WEP passphrase
#define DRV_WIFI_DEFAULT_WEP_KEY_40         "${CONFIG_MRF24WG_WEP_KEY_40}" // customized WEP40 key
#define DRV_WIFI_DEFAULT_WEP_KEY_104        "90E96780C739409DA50034FCAA" // default WEP104 key
#define DRV_WIFI_DEFAULT_PSK_PHRASE         "Microchip 802.11 Secret PSK Password" // default WPA passphrase
#define DRV_WIFI_DEFAULT_WPS_PIN            "12390212" // default WPS PIN
<#elseif CONFIG_MRF24WG_INFRASTRUCTURE_SECURITY_MODE == "WEP-104 (128-bit)">
#define DRV_WIFI_DEFAULT_SECURITY_MODE      DRV_WIFI_SECURITY_WEP_104
#define DRV_WIFI_DEFAULT_WEP_PHRASE         "${CONFIG_MRF24WG_WEP_PASS_PHRASE}" // customized WEP passphrase
#define DRV_WIFI_DEFAULT_WEP_KEY_40         "5AFB6C8E77" // default WEP40 key
#define DRV_WIFI_DEFAULT_WEP_KEY_104        "${CONFIG_MRF24WG_WEP_KEY_104}" // customized WEP104 key
#define DRV_WIFI_DEFAULT_PSK_PHRASE         "Microchip 802.11 Secret PSK Password" // default WPA passphrase
#define DRV_WIFI_DEFAULT_WPS_PIN            "12390212" // default WPS PIN
<#elseif CONFIG_MRF24WG_INFRASTRUCTURE_SECURITY_MODE == "WPA-PSK">
#define DRV_WIFI_DEFAULT_SECURITY_MODE      DRV_WIFI_SECURITY_WPA_WITH_PASS_PHRASE
#define DRV_WIFI_DEFAULT_WEP_PHRASE         "WEP Phrase" // default WEP passphrase
#define DRV_WIFI_DEFAULT_WEP_KEY_40         "5AFB6C8E77" // default WEP40 key
#define DRV_WIFI_DEFAULT_WEP_KEY_104        "90E96780C739409DA50034FCAA" // default WEP104 key
#define DRV_WIFI_DEFAULT_PSK_PHRASE         "${CONFIG_MRF24WG_WPA_PASS_PHRASE}" // customized WPA passphrase
#define DRV_WIFI_DEFAULT_WPS_PIN            "12390212" // default WPS PIN
<#elseif CONFIG_MRF24WG_INFRASTRUCTURE_SECURITY_MODE == "WPA2-PSK">
#define DRV_WIFI_DEFAULT_SECURITY_MODE      DRV_WIFI_SECURITY_WPA2_WITH_PASS_PHRASE
#define DRV_WIFI_DEFAULT_WEP_PHRASE         "WEP Phrase" // default WEP passphrase
#define DRV_WIFI_DEFAULT_WEP_KEY_40         "5AFB6C8E77" // default WEP40 key
#define DRV_WIFI_DEFAULT_WEP_KEY_104        "90E96780C739409DA50034FCAA" // default WEP104 key
#define DRV_WIFI_DEFAULT_PSK_PHRASE         "${CONFIG_MRF24WG_WPA_PASS_PHRASE}" // customized WPA passphrase
#define DRV_WIFI_DEFAULT_WPS_PIN            "12390212" // default WPS PIN
<#elseif CONFIG_MRF24WG_INFRASTRUCTURE_SECURITY_MODE == "WPA-PSK/WPA2-PSK Auto">
#define DRV_WIFI_DEFAULT_SECURITY_MODE      DRV_WIFI_SECURITY_WPA_AUTO_WITH_PASS_PHRASE
#define DRV_WIFI_DEFAULT_WEP_PHRASE         "WEP Phrase" // default WEP passphrase
#define DRV_WIFI_DEFAULT_WEP_KEY_40         "5AFB6C8E77" // default WEP40 key
#define DRV_WIFI_DEFAULT_WEP_KEY_104        "90E96780C739409DA50034FCAA" // default WEP104 key
#define DRV_WIFI_DEFAULT_PSK_PHRASE         "${CONFIG_MRF24WG_WPA_PASS_PHRASE}" // customized WPA passphrase
#define DRV_WIFI_DEFAULT_WPS_PIN            "12390212" // default WPS PIN
<#elseif CONFIG_MRF24WG_INFRASTRUCTURE_SECURITY_MODE == "WPS Push Button">
#define DRV_WIFI_DEFAULT_SECURITY_MODE      DRV_WIFI_SECURITY_WPS_PUSH_BUTTON
#define DRV_WIFI_DEFAULT_WEP_PHRASE         "WEP Phrase" // default WEP passphrase
#define DRV_WIFI_DEFAULT_WEP_KEY_40         "5AFB6C8E77" // default WEP40 key
#define DRV_WIFI_DEFAULT_WEP_KEY_104        "90E96780C739409DA50034FCAA" // default WEP104 key
#define DRV_WIFI_DEFAULT_PSK_PHRASE         "Microchip 802.11 Secret PSK Password" // default WPA passphrase
#define DRV_WIFI_DEFAULT_WPS_PIN            "12390212" // default WPS PIN
<#elseif CONFIG_MRF24WG_INFRASTRUCTURE_SECURITY_MODE == "WPS PIN">
#define DRV_WIFI_DEFAULT_SECURITY_MODE      DRV_WIFI_SECURITY_WPS_PIN
#define DRV_WIFI_DEFAULT_WEP_PHRASE         "WEP Phrase" // default WEP passphrase
#define DRV_WIFI_DEFAULT_WEP_KEY_40         "5AFB6C8E77" // default WEP40 key
#define DRV_WIFI_DEFAULT_WEP_KEY_104        "90E96780C739409DA50034FCAA" // default WEP104 key
#define DRV_WIFI_DEFAULT_PSK_PHRASE         "Microchip 802.11 Secret PSK Password" // default WPA passphrase
#define DRV_WIFI_DEFAULT_WPS_PIN            "${CONFIG_MRF24WG_WPS_PIN}" // customized WPS PIN
</#if><#-- CONFIG_MRF24WG_INFRASTRUCTURE_SECURITY_MODE -->

<#if CONFIG_MRF24WG_INFRASTRUCTURE_SECURITY_MODE == "WPS Push Button" || CONFIG_MRF24WG_INFRASTRUCTURE_SECURITY_MODE == "WPS PIN">
#define DRV_WIFI_SAVE_WPS_CREDENTIALS       DRV_WIFI_ENABLED
<#else>
#define DRV_WIFI_SAVE_WPS_CREDENTIALS       DRV_WIFI_DISABLED
</#if><#-- CONFIG_MRF24WG_INFRASTRUCTURE_SECURITY_MODE -->

#define DRV_WIFI_CHECK_LINK_STATUS          DRV_WIFI_DISABLED /* Gets the MRF to check the link status relying on Tx failures. */
#define DRV_WIFI_LINK_LOST_THRESHOLD        40 /* Consecutive Tx transmission failures to be considered the AP is gone away. */

#define DRV_WIFI_DEFAULT_POWER_SAVE         DRV_WIFI_DISABLED /* DRV_WIFI_ENABLED or DRV_WIFI_DISABLED */
<#elseif CONFIG_MRF24WG_NETWORK_TYPE == "Ad-Hoc">
#define DRV_WIFI_DEFAULT_NETWORK_TYPE       DRV_WIFI_NETWORK_TYPE_ADHOC
#define DRV_WIFI_DEFAULT_CHANNEL_LIST       {${CONFIG_MRF24WG_ADHOC_SOFTAP_OPERATING_CHANNEL}} /* Set Ad-Hoc network channel */
#define DRV_WIFI_DEFAULT_LIST_RETRY_COUNT   (DRV_WIFI_RETRY_ADHOC) /* Number (1..254) of times to try to connect to AP when using Ad-Hoc network type */
#define DRV_WIFI_DEFAULT_ADHOC_PRESCAN      DRV_WIFI_DISABLED
#define DRV_WIFI_DEFAULT_SSID               "${CONFIG_MRF24WG_SSID}"

<#if CONFIG_MRF24WG_ADHOC_SOFTAP_SECURITY_MODE == "Open">
#define DRV_WIFI_DEFAULT_SECURITY_MODE      DRV_WIFI_SECURITY_OPEN
#define DRV_WIFI_DEFAULT_WEP_PHRASE         "WEP Phrase" // default WEP passphrase
#define DRV_WIFI_DEFAULT_WEP_KEY_40         "5AFB6C8E77" // default WEP40 key
#define DRV_WIFI_DEFAULT_WEP_KEY_104        "90E96780C739409DA50034FCAA" // default WEP104 key
#define DRV_WIFI_DEFAULT_PSK_PHRASE         "Microchip 802.11 Secret PSK Password" // default WPA passphrase
#define DRV_WIFI_DEFAULT_WPS_PIN            "12390212" // default WPS PIN
<#elseif CONFIG_MRF24WG_ADHOC_SOFTAP_SECURITY_MODE == "WEP-40 (64-bit)">
#define DRV_WIFI_DEFAULT_SECURITY_MODE      DRV_WIFI_SECURITY_WEP_40
#define DRV_WIFI_DEFAULT_WEP_PHRASE         "${CONFIG_MRF24WG_WEP_PASS_PHRASE}" // customized WEP passphrase
#define DRV_WIFI_DEFAULT_WEP_KEY_40         "${CONFIG_MRF24WG_WEP_KEY_40}" // customized WEP40 key
#define DRV_WIFI_DEFAULT_WEP_KEY_104        "90E96780C739409DA50034FCAA" // default WEP104 key
#define DRV_WIFI_DEFAULT_PSK_PHRASE         "Microchip 802.11 Secret PSK Password" // default WPA passphrase
#define DRV_WIFI_DEFAULT_WPS_PIN            "12390212" // default WPS PIN
<#elseif CONFIG_MRF24WG_ADHOC_SOFTAP_SECURITY_MODE == "WEP-104 (128-bit)">
#define DRV_WIFI_DEFAULT_SECURITY_MODE      DRV_WIFI_SECURITY_WEP_104
#define DRV_WIFI_DEFAULT_WEP_PHRASE         "${CONFIG_MRF24WG_WEP_PASS_PHRASE}" // customized WEP passphrase
#define DRV_WIFI_DEFAULT_WEP_KEY_40         "5AFB6C8E77" // default WEP40 key
#define DRV_WIFI_DEFAULT_WEP_KEY_104        "${CONFIG_MRF24WG_WEP_KEY_104}" // customized WEP104 key
#define DRV_WIFI_DEFAULT_PSK_PHRASE         "Microchip 802.11 Secret PSK Password" // default WPA passphrase
#define DRV_WIFI_DEFAULT_WPS_PIN            "12390212" // default WPS PIN
</#if><#-- CONFIG_MRF24WG_ADHOC_SOFTAP_SECURITY_MODE -->

#define DRV_WIFI_SAVE_WPS_CREDENTIALS       DRV_WIFI_DISABLED

#define DRV_WIFI_CHECK_LINK_STATUS          DRV_WIFI_DISABLED /* Gets the MRF to check the link status relying on Tx failures. */
#define DRV_WIFI_LINK_LOST_THRESHOLD        40 /* Consecutive Tx transmission failures to be considered the AP is gone away. */

#define DRV_WIFI_DEFAULT_POWER_SAVE         DRV_WIFI_DISABLED /* PS_POLL not supported in Ad-Hoc - must be set to DRV_WIFI_DISABLED */

#define DRV_WIFI_ENABLE_STATIC_IP
<#elseif CONFIG_MRF24WG_NETWORK_TYPE == "Soft AP">
#define DRV_WIFI_DEFAULT_NETWORK_TYPE       DRV_WIFI_NETWORK_TYPE_SOFT_AP
#define DRV_WIFI_DEFAULT_CHANNEL_LIST       {${CONFIG_MRF24WG_ADHOC_SOFTAP_OPERATING_CHANNEL}} /* Set Soft AP network channel */
#define DRV_WIFI_DEFAULT_LIST_RETRY_COUNT   (DRV_WIFI_RETRY_ADHOC) /* Dummy, not used */
#define DRV_WIFI_DEFAULT_SSID               "${CONFIG_MRF24WG_SSID}"

<#if CONFIG_MRF24WG_ADHOC_SOFTAP_SECURITY_MODE == "Open">
#define DRV_WIFI_DEFAULT_SECURITY_MODE      DRV_WIFI_SECURITY_OPEN
#define DRV_WIFI_DEFAULT_WEP_PHRASE         "WEP Phrase" // default WEP passphrase
#define DRV_WIFI_DEFAULT_WEP_KEY_40         "5AFB6C8E77" // default WEP40 key
#define DRV_WIFI_DEFAULT_WEP_KEY_104        "90E96780C739409DA50034FCAA" // default WEP104 key
#define DRV_WIFI_DEFAULT_PSK_PHRASE         "Microchip 802.11 Secret PSK Password" // default WPA passphrase
#define DRV_WIFI_DEFAULT_WPS_PIN            "12390212" // default WPS PIN
<#elseif CONFIG_MRF24WG_ADHOC_SOFTAP_SECURITY_MODE == "WEP-40 (64-bit)">
#define DRV_WIFI_DEFAULT_SECURITY_MODE      DRV_WIFI_SECURITY_WEP_40
#define DRV_WIFI_DEFAULT_WEP_PHRASE         "${CONFIG_MRF24WG_WEP_PASS_PHRASE}" // customized WEP passphrase
#define DRV_WIFI_DEFAULT_WEP_KEY_40         "${CONFIG_MRF24WG_WEP_KEY_40}" // customized WEP40 key
#define DRV_WIFI_DEFAULT_WEP_KEY_104        "90E96780C739409DA50034FCAA" // default WEP104 key
#define DRV_WIFI_DEFAULT_PSK_PHRASE         "Microchip 802.11 Secret PSK Password" // default WPA passphrase
#define DRV_WIFI_DEFAULT_WPS_PIN            "12390212" // default WPS PIN
<#elseif CONFIG_MRF24WG_ADHOC_SOFTAP_SECURITY_MODE == "WEP-104 (128-bit)">
#define DRV_WIFI_DEFAULT_SECURITY_MODE      DRV_WIFI_SECURITY_WEP_104
#define DRV_WIFI_DEFAULT_WEP_PHRASE         "${CONFIG_MRF24WG_WEP_PASS_PHRASE}" // customized WEP passphrase
#define DRV_WIFI_DEFAULT_WEP_KEY_40         "5AFB6C8E77" // default WEP40 key
#define DRV_WIFI_DEFAULT_WEP_KEY_104        "${CONFIG_MRF24WG_WEP_KEY_104}" // customized WEP104 key
#define DRV_WIFI_DEFAULT_PSK_PHRASE         "Microchip 802.11 Secret PSK Password" // default WPA passphrase
#define DRV_WIFI_DEFAULT_WPS_PIN            "12390212" // default WPS PIN
</#if><#-- CONFIG_MRF24WG_ADHOC_SOFTAP_SECURITY_MODE -->

#define DRV_WIFI_SAVE_WPS_CREDENTIALS       DRV_WIFI_DISABLED

#define DRV_WIFI_CHECK_LINK_STATUS          DRV_WIFI_DISABLED /* Gets the MRF to check the link status relying on Tx failures. */
#define DRV_WIFI_LINK_LOST_THRESHOLD        40 /* Consecutive Tx transmission failures to be considered the AP is gone away. */
#define DRV_WIFI_SOFTAP_SEND_KEEP_ALIVE     DRV_WIFI_DISABLED /* Gets Soft AP to send keep alive packets to clients. */
#define DRV_WIFI_SOFTAP_LINK_LOST_THRESHOLD 40 /* Consecutive null packet transmission failures to be considered the client STA is gone away. */

#define DRV_WIFI_DEFAULT_POWER_SAVE         DRV_WIFI_DISABLED /* PS_POLL not supported in Soft AP - must be set to DRV_WIFI_DISABLED */

#define DRV_WIFI_ENABLE_STATIC_IP
</#if><#-- CONFIG_MRF24WG_NETWORK_TYPE -->

/*
 * MRF24W FW has a built-in connection manager, and it is enabled by default.
 * If you want to run your own connection manager in host side, you should
 * disable the FW connection manager to avoid possible conflict between the two.
 * Especially these two APIs can be affected if you do not disable it.
 * A) uint16_t DRV_WIFI_Disconnect(void)
 * B) uint16_t DRV_WIFI_Scan(bool scanAll)
 * These APIs will return failure when the conflict occurs.
 */
#define DRV_WIFI_MODULE_CONNECTION_MANAGER  DRV_WIFI_ENABLED

#define DRV_WIFI_SOFTWARE_MULTICAST_FILTER  DRV_WIFI_ENABLED

#define DRV_WIFI_CONFIG_MHC

#define DRV_WIFI_ASSERT(condition, msg) DRV_WIFI_Assert(condition, msg, __FILE__, __LINE__)
<#--
/*******************************************************************************
 End of File
 */
-->