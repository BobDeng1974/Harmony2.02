#include "gfx/libaria/inc/libaria_widget_image.h"

#if LA_IMAGE_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define DEFAULT_WIDTH           100
#define DEFAULT_HEIGHT          100

void _laImageWidget_Constructor(laImageWidget* img)
{
	_laWidget_Constructor((laWidget*)img);
	
	img->widget.destructor = (laWidget_Destructor_FnPtr)&_laImageWidget_Destructor;

	img->widget.type = LA_WIDGET_IMAGE;

	// override base class methods
	//img->widget.update = &(laWidget_Update_FnPtr)_laImageWidget_Update;
	img->widget.paint = (laWidget_Paint_FnPtr)&_laImageWidget_Paint;

	img->widget.rect.width = DEFAULT_WIDTH;
	img->widget.rect.height = DEFAULT_HEIGHT;

	img->widget.borderType = LA_WIDGET_BORDER_NONE;
	img->widget.drawBackground = LA_FALSE;

	img->halign = LA_HALIGN_CENTER;
	img->valign = LA_VALIGN_MIDDLE;
	
	img->image = NULL;
}

void _laImageWidget_Destructor(laImageWidget* img)
{
    // free any existing memory reader
	if(img->reader != NULL)
	{
	    laContext_GetActive()->memIntf.heap.free(img->reader);
	    
	    img->reader = NULL;
	}
	
	_laWidget_Destructor((laWidget*)img);
}

/*void _laImageWidget_Update(laImageWidget* img)
{

}*/

laImageWidget* laImageWidget_New()
{
	laImageWidget* img = NULL;

	if(laContext_GetActive() == NULL)
		return NULL;

	img = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laImageWidget));

    if(img == NULL)
        return NULL;
    
	_laImageWidget_Constructor(img);

	return img;
}

laHAlignment laImageWidget_GetHAlignment(laImageWidget* img)
{
	if(img == NULL)
		return 0;

	return img->halign;
}

void laImageWidget_SetHAlignment(laImageWidget* img,
								 laHAlignment align)
{
	if(img == NULL || img->halign == align)
		return;

	img->halign = align;

	laWidget_Invalidate((laWidget*)img);
}

laVAlignment laImageWidget_GetVAlignment(laImageWidget* img)
{
	if(img == NULL)
		return 0;

	return img->valign;
}

void laImageWidget_SetVAlignment(laImageWidget* img,
								 laVAlignment align)
{
	if(img == NULL || img->valign == align)
		return;

	img->valign = align;

	laWidget_Invalidate((laWidget*)img);
}

GFXU_ImageAsset* laImageWidget_GetImage(laImageWidget* img)
{
	if(img == NULL)
		return NULL;

	return img->image;
}

void laImageWidget_SetImage(laImageWidget* img,
							GFXU_ImageAsset* imgAst)
{
	if(img == NULL || img->image == imgAst)
		return;

	img->image = imgAst;

	laWidget_Invalidate((laWidget*)img);
}

#endif // LA_IMAGE_WIDGET_ENABLED