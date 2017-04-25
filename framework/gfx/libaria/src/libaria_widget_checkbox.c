#include "gfx/libaria/inc/libaria_widget_checkbox.h"

#if LA_CHECKBOX_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define DEFAULT_WIDTH    100
#define DEFAULT_HEIGHT   23

#define DEFAULT_IMAGE_MARGIN    10

//static void cacheTextRect(laCheckBoxWidget* cbox);

void _laCheckBoxWidget_Constructor(laCheckBoxWidget* cbox)
{
	_laWidget_Constructor((laWidget*)cbox);

    cbox->widget.destructor = (laWidget_Destructor_FnPtr)&_laCheckBoxWidget_Destructor;

	cbox->widget.type = LA_WIDGET_CHECKBOX;

	// override base class methods
	cbox->widget.paint = (laWidget_Paint_FnPtr)&_laCheckBoxWidget_Paint;

	cbox->widget.rect.width = DEFAULT_WIDTH;
	cbox->widget.rect.height = DEFAULT_HEIGHT;

	cbox->checked = LA_FALSE;

	cbox->widget.borderType = LA_WIDGET_BORDER_NONE;

	laString_Initialize(&cbox->text);

    cbox->imageMargin = DEFAULT_IMAGE_MARGIN;

	cbox->halign = LA_HALIGN_LEFT;
	cbox->valign = LA_VALIGN_MIDDLE;
	
	cbox->checkedImage = NULL;
	cbox->uncheckedImage = NULL;
	
	cbox->widget.touchDown = (laWidget_TouchDownEvent_FnPtr)&_laCheckBoxWidget_TouchDownEvent;
	cbox->widget.touchUp = (laWidget_TouchUpEvent_FnPtr)&_laCheckBoxWidget_TouchUpEvent;
	cbox->widget.touchMoved = (laWidget_TouchMovedEvent_FnPtr)&_laCheckBoxWidget_TouchMovedEvent;
}

void _laCheckBoxWidget_Destructor(laCheckBoxWidget* cbox)
{
	laString_Destroy(&cbox->text);
	
	// free any existing memory reader
	if(cbox->reader != NULL)
	{
	    laContext_GetActive()->memIntf.heap.free(cbox->reader);
	    
	    cbox->reader = NULL;
	}

	_laWidget_Destructor((laWidget*)cbox);
}

laCheckBoxWidget* laCheckBoxWidget_New()
{
	laCheckBoxWidget* cbox = NULL;

	if(laContext_GetActive() == NULL)
		return NULL;

	cbox = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laCheckBoxWidget));

    if(cbox == NULL)
        return NULL;
    
	_laCheckBoxWidget_Constructor(cbox);

	return cbox;
}

laBool laButtonWidget_GetChecked(laCheckBoxWidget* cbox)
{
	if(cbox == NULL)
		return LA_FALSE;

	return cbox->checked;
}

void laCheckBoxWidget_SetChecked(laCheckBoxWidget* cbox, laBool checked)
{
	if(cbox == NULL)
		return;

	cbox->checked = checked == 0 ? LA_FALSE : LA_TRUE;
}

laHAlignment laCheckBoxWidget_GetHAlignment(laCheckBoxWidget* cbox)
{
	if(cbox == NULL)
		return 0;

	return cbox->halign;
}

void laCheckBoxWidget_SetHAlignment(laCheckBoxWidget* cbox,
									laHAlignment align)
{
	if(cbox == NULL || cbox->halign == align)
		return;

	cbox->halign = align;

	laWidget_Invalidate((laWidget*)cbox);
}

laVAlignment laCheckBoxWidget_GetVAlignment(laCheckBoxWidget* cbox)
{
	if(cbox == NULL)
		return 0;

	return cbox->valign;
}

void laCheckBoxWidget_SetVAlignment(laCheckBoxWidget* cbox,
									laVAlignment align)
{
	if(cbox == NULL || cbox->valign == align)
		return;

	cbox->valign = align;

	laWidget_Invalidate((laWidget*)cbox);
}

void laCheckBoxWidget_GetText(laCheckBoxWidget* cbox, laString* str)
{
    if(cbox == NULL)
        return;
    
    laString_Copy(str, &cbox->text);
}

void laCheckBoxWidget_SetText(laCheckBoxWidget* cbox, laString str)
{
    if(cbox == NULL)
        return;
        
    if(laString_Compare(&cbox->text, &str) == 0)
        return;
        
    laString_Copy(&cbox->text, &str);
    
    laWidget_Invalidate((laWidget*)cbox);
}

GFXU_ImageAsset* laCheckBoxWidget_GetCheckedImage(laCheckBoxWidget* cbox)
{
	if(cbox == NULL)
		return NULL;

	return cbox->checkedImage;
}

void laCheckBoxWidget_SetCheckedImage(laCheckBoxWidget* cbox,
									   GFXU_ImageAsset* img)
{
	if(cbox == NULL || cbox->checkedImage == img)
		return;

	cbox->checkedImage = img;

	laWidget_Invalidate((laWidget*)cbox);
}

GFXU_ImageAsset* laCheckBoxWidget_GetUncheckedImage(laCheckBoxWidget* cbox)
{
	if(cbox == NULL)
		return NULL;

	return cbox->uncheckedImage;
}

