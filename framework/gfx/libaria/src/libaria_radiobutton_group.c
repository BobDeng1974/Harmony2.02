#include "gfx/libaria/inc/libaria_radiobutton_group.h"

#if LA_RADIOBUTTON_WIDGET_ENABLED

#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_widget_radiobutton.h"

laResult laRadioButtonGroup_Create(laRadioButtonGroup** grp)
{
    laRadioButtonGroup* btnGrp;
    
	if(grp == NULL)
		return LA_FAILURE;
		
	*grp = NULL;
	
	btnGrp = laContext_GetActive()->memIntf.heap.calloc(1, sizeof(laRadioButtonGroup));

    if(btnGrp == NULL)
        return LA_FAILURE;

	btnGrp->selected = NULL;
	btnGrp->initialized = LA_FALSE;

	if(laList_Create(&btnGrp->buttonList) == LA_FAILURE)
		return LA_FAILURE;

	btnGrp->initialized = LA_TRUE;
	
	*grp = btnGrp;

	return LA_SUCCESS;
}

void laRadioButtonGroup_Destroy(laRadioButtonGroup* grp)
{
	if(grp == NULL)
		return;

	laList_Clear(&grp->buttonList);
	
	laContext_GetActive()->memIntf.heap.free(grp);
}

laResult laRadioButtonGroup_AddButton(laRadioButtonGroup* grp,
									  laRadioButtonWidget* btn)
{
	if(grp == NULL || grp->initialized != LA_TRUE)
		return LA_FAILURE;

	if(laList_Find(&grp->buttonList, btn) != -1)
		return LA_FAILURE;

    if(grp->buttonList.size > 0)
        _laRadioButtonWidget_Deselect(btn);
    else
        grp->selected = btn;

	laList_PushBack(&grp->buttonList, btn);
	
	btn->group = grp;

	return LA_SUCCESS;
}

laResult laRadioButtonGroup_RemoveButton(laRadioButtonGroup* grp,
										 laRadioButtonWidget* btn)
{
	if(grp == NULL || grp->initialized != LA_TRUE)
		return LA_FAILURE;

	if(laList_Find(&grp->buttonList, btn) == -1)
		return LA_FAILURE;

	laList_Remove(&grp->buttonList, btn);

    btn->group = NULL;
    
    laRadioButtonWidget_SetSelected(btn);
    
    if(grp->buttonList.size == 0)
        laRadioButtonGroup_Destroy(grp);

	return LA_SUCCESS;
}

laResult laRadioButtonGroup_SelectButton(laRadioButtonGroup* grp,
										 laRadioButtonWidget* btn)
{
	if(grp == NULL || grp->initialized != LA_TRUE || grp->selected == btn)
		return LA_FAILURE;

	if(laList_Find(&grp->buttonList, btn) == -1)
		return LA_FAILURE;

	_laRadioButtonWidget_Deselect(grp->selected);
	_laRadioButtonWidget_Select(btn);

	grp->selected = btn;

	return LA_SUCCESS;
}

#endif // LA_RADIOBUTTON_WIDGET_ENABLED