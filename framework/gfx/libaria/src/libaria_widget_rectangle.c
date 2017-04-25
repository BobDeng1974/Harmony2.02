#include "gfx/libaria/inc/libaria_widget_rectangle.h"

#if LA_RECTANGLE_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define DEFAULT_WIDTH           100
#define DEFAULT_HEIGHT          100

#define DEFAULT_THICKNESS       2

void _laRectangleWidget_Constructor(laRectangleWidget* rect)
{
	_laWidget_Constructor((laWidget*)rect);
	
	rect->widget.destructor = (laWidget_Destructor_FnPtr)&_laRectangleWidget_Destructor;

	rect->widget.type = LA_WIDGET_RECTANGLE;

	// override base class methods
	rect->widget.paint = (laWidget_Paint_FnPtr)&_laRectangleWidget_Paint;

	rect->widget.rect.width = DEFAULT_WIDTH;
	rect->widget.rect.height = DEFAULT_HEIGHT;

	rect->widget.borderType = LA_WIDGET_BORDER_NONE;
	rect->widget.drawBackground = LA_TRUE;

	rect->thickness = DEFAULT_THICKNESS;
}

void _laRectangleWidget_Destructor(laRectangleWidget* rect)
{
	_laWidget_Destructor((laWidget*)rect);
}

laRectangleWidget* laRectangleWidget_New()
{
	laRectangleWidget* rect = NULL;

	if(laContext_GetActive() == NULL)
		return NULL;

	rect = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laRectangleWidget));

    if(rect == NULL)
        return NULL;
    
	_laRectangleWidget_Constructor(rect);

	return rect;
}

uint32_t laRectangleWidget_GetThickness(laRectangleWidget* rect)
{
    if(rect == NULL)
        return 0;
        
    return rect->thickness;
}

laResult laRectangleWidget_SetThickness(laRectangleWidget* rect, uint32_t thk)
{
    if(rect == NULL)
        return LA_FAILURE;
        
    if(rect->thickness == thk)
        return LA_SUCCESS;
        
    rect->thickness = thk;
    
    laWidget_Invalidate((laWidget*)rect);
        
    return LA_SUCCESS;
}

#endif // LA_RECTANGLE_WIDGET_ENABLED