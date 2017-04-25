/*******************************************************************************
 Module for Microchip Graphics Library - Hardware Abstraction Layer

  Company:
    Microchip Technology Inc.

  File Name:
    gfx_default_impl.h

  Summary:
    Defines MPLAB Harmony Graphics Hardware Abstraction default software
    function implementations 

  Description:
    Drawing and display timing functions.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2016 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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
#ifndef GFX_DEFAULT_IMPL_H
#define GFX_DEFAULT_IMPL_H
//DOM-IGNORE-END

#include "gfx/hal/inc/gfx_common.h"
#include "gfx/hal/inc/gfx_context.h"
#include "gfx/hal/inc/gfx_pixel_buffer.h"

// empty function, does nothing
GFX_Result defUnsupported(void);

// initializes a context pointer to all of the default 
// function pointers
GFX_Result contextDefInitialization(GFX_Context* context);

// performs a generic initialization of the context
GFX_Result defInitialize(GFX_Context* context);

// default begin and end
GFX_Result defBegin(void);
void defEnd(void);

// empty update function, always returns success
GFX_Result defUpdate(void);

// generic destroy function
void defDestroy(GFX_Context* context);

// brightness functions
GFX_Result defBrightnessRangeGet(uint32_t* low, uint32_t* high);

uint32_t   defBrightnessGet(void);
GFX_Result defBrightnessSet(uint32_t val);      

// default vsync and hsync callback handlers
GFX_SyncCallback_FnPtr defVSyncCallbackGet(void);
GFX_Result defVSyncCallbackSet(GFX_SyncCallback_FnPtr cb);                         

GFX_SyncCallback_FnPtr defHSyncCallbackGet(void);
GFX_Result defHSyncCallbackSet(GFX_SyncCallback_FnPtr cb);

// default orientation and mirroring
GFX_Orientation defLayerOrientationGet(void);
GFX_Result      defLayerOrientationSet(GFX_Orientation ori);

GFX_Bool   defLayerMirroringGet(void);
GFX_Result defLayerMirroringSet(GFX_Bool mirr);    

// default color mode functions
GFX_ColorMode defColorModeGet(void);
GFX_Result defColorModeSet(GFX_ColorMode mode);

// default layer active handlers
uint32_t   defLayerActiveGet(void);
GFX_Result defLayerActiveSet(uint32_t idx);

// default layer visibility and enabling functions
GFX_Bool   defLayerEnabledGet(void);
GFX_Result defLayerEnabledSet(GFX_Bool val);

GFX_Bool   defLayerVisibleGet(void);
GFX_Result defLayerVisibleSet(GFX_Bool val);

// default layer position functions
GFX_Result defLayerPositionGet(int32_t* x, int32_t* y);
GFX_Result defLayerPositionSet(int32_t x, int32_t y);

// default layer size functions
GFX_Result defLayerSizeGet(int32_t* width, int32_t* height);
GFX_Result defLayerSizeSet(int32_t width, int32_t height);

// buffer count and memory management
uint32_t   defLayerBufferCountGet(void);
GFX_Result defLayerBufferCountSet(uint32_t count);

GFX_Buffer defLayerBufferAddressGet(uint32_t idx);
GFX_Result defLayerBufferAddressSet(uint32_t idx, GFX_Buffer address);

GFX_Bool defLayerBufferCoherentGet(uint32_t idx);
GFX_Result defLayerBufferCoherentSet(uint32_t idx, GFX_Bool coherent);

GFX_Result defLayerBufferAllocate(uint32_t idx);
GFX_Result defLayerBufferFree(uint32_t idx);

// default vsync option handler
GFX_Bool   defLayerVsyncGet(void);
GFX_Result defLayerVsyncSet(GFX_Bool vsync);

// default swap functions
GFX_Bool   defLayerSwapGet(void);
GFX_Result defLayerSwapSet(GFX_Bool val);

void defLayerSwapped(GFX_Layer* layer);

// default layer blend and masking functions
GFX_Bool defLayerAlphaEnableGet(void);
GFX_Result defLayerAlphaEnableSet(GFX_Bool enable);

uint32_t defLayerAlphaAmountGet(void);
GFX_Result defLayerAlphaAmountSet(uint32_t amount);

GFX_Bool defLayerMaskEnableGet(void);
GFX_Result defLayerMaskEnableSet(GFX_Bool enable);

GFX_Color defLayerMaskColorGet(void);
GFX_Result defLayerMaskColorSet(GFX_Color color);

// draw pipeline functions
#if GFX_DRAW_PIPELINE_ENABLED
GFX_DrawMode defDrawModeGet(void);
GFX_Result defDrawModeSet(GFX_DrawMode mode);

GFX_Color  defDrawColorGet(void);
GFX_Result defDrawColorSet(GFX_Color color);

void defDrawGradientColorGet(GFX_Color* tl,
                             GFX_Color* tr,
                             GFX_Color* bl,
                             GFX_Color* br);
                                   
GFX_Result defDrawGradientColorSet(GFX_Color tl,
                                   GFX_Color tr,
                                   GFX_Color bl,
                                   GFX_Color br);

GFX_Result defDrawPaletteGet(GFX_PixelBuffer* pb);
GFX_Result defDrawPaletteSet(GFX_PixelBuffer* pb);

GFX_BlendMode defDrawBlendModeGet(void);
GFX_Result    defDrawBlendModeSet(GFX_BlendMode mode);

uint32_t   defDrawAlphaValueGet(void);
GFX_Result defDrawAlphaValueSet(uint32_t value);

uint32_t   defDrawMaskValueGet(void);
GFX_Result defDrawMaskValueSet(uint32_t value);

uint32_t   defDrawThicknessGet(void);
GFX_Result defDrawThicknessSet(uint32_t value);

GFX_Bool   defDrawClipEnabledGet(void);
GFX_Result defDrawClipEnabledSet(GFX_Bool value);

GFX_Result defDrawClipRectGet(GFX_Rect* rect);
GFX_Result defDrawClipRectSet(GFX_Rect* rect);

GFX_Result defDrawLock(void);
GFX_Result defDrawUnlock(void);

GFX_Result defSwap(void);

GFX_Color  defPixelGet(const GFX_PixelBuffer* buffer,
                       const GFX_Point* pnt);
GFX_Result defPixelSet(const GFX_PixelBuffer* buffer,
                       const GFX_Point* pnt,
                       GFX_Color color);
                       
#endif // GFX_DRAW_PIPELINE_ENABLED
#endif /* GFX_DEFAULT_IMPL_H */