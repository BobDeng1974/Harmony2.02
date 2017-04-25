#include "gfx/hal/inc/gfx_context.h"
#include "gfx/utils/inc/gfxu_image.h"
#include "gfx/utils/inc/gfxu_palette.h"

#define JPEG_SendError(x)  pJpegDecoder->bError = x; return(x); /* Point to proper error handler routine */

#define JPEG_SAMPLE_1x1 0
#define JPEG_SAMPLE_1x2 1
#define JPEG_SAMPLE_2x1 2
#define JPEG_SAMPLE_2x2 3

#define MAX_CHANNELS      3 /* This supports only Grayscale and YCbCr images - DONT CHANGE THIS */
#define MAX_BLOCKS        6 /* To decode one logical block, we have to decode 1 to 6 blocks depending on channels and subsampling - DONT REDUCE THIS */
#define MAX_HUFF_TABLES   2 /* Each causes 2 tables -> One for AC and another for DC - DONT REDUCE THIS */
#define MAX_DATA_BUF_LEN  512 /* Increase if you have more data memory */

#define EXIF_2_2_ORIENTATION_OFFSET 0x2E

/* Error list */
enum Errors
{
	IMAGE_FILE_NOT_AVAILABLE
};

/* JPEG Markers list */
enum Markers
{
	SOF0 = 0xC0,
	DHT = 0xC4,
	SOI = 0xD8,
	EOI = 0xD9,
	SOS = 0xDA,
	DQT = 0xDB,
	DRI = 0xDD,
	APP0 = 0xE0,
	APP1 = 0xE1, // EXIF
	COM = 0xFE,
	/* The below markers doesn't have parameters */
	TEM = 0x01,
	RST0 = 0xD0,
	RST1 = 0xD1,
	RST2 = 0xD2,
	RST3 = 0xD3,
	RST4 = 0xD4,
	RST5 = 0xD5,
	RST6 = 0xD6,
	RST7 = 0xD7
};

void jpeg_idct_islow (short *inbuf, uint16_t *quantptr);

/*************************/
/**** DATA STRUCTURES ****/
/*************************/
typedef struct _JPEGDECODER
{
        GFXU_ImageAsset *pImageFile;                       /* Image file pointer */
        GFX_PixelBuffer pixelBlockBuffer;                 /* Pointer to the pixel buffer for the current block to blit */
        GFX_ColorMode   colorMode;             /* Tracks the display color mode */
        
        uint32_t fileIndex;                    /* pointer to current location in image */

/*********** From APP0 ***********/
        uint8_t blJFIF;                            /* JFIF marker found flag */
        uint8_t bMajorRev;                         /* Should be 1 */
        uint8_t bMinorRev;                         /* Should be 0-2 but is not a show stopper */
        /*------- The x/y densities and thumbnail data are ignored --------*/

        /*********** From APP1 EXIF ***********/
        uint8_t bOrientation;
        
        /*********** From SOF0 ***********/
        uint8_t bDataBits;                         /* Data precision, can be 8(, 12 or 16) */
        uint16_t wWidth;                            /* Width in pixels */
        uint16_t wHeight;                           /* Height in pixels */
        uint8_t bChannels;                         /* Number of channels e.g. YCbCr = 3 */
        uint8_t abChannelType[MAX_CHANNELS];
        uint8_t abChannelHSampFactor[MAX_CHANNELS];
        uint8_t abChannelVSampFactor[MAX_CHANNELS];
        uint8_t abChannelQuantTableMap[MAX_CHANNELS];

        /*********** From DQT ***********/
        uint8_t blQuantUses16bits;                 /* If flag is set, it is an error as 16 bit is not supported */
        uint16_t awQuantTable[MAX_CHANNELS][64];    /* Supports only 8 & 16 bit resolutions */

        /*********** From DRI ***********/
        uint16_t wRestartInterval;                  /* The restart interval in blocks */

        /*********** From DHT ***********/
        uint8_t bHuffTables;
        uint8_t abHuffAcSymLen[MAX_HUFF_TABLES][16];   /* Supports only 8 bit resolution */
        uint8_t abHuffAcSymbol[MAX_HUFF_TABLES][256];  /* Maximum possible symbols are 256 */
        uint8_t abHuffDcSymLen[MAX_HUFF_TABLES][16];   /* Supports only 8 bit resolution */
        uint8_t abHuffDcSymbol[MAX_HUFF_TABLES][16];   /* Maximum possible symbols are 16 for DC :-) */
        /*********** For Huffman-Decoding ***********/
        uint16_t awHuffAcSymStart[MAX_HUFF_TABLES][16]; /* Starting symbol for each length */
        uint16_t awHuffDcSymStart[MAX_HUFF_TABLES][16]; /* Starting symbol for each length */

        /*********** From SOS ***********/
        uint8_t abChannelHuffAcTableMap[MAX_CHANNELS];
        uint8_t abChannelHuffDcTableMap[MAX_CHANNELS];

        uint8_t bError;

        /*********** Work memory ***********/
        uint16_t wWorkBits;
        uint8_t bBitsAvailable;
        uint8_t bBlocksInOnePass;
        short asOneBlock[MAX_BLOCKS][64];     /* Temporary storage for a 8x8 block */
        uint16_t  wBlockNumber;
        uint8_t  abChannelMap[MAX_BLOCKS];
        uint8_t  bSubSampleType;
        short asPrevDcValue[MAX_CHANNELS];
        uint8_t *pbCurrentHuffSymLenTable;
        uint8_t *pbCurrentHuffSymbolTable;
        uint16_t *pwCurrentHuffSymStartTable;
        uint16_t *pwCurrentQuantTable;
        uint8_t abDataBuffer[MAX_DATA_BUF_LEN];
        uint16_t wBufferLen;
        uint16_t wBufferIndex;
        uint8_t bFirstBit;

        int32_t wStartX;
        int32_t wStartY;
        
        int32_t wDrawWidth;
        int32_t wDrawHeight;
        
        int32_t wDrawX;
        int32_t wDrawY;        
        
        int32_t wPrevX;
        int32_t wPrevY;
        uint8_t handle; //handle to the driver instance
} JPEGDECODER;

