/*******************************************************************************
  MPLAB Harmony Graphics Composer Generated Implementation File

  File Name:
    libaria_init.c

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

#include "gfx/libaria/libaria_init.h"

laScheme defaultScheme;
laScheme AlternateGradientScheme;
laScheme MainMenuGradientScheme;
laScheme TouchTestScheme;
laScheme GradientScheme;
laImageWidget* ImageWidget3;
laImageWidget* ImageWidget4;
laLabelWidget* LabelWidget1;
laLabelWidget* LabelWidget2;
laButtonWidget* ButtonWidget12;
laListWheelWidget* ListWheel1;
laGroupBoxWidget* GroupBoxWidget1;
laRadioButtonWidget* RadioButtonWidget1;
laRadioButtonWidget* RadioButtonWidget2;
laButtonWidget* ButtonWidget1;
laButtonWidget* ButtonWidget7;
laGradientWidget* GradientWidget2;
laTouchTestWidget* TouchTestWidget1;
laButtonWidget* ButtonWidget2;
laButtonWidget* ButtonWidget3;
laKeyPadWidget* KeyPadWidget1;
laTextFieldWidget* TextFieldWidget1;
laButtonWidget* ButtonWidget5;
laButtonWidget* ButtonWidget6;
laWidget* PanelWidget1;
laSliderWidget* SliderWidget1;
laWidget* PanelWidget2;
laImageWidget* ImageWidget1;
laImageWidget* ImageWidget2;
laButtonWidget* ButtonWidget4;
laButtonWidget* ButtonWidget8;
laImageSequenceWidget* ImageSequenceWidget1;
laButtonWidget* ButtonWidget10;
laButtonWidget* ButtonWidget9;
laButtonWidget* ButtonWidget11;


static void ScreenCreate_MainMenu(laScreen* screen);
static void ScreenCreate_FirstScreen(laScreen* screen);
static void ScreenCreate_SecondScreen(laScreen* screen);
static void ScreenCreate_ThirdScreen(laScreen* screen);
static void ScreenCreate_FourthScreen(laScreen* screen);
static void ScreenCreate_FifthScreen(laScreen* screen);


int32_t libaria_initialize(void)
{
    laScreen* screen;

    laScheme_Initialize(&defaultScheme, GFX_COLOR_MODE_RGB_565);
    defaultScheme.base = 0xFFFF;
    defaultScheme.highlight = 0xC67A;
    defaultScheme.highlightLight = 0xFFFF;
    defaultScheme.shadow = 0x8410;
    defaultScheme.shadowDark = 0x4208;
    defaultScheme.foreground = 0x0;
    defaultScheme.foregroundInactive = 0xD71C;
    defaultScheme.foregroundDisabled = 0x8410;
    defaultScheme.background = 0xFFFF;
    defaultScheme.backgroundInactive = 0xD71C;
    defaultScheme.backgroundDisabled = 0xC67A;
    defaultScheme.text = 0x0;
    defaultScheme.textHighlight = 0x1F;
    defaultScheme.textHighlightText = 0xFFFF;
    defaultScheme.textInactive = 0xD71C;
    defaultScheme.textDisabled = 0x8C92;

    laScheme_Initialize(&AlternateGradientScheme, GFX_COLOR_MODE_RGB_565);
    AlternateGradientScheme.base = 0xF800;
    AlternateGradientScheme.highlight = 0xC67A;
    AlternateGradientScheme.highlightLight = 0xFFFF;
    AlternateGradientScheme.shadow = 0x8410;
    AlternateGradientScheme.shadowDark = 0x4208;
    AlternateGradientScheme.foreground = 0xF800;
    AlternateGradientScheme.foregroundInactive = 0x1F;
    AlternateGradientScheme.foregroundDisabled = 0x8410;
    AlternateGradientScheme.background = 0x17;
    AlternateGradientScheme.backgroundInactive = 0xD71C;
    AlternateGradientScheme.backgroundDisabled = 0xC67A;
    AlternateGradientScheme.text = 0x0;
    AlternateGradientScheme.textHighlight = 0x1F;
    AlternateGradientScheme.textHighlightText = 0xFFFF;
    AlternateGradientScheme.textInactive = 0xD71C;
    AlternateGradientScheme.textDisabled = 0x8C92;

    laScheme_Initialize(&MainMenuGradientScheme, GFX_COLOR_MODE_RGB_565);
    MainMenuGradientScheme.base = 0xFFFF;
    MainMenuGradientScheme.highlight = 0xC67A;
    MainMenuGradientScheme.highlightLight = 0xFFFF;
    MainMenuGradientScheme.shadow = 0x8410;
    MainMenuGradientScheme.shadowDark = 0x4208;
    MainMenuGradientScheme.foreground = 0x8410;
    MainMenuGradientScheme.foregroundInactive = 0xD71C;
    MainMenuGradientScheme.foregroundDisabled = 0x8410;
    MainMenuGradientScheme.background = 0xFFFF;
    MainMenuGradientScheme.backgroundInactive = 0xD71C;
    MainMenuGradientScheme.backgroundDisabled = 0xC67A;
    MainMenuGradientScheme.text = 0x0;
    MainMenuGradientScheme.textHighlight = 0x1F;
    MainMenuGradientScheme.textHighlightText = 0xFFFF;
    MainMenuGradientScheme.textInactive = 0xD71C;
    MainMenuGradientScheme.textDisabled = 0x8C92;

    laScheme_Initialize(&TouchTestScheme, GFX_COLOR_MODE_RGB_565);
    TouchTestScheme.base = 0xFFFF;
    TouchTestScheme.highlight = 0xC67A;
    TouchTestScheme.highlightLight = 0xFFFF;
    TouchTestScheme.shadow = 0x8410;
    TouchTestScheme.shadowDark = 0x4208;
    TouchTestScheme.foreground = 0xF81F;
    TouchTestScheme.foregroundInactive = 0x7FF;
    TouchTestScheme.foregroundDisabled = 0x8410;
    TouchTestScheme.background = 0x17;
    TouchTestScheme.backgroundInactive = 0xD71C;
    TouchTestScheme.backgroundDisabled = 0xC67A;
    TouchTestScheme.text = 0x7FF;
    TouchTestScheme.textHighlight = 0xF81F;
    TouchTestScheme.textHighlightText = 0xFFFF;
    TouchTestScheme.textInactive = 0xD71C;
    TouchTestScheme.textDisabled = 0x8C92;

    laScheme_Initialize(&GradientScheme, GFX_COLOR_MODE_RGB_565);
    GradientScheme.base = 0xF800;
    GradientScheme.highlight = 0xC67A;
    GradientScheme.highlightLight = 0xFFFF;
    GradientScheme.shadow = 0x8410;
    GradientScheme.shadowDark = 0x4208;
    GradientScheme.foreground = 0x7E0;
    GradientScheme.foregroundInactive = 0xFFE0;
    GradientScheme.foregroundDisabled = 0x8410;
    GradientScheme.background = 0x17;
    GradientScheme.backgroundInactive = 0xD71C;
    GradientScheme.backgroundDisabled = 0xC67A;
    GradientScheme.text = 0x0;
    GradientScheme.textHighlight = 0x1F;
    GradientScheme.textHighlightText = 0x87FF;
    GradientScheme.textInactive = 0xD71C;
    GradientScheme.textDisabled = 0x8C92;

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_MainMenu);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_FirstScreen);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_SecondScreen);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_ThirdScreen);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_FourthScreen);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_FifthScreen);
    laContext_AddScreen(screen);

    laContext_SetStringTable(&stringTable);
    laContext_SetActiveScreen(0);

	return 0;
}

static void ScreenCreate_MainMenu(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 480, 272);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    ImageWidget3 = laImageWidget_New();
    laWidget_SetPosition((laWidget*)ImageWidget3, 10, 9);
    laWidget_SetSize((laWidget*)ImageWidget3, 233, 142);
    laWidget_SetDrawBackground((laWidget*)ImageWidget3, LA_FALSE);
    laWidget_SetBorderType((laWidget*)ImageWidget3, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(ImageWidget3, &MicrochipLogo);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)ImageWidget3);

    ImageWidget4 = laImageWidget_New();
    laWidget_SetPosition((laWidget*)ImageWidget4, 269, 0);
    laWidget_SetSize((laWidget*)ImageWidget4, 209, 150);
    laWidget_SetDrawBackground((laWidget*)ImageWidget4, LA_FALSE);
    laWidget_SetBorderType((laWidget*)ImageWidget4, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(ImageWidget4, &NewHarmonyLogo);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)ImageWidget4);

    LabelWidget1 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget1, 63, 159);
    laWidget_SetSize((laWidget*)LabelWidget1, 168, 32);
    laWidget_SetDrawBackground((laWidget*)LabelWidget1, LA_FALSE);
    laWidget_SetBorderType((laWidget*)LabelWidget1, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget1, laString_CreateFromID(string_Harmony));
    laLabelWidget_SetHAlignment(LabelWidget1, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget1);

    LabelWidget2 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget2, 221, 160);
    laWidget_SetSize((laWidget*)LabelWidget2, 190, 31);
    laWidget_SetDrawBackground((laWidget*)LabelWidget2, LA_FALSE);
    laWidget_SetBorderType((laWidget*)LabelWidget2, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget2, laString_CreateFromID(string_Title));
    laLabelWidget_SetHAlignment(LabelWidget2, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget2);

    ButtonWidget12 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget12, 201, 200);
    laWidget_SetSize((laWidget*)ButtonWidget12, 60, 60);
    laWidget_SetLocalRedraw((laWidget*)ButtonWidget12, LA_TRUE);
    laWidget_SetDrawBackground((laWidget*)ButtonWidget12, LA_FALSE);
    laWidget_SetBorderType((laWidget*)ButtonWidget12, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetPressedImage(ButtonWidget12, &Right_Orange);
    laButtonWidget_SetReleasedImage(ButtonWidget12, &Right_Green);
    laButtonWidget_SetImagePosition(ButtonWidget12, LA_RELATIVE_POSITION_BEHIND);
    laButtonWidget_SetPressedOffset(ButtonWidget12, 0);
    laButtonWidget_SetReleasedEventCallback(ButtonWidget12, &ButtonWidget12_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget12);

}

static void ScreenCreate_FirstScreen(laScreen* screen)
{
    laLayer* layer0;
    laRadioButtonGroup* radioButtonGroup_1;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 480, 272);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    ListWheel1 = laListWheelWidget_New();
    laWidget_SetPosition((laWidget*)ListWheel1, 180, 11);
    laWidget_SetSize((laWidget*)ListWheel1, 140, 250);
    laWidget_SetDrawBackground((laWidget*)ListWheel1, LA_TRUE);
    laWidget_SetBorderType((laWidget*)ListWheel1, LA_WIDGET_BORDER_BEVEL);
    laListWheelWidget_SetAlignment(ListWheel1, LA_HALIGN_CENTER);
    laListWheelWidget_AppendItem(ListWheel1);
    laListWheelWidget_SetItemText(ListWheel1, 0, laString_CreateFromID(string_Listbox_Item1));
    laListWheelWidget_AppendItem(ListWheel1);
    laListWheelWidget_SetItemText(ListWheel1, 1, laString_CreateFromID(string_Listbox_Item2));
    laListWheelWidget_AppendItem(ListWheel1);
    laListWheelWidget_SetItemText(ListWheel1, 2, laString_CreateFromID(string_Listbox_Item3));
    laListWheelWidget_AppendItem(ListWheel1);
    laListWheelWidget_SetItemText(ListWheel1, 3, laString_CreateFromID(string_Listbox_Item4));
    laListWheelWidget_AppendItem(ListWheel1);
    laListWheelWidget_SetItemText(ListWheel1, 4, laString_CreateFromID(string_Listbox_Item5));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)ListWheel1);

    GroupBoxWidget1 = laGroupBoxWidget_New();
    laWidget_SetPosition((laWidget*)GroupBoxWidget1, 344, 10);
    laWidget_SetSize((laWidget*)GroupBoxWidget1, 127, 153);
    laWidget_SetDrawBackground((laWidget*)GroupBoxWidget1, LA_TRUE);
    laWidget_SetBorderType((laWidget*)GroupBoxWidget1, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GroupBoxWidget1);

    RadioButtonWidget1 = laRadioButtonWidget_New();
    laWidget_SetPosition((laWidget*)RadioButtonWidget1, 10, 12);
    laWidget_SetSize((laWidget*)RadioButtonWidget1, 107, 56);
    laWidget_SetDrawBackground((laWidget*)RadioButtonWidget1, LA_TRUE);
    laWidget_SetBorderType((laWidget*)RadioButtonWidget1, LA_WIDGET_BORDER_NONE);
    laRadioButtonWidget_SetText(RadioButtonWidget1, laString_CreateFromID(string_RadioButton_English));
    laRadioButtonGroup_Create(&radioButtonGroup_1);
    laRadioButtonGroup_AddButton(radioButtonGroup_1, RadioButtonWidget1);
    laRadioButtonWidget_SetSelected(RadioButtonWidget1);
    laRadioButtonWidget_SetSelectedEventCallback(RadioButtonWidget1, &RadioButtonWidget1_CheckedEvent);

    laWidget_AddChild((laWidget*)GroupBoxWidget1, (laWidget*)RadioButtonWidget1);

    RadioButtonWidget2 = laRadioButtonWidget_New();
    laWidget_SetPosition((laWidget*)RadioButtonWidget2, 10, 82);
    laWidget_SetSize((laWidget*)RadioButtonWidget2, 107, 60);
    laWidget_SetDrawBackground((laWidget*)RadioButtonWidget2, LA_TRUE);
    laWidget_SetBorderType((laWidget*)RadioButtonWidget2, LA_WIDGET_BORDER_NONE);
    laRadioButtonWidget_SetText(RadioButtonWidget2, laString_CreateFromID(string_RadioButton_Chinese));
    laRadioButtonGroup_AddButton(radioButtonGroup_1, RadioButtonWidget2);
    laRadioButtonWidget_SetSelectedEventCallback(RadioButtonWidget2, &RadioButtonWidget2_CheckedEvent);

    laWidget_AddChild((laWidget*)GroupBoxWidget1, (laWidget*)RadioButtonWidget2);

    ButtonWidget1 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget1, 411, 201);
    laWidget_SetSize((laWidget*)ButtonWidget1, 60, 60);
    laWidget_SetLocalRedraw((laWidget*)ButtonWidget1, LA_TRUE);
    laWidget_SetDrawBackground((laWidget*)ButtonWidget1, LA_FALSE);
    laWidget_SetBorderType((laWidget*)ButtonWidget1, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetPressedImage(ButtonWidget1, &Right_Blue);
    laButtonWidget_SetReleasedImage(ButtonWidget1, &Right_Grey);
    laButtonWidget_SetImagePosition(ButtonWidget1, LA_RELATIVE_POSITION_BELOW);
    laButtonWidget_SetPressedOffset(ButtonWidget1, 0);
    laButtonWidget_SetReleasedEventCallback(ButtonWidget1, &ButtonWidget1_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget1);

    ButtonWidget7 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget7, 10, 201);
    laWidget_SetSize((laWidget*)ButtonWidget7, 60, 60);
    laWidget_SetLocalRedraw((laWidget*)ButtonWidget7, LA_TRUE);
    laWidget_SetDrawBackground((laWidget*)ButtonWidget7, LA_FALSE);
    laWidget_SetBorderType((laWidget*)ButtonWidget7, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetPressedImage(ButtonWidget7, &Left_Blue);
    laButtonWidget_SetReleasedImage(ButtonWidget7, &Left_Grey);
    laButtonWidget_SetImagePosition(ButtonWidget7, LA_RELATIVE_POSITION_BELOW);
    laButtonWidget_SetPressedOffset(ButtonWidget7, 0);
    laButtonWidget_SetReleasedEventCallback(ButtonWidget7, &ButtonWidget7_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget7);

}

static void ScreenCreate_SecondScreen(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 1);
    laWidget_SetSize((laWidget*)layer0, 480, 272);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    GradientWidget2 = laGradientWidget_New();
    laWidget_SetSize((laWidget*)GradientWidget2, 479, 269);
    laWidget_SetScheme((laWidget*)GradientWidget2, &GradientScheme);
    laWidget_SetDrawBackground((laWidget*)GradientWidget2, LA_TRUE);
    laWidget_SetBorderType((laWidget*)GradientWidget2, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GradientWidget2);

    TouchTestWidget1 = laTouchTestWidget_New();
    laWidget_SetPosition((laWidget*)TouchTestWidget1, 80, 10);
    laWidget_SetSize((laWidget*)TouchTestWidget1, 320, 249);
    laWidget_SetScheme((laWidget*)TouchTestWidget1, &TouchTestScheme);
    laWidget_SetDrawBackground((laWidget*)TouchTestWidget1, LA_TRUE);
    laWidget_SetBorderType((laWidget*)TouchTestWidget1, LA_WIDGET_BORDER_BEVEL);
    laTouchTestWidget_SetPointAddedEventCallback(TouchTestWidget1, &TouchTestWidget1_PointAddedEvent);
    laWidget_AddChild((laWidget*)GradientWidget2, (laWidget*)TouchTestWidget1);

    ButtonWidget2 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget2, 10, 200);
    laWidget_SetSize((laWidget*)ButtonWidget2, 60, 60);
    laWidget_SetLocalRedraw((laWidget*)ButtonWidget2, LA_TRUE);
    laWidget_SetDrawBackground((laWidget*)ButtonWidget2, LA_FALSE);
    laWidget_SetBorderType((laWidget*)ButtonWidget2, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetPressedImage(ButtonWidget2, &Left_Green);
    laButtonWidget_SetReleasedImage(ButtonWidget2, &Left_Orange);
    laButtonWidget_SetImagePosition(ButtonWidget2, LA_RELATIVE_POSITION_BELOW);
    laButtonWidget_SetPressedOffset(ButtonWidget2, 0);
    laButtonWidget_SetReleasedEventCallback(ButtonWidget2, &ButtonWidget2_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget2);

    ButtonWidget3 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget3, 411, 199);
    laWidget_SetSize((laWidget*)ButtonWidget3, 60, 60);
    laWidget_SetLocalRedraw((laWidget*)ButtonWidget3, LA_TRUE);
    laWidget_SetDrawBackground((laWidget*)ButtonWidget3, LA_FALSE);
    laWidget_SetBorderType((laWidget*)ButtonWidget3, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetPressedImage(ButtonWidget3, &Right_Magenta);
    laButtonWidget_SetReleasedImage(ButtonWidget3, &Right_Green);
    laButtonWidget_SetImagePosition(ButtonWidget3, LA_RELATIVE_POSITION_BELOW);
    laButtonWidget_SetPressedOffset(ButtonWidget3, 0);
    laButtonWidget_SetReleasedEventCallback(ButtonWidget3, &ButtonWidget3_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget3);

}

static void ScreenCreate_ThirdScreen(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 480, 272);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    KeyPadWidget1 = laKeyPadWidget_New(4, 10);
    laWidget_SetPosition((laWidget*)KeyPadWidget1, 10, 61);
    laWidget_SetSize((laWidget*)KeyPadWidget1, 460, 160);
    laWidget_SetDrawBackground((laWidget*)KeyPadWidget1, LA_FALSE);
    laWidget_SetBorderType((laWidget*)KeyPadWidget1, LA_WIDGET_BORDER_BEVEL);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 0, laString_CreateFromID(string_Keypad_1));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 0, 0, laString_CreateFromID(string_Keypad_1));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 0, 0, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 0, laString_CreateFromID(string_Keypad_1));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 0, 0, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 1, laString_CreateFromID(string_Keypad_2));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 0, 1, laString_CreateFromID(string_Keypad_2));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 0, 1, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 1, laString_CreateFromID(string_Keypad_2));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 0, 1, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 2, laString_CreateFromID(string_Keypad_3));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 0, 2, laString_CreateFromID(string_Keypad_3));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 0, 2, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 2, laString_CreateFromID(string_Keypad_3));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 0, 2, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 3, laString_CreateFromID(string_Keypad_4));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 0, 3, laString_CreateFromID(string_Keypad_4));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 0, 3, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 3, laString_CreateFromID(string_Keypad_4));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 0, 3, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 4, laString_CreateFromID(string_Keypad_5));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 0, 4, laString_CreateFromID(string_Keypad_5));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 0, 4, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 4, laString_CreateFromID(string_Keypad_5));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 0, 4, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 5, laString_CreateFromID(string_Keypad_6));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 0, 5, laString_CreateFromID(string_Keypad_6));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 0, 5, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 5, laString_CreateFromID(string_Keypad_6));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 0, 5, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 6, laString_CreateFromID(string_Keypad_7));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 0, 6, laString_CreateFromID(string_Keypad_7));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 0, 6, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 6, laString_CreateFromID(string_Keypad_7));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 0, 6, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 7, laString_CreateFromID(string_Keypad_8));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 0, 7, laString_CreateFromID(string_Keypad_8));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 0, 7, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 7, laString_CreateFromID(string_Keypad_8));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 0, 7, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 8, laString_CreateFromID(string_Keypad_9));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 0, 8, laString_CreateFromID(string_Keypad_9));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 0, 8, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 8, laString_CreateFromID(string_Keypad_9));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 0, 8, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 9, laString_CreateFromID(string_Keypad_0));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 0, 9, laString_CreateFromID(string_Keypad_0));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 0, 9, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 0, 9, laString_CreateFromID(string_Keypad_0));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 0, 9, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 0, laString_CreateFromID(string_Keypad_q));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 1, 0, laString_CreateFromID(string_Keypad_q));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 1, 0, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 0, laString_CreateFromID(string_Keypad_q));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 1, 0, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 1, laString_CreateFromID(string_Keypad_w));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 1, 1, laString_CreateFromID(string_Keypad_w));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 1, 1, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 1, laString_CreateFromID(string_Keypad_w));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 1, 1, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 2, laString_CreateFromID(string_Keypad_e));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 1, 2, laString_CreateFromID(string_Keypad_e));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 1, 2, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 2, laString_CreateFromID(string_Keypad_e));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 1, 2, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 3, laString_CreateFromID(string_Keypad_r));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 1, 3, laString_CreateFromID(string_Keypad_r));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 1, 3, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 3, laString_CreateFromID(string_Keypad_r));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 1, 3, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 4, laString_CreateFromID(string_Keypad_t));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 1, 4, laString_CreateFromID(string_Keypad_t));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 1, 4, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 4, laString_CreateFromID(string_Keypad_t));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 1, 4, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 5, laString_CreateFromID(string_Keypad_y));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 1, 5, laString_CreateFromID(string_Keypad_y));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 1, 5, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 5, laString_CreateFromID(string_Keypad_y));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 1, 5, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 6, laString_CreateFromID(string_Keypad_u));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 1, 6, laString_CreateFromID(string_Keypad_u));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 1, 6, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 6, laString_CreateFromID(string_Keypad_u));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 1, 6, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 7, laString_CreateFromID(string_Keypad_i));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 1, 7, laString_CreateFromID(string_Keypad_i));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 1, 7, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 7, laString_CreateFromID(string_Keypad_i));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 1, 7, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 8, laString_CreateFromID(string_Keypad_o));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 1, 8, laString_CreateFromID(string_Keypad_o));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 1, 8, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 8, laString_CreateFromID(string_Keypad_o));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 1, 8, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 9, laString_CreateFromID(string_Keypad_p));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 1, 9, laString_CreateFromID(string_Keypad_p));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 1, 9, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 1, 9, laString_CreateFromID(string_Keypad_p));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 1, 9, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 0, laString_CreateFromID(string_Keypad_a));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 2, 0, laString_CreateFromID(string_Keypad_a));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 2, 0, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 0, laString_CreateFromID(string_Keypad_a));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 2, 0, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 1, laString_CreateFromID(string_Keypad_s));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 2, 1, laString_CreateFromID(string_Keypad_s));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 2, 1, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 1, laString_CreateFromID(string_Keypad_s));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 2, 1, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 2, laString_CreateFromID(string_Keypad_d));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 2, 2, laString_CreateFromID(string_Keypad_d));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 2, 2, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 2, laString_CreateFromID(string_Keypad_d));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 2, 2, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 3, laString_CreateFromID(string_Keypad_f));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 2, 3, laString_CreateFromID(string_Keypad_f));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 2, 3, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 3, laString_CreateFromID(string_Keypad_f));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 2, 3, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 4, laString_CreateFromID(string_Keypad_g));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 2, 4, laString_CreateFromID(string_Keypad_g));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 2, 4, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 4, laString_CreateFromID(string_Keypad_g));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 2, 4, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 5, laString_CreateFromID(string_Keypad_h));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 2, 5, laString_CreateFromID(string_Keypad_h));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 2, 5, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 5, laString_CreateFromID(string_Keypad_h));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 2, 5, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 6, laString_CreateFromID(string_Keypad_j));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 2, 6, laString_CreateFromID(string_Keypad_j));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 2, 6, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 6, laString_CreateFromID(string_Keypad_j));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 2, 6, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 7, laString_CreateFromID(string_Keypad_k));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 2, 7, laString_CreateFromID(string_Keypad_k));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 2, 7, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 7, laString_CreateFromID(string_Keypad_k));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 2, 7, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 8, laString_CreateFromID(string_Keypad_l));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 2, 8, laString_CreateFromID(string_Keypad_l));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 2, 8, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 8, laString_CreateFromID(string_Keypad_l));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 2, 8, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 2, 9, laString_CreateFromID(string_Backspace));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 2, 9, LA_KEYPAD_CELL_ACTION_BACKSPACE);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 2, 9, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 3, 0, laString_CreateFromID(string_Keypad_z));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 3, 0, laString_CreateFromID(string_Keypad_z));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 3, 0, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 3, 0, laString_CreateFromID(string_Keypad_z));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 3, 0, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 3, 1, laString_CreateFromID(string_Keypad_x));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 3, 1, laString_CreateFromID(string_Keypad_x));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 3, 1, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 3, 1, laString_CreateFromID(string_Keypad_x));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 3, 1, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 3, 2, laString_CreateFromID(string_Keypad_c));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 3, 2, laString_CreateFromID(string_Keypad_c));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 3, 2, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 3, 2, laString_CreateFromID(string_Keypad_c));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 3, 2, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 3, 3, laString_CreateFromID(string_Keypad_v));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 3, 3, laString_CreateFromID(string_Keypad_v));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 3, 3, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 3, 3, laString_CreateFromID(string_Keypad_v));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 3, 3, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 3, 4, laString_CreateFromID(string_Keypad_b));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 3, 4, laString_CreateFromID(string_Keypad_b));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 3, 4, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 3, 4, laString_CreateFromID(string_Keypad_b));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 3, 4, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 3, 5, laString_CreateFromID(string_Keypad_n));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 3, 5, laString_CreateFromID(string_Keypad_n));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 3, 5, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 3, 5, laString_CreateFromID(string_Keypad_n));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 3, 5, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 3, 6, laString_CreateFromID(string_Keypad_m));
    laKeyPadWidget_SetKeyValue(KeyPadWidget1, 3, 6, laString_CreateFromID(string_Keypad_m));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 3, 6, LA_KEYPAD_CELL_ACTION_APPEND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 3, 6, laString_CreateFromID(string_Keypad_m));
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 3, 6, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 3, 7, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 3, 8, LA_RELATIVE_POSITION_BEHIND);
    laKeyPadWidget_SetKeyText(KeyPadWidget1, 3, 9, laString_CreateFromID(string_clear));
    laKeyPadWidget_SetKeyAction(KeyPadWidget1, 3, 9, LA_KEYPAD_CELL_ACTION_CLEAR);
    laKeyPadWidget_SetKeyImagePosition(KeyPadWidget1, 3, 9, LA_RELATIVE_POSITION_BEHIND);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)KeyPadWidget1);

    TextFieldWidget1 = laTextFieldWidget_New();
    laWidget_SetPosition((laWidget*)TextFieldWidget1, 20, 10);
    laWidget_SetSize((laWidget*)TextFieldWidget1, 440, 42);
    laWidget_SetScheme((laWidget*)TextFieldWidget1, &defaultScheme);
    laWidget_SetDrawBackground((laWidget*)TextFieldWidget1, LA_TRUE);
    laWidget_SetBorderType((laWidget*)TextFieldWidget1, LA_WIDGET_BORDER_BEVEL);
    laTextFieldWidget_SetText(TextFieldWidget1, laString_CreateFromID(string_textField_Instruction));
    laTextFieldWidget_SetCursorEnabled(TextFieldWidget1, LA_TRUE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)TextFieldWidget1);

    ButtonWidget5 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget5, 10, 230);
    laWidget_SetSize((laWidget*)ButtonWidget5, 90, 33);
    laWidget_SetDrawBackground((laWidget*)ButtonWidget5, LA_TRUE);
    laWidget_SetBorderType((laWidget*)ButtonWidget5, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(ButtonWidget5, laString_CreateFromID(string_ButtonPreviousScreen));
    laButtonWidget_SetReleasedEventCallback(ButtonWidget5, &ButtonWidget5_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget5);

    ButtonWidget6 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget6, 390, 230);
    laWidget_SetSize((laWidget*)ButtonWidget6, 83, 30);
    laWidget_SetDrawBackground((laWidget*)ButtonWidget6, LA_TRUE);
    laWidget_SetBorderType((laWidget*)ButtonWidget6, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(ButtonWidget6, laString_CreateFromID(string_ButtonNextScreen));
    laButtonWidget_SetReleasedEventCallback(ButtonWidget6, &ButtonWidget6_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget6);

}

static void ScreenCreate_FourthScreen(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 480, 272);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    PanelWidget1 = laWidget_New();
    laWidget_SetPosition((laWidget*)PanelWidget1, 380, 10);
    laWidget_SetSize((laWidget*)PanelWidget1, 81, 181);
    laWidget_SetDrawBackground((laWidget*)PanelWidget1, LA_TRUE);
    laWidget_SetBorderType((laWidget*)PanelWidget1, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, PanelWidget1);

    SliderWidget1 = laSliderWidget_New();
    laWidget_SetPosition((laWidget*)SliderWidget1, 1, 10);
    laWidget_SetSize((laWidget*)SliderWidget1, 80, 162);
    laWidget_SetDrawBackground((laWidget*)SliderWidget1, LA_TRUE);
    laWidget_SetBorderType((laWidget*)SliderWidget1, LA_WIDGET_BORDER_BEVEL);
    laSliderWidget_SetMaximumValue(SliderWidget1, 255);
    laSliderWidget_SetGripSize(SliderWidget1, 15);
    laSliderWidget_SetValueChangedEventCallback(SliderWidget1, &SliderWidget1_ValueChangedEvent);

    laWidget_AddChild((laWidget*)PanelWidget1, (laWidget*)SliderWidget1);

    PanelWidget2 = laWidget_New();
    laWidget_SetPosition((laWidget*)PanelWidget2, 51, 11);
    laWidget_SetSize((laWidget*)PanelWidget2, 300, 180);
    laWidget_SetDrawBackground((laWidget*)PanelWidget2, LA_TRUE);
    laWidget_SetBorderType((laWidget*)PanelWidget2, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, PanelWidget2);

    ImageWidget1 = laImageWidget_New();
    laWidget_SetSize((laWidget*)ImageWidget1, 300, 180);
    laWidget_SetDrawBackground((laWidget*)ImageWidget1, LA_FALSE);
    laWidget_SetBorderType((laWidget*)ImageWidget1, LA_WIDGET_BORDER_LINE);
    laWidget_SetAlphaEnable((laWidget*)ImageWidget1, GFX_TRUE);
    laWidget_SetAlphaAmount((laWidget*)ImageWidget1, 255);
    laImageWidget_SetImage(ImageWidget1, &NewHarmonyLogo);
    laWidget_AddChild((laWidget*)PanelWidget2, (laWidget*)ImageWidget1);

    ImageWidget2 = laImageWidget_New();
    laWidget_SetSize((laWidget*)ImageWidget2, 300, 180);
    laWidget_SetDrawBackground((laWidget*)ImageWidget2, LA_FALSE);
    laWidget_SetBorderType((laWidget*)ImageWidget2, LA_WIDGET_BORDER_LINE);
    laWidget_SetAlphaEnable((laWidget*)ImageWidget2, GFX_TRUE);
    laWidget_SetAlphaAmount((laWidget*)ImageWidget2, 255);
    laImageWidget_SetImage(ImageWidget2, &MicrochipLogo);
    laWidget_AddChild((laWidget*)PanelWidget2, (laWidget*)ImageWidget2);

    ButtonWidget4 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget4, 10, 201);
    laWidget_SetSize((laWidget*)ButtonWidget4, 60, 60);
    laWidget_SetLocalRedraw((laWidget*)ButtonWidget4, LA_TRUE);
    laWidget_SetDrawBackground((laWidget*)ButtonWidget4, LA_FALSE);
    laWidget_SetBorderType((laWidget*)ButtonWidget4, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetPressedImage(ButtonWidget4, &Left_Blue);
    laButtonWidget_SetReleasedImage(ButtonWidget4, &Left_Orange);
    laButtonWidget_SetImagePosition(ButtonWidget4, LA_RELATIVE_POSITION_BELOW);
    laButtonWidget_SetPressedOffset(ButtonWidget4, 0);
    laButtonWidget_SetReleasedEventCallback(ButtonWidget4, &ButtonWidget4_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget4);

    ButtonWidget8 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget8, 410, 200);
    laWidget_SetSize((laWidget*)ButtonWidget8, 60, 60);
    laWidget_SetLocalRedraw((laWidget*)ButtonWidget8, LA_TRUE);
    laWidget_SetDrawBackground((laWidget*)ButtonWidget8, LA_FALSE);
    laWidget_SetBorderType((laWidget*)ButtonWidget8, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetPressedImage(ButtonWidget8, &Right_Green);
    laButtonWidget_SetReleasedImage(ButtonWidget8, &Right_Magenta);
    laButtonWidget_SetImagePosition(ButtonWidget8, LA_RELATIVE_POSITION_BELOW);
    laButtonWidget_SetPressedOffset(ButtonWidget8, 0);
    laButtonWidget_SetReleasedEventCallback(ButtonWidget8, &ButtonWidget8_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget8);

}

static void ScreenCreate_FifthScreen(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 480, 272);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    ImageSequenceWidget1 = laImageSequenceWidget_New();
    laWidget_SetSize((laWidget*)ImageSequenceWidget1, 480, 272);
    laWidget_SetScheme((laWidget*)ImageSequenceWidget1, &TouchTestScheme);
    laWidget_SetDrawBackground((laWidget*)ImageSequenceWidget1, LA_TRUE);
    laWidget_SetBorderType((laWidget*)ImageSequenceWidget1, LA_WIDGET_BORDER_NONE);
    laImageSequenceWidget_SetImageCount(ImageSequenceWidget1, 5);
    laImageSequenceWidget_SetImage(ImageSequenceWidget1, 0, &LucyInTheSky);
    laImageSequenceWidget_SetImage(ImageSequenceWidget1, 1, &USA);
    laImageSequenceWidget_SetImage(ImageSequenceWidget1, 2, &ice_color);
    laImageSequenceWidget_SetImage(ImageSequenceWidget1, 3, &MicrochipLogo);
    laImageSequenceWidget_SetImage(ImageSequenceWidget1, 4, &NewHarmonyLogo);
    laImageSequenceWidget_SetRepeat(ImageSequenceWidget1, LA_TRUE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)ImageSequenceWidget1);

    ButtonWidget10 = laButtonWidget_New();
    laWidget_SetSize((laWidget*)ButtonWidget10, 480, 230);
    laWidget_SetDrawBackground((laWidget*)ButtonWidget10, LA_FALSE);
    laWidget_SetBorderType((laWidget*)ButtonWidget10, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetReleasedEventCallback(ButtonWidget10, &ButtonWidget10_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget10);

    ButtonWidget9 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget9, 11, 237);
    laWidget_SetSize((laWidget*)ButtonWidget9, 100, 25);
    laWidget_SetDrawBackground((laWidget*)ButtonWidget9, LA_TRUE);
    laWidget_SetBorderType((laWidget*)ButtonWidget9, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(ButtonWidget9, laString_CreateFromID(string_ButtonPreviousScreen));
    laButtonWidget_SetReleasedEventCallback(ButtonWidget9, &ButtonWidget9_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget9);

    ButtonWidget11 = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ButtonWidget11, 370, 236);
    laWidget_SetSize((laWidget*)ButtonWidget11, 100, 25);
    laWidget_SetDrawBackground((laWidget*)ButtonWidget11, LA_TRUE);
    laWidget_SetBorderType((laWidget*)ButtonWidget11, LA_WIDGET_BORDER_BEVEL);
    laButtonWidget_SetText(ButtonWidget11, laString_CreateFromID(string_ButtonNextScreen));
    laButtonWidget_SetReleasedEventCallback(ButtonWidget11, &ButtonWidget11_ReleasedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)ButtonWidget11);

}



