#include "gfx/libaria/inc/libaria_widget_window.h"

#if LA_WINDOW_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define DEFAULT_WIDTH           100
#define DEFAULT_HEIGHT          100

#define DEFAULT_ICON_MARGIN     6

void _laWindowWidget_Constructor(laWindowWidget* win)
{
	_laWidget_Constructor((laWidget*)win);
	
	win->widget.destructor = (laWidget_Destructor_FnPtr)&_laWindowWidget_Destructor;

	win->widget.type = LA_WIDGET_WINDOW;

	// override base class methods
	win->widget.paint = (laWidget_Paint_FnPtr)&_laWindowWidget_Paint;

	win->widget.rect.width = DEFAULT_WIDTH;
	win->widget.rect.height = DEFAULT_HEIGHT;

    win->iconMargin = DEFAULT_ICON_MARGIN;

	win->widget.borderType = LA_WIDGET_BORDER_BEVEL;

	laString_Initialize(&win->title);
}

void _laWindowWidget_Destructor(laWindowWidget* win)
{
	laString_Destroy(&win->title);

    // free any existing memory reader
	if(win->reader != NULL)
	{
	    laContext_GetActive()->memIntf.heap.free(win->reader);
	    
	    win->reader = NULL;
	}

	_laWidget_Destructor((laWidget*)win);
}

laWindowWidget* laWindowWidget_New()
{
	laWindowWidget* win = NULL;

	if(laContext_GetActive() == NULL)
		return NULL;

	win = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laWindowWidget));

	_laWindowWidget_Constructor(win);

	return win;
}

void laWindowWidget_GetTitle(laWindowWidget* win, laString* str)
{
    if(win == NULL)
        return;
    
    laString_Copy(str, &win->title);
}

void laWindowWidget_SetTitle(laWindowWidget* win, laString str)
{
    if(win == NULL)
        return;
        
    if(laString_Compare(&win->title, &str) == 0)
        return;
        
    laString_Copy(&win->title, &str);
    
    laWidget_Invalidate((laWidget*)win);
}

GFXU_ImageAsset* laWindowWidget_GetIcon(laWindowWidget* win)
{
    if(win == NULL)
        return NULL;
        
    return win->icon;
}
                                                              
laResult laWindowWidget_SetIcon(laWindowWidget* win, GFXU_ImageAsset* img)
{
    if(win == NULL)
        return LA_FAILURE;
        
    if(win->icon == img)
        return LA_SUCCESS;
        
    win->icon = img;
    
    laWidget_Invalidate((laWidget*)win);
    
    return LA_SUCCESS;
}

uint32_t laWindowWidget_GetIconMargin(laWindowWidget* win)
{
    if(win == NULL)
		return 0;

	return win->iconMargin;
}
                                               
laResult laWindowWidget_SetIconMargin(laWindowWidget* win, uint32_t mg)
{
    if(win == NULL)
        return LA_FAILURE;
        
    if(win->iconMargin == mg)
		return LA_SUCCESS;

	win->iconMargin = mg;

	laWidget_Invalidate((laWidget*)win);
	
	return LA_SUCCESS;
}

#endif // LA_WINDOW_WIDGET_ENABLED