/**************************/
/**** CONSTANT TABLES  ****/
/**************************/
static const uint8_t abZigzag[64] =
{
  0,  1,  8,  16, 9,  2,  3,  10,
  17, 24, 32, 25, 18, 11, 4,  5,
  12, 19, 26, 33, 40, 48, 41, 34,
  27, 20, 13, 6,  7,  14, 21, 28,
  35, 42, 49, 56, 57, 50, 43, 36,
  29, 22, 15, 23, 30, 37, 44, 51,
  58, 59, 52, 45, 38, 31, 39, 46,
  53, 60, 61, 54, 47, 55, 62, 63
};

static void JPEG_Seek(JPEGDECODER* decoder, long offset, int whence)
{
    if(whence == 0)
    {
        decoder->fileIndex = offset;        
    }
    else if(whence == 1)
    {
        decoder->fileIndex += offset;        
    }
}

static size_t JPEG_Read(void *ptr, size_t size, size_t n, JPEGDECODER* decoder)
{
    size_t count = 0;
    uint8_t* pFile;
    uint8_t* bptr;
    
    pFile = (uint8_t*)decoder->pImageFile->header.dataAddress;
    bptr = (uint8_t *)ptr;
    
    for(count = 0; count < size * n; ++count)
    {
        bptr[count] = (uint8_t) pFile[decoder->fileIndex];
        ++decoder->fileIndex;
    }        
    return count;
}

/*******************************************************************************
Function:       void JPEG_vResetDecoder(JPEGDECODER *pJpegDecoder)

Precondition:   None

Overview:       This function resets the variables so that new jpeg image can be
                decoded

Input:          JPEGDECODER

Output:         None
*******************************************************************************/
static void JPEG_vResetDecoder(JPEGDECODER *decoder)
{
    uint16_t wIndex;
    uint8_t *pbptr = (uint8_t*)decoder;
    for(wIndex = 0; wIndex < sizeof(JPEGDECODER); wIndex++)
    {
        pbptr[wIndex] = 0;
    }
}

/*******************************************************************************
Function:       uint16_t JPEG_wReadWord(GFXU_ImageAsset *pfile)

Precondition:   None

Overview:       This function reads and returns a single word obtained as
                Higher byte first followed by lower byte

Input:          Image file

Output:         One word
*******************************************************************************/
static uint16_t JPEG_wReadWord(JPEGDECODER *decoder)
{
     uint8_t btemp;
     uint16_t wData;
     
     JPEG_Read(&btemp, sizeof(btemp), 1, decoder);
     wData = btemp;
     JPEG_Read(&btemp, sizeof(btemp), 1, decoder);
     wData = (wData << 8) | btemp;
     
     return wData;
}

/*******************************************************************************
Function:       uint8_t JPEG_bReadByte(GFXU_ImageAsset *pfile)

Precondition:   None

Overview:       This function reads and returns a single byte from the file

Input:          Image file

Output:         One byte
*******************************************************************************/
static uint8_t JPEG_bReadByte(JPEGDECODER *decoder)
{
     uint8_t bData;
     
     JPEG_Read(&bData, sizeof(bData), 1, decoder);

     return bData;
}

