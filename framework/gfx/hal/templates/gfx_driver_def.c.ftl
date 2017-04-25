#include "gfx/hal/inc/gfx_driver_interface.h"

<#assign GFX_DRIVER_COUNT = 0>
<#if CONFIG_USE_GFX_STACK = true>
<#if CONFIG_DRV_GFX_CONTROLLER_TYPE = "Low Cost Controllerless">
<#include "/framework/gfx/driver/controller/lcc/templates/drv_gfx_lcc_definition.ftl">
<@DRV_GFX_LCC_DRIVER_DECLARATION IDX = 0/>
</#if>
<#if CONFIG_DRV_GFX_CONTROLLER_TYPE = "GLCD">
<#include "/framework/gfx/driver/controller/glcd/templates/drv_gfx_glcd_definition.ftl">
<@DRV_GFX_GLCD_DRIVER_DECLARATION IDX = 0/>
</#if>
<#if CONFIG_DRV_GFX_CONTROLLER_TYPE = "Epson S1D13517">
<#include "/framework/gfx/driver/controller/s1d13517/templates/drv_gfx_s1d13517_definition.ftl">
<@DRV_GFX_S1D13517_DRIVER_DECLARATION IDX = 0/>
</#if>
</#if>

GFX_Result GFX_InitializeDriverList()
{
<#if CONFIG_USE_GFX_STACK = true>
<#if CONFIG_DRV_GFX_CONTROLLER_TYPE = "Low Cost Controllerless">
<#include "/framework/gfx/driver/controller/lcc/templates/drv_gfx_lcc_definition.ftl">
<@DRV_GFX_LCC_DRIVER_DEFINITION
	ID = GFX_DRIVER_COUNT
	IDX = 0/>
<#assign GFX_DRIVER_COUNT = GFX_DRIVER_COUNT + 1>
</#if>
<#if CONFIG_DRV_GFX_CONTROLLER_TYPE = "GLCD">
<#include "/framework/gfx/driver/controller/glcd/templates/drv_gfx_glcd_definition.ftl">
<@DRV_GFX_GLCD_DRIVER_DEFINITION
        ID = GFX_DRIVER_COUNT
        IDX = 0/>
<#assign GFX_DRIVER_COUNT = GFX_DRIVER_COUNT + 1>
</#if>
<#if CONFIG_DRV_GFX_CONTROLLER_TYPE = "Epson S1D13517">
<#include "/framework/gfx/driver/controller/s1d13517/templates/drv_gfx_s1d13517_definition.ftl">
<@DRV_GFX_S1D13517_DRIVER_DEFINITION
	ID = GFX_DRIVER_COUNT
	IDX = 0/>
<#assign GFX_DRIVER_COUNT = GFX_DRIVER_COUNT + 1>
</#if>
</#if>

    return GFX_SUCCESS;
}
