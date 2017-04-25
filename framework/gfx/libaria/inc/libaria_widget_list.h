/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_list.h

  Summary:
    

  Description:
    This module implements list box widget functions.
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

#ifndef LIBARIA_LISTWIDGET_H
#define LIBARIA_LISTWIDGET_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_LIST_WIDGET_ENABLED && LA_SCROLLBAR_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_list.h"
#include "gfx/libaria/inc/libaria_widget.h"
#include "gfx/libaria/inc/libaria_widget_scrollbar.h"
#include "gfx/libaria/inc/libaria_string.h"

typedef struct laListWidget_t laListWidget;

typedef void (*laListWidget_SelectedItemChangedEvent)(laListWidget*,
                                                      uint32_t idx,
                                                      laBool selected);

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Enumeration:
    laListWidget_SelectionMode_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef enum laListWidget_SelectionMode_t
{
    LA_LIST_WIDGET_SELECTION_MODE_SINGLE,
    LA_LIST_WIDGET_SELECTION_MODE_MULTIPLE,
    LA_LIST_WIDGET_SELECTION_MODE_CONTIGUOUS
} laListWidget_SelectionMode;

// *****************************************************************************
/* Structure:
    laListItem_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef struct laListItem_t
{
    laString string;
    GFXU_ImageAsset* icon;
    laBool selected;
} laListItem;

typedef void (*laListWidget_ItemSelectedChangedEvent)(laListWidget*,
                                                      uint32_t idx,
                                                      laBool selected);

// *****************************************************************************
/* Structure:
    laListWidget_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/													  
typedef struct laListWidget_t
{
	laWidget widget;

    laListWidget_SelectionMode mode;
    laBool allowEmpty;

	laList items;

	laHAlignment halign;
	laRelativePosition iconPos;
	uint32_t iconMargin;
	
	uint32_t itemDown;
	
	laScrollBarWidget scrollbar;
	
	struct
	{
	    laListItem* item;
	    GFX_Rect itemRect;
	    
	    int32_t y;
	    
	    uint32_t nextItem;
	} paintState;
	
	laListWidget_ItemSelectedChangedEvent cb;
	
	GFXU_ExternalAssetReader* reader;
} laListWidget;

void _laListWidget_Constructor(laListWidget* lst);
void _laListWidget_Destructor(laListWidget* lst);

void _laListWidget_Paint(laListWidget* lst);

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laListWidget* laListWidget_New()

  Summary:
    

  Description:
    

  Parameters:
	
  Returns:
	laListWidget*
	
  Remarks:
    
*/
LIB_EXPORT laListWidget* laListWidget_New();

// *****************************************************************************
/* Function:
    laListWidget_SelectionMode laListWidget_GetSelectionMode(laListWidget* lst)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
	
  Returns:
	laListWidget_SelectionMode
	
  Remarks:
    
*/
LIB_EXPORT laListWidget_SelectionMode laListWidget_GetSelectionMode(laListWidget* lst);

// *****************************************************************************
/* Function:
    laResult laListWidget_SetSelectionMode(laListWidget* lst,
                                                  laListWidget_SelectionMode mode)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
	laListWidget_SelectionMode
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laListWidget_SetSelectionMode(laListWidget* lst,
                                                  laListWidget_SelectionMode mode);

// *****************************************************************************
/* Function:
    laBool laListWidget_GetAllowEmptySelection(laListWidget* lst)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
		
  Returns:
	laBool
	
  Remarks:
    
*/
LIB_EXPORT laBool laListWidget_GetAllowEmptySelection(laListWidget* lst);

// *****************************************************************************
/* Function:
    laResult laListWidget_SetAllowEmptySelection(laListWidget* lst,
                                                        laBool allow)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
	laBool
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laListWidget_SetAllowEmptySelection(laListWidget* lst,
                                                        laBool allow);

// *****************************************************************************
/* Function:
    laHAlignment laListWidget_GetAlignment(laListWidget* lst)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
		
  Returns:
	laHAlignment
	
  Remarks:
    
*/
LIB_EXPORT laHAlignment laListWidget_GetAlignment(laListWidget* lst);

// *****************************************************************************
/* Function:
    laResult laListWidget_SetAlignment(laListWidget* lst,
										      laHAlignment align)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
	laHAlignment
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laListWidget_SetAlignment(laListWidget* lst,
										      laHAlignment align);
										  
// *****************************************************************************
/* Function:
    laRelativePosition laListWidget_GetIconPosition(laListWidget* lst)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
		
  Returns:
	laRelativePosition
	
  Remarks:
    
*/
LIB_EXPORT laRelativePosition laListWidget_GetIconPosition(laListWidget* lst);

