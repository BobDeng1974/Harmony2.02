/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget.h

  Summary:
    

  Description:
    This module implements top level widget control functions.
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

#ifndef LIBARIA_WIDGET_H
#define LIBARIA_WIDGET_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"
#include "gfx/libaria/inc/libaria_input.h"
#include "gfx/libaria/inc/libaria_list.h"
#include "gfx/libaria/inc/libaria_scheme.h"

#include "gfx/hal/inc/gfx_rect.h"
#include "gfx/utils/gfx_utils.h"

#define DEFAULT_BORDER_MARGIN   4

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

/*
Enumeration:
        laWidgetType_t

    Summary:
        Specifies the different widget types used in the library

    Description:
        This enumeration specifies the different widget types
        used in the library.

    Remarks:
        None.
 */
typedef enum laWidgetType_t
{
	LA_WIDGET_WIDGET,
	LA_WIDGET_LAYER,
#if LA_BUTTON_WIDGET_ENABLED
	LA_WIDGET_BUTTON,
#endif
#if LA_BUTTON_WIDGET_ENABLED
	LA_WIDGET_CHECKBOX,
#endif
#if LA_CIRCLE_WIDGET_ENABLED
	LA_WIDGET_CIRCLE,
#endif
#if LA_DRAWSURFACE_WIDGET_ENABLED
	LA_WIDGET_DRAWSURFACE,
#endif
#if LA_IMAGE_WIDGET_ENABLED
	LA_WIDGET_IMAGE,
#endif
#if LA_IMAGESEQUENCE_WIDGET_ENABLED
	LA_WIDGET_IMAGESEQUENCE,
#endif
#if LA_GRADIENT_WIDGET_ENABLED
	LA_WIDGET_GRADIENT,
#endif
#if LA_GROUPBOX_WIDGET_ENABLED
	LA_WIDGET_GROUPBOX,
#endif
#if LA_KEYPAD_WIDGET_ENABLED && LA_BUTTON_WIDGET_ENABLED
	LA_WIDGET_KEYPAD,
#endif
#if LA_LABEL_WIDGET_ENABLED
	LA_WIDGET_LABEL,
#endif
#if LA_LINE_WIDGET_ENABLED
	LA_WIDGET_LINE,
#endif
#if LA_LIST_WIDGET_ENABLED && LA_SCROLLBAR_WIDGET_ENABLED
	LA_WIDGET_LIST,
#endif
#if LA_LISTWHEEL_WIDGET_ENABLED
	LA_WIDGET_LISTWHEEL,
#endif
#if LA_PROGRESSBAR_WIDGET_ENABLED
	LA_WIDGET_PROGRESSBAR,
#endif
#if LA_RADIOBUTTON_WIDGET_ENABLED
	LA_WIDGET_RADIOBUTTON,
#endif
#if LA_RECTANGLE_WIDGET_ENABLED
	LA_WIDGET_RECTANGLE,
#endif
#if LA_SCROLLBAR_WIDGET_ENABLED
	LA_WIDGET_SCROLLBAR,
#endif
#if LA_SLIDER_WIDGET_ENABLED
	LA_WIDGET_SLIDER,
#endif
#if LA_TEXTFIELD_WIDGET_ENABLED
	LA_WIDGET_TEXTFIELD,
#endif
#if LA_TOUCHTEST_WIDGET_ENABLED
	LA_WIDGET_TOUCHTEST,
#endif
#if LA_WINDOW_WIDGET_ENABLED
	LA_WIDGET_WINDOW,
#endif
	// begin custom types, not essential but good for identifying base pointers

    // end custom types
    //LA_WIDGET_LAST = LA_WIDGET_WINDOW, // change this if adding custom
	//LA_WIDGET_TYPE_COUNT = LA_WIDGET_LAST + 1
} laWidgetType;

