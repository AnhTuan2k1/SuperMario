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
#include "Portal.h"

#include "Collision.h"
#include "Spawn.h"
#include "RedKoopas.h"
#include "Brick.h"
#include "Leaf.h"
#include "Pbutton.h"

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
	if(isHitting)
	if (GetTickCount64() - hit_start > MARIO_HIT_TIME && isHitting)
	{
		hit_start = 0;
		isHitting = false;
		if (vx == 0)
		{
			if (nx > 0) SetState(ID_ANI_MARIO_RACCOON_IDLE_RIGHT);
			else SetState(ID_ANI_MARIO_RACCOON_IDLE_LEFT);
		}
		DebugOut(L">>>end hit>>> \n");
	}

	if (isSlowdown)
	{

		if ((GetTickCount64() - slowdown_start > MARIO_SHOWDOWN_TIME) || isOnPlatform)
		{
			slowdown_start = 0;
			isSlowdown = false;
			ay = MARIO_GRAVITY;
			DebugOut(L">>>end slowdown>>> \n");
		}
		else vy = MARIO_SPEED_SLOWDOWN;
	}

	if (isLoadingPower)
	{
		if (!isOnPlatform) EndLoadPower();

		else if (GetTickCount64() - power_start > MARIO_POWER_TIME)
		{
			power_start = GetTickCount64();
			if (power < MARIO_POWER_MAX) power++;

			if (power == MARIO_POWER_MAX)
				DebugOut(L">>>power max>>> \n");
		}

	}

	if (isFlying)
	{
		if (GetTickCount64() - fly_start > MARIO_FLY_TIME)
		{
			EndFly();
		}
	}

	if (isHolding)
	{
		if (GetTickCount64() - holding_start > holdingTimeMax)
		{
			EndHoldingShell();
		}
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
	else if (dynamic_cast<Spawn*>(e->obj))
		OnCollisionWithSpawn(e);
	else if (dynamic_cast<Leaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<Pbutton*>(e->obj))
		OnCollisionWithPbutton(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);

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

			if (isFlying) vy = -MARIO_FLY_JUMP_DEFLECT_SPEED_Y;
			else vy = -MARIO_JUMP_DEFLECT_SPEED;
			
		}
		else

			if (goomba->GetState() == GOOMBA_STATE_WALKING)
			{
				goomba->SetState(GOOMBA_STATE_DIE);
				if (isFlying) vy = -MARIO_FLY_JUMP_DEFLECT_SPEED_Y;
				else vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level == MARIO_LEVEL_RACCOON)
				{
					SetLevel(MARIO_LEVEL_BIG);
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					SetLevel(MARIO_LEVEL_SMALL);
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
			if (isFlying) vy = -MARIO_FLY_JUMP_DEFLECT_SPEED_Y;
			else vy = -MARIO_JUMP_DEFLECT_SPEED;
			//DebugOut(L">>> Mario 1 >>> \n");
		}
		else
			if (koopa->GetState() == KOOPA_STATE_SHELL_RUNNING)
			{
				koopa->SetState(KOOPA_STATE_SHELL);
				if (isFlying) vy = -MARIO_FLY_JUMP_DEFLECT_SPEED_Y;
				else vy = -MARIO_JUMP_DEFLECT_SPEED;
				//DebugOut(L">>> Mario 2 >>> \n");
			}
			else
				if (koopa->GetState() == KOOPA_STATE_SHELL)
				{
					if (isFlying) vy = -MARIO_FLY_JUMP_DEFLECT_SPEED_Y;
					else vy = -MARIO_JUMP_DEFLECT_SPEED;

					koopa->SetState(KOOPA_STATE_SHELL);
					//DebugOut(L">>> Mario 3 >>> \n");
				}
	}
	else // hit by Goomba
	{
		if (e->nx > 0)
		{
			if (koopa->GetState() == KOOPA_STATE_SHELL)
			{
				koopa->SetState(KOOPA_STATE_SHELL_RUNNING, 1);
				//DebugOut(L">>> Mario 4 >>> \n");
				return;
			}
		}

		else if (e->nx < 0)
		{
			if (koopa->GetState() == KOOPA_STATE_SHELL)
			{
				koopa->SetState(KOOPA_STATE_SHELL_RUNNING, -1);
				//DebugOut(L">>> Mario 5 >>> \n");
				return;
			}
		}

		if (untouchable == 0)
		{
			if (koopa->GetState() == KOOPA_STATE_WALKING || koopa->GetState() == KOOPA_STATE_SHELL_RUNNING)
			{
				if (level == MARIO_LEVEL_RACCOON)
				{
					SetLevel(MARIO_LEVEL_BIG);
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					SetLevel(MARIO_LEVEL_SMALL);
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

		if (mushroom->GetState() == MUSHROOM_STATE_HIDE)
		{
			if (level == MARIO_LEVEL_SMALL)
				mushroom->SetState(MUSHROOM_STATE_BOUNCE);
			else
			{
				mushroom->Delete();
				float xx, yy;
				mushroom->GetPosition(xx,yy);
				CGame::GetInstance()->GetCurrentScene()->AddObject(new Leaf(xx, yy));
			}
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
			if (isFlying) vy = -MARIO_FLY_JUMP_DEFLECT_SPEED_Y;
			else vy = -MARIO_JUMP_DEFLECT_SPEED;
			DebugOut(L">>> Mario 1 >>> \n");
		}
		else
			if (redkoopa->GetState() == REDKOOPA_STATE_SHELL_RUNNING)
			{
				redkoopa->SetState(REDKOOPA_STATE_SHELL);
				if (isFlying) vy = -MARIO_FLY_JUMP_DEFLECT_SPEED_Y;
				else vy = -MARIO_JUMP_DEFLECT_SPEED;
				DebugOut(L">>> Mario 2 >>> \n");
			}
			else
				if (redkoopa->GetState() == REDKOOPA_STATE_SHELL)
				{
					if (isFlying) vy = -MARIO_FLY_JUMP_DEFLECT_SPEED_Y;
					else vy = -MARIO_JUMP_DEFLECT_SPEED;

					redkoopa->SetState(REDKOOPA_STATE_SHELL);
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
				if (level == MARIO_LEVEL_RACCOON)
				{
					SetLevel(MARIO_LEVEL_BIG);
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					SetLevel(MARIO_LEVEL_SMALL);
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

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	Leaf* leaf = dynamic_cast<Leaf*>(e->obj);

	if (level < MARIO_LEVEL_RACCOON)
	{
		SetLevel(level + 1);
	}

	leaf->Delete();
}

void CMario::OnCollisionWithPbutton(LPCOLLISIONEVENT e)
{
	Pbutton* pbutton = dynamic_cast<Pbutton*>(e->obj);

	if (e->ny > 0)
	{
		if (pbutton->GetState() == PBUTTON_STATE_BRICK)
		{
			pbutton->SetState(PBUTTON_STATE_BOUNCED);
		}
	}
	else if (e->ny < 0)
	{
		if (pbutton->GetState() == PBUTTON_STATE_BOUNCED)
		{
			pbutton->SetState(BRICK_STATE_ACTIVED);
		}
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	ExitHiddenZone();
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (isHolding)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_SMALL_HOLD_RIGHT;
			else aniId = ID_ANI_MARIO_SMALL_HOLD_LEFT;
		}

		else if (abs(ax) == MARIO_ACCEL_RUN_X)
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
				if (isHolding)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_HOLD_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_HOLD_LEFT;
				}

				else if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)					
				{
					if (isHolding)
					{
						aniId = ID_ANI_MARIO_SMALL_HOLD_RUNNING_RIGHT;
					}
					else aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				}
				else if (ax == MARIO_ACCEL_WALK_X)
				{
					if (isHolding)
					{
						aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT;
					}
					else aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				}				
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
				{
					if (isHolding)
					{
						aniId = ID_ANI_MARIO_SMALL_HOLD_RUNNING_LEFT;
					}
					else aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				}				
				else if (ax == -MARIO_ACCEL_WALK_X)
				{
					if (isHolding)
					{
						aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT;
					}
					else aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}
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
		if (isHolding)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_HOLD_RIGHT;
			else aniId = ID_ANI_MARIO_HOLD_LEFT;
		}

		else if (abs(ax) == MARIO_ACCEL_RUN_X)
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
				if (isHolding)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_HOLD_RIGHT;
					else aniId = ID_ANI_MARIO_HOLD_LEFT;
				}

				else if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
				{
					if (isHolding)
					{
						aniId = ID_ANI_MARIO_HOLD_RUNNING_RIGHT;
					}
					else aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				}
					
				else if (ax == MARIO_ACCEL_WALK_X)
				{
					if (isHolding)
					{
						aniId = ID_ANI_MARIO_HOLD_WALK_RIGHT;
					}
					else aniId = ID_ANI_MARIO_WALKING_RIGHT;
				}
					
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
				{
					if (isHolding)
					{
						aniId = ID_ANI_MARIO_HOLD_RUNNING_LEFT;
					}
					else aniId = ID_ANI_MARIO_RUNNING_LEFT;
				}
				else if (ax == -MARIO_ACCEL_WALK_X)
				{
					if (isHolding)
					{
						aniId = ID_ANI_MARIO_HOLD_WALK_LEFT;
					}
					else aniId = ID_ANI_MARIO_WALKING_LEFT;
				}
					
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

/// <summary>
/// Get animdation ID for Raccoon Mario
/// </summary>
/// <returns></returns>
int CMario::GetAniIdRaccoon()
{
	int aniId = -1;

	if (!isOnPlatform)
	{
		if (isHitting)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_HIT_RIGHT;
			else aniId = ID_ANI_MARIO_RACCOON_HIT_LEFT;
		}
		else if (isFlying)
		{
			if (nx > 0)
			{
				if (vy < 0) aniId = ID_ANI_MARIO_RACCOON_FLY_UP_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_FLY_DOWN_RIGHT;

			}
			else
			{
				if (vy < 0) aniId = ID_ANI_MARIO_RACCOON_FLY_UP_LEFT;
				else aniId = ID_ANI_MARIO_RACCOON_FLY_DOWN_LEFT;
			}
		}
		else if (isSlowdown)
		{
			if (GetTickCount64() - slowdown_start < MARIO_SHOWDOWN_TIME_SPRITE)
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_FLY_SLOWDOWN_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_FLY_SLOWDOWN_LEFT;
		}

		else if (isHolding)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_HOLD_RIGHT;
			else aniId = ID_ANI_MARIO_RACCOON_HOLD_LEFT;
		}

		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
			{
				if (vy > 0)
					aniId = ID_ANI_MARIO_RACCOON_FALL_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
			}
			else
			{
				if (vy > 0)
					aniId = ID_ANI_MARIO_RACCOON_FALL_LEFT;
				else
					aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (isHitting)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_HIT_RIGHT;
					else aniId = ID_ANI_MARIO_RACCOON_HIT_LEFT;
				}

				else if (isHolding)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_HOLD_RIGHT;
					else aniId = ID_ANI_MARIO_RACCOON_HOLD_LEFT;
				}

				else if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
				{
					if (isHitting)
					{
						if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_HIT_RIGHT;
						else aniId = ID_ANI_MARIO_RACCOON_HIT_LEFT;
					}

					else if (isHolding)
					{
						aniId = ID_ANI_MARIO_RACCOON_HOLD_RUN_RIGHT;
					}

					else aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
				}				
				else if (ax == MARIO_ACCEL_WALK_X)
				{
					if (isHitting)
						aniId = ID_ANI_MARIO_RACCOON_HIT_RIGHT;
					else if (isHolding)
					{
						aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_RIGHT;
					}
					else aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
				}
					
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
				{
					if (isHitting)
					{
						if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_HIT_RIGHT;
						else aniId = ID_ANI_MARIO_RACCOON_HIT_LEFT;
					}
					else if (isHolding)
					{
						aniId = ID_ANI_MARIO_RACCOON_HOLD_RUN_LEFT;
					}

					else aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				}				
				else if (ax == -MARIO_ACCEL_WALK_X)
				{
					if (isHitting)
						aniId = ID_ANI_MARIO_RACCOON_HIT_LEFT;
					else if (isHolding)
					{
						aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_LEFT;
					}
					else aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
				}
					
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;

	//tail->SetAniId(aniId);
	//tail->SetPosition(x, y);
	//tail->SetSpeed(vy, vx);
	//tail->SetXmario(x);
	//AddTail();
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
	else if (level == MARIO_LEVEL_RACCOON)
	{
		aniId = GetAniIdRaccoon();
		if (isFlying)
		{
			if (aniId == ID_ANI_MARIO_RACCOON_IDLE_RIGHT || aniId == ID_ANI_MARIO_RACCOON_IDLE_LEFT
				|| aniId == ID_ANI_MARIO_RACCOON_WALKING_RIGHT || aniId == ID_ANI_MARIO_RACCOON_WALKING_LEFT
				|| aniId == ID_ANI_MARIO_RACCOON_HOLD_RIGHT || aniId == ID_ANI_MARIO_RACCOON_HOLD_LEFT
				|| aniId == ID_ANI_MARIO_HOLD_RIGHT || aniId == ID_ANI_MARIO_HOLD_LEFT
				|| aniId == ID_ANI_MARIO_SMALL_HOLD_RIGHT || aniId == ID_ANI_MARIO_SMALL_HOLD_LEFT)
			{
				ay = MARIO_GRAVITY;
			}

		}
	}
		

	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();

	DebugOutTitle(L"Coins: %d", coin);
	//for (int i = 0; i < CGame::GetInstance()->GetCurrentScene()->NumberObject(); i++)
	//{
	//	if (dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->getObject(i)))
	//	{
	//		position = i;
	//	}
	//}
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
		if (isOnPlatform && !isFlying)
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
			if (level == MARIO_LEVEL_RACCOON)
				y += MARIO_RACCOON_SIT_HEIGHT_ADJUST;
			else
				y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			if (level == MARIO_LEVEL_RACCOON)
				y -= MARIO_RACCOON_SIT_HEIGHT_ADJUST;
			else
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

	case MARIO_STATE_HIT:
		StartHit();
		break;

	case MARIO_STATE_FLY:
		if (isFlying)
		{
			vy = -MARIO_FLY_SPEED_Y;
			isFlying = true;
			ay = MARIO_GRAVITY_FLY;
			DebugOut(L">>>mario fly>>> \n");
		}
		else if(power == MARIO_POWER_MAX)
		{
			vy -= MARIO_FLY_START_SPEED_Y;
			fly_start = GetTickCount64();
			isFlying = true;
			ay = MARIO_GRAVITY_FLY;
			EndLoadPower();

			DebugOut(L">>>start fly>>> \n");
		}
		
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
	else if (level == MARIO_LEVEL_RACCOON)
	{
		int l;
		int r;

		if (nx > 0)
		{
			l = MARIO_BIG_RACCOON_TAIL_BBOX_WIDTH;
			r = 0;			
		}
		else
		{
			l = 0;
			r = MARIO_BIG_RACCOON_TAIL_BBOX_WIDTH;
		}

		//if (nx * nxspriteposition < 0)
		//{
		//	nxspriteposition = nx;

		//	if (r == 0) // left to right
		//	{
		//		x -= MARIO_BIG_RACCOON_TAIL_BBOX_WIDTH;
		//		CGame::GetInstance()->SetCamPos(x + MARIO_BIG_RACCOON_TAIL_BBOX_WIDTH, 0.0f);
		//	}
		//	else
		//	{
		//		x += MARIO_BIG_RACCOON_TAIL_BBOX_WIDTH;
		//		CGame::GetInstance()->SetCamPos(x - MARIO_BIG_RACCOON_TAIL_BBOX_WIDTH, 0.0f);
		//	}
		//}

		if (isSitting)
		{
			left = x - MARIO_BIG_RACCOON_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_RACCOON_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_RACCOON_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_RACCOON_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_RACCOON_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_RACCOON_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_RACCOON_BBOX_WIDTH ;
			bottom = top + MARIO_BIG_RACCOON_BBOX_HEIGHT;
			left += l;
			right -= r;
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

void CMario::GetBoundingBoxRaccoon(float& left, float& top, float& right, float& bottom)
{

}

void CMario::SetPlayer(CMario*& mario)
{
	for (int i = 0; i < CGame::GetInstance()->GetCurrentScene()->NumberObject(); i++)
	{
		if (dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->getObject(i)))
		{
			mario = dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->getObject(i));
		}
	}
}


void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		if (l == MARIO_LEVEL_RACCOON)
		{
			y -= (MARIO_BIG_RACCOON_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2 + 1;
		}
		else
			y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	else if (this->level == MARIO_LEVEL_BIG && l == MARIO_LEVEL_RACCOON)
	{
		y -= (MARIO_BIG_RACCOON_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT) / 2 + 1;
	}

	if (l < 3 && isFlying)
	{
		EndFly();
	}

	if (l < 1)
	{
		SetState(MARIO_STATE_DIE);
	}
	level = l;
}

void CMario::StartHit()
{
	isHitting = true;
	hit_start = GetTickCount64(); 
	CGame::GetInstance()->GetCurrentScene()->AddObject(new Tail(x, y + 7));
	DebugOut(L">>>start hit>>> \n");
}

void CMario::StartSlowdown()
{
	if (isOnPlatform || level != MARIO_LEVEL_RACCOON || isFlying) return;

	isSlowdown = true;
	slowdown_start = GetTickCount64();
	//ay = MARIO_GRAVITY_SLOWDOWN;
	DebugOut(L">>>start slowdown>>> \n");
}

void CMario::StartLoadPower()
{
	if (isLoadingPower) return;

	if (isOnPlatform && level == MARIO_LEVEL_RACCOON)
	{
		isLoadingPower = true;
		power_start = GetTickCount64();
		DebugOut(L">>>start power>>> \n");
	}

}

void CMario::StartHoldingShell()
{
	GetShell();
}

void CMario::DropShell()
{
	Koopa* koopas = new Koopa(x, y);
	koopas->SetState(KOOPA_STATE_SHELL);
	koopas->SetPosition(x + MARIO_BIG_BBOX_WIDTH / 2, y + MARIO_SMALL_BBOX_HEIGHT / 2);

	ULONGLONG droptime = GetTickCount64();
	koopas->SetHideStart(GetTickCount64() - (KOOPA_SHELL_TIMEOUT - holdingTimeMax + GetTickCount64() - holding_start));

	if (nx > 0)
		koopas->SetSpeed(vx + MARIO_DROP_SHELL_SPEED_X, vy - MARIO_DROP_SHELL_SPEED_Y);
	else koopas->SetSpeed(vx - MARIO_DROP_SHELL_SPEED_X, vy - MARIO_DROP_SHELL_SPEED_Y);

	koopas->SetIsDropping(true);
	koopas->SetDroppedstart(GetTickCount64());
	CGame::GetInstance()->GetCurrentScene()->AddObject(koopas);

	isHolding = false;
	holdingTimeMax = 0;
	holding_start = -1;
	DebugOut(L">>>drop shell>>> \n");
}

void CMario::EndHoldingShell()
{
	isHolding = false;
	holdingTimeMax = 0;
	holding_start = -1;

	if (level == MARIO_LEVEL_SMALL)
		CGame::GetInstance()->GetCurrentScene()->AddObject(new Koopa(x, y - (KOOPA_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT)));
	else if (level == MARIO_LEVEL_BIG)
		CGame::GetInstance()->GetCurrentScene()->AddObject(new Koopa(x, y - (KOOPA_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT)));
	else CGame::GetInstance()->GetCurrentScene()->AddObject(new Koopa(x, y));

	StartUntouchable();
	SetLevel(level - 1);
	DebugOut(L">>>end holding shell>>> \n");
}

void CMario::EndLoadPower()
{
	isLoadingPower = false;
	power = 0;
	power_start = -1;
	DebugOut(L">>>end power>>> \n");
}

void CMario::EndFly()
{
	fly_start = -1;
	isFlying = false;
	DebugOut(L">>>end fly>>> \n");
	ay = MARIO_GRAVITY;
}

bool CMario::GetShell()
{
	for (int i = 0; i < CGame::GetInstance()->GetCurrentScene()->NumberObject(); i++)
	{
		if (dynamic_cast<Koopa*>(CGame::GetInstance()->GetCurrentScene()->getObject(i)))
		{
			Koopa* koopas = dynamic_cast<Koopa*>(CGame::GetInstance()->GetCurrentScene()->getObject(i));
			if (koopas->GetState() != KOOPA_STATE_SHELL) continue;

			float xx, yy;
			koopas->GetPosition(xx, yy);
			if (yy - y > -KOOPA_BBOX_HEIGHT_SHELL / 2 &&
				yy - y < MARIO_BIG_RACCOON_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL / 2)
			{
				if (nx > 0)
				{
					if (xx - x > 5 && xx - x < MARIO_BIG_BBOX_WIDTH + 15)
					{
						holdingTimeMax = koopas->GetTimeHideRemain();
						isHolding = true;
						holding_start = GetTickCount64();

						DebugOut(L">>>holding start>>> \n");

						koopas->Delete();
						return true;
					}
				}
				else
				{
					if (x - xx > 5 && x - xx < KOOPA_BBOX_WIDTH + 10)
					{
						holdingTimeMax = koopas->GetTimeHideRemain();
						isHolding = true;
						holding_start = GetTickCount64();

						DebugOut(L">>>holding start>>> \n");

						koopas->Delete();
						return true;
					}
				}
			}
		}

		if (dynamic_cast<RedKoopas*>(CGame::GetInstance()->GetCurrentScene()->getObject(i)))
		{
			RedKoopas* redKoopas = dynamic_cast<RedKoopas*>(CGame::GetInstance()->GetCurrentScene()->getObject(i));
			if (redKoopas->GetState() != KOOPA_STATE_SHELL) continue;

			float xx, yy;
			redKoopas->GetPosition(xx, yy);
			if (yy - y > -KOOPA_BBOX_HEIGHT_SHELL / 2 &&
				yy - y < MARIO_BIG_RACCOON_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL / 2)
			{
				if (nx > 0)
				{
					if (xx - x > 5 && xx - x < MARIO_BIG_BBOX_WIDTH + 5)
					{
						holdingTimeMax = redKoopas->GetTimeHideRemain();
						isHolding = true;
						holding_start = GetTickCount64();

						DebugOut(L">>>holding start>>> \n");

						redKoopas->Delete();
						return true;
					}
				}
				else
				{
					if (x - xx > 5 && x - xx < KOOPA_BBOX_WIDTH + 5)
					{
						holdingTimeMax = redKoopas->GetTimeHideRemain();
						isHolding = true;
						holding_start = GetTickCount64();

						DebugOut(L">>>holding start>>> \n");

						redKoopas->Delete();
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

void CMario::AccessHiddenZone()
{
	isInHiddenZone = true;
	x = HIDDEN_ZONE_X;
	y = HIDDEN_ZONE_Y;
}

void CMario::ExitHiddenZone()
{
	isInHiddenZone = false;
	x = EXIT_HIDDEN_ZONE_X;
	y = EXIT_HIDDEN_ZONE_Y;
}

//void CMario::AddTail()
//{
//	if (GetLevel() == MARIO_LEVEL_RACCOON && state == MARIO_STATE_HIT)
//	{
//		if (tail == NULL)
//		{
//			tail = new Tail(x, y);
//			CGame::GetInstance()->GetCurrentScene()->AddObject(tail);
//		}
//
//	}
//	else
//	{
//		if (tail != NULL)
//		{
//			tail->Delete();
//			tail = NULL;
//			DebugOut(L">>>tail delete>>> \n");
//		}
//	}
//}