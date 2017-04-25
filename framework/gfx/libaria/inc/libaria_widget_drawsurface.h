/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_drawsurface.h

  Summary:
    

  Description:
    This module implements surface container drawing functions.
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

#ifndef LIBARIA_DRAWSURFACE_H
#define LIBARIA_DRAWSURFACE_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_DRAWSURFACE_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_widget.h"

typedef struct laDrawSurfaceWidget_t laDrawSurfaceWidget;

typedef laBool (*laDrawSurfaceWidget_DrawCallback)(laDrawSurfaceWidget* sfc,
                                                   GFX_Rect* bounds);

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Structure:
    laDrawSurfaceWidget_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/												   
typedef struct laDrawSurfaceWidget_t
{
	laWidget widget;

    laDrawSurfaceWidget_DrawCallback cb;
} laDrawSurfaceWidget;

void _laDrawSurfaceWidget_Constructor(laDrawSurfaceWidget* sfc);
void _laDrawSurfaceWidget_Destructor(laDrawSurfaceWidget* sfc);

void _laDrawSurfaceWidget_Paint(laDrawSurfaceWidget* sfc);

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laDrawSurfaceWidget* laDrawSurfaceWidget_New()

  Summary:
    

  Description:
    

  Parameters:
	void
	
  Returns:
	laDrawSurfaceWidget*
	
  Remarks:
    
*/
LIB_EXPORT laDrawSurfaceWidget* laDrawSurfaceWidget_New();

// *****************************************************************************
/* Function:
    laDrawSurfaceWidget_DrawCallback laDrawSurfaceWidget_GetDrawCallback(laDrawSurfaceWidget* sfc)

  Summary:
    

  Description:
    

  Parameters:
	laDrawSurfaceWidget*
	
  Returns:
	laDrawSurfaceWidget_DrawCallback
	
  Remarks:
    
*/
LIB_EXPORT laDrawSurfaceWidget_DrawCallback laDrawSurfaceWidget_GetDrawCallback(laDrawSurfaceWidget* sfc);

// *****************************************************************************
/* Function:
    laResult laDrawSurfaceWidget_SetDrawCallback(laDrawSurfaceWidget* sfc,
		   								                laDrawSurfaceWidget_DrawCallback cb)

  Summary:
    

  Description:
    

  Parameters:
	laDrawSurfaceWidget*
	laDrawSurfaceWidget_DrawCallback
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laDrawSurfaceWidget_SetDrawCallback(laDrawSurfaceWidget* sfc,
		   								                laDrawSurfaceWidget_DrawCallback cb);

#endif // LA_DRAWSURFACE_WIDGET_ENABLED
#endif /* LIBARIA_DRAWSURFACE_H */