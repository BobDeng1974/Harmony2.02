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
 * Name:   Left_Blue
 * Size:   60x60 pixels
 * Mode:   ARGB_8888
 * Format: PNG
 ***********************************/
extern GFXU_ImageAsset Left_Blue;
	
/*********************************
 * GFX Image Asset
 * Name:   Left_Green
 * Size:   60x60 pixels
 * Mode:   ARGB_8888
 * Format: PNG
 ***********************************/
extern GFXU_ImageAsset Left_Green;
	
/*********************************
 * GFX Image Asset
 * Name:   Left_Grey
 * Size:   60x60 pixels
 * Mode:   ARGB_8888
 * Format: PNG
 ***********************************/
extern GFXU_ImageAsset Left_Grey;
	
/*********************************
 * GFX Image Asset
 * Name:   Left_Magenta
 * Size:   60x60 pixels
 * Mode:   ARGB_8888
 * Format: PNG
 ***********************************/
extern GFXU_ImageAsset Left_Magenta;
	
/*********************************
 * GFX Image Asset
 * Name:   Left_Orange
 * Size:   60x60 pixels
 * Mode:   ARGB_8888
 * Format: PNG
 ***********************************/
extern GFXU_ImageAsset Left_Orange;
	
/*********************************
 * GFX Image Asset
 * Name:   Right_Blue
 * Size:   60x60 pixels
 * Mode:   ARGB_8888
 * Format: PNG
 ***********************************/
extern GFXU_ImageAsset Right_Blue;
	
/*********************************
 * GFX Image Asset
 * Name:   Right_Green
 * Size:   60x60 pixels
 * Mode:   ARGB_8888
 * Format: PNG
 ***********************************/
extern GFXU_ImageAsset Right_Green;
	
/*********************************
 * GFX Image Asset
 * Name:   Right_Grey
 * Size:   60x60 pixels
 * Mode:   ARGB_8888
 * Format: PNG
 ***********************************/
extern GFXU_ImageAsset Right_Grey;
	
/*********************************
 * GFX Image Asset
 * Name:   Right_Magenta
 * Size:   60x60 pixels
 * Mode:   ARGB_8888
 * Format: PNG
 ***********************************/
extern GFXU_ImageAsset Right_Magenta;
	
/*********************************
 * GFX Image Asset
 * Name:   Right_Orange
 * Size:   60x60 pixels
 * Mode:   ARGB_8888
 * Format: PNG
 ***********************************/
extern GFXU_ImageAsset Right_Orange;
	
/*********************************
 * GFX Image Asset
 * Name:   MicrochipLogo
 * Size:   300x180 pixels
 * Mode:   RGB_888
 * Format: JPEG
 ***********************************/
extern GFXU_ImageAsset MicrochipLogo;
	
/*********************************
 * GFX Image Asset
 * Name:   NewHarmonyLogo
 * Size:   300x180 pixels
 * Mode:   RGB_888
 * Format: JPEG
 ***********************************/
extern GFXU_ImageAsset NewHarmonyLogo;
	
/*********************************
 * GFX Image Asset
 * Name:   LucyInTheSky
 * Size:   363x272 pixels
 * Mode:   RGB_888
 * Format: JPEG
 ***********************************/
extern GFXU_ImageAsset LucyInTheSky;
	
/*********************************
 * GFX Image Asset
 * Name:   USA
 * Size:   417x272 pixels
 * Mode:   RGB_888
 * Format: JPEG
 ***********************************/
extern GFXU_ImageAsset USA;
	
/*********************************
 * GFX Image Asset
 * Name:   ice_color
 * Size:   480x300 pixels
 * Mode:   RGB_888
 * Format: JPEG
 ***********************************/
extern GFXU_ImageAsset ice_color;
	
/*****************************************************************************
 * MPLAB Harmony Graphics Font Assets
 *****************************************************************************/
/*********************************
 * GFX Font Asset
 * Name:         Calibri
 * Height:       20
 * Style:        Plain
 * Glyph Count:  23
 * Range Count:  10
 * Glyph Ranges: 0x43
			     0x45-0x46
			     0x4E
			     0x50
			     0x53-0x54
			     0x63-0x69
			     0x6C
			     0x6E-0x6F
			     0x72-0x76
			     0x78
 ***********************************/
