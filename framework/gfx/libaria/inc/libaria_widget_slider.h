/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_slider.h

  Summary:
    

  Description:
    This module implements slider control widget functions.
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
#ifndef LIBARIA_SLIDER_H
#define LIBARIA_SLIDER_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_SLIDER_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_widget.h"
#include "gfx/libaria/inc/libaria_string.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Enumeration:
    laSliderState_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef enum laSliderState_t
{
	LA_SLIDER_STATE_NONE,
	LA_SLIDER_STATE_HANDLE_DOWN,
	LA_SLIDER_STATE_AREA_DOWN
} laSliderState;

// *****************************************************************************
/* Enumeration:
    laSliderOrientation_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef enum laSliderOrientation_t
{
    LA_SLIDER_ORIENT_VERTICAL,
    LA_SLIDER_ORIENT_HORIZONTAL
} laSliderOrientation;

typedef struct laSliderWidget_t laSliderWidget;

typedef void (*laSliderWidget_ValueChangedEvent)(laSliderWidget*);

// *****************************************************************************
/* Structure:
    laSliderOrientation_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef struct laSliderWidget_t
{
	laWidget widget;

	laSliderState state;
    laSliderOrientation alignment;
    
    int32_t min;
    int32_t max;
    int32_t value;
    uint32_t grip;
	
	laSliderWidget_ValueChangedEvent valueChangedEvent;
	
	GFX_Point handleDownOffset;
} laSliderWidget;

void _laSliderWidget_Constructor(laSliderWidget* sld);
void _laSliderWidget_Destructor(laSliderWidget* sld);

void _laSliderWidget_Update(laSliderWidget* sld);
void _laSliderWidget_Paint(laSliderWidget* sld);

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laSliderWidget* laSliderWidget_New()

  Summary:
    

  Description:
    

  Parameters:
	
  Returns:
	laSliderWidget*
	
  Remarks:
    
*/
LIB_EXPORT laSliderWidget* laSliderWidget_New();

// *****************************************************************************
/* Function:
    laSliderOrientation laSliderWidget_GetOrientation(laSliderWidget* sld)

  Summary:
    

  Description:
    

  Parameters:
	laSliderWidget*
	
  Returns:
	laSliderOrientation
	
  Remarks:
    
*/
LIB_EXPORT laSliderOrientation laSliderWidget_GetOrientation(laSliderWidget* sld);

// *****************************************************************************
/* Function:
    laResult laSliderWidget_SetOrientation(laSliderWidget* sld,
										          laSliderOrientation align,
								                  laBool swapDimensions)

  Summary:
    

  Description:
    

  Parameters:
	laSliderWidget*
	laSliderOrientation
	laBool
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laSliderWidget_SetOrientation(laSliderWidget* sld,
										          laSliderOrientation align,
								                  laBool swapDimensions);

// *****************************************************************************
/* Function:
    laSliderOrientation laSliderWidget_GetGripSize(laSliderWidget* sld)

  Summary:
    

  Description:
    

  Parameters:
	laSliderWidget*
	
  Returns:
	laSliderOrientation
	
  Remarks:
    
*/												  
LIB_EXPORT laSliderOrientation laSliderWidget_GetGripSize(laSliderWidget* sld);

