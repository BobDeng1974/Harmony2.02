/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_button.h

  Summary:
    

  Description:
    This module implements button widget functions.
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
#ifndef LIBARIA_CHECKBOX_H
#define LIBARIA_CHECKBOX_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_CHECKBOX_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_widget.h"
#include "gfx/libaria/inc/libaria_string.h"

typedef struct laCheckBoxWidget_t laCheckBoxWidget;

typedef void (*laCheckBoxWidget_CheckedEvent)(laCheckBoxWidget*);
typedef void (*laCheckBoxWidget_UncheckedEvent)(laCheckBoxWidget*);

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Structure:
    laCheckBoxWidget_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef struct laCheckBoxWidget_t
{
	laWidget widget;

	laBool checked;  

	laString text;

	laHAlignment halign;
	laVAlignment valign;

	GFXU_ImageAsset* checkedImage;
	GFXU_ImageAsset* uncheckedImage;
	
	laRelativePosition imagePosition;
	uint16_t imageMargin;
	
	GFXU_ExternalAssetReader* reader;

	laCheckBoxWidget_CheckedEvent checkedEvent;
	laCheckBoxWidget_CheckedEvent uncheckedEvent;
} laCheckBoxWidget;

void _laCheckBoxWidget_Constructor(laCheckBoxWidget* cbox);
void _laCheckBoxWidget_Destructor(laCheckBoxWidget* cbox);

void _laCheckBoxWidget_Paint(laCheckBoxWidget* cbox);


// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laCheckBoxWidget* laCheckBoxWidget_New()

  Summary:
    Creates a new instance of a check box widget.  User is responsible for
    the memory allocated until the widget is added to a widget tree.

  Description:
    

  Parameters:
	void
	
  Returns:
	laCheckBoxWidget*
	
  Remarks:
    
*/
LIB_EXPORT laCheckBoxWidget* laCheckBoxWidget_New();

// *****************************************************************************
/* Function:
    laBool laCheckBoxWidget_GetChecked(laCheckBoxWidget* cbox)

  Summary:
    Gets the checked state of the check box

  Description:
    

  Parameters:
	laCheckBoxWidget*
	
  Returns:
	laBool
	
  Remarks:
    
*/
LIB_EXPORT laBool laCheckBoxWidget_GetChecked(laCheckBoxWidget* cbox);

// *****************************************************************************
/* Function:
    void laCheckBoxWidget_SetChecked(laCheckBoxWidget* cbox,
										    laBool checked)

  Summary:
    Sets the checked state of the check box

  Description:
    

  Parameters:
	laCheckBoxWidget*
	laBool
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laCheckBoxWidget_SetChecked(laCheckBoxWidget* cbox,
										    laBool checked);

// *****************************************************************************
/* Function:
    laHAlignment laCheckBoxWidget_GetHAlignment(laCheckBoxWidget* cbox)

  Summary:
    Gets the horizontal alignment of the check box

  Description:
    

  Parameters:
	laCheckBoxWidget*
	
  Returns:
	laHAlignment
	
  Remarks:
    
*/
LIB_EXPORT laHAlignment laCheckBoxWidget_GetHAlignment(laCheckBoxWidget* cbox);

// *****************************************************************************
/* Function:
    void laCheckBoxWidget_SetHAlignment(laCheckBoxWidget* cbox,
											   laHAlignment align)

  Summary:
    Sets the horizontal alignment of the check box.

  Description:
    

  Parameters:
	laCheckBoxWidget*
	laHAlignment
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laCheckBoxWidget_SetHAlignment(laCheckBoxWidget* cbox,
											   laHAlignment align);
// *****************************************************************************
/* Function:
    laVAlignment laCheckBoxWidget_GetVAlignment(laCheckBoxWidget* cbox)

  Summary:
    Gets the vertical alignment of the check box

  Description:
    

  Parameters:
	laCheckBoxWidget*
	
  Returns:
	laVAlignment
	
  Remarks:
    
*/
LIB_EXPORT laVAlignment laCheckBoxWidget_GetVAlignment(laCheckBoxWidget* cbox);

