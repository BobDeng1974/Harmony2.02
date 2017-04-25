/*******************************************************************************
 Display Tasks

  Company:
    Microchip Technology Inc.

  File Name:
   display.c

  Summary:
    Contains the functional implementation of display task for

  Description:
    This file contains the functional implementation of data parsing functions
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2014 released Microchip Technology Inc.  All rights reserved.

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "gfx_resources.h"
#include "gfx/gfx.h"

#include "gfx_hgc_definitions.h"

#define LARGE_FONT      &Arial20pt
#define MEDIUM_FONT     &Arial14pt
#define SMALL_FONT      &Arial12pt
#define RX_DATA_BASE    65
#define TASK_BAR_COLOR GFX_RGBConvert(29, 46, 60)

#define BACKGROUND_COLOR BLACK
#define TEXT_COLOR1     WHITE
#define TEXT_COLOR2     BRIGHTRED


void GFX_MENU_DRAW(void)
{
}


void DispalyTasks(void)
{
    if(appData.display.status == APP_DISP_STATUS_USB_CONNECTED)
    {
        GFX_GOL_ObjectStateSet(hgcObj.pGOL_USB_CONNECTEDObj, GFX_GOL_PICTURECONTROL_DRAW_STATE);
                                           
        GFX_GOL_ProgressBarPositionSet(hgcObj.pGOL_VOLUME_PBARObj, appData.display.volumeP);             
        GFX_GOL_ObjectStateSet(hgcObj.pGOL_VOLUME_PBARObj, GFX_GOL_PROGRESSBAR_DRAW_BAR_STATE); 
        
        GFX_GOL_StaticTextSet(hgcObj.pGOL_SR_VALObj, (GFX_XCHAR *)&appData.display.samplingRate);        
        GFX_GOL_ObjectStateSet(hgcObj.pGOL_SR_VALObj, GFX_GOL_STATICTEXT_DRAW_STATE);          

        GFX_GOL_ObjectStateSet(hgcObj.pGOL_AUDIO_PLAYObj, GFX_GOL_PICTURECONTROL_DRAW_STATE);        
    }    
    else if(appData.display.status == APP_DISP_STATUS_USB_DISCONNECTED)
    {   
        GFX_GOL_ObjectStateSet(hgcObj.pGOL_USB_DISCONNECTEDObj, GFX_GOL_PICTURECONTROL_DRAW_STATE);        
    }             
    else if(appData.display.status == APP_DISP_STATUS_APP_MUTE_ON)
    {       
        GFX_GOL_ObjectStateSet(hgcObj.pGOL_AUDIO_MUTEObj, GFX_GOL_PICTURECONTROL_DRAW_STATE);
        
    }
    else if(appData.display.status == APP_DISP_STATUS_MUTE_OFF)
    {      
        GFX_GOL_ObjectStateSet(hgcObj.pGOL_AUDIO_PLAYObj, GFX_GOL_PICTURECONTROL_DRAW_STATE);        
        
    }
    else if(appData.display.status == APP_DISP_STATUS_VOLUME_INCREASE ||
            appData.display.status == APP_DISP_STATUS_VOLUME_DECREASE)
    {     
        GFX_GOL_ProgressBarPositionSet(hgcObj.pGOL_VOLUME_PBARObj, appData.display.volumeP);             
        GFX_GOL_ObjectStateSet(hgcObj.pGOL_VOLUME_PBARObj, GFX_GOL_PROGRESSBAR_DRAW_BAR_STATE);         
    }
    else if(appData.display.status == APP_DISP_STATUS_SAMPLING_RATE)
    {
        GFX_GOL_StaticTextSet(hgcObj.pGOL_SR_VALObj, (GFX_XCHAR *)&appData.display.samplingRate);
        GFX_GOL_ObjectStateSet(hgcObj.pGOL_SR_VALObj, GFX_GOL_STATICTEXT_DRAW_STATE);         
    }
    else
    {
        
    }
    appData.display.update = false;      
}