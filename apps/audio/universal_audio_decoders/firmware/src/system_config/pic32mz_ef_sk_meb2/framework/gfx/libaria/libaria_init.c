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

laScheme text_label;
laScheme mp3_label_scheme;
laScheme _default;
laScheme wav_label_scheme;
laScheme track_time;
laScheme image_button;
laScheme filled_circle;
laScheme custom_progessbar;
laScheme track_info;
laRectangleWidget* RectangleWidget1;
laImageWidget* background1;
laLabelWidget* DemoNameLabel;
laLabelWidget* LabelWidget2;
laRectangleWidget* Background_0;
laImageWidget* LogoImage_0;
laLabelWidget* DemoName;
laLabelWidget* ReadingLabel;
laImageSequenceWidget* LoadingImageSeq;
laRectangleWidget* background;
laImageWidget* LogoImage;
laLabelWidget* LabelWidget1;
laLabelWidget* WAVIndicator;
laLabelWidget* MP3Indicator;
laWidget* ProgressPanel;
laRectangleWidget* ProgressBarRect;
laImageWidget* CircleIndicator;
laWidget* TrackInfoPanel;
laLabelWidget* TrackNameLabel;
laLabelWidget* TrackArtistLabel;
laLabelWidget* TrackAlbumLabel;
laWidget* ControlPanel;
laButtonWidget* PlayButton;
laButtonWidget* NextTrackButton;
laButtonWidget* PrevTrackButton;
laWidget* PanelWidget1;
laLabelWidget* TrackLengthLabel;
laWidget* PanelWidget2;
laLabelWidget* PlaytimeLabel;


static void ScreenCreate_Welcome(laScreen* screen);
static void ScreenCreate_Reading(laScreen* screen);
static void ScreenCreate_MainScreen(laScreen* screen);


