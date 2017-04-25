/*******************************************************************************
  MPLAB Harmony Graphics Composer Generated Definitions Header

  File Name:
    gfx_hgc_definitions.h

  Summary:
    Build-time generated definitions header based on output by the MPLAB Harmony
    Graphics Composer.

  Description:
    Build-time generated definitions header based on output by the MPLAB Harmony
    Graphics Composer.

    Created with MPLAB Harmony Version ${CONFIG_MPLAB_HARMONY_VERSION_STRING}
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

<#include "/framework/gfxe/templates/gfx_hgc_definitions_macros.ftl">

#ifndef _GFX_HGC_DEFINITIONS_H
#define _GFX_HGC_DEFINITIONS_H

#include "system_config.h"
#include "system_definitions.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END 

typedef enum
{
    HGC_STATE_INIT = 0,
    HGC_STATE_RUNNING
} HGC_STATES;

typedef enum
{
    HGC_SCREEN_STATE_INIT = 0,
<#assign x=CONFIG_GFX_HGC_NUM_SCREENS>
<#list 0..x-1 as i>
    <@GFX_HGC_SCREEN_STATE_DEF SCR_ID = "CONFIG_GFX_HGC_SCREEN_ID_${i}" />
	
</#list>
} HGC_SCREEN_STATES;

<#if CONFIG_GFX_HGC_HAS_SCHEMES = true>
/*** GFX GOL Scheme Definitions ***/
<#assign x=CONFIG_GFX_HGC_NUM_SCHEMES>
<#list 0..x-1 as i>
    <@GFX_HGC_SCHEME_DEF
        INDEX = "${i}"
        GFX_SCHEME_ALPHA = "CONFIG_GFX_HGC_SCHEME_ALPHA_${i}"
        GFX_SCHEME_NAME = "CONFIG_GFX_HGC_SCHEME_NAME_${i}"

        GFX_SCHEME_PRIMARY_COLOR_RED   = "CONFIG_GFX_HGC_SCHEME_PRIMARY_COLOR_RED_${i}"
        GFX_SCHEME_PRIMARY_COLOR_GREEN = "CONFIG_GFX_HGC_SCHEME_PRIMARY_COLOR_GREEN_${i}"
        GFX_SCHEME_PRIMARY_COLOR_BLUE  = "CONFIG_GFX_HGC_SCHEME_PRIMARY_COLOR_BLUE_${i}"

        GFX_SCHEME_SECONDARY_COLOR_RED   = "CONFIG_GFX_HGC_SCHEME_SECONDARY_COLOR_RED_${i}"
        GFX_SCHEME_SECONDARY_COLOR_GREEN = "CONFIG_GFX_HGC_SCHEME_SECONDARY_COLOR_GREEN_${i}"
        GFX_SCHEME_SECONDARY_COLOR_BLUE  = "CONFIG_GFX_HGC_SCHEME_SECONDARY_COLOR_BLUE_${i}"

        GFX_SCHEME_DISABLED_COLOR_RED   = "CONFIG_GFX_HGC_SCHEME_DISABLED_COLOR_RED_${i}"
        GFX_SCHEME_DISABLED_COLOR_GREEN = "CONFIG_GFX_HGC_SCHEME_DISABLED_COLOR_GREEN_${i}"
        GFX_SCHEME_DISABLED_COLOR_BLUE  = "CONFIG_GFX_HGC_SCHEME_DISABLED_COLOR_BLUE_${i}"

        GFX_SCHEME_BACKGROUND_COLOR_RED   = "CONFIG_GFX_HGC_SCHEME_BACKGROUND_COLOR_RED_${i}"
        GFX_SCHEME_BACKGROUND_COLOR_GREEN = "CONFIG_GFX_HGC_SCHEME_BACKGROUND_COLOR_GREEN_${i}"
        GFX_SCHEME_BACKGROUND_COLOR_BLUE  = "CONFIG_GFX_HGC_SCHEME_BACKGROUND_COLOR_BLUE_${i}"

		GFX_SCHEME_EMBOSS_SIZE = "CONFIG_GFX_HGC_SCHEME_EMBOSS_SIZE_${i}"
		
        GFX_SCHEME_EMBOSS_DARK_COLOR_RED   = "CONFIG_GFX_HGC_SCHEME_EMBOSS_DARK_COLOR_RED_${i}"
        GFX_SCHEME_EMBOSS_DARK_COLOR_GREEN = "CONFIG_GFX_HGC_SCHEME_EMBOSS_DARK_COLOR_GREEN_${i}"
        GFX_SCHEME_EMBOSS_DARK_COLOR_BLUE  = "CONFIG_GFX_HGC_SCHEME_EMBOSS_DARK_COLOR_BLUE_${i}"

        GFX_SCHEME_EMBOSS_LIGHT_COLOR_RED   = "CONFIG_GFX_HGC_SCHEME_EMBOSS_LIGHT_COLOR_RED_${i}"
        GFX_SCHEME_EMBOSS_LIGHT_COLOR_GREEN = "CONFIG_GFX_HGC_SCHEME_EMBOSS_LIGHT_COLOR_GREEN_${i}"
        GFX_SCHEME_EMBOSS_LIGHT_COLOR_BLUE  = "CONFIG_GFX_HGC_SCHEME_EMBOSS_LIGHT_COLOR_BLUE_${i}"

        GFX_SCHEME_TEXT_PRIMARY_COLOR_RED   = "CONFIG_GFX_HGC_SCHEME_TEXT_PRIMARY_COLOR_RED_${i}"
        GFX_SCHEME_TEXT_PRIMARY_COLOR_GREEN = "CONFIG_GFX_HGC_SCHEME_TEXT_PRIMARY_COLOR_GREEN_${i}"
        GFX_SCHEME_TEXT_PRIMARY_COLOR_BLUE  = "CONFIG_GFX_HGC_SCHEME_TEXT_PRIMARY_COLOR_BLUE_${i}"

        GFX_SCHEME_TEXT_SECONDARY_COLOR_RED   = "CONFIG_GFX_HGC_SCHEME_TEXT_SECONDARY_COLOR_RED_${i}"
        GFX_SCHEME_TEXT_SECONDARY_COLOR_GREEN = "CONFIG_GFX_HGC_SCHEME_TEXT_SECONDARY_COLOR_GREEN_${i}"
        GFX_SCHEME_TEXT_SECONDARY_COLOR_BLUE  = "CONFIG_GFX_HGC_SCHEME_TEXT_SECONDARY_COLOR_BLUE_${i}"

        GFX_SCHEME_TEXT_DISABLED_COLOR_RED   = "CONFIG_GFX_HGC_SCHEME_TEXT_DISABLED_COLOR_RED_${i}"
        GFX_SCHEME_TEXT_DISABLED_COLOR_GREEN = "CONFIG_GFX_HGC_SCHEME_TEXT_DISABLED_COLOR_GREEN_${i}"
        GFX_SCHEME_TEXT_DISABLED_COLOR_BLUE  = "CONFIG_GFX_HGC_SCHEME_TEXT_DISABLED_COLOR_BLUE_${i}"

		GFX_SCHEME_GRADIENT_START_COLOR_RED   = "CONFIG_GFX_HGC_SCHEME_GRADIENT_START_COLOR_RED_${i}"
        GFX_SCHEME_GRADIENT_START_COLOR_GREEN = "CONFIG_GFX_HGC_SCHEME_GRADIENT_START_COLOR_GREEN_${i}"
        GFX_SCHEME_GRADIENT_START_COLOR_BLUE  = "CONFIG_GFX_HGC_SCHEME_GRADIENT_START_COLOR_BLUE_${i}"
		
		GFX_SCHEME_GRADIENT_END_COLOR_RED   = "CONFIG_GFX_HGC_SCHEME_GRADIENT_END_COLOR_RED_${i}"
        GFX_SCHEME_GRADIENT_END_COLOR_GREEN = "CONFIG_GFX_HGC_SCHEME_GRADIENT_END_COLOR_GREEN_${i}"
        GFX_SCHEME_GRADIENT_END_COLOR_BLUE  = "CONFIG_GFX_HGC_SCHEME_GRADIENT_END_COLOR_BLUE_${i}"

        GFX_SCHEME_BACKGROUND_OFFSET_TOP = "CONFIG_GFX_HGC_SCHEME_BACKGROUND_OFFSET_TOP_${i}"
        GFX_SCHEME_BACKGROUND_OFFSET_LEFT = "CONFIG_GFX_HGC_SCHEME_BACKGROUND_OFFSET_LEFT_${i}"
		
		GFX_SCHEME_FILL_STYLE = "CONFIG_GFX_HGC_SCHEME_FILL_STYLE_${i}"
		GFX_SCHEME_BACKGROUND_TYPE = "CONFIG_GFX_HGC_SCHEME_BACKGROUND_TYPE_${i}"
        />
		
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_BUTTONS = true>
/*** GFX GOL Button Definitions ***/
<#assign x=CONFIG_GFX_HGC_NUM_BUTTONS>
<#list 0..x-1 as i>
    <@GFX_HGC_BUTTON_DEF
        INDEX = "${i}"
        GFX_BUTTON_LEFT = "CONFIG_HGC_BTN_LEFT_${i}"
        GFX_BUTTON_TOP = "CONFIG_HGC_BTN_TOP_${i}"
        GFX_BUTTON_RIGHT = "CONFIG_HGC_BTN_RIGHT_${i}"
        GFX_BUTTON_BOTTOM = "CONFIG_HGC_BTN_BOTTOM_${i}"
        GFX_BUTTON_RADIUS = "CONFIG_HGC_BTN_RADIUS_${i}"
        GFX_BUTTON_STATE = "CONFIG_HGC_BTN_STATE_${i}"
        GFX_BUTTON_PRESS_IMAGE = "CONFIG_HGC_BTN_PRESS_IMAGE_${i}"
        GFX_BUTTON_RELEASE_IMAGE = "CONFIG_HGC_BTN_RELEASE_IMAGE_${i}"
        GFX_BUTTON_TEXT = "CONFIG_HGC_BTN_TEXT_${i}"
        GFX_BUTTON_ALIGNMENT = "CONFIG_HGC_BTN_ALIGNMENT_${i}"
        GFX_BUTTON_SCHEME = "CONFIG_HGC_BTN_SCHEME_${i}"
        />
		
