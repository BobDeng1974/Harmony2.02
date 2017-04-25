#include "gfx/hal/inc/gfx_display.h"
#include "gfx/hal/inc/gfx_common.h"

<#macro BOOL_TO_INT
	VAL
	COMMENT>
<#if VAL == true>
            1, //  ${COMMENT}
<#else>
            0, //  ${COMMENT}
</#if>
</#macro>

<#macro DRV_GFX_DISPLAY_DEF 
	IDX>
    <#noparse>{</#noparse>
	    "${CONFIG_DRV_GFX_DISPLAY_DESC}",  // description
		${CONFIG_DRV_GFX_DISPLAY_COLORS},  // color mode
		<#noparse>{</#noparse>
			0,  // x position (always 0)
			0,  // y position (always 0)
			${CONFIG_DRV_GFX_DISPLAY_WIDTH},  // display width
			${CONFIG_DRV_GFX_DISPLAY_HEIGHT}, // display height
		<#noparse>},</#noparse>
		<#noparse>{</#noparse>
		    ${CONFIG_DRV_GFX_DISPLAY_DATA_WIDTH},  // data bus width
		    <#noparse>{</#noparse>
				${CONFIG_DRV_GFX_DISPLAY_HOR_PULSE_WIDTH},  // horizontal pulse width
				${CONFIG_DRV_GFX_DISPLAY_HOR_BACK_PORCH},  // horizontal back porch
				${CONFIG_DRV_GFX_DISPLAY_HOR_FRONT_PORCH},  // horizontal front porch
		    <#noparse>},</#noparse>
		    <#noparse>{</#noparse>
				${CONFIG_DRV_GFX_DISPLAY_VER_PULSE_WIDTH},  // vertical pulse width
				${CONFIG_DRV_GFX_DISPLAY_VER_BACK_PORCH},  // vertical back porch
				${CONFIG_DRV_GFX_DISPLAY_VER_FRONT_PORCH},  // vertical front porch
		    <#noparse>},</#noparse>
		<#noparse>},</#noparse>
	<#noparse>},</#noparse>
</#macro>

GFX_DisplayInfo GFX_DisplayInfoList[] =
{
<#if CONFIG_USE_GFX_STACK = true>
	<@DRV_GFX_DISPLAY_DEF IDX = 0/>
<#else>
	{ },
</#if>
};