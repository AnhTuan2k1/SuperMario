#pragma once
#include "GameObject.h"

#define THORN_WIDTH 15
#define THORN_HIGHT 225
#define ID_SPRITE_PIPE 133001

#define THORN_SPEED 0.05f
#define THORN_HIGHT_SCOPE 105

#define THORN_STATE_STATIC 131451
#define THORN_STATE_MOVE 131452

class Thorn : public  CGameObject
{
	float init_y;

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnNoCollision(DWORD dt);

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
public:
	virtual void SetState(int state);
	Thorn(float x, float y) : CGameObject(x, y)
	{
		init_y = y;
		SetState(THORN_STATE_STATIC);
	}
};

