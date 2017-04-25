/*********************************************************************
*                 SEGGER Microcontroller Systems LLC                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2016  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.36 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to Microchip Technology Inc. for the
purposes  of  creating  libraries  for  16 -bit  PIC microcontrollers,
32-bit  PIC  microntrollers,  dsPIC  digital  signal  controllers  and
microcontrollers   with   part   name   prefix   "PIC16"  and  "PIC18"
commercialized and distributed by Microchip Technology Inc. as part of
the  MPLAB  Integrated  Development  Environment  under  the terms and
conditions  of  an  End  User  License  Agreement  supplied  with  the
libraries. Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
----------------------------------------------------------------------
File        : LCDConf.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "system_config.h"
#include "system_definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************
#include "GUIDRV_Lin.h"

<#if CONFIG_DRV_GFX_DISPLAY_COLORS == "GFX_COLOR_MODE_RGB_565">
#define DRIVER_TYPE			GUIDRV_LIN_16
#define COLOR_CONVERSION	GUICC_M565
<#elseif CONFIG_DRV_GFX_DISPLAY_COLORS == "GFX_COLOR_MODE_RGB_332">
#define DRIVER_TYPE			GUIDRV_LIN_8
#define COLOR_CONVERSION	GUICC_M332
<#elseif CONFIG_DRV_GFX_DISPLAY_COLORS == "GFX_COLOR_MODE_RGB_888">
#define DRIVER_TYPE			GUIDRV_LIN_24
#define COLOR_CONVERSION	GUICC_M888
</#if>

// *****************************************************************************
// *****************************************************************************
// Section: Layer Configuration 
// *****************************************************************************
// *****************************************************************************
/* TODO: Add any necessary Layer Configuration. 
*/

/*********************************************************************
*
*       LCD_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*   
*/

void LCD_X_Config(void) 
{
<#if CONFIG_USE_GFX_STACK == true>
    GFX_Buffer buffer = NULL;
    
    GUI_DEVICE_CreateAndLink( DRIVER_TYPE, COLOR_CONVERSION, 0, 0);
    
    if (LCD_GetSwapXY()) 
    {
        LCD_SetSizeEx (0, ${CONFIG_DRV_GFX_DISPLAY_HEIGHT}, ${CONFIG_DRV_GFX_DISPLAY_WIDTH});
        LCD_SetVSizeEx(0, ${CONFIG_DRV_GFX_DISPLAY_HEIGHT}, ${CONFIG_DRV_GFX_DISPLAY_WIDTH});
    } 
    else 
    {
        LCD_SetSizeEx (0, ${CONFIG_DRV_GFX_DISPLAY_WIDTH}, ${CONFIG_DRV_GFX_DISPLAY_HEIGHT});
        LCD_SetVSizeEx(0, ${CONFIG_DRV_GFX_DISPLAY_WIDTH}, ${CONFIG_DRV_GFX_DISPLAY_HEIGHT});
    }
    
    GFX_Get(GFXF_LAYER_BUFFER_ADDRESS, 0, &buffer);
    LCD_SetVRAMAddrEx( 0, ( void * )buffer );
</#if>
    
    return;
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Purpose:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if 
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/

int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) 
{

<#if CONFIG_USE_DRV_GFX_LCC == true && CONFIG_DRV_GFX_LCC_MODE == "Internal Memory">

   int retVal = -1;
    
    switch( Cmd )
    {
        case LCD_X_INITCONTROLLER:
        {
            retVal = 0;
            
            break;
        }
        
        default:
        {
            retVal = -1;
            
            break;
        }
    }
    
    return retVal;
<#else>
    return 0;
</#if>

}

/*******************************************************************************
 End of File
 */

