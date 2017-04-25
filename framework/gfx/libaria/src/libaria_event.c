#include "gfx/libaria/inc/libaria_event.h"

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_input.h"

static void processEvent(laEvent* evt);

uint32_t laEvent_GetCount()
{
	laContext* context = laContext_GetActive();
	
	if(context == NULL)
		return 0;

	return context->event.events.size;
}

/*laResult laEvent_GetEvent(uint32_t index, laEvent* evt)
{
	laContext* context = laContext_GetActive();
	
	if(context == NULL || index >= context->event.events.size)
		return LA_FAILURE;

	laList_GetAtIndex(

	*evt = *context->event.events.elements[index];

	return LA_SUCCESS;
}*/

laResult laEvent_SetFilter(laEvent_FilterEvent cb)
{
	laContext* context = laContext_GetActive();
	
	if(context == NULL)
		return LA_FAILURE;

	context->event.filter = cb;

	return LA_SUCCESS;
}

laResult laEvent_AddEvent(laEvent* evt)
{
	laContext* context = laContext_GetActive();

	if(context == NULL || evt == NULL)
		return LA_FAILURE;

	laList_PushBack(&context->event.events, evt);

	return LA_SUCCESS;
}

laResult laEvent_ClearList()
{
	laContext* context = laContext_GetActive();

	if(context == NULL)
		return LA_FAILURE;

	laList_Destroy(&context->event.events);

	return LA_SUCCESS;
}

laResult laEvent_ProcessEvents()
{
	laContext* context = laContext_GetActive();
	laEvent* evt;
	laListNode* node;

	if(context == NULL)
		return LA_FAILURE;

	if(context->event.events.size == 0)
		return LA_SUCCESS;

	node = context->event.events.head;

	while(node != NULL)
	{
		evt = node->val;

		if(context->event.filter != NULL &&
		   context->event.filter(evt) == LA_FALSE)
		   continue;

		processEvent(evt);

		node = node->next;
	}

    // destroys all events in the list (also frees memory)
	laList_Destroy(&context->event.events);

	return LA_SUCCESS;
}

static void processEvent(laEvent* evt)
{
	switch(evt->id)
	{
	    case LA_EVENT_SCREEN_CHANGE:
	    {
	        _laContext_HandleScreenChangeEvent(evt);
	        
	        break;
	    }
		case LA_EVENT_TOUCH_DOWN:
		case LA_EVENT_TOUCH_UP:
		case LA_EVENT_TOUCH_MOVED:
		{
			_laInput_HandleInputEvent(evt);
			
			break;
		}
        default:
            break;
	}
}