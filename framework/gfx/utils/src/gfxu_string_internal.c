#include "gfx/utils/inc/gfxu_string.h"
#include "gfx/utils/inc/gfxu_font.h"
#include "gfx/utils/inc/gfxu_string_utils.h"

#define GFXU_STRING_ARRAY_SIZE 4
#define GFXU_STRING_ENTRY_SIZE 2

GFX_Result GFXU_DrawStringInternal(GFXU_StringTableAsset* tbl,
                                   GFXU_FontAsset* fnt,
                                   uint32_t id,
                                   uint32_t lang,
                                   int32_t x,
                                   int32_t y)
{
    //uint32_t i;
    uint16_t idx;
    uint8_t* stringAddress;
    uint32_t stringSize;
    
    idx = GFXU_StringIndexLookup(tbl, id, lang);
    
    if(GFXU_StringLookup(tbl, idx, &stringAddress, &stringSize))
        return GFX_FAILURE;
        
    /*stringAddress = (uint8_t*)tbl->header.dataAddress;
    
    // find the string data in the string table
    for(i = 0; i < tbl->stringCount; i++)
    {
        if(i == id)
            break;
    
        stringAddress += ((uint32_t*)stringAddress)[0];
    }
    
    stringAddress += GFXU_STRING_ARRAY_SIZE;
    stringSize = (uint32_t)((uint16_t*)stringAddress)[0];
    stringAddress += GFXU_STRING_ENTRY_SIZE;
    
    for(i = 0; i < tbl->languageCount; i++)
    {
        if(i == lang)
            break;
        
        stringAddress += stringSize;
        stringSize = (uint32_t)((uint16_t*)stringAddress)[0];
        stringAddress += GFXU_STRING_ENTRY_SIZE;
    }*/
    
    GFXU_DecodeAndDrawString(stringAddress,
                             stringSize,
                             tbl->encodingMode,
                             fnt,
                             x,
                             y);
    
    return GFX_SUCCESS;
}

GFX_Result GFXU_DrawStringBufferInternal(GFXU_CHAR* buffer,
                                         GFXU_FontAsset* fnt,
                                         int32_t x,
                                         int32_t y)
{
    uint32_t len, offset, width;
    uint32_t i, r;
    uint8_t* data;
    
    len = 0;
    
    while(buffer[len] != '\0')
        len++;
        
    if(len == 0)
        return 0;
    
    for(i = 0; i < len; i++)
    {
        if(GFXU_FontGetGlyphInfo(fnt,
                                 buffer[i],
                                 &offset,
                                 &width) == GFX_FAILURE)
        {
            GFXU_DrawUnknownGlyph(x, y + (fnt->height - (fnt->ascent + fnt->descent)), fnt->ascent + fnt->descent, &width);
        }
        else
        {    
            data = ((uint8_t*)fnt->header.dataAddress);
            data += offset;
                
            for(r = 0; r < fnt->height; r++)
            {
                GFXU_DrawGlyphRow(fnt->bpp, data, width, x, y + r, &offset);
                
                data += offset;
            }
        }
        
        x += width;
    }
    
    return GFX_SUCCESS;
}