/*
Enumeration:
        laBorderType_t

    Summary:
        Specifies the different border types used for the widgets in the library

    Description:
        Specifies the different border types used for the widgets in the library

    Remarks:
        None.
 */
typedef enum laBorderType_t
{
	LA_WIDGET_BORDER_NONE,
	LA_WIDGET_BORDER_LINE,
	LA_WIDGET_BORDER_BEVEL,
	LA_WIDGET_BORDER_LAST = LA_WIDGET_BORDER_BEVEL
} laBorderType;

/*
Enumeration:
        laWidgetDirtyState_t

    Summary:
        Specifies the different dirty states the widget can be assigned

    Description:
        Specifies the different dirty states the widget can be assigned
		This decides whether the particular widget would be re-drawn or not. Dirty widget are re-drawn and Clean are not painted over.

    Remarks:
        None.
 */
typedef enum laWidgetDirtyState_t
{
	LA_WIDGET_DIRTY_STATE_CLEAN,
	LA_WIDGET_DIRTY_STATE_DIRTY,
	LA_WIDGET_DIRTY_STATE_CHILD
} laWidgetDirtyState;

/*
Enumeration:
        laWidgetDrawState_t

    Summary:
        Specifies the different draw states the widget can be assigned

    Description:
        Specifies the different draw states the widget can be assigned
		
    Remarks:
        None.
 */
typedef enum laWidgetDrawState_t
{
	LA_WIDGET_DRAW_STATE_READY,
	LA_WIDGET_DRAW_STATE_DONE,
	
	// widget-specific draw states start here
} laWidgetDrawState;


typedef struct laWidget_t laWidget;

typedef void (*laWidget_Constructor_FnPtr)(laWidget*);
typedef void (*laWidget_Destructor_FnPtr)(laWidget*);
typedef void (*laWidget_Update_FnPtr)(laWidget*, uint32_t);
typedef void (*laWidget_Paint_FnPtr)(laWidget*);
typedef void (*laWidget_DrawFunction_FnPtr)(void*);

typedef void (*laWidget_Moved_FnPtr)(laWidget*);
typedef void (*laWidget_Resized_FnPtr)(laWidget*);

typedef void (*laWidget_Focus_FnPtr)(laWidget*);

typedef void (*laWidget_TouchDownEvent_FnPtr)(laWidget*, laInput_TouchDownEvent*);
typedef void (*laWidget_TouchUpEvent_FnPtr)(laWidget*, laInput_TouchUpEvent*);
typedef void (*laWidget_TouchMovedEvent_FnPtr)(laWidget*, laInput_TouchMovedEvent*);

/* Structure:
        laWidget_t

    Summary:
        Specifies Graphics widget structure to manage all properties and events associated with the widget

    Description:
        Specifies Graphics widget structure to manage all properties and events associated with the widget.
		It also contains information about the parent and children for the widget to manage the tree structure that the library supports.


    Remarks:
        None.
        
*/
typedef struct laWidget_t
{
	uint32_t id;
	laWidgetType type;
	
	laBool editable;

	laBool visible;
	laBool enabled;

	GFX_Rect rect;
	
	laMargin margin;

	laBorderType borderType;
	laBool drawBackground;
	laBool localRedraw;
	
	laBool alphaEnabled;
	uint32_t alphaAmount;

	uint32_t dirtyState;
	uint32_t drawState;
	laWidget_DrawFunction_FnPtr drawFunc;

	laScheme* scheme;

	laBool root;
	laWidget* parent;
	laList children;

	GFXU_ExternalAssetReader* reader;
 
	laWidget_Constructor_FnPtr constructor;
	laWidget_Destructor_FnPtr destructor;

	laWidget_Moved_FnPtr moved;
	laWidget_Resized_FnPtr resized;
	
	laWidget_Focus_FnPtr focusGained;
	laWidget_Focus_FnPtr focusLost;

	laWidget_Update_FnPtr update;
	laWidget_Paint_FnPtr paint;

	laWidget_TouchDownEvent_FnPtr touchDown;
	laWidget_TouchUpEvent_FnPtr touchUp;
	laWidget_TouchMovedEvent_FnPtr touchMoved;
} laWidget;

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

