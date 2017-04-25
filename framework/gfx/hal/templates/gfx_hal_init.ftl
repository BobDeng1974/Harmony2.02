<#--
/*******************************************************************************
  GFX Freemarker Template File

  Company:
    Microchip Technology Inc.

  File Name:
    gfx_definitions.h.ftl

  Summary:
    GFX Freemarker Template File

  Description:

*******************************************************************************/

/*******************************************************************************
Copyright (c) 2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS  WITHOUT  WARRANTY  OF  ANY  KIND,
EITHER EXPRESS  OR  IMPLIED,  INCLUDING  WITHOUT  LIMITATION,  ANY  WARRANTY  OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A  PARTICULAR  PURPOSE.
IN NO EVENT SHALL MICROCHIP OR  ITS  LICENSORS  BE  LIABLE  OR  OBLIGATED  UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,  BREACH  OF  WARRANTY,  OR
OTHER LEGAL  EQUITABLE  THEORY  ANY  DIRECT  OR  INDIRECT  DAMAGES  OR  EXPENSES
INCLUDING BUT NOT LIMITED TO ANY  INCIDENTAL,  SPECIAL,  INDIRECT,  PUNITIVE  OR
CONSEQUENTIAL DAMAGES, LOST  PROFITS  OR  LOST  DATA,  COST  OF  PROCUREMENT  OF
SUBSTITUTE  GOODS,  TECHNOLOGY,  SERVICES,  OR  ANY  CLAIMS  BY  THIRD   PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE  THEREOF),  OR  OTHER  SIMILAR  COSTS.
*******************************************************************************/
-->
<#if CONFIG_GFXE_CONTEXT_0_ENABLED = true>
	sysObj.gfxContext = (uint32_t)GFX_Open(${CONFIG_DRV_GFXE_DISPLAY_0_DEF}, ${CONFIG_DRV_GFXE_CONTROLLER_0_DEF}, NULL);
	
<#list 0..CONFIG_GFX_MAX_LAYERS?number-1 as i>
	GFX_Set(GFXF_LAYER_ACTIVE, ${i});
<#if "CONFIG_GFX_RENDER_LAYER${i}_VISIBLE"?eval = true>
	GFX_Set(GFXF_LAYER_VISIBLE, GFX_TRUE);
<#else>
	GFX_Set(GFXF_LAYER_VISIBLE, GFX_FALSE);
</#if>
	GFX_Set(GFXF_LAYER_POSITION, ${"CONFIG_GFX_RENDER_LAYER${i}_POSITION_X"?eval}, ${"CONFIG_GFX_RENDER_LAYER${i}_POSITION_Y"?eval});
	GFX_Set(GFXF_LAYER_SIZE, ${"CONFIG_GFX_RENDER_LAYER${i}_WIDTH"?eval}, ${"CONFIG_GFX_RENDER_LAYER${i}_HEIGHT"?eval});
	GFX_Set(GFXF_LAYER_COLOR_MODE, ${"CONFIG_GFX_RENDER_LAYER${i}_COLOR_MODE"?eval});
	GFX_Set(GFXF_LAYER_BUFFER_COUNT, ${"CONFIG_GFX_RENDER_LAYER${i}_BUFFER_COUNT"?eval});
</#if>
<#--
/*******************************************************************************
 End of File
*/
-->