int32_t libaria_initialize(void)
{
    laScreen* screen;

    laScheme_Initialize(&text_label, GFX_COLOR_MODE_RGB_565);
    text_label.base = 0xC67A;
    text_label.highlight = 0xC67A;
    text_label.highlightLight = 0xFFFF;
    text_label.shadow = 0x8410;
    text_label.shadowDark = 0x4208;
    text_label.foreground = 0xDEFB;
    text_label.foregroundInactive = 0xD71C;
    text_label.foregroundDisabled = 0x8410;
    text_label.background = 0xFFFF;
    text_label.backgroundInactive = 0xD71C;
    text_label.backgroundDisabled = 0xC67A;
    text_label.text = 0xDEFB;
    text_label.textHighlight = 0x1F;
    text_label.textHighlightText = 0xFFFF;
    text_label.textInactive = 0xD71C;
    text_label.textDisabled = 0x8C92;

    laScheme_Initialize(&mp3_label_scheme, GFX_COLOR_MODE_RGB_565);
    mp3_label_scheme.base = 0xC67A;
    mp3_label_scheme.highlight = 0xC67A;
    mp3_label_scheme.highlightLight = 0xFFFF;
    mp3_label_scheme.shadow = 0x8410;
    mp3_label_scheme.shadowDark = 0x4208;
    mp3_label_scheme.foreground = 0x0;
    mp3_label_scheme.foregroundInactive = 0xD71C;
    mp3_label_scheme.foregroundDisabled = 0x8410;
    mp3_label_scheme.background = 0xFFFF;
    mp3_label_scheme.backgroundInactive = 0xD71C;
    mp3_label_scheme.backgroundDisabled = 0xC67A;
    mp3_label_scheme.text = 0xC638;
    mp3_label_scheme.textHighlight = 0x1F;
    mp3_label_scheme.textHighlightText = 0xFFFF;
    mp3_label_scheme.textInactive = 0xD71C;
    mp3_label_scheme.textDisabled = 0x8C92;

    laScheme_Initialize(&_default, GFX_COLOR_MODE_RGB_565);
    _default.base = 0x2104;
    _default.highlight = 0xBDF7;
    _default.highlightLight = 0xFFFF;
    _default.shadow = 0x8410;
    _default.shadowDark = 0x4208;
    _default.foreground = 0x4208;
    _default.foregroundInactive = 0xD71C;
    _default.foregroundDisabled = 0xBDF7;
    _default.background = 0xFFFF;
    _default.backgroundInactive = 0xD71C;
    _default.backgroundDisabled = 0xC67A;
    _default.text = 0x0;
    _default.textHighlight = 0x1F;
    _default.textHighlightText = 0xFFFF;
    _default.textInactive = 0xFFFF;
    _default.textDisabled = 0x4208;

    laScheme_Initialize(&wav_label_scheme, GFX_COLOR_MODE_RGB_565);
    wav_label_scheme.base = 0xC67A;
    wav_label_scheme.highlight = 0xC67A;
    wav_label_scheme.highlightLight = 0xFFFF;
    wav_label_scheme.shadow = 0x8410;
    wav_label_scheme.shadowDark = 0x4208;
    wav_label_scheme.foreground = 0x0;
    wav_label_scheme.foregroundInactive = 0xD71C;
    wav_label_scheme.foregroundDisabled = 0x8410;
    wav_label_scheme.background = 0xFFFF;
    wav_label_scheme.backgroundInactive = 0xD71C;
    wav_label_scheme.backgroundDisabled = 0xC67A;
    wav_label_scheme.text = 0xC638;
    wav_label_scheme.textHighlight = 0x1F;
    wav_label_scheme.textHighlightText = 0xFFFF;
    wav_label_scheme.textInactive = 0xD71C;
    wav_label_scheme.textDisabled = 0x8C92;

    laScheme_Initialize(&track_time, GFX_COLOR_MODE_RGB_565);
    track_time.base = 0xC67A;
    track_time.highlight = 0xC67A;
    track_time.highlightLight = 0xFFFF;
    track_time.shadow = 0x8410;
    track_time.shadowDark = 0x4208;
    track_time.foreground = 0x0;
    track_time.foregroundInactive = 0xD71C;
    track_time.foregroundDisabled = 0x8410;
    track_time.background = 0xFFFF;
    track_time.backgroundInactive = 0xD71C;
    track_time.backgroundDisabled = 0xC67A;
    track_time.text = 0xDEFB;
    track_time.textHighlight = 0x1F;
    track_time.textHighlightText = 0xFFFF;
    track_time.textInactive = 0xD71C;
    track_time.textDisabled = 0x8C92;

    laScheme_Initialize(&image_button, GFX_COLOR_MODE_RGB_565);
    image_button.base = 0x2104;
    image_button.highlight = 0xC67A;
    image_button.highlightLight = 0xFFFF;
    image_button.shadow = 0x8410;
    image_button.shadowDark = 0x4208;
    image_button.foreground = 0x0;
    image_button.foregroundInactive = 0xD71C;
    image_button.foregroundDisabled = 0x8410;
    image_button.background = 0x2104;
    image_button.backgroundInactive = 0xD71C;
    image_button.backgroundDisabled = 0xC67A;
    image_button.text = 0x0;
    image_button.textHighlight = 0x1F;
    image_button.textHighlightText = 0xFFFF;
    image_button.textInactive = 0xD71C;
    image_button.textDisabled = 0x8C92;

    laScheme_Initialize(&filled_circle, GFX_COLOR_MODE_RGB_565);
    filled_circle.base = 0xFFFF;
    filled_circle.highlight = 0xC67A;
    filled_circle.highlightLight = 0xFFFF;
    filled_circle.shadow = 0x8410;
    filled_circle.shadowDark = 0x4208;
    filled_circle.foreground = 0xFFFF;
    filled_circle.foregroundInactive = 0xD71C;
    filled_circle.foregroundDisabled = 0x8410;
    filled_circle.background = 0x2104;
    filled_circle.backgroundInactive = 0xD71C;
    filled_circle.backgroundDisabled = 0xC67A;
    filled_circle.text = 0x0;
    filled_circle.textHighlight = 0x1F;
    filled_circle.textHighlightText = 0xFFFF;
    filled_circle.textInactive = 0xD71C;
    filled_circle.textDisabled = 0x8C92;

    laScheme_Initialize(&custom_progessbar, GFX_COLOR_MODE_RGB_565);
    custom_progessbar.base = 0xD00C;
    custom_progessbar.highlight = 0xC67A;
    custom_progessbar.highlightLight = 0xFFFF;
    custom_progessbar.shadow = 0x8410;
    custom_progessbar.shadowDark = 0x4208;
    custom_progessbar.foreground = 0x0;
    custom_progessbar.foregroundInactive = 0xD71C;
    custom_progessbar.foregroundDisabled = 0x8410;
    custom_progessbar.background = 0xD00C;
    custom_progessbar.backgroundInactive = 0xD71C;
    custom_progessbar.backgroundDisabled = 0xC67A;
    custom_progessbar.text = 0x0;
    custom_progessbar.textHighlight = 0x1F;
    custom_progessbar.textHighlightText = 0xFFFF;
    custom_progessbar.textInactive = 0xD71C;
    custom_progessbar.textDisabled = 0x8C92;

    laScheme_Initialize(&track_info, GFX_COLOR_MODE_RGB_565);
    track_info.base = 0x9492;
    track_info.highlight = 0xC67A;
    track_info.highlightLight = 0xFFFF;
    track_info.shadow = 0x8410;
    track_info.shadowDark = 0x4208;
    track_info.foreground = 0x8047;
    track_info.foregroundInactive = 0xD71C;
    track_info.foregroundDisabled = 0x8410;
    track_info.background = 0x8410;
    track_info.backgroundInactive = 0xD71C;
    track_info.backgroundDisabled = 0xC67A;
    track_info.text = 0xEF5D;
    track_info.textHighlight = 0x1F;
    track_info.textHighlightText = 0xFFFF;
    track_info.textInactive = 0xD71C;
    track_info.textDisabled = 0x8C92;

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_Welcome);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_Reading);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_MainScreen);
    laContext_AddScreen(screen);

    laContext_SetStringTable(&stringTable);
    laContext_SetActiveScreen(0);

	return 0;
}

