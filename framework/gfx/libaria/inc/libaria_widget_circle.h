/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_circle.h

  Summary:
    

  Description:
    This module implements circle drawing widget functions.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2016 released Microchip Technology Inc.  All rights reserved.

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
#ifndef LIBARIA_CIRCLE_H
#define LIBARIA_CIRCLE_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_CIRCLE_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_widget.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Structure:
    laCircleWidget_t

  Summary:
    Circle widget definition

  Description:
    

  Remarks:
    None.
*/
typedef struct laCircleWidget_t
{
	laWidget widget; // base widget header

    int32_t x;
    int32_t y;
    int32_t radius;
} laCircleWidget;

void _laCircleWidget_Constructor(laCircleWidget* cir);
void _laCircleWidget_Destructor(laCircleWidget* cir);

void _laCircleWidget_Paint(laCircleWidget* cir);

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laCircleWidget* laCircleWidget_New()

  Summary:
    Creats a new instance of a circle widget

  Description:
    

  Parameters:
	void
	
  Returns:
	laCircleWidget*
	
  Remarks:
    
*/
LIB_EXPORT laCircleWidget* laCircleWidget_New();

// *****************************************************************************
/* Function:
    laResult laCircleWidget_GetOrigin(laCircleWidget* cir, int32_t* x, int32_t* y)

  Summary:
    Gets the origin coordiates of a circle widget

  Description:
    

  Parameters:
	laCircleWidget*
	int32_t*
	int32_t*
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laCircleWidget_GetOrigin(laCircleWidget* cir, int32_t* x, int32_t* y);

// *****************************************************************************
/* Function:
    laResult laCircleWidget_SetOrigin(laCircleWidget* cir, int32_t x, int32_t y)

  Summary:
    Sets the origin coordiates of a circle widget

  Description:
    

  Parameters:
	laCircleWidget*
	int32_t*
	int32_t*
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laCircleWidget_SetOrigin(laCircleWidget* cir, int32_t x, int32_t y);

// *****************************************************************************
/* Function:
    uint32_t laCircleWidget_GetRadius(laCircleWidget* cir)

  Summary:
    Gets the radius of a circle widget

  Description:
    

  Parameters:
	laCircleWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laCircleWidget_GetRadius(laCircleWidget* cir);

// *****************************************************************************
/* Function:
    laResult laCircleWidget_SetRadius(laCircleWidget* cir, uint32_t rad)

  Summary:
    Sets the radius of a circle widget

  Description:
    

  Parameters:
	laCircleWidget*
	uint32_t
		
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laCircleWidget_SetRadius(laCircleWidget* cir, uint32_t rad);

#endif // LA_CIRCLE_WIDGET_ENABLED
#endif /* LIBARIA_CIRCLE_H */