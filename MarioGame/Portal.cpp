#include "Portal.h"


CPortal::CPortal(float l, float t, float r, float b, int scene_id )
{
	this->scene_id = scene_id;
	x = l; 
	y = t;
	width = r - l;
	height = b - t;
	isSwitchScene = false;
}

CPortal::CPortal(float l, float t, float r, float b, int scene_id, bool isreward)
{
	this->scene_id = scene_id;
	x = l;
	y = t;
	width = r - l;
	height = b - t;
	isSwitchScene = true;
}

void CPortal::Render()
{
	if (isSwitchScene)
	{
		CAnimations::GetInstance()->Get(ID_ANI_REWARD)->Render(x, y);
	}

	//RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (isSwitchScene)
	{
		l = x - REWARD_BBOX_WIDTH / 2;
		t = y - REWARD_BBOX_HEIGHT / 2;
		r = l + REWARD_BBOX_WIDTH;
		b = t + REWARD_BBOX_HEIGHT;
	}
	else
	{
		l = x;
		t = y;
		r = x + width;
		b = y + height;
	}
	
}