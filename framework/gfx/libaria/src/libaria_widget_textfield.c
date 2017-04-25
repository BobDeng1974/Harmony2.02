#include "gfx/libaria/inc/libaria_widget_textfield.h"

#if LA_TEXTFIELD_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

#define DEFAULT_WIDTH           100
#define DEFAULT_HEIGHT          25

#define DEFAULT_CURSOR_TIME     500

static void _setCursorFromPoint(laTextFieldWidget* txt, GFX_Point* pnt)
{
    GFX_Rect textRect;
    
    laString_GetRect(&txt->text, &textRect);
    
    laUtils_ArrangeRectangleRelative(&textRect,
                                     GFX_Rect_Zero,
                                     txt->editWidget.widget.rect,
                                     txt->halign,
                                     LA_VALIGN_MIDDLE,
                                     0,
                                     txt->editWidget.widget.margin.left,
                                     txt->editWidget.widget.margin.top,
                                     txt->editWidget.widget.margin.right,
                                     txt->editWidget.widget.margin.bottom,
                                     0);
    
    laUtils_RectToScreenSpace((laWidget*)txt, &textRect);
    
    laTextFieldWidget_SetCursorPosition(txt, laString_GetCharIndexAtPoint(&txt->text, pnt->x - txt->editWidget.widget.rect.x));
}

void _laTextFieldWidget_Constructor(laTextFieldWidget* txt)
{
	_laEditWidget_Constructor((laEditWidget*)txt);
	
	txt->editWidget.widget.destructor = (laWidget_Destructor_FnPtr)&_laTextFieldWidget_Destructor;

	txt->editWidget.widget.type = LA_WIDGET_TEXTFIELD;

	// override base class methods
	txt->editWidget.widget.update = (laWidget_Update_FnPtr)&_laTextFieldWidget_Update;
	txt->editWidget.widget.paint = (laWidget_Paint_FnPtr)&_laTextFieldWidget_Paint;
	txt->editWidget.widget.focusGained = (laWidget_Focus_FnPtr)&_laTextFieldWidget_FocusGained;
	txt->editWidget.widget.focusLost = (laWidget_Focus_FnPtr)&_laTextFieldWidget_FocusLost;
	txt->editWidget.widget.touchDown = (laWidget_TouchDownEvent_FnPtr)&_laTextFieldWidget_TouchDownEvent;
	txt->editWidget.widget.touchUp = (laWidget_TouchUpEvent_FnPtr)&_laTextFieldWidget_TouchUpEvent;
	txt->editWidget.widget.touchMoved = (laWidget_TouchMovedEvent_FnPtr)&_laTextFieldWidget_TouchMovedEvent;

    // override edit class methods
    txt->editWidget.startEdit = (laEditWidget_StartEdit_FnPtr)&laTextFieldWidget_StartEdit;
    txt->editWidget.endEdit = (laEditWidget_EndEdit_FnPtr)&laTextFieldWidget_EndEdit;
    txt->editWidget.clear = (laEditWidget_Clear_FnPtr)&laTextFieldWidget_Clear;
    txt->editWidget.accept = (laEditWidget_Accept_FnPtr)&laTextFieldWidget_Accept;
    txt->editWidget.append = (laEditWidget_Append_FnPtr)&laTextFieldWidget_Append;
    txt->editWidget.set = (laEditWidget_Set_FnPtr)&laTextFieldWidget_Set;
    txt->editWidget.backspace = (laEditWidget_Backspace_FnPtr)&laTextFieldWidget_Backspace;

	txt->editWidget.widget.rect.width = DEFAULT_WIDTH;
	txt->editWidget.widget.rect.height = DEFAULT_HEIGHT;
	
	txt->editWidget.widget.borderType = LA_WIDGET_BORDER_BEVEL;

	laString_Initialize(&txt->text);
	
	txt->halign = LA_HALIGN_LEFT;
	txt->editable = LA_TRUE;
	txt->cursorEnable = LA_TRUE;
	txt->cursorDelay = DEFAULT_CURSOR_TIME;
}

void _laTextFieldWidget_Destructor(laTextFieldWidget* txt)
{
	laString_Destroy(&txt->text);
	
	// free any existing memory reader
	if(txt->reader != NULL)
	{
	    laContext_GetActive()->memIntf.heap.free(txt->reader);
	    
	    txt->reader = NULL;
	}

	_laEditWidget_Destructor((laEditWidget*)txt);
}

void _laTextFieldWidget_Update(laTextFieldWidget* txt, uint32_t dt)
{
    if(laContext_GetActive()->edit == (laEditWidget*)txt)
    {
        txt->cursorTime += dt;
        
        if(txt->cursorTime > txt->cursorDelay)
        {
            txt->cursorVisible = !txt->cursorVisible;
            
            //printf("%u\n", txt->cursorTime);
            
            txt->cursorTime = 0;
            
            laWidget_Invalidate((laWidget*)txt);
        }
    }
}

laTextFieldWidget* laTextFieldWidget_New()
{
	laTextFieldWidget* txt = NULL;

	if(laContext_GetActive() == NULL)
		return NULL;

	txt = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laTextFieldWidget));

	_laTextFieldWidget_Constructor(txt);

	return txt;
}

laHAlignment laTextFieldWidget_GetAlignment(laTextFieldWidget* txt)
{
	if(txt == NULL)
		return 0;

	return txt->halign;
}

void laTextFieldWidget_SetAlignment(laTextFieldWidget* txt, laHAlignment align)
{
	if(txt == NULL || txt->halign == align)
		return;

	txt->halign = align;

	laWidget_Invalidate((laWidget*)txt);
}

