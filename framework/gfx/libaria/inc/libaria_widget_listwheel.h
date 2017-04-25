/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_listwheel.h

  Summary:
    

  Description:
    This module implements list wheel (drawing-style list box) widget functions.
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
#ifndef LIBARIA_LISTWHEELWIDGET_H
#define LIBARIA_LISTWHEELWIDGET_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_LISTWHEEL_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_list.h"
#include "gfx/libaria/inc/libaria_widget.h"
#include "gfx/libaria/inc/libaria_widget_scrollbar.h"
#include "gfx/libaria/inc/libaria_string.h"

typedef struct laListWheelWidget_t laListWheelWidget;

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Structure:
    laListWheelItem_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef struct laListWheelItem_t
{
    laString string;
    GFXU_ImageAsset* icon;
} laListWheelItem;

typedef void (*laListWheelWidget_SelectedItemChangedEvent)(laListWheelWidget*,
                                                           uint32_t idx);

// *****************************************************************************
/* Structure:
    laListWheelWidget_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/														   
typedef struct laListWheelWidget_t
{
	laWidget widget;

	laList items;
	int32_t selectedItem;

	laHAlignment halign;
	laRelativePosition iconPos;
	uint32_t iconMargin;
	
	uint32_t itemDown;
	
	int32_t touchY;
	
	struct
	{
	    laListWheelItem* item;
	    GFX_Rect itemRect;
	    
	    int32_t y;
	    
	    uint32_t nextItem;
	} paintState;
	
	laListWheelWidget_SelectedItemChangedEvent cb;
	
	GFXU_ExternalAssetReader* reader;
} laListWheelWidget;

void _laListWheelWidget_Constructor(laListWheelWidget* whl);
void _laListWheelWidget_Destructor(laListWheelWidget* whl);

void _laListWheelWidget_Paint(laListWheelWidget* whl);

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laListWheelWidget* laListWheelWidget_New()

  Summary:
    

  Description:
    

  Parameters:
	
  Returns:
	laListWheelWidget*
	
  Remarks:
    
*/
LIB_EXPORT laListWheelWidget* laListWheelWidget_New();

// *****************************************************************************
/* Function:
    laHAlignment laListWheelWidget_GetAlignment(laListWheelWidget* whl)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	
  Returns:
	laHAlignment
	
  Remarks:
    
*/
LIB_EXPORT laHAlignment laListWheelWidget_GetAlignment(laListWheelWidget* whl);

// *****************************************************************************
/* Function:
    laResult laListWheelWidget_SetAlignment(laListWheelWidget* whl,
										          laHAlignment align)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	laHAlignment
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laListWheelWidget_SetAlignment(laListWheelWidget* whl,
										          laHAlignment align);

// *****************************************************************************
/* Function:
    laRelativePosition laListWheelWidget_GetIconPosition(laListWheelWidget* whl)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	
  Returns:
	laRelativePosition
	
  Remarks:
    
*/												  
LIB_EXPORT laRelativePosition laListWheelWidget_GetIconPosition(laListWheelWidget* whl);

// *****************************************************************************
/* Function:
    laResult laListWheelWidget_SetIconPosition(laListWheelWidget* whl, 
                                                      laRelativePosition pos)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	laRelativePosition
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laListWheelWidget_SetIconPosition(laListWheelWidget* whl, 
                                                      laRelativePosition pos);

// *****************************************************************************
/* Function:
    uint32_t laListWheelWidget_GetIconMargin(laListWheelWidget* whl)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laListWheelWidget_GetIconMargin(laListWheelWidget* whl);

// *****************************************************************************
/* Function:
    laResult laListWheelWidget_SetIconMargin(laListWheelWidget* whl, uint32_t mg)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laListWheelWidget_SetIconMargin(laListWheelWidget* whl, uint32_t mg);

// *****************************************************************************
/* Function:
    uint32_t laListWheelWidget_GetItemCount(laListWheelWidget* whl)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laListWheelWidget_GetItemCount(laListWheelWidget* whl);

// *****************************************************************************
/* Function:
    uint32_t laListWheelWidget_AppendItem(laListWheelWidget* whl)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laListWheelWidget_AppendItem(laListWheelWidget* whl);

// *****************************************************************************
/* Function:
    uint32_t laListWheelWidget_InsertItem(laListWheelWidget* whl, uint32_t idx)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	uint32_t
	
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laListWheelWidget_InsertItem(laListWheelWidget* whl, uint32_t idx);

// *****************************************************************************
/* Function:
    laResult laListWheelWidget_RemoveItem(laListWheelWidget* whl, uint32_t idx)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laListWheelWidget_RemoveItem(laListWheelWidget* whl, uint32_t idx);

// *****************************************************************************
/* Function:
    void laListWheelWidget_RemoveAllItems(laListWheelWidget* whl)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laListWheelWidget_RemoveAllItems(laListWheelWidget* whl);

// *****************************************************************************
/* Function:
    int32_t laListWheelWidget_GetSelectedItem(laListWheelWidget* whl)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	
  Returns:
	int32_t
	
  Remarks:
    
*/
LIB_EXPORT int32_t laListWheelWidget_GetSelectedItem(laListWheelWidget* whl);

