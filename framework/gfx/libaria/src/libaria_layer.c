#include "gfx/libaria/inc/libaria_layer.h"

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_screen.h"
#include "gfx/libaria/inc/libaria_utils.h"

#define DEFAULT_WIDTH   100
#define DEFAULT_HEIGHT  100

laLayer* laLayer_New()
{
	laLayer* lyr = NULL;

	if(laContext_GetActive() == NULL)
		return NULL;

	lyr = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laLayer));
    
	_laWidget_Constructor((laWidget*)lyr);

	lyr->widget.type = LA_WIDGET_LAYER;
	lyr->widget.root = LA_TRUE;
	
	lyr->bufferCount = 1;

	lyr->widget.rect.x = 0;
	lyr->widget.rect.y = 0;
	lyr->widget.rect.width = DEFAULT_WIDTH;
	lyr->widget.rect.height = DEFAULT_HEIGHT;
	
	lyr->alphaEnable = LA_FALSE;

	lyr->widget.moved = (laWidget_Moved_FnPtr)&_laLayer_Moved;
	lyr->widget.resized = (laWidget_Resized_FnPtr)&_laLayer_Resized;
	lyr->widget.paint = (laWidget_Paint_FnPtr)&_laLayer_Paint;

	return lyr;
}

void laLayer_Delete(laLayer* layer)
{
    layer->widget.destructor((laWidget*)layer);
}

laResult laLayer_SetAlphaEnable(laLayer* layer, laBool enable)
{
    if(laWidget_SetAlphaEnable((laWidget*)layer, enable) == GFX_FAILURE)
        return GFX_FAILURE;
    
    if(layer->screen == NULL || laContext_GetActive()->activeScreen != layer->screen)
		return GFX_SUCCESS;
	
	GFX_Set(GFXF_LAYER_ACTIVE, laScreen_GetLayerIndex(layer->screen, layer));
	GFX_Set(GFXF_LAYER_ALPHA_ENABLE, layer->alphaEnable);
	
	return GFX_SUCCESS;
}

laResult laLayer_SetAlphaAmount(laLayer* layer, uint32_t amount)
{
    if(laWidget_SetAlphaAmount((laWidget*)layer, amount) == GFX_FAILURE)
        return GFX_FAILURE;
        
    if(layer->screen == NULL || laContext_GetActive()->activeScreen != layer->screen)
		return GFX_SUCCESS;
	
	GFX_Set(GFXF_LAYER_ACTIVE, laScreen_GetLayerIndex(layer->screen, layer));
	GFX_Set(GFXF_LAYER_ALPHA_AMOUNT, layer->widget.alphaAmount);
	
	return GFX_SUCCESS;
}

laBool laLayer_GetMaskEnable(const laLayer* layer)
{
    if(layer == NULL)
        return 0;
        
    return layer->maskEnable;
}

laResult laLayer_SetMaskEnable(laLayer* layer, laBool enable)
{
    if(layer == NULL || layer->maskEnable == enable)
        return LA_FAILURE;
        
    layer->maskEnable = enable;
        
    if(layer->screen == NULL || laContext_GetActive()->activeScreen != layer->screen)
		return LA_SUCCESS;
	
	GFX_Set(GFXF_LAYER_ACTIVE, laScreen_GetLayerIndex(layer->screen, layer));
	GFX_Set(GFXF_LAYER_MASK_ENABLE, layer->maskEnable);

    return LA_SUCCESS;
}

GFX_Color laLayer_GetMaskColor(const laLayer* layer)
{
    if(layer == NULL)
        return 0;
        
    return layer->maskColor;
}

laResult laLayer_SetMaskColor(laLayer* layer, GFX_Color color)
{
    if(layer == NULL || layer->maskColor == color)
        return LA_FAILURE;
        
    layer->maskColor = color;
        
    if(layer->screen == NULL || laContext_GetActive()->activeScreen != layer->screen)
		return LA_SUCCESS;
	
	GFX_Set(GFXF_LAYER_ACTIVE, laScreen_GetLayerIndex(layer->screen, layer));
	GFX_Set(GFXF_LAYER_MASK_COLOR, layer->maskColor);
	
	return LA_SUCCESS;
}

uint32_t laLayer_GetBufferCount(const laLayer* layer)
{
	if(layer == NULL)
		return 0;

	return layer->bufferCount;
}

laResult laLayer_SetBufferCount(laLayer* layer, uint32_t count)
{
	if(layer == NULL)
		return LA_FAILURE;

    layer->bufferCount = count;
    
    // TODO need to update the HAL if this layer is active
    
    return LA_SUCCESS;
}

laBool laLayer_GetVSync(const laLayer* layer)
{
	if(layer == NULL)
		return 0;

	return layer->vsync;
}

laResult laLayer_SetVSync(laLayer* layer, uint32_t enable)
{
	if(layer == NULL)
		return LA_FAILURE;
    
    layer->vsync = enable;
    
    // TODO need to update the HAL if this layer is active
    
    return LA_SUCCESS;
}

void _laLayer_Moved(laLayer* layer)
{
	if(layer->screen == NULL || laContext_GetActive()->activeScreen != layer->screen)
		return;
	
	GFX_Set(GFXF_LAYER_ACTIVE, laScreen_GetLayerIndex(layer->screen, layer));
	GFX_Set(GFXF_LAYER_POSITION, layer->widget.rect.x, layer->widget.rect.y); 
}

void _laLayer_Resized(laLayer* layer)
{
	if(layer->screen == NULL || laContext_GetActive()->activeScreen != layer->screen)
		return;

	GFX_Set(GFXF_LAYER_ACTIVE, laScreen_GetLayerIndex(layer->screen, layer));
	GFX_Set(GFXF_LAYER_SIZE, layer->widget.rect.width, layer->widget.rect.height); 
}

void _laLayer_Paint(laLayer* layer)
{
    if(layer->widget.drawBackground == LA_TRUE)
	{
	    GFX_Set(GFXF_DRAW_COLOR, layer->widget.scheme->background);
        GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_FILL);
	    GFX_DrawRect(0,
		             0,
				     layer->widget.rect.width,
				     layer->widget.rect.height);
    }
	
	layer->widget.drawState = LA_WIDGET_DRAW_STATE_DONE;
}

void _laLayer_Invalidate(laLayer* layer)
{
    _laWidget_InvalidateChildren((laWidget*)layer);
}

void _laLayer_InvalidateArea(laLayer* layer, GFX_Rect area)
{
    laList invalidList;
    laWidget* widget;
    uint32_t i;
    
    laList_Create(&invalidList);
    
    laUtils_PickRect(layer, area, &invalidList);
    laUtils_ListOcclusionCullTest(&invalidList, area);
    
    if(invalidList.size == 0)
        return;
        
    for(i = 0; i < invalidList.size; i++)
    {
        widget = laList_Get(&invalidList, i);
        
        if(widget->dirtyState == LA_WIDGET_DIRTY_STATE_DIRTY)
            continue;
            
        laWidget_Invalidate(widget);
    }
        
    laList_Clear(&invalidList);
}