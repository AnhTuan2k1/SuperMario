#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.03f
#define KOOPA_RUNING_SPEED 0.2f

#define KOOPA_SHELL_TIMEOUT 3000

#define KOOPA_BBOX_WIDTH 15
#define KOOPA_BBOX_WIDTH_SHELL 15
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_HEIGHT_SHELL 15


#define KOOPA_STATE_WALKING 110
#define KOOPA_STATE_SHELL 220
//#define KOOPA_STATE_HIDE 330
#define KOOPA_STATE_SHELL_RUNNING 440

#define ID_ANI_KOOPA_WALKING 6000
#define ID_ANI_KOOPA_SHELL 6001





class Koopa : public CGameObject
{
	float ax;
	float ay;

	ULONGLONG hide_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithMario(LPCOLLISIONEVENT e);
public:
	Koopa(float x, float y, int state);
	virtual void SetState(int state);
    void SetState(int state, int direct);
};