/*******************************************************************************
Function:       uint8_t JPEG_bReadHeader(JPEGDECODER *pJpegDecoder)

Precondition:   None

Overview:       This function reads the JPEG file header and 
                fills the data structure

Input:          JPEGDECODER

Output:         Error code - '0' means no error
*******************************************************************************/
static uint8_t JPEG_bReadHeader(JPEGDECODER *pJpegDecoder)
{
     GFX_Bool blSOSOver = 0;
     while(pJpegDecoder->fileIndex * sizeof(uint8_t)
             < pJpegDecoder->pImageFile->header.dataSize)
     {
             uint8_t btemp, bcount, bsection;
             uint16_t wSegLen, wOffset;
             
             if(blSOSOver == 1)
             {
                     if(pJpegDecoder->bChannels == 1)
                     {
                             pJpegDecoder->bBlocksInOnePass = 1;
                             pJpegDecoder->bSubSampleType = JPEG_SAMPLE_1x1;
                     }    
                     else if(pJpegDecoder->bChannels == 3)
                     {
                             if((pJpegDecoder->abChannelHSampFactor[0] == 1 && pJpegDecoder->abChannelVSampFactor[0] == 1) &&
                                (pJpegDecoder->abChannelHSampFactor[1] == 1 && pJpegDecoder->abChannelVSampFactor[1] == 1) &&
                                (pJpegDecoder->abChannelHSampFactor[2] == 1 && pJpegDecoder->abChannelVSampFactor[2] == 1))
                             {
                                     pJpegDecoder->bBlocksInOnePass = 3;
                                     pJpegDecoder->abChannelMap[0] = 0;
                                     pJpegDecoder->abChannelMap[1] = 1;
                                     pJpegDecoder->abChannelMap[2] = 2;
                                     pJpegDecoder->bSubSampleType = JPEG_SAMPLE_1x1;
                             }
                             else if((pJpegDecoder->abChannelHSampFactor[0] == 1 && pJpegDecoder->abChannelVSampFactor[0] == 2) &&
                                     (pJpegDecoder->abChannelHSampFactor[1] == 1 && pJpegDecoder->abChannelVSampFactor[1] == 1) &&
                                     (pJpegDecoder->abChannelHSampFactor[2] == 1 && pJpegDecoder->abChannelVSampFactor[2] == 1))
                             {
                                     pJpegDecoder->bBlocksInOnePass = 4;
                                     pJpegDecoder->abChannelMap[0] = 0;
                                     pJpegDecoder->abChannelMap[1] = 0;
                                     pJpegDecoder->abChannelMap[2] = 1;
                                     pJpegDecoder->abChannelMap[3] = 2;
                                     pJpegDecoder->bSubSampleType = JPEG_SAMPLE_1x2;
                             }
                             else if((pJpegDecoder->abChannelHSampFactor[0] == 2 && pJpegDecoder->abChannelVSampFactor[0] == 1) &&
                                     (pJpegDecoder->abChannelHSampFactor[1] == 1 && pJpegDecoder->abChannelVSampFactor[1] == 1) &&
                                     (pJpegDecoder->abChannelHSampFactor[2] == 1 && pJpegDecoder->abChannelVSampFactor[2] == 1))
                             {
                                     pJpegDecoder->bBlocksInOnePass = 4;
                                     pJpegDecoder->abChannelMap[0] = 0;
                                     pJpegDecoder->abChannelMap[1] = 0;
                                     pJpegDecoder->abChannelMap[2] = 1;
                                     pJpegDecoder->abChannelMap[3] = 2;
                                     pJpegDecoder->bSubSampleType = JPEG_SAMPLE_2x1;
                             }
                             else if((pJpegDecoder->abChannelHSampFactor[0] == 2 && pJpegDecoder->abChannelVSampFactor[0] == 2) &&
                                     (pJpegDecoder->abChannelHSampFactor[1] == 1 && pJpegDecoder->abChannelVSampFactor[1] == 1) &&
                                     (pJpegDecoder->abChannelHSampFactor[2] == 1 && pJpegDecoder->abChannelVSampFactor[2] == 1))
                             {
                                     pJpegDecoder->bBlocksInOnePass = 6;
                                     pJpegDecoder->abChannelMap[0] = 0;
                                     pJpegDecoder->abChannelMap[1] = 0;
                                     pJpegDecoder->abChannelMap[2] = 0;
                                     pJpegDecoder->abChannelMap[3] = 0;
                                     pJpegDecoder->abChannelMap[4] = 1;
                                     pJpegDecoder->abChannelMap[5] = 2;
                                     pJpegDecoder->bSubSampleType = JPEG_SAMPLE_2x2;
                             }
                             else
                             {
                                     JPEG_SendError(100);
                             }
                     }
                     return 0;
             }

             JPEG_Read(&btemp, sizeof(btemp), 1, pJpegDecoder);

             if(btemp != 0xFF)
             {
                     continue;
             }

             JPEG_Read(&bsection, sizeof(bsection), 1, pJpegDecoder);
             switch(bsection)
             {
               case SOI:
               case TEM:
               case EOI:
               case RST0:
               case RST1:
               case RST2:
               case RST3:
               case RST4:
               case RST5:
               case RST6:
               case RST7: break;

               case SOF0: /* Start of frame */
                          wSegLen = JPEG_wReadWord(pJpegDecoder);
                          if(wSegLen <= 8)
                          {
                                     JPEG_SendError(100);
                                     break;
                          }
                          pJpegDecoder->bDataBits = JPEG_bReadByte(pJpegDecoder);
                          pJpegDecoder->wHeight   = JPEG_wReadWord(pJpegDecoder);
                          pJpegDecoder->wWidth    = JPEG_wReadWord(pJpegDecoder);
                          pJpegDecoder->bChannels = JPEG_bReadByte(pJpegDecoder);
                          if(wSegLen < 8 + (pJpegDecoder->bChannels * 3))
                          {
                                     JPEG_SendError(100);
                                     break;
                          }
                          for(bcount = 0; bcount < pJpegDecoder->bChannels; bcount++)
                          {
                                     pJpegDecoder->abChannelType[bcount] = JPEG_bReadByte(pJpegDecoder);
                                     btemp = JPEG_bReadByte(pJpegDecoder);
                                     pJpegDecoder->abChannelHSampFactor[bcount] = btemp >> 4;
                                     pJpegDecoder->abChannelVSampFactor[bcount] = btemp & 0x0F;
                                     pJpegDecoder->abChannelQuantTableMap[bcount] = JPEG_bReadByte(pJpegDecoder);
                          }
                          break;

               case APP0: /* Start of Application */
                          wSegLen = JPEG_wReadWord(pJpegDecoder);
                          if(wSegLen < 16)
                          {
                                     JPEG_SendError(100);
                                     break;
                          }
                          else
                          {
                                     unsigned char buf[5];
                                     JPEG_Read(buf, sizeof(buf[0]), 5, pJpegDecoder);
                                     if(buf[0] == 'J' && buf[1] == 'F' && buf[2] == 'I' && buf[3] == 'F' && buf[4] == '\0')
                                     {
                                        pJpegDecoder->blJFIF = 1;
                                     }
                          }
                          pJpegDecoder->bMajorRev = JPEG_bReadByte(pJpegDecoder);
                          pJpegDecoder->bMinorRev = JPEG_bReadByte(pJpegDecoder);
                          if(pJpegDecoder->bMajorRev != 1)
                          {
                                     JPEG_SendError(100);
                                     break;
                          }
                          /* Ignore other bytes in this segment */
                          break;
                          
               case DRI: /* Start of Quantization table */
                    wSegLen = JPEG_wReadWord(pJpegDecoder);
                    if(wSegLen == 4)
                    {
                               pJpegDecoder->wRestartInterval = JPEG_wReadWord(pJpegDecoder);
                    }
                    break;
                    
               case DQT: /* Start of Quantization table */
                          wSegLen = JPEG_wReadWord(pJpegDecoder);
                          if(wSegLen < 67)
                          {
                                     JPEG_SendError(100);
                                     break;
                          }

                          do
                          {
                                     uint8_t bQTableIndex, bCounter;

                                     btemp = JPEG_bReadByte(pJpegDecoder);
                                     bQTableIndex = btemp & 0x0F;
                                     pJpegDecoder->blQuantUses16bits |= (btemp >> 4);
                                     
                                     for(bCounter = 0; bCounter < 64; bCounter++)
                                     {
                                               uint8_t bData1, bData2 = 0;
                                               if(pJpegDecoder->blQuantUses16bits == 0)
                                               {
                                                         JPEG_Read(&bData1, sizeof(uint8_t), 1, pJpegDecoder);
                                                         pJpegDecoder->awQuantTable[bQTableIndex][abZigzag[bCounter]] = bData1;
                                               }
                                               else
                                               {
                                                         JPEG_Read(&bData1, sizeof(uint8_t), 1, pJpegDecoder);
                                                         JPEG_Read(&bData2, sizeof(uint8_t), 1, pJpegDecoder);
                                                         pJpegDecoder->awQuantTable[bQTableIndex][abZigzag[bCounter]] = (((uint16_t)bData1) << 8) + (uint16_t)bData2;
                                               }
                                     }
                                     wSegLen -= (pJpegDecoder->blQuantUses16bits == 0)? 65: 129; /* Table length + information byte */
                          } while(wSegLen >= 67);
                          break;

               case DHT: /* Start of Huffmann table */
                          wSegLen = JPEG_wReadWord(pJpegDecoder);
                          if(wSegLen < 19)
                          {
                                     JPEG_SendError(100);
                                     break;
                          }

                          do
                          {
                                     uint8_t bHTableIndex, bCounter;
                                     uint16_t wNumOfSymbols;
                                     uint8_t blIsAc;
                                     uint8_t *pbLenTable, *pbSymTable;

                                     btemp = JPEG_bReadByte(pJpegDecoder);
                                     bHTableIndex = btemp & 0x0F;
                                     blIsAc = (btemp >> 4) & 0x01;
                                     
                                     if(blIsAc == 0)
                                     {
                                               pbLenTable = (uint8_t*)&pJpegDecoder->abHuffDcSymLen[bHTableIndex][0];
                                               pbSymTable = (uint8_t*)&pJpegDecoder->abHuffDcSymbol[bHTableIndex][0];
                                     }
                                     else
                                     {
                                               pbLenTable = (uint8_t*)&pJpegDecoder->abHuffAcSymLen[bHTableIndex][0];
                                               pbSymTable = (uint8_t*)&pJpegDecoder->abHuffAcSymbol[bHTableIndex][0];
                                     }

                                     JPEG_Read(pbLenTable, sizeof(uint8_t), 16, pJpegDecoder);

                                     for(bCounter = 0, wNumOfSymbols = 0; bCounter < 16; bCounter++)
                                     {
                                               wNumOfSymbols += pbLenTable[bCounter];
                                     }

                                     wSegLen -= 17; /* This table length + information byte */

                                     if(wSegLen < wNumOfSymbols || (blIsAc == 1 && wNumOfSymbols > 256) || (blIsAc == 0 && wNumOfSymbols > 16))
                                     {
                                               JPEG_SendError(100);
                                               break;
                                     }

                                     JPEG_Read(pbSymTable, sizeof(uint8_t), wNumOfSymbols, pJpegDecoder);
                                     wSegLen -= wNumOfSymbols; /* This table length + information byte */
                                     pJpegDecoder->bHuffTables++;
                          } while(wSegLen >= 19);
                          break;

               case SOS: /* Start of Scan parameters */
                          wSegLen = JPEG_wReadWord(pJpegDecoder);
                          if(wSegLen < 3)
                          {
                                     JPEG_SendError(100);
                                     break;
                          }

                          btemp = JPEG_bReadByte(pJpegDecoder);
                          wOffset = wSegLen - (3 + (btemp << 1));

                          if(pJpegDecoder->bChannels != btemp || wSegLen < 3 + (btemp << 1))
                          {
                                     JPEG_SendError(100);
                                     break;
                          }
                          else
                          {
                                     uint8_t bCounter, bChannelId = 0xFF;
                                     
                                     for(bCounter = 0; bCounter < pJpegDecoder->bChannels; bCounter++)
                                     {
                                               uint8_t bindex;

                                               btemp = JPEG_bReadByte(pJpegDecoder);
                                               for(bindex = 0; bindex < MAX_CHANNELS; bindex++)
                                               {
                                                          if(pJpegDecoder->abChannelType[bindex] == btemp)
                                                          {
                                                                    bChannelId = bindex;
                                                                    break;
                                                          }
                                               }

                                               if(bChannelId < MAX_CHANNELS)
                                               {
                                                          btemp = JPEG_bReadByte(pJpegDecoder);
                                                          pJpegDecoder->abChannelHuffAcTableMap[bChannelId] = btemp & 0x0F;
                                                          pJpegDecoder->abChannelHuffDcTableMap[bChannelId] = btemp >> 4;
                                               }
                                     }
                                     JPEG_Seek(pJpegDecoder, wOffset, 1);
                          }
                          blSOSOver = 1;
                          break;

               default: /* Any other segment with length */
                          wSegLen = JPEG_wReadWord(pJpegDecoder);
                          if(wSegLen < 2)
                          {
                                     JPEG_SendError(100);
                                     break;
                          }
                          JPEG_Seek(pJpegDecoder, wSegLen - 2, 1);
             }
     }
     return (pJpegDecoder->blJFIF == 1) ? 0 : 1;
}

