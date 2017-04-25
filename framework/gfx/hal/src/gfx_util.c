#include "gfx/hal/inc/gfx_util.h"

typedef void (*GFX_Orient_FnPtr)(GFX_Point*, GFX_Rect*, GFX_Bool);

static void orient_0(GFX_Point* pnt, GFX_Rect* rect, GFX_Bool mirror);
static void orient_90(GFX_Point* pnt, GFX_Rect* rect, GFX_Bool mirror);
static void orient_180(GFX_Point* pnt, GFX_Rect* rect, GFX_Bool mirror);
static void orient_270(GFX_Point* pnt, GFX_Rect* rect, GFX_Bool mirror);

GFX_Orient_FnPtr orient_ptrs[] =
{
    &orient_0,
    &orient_90,
    &orient_180,
    &orient_270
};

void orient_0(GFX_Point* pnt, GFX_Rect* rect, GFX_Bool mirror)
{ 
    if(mirror == GFX_TRUE)
        pnt->x = rect->width - 1 - pnt->x;
}

void orient_90(GFX_Point* pnt, GFX_Rect* rect, GFX_Bool mirror)
{
    int32_t tx;
    
    if(mirror == GFX_TRUE)
    {
        tx = pnt->x;
        pnt->x = rect->width - 1 - pnt->y;
        pnt->y = rect->height - 1 - tx;
    }
    else
    {
        tx = pnt->x;
        pnt->x = rect->width - 1 - pnt->y;
        pnt->y = tx;
    }
}

void orient_180(GFX_Point* pnt, GFX_Rect* rect, GFX_Bool mirror)
{
    if(mirror == GFX_TRUE)
    {
        pnt->y = rect->height - 1 - pnt->y;
    }
    else
    {
        pnt->x = rect->width - 1 - pnt->x;
        pnt->y = rect->height - 1 - pnt->y;
    }
}

void orient_270(GFX_Point* pnt, GFX_Rect* rect, GFX_Bool mirror)
{
	int32_t tx;
    
    if(mirror == GFX_TRUE)
    {
        tx = pnt->x;
        pnt->x = rect->width - 1 - pnt->y;
        pnt->y = rect->height - 1 - tx;
    }
    else
    {
        tx = pnt->y;
        pnt->y = rect->height - 1 - pnt->x;
        pnt->x = tx;
    }
}

void GFX_UtilOrientPoint(GFX_Point* pnt,
                         GFX_Rect* rect,
                         GFX_Orientation ori,
                         GFX_Bool mirror)
{
    orient_ptrs[ori](pnt, rect, mirror);    
}

void GFX_LayerOriginFromOrientedSpace(GFX_Point* point,
									  GFX_Rect* displayRect,
									  GFX_Rect* layerRect,
									  GFX_Orientation ori,
									  GFX_Bool mirrored)
{
	switch(ori)
    {
        case GFX_ORIENTATION_0:
        {
            if(mirrored == GFX_TRUE)
                point->x = displayRect->width - 1 - layerRect->width - layerRect->x;
            else
                point->x = layerRect->x;
            
			point->y = layerRect->y;
            //point->y = displayRect->y;
            
            break;
        }
        case GFX_ORIENTATION_90:
        {
            point->y = displayRect->width - 1 - layerRect->x - layerRect->width;
            
            if(mirrored == GFX_TRUE)
                point->x = displayRect->height - 1 - layerRect->height - layerRect->y;
            else
                point->x = layerRect->y;
            
            break;
        }
        case GFX_ORIENTATION_180:
        {         
			point->y = displayRect->height - 1 - (layerRect->height + layerRect->y);

            if(mirrored == GFX_TRUE)
				point->x = layerRect->x;
            else
				point->x = displayRect->width - 1 - layerRect->width - layerRect->x;

            break;
        }
        case GFX_ORIENTATION_270:
        {
			point->y = layerRect->x;
            
            if(mirrored == GFX_TRUE)
				point->x = layerRect->y;
            else
                point->x = displayRect->height - 1 - (layerRect->height + layerRect->y);

            break;
        }
    }
}

void GFX_LayerOriginToOrientedSpace(GFX_Point* point,
									GFX_Rect* displayRect,
									GFX_Rect* layerRect,
									GFX_Orientation ori,
									GFX_Bool mirrored)
{
	GFX_Point pnt = {0};

	//pnt.x = point->x;
	//pnt.y = point->y;

	switch(ori)
    {
        case GFX_ORIENTATION_0:
        {
            if(mirrored == GFX_TRUE)
                pnt.x = displayRect->width - 1 - layerRect->width - point->x;
            else
                pnt.x = point->x;

			pnt.y = point->y;
            
            break;
        }
        case GFX_ORIENTATION_90:
        {
            pnt.x = displayRect->width - 1 - layerRect->width - point->y;
            
            if(mirrored == GFX_TRUE)
                pnt.y = displayRect->height - 1 - layerRect->height - point->x;
            else
                pnt.y = point->x;
                
            break;
        }
        case GFX_ORIENTATION_180:
        {
            if(mirrored == GFX_TRUE)
                pnt.x = point->x;
            else
                pnt.x = displayRect->width - 1 - layerRect->width - point->x;

			pnt.y = displayRect->height - 1 - layerRect->height - point->y;
            
            break;
        }
        case GFX_ORIENTATION_270:
        {
			pnt.x = point->y;

            if(mirrored == GFX_TRUE)
                pnt.y = point->x;
            else
                pnt.y = displayRect->height - 1 - layerRect->height - point->x;
                    
            break;
        }
    }
	
	point->x = pnt.x;
	point->y = pnt.y;
}

void GFX_LayerSizeFromOrientedSpace(GFX_Size* layerSize, GFX_Orientation ori)
{
	uint32_t t;

	if(ori == GFX_ORIENTATION_90 || ori == GFX_ORIENTATION_270)
	{
		t = layerSize->width;
		layerSize->width = layerSize->height;
		layerSize->height = t;
	}
}

void GFX_LayerSizeToOrientedSpace(GFX_Size* layerSize, GFX_Orientation ori)
{
	uint32_t t;

	if(ori == GFX_ORIENTATION_90 || ori == GFX_ORIENTATION_270)
	{
		t = layerSize->width;
		layerSize->width = layerSize->height;
		layerSize->height = t;
	}
}