/*    Function:
        laWidget* laWidget_New()
 
    Summary:
        Create a new widget.
		

    Description:
        Create a new widget, alocate memory for the widget through the current active context. 
		Returns a widget object pointer

    Parameters:

		
	Returns:
		lawidget*

*/
LIB_EXPORT laWidget* laWidget_New();

/*    Function:
        void laWidget_Delete(laWidget* widget)
 
    Summary:
        Delete the widget object specified		

    Description:
        Delete a widget object specified, de-allocate memory for the widget through the current active context. 
		
    Parameters:
		lawidget*
		
	Returns:
		void

*/
LIB_EXPORT void laWidget_Delete(laWidget* widget);

// internal constructor and destructor
void _laWidget_Constructor(laWidget* widget);
void _laWidget_Destructor(laWidget* widget);

void _laWidget_Paint(laWidget* widget);

/*    Function:
        int32_t laWidget_GetX(laWidget* widget)
 
    Summary:
        Returns the widget rectangles upper left corner x-coordinate		

    Description:
        Returns the widget rectangles upper left corner x-coordinate
		
    Parameters:
		lawidget*
		
	Returns:
		uint32_t

*/
LIB_EXPORT int32_t laWidget_GetX(laWidget* widget);

/*    Function:
        laResult laWidget_SetX(laWidget* widget, int32_t x)
 
    Summary:
        Sets the widget's x coordinate position		

    Description:
        Sets the widget's x coordinate position		
		
    Parameters:
		lawidget* widget - the widget to modify
		int32_t x - the desired x value
		
	Returns:
		laResult - result of the operation

*/
LIB_EXPORT laResult laWidget_SetX(laWidget* widget, int32_t x);

/*    Function:
        int32_t laWidget_GetY(laWidget* widget)
 
    Summary:
        Returns the widget rectangles upper left corner y-coordinate		

    Description:
        Returns the widget rectangles upper left corner y-coordinate
		
    Parameters:
		lawidget*
		
	Returns:
		uint32_t

*/
LIB_EXPORT int32_t laWidget_GetY(laWidget* widget);

/*    Function:
        laResult laWidget_SetY(laWidget* widget, int32_t y)
 
    Summary:
        Sets the widget's y coordinate position		

    Description:
        Sets the widget's y coordinate position		
		
    Parameters:
		lawidget* widget - the widget to modify
		int32_t y - the desired y value
		
	Returns:
		laResult - result of the operation

*/
LIB_EXPORT laResult laWidget_SetY(laWidget* widget, int32_t y);

/*    Function:
        int32_t laWidget_GetWidth(laWidget* widget)
 
    Summary:
        Returns the widget rectangles width		

    Description:
        Returns the widget rectangles width
		
    Parameters:
		lawidget* widget - the widget to reference
		
	Returns:
		uint32_t - the widget's y coordinate value

*/
LIB_EXPORT int32_t laWidget_GetWidth(laWidget* widget);

/*    Function:
        laResult laWidget_SetWidth(laWidget* widget, int32_t width)
 
    Summary:
        Sets the widget's width value		

    Description:
        Sets the widget's width value	
		
    Parameters:
		lawidget* widget - the widget to modify
		int32_t width - the desired width value, must be > 0
		
	Returns:
		laResult - result of the operation

*/
LIB_EXPORT laResult laWidget_SetWidth(laWidget* widget, int32_t width);

/*    Function:
        int32_t laWidget_GetHeight(laWidget* widget)
 
    Summary:
        Returns the widget rectangles height		

    Description:
        Returns the widget rectangles height
		
    Parameters:
		lawidget* width - the widget to reference
		
	Returns:
		uint32_t - the widget's width value

*/
LIB_EXPORT int32_t laWidget_GetHeight(laWidget* widget);

