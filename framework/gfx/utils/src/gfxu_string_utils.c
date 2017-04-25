#include "gfx/utils/inc/gfxu_string_utils.h"
#include "gfx/utils/inc/gfxu_font.h"

uint32_t GFXU_ExtractString(GFXU_StringTableAsset* tbl,
                            uint32_t id,
                            uint32_t lang,
                            GFXU_CHAR* buffer,
                            uint32_t size,
                            uint32_t offset)
{
    uint16_t idx;
    uint8_t* stringAddress;
    uint32_t stringSize;
    uint32_t codePoint;
    uint32_t tblOffset;
    
    uint32_t i, j;
    
    if(tbl == GFX_NULL)
        return 0;
    
    stringSize = GFXU_GetStringSizeInBytes(tbl, id, lang);
    
    //if(stringSize > size)
    //    return 0;
        
    idx = GFXU_StringIndexLookup(tbl, id, lang);
    
    if(GFXU_StringLookup(tbl, idx, &stringAddress, &stringSize))
        return GFX_FAILURE;
        
    j = 0;
    
    buffer[size - 1] = '\0';
    
    for(i = 0; i < stringSize;)
    {
        if(GFXU_DecodeCodePoint(tbl->encodingMode,
                                stringAddress + i,
                                stringSize,
                                &codePoint,
                                &tblOffset) == GFX_FAILURE)
            return 0;
        
        i += tblOffset;
        
        // don't overrun buffer and leave last index for null
        if(j < size - 1)
            buffer[offset + j++] = codePoint;
        else
            return j;
        
    }
    
    j -= 1;
    
    return j;
}

int32_t GFXU_CompareString(GFXU_StringTableAsset* tbl,
                            uint32_t id,
                            uint32_t lang,
                            GFXU_CHAR* buffer)
{
    uint16_t idx;
    uint8_t* stringAddress;
    uint32_t stringSize, buffSize;
    uint32_t codePoint;
    uint32_t offset;
    
    uint32_t i, j;
    
    if(tbl == GFX_NULL || buffer == GFX_NULL)
        return -1;
    
    stringSize = GFXU_GetStringSizeInBytes(tbl, id, lang);
    
    buffSize = 0;
    
    while(buffer[buffSize] != '\0')
        buffSize++;    
    
    idx = GFXU_StringIndexLookup(tbl, id, lang);
    
    if(GFXU_StringLookup(tbl, idx, &stringAddress, &stringSize))
        return GFX_FAILURE;
        
    j = 0;
    
    for(i = 0; i < stringSize && j < buffSize;)
    {
        if(GFXU_DecodeCodePoint(tbl->encodingMode,
                                stringAddress + i,
                                stringSize,
                                &codePoint,
                                &offset) == GFX_FAILURE)
            return 0;
            
        if(codePoint < buffer[j])
			return -1;
		else if(codePoint > buffer[j])
			return 1;
		else
			j++;
        
        i += offset;
    }
    
    return 0;
}
                                        
uint16_t GFXU_StringIndexLookup(GFXU_StringTableAsset* table,
                                uint32_t stringID,
                                uint32_t languageID)
{
    uint8_t* indexTable = table->stringIndexTable;
    uint16_t* ptr;
    uint32_t indexWidth;
    uint32_t i;
    
    if(stringID >= table->stringCount || languageID >= table->languageCount)
        return GFX_NULL;
        
    // skip header
    indexTable += 3;
    
    indexWidth = indexTable[0];
    
    indexTable += 1;
    
    // skip to string index
    for(i = 0; i < stringID; i++)
        indexTable += (table->languageCount * indexWidth);
    
    if(indexWidth == 1)
    {
        i = indexTable[languageID];
        
        if(i == 0xFF)
            return 0xFFFF;
        else
            return i;
    }
    else
    {
        ptr = (uint16_t*)indexTable;
        
        return ptr[languageID];
    }
}

