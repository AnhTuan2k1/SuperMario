#pragma once
#include "GameObject.h"


#define LEAF_GRAVITY 0.000015f
#define LEAF_SPEED 0.1f
#define LEAF_SPEED_BOUNCE 0.3f
#define LEAF_HEIGHT_BOUNCE 30
#define LEAF_MOVEMENT_SCOPE 30


#define LEAF_BBOX_WIDTH 15
#define LEAF_BBOX_HEIGHT 13

#define LEAF_STATE_MOVING 153
#define LEAF_STATE_HIDE 174
#define LEAF_STATE_BOUNCE 752

#define ID_SPRITE_LEAF 114000

class Leaf : public CGameObject
{
protected:
	
	float ay;
	float y_initial;
	float x_initial;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable()
	{
		if (state == LEAF_STATE_HIDE) return true;
		return false;
	};
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	//void OnCollisionWithMario(LPCOLLISIONEVENT e);

public:
	Leaf(float x, float y);
	virtual void SetState(int state);
};

