#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"
#include "Tail.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_FLY_START_SPEED_Y	0.4f
#define MARIO_FLY_SPEED_Y		0.3f
#define MARIO_FLY_JUMP_DEFLECT_SPEED_Y	0.2f

#define MARIO_GRAVITY			0.002f
#define MARIO_GRAVITY_SLOWDOWN	0.001f
#define MARIO_SPEED_SLOWDOWN	0.05f
#define MARIO_GRAVITY_FLY		0.0004f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_HIT	700

#define MARIO_STATE_HOLD_RIGHT	800
#define MARIO_STATE_HOLD_LEFT	801

#define MARIO_STATE_HOLD_WALKING_RIGHT	802
#define MARIO_STATE_HOLD_WALKING_LEFT	803

#define MARIO_STATE_FLY	900


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_HOLD_RIGHT 1002
#define ID_ANI_MARIO_HOLD_LEFT 1003
#define ID_ANI_MARIO_HOLD_WALK_RIGHT 1004
#define ID_ANI_MARIO_HOLD_WALK_LEFT 1005

#define ID_ANI_MARIO_DIE 999

//RACCOON MARIO
#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT 1700
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT 1701

#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT 1800
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT 1801

#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT 1900
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT 1901

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT 2000
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT 2001

#define ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT 2100
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT 2101

#define ID_ANI_MARIO_RACCOON_SIT_RIGHT 2200
#define ID_ANI_MARIO_RACCOON_SIT_LEFT 2201

#define ID_ANI_MARIO_RACCOON_BRACE_RIGHT 2300
#define ID_ANI_MARIO_RACCOON_BRACE_LEFT 2301

#define ID_ANI_MARIO_RACCOON_BRACE_RIGHT 2300
#define ID_ANI_MARIO_RACCOON_BRACE_LEFT 2301

#define ID_ANI_MARIO_RACCOON_FALL_RIGHT 3100
#define ID_ANI_MARIO_RACCOON_FALL_LEFT 3101

#define ID_ANI_MARIO_RACCOON_HOLD_RIGHT 3200
#define ID_ANI_MARIO_RACCOON_HOLD_LEFT 3201
#define ID_ANI_MARIO_RACCOON_HOLD_WALK_RIGHT 3300
#define ID_ANI_MARIO_RACCOON_HOLD_WALK_LEFT 3301

#define ID_ANI_MARIO_RACCOON_FLY_UP_RIGHT 3400
#define ID_ANI_MARIO_RACCOON_FLY_UP_LEFT 3401
#define ID_ANI_MARIO_RACCOON_FLY_DOWN_RIGHT 3402
#define ID_ANI_MARIO_RACCOON_FLY_DOWN_LEFT 3403

#define ID_ANI_MARIO_RACCOON_HIT_RIGHT 3500
#define ID_ANI_MARIO_RACCOON_HIT_LEFT 3501

#define ID_ANI_MARIO_RACCOON_FLY_SLOWDOWN_RIGHT 3502
#define ID_ANI_MARIO_RACCOON_FLY_SLOWDOWN_LEFT 3503


// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_HOLD_RIGHT 1602
#define ID_ANI_MARIO_SMALL_HOLD_LEFT 1603
#define ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT 1604
#define ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT 1605

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACCOON		3

#define MARIO_BIG_BBOX_WIDTH  13
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_BIG_RACCOON_BBOX_WIDTH  21
#define MARIO_BIG_RACCOON_BBOX_HEIGHT 27
#define MARIO_BIG_RACCOON_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_RACCOON_SITTING_BBOX_HEIGHT 16
#define MARIO_BIG_RACCOON_TAIL_BBOX_WIDTH  8

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)
#define MARIO_RACCOON_SIT_HEIGHT_ADJUST ((MARIO_BIG_RACCOON_BBOX_HEIGHT-MARIO_BIG_RACCOON_SITTING_BBOX_HEIGHT)/2 + 1)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_HIT_TIME 302
#define MARIO_SHOWDOWN_TIME 700
#define MARIO_SHOWDOWN_TIME_SPRITE 700
#define MARIO_POWER_TIME 200
#define MARIO_FLY_TIME 5000

#define MARIO_POWER_MAX 6

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	bool isSlowdown;
	bool isLoadingPower;
	bool isFlying;
	ULONGLONG slowdown_start;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int power;
	int level;
	int untouchable;
	ULONGLONG power_start;
	ULONGLONG fly_start;
	ULONGLONG untouchable_start;
	bool statehit;
	ULONGLONG hit_start;
	BOOLEAN isOnPlatform;
	int coin; 
	//float nxspriteposition;
	//Tail* tail;
	//int position;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithDCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithSpawn(LPCOLLISIONEVENT e);
	void OnCollisionWithRedKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccoon();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		isSlowdown = false;
		isLoadingPower = false;
		isFlying = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		power = 0;
		level = 1;
		untouchable = 0;
		untouchable_start = -1;
		slowdown_start = -1;
		power_start = -1;
		fly_start = -1;
		statehit = false;
		hit_start = -1;
		isOnPlatform = false;
		coin = 0;
		//nxspriteposition = 1;
		//tail = NULL;
		//position = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return 0/*(state != MARIO_STATE_DIE && untouchable==0)*/; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel() { return level; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartHit();
	void StartSlowdown();
	void StartLoadPower();
	void EndLoadPower();
	void EndFly();
	//void AddTail();
	void IncreaseCoin() { coin++; }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void GetBoundingBoxRaccoon(float& left, float& top, float& right, float& bottom);
};