// *****************************************************************************
/* Function:
    laResult laListWheelWidget_SetSelectedItem(laListWheelWidget* whl, 
                                                      uint32_t idx)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laListWheelWidget_SetSelectedItem(laListWheelWidget* whl, 
                                                      uint32_t idx);

// *****************************************************************************
/* Function:
    laResult laListWheelWidget_SelectPreviousItem(laListWheelWidget* whl)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	
  Returns:
	laResult
	
  Remarks:
    
*/													  
LIB_EXPORT laResult laListWheelWidget_SelectPreviousItem(laListWheelWidget* whl);                                                      

// *****************************************************************************
/* Function:
    laResult laListWheelWidget_SelectNextItem(laListWheelWidget* whl)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laListWheelWidget_SelectNextItem(laListWheelWidget* whl);                                                 

// *****************************************************************************
/* Function:
    laString* laListWheelWidget_GetItemText(laListWheelWidget* whl,
                                                   uint32_t index)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	uint32_t
	
  Returns:
	laString*
	
  Remarks:
    
*/
LIB_EXPORT void laListWheelWidget_GetItemText(laListWheelWidget* whl,
                                              uint32_t index,
                                              laString* str);

LIB_EXPORT void laListWheelWidget_SetItemText(laListWheelWidget* whl,
                                              uint32_t index,
                                              laString str);
                                              

// *****************************************************************************
/* Function:
    GFXU_ImageAsset* laListWheelWidget_GetItemIcon(laListWheelWidget* whl,
                                                          uint32_t index)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	uint32_t
	
  Returns:
	GFXU_ImageAsset*
	
  Remarks:
    
*/
LIB_EXPORT GFXU_ImageAsset* laListWheelWidget_GetItemIcon(laListWheelWidget* whl,
                                                          uint32_t index);

// *****************************************************************************
/* Function:
    void laListWheelWidget_SetItemIcon(laListWheelWidget* whl,
                                              uint32_t index,
										      GFXU_ImageAsset* img)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	uint32_t
	GFXU_ImageAsset*
	
  Returns:
	void
	
  Remarks:
    
*/														  
LIB_EXPORT void laListWheelWidget_SetItemIcon(laListWheelWidget* whl,
                                              uint32_t index,
										      GFXU_ImageAsset* img);
									  
void _laListWheelWidget_GetRowRect(laListWheelWidget* whl,
                              uint32_t idx,
                              GFX_Rect* rect);
                              
void _laListWheelWidget_GetLogicalRect(laListWheelWidget* whl,
                                       GFX_Rect* rect);

// *****************************************************************************
/* Function:
    laListWheelWidget_SelectedItemChangedEvent laListWheelWidget_GetSelectedItemChangedEventCallback(laListWheelWidget* whl)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	
  Returns:
	laListWheelWidget_SelectedItemChangedEvent
	
  Remarks:
    
*/
LIB_EXPORT laListWheelWidget_SelectedItemChangedEvent laListWheelWidget_GetSelectedItemChangedEventCallback(laListWheelWidget* whl);

// *****************************************************************************
/* Function:
    void laListWheelWidget_SetSelectedItemChangedEventCallback(laListWheelWidget* whl,
														              laListWheelWidget_SelectedItemChangedEvent cb)

  Summary:
    

  Description:
    

  Parameters:
	laListWheelWidget*
	laListWheelWidget_SelectedItemChangedEvent
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laListWheelWidget_SetSelectedItemChangedEventCallback(laListWheelWidget* whl,
														              laListWheelWidget_SelectedItemChangedEvent cb);
														
#endif // LA_LISTWHEEL_WIDGET_ENABLED
#endif /* LIBARIA_LISTWHEELWIDGET_H */