#include "gfx/libaria/inc/libaria_widget_radiobutton.h"

#if LA_RADIOBUTTON_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_radiobutton_group.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define DEFAULT_WIDTH           100
#define DEFAULT_HEIGHT          25

#define DEFAULT_IMAGE_MARGIN    10

//static void cacheTextRect(laRadioButtonWidget* btn);

void _laRadioButtonWidget_Constructor(laRadioButtonWidget* btn)
{
	_laWidget_Constructor((laWidget*)btn);
	
	btn->widget.destructor = (laWidget_Destructor_FnPtr)&_laRadioButtonWidget_Destructor;

	btn->widget.type = LA_WIDGET_RADIOBUTTON;

	// override base class methods
	//btn->widget.update = &(laWidget_Update_FnPtr)_laRadioButtonWidget_Update;
	btn->widget.paint = (laWidget_Paint_FnPtr)&_laRadioButtonWidget_Paint;

	btn->widget.rect.width = DEFAULT_WIDTH;
	btn->widget.rect.height = DEFAULT_HEIGHT;

	btn->selected = LA_TRUE;

	btn->widget.borderType = LA_WIDGET_BORDER_NONE;

	laString_Initialize(&btn->text);
	
	btn->imageMargin = DEFAULT_IMAGE_MARGIN;

	btn->halign = LA_HALIGN_CENTER;
	btn->valign = LA_VALIGN_MIDDLE;
	
	btn->selectedImage = NULL;
	btn->unselectedImage = NULL;

	btn->widget.touchDown = (laWidget_TouchDownEvent_FnPtr)&_laRadioButtonWidget_TouchDownEvent;
	btn->widget.touchUp = (laWidget_TouchUpEvent_FnPtr)&_laRadioButtonWidget_TouchUpEvent;
	btn->widget.touchMoved = (laWidget_TouchMovedEvent_FnPtr)&_laRadioButtonWidget_TouchMovedEvent;
}

void _laRadioButtonWidget_Destructor(laRadioButtonWidget* btn)
{
    if(btn->group != NULL)
	    laRadioButtonGroup_RemoveButton(btn->group, btn);

	laString_Destroy(&btn->text);
	
	// free any existing memory reader
	if(btn->reader != NULL)
	{
	    laContext_GetActive()->memIntf.heap.free(btn->reader);
	    
	    btn->reader = NULL;
	}

	_laWidget_Destructor((laWidget*)btn);
}

/*void _laRadioButtonWidget_Update(laRadioButtonWidget* btn)
{

}*/

laRadioButtonWidget* laRadioButtonWidget_New()
{
	laRadioButtonWidget* btn = NULL;

	if(laContext_GetActive() == NULL)
		return NULL;

	btn = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laRadioButtonWidget));

    if(btn == NULL)
        return btn;
        
	_laRadioButtonWidget_Constructor(btn);

	return btn;
}

laRadioButtonGroup* laRadioButtonWidget_GetGroup(laRadioButtonWidget* btn)
{
    if(btn == NULL)
        return NULL;
        
    return btn->group;
}

laBool laRadioButtonWidget_GetSelected(laRadioButtonWidget* btn)
{
	if(btn == NULL)
		return LA_FALSE;

	if(btn->group == NULL)
		return LA_TRUE;

	return btn->group->selected == btn;
}

laResult laRadioButtonWidget_SetSelected(laRadioButtonWidget* btn)
{
	if(btn == NULL || btn->selected == LA_TRUE)
		return LA_FAILURE;

	if(btn->group == NULL)
	    return LA_SUCCESS;
	   
	return laRadioButtonGroup_SelectButton(btn->group, btn);
}

void _laRadioButtonWidget_Select(laRadioButtonWidget* btn)
{
    if(btn->selected == LA_TRUE)
        return;

	btn->selected = LA_TRUE;

	if(btn->selectedEvent != NULL)
		btn->selectedEvent(btn);
		
    laWidget_Invalidate((laWidget*)btn);
}

void _laRadioButtonWidget_Deselect(laRadioButtonWidget* btn)
{
    if(btn->selected == LA_FALSE)
        return;

	btn->selected = LA_FALSE;

	if(btn->deselectedEvent != NULL)
		btn->deselectedEvent(btn);
		
    laWidget_Invalidate((laWidget*)btn);
}