GFX_Result GFXU_StringLookup(GFXU_StringTableAsset* table,
                           uint32_t stringIndex,
                           uint8_t** stringAddress,
                           uint32_t* stringSize)
{
    uint32_t i;
    uint32_t stringCount, offset;
    uint8_t* data;
        
    if(stringIndex == 0xFFFF)
        return GFX_FAILURE;
        
    data = table->header.dataAddress;

    // get string count
    stringCount = data[0] + (data[1] << 8);

    data += 2;
    
    // find the string data in the string table
    for(i = 0; i < stringCount; i++)
    {
        if(i == stringIndex)
            break;
        
        offset = data[0] + (data[1] << 8);
        
        data += GFXU_STRING_ENTRY_SIZE + offset;
        
        /*word = (uint16_t*)address;
        
        offset = *word;
        offset += GFXU_STRING_ENTRY_SIZE;
    
        address += offset;*/
    }
    
    //word = (uint16_t*)address;
    *stringSize = data[0] + (data[1] << 8);
    
    data += GFXU_STRING_ENTRY_SIZE;
    //address += GFXU_STRING_ENTRY_SIZE;
    
    *stringAddress = data;
    
    return GFX_SUCCESS;
}
                                
GFXU_FontAsset* GFXU_StringFontIndexLookup(GFXU_StringTableAsset* table,
                                           uint32_t stringID,
                                           uint32_t languageID)
{
    uint8_t* indexTable = table->fontIndexTable;
    uint32_t i;
    
    if(stringID >= table->stringCount || languageID >= table->languageCount)
        return GFX_NULL;
    
    // skip header
    indexTable += 3;
    
    // skip to string index
    for(i = 0; i < stringID; i++)
        indexTable += table->languageCount;
        
    i = indexTable[languageID];
    
    if(i == 0xFF)
        return GFX_NULL;
    
    return table->fontTable[i];
}
                                    

GFX_Result GFXU_FontGetLookupTableEntry(uint8_t* table,
                                        uint32_t index,
                                        uint32_t max,
                                        uint32_t* offset,
                                        uint32_t* width)
{
    uint32_t dataSize = table[0];
    uint32_t widthSize = table[1];
    uint32_t offs, wdth;
    uint32_t i;
    
    table += 2; // advance past table header data
    
    if(index >= max)
        return GFX_FAILURE;
    
    table += index * (dataSize + 1);
    
    offs = 0;
    
    for(i = 0; i < dataSize; i++)
        offs |= (table[i] << (8 * i)); 
    
    *offset = offs;
    
    table += dataSize;
    
    wdth = 0;
    
    for(i = 0; i < widthSize; i++)
        wdth |= (table[i] << (8 * i)); 
    
    *width = wdth;
    
    return GFX_SUCCESS;
}

GFX_Result GFXU_FontGetGlyphInfo(GFXU_FontAsset* fnt,
                                 uint32_t glyph,
                                 uint32_t* offset,
                                 uint32_t* width)
{
    uint32_t i;
    uint32_t idx = 0;
    uint32_t count;
    
    // attempt to find the glyph in the range lookup tables
    for(i = 0; i < fnt->indexTable->count; i++)
    {
        if(glyph >= fnt->indexTable->ranges[i].startID && glyph <= fnt->indexTable->ranges[i].endID)
        {
            idx = glyph - fnt->indexTable->ranges[i].startID;
            count = fnt->indexTable->ranges[i].endID - fnt->indexTable->ranges[i].startID + 1;
            
            return GFXU_FontGetLookupTableEntry(fnt->indexTable->ranges[i].lookupTable,
                                                idx,
                                                count,
                                                offset,
                                                width);
        }
    }
    
    // return width of unknown glyph rectangle
    *width = fnt->height >> 1;
    
    return GFX_FAILURE;
}