</#list>
/*** Button IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_BUTTONS> 
<#list 0..x-1 as i>
    <@GFX_HGC_BUTTON_ID_DEF 
	ID = "CONFIG_HGC_BTN_ID_${i}"
	VALUE = "${100+i}"
	/>
	
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_DGTL_MTRS = true>
/*** GFX GOL Digital Meter Definitions ***/
<#assign x=CONFIG_GFX_HGC_NUM_DGTL_MTRS>
<#list 0..x-1 as i>
    <@GFX_HGC_DGTL_MTR_DEF
        INDEX = "${i}"
        GFX_DGTL_MTR_LEFT = "CONFIG_HGC_DGTL_MTR_LEFT_${i}"
        GFX_DGTL_MTR_TOP = "CONFIG_HGC_DGTL_MTR_TOP_${i}"
        GFX_DGTL_MTR_RIGHT = "CONFIG_HGC_DGTL_MTR_RIGHT_${i}"
        GFX_DGTL_MTR_BOTTOM = "CONFIG_HGC_DGTL_MTR_BOTTOM_${i}"	
		GFX_DGTL_MTR_STATE = "CONFIG_HGC_DGTL_MTR_STATE_${i}"
        GFX_DGTL_MTR_VALUE = "CONFIG_HGC_DGTL_MTR_VALUE_${i}"
        GFX_DGTL_MTR_NO_OF_DIGITS = "CONFIG_HGC_DGTL_MTR_NO_OF_DIGITS_${i}"
        GFX_DGTL_MTR_DOT_POSITION = "CONFIG_HGC_DGTL_MTR_DOT_POSITION_${i}"
        GFX_DGTL_MTR_ALIGNMENT = "CONFIG_HGC_DGTL_MTR_ALIGNMENT_${i}"
        GFX_DGTL_MTR_SCHEME = "CONFIG_HGC_DGTL_MTR_SCHEME_${i}"
		/>
		
