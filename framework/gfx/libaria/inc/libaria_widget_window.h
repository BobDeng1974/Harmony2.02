/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_window.h

  Summary:
    Window Widget

  Description:
    This module implements window container widget functions.
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
#ifndef LIBARIA_WINDOW_H
#define LIBARIA_WINDOW_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_WINDOW_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_widget.h"
#include "gfx/libaria/inc/libaria_string.h"

typedef struct laWindowWidget_t laWindowWidget;

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Structure:
    laWindowWidget_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef struct laWindowWidget_t
{
	laWidget widget;

	laString title;
	
	GFXU_ImageAsset* icon;
	uint32_t iconMargin;
	
	struct
	{
	    GFX_Rect barRect;
	} paintData;

	GFXU_ExternalAssetReader* reader;
} laWindowWidget;

void _laWindowWidget_Constructor(laWindowWidget* win);
void _laWindowWidget_Destructor(laWindowWidget* win);

void _laWindowWidget_Paint(laWindowWidget* win);

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laWindowWidget* laWindowWidget_New()

  Summary:
    

  Description:
    

  Parameters:
	
  Returns:
	laWindowWidget*
	
  Remarks:
    
*/
LIB_EXPORT laWindowWidget* laWindowWidget_New();

LIB_EXPORT void laWindowWidget_GetTitle(laWindowWidget* win, laString* str);
LIB_EXPORT void laWindowWidget_SetTitle(laWindowWidget* win, laString str);

// *****************************************************************************
/* Function:
    GFXU_ImageAsset* laWindowWidget_GetIcon(laWindowWidget* win)

  Summary:
    

  Description:
    

  Parameters:
	laWindowWidget*
		
  Returns:
	GFXU_ImageAsset*
	
  Remarks:
    
*/
LIB_EXPORT GFXU_ImageAsset* laWindowWidget_GetIcon(laWindowWidget* win);

// *****************************************************************************
/* Function:
    laResult laWindowWidget_SetIcon(laWindowWidget* win,
                                           GFXU_ImageAsset* img)

  Summary:
    

  Description:
    

  Parameters:
	laWindowWidget*
	GFXU_ImageAsset*
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laWindowWidget_SetIcon(laWindowWidget* win,
                                           GFXU_ImageAsset* img);

// *****************************************************************************
/* Function:
    uint32_t laWindowWidget_GetIconMargin(laWindowWidget* win)

  Summary:
    

  Description:
    

  Parameters:
	laWindowWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/                                           
LIB_EXPORT uint32_t laWindowWidget_GetIconMargin(laWindowWidget* win);

// *****************************************************************************
/* Function:
    laResult laWindowWidget_SetIconMargin(laWindowWidget* win, uint32_t mg)

  Summary:
    

  Description:
    

  Parameters:
	laWindowWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/ 
LIB_EXPORT laResult laWindowWidget_SetIconMargin(laWindowWidget* win, uint32_t mg);													

#endif // LA_WINDOW_WIDGET_ENABLED
#endif /* LIBARIA_WINDOW_H */