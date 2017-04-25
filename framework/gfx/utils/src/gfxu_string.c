#include "gfx/utils/inc/gfxu_string.h"
#include "gfx/utils/inc/gfxu_font.h"
#include "gfx/utils/inc/gfxu_string_utils.h"

GFX_Result GFXU_DrawStringInternal(GFXU_StringTableAsset* tbl,
                                   GFXU_FontAsset* fnt,
                                   uint32_t id,
                                   uint32_t lang,
                                   int32_t x,
                                   int32_t y);
                                   
GFX_Result GFXU_DrawStringBufferInternal(GFXU_CHAR* buffer,
                                         GFXU_FontAsset* fnt,
                                         int32_t x,
                                         int32_t y);
                                  
GFX_Result GFXU_DrawStringExternal(GFXU_StringTableAsset* tbl,
                                   GFXU_FontAsset* fnt,
                                   uint32_t id,
                                   uint32_t lang,
                                   int32_t x,
                                   int32_t y,
                                   GFXU_MemoryIntf* memoryInterface,
                                   GFXU_ExternalAssetReader** reader);
                                     
GFX_Result GFXU_DrawString(GFXU_StringTableAsset* tbl,
                           uint32_t id,
                           uint32_t lang,
                           int32_t x,
                           int32_t y,
                           GFXU_MemoryIntf* memoryInterface,
                           GFXU_ExternalAssetReader** reader)
{
    GFXU_FontAsset* fnt;
    
    if(tbl == GFX_NULL)
        return GFX_FAILURE;

    // can't draw an external resource with no callback
    //if(img->header.dataLocation != 0 && reader == GFX_NULL)
    //    return GFX_FAILURE;
    
    //y -= fnt->height - fnt->ascent;
    
    fnt = GFXU_StringFontIndexLookup(tbl, id, lang);
    
    if(fnt == GFX_NULL)
        return GFX_FAILURE;
    
    if(tbl->header.dataLocation == GFXU_ASSET_LOCATION_INTERNAL &&
       fnt->header.dataLocation == GFXU_ASSET_LOCATION_INTERNAL)
    {
        return GFXU_DrawStringInternal(tbl, fnt, id, lang, x, y);
    }
    else if(memoryInterface != GFX_NULL && reader != GFX_NULL)
    {
        GFXU_DrawStringExternal(tbl,
                                fnt,
                                id,
                                lang,
                                x,
                                y,
                                memoryInterface,
                                reader);
    }
    
    return GFX_SUCCESS;
}

GFX_Result GFXU_DrawCharString(GFXU_CHAR* str,
                               GFXU_FontAsset* fnt,
                               int32_t x,
                               int32_t y,
                               GFXU_MemoryIntf* memoryInterface,
                               GFXU_ExternalAssetReader** reader)
{
    if(fnt == GFX_NULL)
        return GFX_FAILURE;

    // can't draw an external resource with no callback
    //if(img->header.dataLocation != 0 && reader == GFX_NULL)
    //    return GFX_FAILURE;
    
    //y -= fnt->height - fnt->ascent;
    
    if(fnt->header.dataLocation == GFXU_ASSET_LOCATION_INTERNAL)
    {
        return GFXU_DrawStringBufferInternal(str, fnt, x, y);
    }
    else if(memoryInterface != GFX_NULL && reader != GFX_NULL)
    {
        /*GFXU_DrawStringExternal(tbl,
                                fnt,
                                id,
                                lang,
                                x,
                                y,
                                memoryInterface,
                                reader);*/
    }
    
    return GFX_SUCCESS;
}