</#list>
/*** Digital Meter IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_DGTL_MTRS>
<#list 0..x-1 as i>
    <@GFX_HGC_DGTL_MTR_ID_DEF ID="CONFIG_HGC_DGTL_MTR_ID_${i}" VALUE="${200+i}"/>
	
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_CHECKBOXES = true>
/*** GFX GOL Checkbox Definitions ***/
<#assign x=CONFIG_GFX_HGC_NUM_CHECKBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_CHECKBOX_DEF
        INDEX = "${i}"
        GFX_CHECKBOX_LEFT = "CONFIG_HGC_CHECKBOX_LEFT_${i}"
        GFX_CHECKBOX_TOP = "CONFIG_HGC_CHECKBOX_TOP_${i}"
        GFX_CHECKBOX_RIGHT = "CONFIG_HGC_CHECKBOX_RIGHT_${i}"
        GFX_CHECKBOX_BOTTOM = "CONFIG_HGC_CHECKBOX_BOTTOM_${i}"
        GFX_CHECKBOX_TEXT = "CONFIG_HGC_CHECKBOX_TEXT_${i}"
        GFX_CHECKBOX_STATE = "CONFIG_HGC_CHECKBOX_STATE_${i}"
        GFX_CHECKBOX_ALIGNMENT = "CONFIG_HGC_CHECKBOX_ALIGNMENT_${i}"
        GFX_CHECKBOX_SCHEME = "CONFIG_HGC_CHECKBOX_SCHEME_${i}"
        />
		
</#list>
/*** Checkbox IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_CHECKBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_CHECKBOX_ID_DEF ID="CONFIG_HGC_CHECKBOX_ID_${i}" VALUE="${300+i}"/>
	
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_RADIOBUTTONS = true>
/*** GFX GOL Radio Button Definitions ***/
<#assign x=CONFIG_GFX_HGC_NUM_RADIOBUTTONS>
<#list 0..x-1 as i>
    <@GFX_HGC_RADIOBUTTON_DEF
        INDEX = "${i}"
        GFX_RADIOBUTTON_LEFT = "CONFIG_HGC_RADIOBUTTON_LEFT_${i}"
        GFX_RADIOBUTTON_TOP = "CONFIG_HGC_RADIOBUTTON_TOP_${i}"
        GFX_RADIOBUTTON_RIGHT = "CONFIG_HGC_RADIOBUTTON_RIGHT_${i}"
        GFX_RADIOBUTTON_BOTTOM = "CONFIG_HGC_RADIOBUTTON_BOTTOM_${i}"
        GFX_RADIOBUTTON_TEXT = "CONFIG_HGC_RADIOBUTTON_TEXT_${i}"
        GFX_RADIOBUTTON_STATE = "CONFIG_HGC_RADIOBUTTON_STATE_${i}"
        GFX_RADIOBUTTON_ALIGNMENT = "CONFIG_HGC_RADIOBUTTON_ALIGNMENT_${i}"
        GFX_RADIOBUTTON_SCHEME = "CONFIG_HGC_RADIOBUTTON_SCHEME_${i}"
        GFX_RADIOBUTTON_GROUPNO = "CONFIG_HGC_RADIOBUTTON_GROUPNO_${i}"
        GFX_RADIOBUTTON_NUM_GROUPS_ON_SCREEN = "CONFIG_HGC_RADIOBUTTON_NUM_GROUPS_ON_SCREEN_${i}"
        />
		
</#list>
/*** Radio Button IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_RADIOBUTTONS>
<#list 0..x-1 as i>
    <@GFX_HGC_RADIOBUTTON_ID_DEF ID="CONFIG_HGC_RADIOBUTTON_ID_${i}" VALUE="${400+i}"/>
	
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_SCROLLBARS = true>
/*** GFX GOL Scrollbar Definitions ***/
<#assign x=CONFIG_GFX_HGC_NUM_SCROLLBARS>
<#list 0..x-1 as i>
    <@GFX_HGC_SCROLLBAR_DEF
        INDEX = "${i}"
        GFX_SCROLLBAR_LEFT = "CONFIG_HGC_SCROLLBAR_LEFT_${i}"
        GFX_SCROLLBAR_TOP = "CONFIG_HGC_SCROLLBAR_TOP_${i}"
        GFX_SCROLLBAR_RIGHT = "CONFIG_HGC_SCROLLBAR_RIGHT_${i}"
        GFX_SCROLLBAR_BOTTOM = "CONFIG_HGC_SCROLLBAR_BOTTOM_${i}"
		GFX_SCROLLBAR_STATE = "CONFIG_HGC_SCROLLBAR_STATE_${i}"
        GFX_SCROLLBAR_RANGE = "CONFIG_HGC_SCROLLBAR_RANGE_${i}"
		GFX_SCROLLBAR_PAGE = "CONFIG_HGC_SCROLLBAR_PAGE_${i}"
		GFX_SCROLLBAR_POS = "CONFIG_HGC_SCROLLBAR_POS_${i}"
        GFX_SCROLLBAR_SCHEME = "CONFIG_HGC_SCROLLBAR_SCHEME_${i}"
        />
		
</#list>
/*** Scrollbar IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_SCROLLBARS>
<#list 0..x-1 as i>
    <@GFX_HGC_SCROLLBAR_ID_DEF ID="CONFIG_HGC_SCROLLBAR_ID_${i}" VALUE="${500+i}"/>
	
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_EDITBOXES = true>
/*** GFX GOL Edit box Definitions ***/
<#assign x=CONFIG_GFX_HGC_NUM_EDITBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_EDITBOX_DEF
        INDEX = "${i}"
        GFX_EDITBOX_LEFT = "CONFIG_HGC_EDITBOX_LEFT_${i}"
        GFX_EDITBOX_TOP = "CONFIG_HGC_EDITBOX_TOP_${i}"
        GFX_EDITBOX_RIGHT = "CONFIG_HGC_EDITBOX_RIGHT_${i}"
        GFX_EDITBOX_BOTTOM = "CONFIG_HGC_EDITBOX_BOTTOM_${i}"
		GFX_EDITBOX_STATE = "CONFIG_HGC_EDITBOX_STATE_${i}"
        GFX_EDITBOX_TEXT = "CONFIG_HGC_EDITBOX_TEXT_${i}"
        GFX_EDITBOX_NOOFCHARS = "CONFIG_HGC_EDITBOX_NOOFCHARS_${i}"
        GFX_EDITBOX_ALIGNMENT = "CONFIG_HGC_EDITBOX_ALIGNMENT_${i}"
        GFX_EDITBOX_SCHEME = "CONFIG_HGC_EDITBOX_SCHEME_${i}"
        />
		