// *****************************************************************************
/* Function:
    void laCheckBoxWidget_SetVAlignment(laCheckBoxWidget* cbox,
											   laVAlignment align)

  Summary:
    Sets the vertical alignment of the check box

  Description:
    

  Parameters:
	laCheckBoxWidget*
	laVAlignment
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laCheckBoxWidget_SetVAlignment(laCheckBoxWidget* cbox,
											   laVAlignment align);

// *****************************************************************************
/* Function:
    GFXU_ImageAsset* laCheckBoxWidget_GetCheckedImage(laCheckBoxWidget* btn)

  Summary:
    Gets the checked image of the check box

  Description:
    

  Parameters:
	laCheckBoxWidget*
	
  Returns:
	GFXU_ImageAsset*
	
  Remarks:
    
*/
LIB_EXPORT GFXU_ImageAsset* laCheckBoxWidget_GetCheckedImage(laCheckBoxWidget* btn);

// *****************************************************************************
/* Function:
    void laCheckBoxWidget_SetCheckedImage(laCheckBoxWidget* btn,
											     GFXU_ImageAsset* img)

  Summary:
    Sets the checked image of the check box

  Description:
    

  Parameters:
	laCheckBoxWidget*
	GFXU_ImageAsset*
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laCheckBoxWidget_SetCheckedImage(laCheckBoxWidget* btn,
											     GFXU_ImageAsset* img);

// *****************************************************************************
/* Function:
    GFXU_ImageAsset* laCheckBoxWidget_GetUncheckedImage(laCheckBoxWidget* btn)

  Summary:
    Gets the unchecked image of the check box

  Description:
    

  Parameters:
	laCheckBoxWidget*
	
  Returns:
	GFXU_ImageAsset*
	
  Remarks:
    
*/
LIB_EXPORT GFXU_ImageAsset* laCheckBoxWidget_GetUncheckedImage(laCheckBoxWidget* btn);

// *****************************************************************************
/* Function:
    void laCheckBoxWidget_SetUncheckedImage(laCheckBoxWidget* btn,
										           GFXU_ImageAsset* img)

  Summary:
    Sets the unchecked image of the check box

  Description:
    

  Parameters:
	laCheckBoxWidget*
	GFXU_ImageAsset*
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laCheckBoxWidget_SetUncheckedImage(laCheckBoxWidget* btn,
										           GFXU_ImageAsset* img);

// *****************************************************************************
/* Function:
    laRelativePosition laCheckBoxWidget_GetImagePosition(laCheckBoxWidget* btn)

  Summary:
    Gets the image position of the check box

  Description:
    

  Parameters:
	laCheckBoxWidget*
	
  Returns:
	laRelativePosition
	
  Remarks:
    
*/												   
LIB_EXPORT laRelativePosition laCheckBoxWidget_GetImagePosition(laCheckBoxWidget* btn);

// *****************************************************************************
/* Function:
    void laCheckBoxWidget_SetImagePosition(laCheckBoxWidget* btn, laRelativePosition pos)

  Summary:
    Sets the image position of the check box

  Description:
    

  Parameters:
	laCheckBoxWidget*
	laRelativePosition
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laCheckBoxWidget_SetImagePosition(laCheckBoxWidget* btn, laRelativePosition pos);

// *****************************************************************************
/* Function:
    uint16_t laCheckBoxWidget_GetImageMargin(laCheckBoxWidget* btn)

  Summary:
    Gets the distance between the image and the text

  Description:
    

  Parameters:
	laCheckBoxWidget*
	
  Returns:
	uint16_t
	
  Remarks:
    
*/
LIB_EXPORT uint16_t laCheckBoxWidget_GetImageMargin(laCheckBoxWidget* btn);

