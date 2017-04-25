#include "gfx/utils/inc/gfxu_string.h"

#include <stdlib.h>
#include <string.h>

#include "gfx/utils/inc/gfxu_font.h"
#include "gfx/utils/inc/gfxu_string_utils.h"

typedef enum imageReaderState_t
{
    INTERNAL_STRING_TABLE_READ,
    ATTEMPT_STRING_ARRAY_SIZE_REQUEST,
    WAITING_FOR_STRING_ARRAY_SIZE,
    ATTEMPT_STRING_ENTRY_SIZE_REQUEST,
    WAITING_FOR_STRING_ENTRY_SIZE,
    ATTEMPT_STRING_DATA_REQUEST,
    WAITING_FOR_STRING_DATA,
    INTERNAL_FONT_DATA_READ,
    PREPARE_FONT_DATA_REQUEST,
    ATTEMPT_FONT_DATA_REQUEST,
    WAITING_FOR_FONT_DATA,
    DRAW_GLYPH_DATA,
    DONE
} drawState;

typedef struct GFXU_StringAssetReader_t
{
    GFXU_ExternalAssetReader header;
    
    GFXU_StringTableAsset* string;
    GFXU_FontAsset* font;
    
    int32_t x;
    int32_t y;
    
    uint8_t* readAddress;
    uint32_t readCount;
    uint32_t readSize;
    
    uint32_t stringID;
    uint32_t entryID;
    
    uint8_t stringData[GFXU_STRING_MAX_CHAR_WIDTH];
    uint32_t codePoint;
    
    uint32_t glyphOffset;
    uint32_t glyphRow;
    uint32_t glyphWidth;
    uint8_t* glyphDataAddress;
    uint8_t* glyphData;
    uint32_t glyphDataSize;
    uint32_t glyphDataCapacity;
} GFXU_StringAssetReader;

static GFX_Result internalStringTableRead(GFXU_StringAssetReader* strReader)
{
    uint32_t i;
    
    // find the desired array of strings in the string table
    for(i = 0; i < strReader->string->stringCount; i++)
    {
        if(i == strReader->stringID)
            break;
    
        strReader->readAddress += ((uint32_t*)strReader->readAddress)[0];
    }
   
    strReader->readAddress += GFXU_STRING_ARRAY_SIZE;
    strReader->readSize = (uint32_t)((uint16_t*)strReader->readAddress)[0];
    strReader->readAddress += GFXU_STRING_ENTRY_SIZE;
    
    // iterate to the desired language entry
    for(i = 0; i < strReader->string->languageCount; i++)
    {
        if(i == strReader->entryID)
            break;
        
        strReader->readAddress += strReader->readSize;
        strReader->readSize = (uint32_t)((uint16_t*)strReader->readAddress)[0];
        strReader->readAddress += GFXU_STRING_ENTRY_SIZE;
    }
    
    // if font data is stored locally then use the local data path
    // isn't currently possible because if both data blobs are internal then 
    // the streaming alaorithm isn't used at all
    if(strReader->font->header.dataLocation == GFXU_ASSET_LOCATION_INTERNAL)
        strReader->header.state = INTERNAL_FONT_DATA_READ;
    else
        strReader->header.state = ATTEMPT_FONT_DATA_REQUEST;
    
    strReader->header.status = GFXU_READER_STATUS_READY;
    
    return GFX_SUCCESS;
}

static void stringArraySizeRequestCompleted(GFXU_StringAssetReader* strReader)
{
    // have we iterated to the desired string array
    if(strReader->entryID == strReader->readCount)
    {
        strReader->readAddress += GFXU_STRING_ARRAY_SIZE;
        strReader->readCount = 0;
            
        strReader->header.state = ATTEMPT_STRING_ENTRY_SIZE_REQUEST;
        strReader->header.status = GFXU_READER_STATUS_READY;
    
        return;
    }
    
    // iterate to the next string array
    strReader->readAddress += strReader->readSize;
    strReader->readCount += 1;
    
    // read the next string table array size
    strReader->header.state = ATTEMPT_STRING_ARRAY_SIZE_REQUEST;
    strReader->header.status = GFXU_READER_STATUS_READY;
}

static GFX_Result requestStringArraySize(GFXU_StringAssetReader* strReader)
{
    // read the size of the next array of strings
    if(strReader->header.memIntf->read((GFXU_ExternalAssetReader*)strReader,
                                       strReader->string->header.dataLocation,
                                       strReader->readAddress,
                                       GFXU_STRING_ARRAY_SIZE,
                                       (uint8_t*)&strReader->readSize,
                                       (GFXU_MemoryReadRequestCallback_FnPtr)&stringArraySizeRequestCompleted) == GFX_FAILURE)
    {
        return GFX_FAILURE;
    }
        
    // wait for the next string table array size
    strReader->header.status = GFXU_READER_STATUS_WAITING;
    strReader->header.state = WAITING_FOR_STRING_ARRAY_SIZE; 
    
    return GFX_SUCCESS;                             
}