uint32_t laTextFieldWidget_GetCursorDelay(laTextFieldWidget* txt)
{
    if(txt == NULL)
		return 0;

	return txt->cursorDelay;
}

void laTextFieldWidget_SetCursorDelay(laTextFieldWidget* txt, uint32_t dt)
{
    if(txt == NULL || txt->cursorDelay == dt)
		return;

	txt->cursorDelay = dt;

    if(txt->cursorEnable == LA_TRUE && txt->cursorVisible == LA_TRUE)
	    laWidget_Invalidate((laWidget*)txt);
}

laBool laTextFieldWidget_GetCursorEnabled(laTextFieldWidget* txt)
{
    if(txt == NULL)
		return LA_FALSE;

	return txt->cursorEnable;
}

void laTextFieldWidget_SetCursorEnabled(laTextFieldWidget* txt, laBool en)
{
    if(txt == NULL || txt->cursorEnable == en)
		return;

	txt->cursorEnable = en;

    if(txt->cursorEnable == LA_TRUE && txt->cursorVisible == LA_TRUE)
	    laWidget_Invalidate((laWidget*)txt);
}

uint32_t laTextFieldWidget_GetCursorPosition(laTextFieldWidget* txt)
{
    if(txt == NULL)
		return 0;

	return txt->cursorPos;
}

void laTextFieldWidget_SetCursorPosition(laTextFieldWidget* txt, uint32_t pos)
{
    if(txt == NULL || txt->cursorPos == pos)
		return;

	txt->cursorPos = pos;

    if(txt->cursorVisible == LA_TRUE)
	    laWidget_Invalidate((laWidget*)txt);
}

void laTextFieldWidget_GetText(laTextFieldWidget* txt, laString* str)
{
    if(txt == NULL)
        return;
    
    laString_Copy(str, &txt->text);
}

void laTextFieldWidget_SetText(laTextFieldWidget* txt, laString str)
{
    if(txt == NULL)
        return;
        
    if(laString_Compare(&txt->text, &str) == 0)
        return;
        
    laString_Copy(&txt->text, &str);
    
    txt->cursorPos = txt->text.length;
    
    laWidget_Invalidate((laWidget*)txt);
}

void _laTextFieldWidget_FocusGained(laWidget* widget)
{
    laContext_SetEditWidget(widget);
}

void _laTextFieldWidget_FocusLost(laWidget* widget)
{
    //printf("focus lost\n");
}

laTextFieldWidget_TextChangedCallback laTextFieldWidget_GetTextChangedEventCallback(laTextFieldWidget* txt)
{
	if(txt == NULL)
		return NULL;

	return txt->textChangedEvent;
}

void laTextFieldWidget_SetTextChangedEventCallback(laTextFieldWidget* txt,
											       laTextFieldWidget_TextChangedCallback cb)
{
	if(txt == NULL || txt->textChangedEvent == cb)
		return;

	txt->textChangedEvent = cb;
}

laResult laTextFieldWidget_StartEdit(laTextFieldWidget* txt)
{
    txt->cursorTime = 0;
    txt->cursorVisible = LA_TRUE;
    laWidget_Invalidate((laWidget*)txt);
    
    return LA_SUCCESS;
}

void laTextFieldWidget_EndEdit(laTextFieldWidget* txt)
{
    txt->cursorTime = 0;
    txt->cursorVisible = LA_FALSE;
    laWidget_Invalidate((laWidget*)txt);
}

void laTextFieldWidget_Clear(laTextFieldWidget* txt)
{
    laString_Clear(&txt->text);
    laWidget_Invalidate((laWidget*)txt);
}

void laTextFieldWidget_Accept(laTextFieldWidget* txt)
{
    laContext_SetEditWidget(NULL);
}

void laTextFieldWidget_Append(laTextFieldWidget* txt, laString str)
{
    // initial string value is probably referencing string table
    // extract it to local cache and to make editable
    if(txt->text.table_index != LA_STRING_NULLIDX)
        laString_ExtractFromTable(&txt->text, txt->text.table_index);

    laString_Insert(&txt->text, &str, txt->cursorPos);
    
    txt->cursorPos += laString_Length(&str);
    
    laWidget_Invalidate((laWidget*)txt);
}

void laTextFieldWidget_Set(laTextFieldWidget* txt, laString str)
{
    laString_ExtractFromTable(&txt->text, str.table_index);
    
    txt->cursorPos = txt->text.length;

    laWidget_Invalidate((laWidget*)txt);
}

void laTextFieldWidget_Backspace(laTextFieldWidget* txt)
{
    laString_ReduceLength(&txt->text, txt->text.length - 1);
    
    txt->cursorPos = txt->text.length;

    laWidget_Invalidate((laWidget*)txt);
}

void _laTextFieldWidget_TouchDownEvent(laTextFieldWidget* txt,
                                       laInput_TouchDownEvent* evt)
{
    GFX_Point pnt;
    
    pnt.x = evt->x;
    pnt.y = evt->y;
    
    _setCursorFromPoint(txt, &pnt);
    
    evt->event.accepted = LA_TRUE;
}

void _laTextFieldWidget_TouchUpEvent(laTextFieldWidget* txt,
                                     laInput_TouchUpEvent* evt)
{
    evt->event.accepted = LA_TRUE;
}

void _laTextFieldWidget_TouchMovedEvent(laTextFieldWidget* txt,
                                        laInput_TouchMovedEvent* evt)
{
    /*GFX_Point pnt;
    
    pnt.x = evt->x;
    pnt.y = evt->y;
    
    _setCursorFromPoint(txt, &pnt);*/
    
    evt->event.accepted = LA_TRUE;
}

#endif // LA_TEXTFIELD_WIDGET_ENABLED