laHAlignment laRadioButtonWidget_GetHAlignment(laRadioButtonWidget* btn)
{
	if(btn == NULL)
		return 0;

	return btn->halign;
}

void laRadioButtonWidget_SetHAlignment(laRadioButtonWidget* btn,
									   laHAlignment align)
{
	if(btn == NULL || btn->halign == align)
		return;

	btn->halign = align;

	laWidget_Invalidate((laWidget*)btn);
}

laVAlignment laRadioButtonWidget_GetVAlignment(laRadioButtonWidget* btn)
{
	if(btn == NULL)
		return 0;

	return btn->valign;
}

void laRadioButtonWidget_SetVAlignment(laRadioButtonWidget* btn,
									   laVAlignment align)
{
	if(btn == NULL || btn->valign == align)
		return;

	btn->valign = align;

	laWidget_Invalidate((laWidget*)btn);
}

void laRadioButtonWidget_GetText(laRadioButtonWidget* btn, laString* str)
{
    if(btn == NULL)
        return;
    
    laString_Copy(str, &btn->text);
}

void laRadioButtonWidget_SetText(laRadioButtonWidget* btn, laString str)
{
    if(btn == NULL)
        return;
        
    if(laString_Compare(&btn->text, &str) == 0)
        return;
        
    laString_Copy(&btn->text, &str);
    
    laWidget_Invalidate((laWidget*)btn);
}

GFXU_ImageAsset* laRadioButtonWidget_GetSelectedImage(laRadioButtonWidget* btn)
{
	if(btn == NULL)
		return NULL;

	return btn->selectedImage;
}

void laRadioButtonWidget_SetSelectedImage(laRadioButtonWidget* btn,
									      GFXU_ImageAsset* img)
{
	if(btn == NULL || btn->selectedImage == img)
		return;

	btn->selectedImage = img;

	laWidget_Invalidate((laWidget*)btn);
}

GFXU_ImageAsset* laRadioButtonWidget_GetUnselectedImage(laRadioButtonWidget* btn)
{
	if(btn == NULL)
		return NULL;

	return btn->unselectedImage;
}

void laRadioButtonWidget_SetUnselectedImage(laRadioButtonWidget* btn,
									        GFXU_ImageAsset* img)
{
	if(btn == NULL || btn->unselectedImage == img)
		return;

	btn->unselectedImage = img;

	laWidget_Invalidate((laWidget*)btn);
}

laRelativePosition laRadioButtonWidget_GetImagePosition(laRadioButtonWidget* btn)
{
    if(btn == NULL)
		return LA_RELATIVE_POSITION_LEFTOF;
		
    return btn->imagePosition;
}

void laRadioButtonWidget_SetImagePosition(laRadioButtonWidget* btn, laRelativePosition pos)
{
    if(btn == NULL || btn->imagePosition == pos)
		return;
	
	btn->imagePosition = pos;
	
	laWidget_Invalidate((laWidget*)btn);
}

uint16_t laRadioButtonWidget_GetImageMargin(laRadioButtonWidget* btn)
{
    if(btn == NULL)
		return LA_RELATIVE_POSITION_LEFTOF;
		
    return btn->imageMargin;
}

void laRadioButtonWidget_SetImageMargin(laRadioButtonWidget* btn, uint16_t mg)
{
    if(btn == NULL || btn->imageMargin == mg)
		return;
	
	btn->imageMargin = mg;
	
	laWidget_Invalidate((laWidget*)btn);
}

laRadioButtonWidget_SelectedEvent laRadioButtonWidget_GetSelectedEventCallback(laRadioButtonWidget* btn)
{
	if(btn == NULL)
		return NULL;

	return btn->selectedEvent;
}

void laRadioButtonWidget_SetSelectedEventCallback(laRadioButtonWidget* btn,
									              laRadioButtonWidget_SelectedEvent cb)
{
	if(btn == NULL || btn->selectedEvent == cb)
		return;

	btn->selectedEvent = cb;
}

