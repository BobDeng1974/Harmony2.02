/*******************************************************************************
  MPLAB Harmony Graphics Composer Generated Implementation File

  File Name:
    gfx_hgc_definitions.c

  Summary:
    Build-time generated implementation from the MPLAB Harmony
    Graphics Composer.

  Description:
    Build-time generated implementation from the MPLAB Harmony
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
#include "gfx_hgc_definitions.h"

<#if CONFIG_GFX_HGC_HAS_SCHEMES = true>
/*** Default GFX GOL Scheme ***/
#define GFX_SCHEMEDEFAULT GOLSchemeDefault
extern GFX_GOL_OBJ_SCHEME GFX_SCHEMEDEFAULT;

/*** HGC-specified GFX GOL Scheme ***/
<#assign x=CONFIG_GFX_HGC_NUM_SCHEMES>
<#list 0..x-1 as i>
    <@GFX_HGC_SCHEME_DECLARE
        GFX_SCHEME_INDEX = "${i}"
        />
</#list>

</#if>
/*** Generated Asset References ***/
<#if CONFIG_GFX_HGC_HAS_ASSETS = true>
<#assign x=CONFIG_GFX_HGC_NUM_ASSETS>
<#list 0..x-1 as i>
    <@GFX_HGC_EXTERN_RESOURCE
        RESOURCE = "GFX_GENERATED_RESOURCE_${i}"
        />
</#list>

</#if>
/*** Generated ASCII Text Labels ***/
<#if CONFIG_GFX_HGC_HAS_BUTTONS = true>
<#assign x=CONFIG_GFX_HGC_NUM_BUTTONS>
<#list 0..x-1 as i>
    <@GFX_HGC_BUTTON_TEXT_INIT
        INDEX = "${i}"
        TEXT = "CONFIG_HGC_BTN_TEXT_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_CHECKBOXES = true>
<#assign x=CONFIG_GFX_HGC_NUM_CHECKBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_CHECKBOX_TEXT_INIT
        INDEX = "${i}"
        TEXT = "CONFIG_HGC_CHECKBOX_TEXT_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_RADIOBUTTONS = true>
<#assign x=CONFIG_GFX_HGC_NUM_RADIOBUTTONS>
<#list 0..x-1 as i>
    <@GFX_HGC_RADIOBUTTON_TEXT_INIT
        INDEX = "${i}"
        TEXT = "CONFIG_HGC_RADIOBUTTON_TEXT_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_METERS = true>
<#assign x=CONFIG_GFX_HGC_NUM_METERS>
<#list 0..x-1 as i>
    <@GFX_HGC_METER_TEXT_INIT
        INDEX = "${i}"
        TEXT = "CONFIG_HGC_METER_TEXT_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_EDITBOXES = true>
<#assign x=CONFIG_GFX_HGC_NUM_EDITBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_EDITBOX_TEXT_INIT
        INDEX = "${i}"
        TEXT = "CONFIG_HGC_EDITBOX_TEXT_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_LISTBOXES = true>
<#assign x=CONFIG_GFX_HGC_NUM_LISTBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_LISTBOX_TEXT_INIT
        NAME = "CONFIG_HGC_LISTBOX_ID_${i}"
		INDEX = "${i}"
		COUNT = "CONFIG_HGC_LISTBOX_ITEM_COUNT_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_GROUPBOXES = true>
<#assign x=CONFIG_GFX_HGC_NUM_GROUPBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_GROUPBOX_TEXT_INIT
        NAME = "CONFIG_HGC_GROUPBOX_ID_${i}"
		INDEX = "${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_STATICTEXTS = true>
<#assign x=CONFIG_GFX_HGC_NUM_STATICTEXTS>
<#list 0..x-1 as i>
    <@GFX_HGC_STATIC_TEXT_INIT
        INDEX = "${i}"
        TEXT = "CONFIG_HGC_STATICTEXT_TEXT_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_TEXTENTRYS = true>
<#assign x=CONFIG_GFX_HGC_NUM_TEXTENTRYS>
<#list 0..x-1 as i>
    <@GFX_HGC_TEXTENTRY_TEXT_INIT
        NAME = "CONFIG_HGC_TEXTENTRY_ID_${i}"
		INDEX = "${i}"
		ROW_COUNT = "CONFIG_HGC_TEXTENTRY_ROWCOUNT_${i}"
		COL_COUNT = "CONFIG_HGC_TEXTENTRY_COLCOUNT_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_WINDOWS = true>
<#assign x=CONFIG_GFX_HGC_NUM_WINDOWS>
<#list 0..x-1 as i>
    <@GFX_HGC_WINDOW_TEXT_INIT
        INDEX = "${i}"
        TEXT = "CONFIG_HGC_WINDOW_TEXT_${i}"
        />
</#list>

</#if>
/*** HGC Object Global ***/
HGC_OBJECTS hgcObj;
static HGC_STATES hgcState;

<#if CONFIG_USE_SYS_MSG = true>
/*** Message System Service Globals ***/
SYS_MSG_INSTANCE iSysMsg = SYS_MSG_0;
SYS_OBJ_HANDLE hSysMsg, hMsgType, hMailbox;

/******************************************************************************
  Function:
    void GFX_HGC_TouchMessageCallback ( SYS_MSG_OBJECT *pMsg )

  Summary:
    This function sets up the Message System Service to route touch callbacks
    to the GOL message system  
 */
void GFX_HGC_TouchMessageCallback ( SYS_MSG_OBJECT *pMsg )
{
    static GFX_GOL_MESSAGE gMsg;

    gMsg.type = pMsg->nMessageTypeID;
    gMsg.uiEvent = pMsg->param0;
    gMsg.param1 = pMsg->param1;
    gMsg.param2 = pMsg->param2;

    GFX_GOL_ObjectMessage(GFX_INDEX_0, &gMsg);
}


</#if>
/******************************************************************************
  Function:
    HGC_SCREEN_STATES GFX_HGC_GetScreenState ( void )

  Remarks:
    This function returns the screen state
 */
HGC_SCREEN_STATES GFX_HGC_GetScreenState ( void )
{
    return hgcObj.screenState;
}


/******************************************************************************
  Function:
    void GFX_HGC_SetScreenState ( HGC_SCREEN_STATES newState )

  Remarks:
    This function sets the screen state machine to a new state
 */
void GFX_HGC_SetScreenState ( HGC_SCREEN_STATES newState )
{
    hgcObj.prevRefreshState = hgcObj.screenState;
    hgcObj.screenState = newState;
}


/******************************************************************************
  Function:
    void GFX_HGC_Initialize ( void )

  Summary:
    This function initializes the HGC state machine.  
 */
void GFX_HGC_Initialize ( void )
{
    hgcState = HGC_STATE_INIT;
    hgcObj.screenState = HGC_SCREEN_STATE_INIT;
}


/******************************************************************************
  Function:
    void GFX_HGC_Setup ( void )

  Summary:
    This function sets up the GOL message callback and draw callbacks.  
 */
void GFX_HGC_Setup ( void )
{
<#if CONFIG_USE_SYS_MSG = true>
    hMsgType = SYS_MSG_TypeCreate(SYS_MSG_0, TYPE_TOUCHSCREEN , 0);
    hMailbox = SYS_MSG_MailboxOpen(SYS_MSG_0, (SYS_MSG_RECEIVE_CALLBACK) &GFX_HGC_TouchMessageCallback );
    SYS_MSG_MailboxMsgAdd( hMailbox, hMsgType);

</#if>
<#if CONFIG_GFX_HGC_USE_GOL = true>
    GFX_GOL_MessageCallbackSet(GFX_INDEX_0, &GFX_HGC_MessageCallback);
    GFX_GOL_DrawCallbackSet(GFX_INDEX_0, &GFX_HGC_DrawCallback);

</#if>
<#if CONFIG_GFX_HGC_HAS_SCHEMES = true>
    GFX_HGC_InitializeSchemes();

</#if>
}