GFX_Result GFXU_DecodeASCII(uint8_t* val,
                            uint32_t max,
                            uint32_t* codePoint,
                            uint32_t* size)
{
    *codePoint = val[0];
    *size = 1;
    
    return GFX_SUCCESS;
}

GFX_Result GFXU_DecodeUTF8(uint8_t* val,
                           uint32_t max,
                           uint32_t* codePoint,
                           uint32_t* size)
{
    uint32_t point = 0;
    uint32_t length = 0;
    
    if((val[0] & 0x80) == 0x0)
    {
        length = 1;
        point = val[0] & 0x7F;
    }
    else if((val[0] & 0xE0) == 0xC0)
    {
        length = 2;
        
        if(max < 2)
            return GFX_FAILURE;
        
        point |= (val[0] & 0x1F) << 6;
        point |= (val[1] & 0x3F);
    } 
    else if((val[0] & 0xF0) == 0xE0)
    {
        length = 3;
        
        if(max < 3)
            return GFX_FAILURE;
        
        point |= (val[0] & 0xF) << 12;
        point |= (val[1] & 0x3F) << 6;
        point |= (val[2] & 0x3F);
    }
    else if((val[0] & 0xF8) == 0xF0)
    {
        length = 4;
        
        if(max < 4)
            return GFX_FAILURE;
        
        point |= (val[0] & 0x7) << 18;
        point |= (val[1] & 0x3F) << 12;
        point |= (val[2] & 0x3F) << 6;
        point |= (val[3] & 0x3F);
    }
    else if((val[0] & 0xFC) == 0xF8)
    {   
        length = 5;
        
        if(max < 5)
            return GFX_FAILURE;
        
        point |= (val[0] & 0x3) << 24;
        point |= (val[1] & 0x3F) << 18;
        point |= (val[2] & 0x3F) << 12;
        point |= (val[3] & 0x3F) << 6;
        point |= (val[4] & 0x3F);
    }
    else if((val[0] & 0xFE) == 0xFC)
    {
        length = 6;
        
        if(max < 6)
            return GFX_FAILURE;
        
        point |= (val[0] & 0x1) << 30;
        point |= (val[1] & 0x3F) << 24;
        point |= (val[2] & 0x3F) << 18;
        point |= (val[3] & 0x3F) << 12;
        point |= (val[4] & 0x3F) << 6;
        point |= (val[5] & 0x3F);
    }
    else
        return GFX_FAILURE;
    
    *size = length;
    *codePoint = point;
    
    return GFX_SUCCESS;
}

GFX_Result GFXU_DecodeUTF16(uint8_t* val,
                            uint32_t max,
                            uint32_t* codePoint,
                            uint32_t* size)
{
    uint32_t point = 0;
    uint32_t high, low;
    
    if((val[0] & 0xFC) == 0xD8)
    {
        if(max < 4)
            return GFX_FAILURE;
            
        *size = 4;
        
        high = val[0] << 8;
        high |= val[1];
        high -= 0xD800;
        
        low = val[2] << 8;
        low |= val[3];
        low -= 0xDC00;
        
        point = ((high << 10) + low) + 0x10000;
    }
    else
    {
        if(max < 2)
            return GFX_FAILURE;
            
        *size = 2;
        
        point += val[0];
        point += (val[1] << 8);
    }
    
    *codePoint = point;
    
    return GFX_SUCCESS;
}

typedef GFX_Result (*decodeGlyph_FnPtr)(uint8_t*,
                                        uint32_t,
                                        uint32_t*,
                                        uint32_t*);
                                         
decodeGlyph_FnPtr decodeGlyph[] =
{
    &GFXU_DecodeASCII,
    &GFXU_DecodeUTF8,
    &GFXU_DecodeUTF16
};

GFX_Result GFXU_DecodeCodePoint(uint32_t encoding,
                                uint8_t* data,
                                uint32_t max,
                                uint32_t* codePoint,
                                uint32_t* offset)
{
    return decodeGlyph[encoding](data, max, codePoint, offset);
}

