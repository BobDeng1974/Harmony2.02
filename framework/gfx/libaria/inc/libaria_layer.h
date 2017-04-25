/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_layer.h

  Summary:
    Aria layers map directly to layers provided by the Graphics Hardware
    Abstraction layer.  HAL layers map directly to hardware layers provided
    by graphics hardware.  UI layers are logical containers for widgets
    and provide many of the same features.
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

#ifndef LIBARIA_LAYER_H
#define LIBARIA_LAYER_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"
#include "gfx/libaria/inc/libaria_widget.h"

typedef struct laScreen_t laScreen;

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Enumeration:
    laLayerBufferType_t

  Summary:
    Defines the type of a layer.  If the layer has an explicit address then
    Aria tries to set that through the HAL when the layer is being set up.

  Remarks:
    None.
*/
typedef enum laLayerBufferType_t
{
    LA_BUFFER_TYPE_AUTO,
    LA_BUFFER_TYPE_ADDRESS
} laLayerBufferType;

// *****************************************************************************
/* Structure:
    laLayerBuffer_t

  Summary:
    Structure to maintain the buffer type and track the buffer location for each layer

  Description:
    Structure to maintain the buffer type and track the buffer location for each layer

  Remarks:
    None.
*/
typedef struct laLayerBuffer_t
{
    laLayerBufferType type;
    void* address;
} laLayerBuffer;

// *****************************************************************************
/* Structure:
    laLayer_t

  Summary:
    Primary definition of a layer.  Builds on base functions of a standard
    widget.  Should never have a direct parent.

  Remarks:
    None.
*/
typedef struct laLayer_t
{
	laWidget widget; // base widget
	laScreen* screen; // owning screen pointer

	uint32_t bufferCount; // number of buffers in the layer
	laLayerBuffer buffers[GFX_MAX_BUFFER_COUNT]; // buffer array
	
	laBool alphaEnable; // layer-based alpha blending enable flag
  
    laBool maskEnable;  // layer-based color masking enable flag
    GFX_Color maskColor; // layer-based masking color value

	laBool vsync; // layer vsync flag
} laLayer;

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laLayer* laLayer_New()

  Summary:
    Constructor for a new layer	

  Description:
    Constructor for a new layer, returns the layer object

  Parameters:
	void
	
  Returns:
	laLayer*
	
  Remarks:
    Allocates memory for a layer using the active context memory interface.
    Once added to a screen the it becomes the responsibility of the framework
    to free the memory.
*/
LIB_EXPORT laLayer* laLayer_New();

// *****************************************************************************
/* Function:
    void laLayer_Delete(laLayer* layer)

  Summary:
    Destructor for the layer object	

  Description:
    Destructor for the layer object

  Parameters:
	laLayer*
	
  Returns:
	void
	
  Remarks:
    
*/
LIB_EXPORT void laLayer_Delete(laLayer* layer);

// internal functions
LIB_EXPORT void _laLayer_Moved(laLayer* layer);
LIB_EXPORT void _laLayer_Resized(laLayer* layer);

// *****************************************************************************
/* Function:
    laBool laLayer_GetAlphaEnable(const laLayer* layer)

  Summary:
    Gets the layer alpha enable flag

  Parameters:
	const laLayer* - the layer to reference
	
  Returns:
	laBool - the value of the alpha enable flag
*/
LIB_EXPORT laBool laLayer_GetAlphaEnable(const laLayer* layer);

// *****************************************************************************
/* Function:
    laResult laLayer_SetAlphaEnable(laLayer* layer, laBool enable)

  Summary:
    Sets the layer alpha enable flag to the specified value

  Parameters:
	laLayer* layer - the layer to modify
	laBool enable - the desired value of the flag
	
  Returns:
	laResult - the result of the operation
	
  Remarks:
    
*/
LIB_EXPORT laResult laLayer_SetAlphaEnable(laLayer* layer, laBool enable);

// *****************************************************************************
/* Function:
	uint32_t laLayer_GetAlphaAmount(const laLayer* layer)

  Summary:
    Get's the amount of alpha blending for a given layer

  Parameters:
	laLayer* layer - the layer to reference

  Returns:
    uint32_t - an alpha channel value from 0 - 255
*/
LIB_EXPORT uint32_t laLayer_GetAlphaAmount(const laLayer* layer);