/******************************************************************************
  Function:
    void GFX_HGC_Tasks (SYS_MODULE_OBJ gfxObject);

  Summary:
    This function is called in SYS_Tasks.  The intent wait until the GFX library
    is initialized before supplying items to draw
*/
void GFX_HGC_Tasks  (SYS_MODULE_OBJ gfxObject)
{
    switch ( hgcState )
    {
        case HGC_STATE_INIT:
            if (GFX_Status(gfxObject)==SYS_STATUS_READY)
            {
                GFX_HGC_Setup();
                hgcState = HGC_STATE_RUNNING;
            }
            break;

        case HGC_STATE_RUNNING:
<#if CONFIG_GFX_HGC_USE_GOL = false>
            //Drive screen state machine
            GFX_HGC_DrawScreenTask();
</#if>
            break;

        default:
            break;
    }
}

<#if CONFIG_GFX_HGC_HAS_SCHEMES = true>
/******************************************************************************
  Function:
    void GFX_HGC_SchemeCreate ( void )

  Summary:
    Allocates memory for a new scheme
 */
GFX_GOL_OBJ_SCHEME *GFX_HGC_SchemeCreate(void)
{
    GFX_GOL_OBJ_SCHEME  *pTemp;

    pTemp = (GFX_GOL_OBJ_SCHEME *)GFX_malloc(sizeof(GFX_GOL_OBJ_SCHEME));

    if(pTemp != NULL)
    {
        memcpy(pTemp, &GFX_SCHEMEDEFAULT, sizeof(GFX_GOL_OBJ_SCHEME));
    }

    return (pTemp);
}

</#if>
<#if CONFIG_GFX_HGC_HAS_SCHEMES = true>
/******************************************************************************
  Function:
    void GFX_HGC_InitializeSchemes ( void )

  Summary:
    Initializes all HGC-specified schemes
 */
void GFX_HGC_InitializeSchemes( void )
{
<#assign x=CONFIG_GFX_HGC_NUM_SCHEMES>
<#list 0..x-1 as i>
    <@GFX_HGC_SCHEME_INIT
        INDEX = "${i}"
        GFX_SCHEME_ALPHA = "GFX_SCHEME_ALPHA_${i}"
        GFX_SCHEME_PRIMARY_COLOR = "GFX_SCHEME_PRIMARY_COLOR_RED_${i}, GFX_SCHEME_PRIMARY_COLOR_GREEN_${i}, GFX_SCHEME_PRIMARY_COLOR_BLUE_${i}"
        GFX_SCHEME_SECONDARY_COLOR = "GFX_SCHEME_SECONDARY_COLOR_RED_${i}, GFX_SCHEME_SECONDARY_COLOR_GREEN_${i}, GFX_SCHEME_SECONDARY_COLOR_BLUE_${i}"
        GFX_SCHEME_DISABLED_COLOR = "GFX_SCHEME_DISABLED_COLOR_RED_${i}, GFX_SCHEME_DISABLED_COLOR_GREEN_${i}, GFX_SCHEME_DISABLED_COLOR_BLUE_${i}"
        GFX_SCHEME_BACKGROUND_COLOR = "GFX_SCHEME_BACKGROUND_COLOR_RED_${i}, GFX_SCHEME_BACKGROUND_COLOR_GREEN_${i}, GFX_SCHEME_BACKGROUND_COLOR_BLUE_${i}"
        GFX_SCHEME_EMBOSS_SIZE = "GFX_SCHEME_EMBOSS_SIZE_${i}"
		GFX_SCHEME_EMBOSS_DARK_COLOR = "GFX_SCHEME_EMBOSS_DARK_COLOR_RED_${i}, GFX_SCHEME_EMBOSS_DARK_COLOR_GREEN_${i}, GFX_SCHEME_EMBOSS_DARK_COLOR_BLUE_${i}"
        GFX_SCHEME_EMBOSS_LIGHT_COLOR = "GFX_SCHEME_EMBOSS_LIGHT_COLOR_RED_${i}, GFX_SCHEME_EMBOSS_LIGHT_COLOR_GREEN_${i}, GFX_SCHEME_EMBOSS_LIGHT_COLOR_BLUE_${i}"
        GFX_SCHEME_TEXT_PRIMARY_COLOR = "GFX_SCHEME_TEXT_PRIMARY_COLOR_RED_${i}, GFX_SCHEME_TEXT_PRIMARY_COLOR_GREEN_${i}, GFX_SCHEME_TEXT_PRIMARY_COLOR_BLUE_${i}"
        GFX_SCHEME_TEXT_SECONDARY_COLOR = "GFX_SCHEME_TEXT_SECONDARY_COLOR_RED_${i}, GFX_SCHEME_TEXT_SECONDARY_COLOR_GREEN_${i}, GFX_SCHEME_TEXT_SECONDARY_COLOR_BLUE_${i}"
        GFX_SCHEME_TEXT_DISABLED_COLOR = "GFX_SCHEME_TEXT_DISABLED_COLOR_RED_${i}, GFX_SCHEME_TEXT_DISABLED_COLOR_GREEN_${i}, GFX_SCHEME_TEXT_DISABLED_COLOR_BLUE_${i}"
		GFX_SCHEME_GRADIENT_START_COLOR = "GFX_SCHEME_GRADIENT_START_COLOR_RED_${i}, GFX_SCHEME_GRADIENT_START_COLOR_GREEN_${i}, GFX_SCHEME_GRADIENT_START_COLOR_BLUE_${i}"
		GFX_SCHEME_GRADIENT_END_COLOR = "GFX_SCHEME_GRADIENT_END_COLOR_RED_${i}, GFX_SCHEME_GRADIENT_END_COLOR_GREEN_${i}, GFX_SCHEME_GRADIENT_END_COLOR_BLUE_${i}"
        GFX_SCHEME_BACKGROUND_OFFSET_TOP = "GFX_SCHEME_BACKGROUND_OFFSET_TOP_${i}"
        GFX_SCHEME_BACKGROUND_OFFSET_LEFT = "GFX_SCHEME_BACKGROUND_OFFSET_LEFT_${i}"
        GFX_SCHEME_FONT_RESOURCE = "GFX_SCHEME_FONT_RESOURCE_${i}"
        GFX_SCHEME_BACK_IMAGE_RESOURCE = "GFX_SCHEME_BACK_IMAGE_RESOURCE_${i}"
		GFX_SCHEME_FILL_STYLE = "GFX_SCHEME_FILL_STYLE_${i}"
		GFX_SCHEME_BACKGROUND_TYPE = "GFX_SCHEME_BACKGROUND_TYPE_${i}"
        />
</#list>
}

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
bool GFX_HGC_MessageCallback(GFX_GOL_TRANSLATED_ACTION objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    // process messages for demo screens
    switch (hgcObj.screenState)
    {
<#assign x=CONFIG_GFX_HGC_NUM_SCREENS>
<#list 0..x-1 as i>
    <@GFX_HGC_SCREEN_EVENT SCR_ID = "CONFIG_GFX_HGC_SCREEN_ID_${i}" />
</#list>
      default:
            // process message by default
            return true;
    }
    return true;
}

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
bool GFX_HGC_DrawCallback( void )
{
    switch (hgcObj.screenState)
    {
        case HGC_SCREEN_STATE_INIT:
            //Draw the primary screen as selected in the Composer
            GFX_HGC_SetScreenState(HGC_SCREEN_STATE_SETUP_SCREEN_${CONFIG_GFX_HGC_PRIMARY_SCREEN_ID});
            return true;
<#assign x=CONFIG_GFX_HGC_NUM_SCREENS>
<#list 0..x-1 as i>
    <@GFX_HGC_SCREEN_STATE_TRANSITION SCR_ID = "CONFIG_GFX_HGC_SCREEN_ID_${i}" INDEX = "${i}"/>
</#list>			
        default:
            return true; // release drawing control to GOL by default
    }

    return true; // release drawing control to GOL
}

<#else>
/******************************************************************************
  Function: 
    void GFX_HGC_DrawScreenTask( void )

  Remarks: 
    Task loop to drive the HGC generated screen state machine for HGC design
    that has primitives only
 */
void GFX_HGC_DrawScreenTask( void )
{
    switch (hgcObj.screenState)
    {
        case HGC_SCREEN_STATE_INIT:
            //Draw the primary screen as selected in the Composer
            GFX_HGC_SetScreenState(HGC_SCREEN_STATE_SETUP_SCREEN_${CONFIG_GFX_HGC_PRIMARY_SCREEN_ID});
            break;
<#assign x=CONFIG_GFX_HGC_NUM_SCREENS>
<#list 0..x-1 as i>
    <@GFX_HGC_SCREEN_STATE_TRANSITION  INDEX = "${i}" SCR_ID = "CONFIG_GFX_HGC_SCREEN_ID_${i}"/>
</#list>			
        default:
            break;
    }
}