/*    Function:
        laResult laWidget_SetHeight(laWidget* widget, int32_t height)
 
    Summary:
        Sets the widget's height value		

    Description:
        Sets the widget's height value	
		
    Parameters:
		lawidget* widget - the widget to modify
		int32_t height - the desired height value, must be > 0
		
	Returns:
		laResult - result of the operation

*/
LIB_EXPORT laResult laWidget_SetHeight(laWidget* widget, int32_t height);

// *****************************************************************************
/* Function:
    laBool   laWidget_GetAlphaEnable(laWidget* widget)

  Summary:
    Return the alpha enable property of the widget
	
  Description:
    Return the alpha enable property of the widget

  Parameters:
	laWidget*
	
  Returns:
	laBool
	
  Remarks:
    
*/
LIB_EXPORT laBool   laWidget_GetAlphaEnable(laWidget* widget);

// *****************************************************************************
/* Function:
    laBool   laWidget_GetCumulativeAlphaEnable(laWidget* widget)

  Summary:
    Return the alpha enable property of the the first parent widget that has an alpha enabled is TRUE.
	Return false if none of the parent along the widget tree has an alpha enabled value of TRUE
	
  Description:
    Return the alpha enable property of the the first parent widget that has an alpha enabled is TRUE.
	Return false if none of the parent along the widget tree has an alpha enabled value of TRUE

  Parameters:
	laWidget*
	
  Returns:
	laBool
	
  Remarks:
    
*/
LIB_EXPORT laBool   laWidget_GetCumulativeAlphaEnable(laWidget* widget);

// *****************************************************************************
/* Function:
    laResult laWidget_SetAlphaEnable(laWidget* widget, laBool enable)

  Summary:
    Set the alpha enable property of the widget with the boolean value specified
	
  Description:
    Set the alpha enable property of the widget with the boolean value specified

  Parameters:
	laWidget*
	laBool
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laWidget_SetAlphaEnable(laWidget* widget, laBool enable);

// *****************************************************************************
/* Function:
    uint32_t laWidget_GetAlphaAmount(laWidget* widget)

  Summary:
    Return the widget alpha amount 

  Description:
    Return the widget alpha amount 

  Parameters:
	laLayer*
	
	
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laWidget_GetAlphaAmount(laWidget* widget);


// *****************************************************************************
/* Function:
    uint32_t laWidget_GetCumulativeAlphaAmount(laWidget* widget)

  Summary:
    RYAN_TO_ADD

  Description:
    RYAN_TO_ADD 

  Parameters:
	laWidget*	
	
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laWidget_GetCumulativeAlphaAmount(laWidget* widget);

// *****************************************************************************
/* Function:
    laResult laWidget_SetAlphaAmount(laWidget* widget, uint32_t alpha)
	
  Summary:
    Set the widget alpha amount to the specified alpha amount

  Description:
    Set the widget alpha amount to the specified alpha amount

  Parameters:
	laLayer*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laWidget_SetAlphaAmount(laWidget* widget, uint32_t alpha);

// *****************************************************************************
/* Function:
    laBool laWidget_isOpaque(laWidget* widget)
	
  Summary:
    Check the alpha enabled and alpha amount of the widget or any of its parent to decide opaqueness

  Description:
    Check the alpha enabled and alpha amount of the widget or any of its parent to decide opaqueness
	If the cumulative alpha amount for the widget is less than 255, it is not opaque

  Parameters:
	laWidget*
	
  Returns:
	laBool
	
  Remarks:
    
*/
LIB_EXPORT laBool laWidget_isOpaque(laWidget* widget);

