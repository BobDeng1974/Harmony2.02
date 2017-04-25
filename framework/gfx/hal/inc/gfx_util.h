/*******************************************************************************
 Module for Microchip Graphics Library - Hardware Abstraction Layer

  Company:
    Microchip Technology Inc.

  File Name:
    gfx_util.h

  Summary:
    Utility functions for the Hardware Abstraction Layer

  Description:
    Layer and point utility functions.
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
#ifndef GFX_UTIL_H
#define GFX_UTIL_H
//DOM-IGNORE-END

#include "gfx/hal/inc/gfx_common.h"

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    void GFX_UtilOrientPoint(GFX_Point* point,
                             GFX_Rect* rect,
                             GFX_Orientation ori,
                             GFX_Bool mirror)

  Summary:
    Reorients a point to a given orthogonal orientation and mirroring 
    alignment.

  Parameters:
	GFX_Point* point - the point to reorient
	GFX_Rect* rect - the bounding rectangle space
	GFX_Orientation - the orientation setting
	GFX_Bool - the mirroring setting
	
  Returns:
	void
*/
void GFX_UtilOrientPoint(GFX_Point* point,
                         GFX_Rect* rect,
                         GFX_Orientation ori,
                         GFX_Bool mirror);
			 
// *****************************************************************************
/* Function:
    void GFX_LayerOriginFromOrientedSpace(GFX_Point* point,
									      GFX_Rect* displayRect,
									      GFX_Rect* layerRect,
									      GFX_Orientation ori,
									      GFX_Bool mirrored)

  Summary:
    Transforms a layer point from oriented space to screen space given
    a display rectangle, a display orientation, and a mirroring setting.

  Parameters:
	GFX_Point* point - the origin point
	GFX_Rect* dispayRect - the rectangle of the display
	GFX_Rect* layerRect - the layer rectangle
	GFX_Orientation - the orientation setting
	GFX_Bool - the mirroring setting
	
  Returns:
	void
*/					 
void GFX_LayerOriginFromOrientedSpace(GFX_Point* point,
									  GFX_Rect* displayRect,
									  GFX_Rect* layerRect,
									  GFX_Orientation ori,
									  GFX_Bool mirrored);

// *****************************************************************************
/* Function:
    void GFX_LayerOriginToOrientedSpace(GFX_Point* point,
									GFX_Rect* displayRect,
									GFX_Rect* layerRect,
									GFX_Orientation ori,
									GFX_Bool mirrored)

  Summary:
    Transforms a layer point from screen space to oriented space given
    a display rectangle, a display orientation, and a mirroring setting.

  Parameters:
	GFX_Point* point - the origin point
	GFX_Rect* dispayRect - the rectangle of the display
	GFX_Rect* layerRect - the layer rectangle
	GFX_Orientation - the orientation setting
	GFX_Bool - the mirroring setting
	
  Returns:
	void
*/									  
void GFX_LayerOriginToOrientedSpace(GFX_Point* point,
									GFX_Rect* displayRect,
									GFX_Rect* layerRect,
									GFX_Orientation ori,
									GFX_Bool mirrored);

// *****************************************************************************
/* Function:
    void GFX_LayerSizeFromOrientedSpace(GFX_Size* layerSize, GFX_Orientation ori)

  Summary:
    Transforms a layer size tuple from oriented space to screen space

  Parameters:
	GFX_Size* layerSize - the size dimension
	GFX_Orientation - the orientation setting
		
  Returns:
	void
*/									
void GFX_LayerSizeFromOrientedSpace(GFX_Size* layerSize, GFX_Orientation ori);

// *****************************************************************************
/* Function:
    void GFX_LayerSizeToOrientedSpace(GFX_Size* layerSize, GFX_Orientation ori)

  Summary:
    Transforms a layer size tuple from screen space to oriented space

  Parameters:
	GFX_Size* layerSize - the size dimension
	GFX_Orientation - the orientation setting
		
  Returns:
	void
*/
void GFX_LayerSizeToOrientedSpace(GFX_Size* layerSize, GFX_Orientation ori);
                         
#endif /* GFX_UTIL_H */