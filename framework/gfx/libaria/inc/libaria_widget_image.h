/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_image.h

  Summary:
    

  Description:
    This module implements image widget functions.
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

#ifndef LIBARIA_IMAGE_H
#define LIBARIA_IMAGE_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_IMAGE_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_widget.h"

typedef struct laImageWidget_t laImageWidget;

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Enumeration:
    laImageWidget_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/	
typedef struct laImageWidget_t
{
	laWidget widget;

	laHAlignment halign;
	laVAlignment valign;

	GFXU_ImageAsset* image;
	
	GFXU_ExternalAssetReader* reader;
} laImageWidget;

void _laImageWidget_Constructor(laImageWidget* img);
void _laImageWidget_Destructor(laImageWidget* img);

void _laImageWidget_Paint(laImageWidget* img);

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laImageWidget* laImageWidget_New()

  Summary:
    

  Description:
    

  Parameters:
	void
	
  Returns:
	laImageWidget*
	
  Remarks:
    
*/
LIB_EXPORT laImageWidget* laImageWidget_New();

// *****************************************************************************
/* Function:
    laHAlignment laImageWidget_GetHAlignment(laImageWidget* img)

  Summary:
    

  Description:
    

  Parameters:
	laImageWidget*
	
  Returns:
	laHAlignment
	
  Remarks:
    
*/
LIB_EXPORT laHAlignment laImageWidget_GetHAlignment(laImageWidget* img);

// *****************************************************************************
/* Function:
    void laImageWidget_SetHAlignment(laImageWidget* img,
											laHAlignment align)

  Summary:
    

  Description:
    

  Parameters:
	laImageWidget*
	laHAlignment
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laImageWidget_SetHAlignment(laImageWidget* img,
											laHAlignment align);

// *****************************************************************************
/* Function:
    laVAlignment laImageWidget_GetVAlignment(laImageWidget* img)

  Summary:
    

  Description:
    

  Parameters:
	laImageWidget*
	
  Returns:
	laVAlignment
	
  Remarks:
    
*/
LIB_EXPORT laVAlignment laImageWidget_GetVAlignment(laImageWidget* img);

// *****************************************************************************
/* Function:
    void laImageWidget_SetVAlignment(laImageWidget* img,
											laVAlignment align)

  Summary:
    

  Description:
    

  Parameters:
	laImageWidget*
	laVAlignment
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laImageWidget_SetVAlignment(laImageWidget* img,
											laVAlignment align);													

// *****************************************************************************
/* Function:
    GFXU_ImageAsset* laImageWidget_GetImage(laImageWidget* img)

  Summary:
    

  Description:
    

  Parameters:
	laImageWidget*
	
  Returns:
	GFXU_ImageAsset*
	
  Remarks:
    
*/
LIB_EXPORT GFXU_ImageAsset* laImageWidget_GetImage(laImageWidget* img);
// *****************************************************************************
/* Function:
    void laImageWidget_SetImage(laImageWidget* img,
									   GFXU_ImageAsset* imgAst)

  Summary:
    

  Description:
    

  Parameters:
	laImageWidget*
	GFXU_ImageAsset*
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laImageWidget_SetImage(laImageWidget* img,
									   GFXU_ImageAsset* imgAst);

#endif // LA_IMAGE_WIDGET_ENABLED
#endif /* LIBARIA_IMAGE_H */