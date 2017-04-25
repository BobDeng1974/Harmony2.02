/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_rectangle.h

  Summary:
    

  Description:
    This module implements rectangle drawing widget functions.
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

#ifndef LIBARIA_RECTANGLE_H
#define LIBARIA_RECTANGLE_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_RECTANGLE_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_widget.h"

typedef struct laRectangleWidget_t laRectangleWidget;

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Enumeration:
    laRectangleWidget_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef struct laRectangleWidget_t
{
	laWidget widget;

    uint32_t thickness;
} laRectangleWidget;

void _laRectangleWidget_Constructor(laRectangleWidget* rect);
void _laRectangleWidget_Destructor(laRectangleWidget* rect);

void _laRectangleWidget_Paint(laRectangleWidget* rect);

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laRectangleWidget* laRectangleWidget_New()

  Summary:
    

  Description:
    

  Parameters:
	
  Returns:
	laRectangleWidget*
	
  Remarks:
    
*/
LIB_EXPORT laRectangleWidget* laRectangleWidget_New();
//LIB_EXPORT void laRectangleWidget_Delete(laRectangleWidget* rect);

// *****************************************************************************
/* Function:
    uint32_t laRectangleWidget_GetThickness(laRectangleWidget* rect)

  Summary:
    

  Description:
    

  Parameters:
	laRectangleWidget*
	
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laRectangleWidget_GetThickness(laRectangleWidget* rect);

// *****************************************************************************
/* Function:
    laResult laRectangleWidget_SetThickness(laRectangleWidget* rect, uint32_t thk)

  Summary:
    

  Description:
    

  Parameters:
	laRectangleWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laRectangleWidget_SetThickness(laRectangleWidget* rect, uint32_t thk);

#endif // LA_RECTANGLE_WIDGET_ENABLED
#endif /* LIBARIA_RECTANGLE_H */