</#if>
/******************************************************************************
  Function: 
    void GFX_HGC_SetupScreen( uint8_t  screenId )

  Remarks: 
    Clears current screen and starts a fresh screen with its background color
 */
void GFX_HGC_SetupScreen(uint8_t screenId)
{
    switch (screenId)
    {
<#assign x=CONFIG_GFX_HGC_NUM_SCREENS>
<#list 0..x-1 as i>
    <@GFX_HGC_SETUP_SCREEN 
		SCR_ID = "CONFIG_GFX_HGC_SCREEN_ID_${i}"?eval
		RED = "CONFIG_GFX_HGC_SCREEN_BKGRD_COLOR_RED_${i}"?eval
		GREEN = "CONFIG_GFX_HGC_SCREEN_BKGRD_COLOR_GREEN_${i}"?eval
		BLUE = "CONFIG_GFX_HGC_SCREEN_BKGRD_COLOR_BLUE_${i}"?eval
		AUTOCLEAR = ("CONFIG_GFX_HGC_SCREEN_AUTOCLEAR_${i}"?eval) />
</#list>			
        default:
            break;
    }
}


/******************************************************************************
  Function: 
    bool GFX_HGC_ChangeScreen( uint8_t  screenId )

  Output: 
    Returns true if a screenId matches an existing screen identifier

  Remarks: 
    Can be called to initiate GFX Library to draw a new screen
 */
bool GFX_HGC_ChangeScreen(uint8_t screenId)
{
    switch (screenId)
    {
<#assign x=CONFIG_GFX_HGC_NUM_SCREENS>
<#list 0..x-1 as i>
    <@GFX_HGC_CHANGE_SCREEN SCR_ID = "CONFIG_GFX_HGC_SCREEN_ID_${i}" />
</#list>			
        default:
            return false;
    }

    return true; // release drawing control to GOL
}

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
bool GFX_HGC_DrawScreen_GOL(uint8_t screenId)
{
    switch (screenId)
    {
<#assign x=CONFIG_GFX_HGC_NUM_SCREENS>
<#list 0..x-1 as i>
    <@GFX_HGC_SCREEN_DRAW_GOL 
        SCREEN_INDEX = "${i}"
        SCREEN_ID = "CONFIG_GFX_HGC_SCREEN_ID_${i}"
        SCREEN_NUM_ITEMS  = "CONFIG_GFX_HGC_SCREEN_NUM_GOL_ITEMS_${i}"/>
</#list>			
        default:
            return false;
    }

    return true; // release drawing control to GOL
}


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
bool GFX_HGC_DrawScreen_Primitives(uint8_t screenId)
{
    switch (screenId)
    {
<#assign x=CONFIG_GFX_HGC_NUM_SCREENS>
<#list 0..x-1 as i>
    <@GFX_HGC_SCREEN_DRAW_PRIMITIVES 
        SCREEN_INDEX = "${i}"
        SCREEN_ID = "CONFIG_GFX_HGC_SCREEN_ID_${i}"
        SCREEN_NUM_ITEMS  = "CONFIG_GFX_HGC_SCREEN_NUM_PRIMITIVE_ITEMS_${i}"/>
</#list>			
        default:
            return true;
    }

    return true; // release drawing control to GOL
}


/******************************************************************************
  Function: 
    bool GFX_HGC_DrawItem(int itemId)

  Output:
    Returns true if a itemId matches an existing item identifier

  Remarks: 
    Every item specified in every screen in HGC is listed in this function
 */
