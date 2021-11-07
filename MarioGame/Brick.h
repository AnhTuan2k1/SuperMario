#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define ID_ANI_ROCK_BRICK 10010

#define ID_ANI_BRICK_CLASSICAL 10020
#define ID_ANI_ROCK_BRICK_CLASSICAL 10030

#define BRICK_HEIGHT_BOUNCE 7
#define BRICK_SPEED_BOUNCE 0.01f

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_BOUNCE 154
#define BRICK_STATE_STATIC 144
#define BRICK_STATE_ROCK 134

#define DCOIN_BOUNCE_TIMES 5

class CBrick : public CGameObject {

	float ay;
	int y_initial;
	int bounce_times;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

public:
	CBrick(float x, float y) : CGameObject(x, y) 
	{
		y_initial = y;
		ay = 0;
		SetState(BRICK_STATE_STATIC);
		bounce_times = DCOIN_BOUNCE_TIMES;
	}

	int GetBounceTimes() { return bounce_times; }
	virtual void OnNoCollision(DWORD dt);
	virtual void SetState(int state);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};