// *****************************************************************************
/* Function:
    GFX_Rect laWidget_RectToParentSpace(laWidget* widget)
	
  Summary:
    Returns the rectangle containing the parent of the widget specified

  Description:
    Returns the rectangle containing the parent of the widget specified
	If the widget and the parent are not null, the rectangle defining 
	the parent widget with its upper left corner x and y coordinates is returned

  Parameters:
	laWidget*
	
  Returns:
	GFX_Rect
	
  Remarks:
    
*/
LIB_EXPORT GFX_Rect laWidget_RectToParentSpace(laWidget* widget);

// *****************************************************************************
/* Function:
    GFX_Rect laWidget_RectToLayerSpace(laWidget* widget)
	
  Summary:
    Returns the rectangle of the layer containing the widget tree 

  Description:
    The function evaluate the outermost parent containing the widget and returns the associated rectangle.

  Parameters:
	laWidget*
	
  Returns:
	GFX_Rect
	
  Remarks:
    
*/
LIB_EXPORT GFX_Rect laWidget_RectToLayerSpace(laWidget* widget);

// *****************************************************************************
/* Function:
    GFX_Rect laWidget_RectToScreenSpace(laWidget* widget)
	
  Summary:
    Returns the rectangle of the screen containing the widget tree 

  Description:
    The function evaluate the outermost parent containing the widget and returns the associated screen rectangle.
	RYAN_TO_ADD - the current fnc implementation is only returning the outermost parent rectangle, not calculating the screen rectangle - please check

  Parameters:
	laWidget*
	
  Returns:
	GFX_Rect
	
  Remarks:
    
*/
LIB_EXPORT GFX_Rect laWidget_RectToScreenSpace(laWidget* widget);

// *****************************************************************************
/* Function:
    laResult laWidget_AddChild(laWidget* parent, laWidget* child)
	
  Summary:
    Adds the child to the parent widget specified in the argument

  Description:
    The function checks to see if the child and parent are valid, removes the child from its current parents children list, and assigns the child to the parent widget specified.
	The child is attached at the end of the list of the parent widgets children list.

  Parameters:
	laWidget*
	laWidget*
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laWidget_AddChild(laWidget* parent, laWidget* child);

// *****************************************************************************
/* Function:
    laResult laWidget_RemoveChild(laWidget* parent, laWidget* child)
	
  Summary:
    Removes the child from the parent widget specified in the argument

  Description:
    The function checks to see if the child and parent are valid, removes the child from its current parents children list

  Parameters:
	laWidget*
	laWidget*
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laWidget_RemoveChild(laWidget* parent, laWidget* child);

// *****************************************************************************
/* Function:
    laResult laWidget_SetParent(laWidget* wgt, laWidget* parent)
	
  Summary:
    Sets the parent of the child widget to that specified in the argument list

  Description:
    The function checks to see if the child and parent are valid, removes the child from its current parents children list, and assigns the child to the parent widget specified.
	The child is attached at the end of the list of the parent widgets children list.

  Parameters:
	laWidget*
	laWidget*
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laWidget_SetParent(laWidget* wgt, laWidget* parent);

// *****************************************************************************
/* Function:
    uint32_t laWidget_GetChildCount(laWidget* parent)
	
  Summary:
    Returns the size of the children list of the specified parent widget

  Description:
    Returns the size of the children list of the specified parent widget

  Parameters:
	laWidget*
		
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laWidget_GetChildCount(laWidget* parent);

// *****************************************************************************
/* Function:
    laWidget* laWidget_GetChildAtIndex(laWidget* parent, uint32_t idx)
	
  Summary:
    Fetches the child at the specified index from the children list of the specified parent widget

  Description:
    Fetches the child at the specified index from the children list of the specified parent widget

  Parameters:
	laWidget*
	uint32_t
	
  Returns:
	laWidget*
	
  Remarks:
    
*/
LIB_EXPORT laWidget* laWidget_GetChildAtIndex(laWidget* parent, uint32_t idx);

