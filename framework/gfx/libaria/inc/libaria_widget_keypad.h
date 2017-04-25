/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_keypad.h

  Summary:
    

  Description:
    This module implements keypad widget functions.
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
#ifndef LIBARIA_KEYPAD_H
#define LIBARIA_KEYPAD_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_KEYPAD_WIDGET_ENABLED && LA_BUTTON_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_widget.h"
#include "gfx/libaria/inc/libaria_string.h"

typedef struct laKeyPadWidget_t laKeyPadWidget;
typedef struct laButtonWidget_t laButtonWidget;

typedef void (*laKeyPadWidget_KeyClickEvent)(laKeyPadWidget*,
                                             laButtonWidget*,
                                             uint32_t,
                                             uint32_t);

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Structure:
    laKeyPadCellAction_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef enum laKeyPadCellAction_t
{
    LA_KEYPAD_CELL_ACTION_NONE,
    LA_KEYPAD_CELL_ACTION_APPEND,
    LA_KEYPAD_CELL_ACTION_SET,
    LA_KEYPAD_CELL_ACTION_BACKSPACE,
    LA_KEYPAD_CELL_ACTION_CLEAR,
    LA_KEYPAD_CELL_ACTION_ACCEPT
} laKeyPadCellAction;

// *****************************************************************************
/* Structure:
    laKeyPadCell_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef struct laKeyPadCell_t
{
    laBool enabled;
    laButtonWidget* button;
    laKeyPadCellAction action;
    laString value;
} laKeyPadCell;

// *****************************************************************************
/* Structure:
    laKeyPadCell_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef struct laKeyPadWidget_t
{
	laWidget widget;

    uint32_t rows;
    uint32_t cols;
    
    laKeyPadCell* cells;
    
    laKeyPadWidget_KeyClickEvent clickEvt;

	GFXU_ExternalAssetReader* reader;
} laKeyPadWidget;

void _laKeyPadWidget_Constructor(laKeyPadWidget* pad, uint32_t rows, uint32_t cols);
void _laKeyPadWidget_Destructor(laKeyPadWidget* pad);

void _laKeyPadWidget_Paint(laKeyPadWidget* pad);


// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laKeyPadWidget* laKeyPadWidget_New(uint32_t rows, uint32_t cols)

  Summary:
    

  Description:
    

  Parameters:
	uint32_t
	uint32_t
	
  Returns:
	laKeyPadWidget*
	
  Remarks:
    
*/
LIB_EXPORT laKeyPadWidget* laKeyPadWidget_New(uint32_t rows, uint32_t cols);

// *****************************************************************************
/* Function:
    laKeyPadWidget_KeyClickEvent laKeyPadWidget_GetKeyClickEventCallback(laKeyPadWidget* pad)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	
  Returns:
	laKeyPadWidget_KeyClickEvent
	
  Remarks:
    
*/
LIB_EXPORT laKeyPadWidget_KeyClickEvent laKeyPadWidget_GetKeyClickEventCallback(laKeyPadWidget* pad);

// *****************************************************************************
/* Function:
    void laKeyPadWidget_SetKeyClickEventCallback(laKeyPadWidget* pad,
													    laKeyPadWidget_KeyClickEvent cb)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	laKeyPadWidget_KeyClickEvent
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laKeyPadWidget_SetKeyClickEventCallback(laKeyPadWidget* pad,
													    laKeyPadWidget_KeyClickEvent cb);

// *****************************************************************************
/* Function:
    laBool laKeyPadWidget_GetKeyEnabled(laKeyPadWidget* pad,
                                               uint32_t row,
                                               uint32_t col)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	uint32_t
	uint32_t
	
  Returns:
	laBool
	
  Remarks:
    
*/
LIB_EXPORT laBool laKeyPadWidget_GetKeyEnabled(laKeyPadWidget* pad,
                                               uint32_t row,
                                               uint32_t col);

