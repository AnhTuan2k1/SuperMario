#include "Goomba.h"
#include "Mario.h"
#include "Koopa.h"

CGoomba::CGoomba(float x, float y, int state):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(state);
	isflying = false;
	StartWalking();
}

CGoomba::CGoomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else if (state == WINGGOOMBA_STATE_WALKING)
	{
		left = x - WINGGOOMBA_BBOX_WIDTH / 2;
		top = y - WINGGOOMBA_BBOX_HEIGHT / 2;
		right = left + WINGGOOMBA_BBOX_WIDTH;
		bottom = top + WINGGOOMBA_BBOX_HEIGHT;
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 
	if (dynamic_cast<Koopa*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj))
	{
		if (e->ny != 0)
		{
			vy = 0;
		}
		return;
	}

		

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	if (state == WINGGOOMBA_STATE_WALKING)
	{
		if (isflying)
		{
			vy = -WINGGOOMBA_FLY_SPEED;

			if (GetTickCount64() - fly_start > WINGGOOMBA_FLY_TIMEOUT)
			{
				EndFlying();
				StartWalking();
			}

			if (y < fly_y - WINGGOOMBA_FLY_HEIGHT)
				y = fly_y - WINGGOOMBA_FLY_HEIGHT;
		}
		else if (isWalking)
		{
			if (GetTickCount64() - walk_start > WINGGOOMBA_WALK_TIMEOUT)
			{
				EndWalking();
				StartFlying();
			}
		}
	}

	if (y > 1000) this->Delete();

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE) 
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	else if (state == WINGGOOMBA_STATE_WALKING)
	{
		if (isflying)
			aniId = ID_ANI_WINGGOOMBA_FLY;
		else
			aniId = ID_ANI_WINGGOOMBA_WALKING;
	}
	else if (state == GOOMBA_STATE_DIE_BYKOOPAS)
	{
		
	}
	else if (state == WINGGOOMBA_STATE_HITTED_BYTAIL)
	{
		aniId = ID_ANI_WINGGOOMBA_WALKING;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{		
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_DIE_BYKOOPAS:
			vy = -GOOMBA_JUMP_DEFLECT_SPEED;
			vx = 0;
			ax = 0;
			break;

		case WINGGOOMBA_STATE_WALKING:
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			break;

	}
}

void CGoomba::SetState(int state, int direct)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WINGGOOMBA_STATE_HITTED_BYTAIL:
	case GOOMBA_STATE_HITTED_BYTAIL:
		vy = -GOOMBA_JUMP_DEFLECT_SPEED;
		vx = GOOMBA_JUMP_DEFLECT_SPEEDX * direct;
		ax = 0;

		break;

	}
}

void CGoomba::StartFlying()
{
	isflying = true;
	fly_start = GetTickCount64();
}

void CGoomba::StartWalking()
{
	isWalking = true;
	walk_start = GetTickCount64();
}

void CGoomba::EndWalking()
{
	isWalking = false;
	walk_start = -1;
	fly_y = y;
}

void CGoomba::EndFlying()
{
	isflying = false;
	fly_start = -1;
}
