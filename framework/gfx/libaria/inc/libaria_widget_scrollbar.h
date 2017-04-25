/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_scrollbar.h

  Summary:
    

  Description:
    This module implements scroll bar widget functions.
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
#ifndef LIBARIA_SCROLLBAR_H
#define LIBARIA_SCROLLBAR_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_SCROLLBAR_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_widget.h"
#include "gfx/libaria/inc/libaria_string.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Enumeration:
    laScrollBarState_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef enum laScrollBarState_t
{
	LA_SCROLLBAR_STATE_NONE,
	LA_SCROLLBAR_STATE_TOP_PRESSED,
	LA_SCROLLBAR_STATE_TOP_INSIDE,
	LA_SCROLLBAR_STATE_BOTTOM_PRESSED,
	LA_SCROLLBAR_STATE_BOTTOM_INSIDE,
	LA_SCROLLBAR_STATE_HANDLE_DOWN
} laScrollBarState;

// *****************************************************************************
/* Enumeration:
    laScrollBarOrientation_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef enum laScrollBarOrientation_t
{
    LA_SCROLLBAR_ORIENT_VERTICAL,
    LA_SCROLLBAR_ORIENT_HORIZONTAL
} laScrollBarOrientation;

typedef struct laScrollBarWidget_t laScrollBarWidget;

typedef void (*laScrollBarWidget_ValueChangedEvent)(laScrollBarWidget*);

// *****************************************************************************
/* Structure:
    laScrollBarWidget_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef struct laScrollBarWidget_t
{
	laWidget widget;

	laScrollBarState state;
    laScrollBarOrientation alignment;
    
    //uint32_t min;
    uint32_t max;
    uint32_t extent;
    uint32_t value;
    uint32_t step;
	
	laScrollBarWidget_ValueChangedEvent valueChangedEvent;
	
	GFX_Point handleDownOffset;
} laScrollBarWidget;

void _laScrollBarWidget_Constructor(laScrollBarWidget* bar);
void _laScrollBarWidget_Destructor(laScrollBarWidget* bar);

void _laScrollBarWidget_Update(laScrollBarWidget* bar);
void _laScrollBarWidget_Paint(laScrollBarWidget* bar);

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laScrollBarWidget* laScrollBarWidget_New()

  Summary:
    

  Description:
    

  Parameters:
	
  Returns:
	laScrollBarWidget*
	
  Remarks:
    
*/
LIB_EXPORT laScrollBarWidget* laScrollBarWidget_New();

// *****************************************************************************
/* Function:
    laScrollBarOrientation laScrollBarWidget_GetOrientation(laScrollBarWidget* bar)

  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
	
  Returns:
	laScrollBarOrientation
	
  Remarks:
    
*/
LIB_EXPORT laScrollBarOrientation laScrollBarWidget_GetOrientation(laScrollBarWidget* bar);

