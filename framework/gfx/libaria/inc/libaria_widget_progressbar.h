/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_progressbar.h

  Summary:
    

  Description:
    This module implements progress bar widget functions.
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

#ifndef LIBARIA_PROGRESSBAR_H
#define LIBARIA_PROGRESSBAR_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_PROGRESSBAR_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_widget.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Enumeration:
    laProgressBarDirection_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef enum laProgressBarDirection_t
{
    LA_PROGRESSBAR_DIRECTION_RIGHT,
    LA_PROGRESSBAR_DIRECTION_UP,
    LA_PROGRESSBAR_DIRECTION_LEFT,
    LA_PROGRESSBAR_DIRECTION_DOWN
} laProgressBarDirection;

typedef struct laProgressBarWidget_t laProgressBar;

typedef void (*laProgressBar_ValueChangedEventCallback)(laProgressBar*, uint32_t);

// *****************************************************************************
/* Structure:
    laProgressBarDirection_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef struct laProgressBarWidget_t
{
	laWidget widget;
	
    laProgressBarDirection direction;

    uint32_t value;
    
    laProgressBar_ValueChangedEventCallback cb;
} laProgressBarWidget;

void _laProgressBarWidget_Constructor(laProgressBarWidget* bar);
void _laProgressBarWidget_Destructor(laProgressBarWidget* bar);

void _laProgressBarWidget_Paint(laProgressBarWidget* bar);

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laProgressBarWidget* laProgressBarWidget_New()

  Summary:
    

  Description:
    

  Parameters:
	
  Returns:
	laProgressBarWidget*
	
  Remarks:
    
*/
LIB_EXPORT laProgressBarWidget* laProgressBarWidget_New();

// *****************************************************************************
/* Function:
    laProgressBarDirection laProgressBarWidget_GetDirection(laProgressBarWidget* bar)

  Summary:
    

  Description:
    

  Parameters:
	laProgressBarWidget*
	
  Returns:
	laProgressBarDirection
	
  Remarks:
    
*/
LIB_EXPORT laProgressBarDirection laProgressBarWidget_GetDirection(laProgressBarWidget* bar);

// *****************************************************************************
/* Function:
    laResult laProgressBarWidget_SetDirection(laProgressBarWidget* bar, laProgressBarDirection dir)

  Summary:
    

  Description:
    

  Parameters:
	laProgressBarWidget*
	laProgressBarDirection
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laProgressBarWidget_SetDirection(laProgressBarWidget* bar, laProgressBarDirection dir);

// *****************************************************************************
/* Function:
    uint32_t laProgressBarWidget_GetValue(laProgressBarWidget* bar)

  Summary:
    

  Description:
    

  Parameters:
	laProgressBarWidget*
	
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laProgressBarWidget_GetValue(laProgressBarWidget* bar);

// *****************************************************************************
/* Function:
    laResult laProgressBarWidget_SetValue(laProgressBarWidget* bar, uint32_t value)

  Summary:
    

  Description:
    

  Parameters:
	laProgressBarWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laProgressBarWidget_SetValue(laProgressBarWidget* bar, uint32_t value);

// *****************************************************************************
/* Function:
    laProgressBar_ValueChangedEventCallback laProgressBarWidget_GetValueChangedEventCallback(laProgressBarWidget* bar)

  Summary:
    

  Description:
    

  Parameters:
	laProgressBarWidget*
	
  Returns:
	laProgressBar_ValueChangedEventCallback
	
  Remarks:
    
*/
LIB_EXPORT laProgressBar_ValueChangedEventCallback laProgressBarWidget_GetValueChangedEventCallback(laProgressBarWidget* bar);

// *****************************************************************************
/* Function:
    laResult laProgressBarWidget_SetValueChangedCallback(laProgressBarWidget* bar, laProgressBar_ValueChangedEventCallback cb)

  Summary:
    

  Description:
    

  Parameters:
	laProgressBarWidget*
	laProgressBar_ValueChangedEventCallback
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laProgressBarWidget_SetValueChangedCallback(laProgressBarWidget* bar, laProgressBar_ValueChangedEventCallback cb);

#endif // LA_PROGRESSBAR_WIDGET_ENABLED
#endif /* LIBARIA_PROGRESSBAR_H */