extern GFXU_FontAsset Calibri;
	
/*********************************
 * GFX Font Asset
 * Name:         ArialUnicodeMS
 * Height:       23
 * Style:        Plain
 * Glyph Count:  72
 * Range Count:  36
 * Glyph Ranges: 0x20
			     0x30-0x39
			     0x54
			     0x61-0x7A
			     0x2190
			     0x4E00
			     0x4E03
			     0x4E09-0x4E0B
			     0x4E2D
			     0x4E5D
			     0x4E8C
			     0x4E94
			     0x5165
			     0x516B
			     0x516D
			     0x5373
			     0x53EF
			     0x56DB
			     0x59CB
			     0x5B57
			     0x6478
			     0x6587
			     0x683C
			     0x6D88
			     0x7A7A
			     0x7B2C
			     0x82F1
			     0x865F
			     0x89F8
			     0x8A9E
			     0x8F38
			     0x9375
			     0x958B
			     0x9664
			     0x96F6
			     0x9801
 ***********************************/
extern GFXU_FontAsset ArialUnicodeMS;
	
/*********************************
 * GFX Font Asset
 * Name:         ArialUnicodeMS_Large
 * Height:       25
 * Style:        Bold
 * Glyph Count:  28
 * Range Count:  20
 * Glyph Ranges: 0x20
			     0x41-0x42
			     0x47-0x48
			     0x4C-0x4D
			     0x50
			     0x53
			     0x61
			     0x63
			     0x65
			     0x68-0x69
			     0x6D-0x70
			     0x72-0x73
			     0x77
			     0x79
			     0x50CF
			     0x548C
			     0x5716
			     0x793A
			     0x7BC4
			     0x8AE7
 ***********************************/
extern GFXU_FontAsset ArialUnicodeMS_Large;
	
/*****************************************************************************
 * MPLAB Harmony Graphics String Table
 *****************************************************************************/
/*********************************
 * GFX String Table
 * Name:         stringTable
 * Encoding:     UTF8
 * Languages:    English, Chinese
 * String Count: 51
 ***********************************/
// language IDs
#define language_English    0
#define language_Chinese    1

// string IDs
#define string_Listbox_Item1    0
#define string_Listbox_Item2    1
#define string_Listbox_Item3    2
#define string_Listbox_Item4    3
#define string_Listbox_Item5    4
#define string_RadioButton_English    5
#define string_RadioButton_Chinese    6
#define string_ButtonNextScreen    7
#define string_ButtonPreviousScreen    8
#define string_Keypad_a    9
#define string_Keypad_b    10
#define string_Keypad_c    11
#define string_Keypad_d    12
#define string_Keypad_e    13
#define string_Keypad_f    14
#define string_Keypad_g    15
#define string_Keypad_h    16
#define string_Keypad_i    17
#define string_Keypad_j    18
#define string_Keypad_k    19
#define string_Keypad_l    20
#define string_Keypad_m    21
#define string_Keypad_n    22
#define string_Keypad_o    23
#define string_Keypad_p    24
#define string_Keypad_q    25
#define string_Keypad_r    26
#define string_Keypad_s    27
#define string_Keypad_t    28
#define string_Keypad_u    29
#define string_Keypad_v    30
#define string_Keypad_w    31
#define string_Keypad_x    32
#define string_Keypad_y    33
#define string_Keypad_z    34
#define string_Keypad_1    35
#define string_Keypad_2    36
#define string_Keypad_3    37
#define string_Keypad_4    38
#define string_Keypad_5    39
#define string_Keypad_6    40
#define string_Keypad_7    41
#define string_Keypad_8    42
#define string_Keypad_9    43
#define string_Keypad_0    44
#define string_Backspace    45
#define string_clear    46
#define string_spacebar    47
#define string_textField_Instruction    48
#define string_Title    49
#define string_Harmony    50
 
extern GFXU_StringTableAsset stringTable;

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* GFX_ASSETS_H */

