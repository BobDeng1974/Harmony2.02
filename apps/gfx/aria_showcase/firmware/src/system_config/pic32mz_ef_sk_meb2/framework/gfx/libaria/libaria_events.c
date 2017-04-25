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

// ButtonWidget12 - ReleasedEvent
void ButtonWidget12_ReleasedEvent(laButtonWidget* btn)
{
    // SwitchToFirst - Show Screen - FirstScreen
    laContext_SetActiveScreen(FirstScreen_ID);
}

// RadioButtonWidget1 - CheckedEvent
void RadioButtonWidget1_CheckedEvent(laRadioButtonWidget* cbox)
{
    // SwitchToEnglish
    laContext_SetStringLanguage(language_English);
    laContext_RedrawAll();
}

// RadioButtonWidget2 - CheckedEvent
void RadioButtonWidget2_CheckedEvent(laRadioButtonWidget* cbox)
{
    // SwitchToChinese
    laContext_SetStringLanguage(language_Chinese);
    laContext_RedrawAll();
}

// ButtonWidget1 - ReleasedEvent
void ButtonWidget1_ReleasedEvent(laButtonWidget* btn)
{
    // SwitchScreen - Show Screen - SecondScreen
    laContext_SetActiveScreen(SecondScreen_ID);
}

// ButtonWidget7 - ReleasedEvent
void ButtonWidget7_ReleasedEvent(laButtonWidget* btn)
{
    // SwitchToMainMenu - Show Screen - MainMenu
    laContext_SetActiveScreen(MainMenu_ID);
}

// TouchTestWidget1 - PointAddedEvent
void TouchTestWidget1_PointAddedEvent(laTouchTestWidget* tch, GFX_Point* pnt)
{
}

// ButtonWidget2 - ReleasedEvent
void ButtonWidget2_ReleasedEvent(laButtonWidget* btn)
{
    // GoToScreen1 - Show Screen - FirstScreen
    laContext_SetActiveScreen(FirstScreen_ID);
}

// ButtonWidget3 - ReleasedEvent
void ButtonWidget3_ReleasedEvent(laButtonWidget* btn)
{
    // GoToScreen3 - Show Screen - ThirdScreen
    laContext_SetActiveScreen(ThirdScreen_ID);
}

// ButtonWidget5 - ReleasedEvent
void ButtonWidget5_ReleasedEvent(laButtonWidget* btn)
{
    // SwitchToPrevious - Show Screen - SecondScreen
    laContext_SetActiveScreen(SecondScreen_ID);
}

// ButtonWidget6 - ReleasedEvent
void ButtonWidget6_ReleasedEvent(laButtonWidget* btn)
{
    // SwitchToFourth - Show Screen - FourthScreen
    laContext_SetActiveScreen(FourthScreen_ID);
}

// SliderWidget1 - ValueChangedEvent
void SliderWidget1_ValueChangedEvent(laSliderWidget* sld)
{
    // ChangeValue
    laWidget_SetAlphaAmount((laWidget*)ImageWidget2, 255 - laSliderWidget_GetSliderValue(sld));
    laWidget_SetAlphaAmount((laWidget*)ImageWidget1, laSliderWidget_GetSliderValue(sld));
}

// ButtonWidget4 - ReleasedEvent
void ButtonWidget4_ReleasedEvent(laButtonWidget* btn)
{
    // SwitchToThird - Show Screen - ThirdScreen
    laContext_SetActiveScreen(ThirdScreen_ID);
}

// ButtonWidget8 - ReleasedEvent
void ButtonWidget8_ReleasedEvent(laButtonWidget* btn)
{
    // SwitchToFifth - Show Screen - FifthScreen
    laContext_SetActiveScreen(FifthScreen_ID);
}

// ButtonWidget10 - ReleasedEvent
void ButtonWidget10_ReleasedEvent(laButtonWidget* btn)
{
    // CycleImage
    static int imageIndex = 0;
    imageIndex++;
    if (imageIndex >= laImageSequenceWidget_GetImageCount((laImageSequenceWidget*)ImageSequenceWidget1))
    imageIndex = 0;
    laImageSequenceWidget_ShowImage((laImageSequenceWidget*)ImageSequenceWidget1, imageIndex);
}

// ButtonWidget9 - ReleasedEvent
void ButtonWidget9_ReleasedEvent(laButtonWidget* btn)
{
    // SwitchToFourth - Show Screen - FourthScreen
    laContext_SetActiveScreen(FourthScreen_ID);
}

// ButtonWidget11 - ReleasedEvent
void ButtonWidget11_ReleasedEvent(laButtonWidget* btn)
{
    // SwitchToMainMenu - Show Screen - MainMenu
    laContext_SetActiveScreen(MainMenu_ID);
}