/*******************************************************************************
Function:       uint8_t JPEG_bGenerateHuffmanTables(JPEGDECODER *pJpegDecoder)

Precondition:   None

Overview:       This function generated the table required for Huffman decoding
                from the data read from the header

Input:          JPEGDECODER

Output:         Error code - '0' means no error
*******************************************************************************/
static uint8_t JPEG_bGenerateHuffmanTables(JPEGDECODER *pJpegDecoder)
{
     uint8_t bLength, bTable;

     for(bTable = 0; bTable < pJpegDecoder->bHuffTables / 2; bTable++)
     {
            pJpegDecoder->awHuffAcSymStart[bTable][0] = 0;
            pJpegDecoder->awHuffDcSymStart[bTable][0] = 0;

            for(bLength = 1; bLength < 16; bLength++)
            {
                   pJpegDecoder->awHuffAcSymStart[bTable][bLength] = (pJpegDecoder->awHuffAcSymStart[bTable][bLength - 1] + pJpegDecoder->abHuffAcSymLen[bTable][bLength - 1]) << 1;
                   pJpegDecoder->awHuffDcSymStart[bTable][bLength] = (pJpegDecoder->awHuffDcSymStart[bTable][bLength - 1] + pJpegDecoder->abHuffDcSymLen[bTable][bLength - 1]) << 1;
            }
     }
     return 0;
}

