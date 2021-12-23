#pragma once
#include "GameObject.h"


#define TAIL_BBOX_WIDTH 15
#define TAIL_BBOX_HEIGHT 2

#define TAIL_HIT_BBOX_WIDTH 9
#define TAIL_HIT_BBOX_HEIGHT 5

#define TAIL_SPEED 0.08f

#define TAIL_STATE_DECORATE 284
#define TAIL_STATE_RIGHT 289
#define TAIL_DIE_TIMEOUT 300

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

#define ID_ANI_TAIL_INVISIBLE 3000
#define ID_ANI_TAIL_BRACE_LEFT 3001

#define SCOPE_TAIL_HIT 30

class Tail : public CGameObject
{
protected:

	ULONGLONG hit_start;
	//int aniID;
	float xMario;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithDCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithRedKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithPbutton(LPCOLLISIONEVENT e);


	//GetBoundingBox Raccoon Mario. 
	virtual int IsCollidable()
	{
		return true;
	};
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);	
public:
	//void SetAniId(int marioRaccoonAniID);
	//void SetPosition(float xMario, float yMario);
	//virtual void SetState(int state);
	//void SetSpeed(float VxMario, float VyMario);
	//void SetXmario(const float xMario);

	Tail(float x, float y) : CGameObject(x, y)
	{
		//SetState(TAIL_STATE_RIGHT);
		////aniID = ID_ANI_TAIL_INVISIBLE;
		////vx = TAIL_SPEED;
		xMario = x;
		x = xMario + 7;
		vy = 0;
		vx = TAIL_SPEED;
		hit_start = GetTickCount64();
	}
};

