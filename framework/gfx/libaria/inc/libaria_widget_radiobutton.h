/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_radiobutton.h

  Summary:
    

  Description:
    This module implements radio button widget functions.
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
#ifndef LIBARIA_RADIOBUTTON_H
#define LIBARIA_RADIOBUTTON_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_RADIOBUTTON_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_widget.h"
#include "gfx/libaria/inc/libaria_radiobutton_group.h"
#include "gfx/libaria/inc/libaria_string.h"

typedef struct laRadioButtonWidget_t laRadioButtonWidget;
typedef struct laRadioButtonGroup_t laRadioButtonGroup;

typedef void (*laRadioButtonWidget_SelectedEvent)(laRadioButtonWidget*);
typedef void (*laRadioButtonWidget_DeselectedEvent)(laRadioButtonWidget*);

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Enumeration:
    laRadioButtonWidget_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef struct laRadioButtonWidget_t
{
	laWidget widget;

	laBool selected;
	//uint8_t toggleable;

	laString text;

	laHAlignment halign;
	laVAlignment valign;

	GFXU_ImageAsset* selectedImage;
	GFXU_ImageAsset* unselectedImage;
	
	laRelativePosition imagePosition;
	uint16_t imageMargin;

	laRadioButtonWidget_SelectedEvent selectedEvent;
	laRadioButtonWidget_DeselectedEvent deselectedEvent;

	struct
	{
	    uint8_t enabled;
	} paintData;
	
	GFXU_ExternalAssetReader* reader;

	laRadioButtonGroup* group;
} laRadioButtonWidget;

void _laRadioButtonWidget_Constructor(laRadioButtonWidget* btn);
void _laRadioButtonWidget_Destructor(laRadioButtonWidget* btn);

void _laRadioButtonWidget_Paint(laRadioButtonWidget* btn);


// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laRadioButtonWidget* laRadioButtonWidget_New()

  Summary:
    

  Description:
    

  Parameters:
	
  Returns:
	laProgressBarWidget*
	
  Remarks:
    
*/
LIB_EXPORT laRadioButtonWidget* laRadioButtonWidget_New();
//LIB_EXPORT void laRadioButtonWidget_Delete(laRadioButtonWidget* btn);

// *****************************************************************************
/* Function:
    laRadioButtonGroup* laRadioButtonWidget_GetGroup(laRadioButtonWidget* btn)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
	
  Returns:
	laRadioButtonGroup*
	
  Remarks:
    
*/
LIB_EXPORT laRadioButtonGroup* laRadioButtonWidget_GetGroup(laRadioButtonWidget* btn);

// *****************************************************************************
/* Function:
    laBool laRadioButtonWidget_GetSelected(laRadioButtonWidget* btn)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
	
  Returns:
	laBool
	
  Remarks:
    
*/
LIB_EXPORT laBool laRadioButtonWidget_GetSelected(laRadioButtonWidget* btn);

