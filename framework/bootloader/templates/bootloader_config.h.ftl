<#--
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

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
 -->
// *****************************************************************************
// Section: Bootloader Configuration
// *****************************************************************************
<#if CONFIG_USE_LIVE_UPDATE == true>
#define BOOTLOADER_STATE_SAVE 1
</#if>
/* BOOTLOADER_BASE_ADDRESS and BOOTLOADER_END_ADDRESS reserves program Flash for the application*/
/* Rule:
    1)The memory regions kseg0_program_mem, kseg0_boot_mem, exception_mem and
    kseg1_boot_mem of the application linker script must fall with in APP_FLASH_BASE_ADDRESS
    and APP_FLASH_END_ADDRESS

    2)The base address and end address must align on boundaries according to the flash page size */
<#if CONFIG_PIC32MZ == false>
    <#if CONFIG_BOOT_ADDR_SIZE == "0xbf0">
        <#if CONFIG_BOOTLOADER_TYPE == "USB_HOST">
            <#assign bootloader_length = "0x13C00">
        <#elseif CONFIG_BOOTLOADER_TYPE == "ETHERNET_UDP_PULL">
            <#assign bootloader_length = "0x13000">
        <#elseif CONFIG_BOOTLOADER_TYPE == "USB_DEVICE">
            <#assign bootloader_length = "0x7400">
        <#elseif CONFIG_BOOTLOADER_TYPE == "USART" || CONFIG_BOOTLOADER_TYPE == "I2C">
            <#assign bootloader_length = "0x2000">
        <#else>
            <#assign bootloader_length = "0x3000">
        </#if>
    <#else>
        <#if CONFIG_BOOTLOADER_TYPE == "USB_HOST">
            <#assign bootloader_length = "0x14000">
        <#elseif CONFIG_BOOTLOADER_TYPE == "ETHERNET_UDP_PULL">
            <#assign bootloader_length = "0x13000">
        <#elseif CONFIG_BOOTLOADER_TYPE == "USB_DEVICE">
            <#assign bootloader_length = "0x7000">
        <#elseif CONFIG_BOOTLOADER_TYPE == "USART" || CONFIG_BOOTLOADER_TYPE == "I2C">
            <#assign bootloader_length = "0x0000">
        <#else>
            <#assign bootloader_length = "0x3000">
        </#if>
    </#if>
    <#if CONFIG_BOOT_ADDR_SIZE == "0xbf0">
        <#lt>#define BOOTLOADER_FLASH_BASE_ADDRESS  (0x9D000000 + ${bootloader_length})
    <#elseif CONFIG_BOOTLOADER_TYPE != "USART" && CONFIG_BOOTLOADER_TYPE != "I2C">
        <#lt>#define BOOTLOADER_FLASH_BASE_ADDRESS  (0x9D000000 + ${bootloader_length})
    <#else>
        <#lt>#define BOOTLOADER_FLASH_BASE_ADDRESS   0x9D000000
    </#if>
<#else>
#define BOOTLOADER_FLASH_BASE_ADDRESS   0x9D000000
</#if>
#define BOOTLOADER_FLASH_END_ADDRESS    (0x9D000000 + ${CONFIG_PFM_ADDR_SIZE} - 1)

/* Address of  the Flash from where the application starts executing */
/* Rule: Set BOOTLOADER_FLASH_BASE_ADDRESS to _RESET_ADDR value of application linker script*/
#define BOOTLOADER_RESET_ADDRESS    (BOOTLOADER_FLASH_BASE_ADDRESS)
<#if CONFIG_BOOTLOADER_TRIGGER_TYPE != "NONE">
#define BOOTLOADER_LEGACY
#define BTL_SWITCH                           <#if CONFIG_BOOTLOADER_TRIGGER_TYPE == "BUTTON">BSP_SWITCH_3<#else>0</#if>
#define BOOTLOADER_FLASH_TRIGGER_ADDRESS     <#if CONFIG_BOOTLOADER_TRIGGER_TYPE == "MEMORY">${CONFIG_BOOTLOADER_TRIGGER_MEMORY}<#else>0</#if>
</#if>
<#if CONFIG_BOOTLOADER_TYPE == "ETHERNET_UDP_PULL">
#define BOOTLOADER_UDP_PORT_NUMBER "${CONFIG_BOOTLOADER_PORT_NUMBER}"
</#if>
<#if CONFIG_BOOTLOADER_TYPE == "USB_HOST" || CONFIG_BOOTLOADER_TYPE == "SD_CARD">
#define BOOTLOADER_IMAGE_FILE_NAME  "${CONFIG_DATASTREAM_USBHOST_FILENAME}"
</#if>

// *****************************************************************************
// Section: Bootloader NVM Driver Configuration
// *****************************************************************************
/* NVM Driver Flash Memory row and page size in bytes */
<#if CONFIG_PIC32MZ == false>
    <#if (CONFIG_BOOTLOADER_TYPE != "USART" && CONFIG_BOOTLOADER_TYPE != "I2C") || CONFIG_BOOT_ADDR_SIZE == "0xbf0">
        <#lt>#define USE_PAGE_ERASE  1
    <#else>
        <#lt>#define USE_PAGE_ERASE  0
    </#if>
    <#lt>#define USE_QUAD_WORD_WRITE 0
<#else>
    <#lt>#define USE_PAGE_ERASE  0
    <#lt>#define USE_QUAD_WORD_WRITE 1
</#if>

<#--
/*******************************************************************************
 End of File
*/
-->

