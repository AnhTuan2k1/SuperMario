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


#define KOOPA_STATE_WALKING 110
#define KOOPA_STATE_SHELL 220
//#define KOOPA_STATE_HIDE 330
#define KOOPA_STATE_SHELL_RUNNING 440
#define KOOPA_STATE_DIE_BYKOOPAS 550


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

	virtual int IsCollidable() { return (state != KOOPA_STATE_DIE_BYKOOPAS); };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithMario(LPCOLLISIONEVENT e);
	void OnCollisionWithRedKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
public:
	Koopa(float x, float y) : CGameObject(x, y) 
	{
		this->ax = 0;
		this->ay = KOOPA_GRAVITY;
		hide_start = -1;
		SetState(KOOPA_STATE_WALKING);
	}
	virtual void SetState(int state);
	void SetState(int state, int direct);
};

//class RedKoopa : public Koopa
//{
//
//	float rectangleX;
//	float rectangleWidth;
//	bool isGetPosition;
//
//	virtual void Render()
//	{
//		int aniId = ID_ANI_REDKOOPA_WALKING_LEFT;
//		if (state == REDKOOPA_STATE_WALKING_RIGHT)
//		{
//			aniId = ID_ANI_REDKOOPA_WALKING_RIGHT;
//		}
//
//		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
//	}
//
//public:
//	RedKoopa(float x, float y) : Koopa(x, y)
//	{
//		SetState(REDKOOPA_STATE_WALKING_LEFT);
//		isGetPosition = false;
//		rectangleX = 0;
//		rectangleWidth = 0;
//	}
//
//
//
//	virtual void OnCollisionWith(LPCOLLISIONEVENT e)
//	{
//		if (e->ny != 0 && e->obj->IsBlocking())
//		{
//			if (e->ny < 0 && e->obj->IsBlocking())
//			{
//				vy = 0;
//				return;
//			}
//			vy = 0;
//		}
//		else
//			if (e->nx != 0 && e->obj->IsBlocking())
//			{
//				vx = -vx;
//			}
//		
//
//	}
//	
//
//};