#pragma once
#include "GameObject.h"

#define BOSS_GRAVITY 0.002f
#define BOSS_SPEED_WALK 0.09f
#define BOSS_SPEED_SHELL 0.07f
#define BOSS_SPEED_JUMP 0.4f
#define BOSS_SPEED_ANGRY 0.03f

#define BOSS_SCOPE_AT_MARIO 40
#define BOSS_LIMITED_MOVEMENT_X 2300

#define BONEKOOPA_WALK_TIMEOUT 4000
#define BONEKOOPA_SHELL_TIMEOUT 4000
#define BONEKOOPA_HITED_TIMEOUT 2000

#define ID_ANI_BOSS_WALK 141001
#define ID_ANI_BOSS_JUMP 141003
#define ID_ANI_BOSS_SHELL 141002
#define ID_ANI_BOSS_DIE 141004
#define ID_ANI_STATE_SHELL_IDLE 141005

#define BOSS_WIDTH 27
#define BOSS_HEIGHT 25
#define BOSS_WIDTH_JUMP 25
#define BOSS_HEIGHT_JUMP 25
#define BOSS_WIDTH_SHELL 25
#define BOSS_HEIGHT_SHELL 20
#define BOSS_HEIGHT_DIE 15

#define BOSS_STATE_WALK 78678
#define BOSS_STATE_SHELL 78679
#define BOSS_STATE_JUMP 78670
#define BOSS_STATE_SHELL_IDLE 78671
#define BOSS_STATE_DIE 78672

#define BOSS_LIFE 4

class Boss : public  CGameObject
{
	float ay;
	int life;
	bool jumped;
	ULONGLONG hitted_start;
	ULONGLONG walk_start;
	ULONGLONG shell_start;
	bool switchwalk;
	bool isOnPlatform;
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnNoCollision(DWORD dt);

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	float GetPlayerX();
public:
	virtual void SetState(int state);
	Boss(float x, float y) : CGameObject(x, y)
	{
		life = BOSS_LIFE;
		ay = BOSS_GRAVITY;
		hitted_start = -1;
		walk_start = -1;
		shell_start = -1;
		SetState(BOSS_STATE_SHELL);
	}
	void DecreaseLife() { life--; }
	int GetLife() { return life; }
};