</#list>
/*** Edit Box IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_EDITBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_EDITBOX_ID_DEF ID="CONFIG_HGC_EDITBOX_ID_${i}" VALUE="${600+i}"/>
	
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_LISTBOXES = true>
/*** GFX GOL List box Definitions ***/
<#assign x=CONFIG_GFX_HGC_NUM_LISTBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_LISTBOX_DEF
        INDEX = "${i}"
        GFX_LISTBOX_LEFT = "CONFIG_HGC_LISTBOX_LEFT_${i}"
        GFX_LISTBOX_TOP = "CONFIG_HGC_LISTBOX_TOP_${i}"
        GFX_LISTBOX_RIGHT = "CONFIG_HGC_LISTBOX_RIGHT_${i}"
        GFX_LISTBOX_BOTTOM = "CONFIG_HGC_LISTBOX_BOTTOM_${i}"
		GFX_LISTBOX_STATE = "CONFIG_HGC_LISTBOX_STATE_${i}"
        GFX_LISTBOX_SCHEME = "CONFIG_HGC_LISTBOX_SCHEME_${i}"
		GFX_LISTBOX_ALIGNMENT = "CONFIG_HGC_LISTBOX_ALIGNMENT_${i}"
		GFX_LISTBOX_ITEM_COUNT = "CONFIG_HGC_LISTBOX_ITEM_COUNT_${i}"
        />
		
</#list>
/*** List Box IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_LISTBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_LISTBOX_ID_DEF ID="CONFIG_HGC_LISTBOX_ID_${i}" VALUE="${6000+i}"/>
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_GROUPBOXES = true>
/*** GFX GOL Group box Definitions ***/
<#assign x=CONFIG_GFX_HGC_NUM_GROUPBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_GROUPBOX_DEF
        INDEX = "${i}"
        GFX_GROUPBOX_LEFT = "CONFIG_HGC_GROUPBOX_LEFT_${i}"
        GFX_GROUPBOX_TOP = "CONFIG_HGC_GROUPBOX_TOP_${i}"
        GFX_GROUPBOX_RIGHT = "CONFIG_HGC_GROUPBOX_RIGHT_${i}"
        GFX_GROUPBOX_BOTTOM = "CONFIG_HGC_GROUPBOX_BOTTOM_${i}"
		GFX_GROUPBOX_STATE = "CONFIG_HGC_GROUPBOX_STATE_${i}"
        GFX_GROUPBOX_SCHEME = "CONFIG_HGC_GROUPBOX_SCHEME_${i}"
		GFX_GROUPBOX_ALIGNMENT = "CONFIG_HGC_GROUPBOX_ALIGNMENT_${i}"
        />
		
</#list>
/*** Group Box IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_GROUPBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_GROUPBOX_ID_DEF ID="CONFIG_HGC_GROUPBOX_ID_${i}" VALUE="${7000+i}"/>
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_STATICTEXTS = true>
/*** GFX GOL Button Definitions ***/
<#assign x=CONFIG_GFX_HGC_NUM_STATICTEXTS>
<#list 0..x-1 as i>
    <@GFX_HGC_STATICTEXT_DEF
        INDEX = "${i}"
        GFX_STATICTEXT_LEFT = "CONFIG_HGC_STATICTEXT_LEFT_${i}"
        GFX_STATICTEXT_TOP = "CONFIG_HGC_STATICTEXT_TOP_${i}"
        GFX_STATICTEXT_RIGHT = "CONFIG_HGC_STATICTEXT_RIGHT_${i}"
        GFX_STATICTEXT_BOTTOM = "CONFIG_HGC_STATICTEXT_BOTTOM_${i}"
		GFX_STATICTEXT_STATE = "CONFIG_HGC_STATICTEXT_STATE_${i}"
		GFX_STATICTEXT_TEXT = "CONFIG_HGC_STATICTEXT_TEXT_${i}"        
        GFX_STATICTEXT_ALIGNMENT = "CONFIG_HGC_STATICTEXT_ALIGNMENT_${i}"
        GFX_STATICTEXT_SCHEME = "CONFIG_HGC_STATICTEXT_SCHEME_${i}"
        />
		
</#list>
/*** static text IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_STATICTEXTS>
<#list 0..x-1 as i>
    <@GFX_HGC_STATICTEXT_ID_DEF ID="CONFIG_HGC_STATICTEXT_ID_${i}" VALUE="${700+i}"/>
	
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_TEXTENTRYS = true>
/*** GFX GOL Text Entry Definitions ***/
<#assign x=CONFIG_GFX_HGC_NUM_TEXTENTRYS>
<#list 0..x-1 as i>
    <@GFX_HGC_TEXTENTRY_DEF
        INDEX = "${i}"
        GFX_TEXTENTRY_LEFT = "CONFIG_HGC_TEXTENTRY_LEFT_${i}"
        GFX_TEXTENTRY_TOP = "CONFIG_HGC_TEXTENTRY_TOP_${i}"
        GFX_TEXTENTRY_RIGHT = "CONFIG_HGC_TEXTENTRY_RIGHT_${i}"
        GFX_TEXTENTRY_BOTTOM = "CONFIG_HGC_TEXTENTRY_BOTTOM_${i}"
		GFX_TEXTENTRY_STATE = "CONFIG_HGC_TEXTENTRY_STATE_${i}"
        GFX_TEXTENTRY_SCHEME = "CONFIG_HGC_TEXTENTRY_SCHEME_${i}"
		GFX_TEXTENTRY_BUFFERSIZE = "CONFIG_HGC_TEXTENTRY_BUFFERSIZE_${i}"
		GFX_TEXTENTRY_FONT_ID = "CONFIG_HGC_TEXTENTRY_FONT_${i}"
        GFX_TEXTENTRY_ALIGNMENT = "CONFIG_HGC_TEXTENTRY_ALIGNMENT_${i}"
		GFX_TEXTENTRY_ROW_COUNT = "CONFIG_HGC_TEXTENTRY_ROWCOUNT_${i}"
		GFX_TEXTENTRY_COLUMN_COUNT = "CONFIG_HGC_TEXTENTRY_COLCOUNT_${i}"
        />
		