static void stringEntrySizeRequestCompleted(GFXU_StringAssetReader* strReader)
{
    // if this is the desired entry then read the next array of characters
    if(strReader->entryID == strReader->readCount)
    {
        strReader->readAddress += GFXU_STRING_ENTRY_SIZE;
        strReader->readCount = 0;
            
        strReader->header.state = ATTEMPT_STRING_DATA_REQUEST;
        strReader->header.status = GFXU_READER_STATUS_READY;
    
        return;
    }
    
    // move to the next string entry address
    strReader->readAddress += strReader->readSize;
    strReader->readCount += 1;
    
    // request the next string entry
    strReader->header.state = ATTEMPT_STRING_ENTRY_SIZE_REQUEST;
    strReader->header.status = GFXU_READER_STATUS_READY;
}

static GFX_Result requestStringEntrySize(GFXU_StringAssetReader* strReader)
{
    // request the size of the next entry
    if(strReader->header.memIntf->read((GFXU_ExternalAssetReader*)strReader,
                                       strReader->string->header.dataLocation,
                                       strReader->readAddress,
                                       GFXU_STRING_ENTRY_SIZE,
                                       (uint8_t*)&strReader->readSize,
                                       (GFXU_MemoryReadRequestCallback_FnPtr)&stringEntrySizeRequestCompleted) == GFX_FAILURE)
    {
        return GFX_FAILURE;
    }
        
    // wait for the string entry data
    strReader->header.status = GFXU_READER_STATUS_WAITING;
    strReader->header.state = WAITING_FOR_STRING_ENTRY_SIZE; 
    
    return GFX_SUCCESS;                             
}

static void stringDataRequestCompleted(GFXU_StringAssetReader* strReader)
{
    uint32_t charSize = 0;
    uint32_t width;
    
    // attempt to calculate the code point for the glyph
    if(GFXU_DecodeCodePoint(strReader->string->encodingMode,
                            strReader->stringData,
                            strReader->readSize - strReader->readCount,
                            &strReader->codePoint,
                            &charSize) == GFX_FAILURE)
    {
        // the string data is invalid, abort operation
        strReader->header.status = GFXU_READER_STATUS_FINISHED;
        strReader->header.state = DONE;
        
        return;
    }              
    
    // advance the string character read count
    strReader->readCount += charSize;
    strReader->readAddress += charSize;

    // get the font glyph info from one of the available lookup tables
    if(GFXU_FontGetGlyphInfo(strReader->font,
                             strReader->codePoint,
                             &strReader->glyphOffset,
                             &strReader->glyphWidth) == GFX_FAILURE)
    {
        // the glyph codepoint is not in the available ranges, draw unknown glyph
        GFXU_DrawUnknownGlyph(strReader->x,
                              strReader->y + (strReader->font->height - (strReader->font->ascent + strReader->font->descent)),
                              strReader->font->ascent + strReader->font->descent,
                              &width);
                              
        // advance the draw position
        strReader->x += width;
        
        strReader->header.state = ATTEMPT_STRING_DATA_REQUEST;
        strReader->header.status = GFXU_READER_STATUS_READY;
    }
                          
    // we have a valid code point and an offset pointer into some array
    // of font data.  attempt to draw the glyph
    strReader->glyphRow = 0;
    
    // if the font data is stored locally then use that path
    if(strReader->font->header.dataLocation == GFXU_ASSET_LOCATION_INTERNAL)
        strReader->header.state = INTERNAL_FONT_DATA_READ;
    // else use the streaming font data path
    else
        strReader->header.state = PREPARE_FONT_DATA_REQUEST;
        
    strReader->header.status = GFXU_READER_STATUS_READY;
}

static GFX_Result requestStringData(GFXU_StringAssetReader* strReader)
{
    // have we read the entire string?
    if(strReader->readCount == strReader->readSize)
    {
        strReader->header.status = GFXU_READER_STATUS_FINISHED;
        strReader->header.state = DONE;
        
        if(strReader->glyphData != GFX_NULL)
        {
            strReader->header.memIntf->heap.free(strReader->glyphData);
            strReader->glyphData = GFX_NULL;
        }
        
        return GFX_SUCCESS; 
    }
    
    // read a chunk of string data
    if(strReader->header.memIntf->read((GFXU_ExternalAssetReader*)strReader,
                                       strReader->string->header.dataLocation,
                                       strReader->readAddress,
                                       strReader->readSize,
                                       (uint8_t*)&strReader->stringData,
                                       (GFXU_MemoryReadRequestCallback_FnPtr)&stringDataRequestCompleted) == GFX_FAILURE)
    {
        return GFX_FAILURE;
    }
        
    strReader->header.status = GFXU_READER_STATUS_WAITING;
    strReader->header.state = WAITING_FOR_STRING_DATA; 
    
    return GFX_SUCCESS;                             
}

