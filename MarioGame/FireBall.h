#pragma once
#include "GameObject.h"

#define FIREBALL_SPEED 0.175f
#define FIREBALL_SPEED_SLOW 0.12f
#define FIREBALL_SCOPE_Y 200
#define FIREBALL_TIME_DELAY 2000

#define FIREBALL_BBOX_WIDTH 15
#define FIREBALL_BBOX_HEIGHT 17

#define ID_ANI_FIREBALL_UP 131011
#define ID_ANI_FIREBALL_DOWN 131012

#define FIREBALL_STATE_DELAY 131313
#define FIREBALL_STATE_MOVE 131311

class FireBall : public CGameObject
{
	float y_initial;
	ULONGLONG delay_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void SetState(int state);

public:
	FireBall(float x, float y, bool isdelay = false) : CGameObject(x, y)
	{ 
		y_initial = y; 

		if (isdelay) SetState(FIREBALL_STATE_DELAY);
		else SetState(FIREBALL_STATE_MOVE);
	}
};

