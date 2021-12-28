#pragma once
#include "GameObject.h"

#define BONEKOOPA_GRAVITY 0.002f
#define BONEKOOPA_WALKING_SPEED 0.03f

#define BONEKOOPA_BBOX_WIDTH 13
#define BONEKOOPA_BBOX_HEIGHT 24

#define BONEKOOPA_DIE_BBOX_WIDTH 21
#define BONEKOOPA_DIE_BBOX_HEIGHT 13


#define BONEKOOPA_DIE_TIMEOUT 4000

#define BONEKOOPA_STATE_WALKING 764
#define BONEKOOPA_STATE_DIE 765

#define ID_ANI_BONEKOOPA_WALKING_RIGHT 151002
#define ID_ANI_BONEKOOPA_WALKING_LEFT 151001
#define ID_ANI_BONEKOOPA_DIE_RIGHT 151004
#define ID_ANI_BONEKOOPA_DIE_LEFT 151003



class BoneKoopas : public CGameObject
{
	float ay;

	ULONGLONG die_start;
	bool iswalkingright;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	BoneKoopas(float x, float y) : CGameObject(x, y)
	{
		this->ay = BONEKOOPA_GRAVITY;
		die_start = -1;
		iswalkingright = false;
		SetState(BONEKOOPA_STATE_WALKING);
	}
	virtual void SetState(int state);
};