// *****************************************************************************
/* Function:
    laResult laListWidget_SetIconPosition(laListWidget* lst, 
                                                 laRelativePosition pos)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
	laRelativePosition
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laListWidget_SetIconPosition(laListWidget* lst, 
                                                 laRelativePosition pos);
// *****************************************************************************
/* Function:
    uint32_t laListWidget_GetIconMargin(laListWidget* lst)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laListWidget_GetIconMargin(laListWidget* lst);

// *****************************************************************************
/* Function:
    laResult laListWidget_SetIconMargin(laListWidget* lst, uint32_t mg)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laListWidget_SetIconMargin(laListWidget* lst, uint32_t mg);

// *****************************************************************************
/* Function:
    uint32_t laListWidget_GetItemCount(laListWidget* lst)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laListWidget_GetItemCount(laListWidget* lst);

// *****************************************************************************
/* Function:
    uint32_t laListWidget_AppendItem(laListWidget* lst)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laListWidget_AppendItem(laListWidget* lst);

// *****************************************************************************
/* Function:
    uint32_t laListWidget_InsertItem(laListWidget* lst, uint32_t idx)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
	uint32_t
	
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laListWidget_InsertItem(laListWidget* lst, uint32_t idx);

// *****************************************************************************
/* Function:
    laResult laListWidget_RemoveItem(laListWidget* lst, uint32_t idx)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laListWidget_RemoveItem(laListWidget* lst, uint32_t idx);

// *****************************************************************************
/* Function:
    void laListWidget_RemoveAllItems(laListWidget* lst)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
		
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laListWidget_RemoveAllItems(laListWidget* lst);

// *****************************************************************************
/* Function:
    laBool laListWidget_GetItemSelected(laListWidget* lst,
                                               uint32_t idx)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
	uint32_t
	
  Returns:
	laBool
	
  Remarks:
    
*/
LIB_EXPORT laBool laListWidget_GetItemSelected(laListWidget* lst,
                                               uint32_t idx);

// *****************************************************************************
/* Function:
    laResult laListWidget_SetItemSelected(laListWidget* lst,
                                                 uint32_t idx,
                                                 laBool selected)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
	uint32_t
	laBool
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laListWidget_SetItemSelected(laListWidget* lst,
                                                 uint32_t idx,
                                                 laBool selected);

// *****************************************************************************
/* Function:
    laResult laListWidget_ToggleItemSelected(laListWidget* lst,
                                                    uint32_t idx)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/                                                 
LIB_EXPORT laResult laListWidget_ToggleItemSelected(laListWidget* lst,
                                                    uint32_t idx);

// *****************************************************************************
/* Function:
    void laListWidget_SelectAll(laListWidget* lst)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
		
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laListWidget_SelectAll(laListWidget* lst);                                                 

// *****************************************************************************
/* Function:
    void laListWidget_DeselectAll(laListWidget* lst)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
		
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laListWidget_DeselectAll(laListWidget* lst);                                                    


// *****************************************************************************
/* Function:
    uint32_t laListWidget_GetFirstSelectedItem(laListWidget* lst)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/                                                    
LIB_EXPORT uint32_t laListWidget_GetFirstSelectedItem(laListWidget* lst);

// *****************************************************************************
/* Function:
    uint32_t laListWidget_GetLastSelectedItem(laListWidget* lst)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laListWidget_GetLastSelectedItem(laListWidget* lst);

// *****************************************************************************
/* Function:
    uint32_t laListWidget_GetSelectionCount(laListWidget* lst)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laListWidget_GetSelectionCount(laListWidget* lst);


LIB_EXPORT void laListWidget_GetItemText(laListWidget* lst,
                                         uint32_t index,
                                         laString* str);

LIB_EXPORT void laListWidget_SetItemText(laListWidget* lst,
                                         uint32_t index,
                                         laString str);

// *****************************************************************************
/* Function:
    GFXU_ImageAsset* laListWidget_GetItemIcon(laListWidget* lst,
                                                     uint32_t index)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
	uint32_t
	
  Returns:
	GFXU_ImageAsset*
	
  Remarks:
    
*/
LIB_EXPORT GFXU_ImageAsset* laListWidget_GetItemIcon(laListWidget* lst,
                                                     uint32_t index);

// *****************************************************************************
/* Function:
    void laListWidget_SetItemIcon(laListWidget* lst,
                                         uint32_t index,
										 GFXU_ImageAsset* img)

  Summary:
    

  Description:
    

  Parameters:
	laListWidget*
	uint32_t
	GFXU_ImageAsset*
	
  Returns:
	void
	
  Remarks:
    
*/													 
LIB_EXPORT void laListWidget_SetItemIcon(laListWidget* lst,
                                         uint32_t idx,
										 GFXU_ImageAsset* img);

LIB_EXPORT void laListWidget_SetItemVisible(laListWidget* lst,
                                            uint32_t idx);
			 
void _laListWidget_GetRowRect(laListWidget* lst,
                              uint32_t idx,
                              GFX_Rect* rect);

int32_t _laListWidget_GetRowY(laListWidget* lst, uint32_t idx);
                            
void _laListWidget_GetLogicalRect(laListWidget* lst, GFX_Rect* rect);
                                  
LIB_EXPORT laListWidget_SelectedItemChangedEvent laListWidget_GetSelectedItemChangedEventCallback(laListWidget* lst);

LIB_EXPORT void laListWidget_SetSelectedItemChangedEventCallback(laListWidget* lst,
														         laListWidget_SelectedItemChangedEvent cb);                                  

#endif // LA_LIST_WIDGET_ENABLED && LA_SCROLLBAR_WIDGET_ENABLED
#endif /* LIBARIA_LISTWIDGET_H */