// *****************************************************************************
/* Function:
    laResult laRadioButtonWidget_SetSelected(laRadioButtonWidget* btn)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laRadioButtonWidget_SetSelected(laRadioButtonWidget* btn);

void _laRadioButtonWidget_Select(laRadioButtonWidget* btn);
void _laRadioButtonWidget_Deselect(laRadioButtonWidget* btn);

LIB_EXPORT void laRadioButtonWidget_GetText(laRadioButtonWidget* btn, laString* str);
LIB_EXPORT void laRadioButtonWidget_SetText(laRadioButtonWidget* btn, laString str);

// *****************************************************************************
/* Function:
    laHAlignment laRadioButtonWidget_GetHAlignment(laRadioButtonWidget* btn)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
		
  Returns:
	laHAlignment
	
  Remarks:
    
*/	
LIB_EXPORT laHAlignment laRadioButtonWidget_GetHAlignment(laRadioButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laRadioButtonWidget_SetHAlignment(laRadioButtonWidget* btn,
												  laHAlignment align)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
	laHAlignment
	
  Returns:
	void	
	
  Remarks:
    
*/	
LIB_EXPORT void laRadioButtonWidget_SetHAlignment(laRadioButtonWidget* btn,
												  laHAlignment align);

// *****************************************************************************
/* Function:
    laVAlignment laRadioButtonWidget_GetVAlignment(laRadioButtonWidget* btn)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
		
  Returns:
	laVAlignment
	
  Remarks:
    
*/	
LIB_EXPORT laVAlignment laRadioButtonWidget_GetVAlignment(laRadioButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laRadioButtonWidget_SetVAlignment(laRadioButtonWidget* btn,
												  laVAlignment align)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
	laVAlignment
	
  Returns:
	void
		
  Remarks:
    
*/	
LIB_EXPORT void laRadioButtonWidget_SetVAlignment(laRadioButtonWidget* btn,
												  laVAlignment align);													

// *****************************************************************************
/* Function:
    GFXU_FontAsset* laRadioButtonWidget_GetTextFont(laRadioButtonWidget* btn)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
		
  Returns:
	GFXU_FontAsset*
	
  Remarks:
    
*/	
LIB_EXPORT GFXU_FontAsset* laRadioButtonWidget_GetTextFont(laRadioButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laRadioButtonWidget_SetTextFont(laRadioButtonWidget* btn,
									            GFXU_FontAsset* fnt)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
	GFXU_FontAsset*
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laRadioButtonWidget_SetTextFont(laRadioButtonWidget* btn,
									            GFXU_FontAsset* fnt);

// *****************************************************************************
/* Function:
    GFXU_ImageAsset* laRadioButtonWidget_GetSelectedImage(laRadioButtonWidget* btn)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
		
  Returns:
	GFXU_ImageAsset*
	
  Remarks:
    
*/	
LIB_EXPORT GFXU_ImageAsset* laRadioButtonWidget_GetSelectedImage(laRadioButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laRadioButtonWidget_SetSelectedImage(laRadioButtonWidget* btn,
											         GFXU_ImageAsset* img)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
	GFXU_ImageAsset*
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laRadioButtonWidget_SetSelectedImage(laRadioButtonWidget* btn,
											         GFXU_ImageAsset* img);

// *****************************************************************************
/* Function:
    GFXU_ImageAsset* laRadioButtonWidget_GetUnselectedImage(laRadioButtonWidget* btn)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
		
  Returns:
	GFXU_ImageAsset*
	
  Remarks:
    
*/	
LIB_EXPORT GFXU_ImageAsset* laRadioButtonWidget_GetUnselectedImage(laRadioButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laRadioButtonWidget_SetUnselectedImage(laRadioButtonWidget* btn,
										               GFXU_ImageAsset* img)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
	GFXU_ImageAsset*
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laRadioButtonWidget_SetUnselectedImage(laRadioButtonWidget* btn,
										               GFXU_ImageAsset* img);

// *****************************************************************************
/* Function:
    laRelativePosition laRadioButtonWidget_GetImagePosition(laRadioButtonWidget* btn)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
		
  Returns:
	laRelativePosition
	
  Remarks:
    
*/														   
LIB_EXPORT laRelativePosition laRadioButtonWidget_GetImagePosition(laRadioButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laRadioButtonWidget_SetImagePosition(laRadioButtonWidget* btn, laRelativePosition pos)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
	laRelativePosition
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laRadioButtonWidget_SetImagePosition(laRadioButtonWidget* btn, laRelativePosition pos);

// *****************************************************************************
/* Function:
    uint16_t laRadioButtonWidget_GetImageMargin(laRadioButtonWidget* btn)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
		
  Returns:
	uint16_t
	
  Remarks:
    
*/	
LIB_EXPORT uint16_t laRadioButtonWidget_GetImageMargin(laRadioButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laRadioButtonWidget_SetImageMargin(laRadioButtonWidget* btn, uint16_t mg)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
	uint16_t
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laRadioButtonWidget_SetImageMargin(laRadioButtonWidget* btn, uint16_t mg);

// *****************************************************************************
/* Function:
    laRadioButtonWidget_SelectedEvent laRadioButtonWidget_GetSelectedEventCallback(laRadioButtonWidget* btn)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
		
  Returns:
	laRadioButtonWidget_SelectedEvent
	
  Remarks:
    
*/	
LIB_EXPORT laRadioButtonWidget_SelectedEvent laRadioButtonWidget_GetSelectedEventCallback(laRadioButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laRadioButtonWidget_SetSelectedEventCallback(laRadioButtonWidget* btn,
													         laRadioButtonWidget_SelectedEvent cb)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
	laRadioButtonWidget_SelectedEvent
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laRadioButtonWidget_SetSelectedEventCallback(laRadioButtonWidget* btn,
													         laRadioButtonWidget_SelectedEvent cb);

// *****************************************************************************
/* Function:
    laRadioButtonWidget_DeselectedEvent laRadioButtonWidget_GetDeselectedEventCallback(laRadioButtonWidget* btn)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
		
  Returns:
	laRadioButtonWidget_DeselectedEvent
	
  Remarks:
    
*/	
LIB_EXPORT laRadioButtonWidget_DeselectedEvent laRadioButtonWidget_GetDeselectedEventCallback(laRadioButtonWidget* btn);

// *****************************************************************************
/* Function:
    void laRadioButtonWidget_SetDeselectedEventCallback(laRadioButtonWidget* btn,
													           laRadioButtonWidget_DeselectedEvent cb)

  Summary:
    

  Description:
    

  Parameters:
	laRadioButtonWidget*
	laRadioButtonWidget_DeselectedEvent
	
  Returns:
	void
	
  Remarks:
    
*/	
LIB_EXPORT void laRadioButtonWidget_SetDeselectedEventCallback(laRadioButtonWidget* btn,
													           laRadioButtonWidget_DeselectedEvent cb);

void _laRadioButtonWidget_GetImageRect(laRadioButtonWidget* btn, GFX_Rect* rect);

void _laRadioButtonWidget_TouchDownEvent(laRadioButtonWidget* widget, laInput_TouchDownEvent* evt);
void _laRadioButtonWidget_TouchUpEvent(laRadioButtonWidget* widget, laInput_TouchUpEvent* evt);
void _laRadioButtonWidget_TouchMovedEvent(laRadioButtonWidget* widget, laInput_TouchMovedEvent* evt);

#endif // LA_RADIOBUTTON_WIDGET_ENABLED
#endif /* LIBARIA_RADIOBUTTON_H */