#pragma once
#include "GameObject.h"

#define DEATHBALL_SPEED 0.002f

#define DEATHBALL_RADIUS 60

#define DEATHBALL_BBOX_WIDTH 17
#define DEATHBALL_BBOX_HEIGHT 17


#define ID_SPRITE_DEATHBALL 132002



class DeathBall : public CGameObject
{
	float centerX;
	float centerY;
	float time;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	DeathBall(float x, float y) : CGameObject(x, y)
	{
		time = 1.0f;
		centerX = x;
		centerY = y;
		vx = DEATHBALL_SPEED;
	}
};