// *****************************************************************************
/* Function:
    void laCheckBoxWidget_SetImageMargin(laCheckBoxWidget* btn, uint16_t mg)

  Summary:
    Sets the distance between the image and the text

  Description:
    

  Parameters:
	laCheckBoxWidget*
	uint16_t
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laCheckBoxWidget_SetImageMargin(laCheckBoxWidget* btn, uint16_t mg);

// *****************************************************************************
/* Function:
    laString* laCheckBoxWidget_GetText(laCheckBoxWidget* cbox)

  Summary:
    Gets a copy of the checkbox text.  If the text has local data the data will
    be duplicated.  The caller is responsible for managing the memory 
    as appropriate.

  Description:
    

  Parameters:
	laCheckBoxWidget*
	
  Returns:
	laString*
	
  Remarks:
    
*/
LIB_EXPORT void laCheckBoxWidget_GetText(laCheckBoxWidget* cbox, laString* str);

// *****************************************************************************
/* Function:
    void laCheckBoxWidget_SetText(laCheckBoxWidget* cbox, laString str)

  Summary:
    Sets the checkbox text to the input string.  If the string has local data
    the data will be duplicated and copied to the checkboxes internal string.

  Description:
    

  Parameters:
	laCheckBoxWidget*
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laCheckBoxWidget_SetText(laCheckBoxWidget* cbox, laString str);

// *****************************************************************************
/* Function:
    laCheckBoxWidget_CheckedEvent laCheckBoxWidget_GetCheckedEventCallback(laCheckBoxWidget* cbox)

  Summary:
    Gets the checked event callback

  Description:
    

  Parameters:
	laCheckBoxWidget*
	
  Returns:
	laCheckBoxWidget_CheckedEvent
	
  Remarks:
    
*/
LIB_EXPORT laCheckBoxWidget_CheckedEvent laCheckBoxWidget_GetCheckedEventCallback(laCheckBoxWidget* cbox);

// *****************************************************************************
/* Function:
    void laCheckBoxWidget_SetCheckedEventCallback(laCheckBoxWidget* cbox,
													     laCheckBoxWidget_CheckedEvent cb)

  Summary:
    Sets the checked event callback

  Description:
    

  Parameters:
	laCheckBoxWidget*
	laCheckBoxWidget_CheckedEvent
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laCheckBoxWidget_SetCheckedEventCallback(laCheckBoxWidget* cbox,
													     laCheckBoxWidget_CheckedEvent cb);

// *****************************************************************************
/* Function:
    laCheckBoxWidget_UncheckedEvent laCheckBoxWidget_GetUncheckedEventCallback(laCheckBoxWidget* cbox)

  Summary:
    Gets the unchecked event callback

  Description:
    

  Parameters:
	laCheckBoxWidget*
	
  Returns:
	laCheckBoxWidget_UncheckedEvent
	
  Remarks:
    
*/
LIB_EXPORT laCheckBoxWidget_UncheckedEvent laCheckBoxWidget_GetUncheckedEventCallback(laCheckBoxWidget* cbox);

// *****************************************************************************
/* Function:
    void laCheckBoxWidget_SetUncheckedEventCallback(laCheckBoxWidget* cbox,
													       laCheckBoxWidget_UncheckedEvent cb)

  Summary:
    Sets the unchecked event callback

  Description:
    

  Parameters:
	laCheckBoxWidget*
	laCheckBoxWidget_UncheckedEvent
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laCheckBoxWidget_SetUncheckedEventCallback(laCheckBoxWidget* cbox,
													       laCheckBoxWidget_UncheckedEvent cb);

// internal use only
void _laCheckBoxWidget_GetImageRect(laCheckBoxWidget* widget, GFX_Rect* rect);
void _laCheckBoxWidget_TouchDownEvent(laCheckBoxWidget* widget, laInput_TouchDownEvent* evt);
void _laCheckBoxWidget_TouchUpEvent(laCheckBoxWidget* widget, laInput_TouchUpEvent* evt);
void _laCheckBoxWidget_TouchMovedEvent(laCheckBoxWidget* widget, laInput_TouchMovedEvent* evt);

#endif // LA_CHECKBOX_WIDGET_ENABLED
#endif /* LIBARIA_BUTTON_H */