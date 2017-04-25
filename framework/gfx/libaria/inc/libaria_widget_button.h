/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_button.h

  Summary:
    Defines a button widget
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
#ifndef LIBARIA_BUTTON_H
#define LIBARIA_BUTTON_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_BUTTON_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_widget.h"
#include "gfx/libaria/inc/libaria_string.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Enumeration:
    laButtonState_t

  Summary:
    Controls the button pressed state
*/

typedef enum laButtonState_t
{
	LA_BUTTON_STATE_UP,
	LA_BUTTON_STATE_DOWN,
	LA_BUTTON_STATE_TOGGLED
} laButtonState;

typedef struct laButtonWidget_t laButtonWidget;

typedef void (*laButtonWidget_PressedEvent)(laButtonWidget*);
typedef void (*laButtonWidget_ReleasedEvent)(laButtonWidget*);

// *****************************************************************************
/* Structure:
    laButtonWidget_t

  Summary:
    Implementation of a button widget.

  Description:
    

  Remarks:
    None.
*/
typedef struct laButtonWidget_t
{
	laWidget widget;  // base widget header

	laButtonState state; // button state
	uint8_t toggleable; // indicates if the button is toggleable

	laString text; // the string that holds the button text

	laHAlignment halign; // horizontal alignment of the button
	laVAlignment valign; // vertical alignment of the button

	GFXU_ImageAsset* pressedImage; // button pressed icon image
	GFXU_ImageAsset* releasedImage; // button released icon image
	
	laRelativePosition imagePosition; // icon position in relation to text
	uint32_t imageMargin; // distance between text and icon
	int32_t pressedOffset; // pressed text offset distance

	laButtonWidget_PressedEvent pressedEvent; // pressed event callback
	laButtonWidget_ReleasedEvent releasedEvent; // released event callback

	GFXU_ExternalAssetReader* reader; // external asset reader state
} laButtonWidget;

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************


void _laButtonWidget_Constructor(laButtonWidget* btn);
void _laButtonWidget_Destructor(laButtonWidget* btn);

void _laButtonWidget_Paint(laButtonWidget* btn);

// *****************************************************************************
/* Function:
    laButtonWidget* laButtonWidget_New()

  Summary:
    Creates a new button widget instance.  Invokes the button constructor

  Description:
    Creates a new button widget instance.  Invokes the button constructor

  Returns:
	laButtonWidget* - pointer to a new button widget instance
	
  Remarks:
    Caller is responsible for managing the memory allocated by this function
    until the widget is added to a valid widget tree.
*/
LIB_EXPORT laButtonWidget* laButtonWidget_New();