laRadioButtonWidget_DeselectedEvent laRadioButtonWidget_GetDeselectedEventCallback(laRadioButtonWidget* btn)
{
	if(btn == NULL)
		return NULL;

	return btn->deselectedEvent;
}

void laRadioButtonWidget_SetDeselectedEventCallback(laRadioButtonWidget* btn,
											        laRadioButtonWidget_DeselectedEvent cb)
{
	if(btn == NULL || btn->deselectedEvent == cb)
		return;

	btn->deselectedEvent = cb;
}

void _laRadioButtonWidget_TouchDownEvent(laRadioButtonWidget* btn,
							             laInput_TouchDownEvent* evt)
{
	/*evt->event.accepted = LA_TRUE;

	if(btn->state != LA_RADIOBUTTON_STATE_SELECTED)
		btn->state = LA_RADIOBUTTON_STATE_DOWN;

	if(btn->selectedEvent != NULL)
		btn->selectedEvent(btn);

	laWidget_Invalidate((laWidget*)btn);*/

    GFX_Rect rect;
    GFX_Point pt;
    
    _laRadioButtonWidget_GetImageRect(btn, &rect);
    
    laUtils_ClipRectToParent((laWidget*)btn, &rect);
    
    //laUtils_RectToParentSpace((laWidget*)btn, &rect);
    laUtils_RectToScreenSpace((laWidget*)btn, &rect);
	
	pt.x = evt->x;
	pt.y = evt->y;
	
	if(GFX_RectContainsPoint(&rect, &pt) == GFX_TRUE &&
	   btn->selected == LA_FALSE)
	{
	    evt->event.accepted = LA_TRUE;

	    //printf("radiobutton touch down\n");
	}

	//printf("btn touch down\n");
}

void _laRadioButtonWidget_TouchUpEvent(laRadioButtonWidget* btn,
							           laInput_TouchUpEvent* evt)
{
	/*GFX_Rect rect = btn->widget.rect;
	GFX_Point pnt;

	pnt.x = evt->x;
	pnt.y = evt->y;

	evt->event.accepted = LA_TRUE;

	laUtils_ClipRectToParent((laWidget*)btn, &rect);
	laUtils_RectToScreenSpace((laWidget*)btn, &rect);

	if(GFX_RectContainsPoint(&rect, &pnt) == GFX_TRUE)
	{
		if(btn->state == LA_RADIOBUTTON_STATE_SELECTED)
		{
			btn->state = LA_RADIOBUTTON_STATE_UNSELECTED;

			if(btn->deselectedEvent != NULL)
				btn->deselectedEvent(btn);

			//printf("btn released\n");
		}
		else
			btn->state = LA_RADIOBUTTON_STATE_SELECTED;
		
		laWidget_Invalidate((laWidget*)btn);
	}*/

	
	GFX_Rect rect;
	GFX_Point pnt;

	pnt.x = evt->x;
	pnt.y = evt->y;

	evt->event.accepted = LA_TRUE;

    _laRadioButtonWidget_GetImageRect(btn, &rect);
    
    // move to parent space
    //rect.x += btn->widget.rect.x;
    //rect.y += btn->widget.rect.y;
    
	//laUtils_ClipRectToParent((laWidget*)btn, &rect);
	laUtils_RectToScreenSpace((laWidget*)btn, &rect);

	if(GFX_RectContainsPoint(&rect, &pnt) == GFX_TRUE)
		laRadioButtonGroup_SelectButton(btn->group, btn);
	
	//printf("cbox touch up\n");
}

void _laRadioButtonWidget_TouchMovedEvent(laRadioButtonWidget* btn,
							              laInput_TouchMovedEvent* evt)
{
	evt->event.accepted = LA_TRUE;
}

/*static void cacheTextRect(laRadioButtonWidget* btn)
{
    btn->paintData.stringRect.width = 0;
    btn->paintData.stringRect.height = 0;
    
    if(btn->font == NULL)
        return;
        
    //btn->paintData.stringRect.height = btn->font->height;
    
    laString_GetRect(&btn->text,
                     &btn->paintData.stringRect);
                     
    if(btn->reader == NULL)
        laWidget_Invalidate((laWidget*)btn); // go ahead and repaint
}*/

#endif // LA_RADIOBUTTON_WIDGET_ENABLED