static void ScreenCreate_Welcome(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 480, 272);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    RectangleWidget1 = laRectangleWidget_New();
    laWidget_SetSize((laWidget*)RectangleWidget1, 480, 272);
    laWidget_SetScheme((laWidget*)RectangleWidget1, &_default);
    laWidget_SetDrawBackground((laWidget*)RectangleWidget1, LA_TRUE);
    laWidget_SetBorderType((laWidget*)RectangleWidget1, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)RectangleWidget1);

    background1 = laImageWidget_New();
    laWidget_SetPosition((laWidget*)background1, 2, 5);
    laWidget_SetSize((laWidget*)background1, 125, 28);
    laWidget_SetScheme((laWidget*)background1, &image_button);
    laWidget_SetDrawBackground((laWidget*)background1, LA_TRUE);
    laWidget_SetBorderType((laWidget*)background1, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(background1, &MCHP_LOGO);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)background1);

    DemoNameLabel = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)DemoNameLabel, 2, 35);
    laWidget_SetSize((laWidget*)DemoNameLabel, 276, 25);
    laWidget_SetScheme((laWidget*)DemoNameLabel, &text_label);
    laWidget_SetDrawBackground((laWidget*)DemoNameLabel, LA_FALSE);
    laWidget_SetBorderType((laWidget*)DemoNameLabel, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(DemoNameLabel, laString_CreateFromID(string_DEMO_NAME));
    laLabelWidget_SetHAlignment(DemoNameLabel, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)DemoNameLabel);

    LabelWidget2 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget2, 119, 129);
    laWidget_SetSize((laWidget*)LabelWidget2, 249, 25);
    laWidget_SetScheme((laWidget*)LabelWidget2, &text_label);
    laWidget_SetDrawBackground((laWidget*)LabelWidget2, LA_FALSE);
    laWidget_SetBorderType((laWidget*)LabelWidget2, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget2, laString_CreateFromID(string_InsertUSB));
    laLabelWidget_SetHAlignment(LabelWidget2, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget2);

}

