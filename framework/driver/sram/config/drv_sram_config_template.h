/******************************************************************************
  SRAM Driver Configuration Template Header file.

  Company:
    Microchip Technology Inc.

  File Name:
    drv_sram_config_template.h

  Summary:
    SRAM driver configuration definitions.

  Description:
    This template file describes all the mandatory and optional configuration
    macros that are needed for building the SRAM driver. Do not include this file
    in source code.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2016 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _DRV_SRAM_CONFIG_TEMPLATE_H
#define _DRV_SRAM_CONFIG_TEMPLATE_H

#error "This is a configuration template file.  Do not include it directly."

// *****************************************************************************
/* SRAM Driver instance configuration

  Summary:
    Selects the maximum number of Driver instances that can be supported by the
    dynamic driver.

  Description:
    This definition selects the maximum number of Driver instances that can be
    supported by the dynamic driver. In case of this driver, multiple instances
    of the driver could use the same hardware instance.

  Remarks:
    This macro is mandatory when building the driver for dynamic operation.
*/

#define DRV_SRAM_INSTANCES_NUMBER                        			1

// *****************************************************************************
/* SRAM maximum number of clients

  Summary:
    Selects the maximum number of clients

  Description:
    This definition selects the maximum number of clients that the SRAM driver
    can support at run time. This constant defines the total number of SRAM
    driver clients that will be available to all instances of the SRAM driver.

  Remarks:
    This macro is mandatory when building the driver for dynamic operation.
*/

#define DRV_SRAM_CLIENTS_NUMBER                          			1

// *****************************************************************************
/* SRAM Media Size for the first instance of the driver.

  Summary:
    Specifies the SRAM Media 0 size in Kilo Bytes.

  Description:
    The SRAM driver supports a maximum of two driver instances. This definition
    specifies the SRAM Media Size to be used for the first instance of the
    driver. The size is specified in number of Kilo Bytes. The media size MUST
    never exceed physical available SRAM Memory size. Application code
    requirements should be kept in mind while defining this parameter.

  Remarks:
    This macro is mandatory when building the driver for dynamic operation.
*/

#define DRV_SRAM_MEDIA_0_SIZE                                        32

// *****************************************************************************
/* SRAM Media Size for the second instance of the driver.

  Summary:
    Specifies the SRAM Media 1 size in Kilo Bytes.

  Description:
    The SRAM driver supports a maximum of two driver instances. This definition
    specifies the SRAM Media Size to be used for the second instance of the
    driver. The size is specified in number of Kilo Bytes. The media size MUST
    never exceed physical available SRAM Memory size. Application code
    requirements should be kept in mind while defining this parameter.

  Remarks:
    This macro is mandatory when building the driver for dynamic operation.
*/

#define DRV_SRAM_MEDIA_1_SIZE                                        32

// *****************************************************************************
/* SRAM Driver Disable Error Checks

  Summary:
    Disables the error checks in the driver.

  Description:
    Specifying this macro disables the error checks in the driver. Error checks like 
    parameter validation, NULL checks etc, will be disabled in the driver in order to
    optimize the code space. 

  Remarks:
    This macro is optional and should be specified only if code space is a
    constraint.
*/

#define DRV_SRAM_DISABLE_ERROR_CHECK

#endif // #ifndef _DRV_SRAM_CONFIG_TEMPLATE_H

/*******************************************************************************
 End of File
*/

