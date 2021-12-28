#pragma once
#include "GameObject.h"

#define LAVA_WIDTH 15
#define LAVA_HIGHT 14
#define ID_ANI_SPRITE_PIPE 134101

class Lava : public  CGameObject
{
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnNoCollision(DWORD dt) {};

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

public:
	Lava(float x, float y) : CGameObject(x, y)
	{

	}

};

