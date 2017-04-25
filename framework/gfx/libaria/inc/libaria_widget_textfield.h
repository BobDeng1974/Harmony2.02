/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_textfield.h

  Summary:
    

  Description:
    This module implements text field widget functions.
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

#ifndef LIBARIA_TEXTFIELD_H
#define LIBARIA_TEXTFIELD_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_TEXTFIELD_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_editwidget.h"
#include "gfx/libaria/inc/libaria_string.h"

typedef struct laTextFieldWidget_t laTextFieldWidget;

typedef void (*laTextFieldWidget_TextChangedCallback)(laTextFieldWidget*);

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Enumeration:
    laTextFieldWidget_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef struct laTextFieldWidget_t
{
	laEditWidget editWidget;

	laString text;

	laHAlignment halign;
	
	laBool editable;

    uint32_t cursorPos;
    uint32_t cursorDelay;
	uint32_t cursorTime;
	laBool cursorEnable;
	laBool cursorVisible;
	
	laTextFieldWidget_TextChangedCallback textChangedEvent;
	
	GFXU_ExternalAssetReader* reader;
} laTextFieldWidget;

void _laTextFieldWidget_Constructor(laTextFieldWidget* txt);
void _laTextFieldWidget_Destructor(laTextFieldWidget* txt);

void _laTextFieldWidget_Update(laTextFieldWidget* img, uint32_t dt);
void _laTextFieldWidget_Paint(laTextFieldWidget* txt);

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laTextFieldWidget* laTextFieldWidget_New()

  Summary:
    

  Description:
    

  Parameters:
	
  Returns:
	laTextFieldWidget*
	
  Remarks:
    
*/
LIB_EXPORT laTextFieldWidget* laTextFieldWidget_New();

LIB_EXPORT void laTextFieldWidget_GetText(laTextFieldWidget* txt, laString* str);
LIB_EXPORT void laTextFieldWidget_SetText(laTextFieldWidget* txt, laString str);

// *****************************************************************************
/* Function:
    laHAlignment laTextFieldWidget_GetAlignment(laTextFieldWidget* txt)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
		
  Returns:
	laHAlignment
	
  Remarks:
    
*/
LIB_EXPORT laHAlignment laTextFieldWidget_GetAlignment(laTextFieldWidget* txt);

// *****************************************************************************
/* Function:
    void laTextFieldWidget_SetAlignment(laTextFieldWidget* txt,
										       laHAlignment align)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
	laHAlignment
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laTextFieldWidget_SetAlignment(laTextFieldWidget* txt,
										       laHAlignment align);

// *****************************************************************************
/* Function:
    uint32_t laTextFieldWidget_GetCursorDelay(laTextFieldWidget* txt)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/										       
LIB_EXPORT uint32_t laTextFieldWidget_GetCursorDelay(laTextFieldWidget* txt);

// *****************************************************************************
/* Function:
    void laTextFieldWidget_SetCursorDelay(laTextFieldWidget* txt,
										         uint32_t dt)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
	uint32_t
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laTextFieldWidget_SetCursorDelay(laTextFieldWidget* txt,
										         uint32_t dt);

// *****************************************************************************
/* Function:
    laBool laTextFieldWidget_GetCursorEnabled(laTextFieldWidget* txt)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
		
  Returns:
	laBool
	
  Remarks:
    
*/
LIB_EXPORT laBool laTextFieldWidget_GetCursorEnabled(laTextFieldWidget* txt);

// *****************************************************************************
/* Function:
    void laTextFieldWidget_SetCursorEnabled(laTextFieldWidget* txt,
										           laBool en)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
	laBool
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laTextFieldWidget_SetCursorEnabled(laTextFieldWidget* txt,
										           laBool en);

// *****************************************************************************
/* Function:
    uint32_t laTextFieldWidget_GetCursorPosition(laTextFieldWidget* txt)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/												   
LIB_EXPORT uint32_t laTextFieldWidget_GetCursorPosition(laTextFieldWidget* txt);

// *****************************************************************************
/* Function:
    void laTextFieldWidget_SetCursorPosition(laTextFieldWidget* txt,
										            uint32_t pos)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
	uint32_t
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laTextFieldWidget_SetCursorPosition(laTextFieldWidget* txt,
										            uint32_t pos);

// *****************************************************************************
/* Function:
    laTextFieldWidget_TextChangedCallback laTextFieldWidget_GetTextChangedEventCallback(laTextFieldWidget* txt)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
		
  Returns:
	laTextFieldWidget_TextChangedCallback
	
  Remarks:
    
*/													
LIB_EXPORT laTextFieldWidget_TextChangedCallback laTextFieldWidget_GetTextChangedEventCallback(laTextFieldWidget* txt);

// *****************************************************************************
/* Function:
    void laTextFieldWidget_SetTextChangedEventCallback(laTextFieldWidget* txt,
													          laTextFieldWidget_TextChangedCallback cb)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
	laTextFieldWidget_TextChangedCallback
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laTextFieldWidget_SetTextChangedEventCallback(laTextFieldWidget* txt,
													          laTextFieldWidget_TextChangedCallback cb);

			
void _laTextFieldWidget_TouchDownEvent(laTextFieldWidget* txt, laInput_TouchDownEvent* evt);
void _laTextFieldWidget_TouchUpEvent(laTextFieldWidget* txt, laInput_TouchUpEvent* evt);
void _laTextFieldWidget_TouchMovedEvent(laTextFieldWidget* txt, laInput_TouchMovedEvent* evt);
										       
void _laTextFieldWidget_FocusGained(laWidget* widget);
void _laTextFieldWidget_FocusLost(laWidget* widget);

// *****************************************************************************
/* Function:
    laResult laTextFieldWidget_StartEdit(laTextFieldWidget* txt)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
		
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laTextFieldWidget_StartEdit(laTextFieldWidget* txt);

// *****************************************************************************
/* Function:
    void laTextFieldWidget_EndEdit(laTextFieldWidget* txt)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
		
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laTextFieldWidget_EndEdit(laTextFieldWidget* txt);

// *****************************************************************************
/* Function:
    void laTextFieldWidget_Clear(laTextFieldWidget* txt)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
		
  Returns:
	void
	
  Remarks:
    
*/								      
LIB_EXPORT void laTextFieldWidget_Clear(laTextFieldWidget* txt);

// *****************************************************************************
/* Function:
    void laTextFieldWidget_Accept(laTextFieldWidget* txt)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
		
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laTextFieldWidget_Accept(laTextFieldWidget* txt);

// *****************************************************************************
/* Function:
    void laTextFieldWidget_Append(laTextFieldWidget* txt, laString* str)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
	laString*
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laTextFieldWidget_Append(laTextFieldWidget* txt, laString str);

// *****************************************************************************
/* Function:
    void laTextFieldWidget_Set(laTextFieldWidget* txt, laString* str)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
	laString*
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laTextFieldWidget_Set(laTextFieldWidget* txt, laString str);

// *****************************************************************************
/* Function:
    void laTextFieldWidget_Backspace(laTextFieldWidget* txt)

  Summary:
    

  Description:
    

  Parameters:
	laTextFieldWidget*
		
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laTextFieldWidget_Backspace(laTextFieldWidget* txt);

#endif // LA_TEXTFIELD_WIDGET_ENABLED
#endif /* LIBARIA_TEXTFIELD_H */