static GFX_Result prepareFontDataRequest(GFXU_StringAssetReader* strReader)
{
    // calculate the size in bytes of a row of glyph pixels
    if(strReader->font->bpp == GFXU_FONT_BPP_1)
    {
        strReader->glyphDataSize = strReader->glyphWidth >> 3;
        
        if(strReader->glyphWidth % 8 > 0)
            strReader->glyphDataSize++;
    }
    else if(strReader->font->bpp == GFXU_FONT_BPP_8)
    {
        strReader->glyphDataSize = strReader->glyphWidth;
    }
    
    // adjust the glyph row data array
    if(strReader->glyphDataCapacity == 0 ||
       strReader->glyphDataCapacity < strReader->glyphDataSize)
    {
        // free the pointer if it is valid
        if(strReader->glyphData != GFX_NULL)
            strReader->header.memIntf->heap.free(strReader->glyphData);
            
        // calculate sizes and capacities
        strReader->glyphDataCapacity = strReader->glyphDataSize;
        strReader->glyphData = strReader->header.memIntf->heap.malloc(strReader->glyphDataCapacity);
    
        if(strReader->glyphData == GFX_NULL)
        {
            // failed to get the necessary memory, can't do anything else
            strReader->header.status = GFXU_READER_STATUS_FINISHED;
            strReader->header.state = DONE;
        }
    }
    
    // set the glyph address
    strReader->glyphDataAddress = ((uint8_t*)strReader->font->header.dataAddress) +
                                  strReader->glyphOffset;
    
    // request some glyph data
    strReader->header.status = GFXU_READER_STATUS_READY;
    strReader->header.state = ATTEMPT_FONT_DATA_REQUEST;
    
    return GFX_SUCCESS;
}

static GFX_Result internalFontDataRead(GFXU_StringAssetReader* strReader)
{
    uint32_t offset, r;
    uint8_t* data;
    
    // font data is internal, simply find the offset in the data blob
    data = ((uint8_t*)strReader->font->header.dataAddress);
    data += strReader->glyphOffset;
    
    // iterate and draw the data
    for(r = 0; r < strReader->font->height; r++)
    {
        GFXU_DrawGlyphRow(strReader->font->bpp,
                          data,
                          strReader->glyphWidth,
                          strReader->x,
                          strReader->y + r,
                          &offset);
                          
        data += offset;
    }
    
    // advance the draw position
    strReader->x += strReader->glyphWidth;
        
    // read the next character
    strReader->header.state = ATTEMPT_STRING_DATA_REQUEST;
    strReader->header.status = GFXU_READER_STATUS_READY;

    return GFX_SUCCESS;
}

static void fontDataRequestCompleted(GFXU_StringAssetReader* strReader)
{
    // got some font data, prepare to draw it
    strReader->header.status = GFXU_READER_STATUS_READY;
    strReader->header.state = DRAW_GLYPH_DATA; 
}

static GFX_Result requestFontData(GFXU_StringAssetReader* strReader)
{
    // read a chunk of font data
    if(strReader->header.memIntf->read((GFXU_ExternalAssetReader*)strReader,
                                       strReader->font->header.dataLocation,
                                       strReader->glyphDataAddress,
                                       strReader->glyphDataSize,
                                       (uint8_t*)strReader->glyphData,
                                       (GFXU_MemoryReadRequestCallback_FnPtr)&fontDataRequestCompleted) == GFX_FAILURE)
    {
        return GFX_FAILURE;
    }
        
    // wait for the font data
    strReader->header.status = GFXU_READER_STATUS_WAITING;
    strReader->header.state = WAITING_FOR_FONT_DATA; 
    
    return GFX_SUCCESS;                           
}