bool GFX_HGC_DrawItem(int itemId)
{
    switch(itemId)
    {
<#if CONFIG_GFX_HGC_HAS_BUTTONS = true>
<#assign x=CONFIG_GFX_HGC_NUM_BUTTONS>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_BUTTON
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_BUTTON_ID = "CONFIG_HGC_BTN_ID_${i}"
        GFX_BUTTON_LEFT = "GFX_BUTTON_LEFT_${i}"
        GFX_BUTTON_TOP = "GFX_BUTTON_TOP_${i}"
        GFX_BUTTON_RIGHT = "GFX_BUTTON_RIGHT_${i}"
        GFX_BUTTON_BOTTOM = "GFX_BUTTON_BOTTOM_${i}"
        GFX_BUTTON_RADIUS = "GFX_BUTTON_RADIUS_${i}"
        GFX_BUTTON_STATE = "GFX_BUTTON_STATE_${i}"
        GFX_BUTTON_PRESS_IMAGE = "GFX_BUTTON_PRESS_IMAGE_${i}"
        GFX_BUTTON_RELEASE_IMAGE = "GFX_BUTTON_RELEASE_IMAGE_${i}"
        GFX_BUTTON_TEXT = "GFX_BUTTON_TEXT_${i}"
        GFX_BUTTON_ALIGNMENT = "GFX_BUTTON_ALIGNMENT_${i}"
        GFX_BUTTON_SCHEME = "GFX_BUTTON_SCHEME_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_DGTL_MTRS = true>
<#assign x=CONFIG_GFX_HGC_NUM_DGTL_MTRS>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_DGTL_MTR
        GFX_INDEX = "GFX_INDEX_0"
        GFX_DGTL_MTR_ID = "CONFIG_HGC_DGTL_MTR_ID_${i}"
        GFX_DGTL_MTR_LEFT = "GFX_DGTL_MTR_LEFT_${i}"
        GFX_DGTL_MTR_TOP = "GFX_DGTL_MTR_TOP_${i}"
        GFX_DGTL_MTR_RIGHT = "GFX_DGTL_MTR_RIGHT_${i}"
        GFX_DGTL_MTR_BOTTOM = "GFX_DGTL_MTR_BOTTOM_${i}"
		GFX_DGTL_MTR_STATE = "GFX_DGTL_MTR_STATE_${i}"
		GFX_DGTL_MTR_VALUE = "GFX_DGTL_MTR_VALUE_${i}"
        GFX_DGTL_MTR_NO_OF_DIGITS = "GFX_DGTL_MTR_NO_OF_DIGITS_${i}"
        GFX_DGTL_MTR_DOT_POSITION = "GFX_DGTL_MTR_DOT_POSITION_${i}"
        GFX_DGTL_MTR_ALIGNMENT = "GFX_DGTL_MTR_ALIGNMENT_${i}"
        GFX_DGTL_MTR_SCHEME = "GFX_DGTL_MTR_SCHEME_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_CHECKBOXES = true>
<#assign x=CONFIG_GFX_HGC_NUM_CHECKBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_CHECKBOX
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_CHECKBOX_ID = "CONFIG_HGC_CHECKBOX_ID_${i}"
        GFX_CHECKBOX_LEFT = "GFX_CHECKBOX_LEFT_${i}"
        GFX_CHECKBOX_TOP = "GFX_CHECKBOX_TOP_${i}"
        GFX_CHECKBOX_RIGHT = "GFX_CHECKBOX_RIGHT_${i}"
        GFX_CHECKBOX_BOTTOM = "GFX_CHECKBOX_BOTTOM_${i}"
		GFX_CHECKBOX_TEXT = "GFX_CHECKBOX_TEXT_${i}"
        GFX_CHECKBOX_STATE = "GFX_CHECKBOX_STATE_${i}"
        GFX_CHECKBOX_ALIGNMENT = "GFX_CHECKBOX_ALIGNMENT_${i}"
        GFX_CHECKBOX_SCHEME = "GFX_CHECKBOX_SCHEME_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_RADIOBUTTONS = true>
<#assign x=CONFIG_GFX_HGC_NUM_RADIOBUTTONS>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_RADIOBUTTON
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_RADIOBUTTON_ID = "CONFIG_HGC_RADIOBUTTON_ID_${i}"
        GFX_RADIOBUTTON_LEFT = "GFX_RADIOBUTTON_LEFT_${i}"
        GFX_RADIOBUTTON_TOP = "GFX_RADIOBUTTON_TOP_${i}"
        GFX_RADIOBUTTON_RIGHT = "GFX_RADIOBUTTON_RIGHT_${i}"
        GFX_RADIOBUTTON_BOTTOM = "GFX_RADIOBUTTON_BOTTOM_${i}"
		GFX_RADIOBUTTON_TEXT = "GFX_RADIOBUTTON_TEXT_${i}"
        GFX_RADIOBUTTON_STATE = "GFX_RADIOBUTTON_STATE_${i}"
        GFX_RADIOBUTTON_ALIGNMENT = "GFX_RADIOBUTTON_ALIGNMENT_${i}"
        GFX_RADIOBUTTON_SCHEME = "GFX_RADIOBUTTON_SCHEME_${i}"
        GFX_RADIOBUTTON_GROUPNO = "GFX_RADIOBUTTON_GROUPNO_${i}"
        GFX_RADIOBUTTON_NUM_GROUPS_ON_SCREEN = "GFX_RADIOBUTTON_NUM_GROUPS_ON_SCREEN_${i}"
        />
</#list>
</#if>	
<#if CONFIG_GFX_HGC_HAS_SCROLLBARS = true>
<#assign x=CONFIG_GFX_HGC_NUM_SCROLLBARS>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_SCROLLBAR
        GFX_INDEX = "GFX_INDEX_0"
        GFX_SCROLLBAR_ID = "CONFIG_HGC_SCROLLBAR_ID_${i}"
        GFX_SCROLLBAR_LEFT = "GFX_SCROLLBAR_LEFT_${i}"
        GFX_SCROLLBAR_TOP = "GFX_SCROLLBAR_TOP_${i}"
        GFX_SCROLLBAR_RIGHT = "GFX_SCROLLBAR_RIGHT_${i}"
        GFX_SCROLLBAR_BOTTOM = "GFX_SCROLLBAR_BOTTOM_${i}"
		GFX_SCROLLBAR_STATE = "GFX_SCROLLBAR_STATE_${i}"
		GFX_SCROLLBAR_RANGE = "GFX_SCROLLBAR_RANGE_${i}"
		GFX_SCROLLBAR_PAGE = "GFX_SCROLLBAR_PAGE_${i}"
		GFX_SCROLLBAR_POS = "GFX_SCROLLBAR_POS_${i}"
        GFX_SCROLLBAR_SCHEME = "GFX_SCROLLBAR_SCHEME_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_PROGRESSBARS = true>
<#assign x=CONFIG_GFX_HGC_NUM_PROGRESSBARS>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_PROGRESSBAR
        GFX_INDEX = "GFX_INDEX_0"
        GFX_PROGRESSBAR_ID = "CONFIG_HGC_PROGRESSBAR_ID_${i}"
        GFX_PROGRESSBAR_LEFT = "GFX_PROGRESSBAR_LEFT_${i}"
        GFX_PROGRESSBAR_TOP = "GFX_PROGRESSBAR_TOP_${i}"
        GFX_PROGRESSBAR_RIGHT = "GFX_PROGRESSBAR_RIGHT_${i}"
        GFX_PROGRESSBAR_BOTTOM = "GFX_PROGRESSBAR_BOTTOM_${i}"
		GFX_PROGRESSBAR_STATE = "GFX_PROGRESSBAR_STATE_${i}"
		GFX_PROGRESSBAR_POS = "GFX_PROGRESSBAR_POS_${i}"
		GFX_PROGRESSBAR_RANGE = "GFX_PROGRESSBAR_RANGE_${i}"				
        GFX_PROGRESSBAR_SCHEME = "GFX_PROGRESSBAR_SCHEME_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_METERS = true>
<#assign x=CONFIG_GFX_HGC_NUM_METERS>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_METER
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_METER_ID = "CONFIG_HGC_METER_ID_${i}"
        GFX_METER_LEFT = "GFX_METER_LEFT_${i}"
        GFX_METER_TOP = "GFX_METER_TOP_${i}"
        GFX_METER_RIGHT = "GFX_METER_RIGHT_${i}"
        GFX_METER_BOTTOM = "GFX_METER_BOTTOM_${i}"
		GFX_METER_STATE = "GFX_METER_STATE_${i}"
		GFX_METER_TYPE = "GFX_METER_TYPE_${i}"
		GFX_METER_VALUE = "GFX_METER_VALUE_${i}"
		GFX_METER_MIN_VALUE = "GFX_METER_MIN_VALUE_${i}"				
		GFX_METER_MAX_VALUE = "GFX_METER_MAX_VALUE_${i}"
        GFX_METER_TITLE_FONT = "CONFIG_HGC_METER_TITLEFONT_${i}"
        GFX_METER_VALUE_FONT = "CONFIG_HGC_METER_VALUEFONT_${i}"			
        GFX_METER_SCHEME = "GFX_METER_SCHEME_${i}"

        GFX_METER_COLOR1 = "GFX_METER_COLOR1_RED_${i}, GFX_METER_COLOR1_GREEN_${i}, GFX_METER_COLOR1_BLUE_${i}"
        GFX_METER_COLOR2 = "GFX_METER_COLOR2_RED_${i}, GFX_METER_COLOR2_GREEN_${i}, GFX_METER_COLOR2_BLUE_${i}"
        GFX_METER_COLOR3 = "GFX_METER_COLOR3_RED_${i}, GFX_METER_COLOR3_GREEN_${i}, GFX_METER_COLOR3_BLUE_${i}"
        GFX_METER_COLOR3 = "GFX_METER_COLOR3_RED_${i}, GFX_METER_COLOR3_GREEN_${i}, GFX_METER_COLOR3_BLUE_${i}"
        GFX_METER_COLOR4 = "GFX_METER_COLOR4_RED_${i}, GFX_METER_COLOR4_GREEN_${i}, GFX_METER_COLOR4_BLUE_${i}"
        GFX_METER_COLOR5 = "GFX_METER_COLOR5_RED_${i}, GFX_METER_COLOR5_GREEN_${i}, GFX_METER_COLOR5_BLUE_${i}"
        GFX_METER_COLOR6 = "GFX_METER_COLOR6_RED_${i}, GFX_METER_COLOR6_GREEN_${i}, GFX_METER_COLOR6_BLUE_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_EDITBOXES = true>
<#assign x=CONFIG_GFX_HGC_NUM_EDITBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_EDITBOX
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_EDITBOX_ID = "CONFIG_HGC_EDITBOX_ID_${i}"
        GFX_EDITBOX_LEFT = "GFX_EDITBOX_LEFT_${i}"
        GFX_EDITBOX_TOP = "GFX_EDITBOX_TOP_${i}"
        GFX_EDITBOX_RIGHT = "GFX_EDITBOX_RIGHT_${i}"
        GFX_EDITBOX_BOTTOM = "GFX_EDITBOX_BOTTOM_${i}"
		GFX_EDITBOX_STATE = "GFX_EDITBOX_STATE_${i}"
		GFX_EDITBOX_TEXT = "GFX_EDITBOX_TEXT_${i}"
        GFX_EDITBOX_NOOFCHARS = "GFX_EDITBOX_NOOFCHARS_${i}"
        GFX_EDITBOX_ALIGNMENT = "GFX_EDITBOX_ALIGNMENT_${i}"
        GFX_EDITBOX_SCHEME = "GFX_EDITBOX_SCHEME_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_LISTBOXES = true>
<#assign x=CONFIG_GFX_HGC_NUM_LISTBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_LISTBOX
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_LISTBOX_ID = "CONFIG_HGC_LISTBOX_ID_${i}"
        GFX_LISTBOX_LEFT = "GFX_LISTBOX_LEFT_${i}"
        GFX_LISTBOX_TOP = "GFX_LISTBOX_TOP_${i}"
        GFX_LISTBOX_RIGHT = "GFX_LISTBOX_RIGHT_${i}"
        GFX_LISTBOX_BOTTOM = "GFX_LISTBOX_BOTTOM_${i}"
		GFX_LISTBOX_STATE = "GFX_LISTBOX_STATE_${i}"
        GFX_LISTBOX_ALIGNMENT = "GFX_LISTBOX_ALIGNMENT_${i}"
        GFX_LISTBOX_SCHEME = "GFX_LISTBOX_SCHEME_${i}"
		GFX_LISTBOX_ITEM_COUNT = "CONFIG_HGC_LISTBOX_ITEM_COUNT_${i}"
		GFX_LISTBOX_ITEM_FOCUS = "CONFIG_HGC_LISTBOX_ITEM_FOCUS_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_GROUPBOXES = true>
<#assign x=CONFIG_GFX_HGC_NUM_GROUPBOXES>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_GROUPBOX
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_GROUPBOX_ID = "CONFIG_HGC_GROUPBOX_ID_${i}"
        GFX_GROUPBOX_LEFT = "GFX_GROUPBOX_LEFT_${i}"
        GFX_GROUPBOX_TOP = "GFX_GROUPBOX_TOP_${i}"
        GFX_GROUPBOX_RIGHT = "GFX_GROUPBOX_RIGHT_${i}"
        GFX_GROUPBOX_BOTTOM = "GFX_GROUPBOX_BOTTOM_${i}"
		GFX_GROUPBOX_STATE = "GFX_GROUPBOX_STATE_${i}"
        GFX_GROUPBOX_SCHEME = "GFX_GROUPBOX_SCHEME_${i}"
		GFX_GROUPBOX_TEXT = "CONFIG_HGC_GROUPBOX_TEXT_${i}"
		GFX_GROUPBOX_ALIGNMENT = "GFX_GROUPBOX_ALIGNMENT_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_STATICTEXTS = true>
<#assign x=CONFIG_GFX_HGC_NUM_STATICTEXTS>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_STATICTEXT
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_STATICTEXT_ID = "CONFIG_HGC_STATICTEXT_ID_${i}"
        GFX_STATICTEXT_LEFT = "GFX_STATICTEXT_LEFT_${i}"
        GFX_STATICTEXT_TOP = "GFX_STATICTEXT_TOP_${i}"
        GFX_STATICTEXT_RIGHT = "GFX_STATICTEXT_RIGHT_${i}"
        GFX_STATICTEXT_BOTTOM = "GFX_STATICTEXT_BOTTOM_${i}"
		GFX_STATICTEXT_STATE = "GFX_STATICTEXT_STATE_${i}"
		GFX_STATICTEXT_TEXT = "GFX_STATICTEXT_TEXT_${i}"
        GFX_STATICTEXT_FRAME = "GFX_STATICTEXT_FRAME_${i}"
        GFX_STATICTEXT_ALIGNMENT = "GFX_STATICTEXT_ALIGNMENT_${i}"
        GFX_STATICTEXT_SCHEME = "GFX_STATICTEXT_SCHEME_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_TEXTENTRYS = true>
<#assign x=CONFIG_GFX_HGC_NUM_TEXTENTRYS>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_TEXTENTRY
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_TEXTENTRY_ID = "CONFIG_HGC_TEXTENTRY_ID_${i}"
        GFX_TEXTENTRY_LEFT = "HGC_TEXTENTRY_LEFT_${i}"
        GFX_TEXTENTRY_TOP = "HGC_TEXTENTRY_TOP_${i}"
        GFX_TEXTENTRY_RIGHT = "HGC_TEXTENTRY_RIGHT_${i}"
        GFX_TEXTENTRY_BOTTOM = "HGC_TEXTENTRY_BOTTOM_${i}"
		GFX_TEXTENTRY_STATE = "HGC_TEXTENTRY_STATE_${i}"
		GFX_TEXTENTRY_SCHEME = "HGC_TEXTENTRY_SCHEME_${i}"
		GFX_TEXTENTRY_BUFFERSIZE = "HGC_TEXTENTRY_BUFFERSIZE_${i}"
		GFX_TEXTENTRY_FONT_ID = "CONFIG_HGC_TEXTENTRY_FONT_${i}"
        GFX_TEXTENTRY_ALIGNMENT = "HGC_TEXTENTRY_ALIGNMENT_${i}"
		GFX_TEXTENTRY_ROW_COUNT = "HGC_TEXTENTRY_ROW_COUNT_${i}"
		GFX_TEXTENTRY_COLUMN_COUNT = "HGC_TEXTENTRY_COLUMN_COUNT_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_WINDOWS = true>
<#assign x=CONFIG_GFX_HGC_NUM_WINDOWS>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_WINDOW
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_WINDOW_ID = "CONFIG_HGC_WINDOW_ID_${i}"
        GFX_WINDOW_LEFT = "GFX_WINDOW_LEFT_${i}"
        GFX_WINDOW_TOP = "GFX_WINDOW_TOP_${i}"
        GFX_WINDOW_RIGHT = "GFX_WINDOW_RIGHT_${i}"
        GFX_WINDOW_BOTTOM = "GFX_WINDOW_BOTTOM_${i}"
		GFX_WINDOW_STATE = "GFX_WINDOW_STATE_${i}"
		GFX_WINDOW_IMAGE = "GFX_WINDOW_IMAGE_${i}"
		GFX_WINDOW_TEXT = "GFX_WINDOW_TEXT_${i}"       
        GFX_WINDOW_ALIGNMENT = "GFX_WINDOW_ALIGNMENT_${i}"
        GFX_WINDOW_SCHEME = "GFX_WINDOW_SCHEME_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_PICTURES = true>
<#assign x=CONFIG_GFX_HGC_NUM_PICTURES>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_PICTURE
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_PICTURE_ID = "CONFIG_HGC_PICTURE_ID_${i}"
        GFX_PICTURE_LEFT = "GFX_PICTURE_LEFT_${i}"
        GFX_PICTURE_TOP = "GFX_PICTURE_TOP_${i}"
        GFX_PICTURE_RIGHT = "GFX_PICTURE_RIGHT_${i}"
        GFX_PICTURE_BOTTOM = "GFX_PICTURE_BOTTOM_${i}"
		GFX_PICTURE_STATE = "GFX_PICTURE_STATE_${i}"
		GFX_PICTURE_SCALE = "GFX_PICTURE_SCALE_${i}"
		GFX_PICTURE_IMAGE = "CONFIG_HGC_PICTURE_IMAGE_${i}"
        GFX_PICTURE_SCHEME = "GFX_PICTURE_SCHEME_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_LINES = true>
<#assign x=CONFIG_GFX_HGC_NUM_LINES>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_LINE
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_LINE_ID = "CONFIG_GFX_HGC_LINE_ID_${i}"
        HGC_LINE_P1X = "CONFIG_HGC_LINE_P1X_${i}"
        HGC_LINE_P1Y = "CONFIG_HGC_LINE_P1Y_${i}"
        HGC_LINE_P2X = "CONFIG_HGC_LINE_P2X_${i}"
        HGC_LINE_P2Y = "CONFIG_HGC_LINE_P2Y_${i}"
		GFX_LINE_STYLE = "CONFIG_HGC_LINE_STYLE_${i}"
        HGC_LINE_RED   = "CONFIG_HGC_LINE_RED_${i}"
        HGC_LINE_GREEN = "CONFIG_HGC_LINE_GREEN_${i}"
        HGC_LINE_BLUE  = "CONFIG_HGC_LINE_BLUE_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_RECTANGLES = true>
<#assign x=CONFIG_GFX_HGC_NUM_RECTANGLES>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_RECTANGLE
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_RECTANGLE_ID = "CONFIG_GFX_HGC_RECTANGLE_ID_${i}"
		HGC_RECTANGLE_P1X = "CONFIG_HGC_RECTANGLE_P1X_${i}"
        HGC_RECTANGLE_P1Y = "CONFIG_HGC_RECTANGLE_P1Y_${i}"
        HGC_RECTANGLE_P2X = "CONFIG_HGC_RECTANGLE_P2X_${i}"
        HGC_RECTANGLE_P2Y = "CONFIG_HGC_RECTANGLE_P2Y_${i}"
		HGC_RECTANGLE_RADIUS = "CONFIG_HGC_RECTANGLE_RADIUS_${i}"
		HGC_RECTANGLE_OUTLINE = "CONFIG_HGC_RECTANGLE_OUTLINE_${i}"
		HGC_RECTANGLE_OUTLINE_STYLE = "CONFIG_HGC_RECTANGLE_OUTLINE_STYLE_${i}"
        HGC_RECTANGLE_OUTLINE_RED = "CONFIG_HGC_RECTANGLE_OUTLINE_RED_${i}"
        HGC_RECTANGLE_OUTLINE_GREEN = "CONFIG_HGC_RECTANGLE_OUTLINE_GREEN_${i}"
        HGC_RECTANGLE_OUTLINE_BLUE = "CONFIG_HGC_RECTANGLE_OUTLINE_BLUE_${i}"
		HGC_RECTANGLE_FILL_STYLE = "CONFIG_HGC_RECTANGLE_FILL_STYLE_${i}"
		HGC_RECTANGLE_FILL_RED = "CONFIG_HGC_RECTANGLE_FILL_RED_${i}"
        HGC_RECTANGLE_FILL_GREEN = "CONFIG_HGC_RECTANGLE_FILL_GREEN_${i}"
        HGC_RECTANGLE_FILL_BLUE = "CONFIG_HGC_RECTANGLE_FILL_BLUE_${i}"
		HGC_RECTANGLE_ALPHA = "CONFIG_HGC_RECTANGLE_ALPHA_${i}"
		HGC_RECTANGLE_START_RED = "CONFIG_HGC_RECTANGLE_GRADIENT_START_RED_${i}"
		HGC_RECTANGLE_START_GREEN = "CONFIG_HGC_RECTANGLE_GRADIENT_START_GREEN_${i}"
		HGC_RECTANGLE_START_BLUE = "CONFIG_HGC_RECTANGLE_GRADIENT_START_BLUE_${i}"
		HGC_RECTANGLE_END_RED = "CONFIG_HGC_RECTANGLE_GRADIENT_END_RED_${i}"
		HGC_RECTANGLE_END_GREEN = "CONFIG_HGC_RECTANGLE_GRADIENT_END_GREEN_${i}"
		HGC_RECTANGLE_END_BLUE = "CONFIG_HGC_RECTANGLE_GRADIENT_END_BLUE_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_CIRCLES = true>
<#assign x=CONFIG_GFX_HGC_NUM_CIRCLES>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_CIRCLE
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_CIRCLE_ID = "CONFIG_GFX_HGC_CIRCLE_ID_${i}"
		HGC_CIRCLE_ORIGIN_X = "CONFIG_HGC_CIRCLE_ORIGIN_X_${i}"
        HGC_CIRCLE_ORIGIN_Y = "CONFIG_HGC_CIRCLE_ORIGIN_Y_${i}"
		HGC_CIRCLE_RADIUS = "CONFIG_HGC_CIRCLE_RADIUS_${i}"
		HGC_CIRCLE_OUTLINE = "CONFIG_HGC_CIRCLE_OUTLINE_${i}"
		HGC_CIRCLE_OUTLINE_STYLE = "CONFIG_HGC_CIRCLE_OUTLINE_STYLE_${i}"
        HGC_CIRCLE_OUTLINE_RED = "CONFIG_HGC_CIRCLE_OUTLINE_RED_${i}"
        HGC_CIRCLE_OUTLINE_GREEN = "CONFIG_HGC_CIRCLE_OUTLINE_GREEN_${i}"
        HGC_CIRCLE_OUTLINE_BLUE = "CONFIG_HGC_CIRCLE_OUTLINE_BLUE_${i}"
		HGC_CIRCLE_FILL_STYLE = "CONFIG_HGC_CIRCLE_FILL_STYLE_${i}"
		HGC_CIRCLE_FILL_RED = "CONFIG_HGC_CIRCLE_FILL_RED_${i}"
        HGC_CIRCLE_FILL_GREEN = "CONFIG_HGC_CIRCLE_FILL_GREEN_${i}"
        HGC_CIRCLE_FILL_BLUE = "CONFIG_HGC_CIRCLE_FILL_BLUE_${i}"
		HGC_CIRCLE_ALPHA = "CONFIG_HGC_CIRCLE_ALPHA_${i}"
		HGC_CIRCLE_START_RED = "CONFIG_HGC_CIRCLE_GRADIENT_START_RED_${i}"
		HGC_CIRCLE_START_GREEN = "CONFIG_HGC_CIRCLE_GRADIENT_START_GREEN_${i}"
		HGC_CIRCLE_START_BLUE = "CONFIG_HGC_CIRCLE_GRADIENT_START_BLUE_${i}"
		HGC_CIRCLE_END_RED = "CONFIG_HGC_CIRCLE_GRADIENT_END_RED_${i}"
		HGC_CIRCLE_END_GREEN = "CONFIG_HGC_CIRCLE_GRADIENT_END_GREEN_${i}"
		HGC_CIRCLE_END_BLUE = "CONFIG_HGC_CIRCLE_GRADIENT_END_BLUE_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_IMAGES = true>
<#assign x=CONFIG_GFX_HGC_NUM_IMAGES>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_IMAGE
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_IMAGE_ID = "CONFIG_GFX_HGC_IMAGE_ID_${i}"
		HGC_IMAGE_ORIGIN_X = "CONFIG_HGC_IMAGE_ORIGIN_X_${i}"
        HGC_IMAGE_ORIGIN_Y = "CONFIG_HGC_IMAGE_ORIGIN_Y_${i}"
		HGC_IMAGE_IMAGE_ID = "CONFIG_GFX_HGC_IMAGE_IMAGE_ID_${i}"
		HGC_IMAGE_TRANSPARENCY_RED = "CONFIG_HGC_IMAGE_TRANSPARENCY_RED_${i}"
		HGC_IMAGE_TRANSPARENCY_GREEN = "CONFIG_HGC_IMAGE_TRANSPARENCY_GREEN_${i}"
		HGC_IMAGE_TRANSPARENCY_BLUE = "CONFIG_HGC_IMAGE_TRANSPARENCY_BLUE_${i}"
        HGC_IMAGE_CLIP_X = "CONFIG_HGC_IMAGE_CLIP_X_${i}"
        HGC_IMAGE_CLIP_Y = "CONFIG_HGC_IMAGE_CLIP_Y_${i}"
        HGC_IMAGE_CLIP_WIDTH = "CONFIG_HGC_IMAGE_CLIP_WIDTH_${i}"
		HGC_IMAGE_CLIP_HEIGHT = "CONFIG_HGC_IMAGE_CLIP_HEIGHT_${i}"
        />
</#list>
</#if>
<#if CONFIG_GFX_HGC_HAS_TEXTS = true>
<#assign x=CONFIG_GFX_HGC_NUM_TEXTS>
<#list 0..x-1 as i>
    <@GFX_HGC_CREATE_TEXT
        INDEX = "${i}"
        GFX_INDEX = "GFX_INDEX_0"
        GFX_TEXT_ID = "CONFIG_GFX_HGC_TEXT_ID_${i}"
		HGC_TEXT_ORIGIN_X = "CONFIG_HGC_TEXT_ORIGIN_X_${i}"
        HGC_TEXT_ORIGIN_Y = "CONFIG_HGC_TEXT_ORIGIN_Y_${i}"
		HGC_TEXT_STRING = "CONFIG_HGC_TEXT_STRING_${i}"
		HGC_TEXT_FONT_ID = "CONFIG_GFX_HGC_TEXT_FONT_ID_${i}"
		HGC_TEXT_COLOR_RED = "CONFIG_HGC_TEXT_COLOR_RED_${i}"
		HGC_TEXT_COLOR_GREEN = "CONFIG_HGC_TEXT_COLOR_GREEN_${i}"
		HGC_TEXT_COLOR_BLUE = "CONFIG_HGC_TEXT_COLOR_BLUE_${i}"
        HGC_TEXT_CLIP_X = "CONFIG_HGC_TEXT_CLIP_X_${i}"
        HGC_TEXT_CLIP_Y = "CONFIG_HGC_TEXT_CLIP_Y_${i}"
		HGC_TEXT_ALIGNMENT = "CONFIG_HGC_TEXT_ALIGNMENT_${i}"
        />
</#list>
</#if>
	default:
		return false; // process by default
    }

    return true;
}

