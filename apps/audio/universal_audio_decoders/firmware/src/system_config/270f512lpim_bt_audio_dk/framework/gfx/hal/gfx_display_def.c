#include "gfx/hal/inc/gfx_display.h"
#include "gfx/hal/inc/gfx_common.h"


GFX_DisplayInfo GFX_DisplayInfoList[] =
{
    {
	    "",  // description
		GFX_COLOR_MODE_RGB_888,  // color mode
		{
			0,  // x position (always 0)
			0,  // y position (always 0)
			320,  // display width
			200, // display height
		},
		{
		    16,  // data bus width
		    {
				0,  // horizontal pulse width
				0,  // horizontal back porch
				0,  // horizontal front porch
		    },
		    {
				0,  // vertical pulse width
				0,  // vertical back porch
				0,  // vertical front porch
		    },
		},
	},
};