/*******************************************************************************
Function:       uint8_t JPEG_bGet1Bit(JPEGDECODER *pJpegDecoder)

Precondition:   None

Overview:       This function returns 1 bit as the lsb of the returned byte.
                It automatically fills the buffer if it becomes empty.
                It also converts 0xFF00 into 0.

Input:          JPEGDECODER

Output:         One bit
*******************************************************************************/
static uint8_t JPEG_bGet1Bit(JPEGDECODER *pJpegDecoder)
{
     uint8_t bBit = 0;

     if(pJpegDecoder->wBufferIndex >= pJpegDecoder->wBufferLen)
     {
            pJpegDecoder->wBufferLen = JPEG_Read(&pJpegDecoder->abDataBuffer[0], sizeof(uint8_t), MAX_DATA_BUF_LEN, pJpegDecoder);
            while(pJpegDecoder->abDataBuffer[pJpegDecoder->wBufferLen - 1] == 0xFF)
            {
                   pJpegDecoder->wBufferLen--;
                   JPEG_Seek(pJpegDecoder, -1, 1);
            }
            pJpegDecoder->wBufferIndex = 0;
     }

     while(pJpegDecoder->bBitsAvailable == 0) /* Be very careful to touch this part of code! You must know exactly what you are doing */
     {
            pJpegDecoder->bBitsAvailable = 16;
            pJpegDecoder->wWorkBits = pJpegDecoder->abDataBuffer[pJpegDecoder->wBufferIndex++];
            pJpegDecoder->wWorkBits = (pJpegDecoder->wWorkBits << 8) + pJpegDecoder->abDataBuffer[pJpegDecoder->wBufferIndex++];
            if(pJpegDecoder->wBufferIndex > pJpegDecoder->wBufferLen) /* wBufferIndex need not be even because of the below condition */
            {
                   pJpegDecoder->bBitsAvailable = 8;
            }
            else if((pJpegDecoder->wWorkBits & 0x00FF) == 0x00FF)
            {
                   pJpegDecoder->bBitsAvailable = 8;
                   pJpegDecoder->wBufferIndex--;
            }
            else if(pJpegDecoder->wWorkBits >= 0xFF00)
            {
                   if(pJpegDecoder->wWorkBits == 0xFF00)
                   {
                         pJpegDecoder->bBitsAvailable = 8;
                   }
            }
     }

     bBit = (pJpegDecoder->wWorkBits & 0x8000)? 0x01: 0;

     pJpegDecoder->wWorkBits <<= 1;
     pJpegDecoder->bBitsAvailable--;

     return bBit;
}

/*******************************************************************************
Function:       uint16_t JPEG_wGetBits(JPEGDECODER *pJpegDecoder, uint8_t bLen)

Precondition:   None

Overview:       This function returns bLen number of bits as the lsb of the
                returned word and it automatically fills the buffer
                if it becomes empty.

Input:          JPEGDECODER, Number of bits

Output:         Requested number of bits
*******************************************************************************/
static uint16_t JPEG_wGetBits(JPEGDECODER *pJpegDecoder, uint8_t bLen)
{
     uint16_t wVal = 0;

     wVal = pJpegDecoder->bFirstBit = JPEG_bGet1Bit(pJpegDecoder);
     bLen--;

     while(bLen)
     {
            wVal = (wVal << 1) + JPEG_bGet1Bit(pJpegDecoder);
            bLen--;
     }

     return wVal;   
}

/*******************************************************************************
Function:       uint16_t JPEG_wGetRestartWord(JPEGDECODER *pJpegDecoder)

Precondition:   File pointer must point to the restart word

Overview:       Returns the restart word

Input:          JPEGDECODER

Output:         Restart word
*******************************************************************************/
static uint16_t JPEG_wGetRestartWord(JPEGDECODER *pJpegDecoder)
{
     uint16_t wRestartWord;
     while((pJpegDecoder->bBitsAvailable & 0x07) != 0) /* This is to clearoff wnwanted bits to go to fresh byte */
     {
            JPEG_bGet1Bit(pJpegDecoder);
     }
     wRestartWord = JPEG_wGetBits(pJpegDecoder, 16);
     return(wRestartWord);
}

/*******************************************************************************
Function:       int16_t JPEG_sGetBitsValue(JPEGDECODER *pJpegDecoder, uint8_t bLen)

Precondition:   None

Overview:       Returns the signed value of the bLen bits of data

Input:          JPEGDECODER, Number of bits

Output:         Signed number
*******************************************************************************/
static int16_t JPEG_sGetBitsValue(JPEGDECODER *pJpegDecoder, uint8_t bLen)
{
     uint16_t wVal = 0;

     if(bLen != 0)
     {  
            wVal = JPEG_wGetBits(pJpegDecoder, bLen);
            if(pJpegDecoder->bFirstBit == 0)
            {
                   wVal = ~(wVal | (0xFFFF << bLen));
                   return ((int16_t)wVal * -1);
            }
     }
     return (int16_t)wVal;
}

/*******************************************************************************
Function:       uint8_t JPEG_bGetNextHuffByte(JPEGDECODER *pJpegDecoder)

Precondition:   File pointer must point to the Huffman data

Overview:       Returns the Huffman decoded data

Input:          JPEGDECODER

Output:         Huffman decoded data
*******************************************************************************/
static uint8_t JPEG_bGetNextHuffByte(JPEGDECODER *pJpegDecoder)
{
     uint8_t bBits, bSymbol = 0;
     uint16_t wBitPattern = 0, wSymbolOffset = 0;

     for(bBits = 0; bBits < 16; bBits++)
     {
            uint8_t bSymbols;
            uint16_t wDiff;

            wBitPattern = (wBitPattern << 1) + JPEG_bGet1Bit(pJpegDecoder);
            bSymbols = pJpegDecoder->pbCurrentHuffSymLenTable[bBits];
            if(bSymbols == 0)
            {
                   continue;
            }

            wDiff = wBitPattern - pJpegDecoder->pwCurrentHuffSymStartTable[bBits];
            if(wDiff < bSymbols)
            {
                   bSymbol = pJpegDecoder->pbCurrentHuffSymbolTable[wSymbolOffset + wDiff];
                   break;
            }
            wSymbolOffset += bSymbols;
     }
     return bSymbol;
}