// *****************************************************************************
/* Function:
    int32_t laWidget_GetIndexOfChild(laWidget* parent, laWidget* child)
	
  Summary:
    Fetches the index of the child from the children list of the specified parent widget

  Description:
    Traverses the children list of the specified parent widget and finds the index of the child widget specified. 

  Parameters:
	laWidget*
	laWidget
	
  Returns:
	int32_t
	
  Remarks:
    
*/
LIB_EXPORT int32_t laWidget_GetIndexOfChild(laWidget* parent, laWidget* child);

// *****************************************************************************
/* Function:
    laBool laWidget_GetEnabled(laWidget* widget)
	
  Summary:
    Returns the boolean value of the widget enabled property

  Description:
    Returns the boolean value of the widget enabled property

  Parameters:
	laWidget*
	
	
  Returns:
	laBool
	
  Remarks:
    
*/
LIB_EXPORT laBool laWidget_GetEnabled(laWidget* widget);

// *****************************************************************************
/* Function:
    void laWidget_SetEnabled(laWidget* widget, laBool enable)
	
  Summary:
    Sets the boolean value of the widget enabled property

  Description:
    Sets the boolean value of the widget enabled property

  Parameters:
	laWidget*
	laBool
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laWidget_SetEnabled(laWidget* widget, laBool enable);

// *****************************************************************************
/* Function:
    laBool laWidget_GetVisible(laWidget* widget)
	
  Summary:
    Returns the boolean value of the widget visible property

  Description:
    Returns the boolean value of the widget visible property

  Parameters:
	laWidget*	
	
  Returns:
	laBool
	
  Remarks:
    
*/
LIB_EXPORT laBool laWidget_GetVisible(laWidget* widget);

// *****************************************************************************
/* Function:
    void laWidget_SetVisible(laWidget* widget, laBool visible)
	
  Summary:
    Sets the boolean value of the widget visible property

  Description:
    Sets the boolean value of the widget visible property

  Parameters:
	laWidget*
	laBool
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laWidget_SetVisible(laWidget* widget, laBool visible);

// *****************************************************************************
/* Function:
    laScheme* laWidget_GetScheme(laWidget* widget)
	
  Summary:
    Returns the scheme associated with the specified widget

  Description:
    Returns the scheme associated with the specified widget

  Parameters:
	laWidget*
		
  Returns:
	laScheme*
	
  Remarks:
    
*/
LIB_EXPORT laScheme* laWidget_GetScheme(laWidget* widget);

// *****************************************************************************
/* Function:
    void laWidget_SetScheme(laWidget* widget, laScheme* scheme)
	
  Summary:
    Sets the scheme variable for the specified widget

  Description:
    Sets the scheme variable for the specified widget
	The scheme defines the appearance of the widget

  Parameters:
	laWidget*
	laScheme*
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laWidget_SetScheme(laWidget* widget, laScheme* scheme);

// *****************************************************************************
/* Function:
    void laWidget_SetPosition(laWidget* widget, int32_t x, int32_t y)
	
  Summary:
    Changes the widget position to the new defined x and y ordinates.

  Description:
	Changes the widget position to the new defined x and y ordinates.
	The widget rectangle upper left x and y co-ordinates are assigned to be the x and y values specified in the arguments.
	The function paints over the older widget area and the new widget area and moves the widget making sure the areas are clean and do not contain any dirty objects.


  Parameters:
	laWidget*
	int32_t
	int32_t
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laWidget_SetPosition(laWidget* widget, int32_t x, int32_t y);

// *****************************************************************************
/* Function:
    void laWidget_Translate(laWidget* widget, int32_t x, int32_t y)
	
  Summary:
    Changes the widget position by moving the widget by the defined x and y increments.

  Description:
	Changes the widget position by moving the widget by the defined x and y increments.
	The widget rectangle upper left x and y co-ordinates are added to be the x and y values specified in the arguments.
	The function paints over the older widget area and the new widget area and moves the widget making sure the areas are clean and do not contain any dirty objects.


  Parameters:
	laWidget*
	int32_t
	int32_t
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laWidget_Translate(laWidget* widget, int32_t x, int32_t y);

// *****************************************************************************
/* Function:
    void laWidget_SetSize(laWidget* widget, uint32_t width, uint32_t height)
	
  Summary:
    Changes the widget size to the new defined width and height dimensions.

  Description:
	Changes the widget size to the new width and height dimensions.
	
  Parameters:
	laWidget*
	int32_t
	int32_t
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laWidget_SetSize(laWidget* widget, uint32_t width, uint32_t height);

// *****************************************************************************
/* Function:
    void laWidget_Resize(laWidget* widget, int32_t width, int32_t height)
	
  Summary:
    Changes the widget size by the new defined width and height increments.

  Description:
	Changes the widget size by the new defined width and height increments.
	
  Parameters:
	laWidget*
	int32_t
	int32_t
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laWidget_Resize(laWidget* widget, int32_t width, int32_t height);

// *****************************************************************************
/* Function:
    laBorderType laWidget_GetBorderType(laWidget* widget)
	
  Summary:
    Return the border type associated with the widget object

  Description:
	Return the border type associated with the widget object
	
  Parameters:
	laWidget*
	
  Returns:
	laBorderType
	
  Remarks:
    
*/
LIB_EXPORT laBorderType laWidget_GetBorderType(laWidget* widget);

