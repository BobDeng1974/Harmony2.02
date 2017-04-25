#include "gfx/libaria/inc/libaria_widget_label.h"

#if LA_LABEL_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define DEFAULT_WIDTH           100
#define DEFAULT_HEIGHT          25

void _laLabelWidget_Constructor(laLabelWidget* lbl)
{
	_laWidget_Constructor((laWidget*)lbl);
	
	lbl->widget.destructor = (laWidget_Destructor_FnPtr)&_laLabelWidget_Destructor;

	lbl->widget.type = LA_WIDGET_LABEL;

	// override base class methods
	lbl->widget.paint = (laWidget_Paint_FnPtr)&_laLabelWidget_Paint;

	lbl->widget.rect.width = DEFAULT_WIDTH;
	lbl->widget.rect.height = DEFAULT_HEIGHT;

	lbl->widget.borderType = LA_WIDGET_BORDER_NONE;

	laString_Initialize(&lbl->text);
	
	lbl->halign = LA_HALIGN_CENTER;
	lbl->valign = LA_VALIGN_MIDDLE;
}

void _laLabelWidget_Destructor(laLabelWidget* lbl)
{
	laString_Destroy(&lbl->text);
	
	// free any existing memory reader
	if(lbl->reader != NULL)
	{
	    laContext_GetActive()->memIntf.heap.free(lbl->reader);
	    
	    lbl->reader = NULL;
	}

	_laWidget_Destructor((laWidget*)lbl);
}

/*void _laLabelWidget_Update(laLabelWidget* lbl)
{

}*/

laLabelWidget* laLabelWidget_New()
{
	laLabelWidget* lbl = NULL;

	if(laContext_GetActive() == NULL)
		return NULL;

	lbl = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laLabelWidget));

	_laLabelWidget_Constructor(lbl);

	return lbl;
}

laHAlignment laLabelWidget_GetHAlignment(laLabelWidget* lbl)
{
	if(lbl == NULL)
		return 0;

	return lbl->halign;
}

void laLabelWidget_SetHAlignment(laLabelWidget* lbl,
								 laHAlignment align)
{
	if(lbl == NULL || lbl->halign == align)
		return;

	lbl->halign = align;

	laWidget_Invalidate((laWidget*)lbl);
}

laVAlignment laLabelWidget_GetVAlignment(laLabelWidget* lbl)
{
	if(lbl == NULL)
		return 0;

	return lbl->valign;
}

void laLabelWidget_SetVAlignment(laLabelWidget* lbl,
								 laVAlignment align)
{
	if(lbl == NULL || lbl->valign == align)
		return;

	lbl->valign = align;

	laWidget_Invalidate((laWidget*)lbl);
}

void laLabelWidget_GetText(laLabelWidget* lbl, laString* str)
{
    if(lbl == NULL)
        return;
    
    laString_Copy(str, &lbl->text);
}

void laLabelWidget_SetText(laLabelWidget* lbl, laString str)
{
    if(lbl == NULL)
        return;
        
    if(laString_Compare(&lbl->text, &str) == 0)
        return;
        
    laString_Copy(&lbl->text, &str);
    
    laWidget_Invalidate((laWidget*)lbl);
}

#endif // LA_IMAGE_WIDGET_ENABLED