#define range_limit(x) (x<0)?0:(x>0xFF)?0xFF:x
/*******************************************************************************
Function:       uint8_t JPEG_bDecodeOneBlock(JPEGDECODER *pJpegDecoder)

Precondition:   File pointer must point to a new block of data

Overview:       Decodes the 8x8 pixel values of all the channels
                (A multiple of 8x8 block if subsampling is used)

Input:          JPEGDECODER

Output:         Error code - '0' means no error
*******************************************************************************/
static uint8_t JPEG_bDecodeOneBlock(JPEGDECODER *pJpegDecoder)
{
     uint8_t bBlock, bCounter;


     for(bBlock = 0; bBlock < pJpegDecoder->bBlocksInOnePass; bBlock++)
     {
            uint8_t bByteCount, bHuffbyte;

            if((pJpegDecoder->wRestartInterval > 0) && (pJpegDecoder->wBlockNumber == pJpegDecoder->wRestartInterval * pJpegDecoder->bBlocksInOnePass))
            {
                   uint16_t wRestartWord = JPEG_wGetRestartWord(pJpegDecoder);
                   if(wRestartWord < 0xFFD0 || wRestartWord > 0xFFD7)
                   {
                            JPEG_SendError(100);
                   }                          
                   for(bCounter = 0; bCounter < MAX_CHANNELS; bCounter++)
                   {
                            pJpegDecoder->asPrevDcValue[bCounter] = 0;
                   }                   
                   pJpegDecoder->wBlockNumber = 0;
            }

            for(bCounter = 0; bCounter < 64; bCounter++)
            {
                   pJpegDecoder->asOneBlock[bBlock][bCounter] = 0;
            }

            pJpegDecoder->pwCurrentQuantTable = &pJpegDecoder->awQuantTable[pJpegDecoder->abChannelQuantTableMap[pJpegDecoder->abChannelMap[bBlock]]][0];

            /* Decode DC value */
            bByteCount = 0;
            pJpegDecoder->pbCurrentHuffSymLenTable = &pJpegDecoder->abHuffDcSymLen[pJpegDecoder->abChannelHuffDcTableMap[pJpegDecoder->abChannelMap[bBlock]]][0];
            pJpegDecoder->pbCurrentHuffSymbolTable = &pJpegDecoder->abHuffDcSymbol[pJpegDecoder->abChannelHuffDcTableMap[pJpegDecoder->abChannelMap[bBlock]]][0];
            pJpegDecoder->pwCurrentHuffSymStartTable = &pJpegDecoder->awHuffDcSymStart[pJpegDecoder->abChannelHuffDcTableMap[pJpegDecoder->abChannelMap[bBlock]]][0];
            bHuffbyte = JPEG_bGetNextHuffByte(pJpegDecoder);
            pJpegDecoder->asOneBlock[bBlock][0] = JPEG_sGetBitsValue(pJpegDecoder, bHuffbyte & 0x0F) + pJpegDecoder->asPrevDcValue[pJpegDecoder->abChannelMap[bBlock]];
            pJpegDecoder->asPrevDcValue[pJpegDecoder->abChannelMap[bBlock]] = pJpegDecoder->asOneBlock[bBlock][0];

            /* Decode AC value */
            bByteCount = 1;
            pJpegDecoder->pbCurrentHuffSymLenTable = &pJpegDecoder->abHuffAcSymLen[pJpegDecoder->abChannelHuffAcTableMap[pJpegDecoder->abChannelMap[bBlock]]][0];
            pJpegDecoder->pbCurrentHuffSymbolTable = &pJpegDecoder->abHuffAcSymbol[pJpegDecoder->abChannelHuffAcTableMap[pJpegDecoder->abChannelMap[bBlock]]][0];
            pJpegDecoder->pwCurrentHuffSymStartTable = &pJpegDecoder->awHuffAcSymStart[pJpegDecoder->abChannelHuffAcTableMap[pJpegDecoder->abChannelMap[bBlock]]][0];
            while(bByteCount < 64)
            {
                   bHuffbyte = JPEG_bGetNextHuffByte(pJpegDecoder);
                   bByteCount += (bHuffbyte >> 4);
                   if(bHuffbyte == 0 /* EOB */)
                   {
                          break;
                   }
                   if(bByteCount > 63)
                   {
                          JPEG_SendError(100);
                   }
                   pJpegDecoder->asOneBlock[bBlock][abZigzag[bByteCount++]] = JPEG_sGetBitsValue(pJpegDecoder, bHuffbyte & 0x0F);
            }
            pJpegDecoder->wBlockNumber++;
            jpeg_idct_islow(&pJpegDecoder->asOneBlock[bBlock][0],pJpegDecoder->pwCurrentQuantTable);
     }

     return 0;
}

#define JPEG_WRITE_TO_DISPLAY
/*******************************************************************************
Function:       void JPEG_vInitDisplay(JPEGDECODER *pJpegDecoder)

Precondition:   None

Overview:       Initializes the (x, y) co-ordinates to (0, 0)

Input:          JPEGDECODER

Output:         None
*******************************************************************************/
static void JPEG_vInitDisplay(JPEGDECODER *pJpegDecoder)
{
    pJpegDecoder->wPrevX = 0;
    pJpegDecoder->wPrevY = 0;
}