<#if CONFIG_GFX_HGC_HAS_BUTTONS = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_MsgButtons(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)

  Output:
    Returns true if a Object ID matches an existing item identifier

  Remarks: 
    Handles GFX GOL Button events
 */
bool GFX_HGC_MsgButtons(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
<#assign x=CONFIG_GFX_HGC_NUM_BUTTONS>
<#list 0..x-1 as i>
<#if "CONFIG_HGC_BTN_${i}_EVENT_PRESSED_ACTION_COUNT"?eval?? ||
     "CONFIG_HGC_BTN_${i}_EVENT_STILLPRESSED_ACTION_COUNT"?eval?? == true||
	 "CONFIG_HGC_BTN_${i}_EVENT_RELEASED_ACTION_COUNT"?eval?? == true ||
	 "CONFIG_HGC_BTN_${i}_EVENT_CANCELPRESS_ACTION_COUNT"?eval?? == true>
    <@GFX_HGC_BUTTON_GENERATE_EVENTS
        GFX_BUTTON_ID = "CONFIG_HGC_BTN_ID_${i}"
		GFX_INDEX = "GFX_INDEX_0"
		GFX_BUTTON_INDEX = "${i}"
		GFX_BTN_PRESSED_EVENT_ACTION_COUNT       = "CONFIG_HGC_BTN_${i}_EVENT_PRESSED_ACTION_COUNT"
		GFX_BTN_STILLPRESSED_EVENT_ACTION_COUNT = "CONFIG_HGC_BTN_${i}_EVENT_STILLPRESSED_ACTION_COUNT"
		GFX_BTN_RELEASED_EVENT_ACTION_COUNT      = "CONFIG_HGC_BTN_${i}_EVENT_RELEASED_ACTION_COUNT"
		GFX_BTN_CANCELPRESS_EVENT_ACTION_COUNT  = "CONFIG_HGC_BTN_${i}_EVENT_CANCELPRESS_ACTION_COUNT"
        />
</#if>
</#list>
        default:
            return false; // process by default
    }

    return true;
}

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
bool GFX_HGC_MsgDigitalMeters(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
<#assign x=CONFIG_GFX_HGC_NUM_DGTL_MTRS>
<#list 0..x-1 as i>
<#if "CONFIG_HGC_DGTL_MTR_${i}_EVENT_SELECTED_ACTION_COUNT"?eval??>
    <@GFX_HGC_DGTL_MTR_GENERATE_EVENTS
        GFX_DGTL_MTR_ID = "CONFIG_HGC_DGTL_MTR_ID_${i}"
		GFX_INDEX = "GFX_INDEX_0"
		GFX_DGTL_MTR_INDEX = "${i}"
		GFX_DGTL_MTR_SELECTED_EVENT_ACTION_COUNT   = "CONFIG_HGC_DGTL_MTR_${i}_EVENT_SELECTED_ACTION_COUNT"
		/>
</#if>
</#list>
        default:
            return false; // default false as it is not processed
    }    
}

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
bool GFX_HGC_MsgCheckBoxes(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
<#assign x=CONFIG_GFX_HGC_NUM_CHECKBOXES>
<#list 0..x-1 as i>
<#if "CONFIG_HGC_CHECKBOX_${i}_EVENT_CHECKED_ACTION_COUNT"?eval?? ||
     "CONFIG_HGC_CHECKBOX_${i}_EVENT_UNCHECKED_ACTION_COUNT"?eval?? == true>
    <@GFX_HGC_CHECKBOX_GENERATE_EVENTS
        GFX_CHECKBOX_ID = "CONFIG_HGC_CHECKBOX_ID_${i}"
		GFX_INDEX = "GFX_INDEX_0"
		GFX_CHECKBOX_INDEX = "${i}"
		GFX_CHECKBOX_CHECKED_EVENT_ACTION_COUNT   = "CONFIG_HGC_CHECKBOX_${i}_EVENT_CHECKED_ACTION_COUNT"
		GFX_CHECKBOX_UNCHECKED_EVENT_ACTION_COUNT = "CONFIG_HGC_CHECKBOX_${i}_EVENT_UNCHECKED_ACTION_COUNT"
        />
</#if>
</#list>
        default:
            return false; // default false as it is not processed
    }    
}

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
bool GFX_HGC_MsgRadioButtons(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
<#assign x=CONFIG_GFX_HGC_NUM_RADIOBUTTONS>
<#list 0..x-1 as i>
<#if "CONFIG_HGC_RADIOBUTTON_${i}_EVENT_CHECKED_ACTION_COUNT"?eval??>
    <@GFX_HGC_RADIOBUTTON_GENERATE_EVENTS
        GFX_RADIOBUTTON_ID = "CONFIG_HGC_RADIOBUTTON_ID_${i}"
		GFX_INDEX = "GFX_INDEX_0"
		GFX_RADIOBUTTON_INDEX = "${i}"
		GFX_RADIOBUTTON_CHECKED_EVENT_ACTION_COUNT   = "CONFIG_HGC_RADIOBUTTON_${i}_EVENT_CHECKED_ACTION_COUNT"
        />
</#if>
</#list>
        default:
            return false; // default false as it is not processed
    }    
}

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
bool GFX_HGC_MsgScrollBars(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
<#assign x=CONFIG_GFX_HGC_NUM_SCROLLBARS>
<#list 0..x-1 as i>
<#if "CONFIG_HGC_SCROLLBAR_${i}_EVENT_INCREMENT_ACTION_COUNT"?eval?? ||
     "CONFIG_HGC_SCROLLBAR_${i}_EVENT_DECREMENT_ACTION_COUNT"?eval?? == true>
    <@GFX_HGC_SCROLLBAR_GENERATE_EVENTS
        GFX_SCROLLBAR_ID = "CONFIG_HGC_SCROLLBAR_ID_${i}"
		GFX_INDEX = "GFX_INDEX_0"
		GFX_SCROLLBAR_INDEX = "${i}"
		GFX_SCROLLBAR_INCREMENT_EVENT_ACTION_COUNT = "CONFIG_HGC_SCROLLBAR_${i}_EVENT_INCREMENT_ACTION_COUNT"
		GFX_SCROLLBAR_DECREMENT_EVENT_ACTION_COUNT = "CONFIG_HGC_SCROLLBAR_${i}_EVENT_DECREMENT_ACTION_COUNT"
        />
</#if>
</#list>
        default:
            return false; // default false as it is not processed
    }    
}

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
bool GFX_HGC_MsgProgressBars(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
<#assign x=CONFIG_GFX_HGC_NUM_PROGRESSBARS>
<#list 0..x-1 as i>
<#if "CONFIG_HGC_PROGRESSBAR_${i}_EVENT_SELECTED_ACTION_COUNT"?eval??>
    <@GFX_HGC_PROGRESSBAR_GENERATE_EVENTS
        GFX_PROGRESSBAR_ID = "CONFIG_HGC_PROGRESSBAR_ID_${i}"
		GFX_INDEX = "GFX_INDEX_0"
		GFX_PROGRESSBAR_INDEX = "${i}"
		GFX_PROGRESSBAR_SELECTED_EVENT_ACTION_COUNT   = "CONFIG_HGC_PROGRESSBAR_${i}_EVENT_SELECTED_ACTION_COUNT"
		/>
</#if>
</#list>
        default:
            return false; // default false as it is not processed
    }    
}

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
bool GFX_HGC_MsgEditBoxes(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
<#assign x=CONFIG_GFX_HGC_NUM_EDITBOXES>
<#list 0..x-1 as i>
<#if "CONFIG_HGC_EDITBOX_${i}_EVENT_ADD_CHAR_ACTION_COUNT"?eval?? ||
     "CONFIG_HGC_EDITBOX_${i}_EVENT_DEL_CHAR_ACTION_COUNT"?eval?? == true||
	 "CONFIG_HGC_EDITBOX_${i}_EVENT_TOUCHSCREEN_ACTION_COUNT"?eval?? == true>
    <@GFX_HGC_EDITBOX_GENERATE_EVENTS
        GFX_EDITBOX_ID = "CONFIG_HGC_EDITBOX_ID_${i}"
		GFX_INDEX = "GFX_INDEX_0"
		GFX_EDITBOX_INDEX = "${i}"
		GFX_EDITBOX_ADD_CHAR_EVENT_ACTION_COUNT       = "CONFIG_HGC_EDITBOX_${i}_EVENT_ADD_CHAR_ACTION_COUNT"
		GFX_EDITBOX_DEL_CHAR_EVENT_ACTION_COUNT = "CONFIG_HGC_EDITBOX_${i}_EVENT_DEL_CHAR_ACTION_COUNT"
		GFX_EDITBOX_TOUCHSCREEN_EVENT_ACTION_COUNT      = "CONFIG_HGC_EDITBOX_${i}_EVENT_TOUCHSCREEN_ACTION_COUNT"
		/>
</#if>
</#list>
        default:
            return false; // default false as it is not processed
    }    
}

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
bool GFX_HGC_MsgListBoxes(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
<#assign x=CONFIG_GFX_HGC_NUM_LISTBOXES>
<#list 0..x-1 as i>
<#if "CONFIG_HGC_LISTBOX_${i}_EVENT_TOUCH_ACTION_COUNT"?eval?? ||
     "CONFIG_HGC_LISTBOX_${i}_EVENT_MOVE_ACTION_COUNT"?eval?? == true||
	 "CONFIG_HGC_LISTBOX_${i}_EVENT_SELECTED_ACTION_COUNT"?eval?? == true>
    <@GFX_HGC_LISTBOX_GENERATE_EVENTS
        GFX_LISTBOX_ID = "CONFIG_HGC_LISTBOX_ID_${i}"
		GFX_INDEX = "GFX_INDEX_0"
		GFX_LISTBOX_INDEX = "${i}"
		GFX_LISTBOX_TOUCH_EVENT_ACTION_COUNT    = "CONFIG_HGC_LISTBOX_${i}_EVENT_TOUCH_ACTION_COUNT"
		GFX_LISTBOX_MOVE_EVENT_ACTION_COUNT     = "CONFIG_HGC_LISTBOX_${i}_EVENT_MOVE_ACTION_COUNT"
		GFX_LISTBOX_SELECTED_EVENT_ACTION_COUNT = "CONFIG_HGC_LISTBOX_${i}_EVENT_SELECTED_ACTION_COUNT"
		/>
</#if>
</#list>
        default:
            return false; // default false as it is not processed
    }    
}