// *****************************************************************************
/* Function:
    laResult laLayer_SetAlphaAmount(laLayer* layer, uint32_t amount)

  Summary:
    Set's the amount of alpha blending for a given layer

  Description:
    Set's the amount of alpha blending for a given layer

  Parameters:
	laLayer* layer - the layer to reference
	uint32_t amount - an alpha amount from 0 - 255
	
  Returns:
	laResult - success if the operation succeeded
	
  Remarks:
    
*/
LIB_EXPORT laResult laLayer_SetAlphaAmount(laLayer* layer, uint32_t amount);

// *****************************************************************************
/* Function:
    laBool laLayer_GetMaskEnable(const laLayer* layer)

  Summary:
    Gets the layer mask enable flag

  Description:
    Gets the layer mask enable flag

  Parameters:
	laLayer* layer - the layer to reference
	
  Returns:
	laBool - the value of the mask enable flag
	
  Remarks:
    
*/
LIB_EXPORT laBool laLayer_GetMaskEnable(const laLayer* layer);

// *****************************************************************************
/* Function:
    laResult laLayer_SetMaskEnable(laLayer* layer, laBool enable)

  Summary:
    Sets the layer mask enable flag to the specified value

  Parameters:
	laLayer* layer - the layer to modify
	laBool enable - the desired value of the flag
	
  Returns:
	laResult - the result of the operation
	
  Remarks:
    
*/
LIB_EXPORT laResult laLayer_SetMaskEnable(laLayer* layer, laBool enable);

// *****************************************************************************
/* Function:
    GFX_Color laLayer_GetMaskColor(const laLayer* layer)

  Summary:
    Returns the mask color value for the current layer 

  Description:
    Returns the mask color value for the current layer 

  Parameters:
	laLayer* layer - the layer to reference
	
  Returns:
	GFX_Color - the layer mask color value
	
  Remarks:
    
*/
LIB_EXPORT GFX_Color laLayer_GetMaskColor(const laLayer* layer);

// *****************************************************************************
/* Function:
    void laLayer_SetMaskColor(laLayer* layer, GFX_Color color)

  Summary:
    Set the mask color value for the current layer to the specified value

  Description:
    Set the mask color value for the current layer to the specified value 

  Parameters:
	laLayer* layer - the layer to modify
	GFX_color color - the desired mask color value
	
  Returns:
	laResult - the result of the operation
	
  Remarks:
    
*/
LIB_EXPORT laResult laLayer_SetMaskColor(laLayer* layer, GFX_Color color);

// *****************************************************************************
/* Function:
    uint32_t laLayer_GetBufferCount(const laLayer* layer)

  Summary:
    Return the buffer count for the current layer

  Description:
    Return the buffer count for the current layer

  Parameters:
	laLayer* layer - the layer to reference

  Returns:
	uint32_t - the current number of buffers for the layer
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laLayer_GetBufferCount(const laLayer* layer);

// *****************************************************************************
/* Function:
    laResult laLayer_SetBufferCount(laLayer* layer, uint32_t count)

  Summary:
    Set the buffer count for the current layer to the specified value

  Description:
    Set the buffer count for the current layer to the specified value

  Parameters:
	laLayer* layer - the layer to modify
	uint32_t count - the desired number of buffers

  Returns:
	laResult - the result of the operation
	
  Remarks:
    
*/
LIB_EXPORT laResult laLayer_SetBufferCount(laLayer* layer, uint32_t count);

// *****************************************************************************
/* Function:
    laBool laLayer_GetVSync(const laLayer* layer)

  Summary:
    Gets the layer's vsync flag setting

  Description:
    

  Parameters:
	const laLayer* layer - the layer to reference
	
  Returns:
	laBool - the state of the layer's vsync flag
	
  Remarks:
    
*/											 
LIB_EXPORT laBool laLayer_GetVSync(const laLayer* layer);

// *****************************************************************************
/* Function:
    void laLayer_SetVSync(laLayer* layer, laBool enable)

  Summary:
    Sets the layer's vsync flag.

  Description:
    Sets the layer's vsync flag.

  Parameters:
	const laLayer* layer - the layer to modify
	
  Returns:
	laResult - the result of the operation
	
  Remarks:
    
*/	
LIB_EXPORT laResult laLayer_SetVSync(laLayer* layer, laBool enable);

void _laLayer_Invalidate(laLayer* layer);
void _laLayer_InvalidateArea(laLayer* layer, GFX_Rect area);

void _laLayer_Paint(laLayer* layer);

#endif /* LIBARIA_LAYER_H */