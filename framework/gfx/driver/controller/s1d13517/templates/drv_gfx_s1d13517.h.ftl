#ifndef DRV_GFX_S1D13517_H
#define DRV_GFX_S1D13517_H

#include "gfx/hal/inc/gfx_common.h"
#include "gfx/hal/inc/gfx_driver_interface.h"

#ifdef __cplusplus
    extern "C" {
#endif

GFX_Result driverS1D13517InfoGet(GFX_DriverInfo* info);
GFX_Result driverS1D13517ContextInitialize(GFX_Context* context);

#ifdef __cplusplus
    }
#endif

#endif /* DRV_GFX_S1D13517_H */