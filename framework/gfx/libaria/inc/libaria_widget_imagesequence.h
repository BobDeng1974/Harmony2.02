/*******************************************************************************
 Module for Microchip Graphics Library - Aria User Interface Library

  Company:
    Microchip Technology Inc.

  File Name:
    libaria_widget_imagesequence.h

  Summary:
    

  Description:
    This module implements image sequence (slide show) widget drawing functions.
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

#ifndef LIBARIA_IMAGESEQUENCE_H
#define LIBARIA_IMAGESEQUENCE_H
//DOM-IGNORE-END

#include "gfx/libaria/inc/libaria_common.h"

#if LA_IMAGESEQUENCE_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_widget.h"
#include "gfx/libaria/inc/libaria_string.h"

#define LA_IMAGESEQ_RESTART -1

typedef struct laImageSequenceWidget_t laImageSequenceWidget;

typedef void (*laImageSequenceImageChangedEvent_FnPtr)(laImageSequenceWidget*);

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Enumeration:
    laImageSequenceEntry_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/	
typedef struct laImageSequenceEntry_t
{
    GFXU_ImageAsset* image;
    
    uint32_t delay;
    
    laHAlignment halign;
	laVAlignment valign;
} laImageSequenceEntry;

// *****************************************************************************
/* Enumeration:
    laImageSequenceWidget_t

  Summary:
    

  Description:
    

  Remarks:
    None.
*/
typedef struct laImageSequenceWidget_t
{
	laWidget widget;

    uint32_t count;
	laImageSequenceEntry* images;
	
	int32_t activeIdx;
	
	laBool playing;
	uint32_t time;
	
	laBool repeat;
	
	laImageSequenceImageChangedEvent_FnPtr cb;
	
	GFXU_ExternalAssetReader* reader;
} laImageSequenceWidget;

void _laImageSequenceWidget_Constructor(laImageSequenceWidget* img);
void _laImageSequenceWidget_Destructor(laImageSequenceWidget* img);

void _laImageSequenceWidget_Update(laImageSequenceWidget* img, uint32_t dt);
void _laImageSequenceWidget_Paint(laImageSequenceWidget* img);

// *****************************************************************************
// *****************************************************************************
// Section: Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    laImageSequenceWidget* laImageSequenceWidget_New()

  Summary:
    

  Description:
    

  Parameters:
	void
	
  Returns:
	laImageSequenceWidget*
	
  Remarks:
    
*/
LIB_EXPORT laImageSequenceWidget* laImageSequenceWidget_New();

// *****************************************************************************
/* Function:
    uint32_t laImageSequenceWidget_GetImageCount(laImageSequenceWidget* img)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laImageSequenceWidget_GetImageCount(laImageSequenceWidget* img);

// *****************************************************************************
/* Function:
    laResult laImageSequenceWidget_SetImageCount(laImageSequenceWidget* img,
                                                        uint32_t count)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laImageSequenceWidget_SetImageCount(laImageSequenceWidget* img,
                                                        uint32_t count);

														// *****************************************************************************
/* Function:
    GFXU_ImageAsset* laImageSequenceWidget_GetImage(laImageSequenceWidget* img,
                                                           uint32_t idx)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	uint32_t
	
  Returns:
	GFXU_ImageAsset*
	
  Remarks:
    
*/
LIB_EXPORT GFXU_ImageAsset* laImageSequenceWidget_GetImage(laImageSequenceWidget* img,
                                                           uint32_t idx);
// *****************************************************************************
/* Function:
    laResult laImageSequenceWidget_SetImage(laImageSequenceWidget* img,
									               uint32_t idx,
									               GFXU_ImageAsset* imgAst)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	uint32_t
	GFXU_ImageAsset*
	
  Returns:
	laResult
	
  Remarks:
    
*/														   
LIB_EXPORT laResult laImageSequenceWidget_SetImage(laImageSequenceWidget* img,
									               uint32_t idx,
									               GFXU_ImageAsset* imgAst);
									          
// *****************************************************************************
/* Function:
    uint32_t laImageSequenceWidget_GetImageDelay(laImageSequenceWidget* img,
                                                        uint32_t idx)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	uint32_t
	
  Returns:
	uint32_t
	
  Remarks:
    
*/
LIB_EXPORT uint32_t laImageSequenceWidget_GetImageDelay(laImageSequenceWidget* img,
                                                        uint32_t idx);

// *****************************************************************************
/* Function:
    laResult laImageSequenceWidget_SetImageDelay(laImageSequenceWidget* img,
									                    uint32_t idx,
									                    uint32_t delay)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	uint32_t
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laImageSequenceWidget_SetImageDelay(laImageSequenceWidget* img,
									                    uint32_t idx,
									                    uint32_t delay);

// *****************************************************************************
/* Function:
    laHAlignment laImageSequenceWidget_GetImageHAlignment(laImageSequenceWidget* img,
                                                                 uint32_t idx)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	uint32_t
	
  Returns:
	laHAlignment
	
  Remarks:
    
*/
LIB_EXPORT laHAlignment laImageSequenceWidget_GetImageHAlignment(laImageSequenceWidget* img,
                                                                 uint32_t idx);
																 
