#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Koopa.h"
#include "Coin.h"
#include "DCoin.h"
#include "QuestionBrick.h"
#include "Mushroom.h"
//#include "Portal.h"

#include "Collision.h"
#include "Spawn.h"
#include "RedKoopas.h"
#include "Brick.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	if (x < 0)
	{
		x = 0;
		y -= vy * dt;
	}
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<DCoin*>(e->obj))
		OnCollisionWithDCoin(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<Koopa*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<QuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<Mushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<RedKoopas*>(e->obj))
		OnCollisionWithRedKoopas(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);

	else if (dynamic_cast<Spawn*>(e->obj))
		OnCollisionWithSpawn(e);

	if (e->ny != 0 && e->obj->IsBlocking())
	{
		if (e->ny < 0 && e->obj->IsBlocking())
		{
			vy = 0;
			isOnPlatform = true;
			return;
		}


		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}

	//else if (dynamic_cast<CPortal*>(e->obj))
	//	OnCollisionWithPortal(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() == WINGGOOMBA_STATE_WALKING)
		{
			goomba->SetState(GOOMBA_STATE_WALKING);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else

			if (goomba->GetState() == GOOMBA_STATE_WALKING)
			{
				goomba->SetState(GOOMBA_STATE_DIE);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	Koopa* koopa = dynamic_cast<Koopa*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (koopa->GetState() == KOOPA_STATE_WALKING)
		{
			koopa->SetState(KOOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			DebugOut(L">>> Mario 1 >>> \n");
		}
		else
			if (koopa->GetState() == KOOPA_STATE_SHELL_RUNNING)
			{
				koopa->SetState(KOOPA_STATE_SHELL);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				DebugOut(L">>> Mario 2 >>> \n");
			}
			else
				if (koopa->GetState() == KOOPA_STATE_SHELL)
				{
					vy = -MARIO_JUMP_DEFLECT_SPEED;
					DebugOut(L">>> Mario 3 >>> \n");
				}
	}
	else // hit by Goomba
	{
		if (e->nx > 0)
		{
			if (koopa->GetState() == KOOPA_STATE_SHELL)
			{
				koopa->SetState(KOOPA_STATE_SHELL_RUNNING, 1);
				DebugOut(L">>> Mario 4 >>> \n");
				return;
			}
		}

		else if (e->nx < 0)
		{
			if (koopa->GetState() == KOOPA_STATE_SHELL)
			{
				koopa->SetState(KOOPA_STATE_SHELL_RUNNING, -1);
				DebugOut(L">>> Mario 5 >>> \n");
				return;
			}
		}

		if (untouchable == 0)
		{
			if (koopa->GetState() == KOOPA_STATE_WALKING || koopa->GetState() == KOOPA_STATE_SHELL_RUNNING)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
					DebugOut(L">>> Mario 6 >>> \n");
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithDCoin(LPCOLLISIONEVENT e)
{
	if (e->ny > 0)
	{
		DCoin* dcoin = dynamic_cast<DCoin*>(e->obj);
		if (dcoin->GetState() == DCOIN_STATE_STATIC)
		{
			dcoin->SetState(DCOIN_STATE_BOUNCE);
			coin++;
		}
	}
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	if (e->ny > 0)
	{
		QuestionBrick* questionBrick = dynamic_cast<QuestionBrick*>(e->obj);
		if (questionBrick->GetState() == QUESTION_BRICK_STATE_STATIC)
		{
			questionBrick->SetState(QUESTION_BRICK_STATE_BOUNCE);
		}
	}
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	if (e->ny > 0)
	{		
		CBrick* brick = dynamic_cast<CBrick*>(e->obj);
		if (brick->Isbreak())
		{
			if (GetLevel() == MARIO_LEVEL_SMALL)
			{
				brick->SetState(BRICK_STATE_BOUNCE);
			}
			else
			{
				brick->SetState(BRICK_STATE_BREAK);				
			}
		}


		if (brick->GetBounceTimes() == 0) return;
		if (brick->GetState() == BRICK_STATE_STATIC)
		{
			brick->SetState(BRICK_STATE_BOUNCE);
		}		
	}
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	Mushroom* mushroom = dynamic_cast<Mushroom*>(e->obj);

	if (mushroom->GetState() == MUSHROOM_STATE_MOVING && level == MARIO_LEVEL_SMALL)
	{
		SetLevel(MARIO_LEVEL_BIG);
		mushroom->Delete();
	}

	if (e->ny > 0) 
	{
		if (level != MARIO_LEVEL_SMALL)
		{
			mushroom->Delete();
		}
		else if (mushroom->GetState() == MUSHROOM_STATE_HIDE)
		{
			mushroom->SetState(MUSHROOM_STATE_BOUNCE);
		}
	}
	
}

void CMario::OnCollisionWithSpawn(LPCOLLISIONEVENT e)
{
	Spawn* spawn = dynamic_cast<Spawn*>(e->obj);

	spawn->CreateEnemies();
	spawn->Delete();
	DebugOut(L">>>Spawn OK>>> \n");
}

void CMario::OnCollisionWithRedKoopas(LPCOLLISIONEVENT e)
{
	RedKoopas* redkoopa = dynamic_cast<RedKoopas*>(e->obj);

	// jump on top >> kill Koopa and deflect a bit 
	if (e->ny < 0)
	{
		if (redkoopa->GetState() == REDKOOPA_STATE_WALKING_LEFT || redkoopa->GetState() == REDKOOPA_STATE_WALKING_RIGHT)
		{
			redkoopa->SetState(REDKOOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			DebugOut(L">>> Mario 1 >>> \n");
		}
		else
			if (redkoopa->GetState() == REDKOOPA_STATE_SHELL_RUNNING)
			{
				redkoopa->SetState(REDKOOPA_STATE_SHELL);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				DebugOut(L">>> Mario 2 >>> \n");
			}
			else
				if (redkoopa->GetState() == REDKOOPA_STATE_SHELL)
				{
					vy = -MARIO_JUMP_DEFLECT_SPEED;
					DebugOut(L">>> Mario 3 >>> \n");
				}
	}
	else // hit by Koopa
	{
		if (e->nx > 0)
		{
			if (redkoopa->GetState() == REDKOOPA_STATE_SHELL)
			{
				redkoopa->SetState(REDKOOPA_STATE_SHELL_RUNNING, 1);
				DebugOut(L">>> Mario 4 >>> \n");
				return;
			}
		}

		else if (e->nx < 0)
		{
			if (redkoopa->GetState() == REDKOOPA_STATE_SHELL)
			{
				redkoopa->SetState(REDKOOPA_STATE_SHELL_RUNNING, -1);
				DebugOut(L">>> Mario 5 >>> \n");
				return;
			}
		}

		if (untouchable == 0)
		{
			if (redkoopa->GetState() == REDKOOPA_STATE_WALKING_LEFT || redkoopa->GetState() == REDKOOPA_STATE_WALKING_RIGHT
				|| redkoopa->GetState() == REDKOOPA_STATE_SHELL_RUNNING)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
					DebugOut(L">>> Mario 6 >>> \n");
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

//void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
//{
//	CPortal* p = (CPortal*)e->obj;
//	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
//}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();

	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}
