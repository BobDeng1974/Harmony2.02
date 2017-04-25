#include "gfx/utils/inc/gfxu_image.h"

GFX_Result GFXU_DrawImageRawInternal(GFXU_ImageAsset* img,
                                     int32_t src_x,
                                     int32_t src_y,
                                     int32_t src_width,
                                     int32_t src_height,
                                     int32_t dest_x,
                                     int32_t dest_y);
                                     
GFX_Result GFXU_DrawImageRLEInternal(GFXU_ImageAsset* img,
                                     int32_t src_x,
                                     int32_t src_y,
                                     int32_t src_width,
                                     int32_t src_height,
                                     int32_t dest_x,
                                     int32_t dest_y);
                                  
GFX_Result GFXU_DrawImageRawExternal(GFXU_ImageAsset* img,
                                     int32_t src_x,
                                     int32_t src_y,
                                     int32_t src_width,
                                     int32_t src_height,
                                     int32_t dest_x,
                                     int32_t dest_y,
                                     GFXU_MemoryIntf* memoryInterface,
                                     GFXU_ExternalAssetReader** reader);
                                     
GFX_Result GFXU_DrawImageRLEExternal(GFXU_ImageAsset* img,
                                     int32_t src_x,
                                     int32_t src_y,
                                     int32_t src_width,
                                     int32_t src_height,
                                     int32_t dest_x,
                                     int32_t dest_y,
                                     GFXU_MemoryIntf* memoryInterface,
                                     GFXU_ExternalAssetReader** reader);

GFX_Result GFXU_DrawImagePngInternal(GFXU_ImageAsset* img,
                                     int32_t src_x,
                                     int32_t src_y,
                                     int32_t src_width,
                                     int32_t src_height,
                                     int32_t dest_x,
                                     int32_t dest_y);
                                     
GFX_Result GFXU_DrawImagePngInternal(GFXU_ImageAsset* img,
                                     int32_t src_x,
                                     int32_t src_y,
                                     int32_t src_width,
                                     int32_t src_height,
                                     int32_t dest_x,
                                     int32_t dest_y);
                                  
GFX_Result GFXU_DrawImageJpgInternal(GFXU_ImageAsset* img,
                                     int32_t src_x,
                                     int32_t src_y,
                                     int32_t src_width,
                                     int32_t src_height,
                                     int32_t dest_x,
                                     int32_t dest_y);
                                  
GFX_Result GFXU_DrawImage(GFXU_ImageAsset* img,
                          int32_t src_x,
                          int32_t src_y,
                          int32_t src_width,
                          int32_t src_height,
                          int32_t dest_x,
                          int32_t dest_y,
                          GFXU_MemoryIntf* memoryInterface,
                          GFXU_ExternalAssetReader** reader)
{
    GFX_Rect image_rect, source_rect, source_clip_rect;
    
    if(img == GFX_NULL)
        return GFX_FAILURE;

    image_rect.x = 0;
    image_rect.y = 0;
    image_rect.width = img->width;
    image_rect.height = img->height;
    
    source_rect.x = src_x;
    source_rect.y = src_y;
    source_rect.width = src_width;
    source_rect.height = src_height;
    
    if(GFX_RectIntersects(&image_rect, &source_rect) == GFX_FALSE)
        return GFX_FAILURE;
    
    GFX_RectClip(&image_rect, &source_rect, &source_clip_rect);

    // can't draw an external resource with no callback
    //if(img->header.dataLocation != 0 && reader == GFX_NULL)
    //    return GFX_FAILURE;
    
    if(img->header.dataLocation == GFXU_ASSET_LOCATION_INTERNAL)
    {
        if(img->format == GFXU_IMAGE_FORMAT_RAW)
        {
            if(img->compType == GFXU_IMAGE_COMPRESSION_NONE)
            {
                return GFXU_DrawImageRawInternal(img,
                                      source_clip_rect.x,
                                      source_clip_rect.y,
                                      source_clip_rect.width,
                                      source_clip_rect.height,
                                      dest_x,
                                      dest_y);
            }
            else if(img->compType == GFXU_IMAGE_COMPRESSION_RLE)
            {
                return GFXU_DrawImageRLEInternal(img,
                                      source_clip_rect.x,
                                      source_clip_rect.y,
                                      source_clip_rect.width,
                                      source_clip_rect.height,
                                      dest_x,
                                      dest_y);
            }
            
        }
        else if(img->format == GFXU_IMAGE_FORMAT_PNG)
        {
            return GFXU_DrawImagePngInternal(img,
                                  source_clip_rect.x,
                                  source_clip_rect.y,
                                  source_clip_rect.width,
                                  source_clip_rect.height,
                                  dest_x,
                                  dest_y);        
        }
        else if(img->format == GFXU_IMAGE_FORMAT_JPEG)
        {
            return GFXU_DrawImageJpgInternal(img,
                                  source_clip_rect.x,
                                  source_clip_rect.y,
                                  source_clip_rect.width,
                                  source_clip_rect.height,
                                  dest_x,
                                  dest_y);                
        }
    }
    else if(memoryInterface != GFX_NULL &&
            reader != GFX_NULL)
    {
        if(img->format == GFXU_IMAGE_FORMAT_RAW)
        {
            if(img->compType == GFXU_IMAGE_COMPRESSION_NONE)
            {
                return GFXU_DrawImageRawExternal(img,
                                                 source_clip_rect.x,
                                                 source_clip_rect.y,
                                                 source_clip_rect.width,
                                                 source_clip_rect.height,
                                                 dest_x,
                                                 dest_y,
                                                 memoryInterface,
                                                 reader);
            }
            else if(img->compType == GFXU_IMAGE_COMPRESSION_RLE)
            {
                return GFXU_DrawImageRLEExternal(img,
                                      source_clip_rect.x,
                                      source_clip_rect.y,
                                      source_clip_rect.width,
                                      source_clip_rect.height,
                                      dest_x,
                                      dest_y,
                                      memoryInterface,
                                      reader);
            }
        }
    }
    
    return GFX_FAILURE;
}