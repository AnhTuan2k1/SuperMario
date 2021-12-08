#pragma once
#include "GameObject.h"


#define TAIL_BBOX_WIDTH 8
#define TAIL_BBOX_HEIGHT 8

#define TAIL_HIT_BBOX_WIDTH 9
#define TAIL_HIT_BBOX_HEIGHT 5

#define TAIL_STATE_DECORATE 284
#define TAIL_STATE_HIT 289
#define TAIL_DIE_TIMEOUT 1200

#define ID_ANI_TAIL_IDLE_RIGHT 2400
#define ID_ANI_TAIL_IDLE_LEFT 2401

#define ID_ANI_TAIL_WALKING_RIGHT 2500
#define ID_ANI_TAIL_WALKING_LEFT 2501

#define ID_ANI_TAIL_RUNNING_RIGHT 2600
#define ID_ANI_TAIL_RUNNING_LEFT 2601

#define ID_ANI_TAIL_JUMP_WALK_RIGHT 2700
#define ID_ANI_TAIL_JUMP_WALK_LEFT 2701

#define ID_ANI_TAIL_JUMP_RUN_RIGHT 2800
#define ID_ANI_TAIL_JUMP_RUN_LEFT 2801

#define ID_ANI_TAIL_SIT_RIGHT 2900
#define ID_ANI_TAIL_SIT_LEFT 2901

#define ID_ANI_TAIL_BRACE_RIGHT 3000
#define ID_ANI_TAIL_BRACE_LEFT 3001

class Tail : public CGameObject
{
protected:

	ULONGLONG hit_start;
	int aniID;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable()
	{
		return (state == TAIL_STATE_HIT);
	};
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);	

public:
	Tail(float x, float y) : CGameObject(x, y) 
	{ 
		SetState(TAIL_STATE_DECORATE); 
		aniID = ID_ANI_TAIL_IDLE_RIGHT;
	}

	void SetAniId(int marioRaccoonAniID);
	void SetPosition(float xMario, float yMario);
	virtual void SetState(int state);
	void RenderBoundingBox();
};

