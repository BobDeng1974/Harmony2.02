/*******************************************************************************
  CAN Peripheral Library Template Implementation

  File Name:
    can_FilterToChannelLink_pic32.h

  Summary:
    CAN PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : FilterToChannelLink
    and its Variant : pic32
    For following APIs :
        PLIB_CAN_FilterToChannelLink
        PLIB_CAN_ExistsFilterToChannelLink

*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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

#ifndef _CAN_FILTERTOCHANNELLINK_PIC32_H
#define _CAN_FILTERTOCHANNELLINK_PIC32_H

#include "../templates/can_registers.h"

//******************************************************************************
/* Function :  CAN_FilterToChannelLink_pic32

  Summary:
    Implements pic32 variant of PLIB_CAN_FilterToChannelLink 

  Description:
    This template implements the pic32 variant of the PLIB_CAN_FilterToChannelLink function.
*/

PLIB_TEMPLATE void CAN_FilterToChannelLink_pic32( CAN_MODULE_ID index , CAN_FILTER filter , CAN_FILTER_MASK mask , CAN_CHANNEL channel )
{
	volatile can_registers_t * can = ((can_registers_t *)(index));
    /* This function will link a filter to a channel. fltcon is the filter
      control register that is associated with the filter and sub index
      provides the shift amount with in the filter control register. The
      filter control register has four bytes each controlling a filter.
      The contents if the other filter fields should not be changed. */

    unsigned char 	regOffSET = filter%4;

	uint32_t maskbits =  _C1FLTCON0_MSEL0_MASK << (regOffSET*8);
	uint32_t position = _C1FLTCON0_MSEL0_POSITION + (regOffSET*8);

	can->CFLTCON[filter].CFLTCON0SET = (maskbits & (mask << position));

	maskbits = _C1FLTCON0_FSEL0_MASK << (regOffSET*8u);
	position = _C1FLTCON0_FSEL0_POSITION + (regOffSET*8u);

	can->CFLTCON[filter].CFLTCON0SET = (maskbits & (channel << position));
}


//******************************************************************************
/* Function :  CAN_ExistsFilterToChannelLink_pic32

  Summary:
    Implements pic32 variant of PLIB_CAN_ExistsFilterToChannelLink

  Description:
    This template implements the pic32 variant of the PLIB_CAN_ExistsFilterToChannelLink function.
*/

#define PLIB_CAN_ExistsFilterToChannelLink PLIB_CAN_ExistsFilterToChannelLink
PLIB_TEMPLATE bool CAN_ExistsFilterToChannelLink_pic32( CAN_MODULE_ID index )
{
    return true;
}


#endif /*_CAN_FILTERTOCHANNELLINK_PIC32_H*/

/******************************************************************************
 End of File
*/