void laCheckBoxWidget_SetUncheckedImage(laCheckBoxWidget* cbox,
									    GFXU_ImageAsset* img)
{
	if(cbox == NULL || cbox->uncheckedImage == img)
		return;

	cbox->uncheckedImage = img;

	laWidget_Invalidate((laWidget*)cbox);
}

laRelativePosition laCheckBoxWidget_GetImagePosition(laCheckBoxWidget* cbox)
{
    if(cbox == NULL)
		return LA_RELATIVE_POSITION_LEFTOF;
		
    return cbox->imagePosition;
}

void laCheckBoxWidget_SetImagePosition(laCheckBoxWidget* cbox, laRelativePosition pos)
{
    if(cbox == NULL || cbox->imagePosition == pos)
		return;
	
	cbox->imagePosition = pos;
	
	laWidget_Invalidate((laWidget*)cbox);
}

uint16_t laCheckBoxWidget_GetImageMargin(laCheckBoxWidget* cbox)
{
    if(cbox == NULL)
		return LA_RELATIVE_POSITION_LEFTOF;
		
    return cbox->imageMargin;
}

void laCheckBoxWidget_SetImageMargin(laCheckBoxWidget* cbox, uint16_t mg)
{
    if(cbox == NULL || cbox->imageMargin == mg)
		return;
	
	cbox->imageMargin = mg;
	
	laWidget_Invalidate((laWidget*)cbox);
}

laCheckBoxWidget_CheckedEvent laCheckBoxWidget_GetCheckedEventCallback(laCheckBoxWidget* cbox)
{
	if(cbox == NULL)
		return NULL;

	return cbox->checkedEvent;
}

void laCheckBoxWidget_SetCheckedEventCallback(laCheckBoxWidget* cbox,
											         laCheckBoxWidget_CheckedEvent cb)
{
	if(cbox == NULL)
		return;

	cbox->checkedEvent = cb;
}

laCheckBoxWidget_UncheckedEvent laCheckBoxWidget_GetUncheckedEventCallback(laCheckBoxWidget* cbox)
{
	if(cbox == NULL)
		return NULL;

	return cbox->uncheckedEvent;
}

void laCheckBoxWidget_SetUncheckedEventCallback(laCheckBoxWidget* cbox,
											         laCheckBoxWidget_UncheckedEvent cb)
{
	if(cbox == NULL)
		return;

	cbox->uncheckedEvent = cb;
}

void _laCheckBoxWidget_TouchDownEvent(laCheckBoxWidget* cbox,
							          laInput_TouchDownEvent* evt)
{
    GFX_Rect rect;
    GFX_Point pt;
    
    _laCheckBoxWidget_GetImageRect(cbox, &rect);
    
    laUtils_ClipRectToParent((laWidget*)cbox, &rect);
    
    laUtils_RectToScreenSpace((laWidget*)cbox, &rect);
	
	pt.x = evt->x;
	pt.y = evt->y;
	
	if(GFX_RectContainsPoint(&rect, &pt) == GFX_TRUE)
	{
	    evt->event.accepted = LA_TRUE;

	   // printf("cbox touch down\n");
	}
}

void _laCheckBoxWidget_TouchUpEvent(laCheckBoxWidget* cbox,
							        laInput_TouchUpEvent* evt)
{
	GFX_Rect rect;
	GFX_Point pnt;

	pnt.x = evt->x;
	pnt.y = evt->y;

	evt->event.accepted = LA_TRUE;

    _laCheckBoxWidget_GetImageRect(cbox, &rect);
    
    // move to parent space
    //rect.x += cbox->widget.rect.x;
    //rect.y += cbox->widget.rect.y;
    
	//laUtils_ClipRectToParent((laWidget*)cbox, &rect);
	laUtils_RectToScreenSpace((laWidget*)cbox, &rect);

	if(GFX_RectContainsPoint(&rect, &pnt) == GFX_TRUE)
	{
		cbox->checked = !cbox->checked;

		if(cbox->checked == LA_TRUE && cbox->checkedEvent != NULL)
		    cbox->checkedEvent(cbox);
		else if(cbox->checked == LA_FALSE && cbox->uncheckedEvent != NULL)
		    cbox->uncheckedEvent(cbox);

		//printf("cbox released\n");
		
		laWidget_Invalidate((laWidget*)cbox);
	}
	
	//printf("cbox touch up\n");
}

void _laCheckBoxWidget_TouchMovedEvent(laCheckBoxWidget* cbox,
							           laInput_TouchMovedEvent* evt)
{
	evt->event.accepted = LA_TRUE;
}

/*static void cacheTextRect(laCheckBoxWidget* cbox)
{
    cbox->paintData.stringRect.width = 0;
    cbox->paintData.stringRect.height = 0;
    
    if(cbox->text.font == NULL)
        return;
        
    laString_GetRect(&cbox->text,
                     &cbox->paintData.stringRect,
                     &cbox->reader);
                     
    if(cbox->reader == NULL)
        laWidget_Invalidate((laWidget*)cbox); // go ahead and repaint
}*/

#endif // LA_CHECKBOX_WIDGET_ENABLED