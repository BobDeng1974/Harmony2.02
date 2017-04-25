#include "gfx/utils/inc/gfxu_image.h"

#include <stdlib.h>
#include <string.h>

#include "gfx/utils/inc/gfxu_palette.h"
#include "gfx/utils/inc/gfxu_image_utils.h"

typedef enum imageReaderState_t
{
    PREPARE_IMAGE_DATA_REQUEST,
    ATTEMPT_IMAGE_DATA_REQUEST,
    WAITING_FOR_IMAGE_DATA,
    DRAW_IMAGE_DATA,
    DONE
} drawState;

typedef struct GFXU_ImageAssetReader_t
{
    GFXU_ExternalAssetReader header;
    
    GFXU_ImageAsset* img;
    
    GFX_Rect sourceRect;
    GFX_Point destPoint;
    
    uint32_t row_max;
    uint32_t col_max;
    
    uint32_t row;
    uint32_t col;
    
    uint32_t imageIndex;
    GFX_Color imageColor;
    
    uint32_t paletteIndex;
    uint32_t paletteCache;
    GFX_Color paletteColor;
    
} GFXU_ImageAssetReader;

static GFX_Result calculateImageIndex(GFXU_ImageAssetReader* imgReader)
{
    imgReader->imageIndex = imgReader->sourceRect.x + imgReader->col + 
                           ((imgReader->sourceRect.y + imgReader->row) * imgReader->img->width);

    imgReader->header.state = ATTEMPT_IMAGE_DATA_REQUEST;
    
    return GFX_SUCCESS;
}

static void imageReadRequestCompleted(GFXU_ImageAssetReader* imgReader)
{
    imgReader->header.state = DRAW_IMAGE_DATA;
    imgReader->header.status = GFXU_READER_STATUS_DRAWING;
}

static GFX_Result requestImageData(GFXU_ImageAssetReader* imgReader)
{
    void* address;
    uint32_t offs;
       
    if(imgReader->header.memIntf->read == GFX_NULL)
        return GFX_FAILURE;
       
    offs = getOffsetFromIndexAndBPP(imgReader->imageIndex,
                                    GFX_ColorModeInfoGet(imgReader->img->colorMode).bppOrdinal);
    
    address = imgReader->img->header.dataAddress;
    address = (void*)(((uint8_t*)address) + offs);

    if(imgReader->header.memIntf->read((GFXU_ExternalAssetReader*)imgReader,
                                      imgReader->img->header.dataLocation,
                                      address,
                                      GFX_ColorModeInfoGet(imgReader->img->colorMode).size,
                                      (uint8_t*)&imgReader->imageColor,
                                      (GFXU_MemoryReadRequestCallback_FnPtr)&imageReadRequestCompleted) == GFX_FAILURE)
    {
        return GFX_FAILURE;
    }
        
    imgReader->header.status = GFXU_READER_STATUS_WAITING;
    imgReader->header.state = WAITING_FOR_IMAGE_DATA; 
    
    return GFX_SUCCESS;                             
}

static GFX_Result drawImageData(GFXU_ImageAssetReader* imgReader)
{
    GFX_ColorMode colorMode;
    
    if(GFX_Get(GFXF_COLOR_MODE, &colorMode) == GFX_FAILURE)
        return GFX_FAILURE;
        
    if(GFX_Set(GFXF_DRAW_COLOR, GFX_ColorConvert(imgReader->img->colorMode,
                                                 colorMode,
                                                 imgReader->imageColor)) == GFX_FAILURE)
        return GFX_FAILURE;
    
    if(imgReader->img->useMask == GFX_TRUE)
    {
        if(GFX_Set(GFXF_DRAW_MASK_VALUE, GFX_ColorConvert(imgReader->img->colorMode,
                                                          colorMode,
                                                          imgReader->img->mask)) == GFX_FAILURE)
            return GFX_FAILURE;
            
        GFX_Set(GFXF_DRAW_MASK_ENABLE, GFX_TRUE);
    }
       
    GFX_DrawPixel(imgReader->destPoint.x + imgReader->col,
                  imgReader->destPoint.y + imgReader->row);
        
    imgReader->col++;
   
    if(imgReader->col == imgReader->col_max)
    {
        imgReader->row++;
        imgReader->col = 0;
    }
    
    if(imgReader->row == imgReader->row_max)
    {
        imgReader->header.status = GFXU_READER_STATUS_FINISHED;
        imgReader->header.state = DONE;
    }
    else
    {
        imgReader->header.state = PREPARE_IMAGE_DATA_REQUEST;   
    }

    return GFX_SUCCESS;
}

static GFX_Result run(GFXU_ExternalAssetReader* reader)
{
    GFXU_ImageAssetReader* imgReader = (GFXU_ImageAssetReader*)reader;
    
    if(imgReader == GFX_NULL)
        return GFX_FAILURE;
    
    switch(imgReader->header.state)
    {
        case PREPARE_IMAGE_DATA_REQUEST:
            return calculateImageIndex(imgReader);
        case ATTEMPT_IMAGE_DATA_REQUEST:
            return requestImageData(imgReader);
        case DRAW_IMAGE_DATA:
            return drawImageData(imgReader);
        case WAITING_FOR_IMAGE_DATA:
        default:
            return GFX_SUCCESS;
    }
}

GFX_Result GFXU_DrawImagePngExternal(GFXU_ImageAsset* img,
                                     int32_t src_x,
                                     int32_t src_y,
                                     int32_t src_width,
                                     int32_t src_height,
                                     int32_t dest_x,
                                     int32_t dest_y,
                                     GFXU_MemoryIntf* memIntf,
                                     GFXU_ExternalAssetReader** reader)
{
    GFXU_ImageAssetReader* imgReader;
    
    imgReader = (GFXU_ImageAssetReader*)memIntf->heap.calloc(1, 
                                             sizeof(GFXU_ImageAssetReader));
    
    if(imgReader == GFX_NULL)
        return GFX_FAILURE;
    
    imgReader->header.memIntf = memIntf;
    imgReader->header.run = &run;
    imgReader->header.status = GFXU_READER_STATUS_READY;
    imgReader->header.state = PREPARE_IMAGE_DATA_REQUEST;
    
    imgReader->img = img;
    
    imgReader->sourceRect.x = src_x;
    imgReader->sourceRect.y = src_y;
    imgReader->sourceRect.width = src_width;
    imgReader->sourceRect.height = src_height;
    
    imgReader->destPoint.x = dest_x;
    imgReader->destPoint.y = dest_y;
    
    imgReader->row_max = src_height;
    imgReader->col_max = src_width;
    
    *reader = (GFXU_ExternalAssetReader*)imgReader;

    return GFX_SUCCESS;
}