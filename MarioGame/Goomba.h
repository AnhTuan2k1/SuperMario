#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f
#define WINGGOOMBA_FLY_SPEED 0.07f
#define GOOMBA_JUMP_DEFLECT_SPEED  0.35f
#define GOOMBA_JUMP_DEFLECT_SPEEDX  0.15f

#define GOOMBA_BBOX_WIDTH 15
#define GOOMBA_BBOX_HEIGHT 15
#define WINGGOOMBA_BBOX_WIDTH 20
#define WINGGOOMBA_BBOX_HEIGHT 18
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500
#define WINGGOOMBA_FLY_TIMEOUT 1500
#define WINGGOOMBA_WALK_TIMEOUT 2000
#define WINGGOOMBA_FLY_HEIGHT 25

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_DIE_BYKOOPAS -200
#define GOOMBA_STATE_HITTED_BYTAIL -271
#define WINGGOOMBA_STATE_HITTED_BYTAIL -272

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001


#define WINGGOOMBA_STATE_WALKING 110

#define ID_ANI_WINGGOOMBA_WALKING 5002
#define ID_ANI_WINGGOOMBA_FLY 5003

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 
	float fly_y;

	ULONGLONG die_start;
	ULONGLONG fly_start;
	ULONGLONG walk_start;

	bool isflying;
	bool isWalking;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() 
	{ 
		if (state == GOOMBA_STATE_DIE_BYKOOPAS || state == GOOMBA_STATE_HITTED_BYTAIL
			|| state == WINGGOOMBA_STATE_HITTED_BYTAIL)
			return false;
		else return true;
	};
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y, int state);
	CGoomba(float x, float y);
	virtual void SetState(int state);
	void SetState(int state, int direct);
	void StartFlying();
	void StartWalking();
	void EndWalking();
	void EndFlying();
};