// *****************************************************************************
/* Function:
    void laWidget_SetBorderType(laWidget* widget, laBorderType type)
	
  Summary:
    Set the border type associated with the widget object

  Description:
	Set the border type associated with the widget object
	
  Parameters:
	laWidget*
	laBorderType
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laWidget_SetBorderType(laWidget* widget, laBorderType type);

// *****************************************************************************
/* Function:
    laBool laWidget_GetDrawBackground(laWidget* widget)
	
  Summary:
    Return the property value 'draw background' associated with the widget object

  Description:
	Return the property value 'draw background' associated with the widget object
	The draw background property decides if the widget background is drawn and re-drawn. 
	If draw background is unmarked, currently the entire parent widget will be re-drawn 
	in the event that the widget gets dirty and needs re-drawing.
	
  Parameters:
	laWidget*
		
  Returns:
	laBool
	
  Remarks:
    
*/
LIB_EXPORT laBool laWidget_GetDrawBackground(laWidget* widget);

// *****************************************************************************
/* Function:
    void laWidget_SetDrawBackground(laWidget* widget, laBool enable)
	
  Summary:
    Set the property value 'draw background' associated with the widget object

  Description:
	Set the property value 'draw background' associated with the widget object
	The draw background property decides if the widget background is drawn and re-drawn. 
	If draw background is unmarked, currently the entire parent widget will be re-drawn 
	in the event that the widget gets dirty and needs re-drawing.
	
  Parameters:
	laWidget*
	laBool
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laWidget_SetDrawBackground(laWidget* widget, laBool enable);

LIB_EXPORT laBool laWidget_GetLocalRedraw(laWidget* widget);
LIB_EXPORT void laWidget_SetLocalRedraw(laWidget* widget, laBool enable);

// *****************************************************************************
/* Function:
    laResult laWidget_GetMargin (laWidget* widget, laMargin* mg)
	
  Summary:
    Returns the margin value associated with the widget in the laMargin pointer 

  Description:
	Returns the margin value associated with the widget in the laMargin pointer
	
  Parameters:
	laWidget*
	laMargin*
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laWidget_GetMargin (laWidget* widget, laMargin* mg);

// *****************************************************************************
/* Function:
    void laWidget_SetMargins(laWidget* widget,
                                    uint32_t left,
                                    uint32_t top,
                                    uint32_t right,
                                    uint32_t bottom)
	
  Summary:
    Set the margin value for left, right, top and bottom margins associated with the widget

  Description:
	Set the margin value for left, right, top and bottom margins associated with the widget
	
  Parameters:
	laWidget*
	uint32_t
	uint32_t
	uint32_t
	uint32_t
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laWidget_SetMargins(laWidget* widget,
                                    uint32_t left,
                                    uint32_t top,
                                    uint32_t right,
                                    uint32_t bottom);

// *****************************************************************************
/* Function:
    laBool laWidget_HasFocus(laWidget* widget)
	
  Summary:
    Checks if the widget specified has focus in the current context

  Description:
	Checks if the widget specified has focus in the current context
	Returns TRUe if the widget has focus and FALSE if the widget is not in focus
	
  Parameters:
	laWidget*
	
  Returns:
	laBool
	
  Remarks:
    
*/								
LIB_EXPORT laBool laWidget_HasFocus(laWidget* widget);