</#list>
/*** Text Entry IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_TEXTENTRYS>
<#list 0..x-1 as i>
    <@GFX_HGC_TEXTENTRY_ID_DEF ID="CONFIG_HGC_TEXTENTRY_ID_${i}" VALUE="${10000+i}"/>
</#list>

</#if>
<#if CONFIG_GFX_HGC_HAS_WINDOWS = true>
/*** GFX GOL windows Definitions ***/
<#assign x=CONFIG_GFX_HGC_NUM_WINDOWS>
<#list 0..x-1 as i>
    <@GFX_HGC_WINDOW_DEF
        INDEX = "${i}"
        GFX_WINDOW_LEFT = "CONFIG_HGC_WINDOW_LEFT_${i}"
        GFX_WINDOW_TOP = "CONFIG_HGC_WINDOW_TOP_${i}"
        GFX_WINDOW_RIGHT = "CONFIG_HGC_WINDOW_RIGHT_${i}"
        GFX_WINDOW_BOTTOM = "CONFIG_HGC_WINDOW_BOTTOM_${i}"
		GFX_WINDOW_STATE = "CONFIG_HGC_WINDOW_STATE_${i}"
		GFX_WINDOW_IMAGE = "CONFIG_HGC_WINDOW_IMAGE_${i}"
		GFX_WINDOW_TEXT = "CONFIG_HGC_WINDOW_TEXT_${i}"  
        GFX_WINDOW_ALIGNMENT = "CONFIG_HGC_WINDOW_ALIGNMENT_${i}"
        GFX_WINDOW_SCHEME = "CONFIG_HGC_WINDOW_SCHEME_${i}"
        />
		
</#list>
/*** Window IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_WINDOWS>
<#list 0..x-1 as i>
    <@GFX_HGC_WINDOW_ID_DEF ID="CONFIG_HGC_WINDOW_ID_${i}" VALUE="${975+i}"/>
	
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_PICTURES = true>
/*** GFX GOL windows Definitions ***/
<#assign x=CONFIG_GFX_HGC_NUM_PICTURES>
<#list 0..x-1 as i>
    <@GFX_HGC_PICTURE_DEF
        INDEX = "${i}"
        GFX_PICTURE_LEFT = "CONFIG_HGC_PICTURE_LEFT_${i}"
        GFX_PICTURE_TOP = "CONFIG_HGC_PICTURE_TOP_${i}"
        GFX_PICTURE_RIGHT = "CONFIG_HGC_PICTURE_RIGHT_${i}"
        GFX_PICTURE_BOTTOM = "CONFIG_HGC_PICTURE_BOTTOM_${i}"
		GFX_PICTURE_STATE = "CONFIG_HGC_PICTURE_STATE_${i}"
        GFX_PICTURE_SCALE = "CONFIG_HGC_PICTURE_SCALE_${i}"
        GFX_PICTURE_SCHEME = "CONFIG_HGC_PICTURE_SCHEME_${i}"
        />
		
</#list>
/*** Pictures IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_PICTURES>
<#list 0..x-1 as i>
    <@GFX_HGC_PICTURE_ID_DEF ID="CONFIG_HGC_PICTURE_ID_${i}" VALUE="${800+i}"/>
	
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_PROGRESSBARS = true>
/*** GFX GOL Progressbar Definitions ***/
<#assign x=CONFIG_GFX_HGC_NUM_PROGRESSBARS>
<#list 0..x-1 as i>
    <@GFX_HGC_PROGRESSBAR_DEF
        INDEX = "${i}"
        GFX_PROGRESSBAR_LEFT = "CONFIG_HGC_PROGRESSBAR_LEFT_${i}"
        GFX_PROGRESSBAR_TOP = "CONFIG_HGC_PROGRESSBAR_TOP_${i}"
        GFX_PROGRESSBAR_RIGHT = "CONFIG_HGC_PROGRESSBAR_RIGHT_${i}"
        GFX_PROGRESSBAR_BOTTOM = "CONFIG_HGC_PROGRESSBAR_BOTTOM_${i}"
		GFX_PROGRESSBAR_STATE = "CONFIG_HGC_PROGRESSBAR_STATE_${i}"
        GFX_PROGRESSBAR_RANGE = "CONFIG_HGC_PROGRESSBAR_RANGE_${i}"
		GFX_PROGRESSBAR_POS = "CONFIG_HGC_PROGRESSBAR_POS_${i}"		
        GFX_PROGRESSBAR_SCHEME = "CONFIG_HGC_PROGRESSBAR_SCHEME_${i}"
        />
		