/*******************************************************************************
Function:       uint8_t JPEG_bPaintOneBlock(JPEGDECODER *pJpegDecoder)

Precondition:   One block - 8x8 pixel data of all channels must be decoded

Overview:       Displays one 8x8 on the screen
                (A multiple of 8x8 block if subsampling is used)

Input:          JPEGDECODER

Output:         Error code - '0' means no error
*******************************************************************************/
static uint8_t JPEG_bPaintOneBlock(JPEGDECODER *pJpegDecoder)
{
    static uint16_t wX, wY, wX2, psCxIndex;
    static uint8_t r,g,b;
    static short *psY,*psCb,*psCr;
    static int32_t s1,s2,s3;
    static uint8_t bBlock, bOffsetY[2] = {0,8}, bOffsetX[4] = {0,8,0,8}, bCbCrOffset[4] = {0,4,32,36};
    static uint16_t wXPos, wYPos,wYPos2;
    static uint8_t shiftX, shiftY;
    static GFX_Point pnt;
    static GFX_Color color;
	uint8_t *pixels;

    if(pJpegDecoder->bSubSampleType == JPEG_SAMPLE_1x1)
    {
        shiftX = 8; 
        shiftY = 8;

        if (GFX_PixelBufferCreate(shiftX,
			shiftY,
			pJpegDecoder->colorMode,
			&pixels,
			&pJpegDecoder->pixelBlockBuffer) == GFX_FAILURE)
        {
            return 0;
        }
        
		pJpegDecoder->pixelBlockBuffer.pixels = GFX_ActiveContext()->memory.malloc(pJpegDecoder->pixelBlockBuffer.buffer_length);
        
        psY = &pJpegDecoder->asOneBlock[0][0]; 
        psCb = &pJpegDecoder->asOneBlock[1][0]; 
        psCr = &pJpegDecoder->asOneBlock[2][0];

        for(wY = 0; wY < 8; wY++)
        {
            for(wX = 0; wX < 8; wX++)
            {
                s1 = ((*psY) + 128)*128, s2 = (*psCb), s3 = (*psCr);
                r = range_limit((s1 + 180*s3)>>7);
                g = range_limit((s1 - 44*s2 - 91*s3)>>7);
                b = range_limit((s1 + 227*s2)>>7);
                
//              IMG_vSetColor(r, g, b);
//              IMG_vPixelArray(wX + (wY<<3));
//				pixel[wX + (wY<<3)] = GFX_RGBConvert(r, g, b);
                
                color = r << 16 | g << 8 | b;

                pnt.x = wX;
				pnt.y = (wY << 3);
                
                GFX_PixelBufferSet(
                    &pJpegDecoder->pixelBlockBuffer,
                    &pnt,
                    GFX_ColorConvert(GFX_COLOR_MODE_RGB_888,
                        pJpegDecoder->colorMode,
                        color));
                
                psY++; psCb++; psCr++;
            }  
         }
     }       
     else if(pJpegDecoder->bSubSampleType == JPEG_SAMPLE_1x2)
     {
        shiftX = 8; 
        shiftY = 16;

        if (GFX_PixelBufferCreate(shiftX,
			shiftY,
			pJpegDecoder->colorMode,
			&pixels,
			&pJpegDecoder->pixelBlockBuffer) == GFX_FAILURE)
        {
            return 0;
        }
        
		pJpegDecoder->pixelBlockBuffer.pixels = GFX_ActiveContext()->memory.malloc(pJpegDecoder->pixelBlockBuffer.buffer_length);

        for(bBlock = 0; bBlock < 2; bBlock++)
        {
            psY = &pJpegDecoder->asOneBlock[bBlock][0];
            psCb = &pJpegDecoder->asOneBlock[2][bBlock<<5];
            psCr = &pJpegDecoder->asOneBlock[3][bBlock<<5];

            for(wY = 0; wY < 8; wY++)
            {
                for(wX = 0; wX < 8; wX++)
                {
                    s1 = ((*psY) + 128)*128;
                    s2 = psCb[(wY>>1)*8+wX];
                    s3 = psCr[(wY>>1)*8+wX];
                    r = range_limit((s1 + 180*s3)>>7);
                    g = range_limit((s1 - 44*s2 - 91*s3)>>7);
                    b = range_limit((s1 + 227*s2)>>7);                    
                    //pixel[wX + ((bOffsetY[bBlock] + wY)<<3)] = GFX_RGBConvert(r, g, b);
                    
                    color = r << 16 | g << 8 | b;

                    pnt.x = wX;
					pnt.y = ((bOffsetY[bBlock] + wY) << 3);

                    GFX_PixelBufferSet(
                        &pJpegDecoder->pixelBlockBuffer,
                        &pnt,
                        GFX_ColorConvert(GFX_COLOR_MODE_RGB_888,
                            pJpegDecoder->colorMode,
                            color));

                    psY++;
                }
            }
        }
     }       
     else if(pJpegDecoder->bSubSampleType == JPEG_SAMPLE_2x1)
     {
        shiftX = 16; 
        shiftY = 8;

        if (GFX_PixelBufferCreate(shiftX,
			shiftY,
			pJpegDecoder->colorMode,
			&pixels,
			&pJpegDecoder->pixelBlockBuffer) == GFX_FAILURE)
        {
            return 0;
        }
        
		pJpegDecoder->pixelBlockBuffer.pixels = GFX_ActiveContext()->memory.malloc(pJpegDecoder->pixelBlockBuffer.buffer_length);

        for(bBlock = 0; bBlock < 2; bBlock++)
        {
            psY = &pJpegDecoder->asOneBlock[bBlock][0];
            psCb = &pJpegDecoder->asOneBlock[2][bBlock<<2];
            psCr = &pJpegDecoder->asOneBlock[3][bBlock<<2];

            for(wY = 0; wY < 8; wY++)
            {
                for(wX = 0; wX < 8; wX++)
                {
                    s1 = ((*psY) + 128)*128;
                    s2 = psCb[(wY*8)+(wX>>1)];
                    s3 = psCr[(wY*8)+(wX>>1)];
                    r = range_limit((s1 + 180*s3)>>7);
                    g = range_limit((s1 - 44*s2 - 91*s3)>>7);
                    b = range_limit((s1 + 227*s2)>>7);
//                    pixel[bOffsetX[bBlock] + wX + (wY<<4)] = GFX_RGBConvert(r, g, b);
                    
                    color = r << 16 | g << 8 | b;

                    pnt.x = bOffsetX[bBlock] + wX;
					pnt.y = (wY << 4);

                    GFX_PixelBufferSet(
                        &pJpegDecoder->pixelBlockBuffer,
                        &pnt,
                        GFX_ColorConvert(GFX_COLOR_MODE_RGB_888,
                            pJpegDecoder->colorMode,
                            color));

                    psY++;
                }
            }
        }
     }
     else if(pJpegDecoder->bSubSampleType == JPEG_SAMPLE_2x2)
     {
        shiftX = 16; 
        shiftY = 16;

        if (GFX_PixelBufferCreate(shiftX,
			shiftY,
			pJpegDecoder->colorMode,
			&pixels,
			&pJpegDecoder->pixelBlockBuffer) == GFX_FAILURE)
        {
            return 0;
        }
        
		pJpegDecoder->pixelBlockBuffer.pixels = GFX_ActiveContext()->memory.malloc(pJpegDecoder->pixelBlockBuffer.buffer_length);

        for(bBlock = 0; bBlock < 4; bBlock++)
        {
            wXPos = bOffsetX[bBlock];
            wYPos = bOffsetY[bBlock>>1];

            psY = &pJpegDecoder->asOneBlock[bBlock][0];
            psCb = &pJpegDecoder->asOneBlock[4][bCbCrOffset[bBlock]];
            psCr = &pJpegDecoder->asOneBlock[5][bCbCrOffset[bBlock]];

            for(wY = 0; wY < 8; wY++)
            {
                wYPos2 = wYPos + wY;

                for(wX = 0; wX < 4; wX++)
                {
                    psCxIndex = (wY>>1)*8 + wX;
                    s2 = psCb[psCxIndex];
                        s3 = psCr[psCxIndex];

                    for(wX2 = 0; wX2 < 2; wX2++)
                    {
                        s1 = ((*psY++) + 128)*128;
                        r = range_limit((s1 + 180*s3)>>7);
                        g = range_limit((s1 - 44*s2 - 91*s3)>>7);
                        b = range_limit((s1 + 227*s2)>>7);
                        //pixel[wXPos + (wX<<1) + wX2 + (wYPos2<<4)] = GFX_RGBConvert(r, g, b);

                        color = r << 16 | g << 8 | b;

                        pnt.x = wXPos + (wX<<1) + wX2;
                        pnt.y = wYPos2;

                        GFX_PixelBufferSet(
                            &pJpegDecoder->pixelBlockBuffer,
                            &pnt,
                            GFX_ColorConvert(GFX_COLOR_MODE_RGB_888,
                                pJpegDecoder->colorMode,
                                color));
                    }    
                }
            }
        }
    }

	GFX_DrawBlit(&pJpegDecoder->pixelBlockBuffer,
		0, 0, shiftX, shiftY, pJpegDecoder->wPrevX + pJpegDecoder->wDrawX, pJpegDecoder->wPrevY + pJpegDecoder->wDrawY);
    
    pJpegDecoder->wPrevX += shiftX;

	if (pJpegDecoder->wPrevX >= pJpegDecoder->wWidth + pJpegDecoder->wStartX)
	{
		pJpegDecoder->wPrevX = pJpegDecoder->wStartX;
		pJpegDecoder->wPrevY += shiftY;
	}
    
	GFX_ActiveContext()->memory.free(pJpegDecoder->pixelBlockBuffer.pixels);
    
    return 0;
}

