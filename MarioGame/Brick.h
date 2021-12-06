#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10020
#define ID_ANI_ROCK_BRICK 10030

#define ID_ANI_BRICK_CLASSICAL 10000
#define ID_ANI_ROCK_BRICK_CLASSICAL 10010

#define BRICK_HEIGHT_BOUNCE 7
#define BRICK_SPEED_BOUNCE 0.01f

#define BRICK_WIDTH 15
#define BRICK_BBOX_WIDTH 15
#define BRICK_BBOX_HEIGHT 15

#define BRICK_STATE_BOUNCE 154
#define BRICK_STATE_STATIC 144
#define BRICK_STATE_ROCK 134
#define BRICK_STATE_BREAK 133

#define DCOIN_BOUNCE_TIMES 5

class CBrick : public CGameObject {

	float ay;
	float y_initial;
	int bounce_times;
	bool isBreak;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

public:
	CBrick(float x, float y, bool isBreak = false, int state = BRICK_STATE_STATIC) : CGameObject(x, y)
	{
		y_initial = y;
		ay = 0;
		SetState(state);
		bounce_times = DCOIN_BOUNCE_TIMES;
		this->isBreak = isBreak;
	}

	bool Isbreak() { return isBreak; }
	float GetX() { return x; }
	float GetY() { return y; }
	int GetBounceTimes() { return bounce_times; }
	virtual void OnNoCollision(DWORD dt);
	virtual void SetState(int state);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

#define PIECE_BRICK 22222
#define PIECE_BRICK_GRAVITY 0.008f
class PieceBrick : public CGameObject {

	float ay;

	int IsBlocking() {return 0;}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

public:
	PieceBrick(float x, float y, int type = 1);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};