// *****************************************************************************
/* Function:
    laResult laSliderWidget_SetGripSize(laSliderWidget* sld,
										       uint32_t size)

  Summary:
    

  Description:
    

  Parameters:
	laSliderWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laSliderWidget_SetGripSize(laSliderWidget* sld,
										       uint32_t size);

// *****************************************************************************
/* Function:
    uint32_t laSliderWidget_GetMininumValue(laSliderWidget* sld)

  Summary:
    

  Description:
    

  Parameters:
	laSliderWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/											   
LIB_EXPORT uint32_t laSliderWidget_GetMininumValue(laSliderWidget* sld);

// *****************************************************************************
/* Function:
    laResult laSliderWidget_SetMinimumValue(laSliderWidget* sld,
                                                      uint32_t val)

  Summary:
    

  Description:
    

  Parameters:
	laSliderWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laSliderWidget_SetMinimumValue(laSliderWidget* sld,
                                                      uint32_t val);

// *****************************************************************************
/* Function:
    uint32_t laSliderWidget_GetMaxinumValue(laSliderWidget* sld)

  Summary:
    

  Description:
    

  Parameters:
	laSliderWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/                                                      
LIB_EXPORT uint32_t laSliderWidget_GetMaxinumValue(laSliderWidget* sld);

// *****************************************************************************
/* Function:
    laResult laSliderWidget_SetMaximumValue(laSliderWidget* sld,
                                                      uint32_t val)

  Summary:
    

  Description:
    

  Parameters:
	laSliderWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laSliderWidget_SetMaximumValue(laSliderWidget* sld,
                                                      uint32_t val);                                                     

// *****************************************************************************
/* Function:
    uint32_t laSliderWidget_GetSliderValue(laSliderWidget* sld)

  Summary:
    

  Description:
    

  Parameters:
	laSliderWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/													  
LIB_EXPORT int32_t laSliderWidget_GetSliderValue(laSliderWidget* sld);

// *****************************************************************************
/* Function:
    laResult laSliderWidget_SetSliderValue(laSliderWidget* sld,
                                           int32_t val)

  Summary:
    

  Description:
    

  Parameters:
	laSliderWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laSliderWidget_SetSliderValue(laSliderWidget* sld,
                                                  int32_t val);         

// *****************************************************************************
/* Function:
    uint32_t laSliderWidget_GetSliderPercentage(laSliderWidget* sld)

  Summary:
    

  Description:
    

  Parameters:
	laSliderWidget*
		
  Returns:
	int32_t
	
  Remarks:
    
*/												  
LIB_EXPORT uint32_t laSliderWidget_GetSliderPercentage(laSliderWidget* sld);

// *****************************************************************************
/* Function:
    laResult laSliderWidget_SetSliderPercentage(laSliderWidget* sld,
                                                uint32_t val)

  Summary:
    

  Description:
    

  Parameters:
	laSliderWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laSliderWidget_SetSliderPercentage(laSliderWidget* sld,
                                                       uint32_t val);                                                                                                 

// *****************************************************************************
/* Function:
    laResult laSliderWidget_Step(laSliderWidget* sld, int32_t amount)

  Summary:
    

  Description:
    

  Parameters:
	laSliderWidget*
	int32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/													   
LIB_EXPORT laResult laSliderWidget_Step(laSliderWidget* sld, int32_t amount);

// *****************************************************************************
/* Function:
    laSliderWidget_ValueChangedEvent laSliderWidget_GetValueChangedEventCallback(laSliderWidget* sld)

  Summary:
    

  Description:
    

  Parameters:
	laSliderWidget*
		
  Returns:
	laSliderWidget_ValueChangedEvent
	
  Remarks:
    
*/											  
LIB_EXPORT laSliderWidget_ValueChangedEvent laSliderWidget_GetValueChangedEventCallback(laSliderWidget* sld);

// *****************************************************************************
/* Function:
    void laSliderWidget_SetValueChangedEventCallback(laSliderWidget* sld,
													        laSliderWidget_ValueChangedEvent cb)

  Summary:
    

  Description:
    

  Parameters:
	laSliderWidget*
	laSliderWidget_ValueChangedEvent
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laSliderWidget_SetValueChangedEventCallback(laSliderWidget* sld,
													        laSliderWidget_ValueChangedEvent cb);

void _laSliderWidget_TouchDownEvent(laSliderWidget* sld, laInput_TouchDownEvent* evt);
void _laSliderWidget_TouchUpEvent(laSliderWidget* sld, laInput_TouchUpEvent* evt);
void _laSliderWidget_TouchMovedEvent(laSliderWidget* sld, laInput_TouchMovedEvent* evt);

void _laSlider_GetSlideAreaRect(laSliderWidget* sld, GFX_Rect* rect);
void _laSlider_GetHandleRect(laSliderWidget* sld, GFX_Rect* rect);

uint32_t _laSlider_GetPercentFromPoint(laSliderWidget* sld, GFX_Point* pnt);
uint32_t _laSlider_GetValueFromPercent(laSliderWidget* sld, uint32_t per);

#endif // LA_SLIDER_WIDGET_ENABLED
#endif /* LIBARIA_SLIDER_H */