// *****************************************************************************
/* Function:
    void laKeyPadWidget_SetKeyEnabled(laKeyPadWidget* pad,
                                             uint32_t row,
                                             uint32_t col,
                                             laBool enabled)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	uint32_t
	uint32_t
	laBool
	
  Returns:
	void
	
  Remarks:
    
*/											   
LIB_EXPORT void laKeyPadWidget_SetKeyEnabled(laKeyPadWidget* pad,
                                             uint32_t row,
                                             uint32_t col,
                                             laBool enabled);

LIB_EXPORT void laKeyPadWidget_GetKeyText(laKeyPadWidget* pad,
                                          uint32_t row,
                                          uint32_t col,
                                          laString* str);
                                          
LIB_EXPORT void laKeyPadWidget_SetKeyText(laKeyPadWidget* pad,
                                          uint32_t row,
                                          uint32_t col,
                                          laString str);                                          

// *****************************************************************************
/* Function:
    GFXU_ImageAsset* laKeyPadWidget_GetKeyPressedImage(laKeyPadWidget* pad,
                                                              uint32_t row,
                                                              uint32_t col)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	uint32_t
	uint32_t
	
  Returns:
	GFXU_ImageAsset*
	
  Remarks:
    
*/										  
LIB_EXPORT GFXU_ImageAsset* laKeyPadWidget_GetKeyPressedImage(laKeyPadWidget* pad,
                                                              uint32_t row,
                                                              uint32_t col);

// *****************************************************************************
/* Function:
    void laKeyPadWidget_SetKeyPressedImage(laKeyPadWidget* pad,
                                                  uint32_t row,
                                                  uint32_t col,
											      GFXU_ImageAsset* img)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	uint32_t
	uint32_t
	GFXU_ImageAsset*
	
  Returns:
	void
	
  Remarks:
    
*/															  
LIB_EXPORT void laKeyPadWidget_SetKeyPressedImage(laKeyPadWidget* pad,
                                                  uint32_t row,
                                                  uint32_t col,
											      GFXU_ImageAsset* img);

// *****************************************************************************
/* Function:
    GFXU_ImageAsset* laKeyPadWidget_GetKeyReleasedImage(laKeyPadWidget* pad,
                                                               uint32_t row,
                                                               uint32_t col)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	uint32_t
	uint32_t
	
  Returns:
	GFXU_ImageAsset*
	
  Remarks:
    
*/												  
LIB_EXPORT GFXU_ImageAsset* laKeyPadWidget_GetKeyReleasedImage(laKeyPadWidget* pad,
                                                               uint32_t row,
                                                               uint32_t col);

// *****************************************************************************
/* Function:
    void laKeyPadWidget_SetKeyReleasedImage(laKeyPadWidget* pad,
                                                   uint32_t row,
                                                   uint32_t col,
												   GFXU_ImageAsset* img)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	uint32_t
	uint32_t
	GFXU_ImageAsset*
	
  Returns:
	void
	
  Remarks:
    
*/                                                               
LIB_EXPORT void laKeyPadWidget_SetKeyReleasedImage(laKeyPadWidget* pad,
                                                   uint32_t row,
                                                   uint32_t col,
												   GFXU_ImageAsset* img);

// *****************************************************************************
/* Function:
    laRelativePosition laKeyPadWidget_GetKeyImagePosition(laKeyPadWidget* pad,
                                                                 uint32_t row,
                                                                 uint32_t col)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	uint32_t
	uint32_t
	
  Returns:
	laRelativePosition
	
  Remarks:
    
*/												   
LIB_EXPORT laRelativePosition laKeyPadWidget_GetKeyImagePosition(laKeyPadWidget* pad,
                                                                 uint32_t row,
                                                                 uint32_t col);

// *****************************************************************************
/* Function:
    void laKeyPadWidget_SetKeyImagePosition(laKeyPadWidget* pad,
                                                   uint32_t row,
                                                   uint32_t col,
                                                   laRelativePosition pos)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	uint32_t
	uint32_t
	laRelativePosition
	
  Returns:
	void
	
  Remarks:
    
*/                                                                 
LIB_EXPORT void laKeyPadWidget_SetKeyImagePosition(laKeyPadWidget* pad,
                                                   uint32_t row,
                                                   uint32_t col,
                                                   laRelativePosition pos);