static void ScreenCreate_Reading(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 480, 272);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    Background_0 = laRectangleWidget_New();
    laWidget_SetSize((laWidget*)Background_0, 480, 272);
    laWidget_SetScheme((laWidget*)Background_0, &image_button);
    laWidget_SetDrawBackground((laWidget*)Background_0, LA_TRUE);
    laWidget_SetBorderType((laWidget*)Background_0, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)Background_0);

    LogoImage_0 = laImageWidget_New();
    laWidget_SetPosition((laWidget*)LogoImage_0, 2, 5);
    laWidget_SetSize((laWidget*)LogoImage_0, 125, 28);
    laWidget_SetScheme((laWidget*)LogoImage_0, &image_button);
    laWidget_SetDrawBackground((laWidget*)LogoImage_0, LA_FALSE);
    laWidget_SetBorderType((laWidget*)LogoImage_0, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(LogoImage_0, &MCHP_LOGO);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LogoImage_0);

    DemoName = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)DemoName, 2, 35);
    laWidget_SetSize((laWidget*)DemoName, 276, 25);
    laWidget_SetScheme((laWidget*)DemoName, &text_label);
    laWidget_SetDrawBackground((laWidget*)DemoName, LA_FALSE);
    laWidget_SetBorderType((laWidget*)DemoName, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(DemoName, laString_CreateFromID(string_DEMO_NAME));
    laLabelWidget_SetHAlignment(DemoName, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)DemoName);

    ReadingLabel = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)ReadingLabel, 83, 106);
    laWidget_SetSize((laWidget*)ReadingLabel, 191, 56);
    laWidget_SetScheme((laWidget*)ReadingLabel, &text_label);
    laWidget_SetDrawBackground((laWidget*)ReadingLabel, LA_FALSE);
    laWidget_SetBorderType((laWidget*)ReadingLabel, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(ReadingLabel, laString_CreateFromID(string_MSD_STATUS));
    laLabelWidget_SetHAlignment(ReadingLabel, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)ReadingLabel);

    LoadingImageSeq = laImageSequenceWidget_New();
    laWidget_SetPosition((laWidget*)LoadingImageSeq, 277, 106);
    laWidget_SetSize((laWidget*)LoadingImageSeq, 52, 52);
    laWidget_SetScheme((laWidget*)LoadingImageSeq, &_default);
    laWidget_SetDrawBackground((laWidget*)LoadingImageSeq, LA_TRUE);
    laWidget_SetBorderType((laWidget*)LoadingImageSeq, LA_WIDGET_BORDER_NONE);
    laImageSequenceWidget_SetImageCount(LoadingImageSeq, 8);
    laImageSequenceWidget_SetImage(LoadingImageSeq, 0, &load01);
    laImageSequenceWidget_SetImageDelay(LoadingImageSeq, 0, 12000);
    laImageSequenceWidget_SetImage(LoadingImageSeq, 1, &load02);
    laImageSequenceWidget_SetImageDelay(LoadingImageSeq, 1, 12000);
    laImageSequenceWidget_SetImage(LoadingImageSeq, 2, &load03);
    laImageSequenceWidget_SetImageDelay(LoadingImageSeq, 2, 12000);
    laImageSequenceWidget_SetImage(LoadingImageSeq, 3, &load04);
    laImageSequenceWidget_SetImageDelay(LoadingImageSeq, 3, 12000);
    laImageSequenceWidget_SetImage(LoadingImageSeq, 4, &load05);
    laImageSequenceWidget_SetImageDelay(LoadingImageSeq, 4, 12000);
    laImageSequenceWidget_SetImage(LoadingImageSeq, 5, &load06);
    laImageSequenceWidget_SetImageDelay(LoadingImageSeq, 5, 12000);
    laImageSequenceWidget_SetImage(LoadingImageSeq, 6, &load07);
    laImageSequenceWidget_SetImageDelay(LoadingImageSeq, 6, 12000);
    laImageSequenceWidget_SetImage(LoadingImageSeq, 7, &load08);
    laImageSequenceWidget_SetImageDelay(LoadingImageSeq, 7, 12000);
    laImageSequenceWidget_SetRepeat(LoadingImageSeq, LA_TRUE);
    laImageSequenceWidget_Play(LoadingImageSeq);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LoadingImageSeq);

}

