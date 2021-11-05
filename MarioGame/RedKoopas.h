#pragma once
#include "GameObject.h"


#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.03f
#define KOOPA_RUNING_SPEED 0.2f
#define KOOPA_JUMP_DEFLECT_SPEED 0.3f

#define KOOPA_SHELL_TIMEOUT 7000

#define KOOPA_BBOX_WIDTH 15
#define KOOPA_BBOX_WIDTH_SHELL 15
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_HEIGHT_SHELL 15


#define REDKOOPA_STATE_WALKING_LEFT 120
#define REDKOOPA_STATE_WALKING_RIGHT 121

#define REDKOOPA_STATE_SHELL 220
//#define KOOPA_STATE_HIDE 330
#define REDKOOPA_STATE_SHELL_RUNNING 440
#define REDKOOPA_STATE_DIE_BYKOOPAS 550

#define ID_ANI_REDKOOPA_WALKING_LEFT 6002
#define ID_ANI_REDKOOPA_WALKING_RIGHT 6003
#define ID_ANI_REDKOOPA_SHELL 6004

class RedKoopas : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG hide_start;

	float rectangleX;
	float rectangleWidth;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return (state != REDKOOPA_STATE_DIE_BYKOOPAS); };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithMario(LPCOLLISIONEVENT e);
	void OnCollisionWithRedKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithRectangle(LPCOLLISIONEVENT e);
public:
	RedKoopas(float x, float y) : CGameObject(x, y)
	{
		this->ax = 0;
		this->ay = KOOPA_GRAVITY;
		hide_start = -1;
		SetState(REDKOOPA_STATE_WALKING_LEFT);

		rectangleX = 0;
		rectangleWidth = 0;
	}
	virtual void SetState(int state);
	void SetState(int state, int direct);
};