</#if>
<#if CONFIG_GFX_HGC_HAS_GROUPBOXES = true>
/******************************************************************************
  Function: 
    bool GFX_HGC_MsgGroupBoxes(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)

  Output:
    Returns true if a Object ID matches an existing item identifier

  Remarks: 
    Handles GFX GOL Group Boxes events
 */
bool GFX_HGC_MsgGroupBoxes(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
<#assign x=CONFIG_GFX_HGC_NUM_GROUPBOXES>
<#list 0..x-1 as i>
<#if "CONFIG_HGC_GROUPBOX_${i}_EVENT_SELECTED_ACTION_COUNT"?eval?? == true>
    <@GFX_HGC_GROUPBOX_GENERATE_EVENTS
        GFX_GROUPBOX_ID = "CONFIG_HGC_GROUPBOX_ID_${i}"
		GFX_INDEX = "GFX_INDEX_0"
		GFX_GROUPBOX_INDEX = "${i}"
		GFX_GROUPBOX_SELECTED_EVENT_ACTION_COUNT = "CONFIG_HGC_GROUPBOX_${i}_EVENT_SELECTED_ACTION_COUNT"
		/>
</#if>
</#list>
        default:
            return false; // default false as it is not processed
    }    
}

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
bool GFX_HGC_MsgStaticTexts(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
<#assign x=CONFIG_GFX_HGC_NUM_STATICTEXTS>
<#list 0..x-1 as i>
<#if "CONFIG_HGC_STATICTEXT_${i}_EVENT_SELECTED_ACTION_COUNT"?eval??>
    <@GFX_HGC_STATICTEXT_GENERATE_EVENTS
        GFX_STATICTEXT_ID = "CONFIG_HGC_STATICTEXT_ID_${i}"
		GFX_INDEX = "GFX_INDEX_0"
		GFX_STATICTEXT_INDEX = "${i}"
		GFX_STATICTEXT_SELECTED_EVENT_ACTION_COUNT = "CONFIG_HGC_STATICTEXT_${i}_EVENT_SELECTED_ACTION_COUNT"
		/>
</#if>
</#list>
        default:
            return false; // default false as it is not processed
    }    
}

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
bool GFX_HGC_MsgPictures(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
<#assign x=CONFIG_GFX_HGC_NUM_PICTURES>
<#list 0..x-1 as i>
<#if "CONFIG_HGC_PICTURE_${i}_EVENT_SELECTED_ACTION_COUNT"?eval??>
    <@GFX_HGC_PICTURE_GENERATE_EVENTS
        GFX_PICTURE_ID = "CONFIG_HGC_PICTURE_ID_${i}"
		GFX_INDEX = "GFX_INDEX_0"
		GFX_PICTURE_INDEX = "${i}"
		GFX_PICTURE_SELECTED_EVENT_ACTION_COUNT   = "CONFIG_HGC_PICTURE_${i}_EVENT_SELECTED_ACTION_COUNT"
		/>
</#if>
</#list>
        default:
            return false; // default false as it is not processed
    }    
}

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
bool GFX_HGC_MsgWindows(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
<#assign x=CONFIG_GFX_HGC_NUM_WINDOWS>
<#list 0..x-1 as i>
<#if "CONFIG_HGC_WINDOW_${i}_EVENT_TITLE_ACTION_COUNT"?eval?? ||
     "CONFIG_HGC_WINDOW_${i}_EVENT_CLIENT_ACTION_COUNT"?eval?? == true>
    <@GFX_HGC_WINDOW_GENERATE_EVENTS
        GFX_WINDOW_ID = "CONFIG_HGC_WINDOW_ID_${i}"
		GFX_INDEX = "GFX_INDEX_0"
		GFX_WINDOW_INDEX = "${i}"
		GFX_WINDOW_TITLE_EVENT_ACTION_COUNT = "CONFIG_HGC_WINDOW_${i}_EVENT_TITLE_ACTION_COUNT"
		GFX_WINDOW_CLIENT_EVENT_ACTION_COUNT = "CONFIG_HGC_WINDOW_${i}_EVENT_CLIENT_ACTION_COUNT"
        />
</#if>
</#list>
        default:
            return false; // default false as it is not processed
    }    
}

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
bool GFX_HGC_MsgTextEntrys(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
<#assign x=CONFIG_GFX_HGC_NUM_TEXTENTRYS>
<#list 0..x-1 as i>
<#if "CONFIG_HGC_TEXTENTRY_${i}_EVENT_PRESS_ACTION_COUNT"?eval?? ||
     "CONFIG_HGC_TEXTENTRY_${i}_EVENT_RELEASED_ACTION_COUNT"?eval?? == true||
	 "CONFIG_HGC_TEXTENTRY_${i}_EVENT_ADD_CHAR_ACTION_COUNT"?eval?? == true ||
	 "CONFIG_HGC_TEXTENTRY_${i}_EVENT_DELETE_ACTION_COUNT"?eval?? == true ||
	 "CONFIG_HGC_TEXTENTRY_${i}_EVENT_SPACE_ACTION_COUNT"?eval?? == true ||
	 "CONFIG_HGC_TEXTENTRY_${i}_EVENT_ENTER_ACTION_COUNT"?eval?? == true>
    <@GFX_HGC_TEXTENTRY_GENERATE_EVENTS
        GFX_TEXTENTRY_ID = "CONFIG_HGC_TEXTENTRY_ID_${i}"
		GFX_INDEX = "GFX_INDEX_0"
		GFX_TEXTENTRY_INDEX = "${i}"
		GFX_TEXTENTRY_PRESS_EVENT_ACTION_COUNT    = "CONFIG_HGC_TEXTENTRY_${i}_EVENT_PRESS_ACTION_COUNT"
		GFX_TEXTENTRY_RELEASED_EVENT_ACTION_COUNT = "CONFIG_HGC_TEXTENTRY_${i}_EVENT_RELEASED_ACTION_COUNT"
		GFX_TEXTENTRY_ADD_CHAR_EVENT_ACTION_COUNT = "CONFIG_HGC_TEXTENTRY_${i}_EVENT_ADD_CHAR_ACTION_COUNT"
		GFX_TEXTENTRY_DELETE_EVENT_ACTION_COUNT   = "CONFIG_HGC_TEXTENTRY_${i}_EVENT_DELETE_ACTION_COUNT"
		GFX_TEXTENTRY_SPACE_EVENT_ACTION_COUNT    = "CONFIG_HGC_TEXTENTRY_${i}_EVENT_SPACE_ACTION_COUNT"
		GFX_TEXTENTRY_ENTER_EVENT_ACTION_COUNT    = "CONFIG_HGC_TEXTENTRY_${i}_EVENT_ENTER_ACTION_COUNT"
        />
</#if>
</#list>
        default:
            return false; // process by default
    }

    return true;
}

</#if>

<#--
/*******************************************************************************
 End of File
*/
-->