</#list>
/*** Progressbar IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_PROGRESSBARS>
<#list 0..x-1 as i>
    <@GFX_HGC_PROGRESSBAR_ID_DEF ID="CONFIG_HGC_PROGRESSBAR_ID_${i}" VALUE="${900+i}"/>
	
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_METERS = true>
/*** GFX GOL Meter Definitions ***/
<#assign x=CONFIG_GFX_HGC_NUM_METERS>
<#list 0..x-1 as i>
    <@GFX_HGC_METER_DEF
        INDEX = "${i}"
        GFX_METER_LEFT = "CONFIG_HGC_METER_LEFT_${i}"
        GFX_METER_TOP = "CONFIG_HGC_METER_TOP_${i}"
        GFX_METER_RIGHT = "CONFIG_HGC_METER_RIGHT_${i}"
        GFX_METER_BOTTOM = "CONFIG_HGC_METER_BOTTOM_${i}"
		GFX_METER_STATE = "CONFIG_HGC_METER_STATE_${i}"
        GFX_METER_VALUE = "CONFIG_HGC_METER_VALUE_${i}"
		GFX_METER_MINVALUE = "CONFIG_HGC_METER_MIN_VALUE_${i}"		
		GFX_METER_MAXVALUE = "CONFIG_HGC_METER_MAX_VALUE_${i}"
        GFX_METER_TYPE = "CONFIG_HGC_METER_TYPE_${i}"
        GFX_METER_SCHEME = "CONFIG_HGC_METER_SCHEME_${i}"

        GFX_METER_COLOR1_RED = "CONFIG_HGC_METER_COLOR_1_RED_${i}"
        GFX_METER_COLOR1_GREEN = "CONFIG_HGC_METER_COLOR_1_GREEN_${i}"
        GFX_METER_COLOR1_BLUE = "CONFIG_HGC_METER_COLOR_1_BLUE_${i}"

        GFX_METER_COLOR2_RED = "CONFIG_HGC_METER_COLOR_2_RED_${i}"
        GFX_METER_COLOR2_GREEN = "CONFIG_HGC_METER_COLOR_2_GREEN_${i}"
        GFX_METER_COLOR2_BLUE = "CONFIG_HGC_METER_COLOR_2_BLUE_${i}"

        GFX_METER_COLOR3_RED = "CONFIG_HGC_METER_COLOR_3_RED_${i}"
        GFX_METER_COLOR3_GREEN = "CONFIG_HGC_METER_COLOR_3_GREEN_${i}"
        GFX_METER_COLOR3_BLUE = "CONFIG_HGC_METER_COLOR_3_BLUE_${i}"

        GFX_METER_COLOR4_RED = "CONFIG_HGC_METER_COLOR_4_RED_${i}"
        GFX_METER_COLOR4_GREEN = "CONFIG_HGC_METER_COLOR_4_GREEN_${i}"
        GFX_METER_COLOR4_BLUE = "CONFIG_HGC_METER_COLOR_4_BLUE_${i}"

        GFX_METER_COLOR5_RED = "CONFIG_HGC_METER_COLOR_5_RED_${i}"
        GFX_METER_COLOR5_GREEN = "CONFIG_HGC_METER_COLOR_5_GREEN_${i}"
        GFX_METER_COLOR5_BLUE = "CONFIG_HGC_METER_COLOR_5_BLUE_${i}"

        GFX_METER_COLOR6_RED = "CONFIG_HGC_METER_COLOR_6_RED_${i}"
        GFX_METER_COLOR6_GREEN = "CONFIG_HGC_METER_COLOR_6_GREEN_${i}"
        GFX_METER_COLOR6_BLUE = "CONFIG_HGC_METER_COLOR_6_BLUE_${i}"
        />
		
</#list>
/*** Meter IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_METERS>
<#list 0..x-1 as i>
    <@GFX_HGC_METER_ID_DEF ID="CONFIG_HGC_METER_ID_${i}" VALUE="${1200+i}"/>
	
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_LINES = true>
/*** Line IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_LINES>
<#list 0..x-1 as i>
    <@GFX_HGC_LINE_ID_DEF ID="CONFIG_GFX_HGC_LINE_ID_${i}" VALUE="${950+i}"/>
	
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_RECTANGLES = true>
/*** Rectangle IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_RECTANGLES>
<#list 0..x-1 as i>
    <@GFX_HGC_RECTANGLE_ID_DEF ID="CONFIG_GFX_HGC_RECTANGLE_ID_${i}" VALUE="${1000+i}"/>
	
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_CIRCLES = true>
/*** Circle IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_CIRCLES>
<#list 0..x-1 as i>
    <@GFX_HGC_CIRCLE_ID_DEF ID="CONFIG_GFX_HGC_CIRCLE_ID_${i}" VALUE="${1050+i}"/>
	
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_IMAGES = true>
/*** Image IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_IMAGES>
<#list 0..x-1 as i>
    <@GFX_HGC_IMAGE_ID_DEF ID="CONFIG_GFX_HGC_IMAGE_ID_${i}" VALUE="${1100+i}"/>
	
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_TEXTS = true>
/*** Text IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_TEXTS>
<#list 0..x-1 as i>
    <@GFX_HGC_TEXT_ID_DEF ID="CONFIG_GFX_HGC_TEXT_ID_${i}" VALUE="${1150+i}"/>
	
</#list>
</#if>
/*** Screen IDs ***/
<#assign x=CONFIG_GFX_HGC_NUM_SCREENS>
<#list 0..x-1 as i>
    <@GFX_HGC_SCREEN_ID_DEF SCR_ID="CONFIG_GFX_HGC_SCREEN_ID_${i}" VALUE="${i}"/>
	
</#list>


// *****************************************************************************
/* MPLAB Harmony Graphics Composer Objects

  Summary:
    Structure holding the graphics object handles

  Description:
    This structure contains the object handles for all graphics objects 
    generated by the Harmony Graphics Composer

  Remarks:
*/

