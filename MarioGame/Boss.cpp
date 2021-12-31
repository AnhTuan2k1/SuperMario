#include "Boss.h"
#include "Mario.h"
#include "Portal.h"

void Boss::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == BOSS_STATE_DIE) return;
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		if (e->ny < 0 && e->obj->IsBlocking())
		{
			vy = 0;
			isOnPlatform = true;
		}
		vy = 0;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = -vx;
	}

	/*if (dynamic_cast<CMario*>(e->obj))
	{
		CMario* mario = dynamic_cast<CMario*>(e->obj);

		if (e->nx != 0)
		{
			if (mario->getUntouchable() == 1) return;
			mario->StartUntouchable();
			mario->SetLevel(mario->GetLevel() - 1);
		}
		else if (e->ny > 0)
		{	
			if (state != BOSS_STATE_SHELL_IDLE)
			{
				SetState(BOSS_STATE_SHELL_IDLE);
				mario->MarioJumpDeflect();
				life--;
			}

			if (life <= 0)
			{
				SetState(BOSS_STATE_DIE);
			}
		}
	}*/
}

void Boss::OnNoCollision(DWORD dt)
{
	y += vy * dt;
	x += vx * dt;
}

void Boss::Render()
{
	int aniId = ID_ANI_BOSS_WALK;
	if (state == BOSS_STATE_SHELL)
	{
		if (!isOnPlatform)
		{
			aniId = ID_ANI_BOSS_JUMP;
		}
		else
			aniId = ID_ANI_BOSS_SHELL;
	}
	else if (state == BOSS_STATE_SHELL_IDLE)
	{
		aniId = ID_ANI_STATE_SHELL_IDLE;
	}
	else if (state == BOSS_STATE_DIE)
	{
		aniId = ID_ANI_BOSS_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	float angrySpeed = 0;
	if (life < 3) angrySpeed = BOSS_SPEED_ANGRY;

	float playerX = GetPlayerX();

	if (x > playerX + BOSS_SCOPE_AT_MARIO && playerX > BOSS_LIMITED_MOVEMENT_X)
	{
		if (state == BOSS_STATE_WALK)
			vx = -BOSS_SPEED_WALK - angrySpeed;
		else if (state == BOSS_STATE_SHELL)
			vx = -BOSS_SPEED_SHELL - angrySpeed;
		else if (state == BOSS_STATE_SHELL_IDLE|| state == BOSS_STATE_DIE)
			vx = 0;
	}
	else if (x < playerX - BOSS_SCOPE_AT_MARIO || playerX < BOSS_LIMITED_MOVEMENT_X)
	{
		if (state == BOSS_STATE_WALK)
			vx = BOSS_SPEED_WALK + angrySpeed;
		else if (state == BOSS_STATE_SHELL)
			vx = BOSS_SPEED_SHELL + angrySpeed;
		else if (state == BOSS_STATE_SHELL_IDLE || state == BOSS_STATE_DIE)
			vx = 0;
	}


	if (state == BOSS_STATE_SHELL_IDLE && GetTickCount64() - hitted_start > BONEKOOPA_HITED_TIMEOUT)
	{
		hitted_start = -1;

		if (switchwalk) SetState(BOSS_STATE_WALK);
		else SetState(BOSS_STATE_SHELL);

		y -= (BOSS_HEIGHT - BOSS_HEIGHT_SHELL) / 2 + 1;
	}

	if (state == BOSS_STATE_SHELL ) 
	{
		if (GetTickCount64() - shell_start > BONEKOOPA_SHELL_TIMEOUT)
		{
			shell_start = -1;
			SetState(BOSS_STATE_WALK);
			y -= (BOSS_HEIGHT - BOSS_HEIGHT_SHELL) / 2 + 1;
		}

		if (!jumped)
			if (GetTickCount64() - shell_start > BONEKOOPA_SHELL_TIMEOUT - 3000)
			{
				vy = -BOSS_SPEED_JUMP;
				jumped = true;
			}
	}

	if (state == BOSS_STATE_WALK && GetTickCount64() - walk_start > BONEKOOPA_WALK_TIMEOUT)
	{
		walk_start = -1;
		SetState(BOSS_STATE_SHELL);
		y += (BOSS_HEIGHT - BOSS_HEIGHT_SHELL) / 2;
	}

	isOnPlatform = false;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Boss::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == BOSS_STATE_SHELL || state == BOSS_STATE_SHELL_IDLE)
	{
		l = x - BOSS_WIDTH_SHELL / 2;
		t = y - BOSS_HEIGHT_SHELL / 2;
		r = l + BOSS_WIDTH_SHELL;
		b = t + BOSS_HEIGHT_SHELL;
	}
	else if (state == BOSS_STATE_JUMP)
	{
		l = x - BOSS_WIDTH_JUMP / 2;
		t = y - BOSS_HEIGHT_JUMP / 2;
		r = l + BOSS_WIDTH_JUMP;
		b = t + BOSS_HEIGHT_JUMP;
	}
	else if (state == BOSS_STATE_DIE)
	{
		l = x - BOSS_WIDTH / 2;
		t = y - BOSS_HEIGHT_DIE / 2;
		r = l + BOSS_WIDTH;
		b = t + BOSS_HEIGHT_DIE;
	}
	else
	{
		l = x - BOSS_WIDTH / 2;
		t = y - BOSS_HEIGHT / 2;
		r = l + BOSS_WIDTH;
		b = t + BOSS_HEIGHT;
	}
}

void Boss::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOSS_STATE_WALK:
		walk_start = GetTickCount64();
		break;

	case BOSS_STATE_SHELL:
		shell_start = GetTickCount64();
		jumped = false;
		break;

	case BOSS_STATE_JUMP:

		break;

	case BOSS_STATE_SHELL_IDLE:
		hitted_start = GetTickCount64();
		switchwalk = !switchwalk;
		break;

	case BOSS_STATE_DIE:
		vx = 0;
		//y += (BOSS_HEIGHT - BOSS_HEIGHT_DIE) / 2 - 1;
		CGame::GetInstance()->GetCurrentScene()->AddObject(new CPortal(x, y - 30, 15, 15, 3, true));
		break;
	}
}


float Boss::GetPlayerX()
{
	float xx = 0, yy;
	for (int i = 0; i < CGame::GetInstance()->GetCurrentScene()->NumberObject(); i++)
	{
		if (dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->getObject(i)))
		{
			CMario* mario = dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->getObject(i));
			mario->GetPosition(xx, yy);
		}
	}
	return xx;
}