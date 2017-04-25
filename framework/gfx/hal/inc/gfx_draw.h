/*******************************************************************************
 Module for Microchip Graphics Library - Hardware Abstraction Layer

  Company:
    Microchip Technology Inc.

  File Name:
    gfx_draw.h

  Summary:
    Main header file for MPLAB Harmony Graphics Hardware Abstraction primitive
    draw functions

  Description:
    Shape drawing functions.
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
#ifndef GFX_DRAW_H
#define GFX_DRAW_H
//DOM-IGNORE-END

#include "gfx/hal/inc/gfx_common.h"

#if GFX_DRAW_PIPELINE_ENABLED

#include "gfx/hal/inc/gfx_draw_blit.h"
#include "gfx/hal/inc/gfx_draw_circle.h"
#include "gfx/hal/inc/gfx_draw_line.h"
#include "gfx/hal/inc/gfx_draw_pixel.h"
#include "gfx/hal/inc/gfx_draw_rect.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Enumeration:
    GFX_DrawMode_t

  Summary:
    Gradient draw modes.

  Description:
    line - draws the outline of a shape
    fill - draws a filled shape
    gradient left/right - draws a gradient from left to right, uses the first
                          two gradient colors
    gradient top/bottom - draws a gradient from top to bottom, uses the first
                          two gradient colors
    

  Remarks:
    None.
*/
typedef enum GFX_DrawMode_t
{
    GFX_DRAW_LINE = 0x0,
    GFX_DRAW_FILL,
    GFX_DRAW_GRADIENT_LEFT_RIGHT,
    GFX_DRAW_GRADIENT_TOP_BOTTOM
} GFX_DrawMode;

#define GFX_DRAW_MODE_COUNT (GFX_DRAW_GRADIENT_TOP_BOTTOM + 1)

// *****************************************************************************
/* Enumeration:
    GFX_AntialiasMode_t

  Summary:
    Enables anti-aliased drawing hint

  Description:
    

  Remarks:
    None.
*/
typedef enum GFX_AntialiasMode_t
{
    GFX_ANTIALIAS_OFF = 0x0,
    GFX_ANTIALIAS_ON  = 0x1
} GFX_AntialiasMode;

#define GFX_ANTIALIAS_MODE_COUNT (GFX_ANTIALIAS_ON+1)

// *****************************************************************************
/* Structure:
    GFX_DrawState_t

  Summary:
    A list of drawing hints for shape drawing algorithms

  Description:
    mode - the shape drawing mode
    
    color - the draw color
    
    gradient - the list of gradient colors
    
    palette - the palette lookup table for blits
    
    alphaEnable - indicates if alpha blending is enabled
    alphaValue - the desired alpha blending amount
    
    maskEnable - indicates if pixel masking is enabled    
    maskValue - the mask/transparency color value
    
    clipEnable - indicate of pixel clipping is enabled
    clipRect - the pixel clipping rectangle

  Remarks:
    None.
*/
typedef struct GFX_DrawState_t
{
    GFX_DrawMode mode;
    
    GFX_Color color;
    
    struct
    {
        GFX_Color c0;
        GFX_Color c1;
        GFX_Color c2;
        GFX_Color c3;
    } gradient;
    
    GFX_PixelBuffer palette;
    
    GFX_Bool alphaEnable;
    uint32_t alphaValue;
    
    GFX_Bool maskEnable;
    uint32_t maskValue;
    
    GFX_Bool antialias;
    uint32_t thickness;

    GFX_Bool clipEnable;
    GFX_Rect clipRect;    
} GFX_DrawState;

#endif // GFX_DRAW_PIPELINE_ENABLED

#endif /* GFX_DRAW_H */