typedef struct HGC_OBJECTS
{
    HGC_SCREEN_STATES screenState;      // current state of screen state machine
    HGC_SCREEN_STATES prevRefreshState; // previous state of screen state machine

    /*** GOL Objects References ***/
<#if CONFIG_GFX_HGC_HAS_BUTTONS = true>
<#assign x=CONFIG_GFX_HGC_NUM_BUTTONS> 
<#list 0..x-1 as i>
    <@GFX_HGC_BUTTON_EXTERN_DEF ID = "CONFIG_HGC_BTN_ID_${i}"/>
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_DGTL_MTRS = true>
<#assign x=CONFIG_GFX_HGC_NUM_DGTL_MTRS>
<#list 0..x-1 as i>
    <@GFX_HGC_DGTL_MTR_EXTERN_DEF ID="CONFIG_HGC_DGTL_MTR_ID_${i}"/>
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_CHECKBOXES = true>
<#assign x=CONFIG_GFX_HGC_NUM_CHECKBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_CHECKBOX_EXTERN_DEF ID="CONFIG_HGC_CHECKBOX_ID_${i}"/>
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_RADIOBUTTONS = true>
<#assign x=CONFIG_GFX_HGC_NUM_RADIOBUTTONS>
<#list 0..x-1 as i>
    <@GFX_HGC_RADIOBUTTON_EXTERN_DEF ID="CONFIG_HGC_RADIOBUTTON_ID_${i}"/>
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_SCROLLBARS = true>
<#assign x=CONFIG_GFX_HGC_NUM_SCROLLBARS>
<#list 0..x-1 as i>
    <@GFX_HGC_SCROLLBAR_EXTERN_DEF ID="CONFIG_HGC_SCROLLBAR_ID_${i}"/>
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_EDITBOXES = true>
<#assign x=CONFIG_GFX_HGC_NUM_EDITBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_EDITBOX_EXTERN_DEF ID="CONFIG_HGC_EDITBOX_ID_${i}"/>
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_LISTBOXES = true>
    GFX_GOL_LISTITEM* pListBoxItem;
<#assign x=CONFIG_GFX_HGC_NUM_LISTBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_LISTBOX_EXTERN_DEF ID="CONFIG_HGC_LISTBOX_ID_${i}"/>
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_GROUPBOXES = true>
<#assign x=CONFIG_GFX_HGC_NUM_GROUPBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_GROUPBOX_EXTERN_DEF ID="CONFIG_HGC_GROUPBOX_ID_${i}"/>
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_STATICTEXTS = true>
<#assign x=CONFIG_GFX_HGC_NUM_STATICTEXTS>
<#list 0..x-1 as i>
    <@GFX_HGC_STATICTEXT_EXTERN_DEF ID="CONFIG_HGC_STATICTEXT_ID_${i}"/>
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_TEXTENTRYS = true>
<#assign x=CONFIG_GFX_HGC_NUM_TEXTENTRYS>
<#list 0..x-1 as i>
    <@GFX_HGC_TEXTENTRY_EXTERN_DEF ID="CONFIG_HGC_TEXTENTRY_ID_${i}"/>
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_WINDOWS = true>
<#assign x=CONFIG_GFX_HGC_NUM_WINDOWS>
<#list 0..x-1 as i>
    <@GFX_HGC_WINDOW_EXTERN_DEF ID="CONFIG_HGC_WINDOW_ID_${i}"/>
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_PICTURES = true>
<#assign x=CONFIG_GFX_HGC_NUM_PICTURES>
<#list 0..x-1 as i>
    <@GFX_HGC_PICTURE_EXTERN_DEF ID="CONFIG_HGC_PICTURE_ID_${i}"/>
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_PROGRESSBARS = true>
<#assign x=CONFIG_GFX_HGC_NUM_PROGRESSBARS>
<#list 0..x-1 as i>
    <@GFX_HGC_PROGRESSBAR_EXTERN_DEF ID="CONFIG_HGC_PROGRESSBAR_ID_${i}"/>
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_METERS = true>
<#assign x=CONFIG_GFX_HGC_NUM_METERS>
<#list 0..x-1 as i>
    <@GFX_HGC_METER_EXTERN_DEF ID="CONFIG_HGC_METER_ID_${i}"/>
</#list>
</#if>
} HGC_OBJECTS;

extern HGC_OBJECTS hgcObj;

<#if CONFIG_USE_SYS_MSG = true>
/******************************************************************************
  Function:
    void GFX_HGC_TouchMessageCallback ( SYS_MSG_OBJECT *pMsg )

  Summary:
    This function sets up the Message System Service to route touch callbacks
    to the GOL message system  
 */
void GFX_HGC_TouchMessageCallback ( SYS_MSG_OBJECT *pMsg );


</#if>
/******************************************************************************
  Function:
    void GFX_HGC_Initialize ( void )

  Summary:
    This function initializes the HGC state machine.  
 */
void GFX_HGC_Initialize ( void );


/******************************************************************************
  Function:
    void GFX_HGC_Setup ( void )

  Summary:
    This function sets up the GOL message callback and draw callbacks.  
 */
void GFX_HGC_Setup ( void );


/******************************************************************************
  Function:
    HGC_SCREEN_STATES GFX_HGC_GetScreenState ( void )

  Remarks:
    This function returns the screen state
 */
HGC_SCREEN_STATES GFX_HGC_GetScreenState ( void );


/******************************************************************************
  Function:
    void GFX_HGC_SetScreenState ( HGC_SCREEN_STATES newState )

  Remarks:
    This function sets the screen state machine to a new state
 */
void GFX_HGC_SetScreenState ( HGC_SCREEN_STATES newState );


/******************************************************************************
  Function:
    void GFX_HGC_Tasks (SYS_MODULE_OBJ gfxObject);

  Summary:
    This function is called in SYS_Tasks.  The intent wait until the GFX library
    is initialized before supplying items to draw
*/
void GFX_HGC_Tasks  (SYS_MODULE_OBJ gfxObject);


<#if CONFIG_GFX_HGC_HAS_SCHEMES = true>
/******************************************************************************
  Function:
    void GFX_HGC_SchemeCreate ( void )

  Summary:
    Allocates memory for a new scheme
 */
GFX_GOL_OBJ_SCHEME *GFX_HGC_SchemeCreate(void);


/******************************************************************************
  Function:
    void GFX_HGC_InitializeSchemes ( void )

  Summary:
    Initializes all HGC-specified schemes
 */
void GFX_HGC_InitializeSchemes( void );


</#if>
<#if CONFIG_GFX_HGC_USE_GOL = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_MESSAGECallback(uint16_t objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)

  Input: 
    objMsg - translated message for the object,
    pObj - pointer to the object,
    pMsg - pointer to the non-translated, raw GOL message

  Output: 
    If the function returns non-zero the message will be processed by default

  Remarks: 
    GFX_GOL_MESSAGECallback() function calls it each time the valid message for the GOL object is received.
 */
bool GFX_HGC_MessageCallback(GFX_GOL_TRANSLATED_ACTION objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg);


</#if>
<#if CONFIG_GFX_HGC_USE_GOL = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_DrawCallback( void )

  Output: 
    If the function returns non-zero the draw control will be passed to GOL

  Remarks: 
    GFX_GOL_Draw() function calls it each time when GOL objects drawing is 
    completed. HGC-specified draw data is grouped by screens states. It takes 
    two states to complete the drawing of each screen.  GFX GOL objects are drawn
    first and then GFX Primitives are drawn next to ensure primitives are not
    covered by GOL objects.
 */