// *****************************************************************************
/* Function:
    uint32_t laKeyPadWidget_GetKeyImageMargin(laKeyPadWidget* pad,
                                                     uint32_t row,
                                                     uint32_t col)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	uint32_t
	uint32_t
	
  Returns:
	uint32_t
	
  Remarks:
    
*/												   
LIB_EXPORT uint32_t laKeyPadWidget_GetKeyImageMargin(laKeyPadWidget* pad,
                                                     uint32_t row,
                                                     uint32_t col);

// *****************************************************************************
/* Function:
    void laKeyPadWidget_SetKeyImageMargin(laKeyPadWidget* pad,
                                                 uint32_t row,
                                                 uint32_t col,
                                                 uint32_t mg)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	uint32_t
	uint32_t
	uint32_t
	
  Returns:
	void
	
  Remarks:
    
*/                                                     
LIB_EXPORT void laKeyPadWidget_SetKeyImageMargin(laKeyPadWidget* pad,
                                                 uint32_t row,
                                                 uint32_t col,
                                                 uint32_t mg);

// *****************************************************************************
/* Function:
    laBool laKeyPadWidget_GetKeyDrawBackground(laKeyPadWidget* pad,
                                                      uint32_t row,
                                                      uint32_t col)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	uint32_t
	uint32_t
	
  Returns:
	laBool
	
  Remarks:
    
*/                                                 
LIB_EXPORT laBool laKeyPadWidget_GetKeyDrawBackground(laKeyPadWidget* pad,
                                                      uint32_t row,
                                                      uint32_t col);

// *****************************************************************************
/* Function:
    void laKeyPadWidget_SetKeyDrawBackground(laKeyPadWidget* pad,
                                                    uint32_t row,
                                                    uint32_t col,
                                                    laBool draw)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	uint32_t
	uint32_t
	laBool
	
  Returns:
	void
	
  Remarks:
    
*/													  
LIB_EXPORT void laKeyPadWidget_SetKeyDrawBackground(laKeyPadWidget* pad,
                                                    uint32_t row,
                                                    uint32_t col,
                                                    laBool draw);

// *****************************************************************************
/* Function:
    laKeyPadCellAction laKeyPadWidget_GetKeyAction(laKeyPadWidget* pad,
                                                          uint32_t row,
                                                          uint32_t col)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	uint32_t
	uint32_t
	
  Returns:
	laKeyPadCellAction
	
  Remarks:
    
*/
LIB_EXPORT laKeyPadCellAction laKeyPadWidget_GetKeyAction(laKeyPadWidget* pad,
                                                          uint32_t row,
                                                          uint32_t col);

// *****************************************************************************
/* Function:
    laResult laKeyPadWidget_SetKeyAction(laKeyPadWidget* pad,
                                                uint32_t row,
                                                uint32_t col,
                                                laKeyPadCellAction action)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	uint32_t
	uint32_t
	laKeyPadCellAction
	
  Returns:
	laResult
	
  Remarks:
    
*/														  
LIB_EXPORT laResult laKeyPadWidget_SetKeyAction(laKeyPadWidget* pad,
                                                uint32_t row,
                                                uint32_t col,
                                                laKeyPadCellAction action);

// *****************************************************************************
/* Function:
    laString* laKeyPadWidget_GetKeyValue(laKeyPadWidget* pad,
                                                uint32_t row,
                                                uint32_t col)

  Summary:
    

  Description:
    

  Parameters:
	laKeyPadWidget*
	uint32_t
	uint32_t
	
  Returns:
	laString*
	
  Remarks:
    
*/												
LIB_EXPORT laString* laKeyPadWidget_GetKeyValue(laKeyPadWidget* pad,
                                                uint32_t row,
                                                uint32_t col);

LIB_EXPORT void laKeyPadWidget_SetKeyValue(laKeyPadWidget* pad,
                                           uint32_t row,
                                           uint32_t col,
                                           laString str);

#endif // LA_WIDGET_KEYPAD_ENABLED && LA_WIDGET_BUTTON_ENABLED
#endif /* LIBARIA_KEYPAD_H */