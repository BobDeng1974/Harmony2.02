#include "gfx/libaria/inc/libaria_input.h"
#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/inc/libaria_widget.h"

laBool laInput_GetEnabled()
{
	laContext* context = laContext_GetActive();
	
	if(context == NULL)
		return LA_FALSE;

	return context->input.enabled;
}

laResult laInput_SetEnabled(laBool enable)
{
	laContext* context = laContext_GetActive();
	
	if(context == NULL)
		return LA_FAILURE;

	context->input.enabled = enable;

	return LA_SUCCESS;
}

laResult laInput_InjectTouchDown(uint32_t id, int32_t x, int32_t y)
{
	laInput_TouchDownEvent* evt;
	laContext* context = laContext_GetActive();

	if(context == NULL ||                          // need a valid context
	   context->input.enabled == LA_FALSE ||       // inputs are disabled
	   id >= LA_MAX_TOUCH_STATES ||                // don't overrun array
	   context->input.touch[id].valid == LA_TRUE)  // touch id must be invalid
		return GFX_FAILURE;

	context->input.touch[id].valid = LA_TRUE;
	context->input.touch[id].x = x;
	context->input.touch[id].y = y;

	evt = context->memIntf.heap.calloc(1, sizeof(laInput_TouchDownEvent));

	if(evt == NULL)
		return GFX_FAILURE;
    
	evt->event.id = LA_EVENT_TOUCH_DOWN;
	evt->touchID = id;
	evt->x = x;
	evt->y = y;

	if(laEvent_AddEvent((laEvent*)evt) == GFX_FAILURE)
	{
		context->memIntf.heap.free(evt);

		return GFX_FAILURE;
	}	

	return GFX_SUCCESS;
}

laResult laInput_InjectTouchUp(uint32_t id, int32_t x, int32_t y)
{
	laInput_TouchUpEvent* evt;
	laContext* context = laContext_GetActive();

	if(context == NULL ||                           // need a valid context
	   id >= LA_MAX_TOUCH_STATES ||                 // don't overrun array
	   context->input.touch[id].valid == LA_FALSE)  // touch id must be valid
		return GFX_FAILURE;

	context->input.touch[id].valid = LA_FALSE;

	evt = context->memIntf.heap.calloc(1, sizeof(laInput_TouchUpEvent));

	if(evt == NULL)
		return GFX_FAILURE;
    
	evt->event.id = LA_EVENT_TOUCH_UP;
	evt->touchID = id;
	evt->x = x;
	evt->y = y;

	if(laEvent_AddEvent((laEvent*)evt) == GFX_FAILURE)
	{
		context->memIntf.heap.free(evt);

		return GFX_FAILURE;
	}	

	return GFX_SUCCESS;
}

laResult laInput_InjectTouchMoved(uint32_t id, int32_t x, int32_t y)
{
	laInput_TouchMovedEvent* evt;
	laContext* context = laContext_GetActive();

	if(context == NULL ||                           // need a valid context
	   id >= LA_MAX_TOUCH_STATES ||                 // don't overrun array
	   context->input.touch[id].valid == LA_FALSE)  // touch id must be valid
		return GFX_FAILURE;

	evt = context->memIntf.heap.calloc(1, sizeof(laInput_TouchMovedEvent));

	if(evt == NULL)
		return GFX_FAILURE;

	evt->event.id = LA_EVENT_TOUCH_MOVED;
	evt->touchID = id;
	evt->prevX = context->input.touch[id].x;
	evt->prevY = context->input.touch[id].y;
	evt->x = x;
	evt->y = y;

	context->input.touch[id].x = x;
	context->input.touch[id].y = y;

	if(laEvent_AddEvent((laEvent*)evt) == GFX_FAILURE)
	{
		context->memIntf.heap.free(evt);

		return GFX_FAILURE;
	}	

	return GFX_SUCCESS;
}

void handleTouchDown(laInput_TouchDownEvent* evt)
{
	laWidget* targetWidget;

	targetWidget = laUtils_Pick(evt->x, evt->y);

	if(targetWidget == NULL)
		return;

	while(targetWidget != NULL)
	{
		targetWidget->touchDown(targetWidget, evt);
		
		if(evt->event.accepted == LA_TRUE)
			break;

		targetWidget = targetWidget->parent;
	}

	laContext_SetFocusWidget(targetWidget);
}

void handleTouchUp(laInput_TouchUpEvent* evt)
{
	laContext* context = laContext_GetActive();

	if(context->focus == NULL)
		return;

	context->focus->touchUp(context->focus, evt);

	//context->focus = NULL;
}

void handleTouchMoved(laInput_TouchMovedEvent* evt)
{
	laContext* context = laContext_GetActive();

	if(context->focus == NULL)
		return;

	context->focus->touchMoved(context->focus, evt);
}

laResult _laInput_HandleInputEvent(laEvent* evt)
{
	//if(laContext_GetActive()->input.inputTarget == NULL)
	//	return LA_SUCCESS;

	switch(evt->id)
	{
		case LA_EVENT_TOUCH_DOWN:
		{
			handleTouchDown((laInput_TouchDownEvent*)evt);
			break;
		}
		case LA_EVENT_TOUCH_UP:
		{
			handleTouchUp((laInput_TouchUpEvent*)evt);
			break;
		}
		case LA_EVENT_TOUCH_MOVED:
		{
			handleTouchMoved((laInput_TouchMovedEvent*)evt);
			break;
		}
        default:
            break;
	}

	return LA_SUCCESS;
}