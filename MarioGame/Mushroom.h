#pragma once
#include "GameObject.h"


#define MUSHROOM_GRAVITY 0.0008f
#define MUSHROOM_SPEED 0.075f
#define MUSHROOM_SPEED_BOUNCE 0.015f
#define MUSHROOM_HEIGHT_BOUNCE 16

#define MUSHROOM_BBOX_WIDTH 15
#define MUSHROOM_BBOX_HEIGHT 15

#define MUSHROOM_STATE_MOVING 113
#define MUSHROOM_STATE_HIDE 114
#define MUSHROOM_STATE_BOUNCE 115


class Mushroom : public CGameObject
{
protected:
	float ax;
	float ay;
	float y_initial;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable()
	{
		return 1;
	};
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	Mushroom(float x, float y);
	virtual void SetState(int state);
};