static GFX_Result drawGlyphRow(GFXU_StringAssetReader* strReader)
{
    uint32_t offset;
    
    // draw the glyph
    if(GFXU_DrawGlyphRow(strReader->font->bpp,
                         strReader->glyphData,
                         strReader->glyphWidth,
                         strReader->x,
                         strReader->y + strReader->glyphRow,
                         &offset) == GFX_FAILURE)
    {
        return GFX_FAILURE;
    }
    
    // prepare for next string data read
    strReader->glyphRow += 1;
    
    // check to see if the entire glyph has been rendered
    if(strReader->glyphRow == strReader->font->height)
    {
        // advance draw point
        strReader->x += strReader->glyphWidth;
        
        // get some more string data
        strReader->header.state = ATTEMPT_STRING_DATA_REQUEST;
        strReader->header.status = GFXU_READER_STATUS_READY;
    
        return GFX_SUCCESS;
    }
    
    // advance the glyph data address to the next row
    strReader->glyphDataAddress = ((uint8_t*)strReader->font->header.dataAddress) +
                                  strReader->glyphOffset +
                                  (strReader->glyphDataSize * strReader->glyphRow);
    
    // read some glyph data
    strReader->header.state = ATTEMPT_FONT_DATA_REQUEST;
    strReader->header.status = GFXU_READER_STATUS_READY;
    
    return GFX_SUCCESS;                             
}

static GFX_Result run(GFXU_ExternalAssetReader* reader)
{
    GFXU_StringAssetReader* strReader = (GFXU_StringAssetReader*)reader;
    
    if(strReader == GFX_NULL)
        return GFX_FAILURE;
    
    switch(strReader->header.state)
    {
        case INTERNAL_STRING_TABLE_READ:
            return internalStringTableRead(strReader);
        case ATTEMPT_STRING_ARRAY_SIZE_REQUEST:
            return requestStringArraySize(strReader);
        case ATTEMPT_STRING_ENTRY_SIZE_REQUEST:
            return requestStringEntrySize(strReader);
        case ATTEMPT_STRING_DATA_REQUEST:
            return requestStringData(strReader);
        case INTERNAL_FONT_DATA_READ:
            return internalFontDataRead(strReader);
        case PREPARE_FONT_DATA_REQUEST:
            return prepareFontDataRequest(strReader);
        case ATTEMPT_FONT_DATA_REQUEST:
            return requestFontData(strReader);
        case DRAW_GLYPH_DATA:
            return drawGlyphRow(strReader);
        case WAITING_FOR_STRING_ARRAY_SIZE:
        case WAITING_FOR_STRING_ENTRY_SIZE:
        case WAITING_FOR_FONT_DATA:
        default:
            return GFX_SUCCESS;
    }
}

GFX_Result GFXU_DrawStringExternal(GFXU_StringTableAsset* str,
                                   GFXU_FontAsset* fnt,
                                   uint32_t id,
                                   uint32_t lang,
                                   int32_t x,
                                   int32_t y,
                                   GFXU_MemoryIntf* memIntf,
                                   GFXU_ExternalAssetReader** reader)
{
    GFXU_StringAssetReader* strReader;
    
    // create the reader state manager object
    strReader = (GFXU_StringAssetReader*)memIntf->heap.calloc(1, 
                                             sizeof(GFXU_StringAssetReader));
    
    if(strReader == GFX_NULL)
        return GFX_FAILURE;
    
    // set reader state manager member variables
    strReader->header.memIntf = memIntf;
    strReader->header.run = &run;
    strReader->header.status = GFXU_READER_STATUS_READY;
    
    strReader->string = str;
    strReader->stringID = id;
    strReader->entryID = lang;
    
    strReader->font = fnt;
    
    strReader->x = x;
    strReader->y = y;
    
    strReader->readAddress = (uint8_t*)str->header.dataAddress;
    
    // first thing to do is examine the string table
    if(strReader->string->header.dataLocation == GFXU_ASSET_LOCATION_INTERNAL)
        strReader->header.state = INTERNAL_STRING_TABLE_READ;
    else
        strReader->header.state = ATTEMPT_STRING_ARRAY_SIZE_REQUEST;
    
    // return the reader as a generic pointer
    *reader = (GFXU_ExternalAssetReader*)strReader;

    return GFX_SUCCESS;
}

#if 0

GFX_Result GFXU_DrawStringInternal(GFXU_StringTableAsset* tbl,
                                   GFXU_FontAsset* fnt,
                                   uint32_t id,
                                   uint32_t lang,
                                   int32_t x,
                                   int32_t y,
                                   GFXU_MemoryIntf* memIntf,
                                   GFXU_ExternalAssetReader** reader)
{
    uint32_t i;
    uint8_t* stringAddress;
    uint32_t stringSize;
    
    stringAddress = (uint8_t*)tbl->header.dataAddress;
    
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
    }
    
    GFXU_DecodeAndDrawString(stringAddress,
                             stringSize,
                             tbl->encodingMode,
                             fnt,
                             x,
                             y);
    
    return GFX_SUCCESS;
}

#endif