int8_t JPEG_bInterpretResourceHeader(GFXU_ImageAsset* img)
{
    JPEGDECODER JPEG_JpegDecoder;
    
    if (img == NULL)
        return -1;

    JPEG_vResetDecoder(&JPEG_JpegDecoder);
    JPEG_JpegDecoder.pImageFile = img;

    if(JPEG_bReadHeader(&JPEG_JpegDecoder) != 0)
    {
        return(1);
    }

    return 0;
}

/*******************************************************************************
Function:       uint8_t JPEG_bDecode(GFXU_ImageAsset *pfile, BOOL bFirstTime)

Precondition:   The global variables of Image decoder must be set

Overview:       This function decodes and displays a jpeg image

Input:          Image file, BOOLean indicating if this is the first time calling 
				the JPEG_bDecode function (needed to reset internal decoding 
				state variables).  If bFirstTime is true, pfile must be set.
				If bFirstTime is false, pfile is ignored (uses previously
				provided file handle).

Output:         Error code - '0' means not yet completed
*******************************************************************************/
GFX_Result GFXU_DrawImageJpgInternal(GFXU_ImageAsset* img,
                                     int32_t src_x,
                                     int32_t src_y,
                                     int32_t src_width,
                                     int32_t src_height,
                                     int32_t dest_x,
                                     int32_t dest_y)
{
	static uint16_t whblocks, wvblocks;
	static uint16_t wi, wj;
	static JPEGDECODER JPEG_JpegDecoder;
	static enum
	{
		INITIAL,
		HEADER_DECODED,
		BLOCK_DECODE,
        BLOCK_PAINT,
		DECODE_DONE
	} decodestate = INITIAL;
	
    switch(decodestate)
    {    
        case INITIAL:                        
            JPEG_vResetDecoder(&JPEG_JpegDecoder);

            JPEG_JpegDecoder.pImageFile = img;
            JPEG_JpegDecoder.wStartY = src_y;
            JPEG_JpegDecoder.wStartX = src_x;
            JPEG_JpegDecoder.wDrawWidth = src_width;
            JPEG_JpegDecoder.wDrawHeight = src_height;
            JPEG_JpegDecoder.wDrawX = dest_x;
            JPEG_JpegDecoder.wDrawY = dest_y;

            if(GFX_Get(GFXF_COLOR_MODE, &JPEG_JpegDecoder.colorMode) == GFX_FAILURE)
                return GFX_FAILURE;         

            if(JPEG_bReadHeader(&JPEG_JpegDecoder) != 0)
            {
                //IMG_vImageFail();
                return GFX_FAILURE;
            }
            decodestate = HEADER_DECODED;
        
        case HEADER_DECODED:
//            IMG_wImageWidth = JPEG_JpegDecoder.wWidth;
//            IMG_wImageHeight = JPEG_JpegDecoder.wHeight;
//            IMG_vSetboundaries();

            JPEG_bGenerateHuffmanTables(&JPEG_JpegDecoder);

            whblocks = JPEG_JpegDecoder.wWidth >> 3;
            wvblocks = JPEG_JpegDecoder.wHeight >> 3;

            if((whblocks << 3) < JPEG_JpegDecoder.wWidth) /* Odd sizes */
            {
                whblocks++;
            }

            if((wvblocks << 3) < JPEG_JpegDecoder.wHeight) /* Odd sizes */
            {
                wvblocks++;
            }

            if(JPEG_JpegDecoder.bSubSampleType == JPEG_SAMPLE_1x2)
            {
                wvblocks =  (wvblocks>>1) + (wvblocks&1);
            }
            else if(JPEG_JpegDecoder.bSubSampleType == JPEG_SAMPLE_2x1)
            {
                whblocks = (whblocks>>1) + (whblocks&1);
            }
            else if(JPEG_JpegDecoder.bSubSampleType == JPEG_SAMPLE_2x2)
            {
                wvblocks =  (wvblocks>>1) + (wvblocks&1);
                whblocks = (whblocks>>1) + (whblocks&1);
            }

            JPEG_vInitDisplay(&JPEG_JpegDecoder);

            wi = 0;
            wj = 0;

            decodestate = BLOCK_DECODE;

        case BLOCK_DECODE:  
            while(wi < whblocks)
            {
                JPEG_bDecodeOneBlock(&JPEG_JpegDecoder); /* Fills a block after correcting the zigzag, dequantizing, IDCR and color conversion to RGB */

                decodestate = BLOCK_PAINT;
        case BLOCK_PAINT:
                if(JPEG_bPaintOneBlock(&JPEG_JpegDecoder))   /* Sends the block to the Graphics unit */
                {
                    //IMG_vImageFail();
                    return GFX_FAILURE; //Painting not finished
                }

                wj++;

                if(wj >= wvblocks)
                {
                    wj = 0;
                    wi++;
                }
            }

            //IMG_vImageComplete();
            decodestate = INITIAL;
        default:            
            return GFX_SUCCESS;
    }
    return GFX_SUCCESS;
}