GFX_Result GFXU_DecodeAndDrawString(uint8_t* string,
                                    uint32_t length,
                                    GFXU_StringEncodingMode mode,
                                    GFXU_FontAsset* fnt,
                                    int32_t x,
                                    int32_t y)
{
    uint32_t glyph, offset, width;
    uint8_t* data;
    uint32_t i, r;
    //uint32_t startY = 
    
    for(i = 0; i < length;)
    {
        if(GFXU_DecodeCodePoint(mode,
                                &string[i],
                                length - i,
                                &glyph,
                                &width) == GFX_FAILURE)
            return GFX_FAILURE;
            
        i += width;
    
        // attempt to find the glyph raster data
        // if no data found then draw empty rectangle
        if(GFXU_FontGetGlyphInfo(fnt,
                                 glyph,
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
                GFXU_DrawGlyphRow(fnt->bpp, data, width, x, y + r - (fnt->height - (fnt->ascent + fnt->descent)), &offset);
                
                data += offset;
            }
        }
        
        x += width;
    }
    
    return GFX_SUCCESS;
}

GFX_Result drawGlyphRow1bpp(uint8_t* data, 
                            uint32_t width,
                            int32_t x,
                            int32_t y,
                            uint32_t* offset)
{
    uint32_t i;
    uint32_t offs;
    uint8_t val;
            
    //byte = data*(((uint8_t*)buffer->pixels) + (idx >> 3));
    
    //color = byte & (0x80 >> offs);
    
    //color >>= 7 - offs;
    
    for(i = 0; i < width; i++)
    {
        offs = (i % 8);
        val = data[i >> 3];
        val = data[i >> 3] & (0x80 >> offs);
        
        if(val > 0)
            GFX_DrawPixel(x + i, y);
    }
    
    *offset = width >> 3;
    *offset += (width % 8) > 0 ? 1 : 0;
    
    return GFX_SUCCESS;
}
                            
GFX_Result drawGlyphRow8bpp(uint8_t* data,
                            uint32_t width,
                            int32_t x,
                            int32_t y,
                            uint32_t* offset)
{
    uint32_t i;
    GFX_BlendMode mode;
    
    // store old blending mode
    GFX_Get(GFXF_DRAW_BLEND_MODE, &mode);
            
    // enable alpha blending on the current blend mode
    GFX_Set(GFXF_DRAW_BLEND_MODE, mode | GFX_BLEND_ALPHA);
    
    for(i = 0; i < width; i++)
    {
        if(data[i] > 0)
        {
            GFX_Set(GFXF_DRAW_ALPHA_VALUE, data[i]);
            GFX_DrawPixel(x + i, y);
        }
    }
    
    // restore old blending mode
    GFX_Set(GFXF_DRAW_BLEND_MODE, mode);
    
    *offset = width;
    
    return GFX_SUCCESS;
}        

typedef GFX_Result (*drawGlyphRow_FnPtr)(uint8_t*,
                                         uint32_t,
                                         int32_t,
                                         int32_t,
                                         uint32_t*);
                                         
drawGlyphRow_FnPtr drawGlyphRow[] =
{
    &drawGlyphRow1bpp,
    &drawGlyphRow8bpp
};

GFX_Result GFXU_DrawGlyphRow(GFXU_FontAssetBPP bpp,
                             uint8_t* data,
                             uint32_t width,
                             int32_t x,
                             int32_t y,
                             uint32_t* offset)
{
    return drawGlyphRow[bpp](data, width, x, y, offset);
}

void GFXU_DrawUnknownGlyph(int32_t x,
                           int32_t y,
                           uint32_t height,
                           uint32_t* offset)
{
    uint32_t width = (height >> 1);
    
    GFX_Set(GFXF_DRAW_MODE, GFX_DRAW_LINE);
    GFX_DrawRect(x + 2, y + 1, width - 3, height - 1);
    
    *offset = width;
}