// *****************************************************************************
/* Function:
    void laScrollBarWidget_SetOrientation(laScrollBarWidget* bar,
											     laScrollBarOrientation align)

  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
	laScrollBarOrientation
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laScrollBarWidget_SetOrientation(laScrollBarWidget* bar,
											     laScrollBarOrientation align,
								                 laBool swapDimensions);

// *****************************************************************************
/* Function:
    uint32_t laScrollBarWidget_GetMaxinumValue(laScrollBarWidget* bar)

  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/												 
LIB_EXPORT uint32_t laScrollBarWidget_GetMaxinumValue(laScrollBarWidget* bar);

// *****************************************************************************
/* Function:
    laResult laScrollBarWidget_SetMaximumValue(laScrollBarWidget* bar,
                                                      uint32_t val)
  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laScrollBarWidget_SetMaximumValue(laScrollBarWidget* bar,
                                                      uint32_t val);                                                     

// *****************************************************************************
/* Function:
    uint32_t laScrollBarWidget_GetExtentValue(laScrollBarWidget* bar)
  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
	
	
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laScrollBarWidget_GetExtentValue(laScrollBarWidget* bar);

// *****************************************************************************
/* Function:
    laResult laScrollBarWidget_SetExtentValue(laScrollBarWidget* bar,
                                                     uint32_t val)
  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laScrollBarWidget_SetExtentValue(laScrollBarWidget* bar,
                                                     uint32_t val); 

// *****************************************************************************
/* Function:
    uint32_t laScrollBarWidget_GetScrollValue(laScrollBarWidget* bar)
	
  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/                                                     
LIB_EXPORT uint32_t laScrollBarWidget_GetScrollValue(laScrollBarWidget* bar);

// *****************************************************************************
/* Function:
    laResult laScrollBarWidget_SetScrollValue(laScrollBarWidget* bar,
                                                     uint32_t val)
  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laScrollBarWidget_SetScrollValue(laScrollBarWidget* bar,
                                                     uint32_t val);         

// *****************************************************************************
/* Function:
    uint32_t laScrollBarWidget_GetScrollPercentage(laScrollBarWidget* bar)
  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/                                                     
LIB_EXPORT uint32_t laScrollBarWidget_GetScrollPercentage(laScrollBarWidget* bar);

// *****************************************************************************
/* Function:
    laResult laScrollBarWidget_SetScrollPercentage(laScrollBarWidget* bar,
                                                          uint32_t val)
  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laScrollBarWidget_SetScrollPercentage(laScrollBarWidget* bar,
                                                          uint32_t val);                                                                                                 

// *****************************************************************************
/* Function:
    uint32_t laScrollBarWidget_GetStepSize(laScrollBarWidget* bar)
	
  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/														  
LIB_EXPORT uint32_t laScrollBarWidget_GetStepSize(laScrollBarWidget* bar);

// *****************************************************************************
/* Function:
    laResult laScrollBarWidget_SetStepSize(laScrollBarWidget* bar,
                                                  uint32_t val)
												  
  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laScrollBarWidget_SetStepSize(laScrollBarWidget* bar,
                                                  uint32_t val);

// *****************************************************************************
/* Function:
    laResult laScrollBarWidget_StepBackward(laScrollBarWidget* bar)
	
  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
		
  Returns:
	laResult
	
  Remarks:
    
*/                                                  
LIB_EXPORT laResult laScrollBarWidget_StepBackward(laScrollBarWidget* bar);

// *****************************************************************************
/* Function:
    laResult laScrollBarWidget_StepForward(laScrollBarWidget* bar)
	
  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
		
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laScrollBarWidget_StepForward(laScrollBarWidget* bar);

// *****************************************************************************
/* Function:
    laScrollBarWidget_ValueChangedEvent laScrollBarWidget_GetValueChangedEventCallback(laScrollBarWidget* bar)
  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
		
  Returns:
	laScrollBarWidget_ValueChangedEvent
	
  Remarks:
    
*/											  
LIB_EXPORT laScrollBarWidget_ValueChangedEvent laScrollBarWidget_GetValueChangedEventCallback(laScrollBarWidget* bar);

// *****************************************************************************
/* Function:
    void laScrollBarWidget_SetValueChangedEventCallback(laScrollBarWidget* bar,
													           laScrollBarWidget_ValueChangedEvent cb)
  Summary:
    

  Description:
    

  Parameters:
	laScrollBarWidget*
	laScrollBarWidget_ValueChangedEvent
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laScrollBarWidget_SetValueChangedEventCallback(laScrollBarWidget* bar,
													           laScrollBarWidget_ValueChangedEvent cb);

void _laScrollBarWidget_TouchDownEvent(laScrollBarWidget* bar, laInput_TouchDownEvent* evt);
void _laScrollBarWidget_TouchUpEvent(laScrollBarWidget* bar, laInput_TouchUpEvent* evt);
void _laScrollBarWidget_TouchMovedEvent(laScrollBarWidget* bar, laInput_TouchMovedEvent* evt);

void _laScrollBar_GetUpLeftButtonRect(laScrollBarWidget* bar, GFX_Rect* rect);
void _laScrollBar_GetDownRightButtonRect(laScrollBarWidget* bar, GFX_Rect* rect);
void _laScrollBar_GetScrollAreaRect(laScrollBarWidget* bar, GFX_Rect* rect);
void _laScrollBar_GetHandleRect(laScrollBarWidget* bar, GFX_Rect* rect);

uint32_t _laScrollWidget_GetExtent(laScrollBarWidget* bar);
uint32_t _laScrollBar_GetPercentFromPoint(laScrollBarWidget* bar, GFX_Point* pnt);
uint32_t _laScrollBar_GetValueFromPercent(laScrollBarWidget* bar, uint32_t per);

#endif // LA_SCROLLBAR_WIDGET_ENABLED
#endif /* LIBARIA_SCROLLBAR_H */