// *****************************************************************************
/* Function:
    laBool laButtonWidget_GetToggleable(laButtonWidget* btn)

  Summary:
    Gets the value of this button's toggle flag 

  Description:
    
  Parameters:
	laButtonWidget* btn - the button to reference
	
  Returns:
	laBool - the value of the toggle flag
    
*/
LIB_EXPORT laBool laButtonWidget_GetToggleable(laButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laButtonWidget_SetToggleable(laButtonWidget* btn,
									  laBool toggleable)

  Summary:
    Enables the toggle mode for a button.  When pressed, toggle buttons will
    stay down until pressed again.

  Description:
    
  Parameters:
	laButtonWidget* btn - the button to modify
	laBool toggleable - the desired togglestate
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laButtonWidget_SetToggleable(laButtonWidget* btn,
										     laBool toggleable);
										     
// *****************************************************************************
/* Function:
    laBool laButtonWidget_GetPressed(laButtonWidget* btn)

  Summary:
    Gets the pressed state of a button

  Description:
    
  Parameters:
	laButtonWidget* btn - the button to reference
		
  Returns:
	laBool - the button pressed state
	
  Remarks:
    
*/										  
LIB_EXPORT laBool laButtonWidget_GetPressed(laButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laButtonWidget_SetPressed(laButtonWidget* btn, laBool pressed)

  Summary:
    Sets the pressed state for a button.

  Description:
    
  Parameters:
	laButtonWidget* btn - the button to modify
	laBool pressed - the pressed state
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laButtonWidget_SetPressed(laButtonWidget* btn, laBool pressed);									

// *****************************************************************************
/* Function:
    void laButtonWidget_GetText(laButtonWidget* btn, laString* str)

  Summary:
    Gets the text for a button.  If the button's string has local data then
    a duplicate of the string will be allocated.  The caller is responsible
    for managing the memory for the duplicated string.  If the button string
    is a string table reference then only the reference ID is copied.

  Description:
    
  Parameters:
	laButtonWidget* btn - the button to reference
	laString* str - pointer to a string to copy the button string into
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laButtonWidget_GetText(laButtonWidget* btn, laString* str);

// *****************************************************************************
/* Function:
    void laButtonWidget_SetText(laButtonWidget* btn, laString str)

  Summary:
    Sets the text for a button.  If the input string has local data then
    the data will be copied into the button's local string, causing a memory
    allocation.  If the input string is a string table reference then only the
    reference will be copied.  The input string can be safely modified and
    the button string will not be affected.  
    
  Description:
    
  Parameters:
	laButtonWidget* btn - the button to modify
	laString str - the string to set to the button
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laButtonWidget_SetText(laButtonWidget* btn, laString str);

// *****************************************************************************
/* Function:
    laHAlignment laButtonWidget_GetHAlignment(laButtonWidget* btn)

  Summary:
    Gets the horizontal alignment setting for a button

  Description:
    
  Parameters:
	laButtonWidget* btn - the button to reference
		
  Returns:
	laHAlignment - the horizontal alignment value
	
  Remarks:
    
*/	
LIB_EXPORT laHAlignment laButtonWidget_GetHAlignment(laButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laButtonWidget_SetHAlignment(laButtonWidget* btn,
											 laHAlignment align)

  Summary:
    Sets the horizontal alignment value for a button

  Description:
    
  Parameters:
	laButtonWidget* btn - the button to modify
	laHAlignment align - the desired alignment value
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laButtonWidget_SetHAlignment(laButtonWidget* btn,
											 laHAlignment align);
											 
// *****************************************************************************
/* Function:
    laVAlignment laButtonWidget_GetVAlignment(laButtonWidget* btn)

  Summary:
    Gets the vertical alignment setting for a button

  Description:
    
  Parameters:
	laButtonWidget* btn - the button to reference
		
  Returns:
	laVAlignment - the vertical alignment setting for the button
	
  Remarks:
    
*/	
LIB_EXPORT laVAlignment laButtonWidget_GetVAlignment(laButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laButtonWidget_SetVAlignment(laButtonWidget* btn,
											 laVAlignment align)

  Summary:
    Sets the vertical alignment for a button

  Description:
    
  Parameters:
	laButtonWidget* btn - the btn to modify
	laVAlignment align - the desired vertical alignment setting
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laButtonWidget_SetVAlignment(laButtonWidget* btn,
											 laVAlignment align);													

// *****************************************************************************
/* Function:
    GFXU_ImageAsset* laButtonWidget_GetPressedImage(laButtonWidget* btn)

  Summary:
    Gets the pressed image asset pointer for a button

  Description:
    
  Parameters:
	laButtonWidget* btn - the button to reference
		
  Returns:
	GFXU_ImageAsset*
	
  Remarks:
    
*/	
LIB_EXPORT GFXU_ImageAsset* laButtonWidget_GetPressedImage(laButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laButtonWidget_SetPressedImage(laButtonWidget* btn,
											   GFXU_ImageAsset* img)

  Summary:
    Sets the image to be used as a pressed icon

  Description:
    
  Parameters:
	laButtonWidget*  
	GFXU_ImageAsset*
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laButtonWidget_SetPressedImage(laButtonWidget* btn,
											   GFXU_ImageAsset* img);

// *****************************************************************************
/* Function:
    GFXU_ImageAsset* laButtonWidget_GetReleasedImage(laButtonWidget* btn)

  Summary:
    Gets the currently used released icon

  Description:
    
  Parameters:
	laButtonWidget* btn - the button to reference
		
  Returns:
	GFXU_ImageAsset*
	
  Remarks:
    
*/	
LIB_EXPORT GFXU_ImageAsset* laButtonWidget_GetReleasedImage(laButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laButtonWidget_SetReleasedImage(laButtonWidget* btn,
												GFXU_ImageAsset* img)

  Summary:
    Sets the image to be used as the released icon

  Description:
    
  Parameters:
	laButtonWidget*  
	GFXU_ImageAsset*
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laButtonWidget_SetReleasedImage(laButtonWidget* btn,
												GFXU_ImageAsset* img);
												
// *****************************************************************************
/* Function:
    laRelativePosition laButtonWidget_GetImagePosition(laButtonWidget* btn)

  Summary:
    Gets the position of the button icon

  Description:
    
  Parameters:
	laButtonWidget* btn - the button to reference
		
  Returns:
	laRelativePosition
	
  Remarks:
    
*/	
LIB_EXPORT laRelativePosition laButtonWidget_GetImagePosition(laButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laButtonWidget_SetImagePosition(laButtonWidget* btn, laRelativePosition pos)

  Summary:
    Sets the position of the button icon

  Description:
    
  Parameters:
	laButtonWidget*  
	laRelativePosition
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laButtonWidget_SetImagePosition(laButtonWidget* btn, laRelativePosition pos);

// *****************************************************************************
/* Function:
    uint32_t laButtonWidget_GetImageMargin(laButtonWidget* btn)

  Summary:
    Gets the distance between the icon and the text

  Description:
    
  Parameters:
	laButtonWidget* btn - the button to reference
		
  Returns:
	uint32_t
	
  Remarks:
    
*/	
LIB_EXPORT uint32_t laButtonWidget_GetImageMargin(laButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laButtonWidget_SetImageMargin(laButtonWidget* btn, uint32_t mg)

  Summary:
    Sets the distance between the icon and text

  Description:
    
  Parameters:
	laButtonWidget*  
	uint32_t
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laButtonWidget_SetImageMargin(laButtonWidget* btn, uint32_t mg);

// *****************************************************************************
/* Function:
    int32_t laButtonWidget_GetPressedOffset(laButtonWidget* btn)

  Summary:
    Gets the offset of the button internals when pressed

  Description:
    
  Parameters:
	laButtonWidget* btn - the button to reference
		
  Returns:
	int32_t
	
  Remarks:
    
*/	
LIB_EXPORT int32_t laButtonWidget_GetPressedOffset(laButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laButtonWidget_SetPressedOffset(laButtonWidget* btn, int32_t offs)

  Summary:
    Sets the offset of the button internals when pressed

  Description:
    
  Parameters:
	laButtonWidget*  
	int32_t
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laButtonWidget_SetPressedOffset(laButtonWidget* btn, int32_t offs);

// *****************************************************************************
/* Function:
    laButtonWidget_PressedEvent laButtonWidget_GetPressedEventCallback(laButtonWidget* btn)

  Summary:
    Gets the callback associated with the button pressed event

  Description:
    
  Parameters:
	laButtonWidget* btn - the button to reference
		
  Returns:
	laButtonWidget_PressedEvent
	
  Remarks:
    
*/	
LIB_EXPORT laButtonWidget_PressedEvent laButtonWidget_GetPressedEventCallback(laButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laButtonWidget_SetPressedEventCallback(laButtonWidget* btn,
												laButtonWidget_PressedEvent cb)

  Summary:
    Sets the pressed event callback for the button

  Description:
    
  Parameters:
	laButtonWidget*  
	laButtonWidget_PressedEvent
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laButtonWidget_SetPressedEventCallback(laButtonWidget* btn,
													   laButtonWidget_PressedEvent cb);
// *****************************************************************************
/* Function:
    laButtonWidget_ReleasedEvent laButtonWidget_GetReleasedEventCallback(laButtonWidget* btn)
    
  Summary:
    Gets the callback for the button released event

  Description:
    
  Parameters:
	laButtonWidget* btn - the button to reference
		
  Returns:
	laButtonWidget_ReleasedEvent
	
  Remarks:
    
*/	
LIB_EXPORT laButtonWidget_ReleasedEvent laButtonWidget_GetReleasedEventCallback(laButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laButtonWidget_SetReleasedEventCallback(laButtonWidget* btn,
												 laButtonWidget_ReleasedEvent cb)

  Summary:
    Sets the callback for the button released event

  Description:
    
  Parameters:
	laButtonWidget*  
	laButtonWidget_ReleasedEvent
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laButtonWidget_SetReleasedEventCallback(laButtonWidget* btn,
														laButtonWidget_ReleasedEvent cb);

#endif /* LA_BUTTON_WIDGET_ENABLED */
#endif /* LIBARIA_BUTTON_H */

