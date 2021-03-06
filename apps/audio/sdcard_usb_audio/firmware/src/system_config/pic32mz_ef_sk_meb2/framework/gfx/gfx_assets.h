/*******************************************************************************
  MPLAB Harmony Graphics Asset Header File

  File Name:
    gfx_assets.h

  Summary:
    Header file containing a list of asset specifications for use with the
	MPLAB Harmony Graphics Stack.

  Description:
    Header file containing a list of asset specifications for use with the
	MPLAB Harmony Graphics Stack.

    Created with MPLAB Harmony Version 2.02
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
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
// DOM-IGNORE-END

#ifndef GFX_ASSETS_H
#define GFX_ASSETS_H

#include "gfx/utils/gfx_utils.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END 

/*** Generated Asset Descriptors ***/
/*****************************************************************************
 * MPLAB Harmony Graphics Asset Location IDs
 *****************************************************************************/
#define GFXU_ASSET_LOCATION_ID_INTERNAL    0
 
/*****************************************************************************
 * MPLAB Harmony Graphics Image Assets
 *****************************************************************************/
/*********************************
 * GFX Image Asset
 * Name:   AudioMute16_2
 * Size:   32x25 pixels
 * Mode:   INDEX_4
 * Format: RAW
 ***********************************/
extern GFXU_ImageAsset AudioMute16_2;
	
/*********************************
 * GFX Image Asset
 * Name:   AudioPlay16_2
 * Size:   29x22 pixels
 * Mode:   INDEX_4
 * Format: RAW
 ***********************************/
extern GFXU_ImageAsset AudioPlay16_2;
	
/*********************************
 * GFX Image Asset
 * Name:   MCHP_LOGO
 * Size:   122x30 pixels
 * Mode:   RGB_888
 * Format: RAW
 ***********************************/
extern GFXU_ImageAsset MCHP_LOGO;
	
/*****************************************************************************
 * MPLAB Harmony Graphics Palette Assets
 *****************************************************************************/
/*********************************
 * GFX Palette Asset
 * Name:   AudioMute16_2_palette
 * Colors: 6
 * Format: RGB_888
 ***********************************/
extern GFXU_PaletteAsset AudioMute16_2_palette;
	
/*********************************
 * GFX Palette Asset
 * Name:   AudioPlay16_2_palette
 * Colors: 5
 * Format: RGB_888
 ***********************************/
extern GFXU_PaletteAsset AudioPlay16_2_palette;
	
/*****************************************************************************
 * MPLAB Harmony Graphics Font Assets
 *****************************************************************************/
/*********************************
 * GFX Font Asset
 * Name:         Arial14pt
 * Height:       17
 * Style:        Plain
 * Glyph Count:  96
 * Range Count:  1
 * Glyph Ranges: 0x20-0x7F
 ***********************************/
extern GFXU_FontAsset Arial14pt;
	
/*********************************
 * GFX Font Asset
 * Name:         Arial
 * Height:       24
 * Style:        Plain
 * Glyph Count:  2
 * Range Count:  2
 * Glyph Ranges: 0x2B
			     0x2D
 ***********************************/
extern GFXU_FontAsset Arial;
	
/*****************************************************************************
 * MPLAB Harmony Graphics String Table
 *****************************************************************************/
/*********************************
 * GFX String Table
 * Name:         stringTable
 * Encoding:     ASCII
 * Languages:    English
 * String Count: 6
 ***********************************/
// language IDs
#define language_English    0

// string IDs
#define string_sd_radio_button_str    0
#define string_usb_radio_button_str    1
#define string_group_box_str    2
#define string_demo_title_str    3
#define string_volume_up_button_str    4
#define string_volume_down_button_str    5
 
extern GFXU_StringTableAsset stringTable;

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* GFX_ASSETS_H */

