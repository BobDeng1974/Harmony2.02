<#macro DRV_GFX_NANO2D_DRIVER_DECLARATION IDX>
GFX_Result driverNANO2DInfoGet(GFX_DriverInfo* info);
GFX_Result driverNANO2DContextInitialize(GFX_Context* context);
</#macro>

<#macro DRV_GFX_NANO2D_DRIVER_DEFINITION
	ID
	IDX>
    GFX_DriverInterfaces[${ID}].infoGet = &driverNano2dInfoGet;
    GFX_DriverInterfaces[${ID}].contextInitialize = &driverNano2dContextInitialize;
</#macro>
