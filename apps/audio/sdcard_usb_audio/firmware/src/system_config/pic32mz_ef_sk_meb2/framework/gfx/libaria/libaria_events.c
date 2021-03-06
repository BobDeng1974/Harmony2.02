/*******************************************************************************
  MPLAB Harmony Graphics Composer Generated Implementation File

  File Name:
    libaria_events.c

  Summary:
    Build-time generated implementation from the MPLAB Harmony
    Graphics Composer.

  Description:
    Build-time generated implementation from the MPLAB Harmony
    Graphics Composer.

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

#include "gfx/libaria/libaria_events.h"
#include "app_display_task.h"

// RadioButtonSd - CheckedEvent
void RadioButtonSd_CheckedEvent(laRadioButtonWidget* cbox)
{
    // CustomAction
    laWidget_SetEnabled((laWidget *)TrackListBox, true);
    laListWidget_SetSelectionMode(TrackListBox, LA_LIST_WIDGET_SELECTION_MODE_SINGLE);
    laListWidget_SetItemSelected(TrackListBox, 0, true);
    APP_DISPLAY_StreamSourceSet(0);
    APP_DISPLAY_VolumeMuteSourceSet(0);
}

// RadioButtonUSB - CheckedEvent
void RadioButtonUSB_CheckedEvent(laRadioButtonWidget* cbox)
{
    // CustomAction
    laWidget_SetEnabled((laWidget *)TrackListBox, false);
    APP_DISPLAY_StreamSourceSet(1);
    APP_DISPLAY_VolumeMuteSourceSet(1);
}

// TrackListBox - SelectionChangedEvent
void TrackListBox_SelectionChangedEvent(laListWidget* img, uint32_t idx, laBool selected)
{
    // CustomAction
    if (true == selected) 
    {
    	APP_SDCARD_AUDIO_RandomTrackSet(idx);
    }
}

// MuteButton - PressedEvent
void MuteButton_PressedEvent(laButtonWidget* btn)
{
    // CustomAction
    APP_DISPLAY_VolumeMuteChange(1);
}

// MuteButton - ReleasedEvent
void MuteButton_ReleasedEvent(laButtonWidget* btn)
{
    // CustomAction
    APP_DISPLAY_VolumeMuteChange(0);
}

// VolumeDownButton - ReleasedEvent
void VolumeDownButton_ReleasedEvent(laButtonWidget* btn)
{
    // CustomAction
    APP_DISPLAY_VolumeMuteChange(3);
}

// VolumeUpButton - ReleasedEvent
void VolumeUpButton_ReleasedEvent(laButtonWidget* btn)
{
    // CustomAction
    APP_DISPLAY_VolumeMuteChange(2);
}