// *****************************************************************************
/* Function:
    laResult laWidget_SetFocus(laWidget* widget)
	
  Summary:
    Set the widget into focus for the current context.

  Description:
	Set the widget into focus for the current context.
	The input events etc are received by the widget once it is in focus
	
  Parameters:
	laWidget*
	
  Returns:
	laBool
	
  Remarks:
    
*/	
LIB_EXPORT laResult laWidget_SetFocus(laWidget* widget); 

// *****************************************************************************
/* Function:
    laResult laWidget_OverrideTouchDownEvent(laWidget* widget, laWidget_TouchDownEvent_FnPtr ptr)
	
  Summary:
    Replace the TouchDownEvent callback for the widget with the new function pointer specified

  Description:
	Replace the TouchDownEvent callback for the widget with the new function pointer specified
	
  Parameters:
	laWidget*
	laWidget_TouchDownEvent_FnPtr
	
  Returns:
	laResult
	
  Remarks:
    
*/	
LIB_EXPORT laResult laWidget_OverrideTouchDownEvent(laWidget* widget, laWidget_TouchDownEvent_FnPtr ptr);

// *****************************************************************************
/* Function:
    laResult laWidget_OverrideTouchUpEvent(laWidget* widget, laWidget_TouchUpEvent_FnPtr ptr)
	
  Summary:
    Replace the TouchUpEvent callback for the widget with the new function pointer specified

  Description:
	Replace the TouchUpEvent callback for the widget with the new function pointer specified
	
  Parameters:
	laWidget*
	laWidget_TouchUpEvent_FnPtr
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laWidget_OverrideTouchUpEvent(laWidget* widget, laWidget_TouchUpEvent_FnPtr ptr);

// *****************************************************************************
/* Function:
    laResult laWidget_OverrideTouchMovedEvent(laWidget* widget, laWidget_TouchMovedEvent_FnPtr ptr)
	
  Summary:
    Replace the TouchMovedEvent callback for the widget with the new function pointer specified

  Description:
	Replace the TouchMovedEvent callback for the widget with the new function pointer specified
	
  Parameters:
	laWidget*
	laWidget_TouchMovedEvent_FnPtr
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laWidget_OverrideTouchMovedEvent(laWidget* widget, laWidget_TouchMovedEvent_FnPtr ptr);

// *****************************************************************************
/* Function:
    void laWidget_Invalidate(laWidget* widget)
	
  Summary:
    Re-draws the widget specified.

  Description:
	Re-draws the widget specified.
	The function evaluates if the widget alone, parent widget or the entire layer has to be re-drawn.
	
  Parameters:
	laWidget*
		
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laWidget_Invalidate(laWidget* widget);

//void _laWidget_InvalidateArea(laWidget* widget, GFX_Rect* rect);
void _laWidget_InvalidateRight(laWidget* widget, GFX_Rect* rect);
void _laWidget_InvalidateArea(laWidget* widget, GFX_Rect* area);

void _laWidget_ChildInvalidated(laWidget* parent, laWidget* child);

void _laWidget_InvalidateChildren(laWidget* widget);
void _laWidget_ValidateChildren(laWidget* widget);

#endif /* LIBARIA_WIDGET_H */