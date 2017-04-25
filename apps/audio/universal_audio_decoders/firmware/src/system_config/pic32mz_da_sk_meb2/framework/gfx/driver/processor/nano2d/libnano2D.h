/****************************************************************************
*
*    Copyright (c) 2005 - 2014 by Vivante Corp.  All rights reserved.
*
*    The material in this file is confidential and contains trade secrets
*    of Vivante Corporation. This is proprietary information owned by
*    Vivante Corporation. No part of this work may be disclosed,
*    reproduced, copied, transmitted, or used in any way for any purpose,
*    without the express written permission of Vivante Corporation.
*
*****************************************************************************/


#ifndef _nano2d_h__
#define _nano2d_h__

#include "framework/gfx/driver/processor/nano2d/libnano2D_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct n2d_module_parameters
{
    n2d_int32_t     irqLine2D;
    n2d_uint32_t    registerMemBase2D;
    n2d_uint32_t    registerMemSize2D;
    n2d_uint32_t    contiguousSize;
    n2d_uint32_t    contiguousBase;
    n2d_uint32_t    baseAddress;
}
n2d_module_parameters_t;

typedef enum n2d_blend
{
    N2D_BLEND_NONE,
    N2D_BLEND_SRC_OVER,
    N2D_BLEND_DST_OVER,
    N2D_BLEND_SRC_IN,
    N2D_BLEND_DST_IN,
    N2D_BLEND_ADDITIVE,
    N2D_BLEND_SUBTRACT,
}
n2d_blend_t;

typedef enum n2d_buffer_format
{
    N2D_RGBA8888,
    N2D_BGRA8888,
    N2D_RGB565,
    N2D_BGR565,
    N2D_RGBA4444,
    N2D_BGRA4444,
    N2D_A8,
    N2D_YUYV,
    N2D_UYVY,
}
n2d_buffer_format_t;

typedef enum n2d_orientation
{
    N2D_0,
    N2D_90,
    N2D_180,
    N2D_270,
}
n2d_orientation_t;

typedef struct n2d_buffer
{
    n2d_int32_t width;
    n2d_int32_t height;
    n2d_int32_t stride;
    n2d_buffer_format_t format;
    n2d_orientation_t orientation;
    void *handle;
    void *memory;
    n2d_uint32_t gpu;
}
n2d_buffer_t;

typedef enum n2d_error
{
    N2D_SUCCESS = 0,
    N2D_INVALID_ARGUMENT,
    N2D_OUT_OF_MEMORY,
    N2D_NO_CONTEXT,
    N2D_TIMEOUT,
    N2D_OUT_OF_RESOURCES,
    N2D_GENERIC_IO,
    N2D_NOT_SUPPORTED,
}
n2d_error_t;

typedef struct n2d_point
{
    n2d_int32_t x;
    n2d_int32_t y;
}
n2d_point_t;

typedef struct n2d_rectangle
{
    n2d_int32_t x;
    n2d_int32_t y;
    n2d_int32_t width;
    n2d_int32_t height;
}
n2d_rectangle_t;

typedef enum n2d_transparency
{
    N2D_TRANSPARENCY_NONE,
    N2D_TRANSPARENCY_SOURCE,
    N2D_TRANSPARENCY_DESTINATION,
}
n2d_transparency_t;

typedef n2d_int32_t n2d_color_t;

n2d_error_t n2d_allocate(
    n2d_buffer_t *buffer);

n2d_error_t n2d_blit(
    n2d_buffer_t *destination,
    n2d_rectangle_t *destination_rectangle,
    n2d_buffer_t *source,
    n2d_rectangle_t *source_rectangle,
    n2d_blend_t blend);

n2d_error_t n2d_close(
    void);

n2d_error_t n2d_draw_state(
    n2d_transparency_t transparency,
    n2d_color_t color,
    n2d_uint8_t foreground_rop,
    n2d_uint8_t background_rop);

n2d_error_t n2d_fill(
    n2d_buffer_t *destination,
    n2d_rectangle_t *rectangle,
    n2d_color_t color,
    n2d_blend_t blend);

n2d_error_t n2d_free(
    n2d_buffer_t *buffer);

n2d_error_t n2d_line(
    n2d_buffer_t *destination,
    n2d_point_t start,
    n2d_point_t end,
    n2d_rectangle_t *clip,
    n2d_color_t color,
    n2d_blend_t blend);

n2d_error_t n2d_map(
    n2d_buffer_t *buffer);

n2d_error_t n2d_open(
    void);

n2d_error_t n2d_unmap(
    n2d_buffer_t *buffer);

n2d_error_t n2d_init_hardware(
    n2d_module_parameters_t *params
    );

#ifdef __cplusplus
}
#endif

#endif /* _nano2d_h__ */