bool GFX_HGC_DrawCallback( void );
<#else>
/******************************************************************************
  Function: 
    void GFX_HGC_DrawScreenTask( void )

  Remarks: 
    Task loop to drive the HGC generated screen state machine for HGC design
    that has GFX_Primitives only
 */
void GFX_HGC_DrawScreenTask( void );


</#if>
<#if CONFIG_GFX_HGC_USE_GOL = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_DrawScreen_GOL( uint8_t  screenId )

  Output: 
    Returns true if a screenId matches an existing screen identifier

  Remarks: 
    HGC-specified GFX GOL objects are drawn here, grouped by screen.
    The draw order is reverse Z-ordered.
 */
bool GFX_HGC_DrawScreen_GOL(uint8_t screenId);


</#if>
/******************************************************************************
  Function: 
    bool GFX_HGC_DrawScreen_Primitives( uint8_t  screenId )

  Output:
    Returns true if a screenId matches an existing screen identifier

  Remarks: 
    HGC-specified GFX Primitives are drawn here, grouped by screen.
    GFX Primitives are drawn after GFX GOL Objects to make sure GFX GOL Objects
    do not cover GFX Primitives
 */
bool GFX_HGC_DrawScreen_Primitives(uint8_t screenId);


/******************************************************************************
  Function: 
    void GFX_HGC_SetupScreen( uint8_t  screenId )

  Remarks: 
    Clears current screen and starts a fresh screen with its background color
 */
void GFX_HGC_SetupScreen(uint8_t screenId);


/******************************************************************************
  Function: 
    bool GFX_HGC_ChangeScreen( uint8_t  screenId )

  Output: 
    Returns true if a screenId matches an existing screen identifier

  Remarks: 
    Can be called to initiate GFX Library to draw a new screen
 */
bool GFX_HGC_ChangeScreen(uint8_t screenId);


/******************************************************************************
  Function: 
    bool GFX_HGC_DrawItem(int itemId)

  Output:
    Returns true if a itemId matches an existing item identifier

  Remarks: 
    Every item specified in every screen in HGC is listed in this function
 */
bool GFX_HGC_DrawItem(int itemId);


<#if CONFIG_GFX_HGC_HAS_BUTTONS = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_MsgButtons(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)

  Output:
    Returns true if a Object ID matches an existing item identifier

  Remarks: 
    Handles GFX GOL Button events
 */
bool GFX_HGC_MsgButtons(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg);

</#if>
<#if CONFIG_GFX_HGC_HAS_DGTL_MTRS = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_MsgDigitalMeters(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)

  Output:
    Returns true if a Object ID matches an existing item identifier

  Remarks: 
    Handles GFX GOL Digital Meter events
 */
bool GFX_HGC_MsgDigitalMeters(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg);

</#if>
<#if CONFIG_GFX_HGC_HAS_CHECKBOXES = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_MsgCheckBoxes(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)

  Output:
    Returns true if a Object ID matches an existing item identifier

  Remarks: 
    Handles GFX GOL Check Boxes events
 */
bool GFX_HGC_MsgCheckBoxes(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg);

</#if>
<#if CONFIG_GFX_HGC_HAS_RADIOBUTTONS = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_MsgRadioButtons(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)

  Output:
    Returns true if a Object ID matches an existing item identifier

  Remarks: 
    Handles GFX GOL Radio Button events
 */
bool GFX_HGC_MsgRadioButtons(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg);

</#if>
<#if CONFIG_GFX_HGC_HAS_SCROLLBARS = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_MsgScrollBars(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)

  Output:
    Returns true if a Object ID matches an existing item identifier

  Remarks: 
    Handles GFX GOL Scroll Bar events
 */
bool GFX_HGC_MsgScrollBars(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg);

</#if>
<#if CONFIG_GFX_HGC_HAS_EDITBOXES = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_MsgEditBoxes(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)

  Output:
    Returns true if a Object ID matches an existing item identifier

  Remarks: 
    Handles GFX GOL Edit Boxes events
 */
bool GFX_HGC_MsgEditBoxes(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg);

</#if>
<#if CONFIG_GFX_HGC_HAS_LISTBOXES = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_MsgListBoxes(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)

  Output:
    Returns true if a Object ID matches an existing item identifier

  Remarks: 
    Handles GFX GOL List Boxes events
 */
bool GFX_HGC_MsgListBoxes(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg);

</#if>
<#if CONFIG_GFX_HGC_HAS_PICTURES = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_MsgPictures(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)

  Output:
    Returns true if a Object ID matches an existing item identifier

  Remarks: 
    Handles GFX GOL Picture Control events
 */
bool GFX_HGC_MsgPictures(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg);

</#if>
<#if CONFIG_GFX_HGC_HAS_STATICTEXTS = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_MsgStaticTexts(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)

  Output:
    Returns true if a Object ID matches an existing item identifier

  Remarks: 
    Handles GFX GOL Static Text events
 */
bool GFX_HGC_MsgStaticTexts(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg);

</#if>
<#if CONFIG_GFX_HGC_HAS_WINDOWS = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_MsgWindows(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)

  Output:
    Returns true if a Object ID matches an existing item identifier

  Remarks: 
    Handles GFX GOL Window events
 */
bool GFX_HGC_MsgWindows(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg);

</#if>
<#if CONFIG_GFX_HGC_HAS_PROGRESSBARS = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_MsgProgressBars(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)

  Output:
    Returns true if a Object ID matches an existing item identifier

  Remarks: 
    Handles GFX GOL Progress Bar events
 */
bool GFX_HGC_MsgProgressBars(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg);

</#if>
<#if CONFIG_GFX_HGC_HAS_TEXTENTRYS = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_MsgTextEntrys(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)

  Output:
    Returns true if a Object ID matches an existing item identifier

  Remarks: 
    Handles GFX GOL Text Entry events
 */
bool GFX_HGC_MsgTextEntrys(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg);

</#if>

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // _GFX_HGC_DEFINITIONS_H
/*******************************************************************************
 End of File
*/
