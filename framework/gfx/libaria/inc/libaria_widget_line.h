/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_line.h

  Summary:
    

  Description:
    This module implements line draw widget functions.
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
#ifndef LIBARIA_LINE_H
#define LIBARIA_LINE_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_LINE_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_widget.h"

typedef struct laLineWidget_t laLineWidget;

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Structure:
    laLineWidget_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef struct laLineWidget_t
{
	laWidget widget;

    int32_t x1;
    int32_t y1;
    int32_t x2;
    int32_t y2;
} laLineWidget;

void _laLineWidget_Constructor(laLineWidget* line);
void _laLineWidget_Destructor(laLineWidget* line);

void _laLineWidget_Paint(laLineWidget* line);

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laLineWidget* laLineWidget_New()

  Summary:
    

  Description:
    

  Parameters:
	
  Returns:
	laLineWidget*
	
  Remarks:
    
*/
LIB_EXPORT laLineWidget* laLineWidget_New();

// *****************************************************************************
/* Function:
    laResult laLineWidget_GetStartPoint(laLineWidget* line, int32_t* x, int32_t* y)

  Summary:
    

  Description:
    

  Parameters:
	laLineWidget
	int32_t*
	int32_t*
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laLineWidget_GetStartPoint(laLineWidget* line, int32_t* x, int32_t* y);

// *****************************************************************************
/* Function:
    laResult laLineWidget_SetStartPoint(laLineWidget* line, int32_t x, int32_t y)

  Summary:
    

  Description:
    

  Parameters:
	laLineWidget
	int32_t
	int32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laLineWidget_SetStartPoint(laLineWidget* line, int32_t x, int32_t y);

// *****************************************************************************
/* Function:
    laResult laLineWidget_GetEndPoint(laLineWidget* line, int32_t* x, int32_t* y)

  Summary:
    

  Description:
    

  Parameters:
	laLineWidget
	int32_t*
	int32_t*
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laLineWidget_GetEndPoint(laLineWidget* line, int32_t* x, int32_t* y);

// *****************************************************************************
/* Function:
    laResult laLineWidget_SetEndPoint(laLineWidget* line, int32_t x, int32_t y)

  Summary:
    

  Description:
    

  Parameters:
	laLineWidget
	int32_t
	int32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laLineWidget_SetEndPoint(laLineWidget* line, int32_t x, int32_t y);

#endif // LA_LINE_WIDGET_ENABLED
#endif /* LIBARIA_LINE_H */