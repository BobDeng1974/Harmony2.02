/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_label.h

  Summary:
    

  Description:
    This module implements label (text) widget functions.
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
#ifndef LIBARIA_LABEL_H
#define LIBARIA_LABEL_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_LABEL_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_widget.h"
#include "gfx/libaria/inc/libaria_string.h"

typedef struct laLabelWidget_t laLabelWidget;

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Structure:
    laLabelWidget_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef struct laLabelWidget_t
{
	laWidget widget;

	laString text;

	laHAlignment halign;
	laVAlignment valign;

	GFXU_ExternalAssetReader* reader;
} laLabelWidget;

void _laLabelWidget_Constructor(laLabelWidget* lbl);
void _laLabelWidget_Destructor(laLabelWidget* lbl);

void _laLabelWidget_Paint(laLabelWidget* lbl);


// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laLabelWidget* laLabelWidget_New()

  Summary:
    

  Description:
    

  Parameters:
	
  Returns:
	laLabelWidget*
	
  Remarks:
    
*/
LIB_EXPORT laLabelWidget* laLabelWidget_New();

LIB_EXPORT void laLabelWidget_GetText(laLabelWidget* lbl, laString* str);
LIB_EXPORT void laLabelWidget_SetText(laLabelWidget* lbl, laString str);

// *****************************************************************************
/* Function:
    laHAlignment laLabelWidget_GetHAlignment(laLabelWidget* lbl)

  Summary:
    

  Description:
    

  Parameters:
	laLabelWidget*
		
  Returns:
	laHAlignment
	
  Remarks:
    
*/
LIB_EXPORT laHAlignment laLabelWidget_GetHAlignment(laLabelWidget* lbl);

// *****************************************************************************
/* Function:
    void laLabelWidget_SetHAlignment(laLabelWidget* lbl,
											laHAlignment align)

  Summary:
    

  Description:
    

  Parameters:
	laLabelWidget*
	laHAlignment
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laLabelWidget_SetHAlignment(laLabelWidget* lbl,
											laHAlignment align);

// *****************************************************************************
/* Function:
    laVAlignment laLabelWidget_GetVAlignment(laLabelWidget* lbl)

  Summary:
    

  Description:
    

  Parameters:
	laLabelWidget*
		
  Returns:
	laVAlignment
	
  Remarks:
    
*/
LIB_EXPORT laVAlignment laLabelWidget_GetVAlignment(laLabelWidget* lbl);

// *****************************************************************************
/* Function:
    void laLabelWidget_SetVAlignment(laLabelWidget* lbl,
											laVAlignment align)

  Summary:
    

  Description:
    

  Parameters:
	laLabelWidget*
	laVAlignment
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laLabelWidget_SetVAlignment(laLabelWidget* lbl,
											laVAlignment align);													

#endif // LA_IMAGE_WIDGET_ENABLED
#endif /* LIBARIA_LABEL_H */