static void ScreenCreate_MainScreen(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 480, 272);
    laLayer_SetBufferCount(layer0, 1);

    laScreen_SetLayer(screen, 0, layer0);

    background = laRectangleWidget_New();
    laWidget_SetSize((laWidget*)background, 480, 271);
    laWidget_SetScheme((laWidget*)background, &_default);
    laWidget_SetDrawBackground((laWidget*)background, LA_TRUE);
    laWidget_SetBorderType((laWidget*)background, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)background);

    LogoImage = laImageWidget_New();
    laWidget_SetPosition((laWidget*)LogoImage, 2, 5);
    laWidget_SetSize((laWidget*)LogoImage, 125, 28);
    laWidget_SetScheme((laWidget*)LogoImage, &image_button);
    laWidget_SetDrawBackground((laWidget*)LogoImage, LA_FALSE);
    laWidget_SetBorderType((laWidget*)LogoImage, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(LogoImage, &MCHP_LOGO);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LogoImage);

    LabelWidget1 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget1, 2, 35);
    laWidget_SetSize((laWidget*)LabelWidget1, 276, 25);
    laWidget_SetScheme((laWidget*)LabelWidget1, &text_label);
    laWidget_SetDrawBackground((laWidget*)LabelWidget1, LA_FALSE);
    laWidget_SetBorderType((laWidget*)LabelWidget1, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget1, laString_CreateFromID(string_DEMO_NAME));
    laLabelWidget_SetHAlignment(LabelWidget1, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget1);

    WAVIndicator = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)WAVIndicator, 286, 12);
    laWidget_SetSize((laWidget*)WAVIndicator, 35, 25);
    laWidget_SetLocalRedraw((laWidget*)WAVIndicator, LA_TRUE);
    laWidget_SetScheme((laWidget*)WAVIndicator, &wav_label_scheme);
    laWidget_SetDrawBackground((laWidget*)WAVIndicator, LA_FALSE);
    laWidget_SetBorderType((laWidget*)WAVIndicator, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(WAVIndicator, laString_CreateFromID(string_WAV_DECODER));
    laLabelWidget_SetHAlignment(WAVIndicator, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)WAVIndicator);

    MP3Indicator = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)MP3Indicator, 328, 12);
    laWidget_SetSize((laWidget*)MP3Indicator, 31, 24);
    laWidget_SetLocalRedraw((laWidget*)MP3Indicator, LA_TRUE);
    laWidget_SetScheme((laWidget*)MP3Indicator, &mp3_label_scheme);
    laWidget_SetDrawBackground((laWidget*)MP3Indicator, LA_FALSE);
    laWidget_SetBorderType((laWidget*)MP3Indicator, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(MP3Indicator, laString_CreateFromID(string_MP3_DECODER));
    laLabelWidget_SetHAlignment(MP3Indicator, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)MP3Indicator);

    ProgressPanel = laWidget_New();
    laWidget_SetPosition((laWidget*)ProgressPanel, 77, 215);
    laWidget_SetSize((laWidget*)ProgressPanel, 325, 29);
    laWidget_SetScheme((laWidget*)ProgressPanel, &_default);
    laWidget_SetDrawBackground((laWidget*)ProgressPanel, LA_TRUE);
    laWidget_SetBorderType((laWidget*)ProgressPanel, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, ProgressPanel);

    ProgressBarRect = laRectangleWidget_New();
    laWidget_SetPosition((laWidget*)ProgressBarRect, 15, 15);
    laWidget_SetSize((laWidget*)ProgressBarRect, 300, 5);
    laWidget_SetScheme((laWidget*)ProgressBarRect, &custom_progessbar);
    laWidget_SetDrawBackground((laWidget*)ProgressBarRect, LA_TRUE);
    laWidget_SetBorderType((laWidget*)ProgressBarRect, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)ProgressPanel, (laWidget*)ProgressBarRect);

    CircleIndicator = laImageWidget_New();
    laWidget_SetPosition((laWidget*)CircleIndicator, 15, 9);
    laWidget_SetSize((laWidget*)CircleIndicator, 16, 16);
    laWidget_SetScheme((laWidget*)CircleIndicator, &filled_circle);
    laWidget_SetDrawBackground((laWidget*)CircleIndicator, LA_FALSE);
    laWidget_SetBorderType((laWidget*)CircleIndicator, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(CircleIndicator, &progress_indicator_circle);
    laWidget_AddChild((laWidget*)ProgressPanel, (laWidget*)CircleIndicator);

    TrackInfoPanel = laWidget_New();
    laWidget_SetPosition((laWidget*)TrackInfoPanel, 0, 100);
    laWidget_SetSize((laWidget*)TrackInfoPanel, 480, 50);
    laWidget_SetScheme((laWidget*)TrackInfoPanel, &_default);
    laWidget_SetDrawBackground((laWidget*)TrackInfoPanel, LA_TRUE);
    laWidget_SetBorderType((laWidget*)TrackInfoPanel, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, TrackInfoPanel);

    TrackNameLabel = laLabelWidget_New();
    laWidget_SetSize((laWidget*)TrackNameLabel, 480, 25);
    laWidget_SetScheme((laWidget*)TrackNameLabel, &track_info);
    laWidget_SetDrawBackground((laWidget*)TrackNameLabel, LA_FALSE);
    laWidget_SetBorderType((laWidget*)TrackNameLabel, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(TrackNameLabel, laString_CreateFromID(string_TRACK_NAME));
    laWidget_AddChild((laWidget*)TrackInfoPanel, (laWidget*)TrackNameLabel);

    TrackArtistLabel = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)TrackArtistLabel, 0, 30);
    laWidget_SetSize((laWidget*)TrackArtistLabel, 240, 25);
    laWidget_SetScheme((laWidget*)TrackArtistLabel, &track_info);
    laWidget_SetDrawBackground((laWidget*)TrackArtistLabel, LA_FALSE);
    laWidget_SetBorderType((laWidget*)TrackArtistLabel, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(TrackArtistLabel, laString_CreateFromID(string_TRACK_ARTIST));
    laLabelWidget_SetHAlignment(TrackArtistLabel, LA_HALIGN_RIGHT);
    laWidget_AddChild((laWidget*)TrackInfoPanel, (laWidget*)TrackArtistLabel);

    TrackAlbumLabel = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)TrackAlbumLabel, 240, 30);
    laWidget_SetSize((laWidget*)TrackAlbumLabel, 240, 25);
    laWidget_SetScheme((laWidget*)TrackAlbumLabel, &track_info);
    laWidget_SetDrawBackground((laWidget*)TrackAlbumLabel, LA_FALSE);
    laWidget_SetBorderType((laWidget*)TrackAlbumLabel, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(TrackAlbumLabel, laString_CreateFromID(string_ALBUM));
    laLabelWidget_SetHAlignment(TrackAlbumLabel, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)TrackInfoPanel, (laWidget*)TrackAlbumLabel);

    ControlPanel = laWidget_New();
    laWidget_SetPosition((laWidget*)ControlPanel, 150, 182);
    laWidget_SetSize((laWidget*)ControlPanel, 183, 30);
    laWidget_SetScheme((laWidget*)ControlPanel, &_default);
    laWidget_SetDrawBackground((laWidget*)ControlPanel, LA_TRUE);
    laWidget_SetBorderType((laWidget*)ControlPanel, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, ControlPanel);

    PlayButton = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)PlayButton, 75, -2);
    laWidget_SetSize((laWidget*)PlayButton, 30, 30);
    laWidget_SetScheme((laWidget*)PlayButton, &image_button);
    laWidget_SetDrawBackground((laWidget*)PlayButton, LA_TRUE);
    laWidget_SetBorderType((laWidget*)PlayButton, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetReleasedImage(PlayButton, &Play);
    laButtonWidget_SetImagePosition(PlayButton, LA_RELATIVE_POSITION_RIGHTOF);
    laButtonWidget_SetReleasedEventCallback(PlayButton, &PlayButton_ReleasedEvent);

    laWidget_AddChild((laWidget*)ControlPanel, (laWidget*)PlayButton);

    NextTrackButton = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)NextTrackButton, 150, -2);
    laWidget_SetSize((laWidget*)NextTrackButton, 30, 30);
    laWidget_SetLocalRedraw((laWidget*)NextTrackButton, LA_TRUE);
    laWidget_SetScheme((laWidget*)NextTrackButton, &image_button);
    laWidget_SetDrawBackground((laWidget*)NextTrackButton, LA_FALSE);
    laWidget_SetBorderType((laWidget*)NextTrackButton, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetPressedImage(NextTrackButton, &NextShrink);
    laButtonWidget_SetReleasedImage(NextTrackButton, &Next);
    laButtonWidget_SetImagePosition(NextTrackButton, LA_RELATIVE_POSITION_RIGHTOF);
    laButtonWidget_SetReleasedEventCallback(NextTrackButton, &NextTrackButton_ReleasedEvent);

    laWidget_AddChild((laWidget*)ControlPanel, (laWidget*)NextTrackButton);

    PrevTrackButton = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)PrevTrackButton, 0, -2);
    laWidget_SetSize((laWidget*)PrevTrackButton, 30, 30);
    laWidget_SetScheme((laWidget*)PrevTrackButton, &image_button);
    laWidget_SetDrawBackground((laWidget*)PrevTrackButton, LA_TRUE);
    laWidget_SetBorderType((laWidget*)PrevTrackButton, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetPressedImage(PrevTrackButton, &PrevShrink);
    laButtonWidget_SetReleasedImage(PrevTrackButton, &Prev);
    laButtonWidget_SetReleasedEventCallback(PrevTrackButton, &PrevTrackButton_ReleasedEvent);

    laWidget_AddChild((laWidget*)ControlPanel, (laWidget*)PrevTrackButton);

    PanelWidget1 = laWidget_New();
    laWidget_SetPosition((laWidget*)PanelWidget1, 321, 241);
    laWidget_SetSize((laWidget*)PanelWidget1, 74, 25);
    laWidget_SetLocalRedraw((laWidget*)PanelWidget1, LA_TRUE);
    laWidget_SetScheme((laWidget*)PanelWidget1, &_default);
    laWidget_SetDrawBackground((laWidget*)PanelWidget1, LA_TRUE);
    laWidget_SetBorderType((laWidget*)PanelWidget1, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, PanelWidget1);

    TrackLengthLabel = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)TrackLengthLabel, 22, 0);
    laWidget_SetSize((laWidget*)TrackLengthLabel, 51, 24);
    laWidget_SetScheme((laWidget*)TrackLengthLabel, &track_time);
    laWidget_SetDrawBackground((laWidget*)TrackLengthLabel, LA_FALSE);
    laWidget_SetBorderType((laWidget*)TrackLengthLabel, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(TrackLengthLabel, laString_CreateFromID(string_TRACK_LENGTH));
    laLabelWidget_SetHAlignment(TrackLengthLabel, LA_HALIGN_RIGHT);
    laWidget_AddChild((laWidget*)PanelWidget1, (laWidget*)TrackLengthLabel);

    PanelWidget2 = laWidget_New();
    laWidget_SetPosition((laWidget*)PanelWidget2, 96, 243);
    laWidget_SetSize((laWidget*)PanelWidget2, 48, 26);
    laWidget_SetLocalRedraw((laWidget*)PanelWidget2, LA_TRUE);
    laWidget_SetScheme((laWidget*)PanelWidget2, &_default);
    laWidget_SetDrawBackground((laWidget*)PanelWidget2, LA_TRUE);
    laWidget_SetBorderType((laWidget*)PanelWidget2, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, PanelWidget2);

    PlaytimeLabel = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)PlaytimeLabel, -4, -3);
    laWidget_SetSize((laWidget*)PlaytimeLabel, 51, 25);
    laWidget_SetScheme((laWidget*)PlaytimeLabel, &track_time);
    laWidget_SetDrawBackground((laWidget*)PlaytimeLabel, LA_FALSE);
    laWidget_SetBorderType((laWidget*)PlaytimeLabel, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(PlaytimeLabel, laString_CreateFromID(string_PLAY_TIME));
    laLabelWidget_SetHAlignment(PlaytimeLabel, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)PanelWidget2, (laWidget*)PlaytimeLabel);

}