// *****************************************************************************
/* Function:
    laResult laImageSequenceWidget_SetImageHAlignment(laImageSequenceWidget* img,
									                         uint32_t idx,
									                         laHAlignment align)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	uint32_t
	laHAlignment
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laImageSequenceWidget_SetImageHAlignment(laImageSequenceWidget* img,
									                         uint32_t idx,
									                         laHAlignment align);

// *****************************************************************************
/* Function:
    laVAlignment laImageSequenceWidget_GetImageVAlignment(laImageSequenceWidget* img,
                                                                 uint32_t idx)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	uint32_t
	
  Returns:
	laVAlignment
	
  Remarks:
    
*/
LIB_EXPORT laVAlignment laImageSequenceWidget_GetImageVAlignment(laImageSequenceWidget* img,
                                                                 uint32_t idx);

// *****************************************************************************
/* Function:
    laResult laImageSequenceWidget_SetImageVAlignment(laImageSequenceWidget* img,
									                         uint32_t idx,
									                         laVAlignment align)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	uint32_t
	laVAlignment
	
  Returns:
	laResult
	
  Remarks:
    
*/																 
LIB_EXPORT laResult laImageSequenceWidget_SetImageVAlignment(laImageSequenceWidget* img,
									                         uint32_t idx,
									                         laVAlignment align);

// *****************************************************************************
/* Function:
    laResult laImageSequenceWidget_Stop(laImageSequenceWidget* img)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laImageSequenceWidget_Stop(laImageSequenceWidget* img);

// *****************************************************************************
/* Function:
    laResult laImageSequenceWidget_Play(laImageSequenceWidget* img)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laImageSequenceWidget_Play(laImageSequenceWidget* img);

// *****************************************************************************
/* Function:
    laResult laImageSequenceWidget_Rewind(laImageSequenceWidget* img)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laImageSequenceWidget_Rewind(laImageSequenceWidget* img);

// *****************************************************************************
/* Function:
    laBool laImageSequenceWidget_IsPlaying(laImageSequenceWidget* img)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	
  Returns:
	laBool
	
  Remarks:
    
*/
LIB_EXPORT laBool laImageSequenceWidget_IsPlaying(laImageSequenceWidget* img);

// *****************************************************************************
/* Function:
    laBool laImageSequenceWidget_GetRepeat(laImageSequenceWidget* img)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	
  Returns:
	laBool
	
  Remarks:
    
*/
LIB_EXPORT laBool laImageSequenceWidget_GetRepeat(laImageSequenceWidget* img);

// *****************************************************************************
/* Function:
    laResult laImageSequenceWidget_SetRepeat(laImageSequenceWidget* img,
                                                    laBool repeat)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	laBool
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laImageSequenceWidget_SetRepeat(laImageSequenceWidget* img,
                                                    laBool repeat);

// *****************************************************************************
/* Function:
    laResult laImageSequenceWidget_ShowImage(laImageSequenceWidget* img,
                                                    uint32_t idx)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	uint32_t
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laImageSequenceWidget_ShowImage(laImageSequenceWidget* img,
                                                    uint32_t idx);

LIB_EXPORT laResult laImageSequenceWidget_ShowNextImage(laImageSequenceWidget* img);
LIB_EXPORT laResult laImageSequenceWidget_ShowPreviousImage(laImageSequenceWidget* img);

// *****************************************************************************
/* Function:
    laImageSequenceImageChangedEvent_FnPtr laImageSequenceWidget_GetImageChangedEventCallback(laImageSequenceWidget* img)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	
  Returns:
	laImageSequenceImageChangedEvent_FnPtr
	
  Remarks:
    
*/
LIB_EXPORT laImageSequenceImageChangedEvent_FnPtr laImageSequenceWidget_GetImageChangedEventCallback(laImageSequenceWidget* img);

// *****************************************************************************
/* Function:
    laResult laImageSequenceWidget_SetImageChangedEventCallback(laImageSequenceWidget* img,
									                                   laImageSequenceImageChangedEvent_FnPtr cb)

  Summary:
    

  Description:
    

  Parameters:
	laImageSequenceWidget*
	laImageSequenceImageChangedEvent_FnPtr
	
  Returns:
	laResult
	
  Remarks:
    
*/
LIB_EXPORT laResult laImageSequenceWidget_SetImageChangedEventCallback(laImageSequenceWidget* img,
									                                   laImageSequenceImageChangedEvent_FnPtr cb);

#endif // LA_IMAGESEQUENCE_WIDGET_ENABLED									                         
#endif /* LIBARIA_IMAGESEQUENCE_H */