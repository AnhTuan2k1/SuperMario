#include "Koopa.h"
#include "Goomba.h"
#include "Mario.h"

void Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_SHELL)
	{
		left = x - KOOPA_BBOX_WIDTH_SHELL / 2;
		top = y - KOOPA_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPA_BBOX_WIDTH_SHELL;
		bottom = top + KOOPA_BBOX_HEIGHT_SHELL;
	}else if (state == KOOPA_STATE_SHELL_RUNNING)
	{
		left = x - KOOPA_BBOX_WIDTH_SHELL / 2;
		top = y - KOOPA_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPA_BBOX_WIDTH_SHELL;
		bottom = top + KOOPA_BBOX_HEIGHT_SHELL;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

Koopa::Koopa(float x, float y, int state)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	hide_start = -1;
	SetState(state);
}

void Koopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_SHELL:
		hide_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_SHELL_RUNNING:
		vx = -KOOPA_RUNING_SPEED;
	}
}

void Koopa::SetState(int state, int direct)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_SHELL:
		hide_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_SHELL_RUNNING:
		vx = -KOOPA_RUNING_SPEED*direct;
		this->ay = KOOPA_GRAVITY;
	}
}

void Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_STATE_SHELL) && (GetTickCount64() - hide_start > KOOPA_SHELL_TIMEOUT))
	{
		this->ax = 0;
		this->ay = KOOPA_GRAVITY;
		hide_start = -1;
		SetState(KOOPA_STATE_WALKING);
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Koopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING;
	if (state == KOOPA_STATE_SHELL)
	{
		aniId = ID_ANI_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_SHELL_RUNNING)
	{
		aniId = ID_ANI_KOOPA_SHELL;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void Koopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void Koopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		if (e->ny < 0 && e->obj->IsBlocking())
		{
			vy = 0;
			return;
		}
		vy = 0;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = -vx;
		}

	if (dynamic_cast<CGoomba*>(e->obj)) OnCollisionWithGoomba(e);
	if (dynamic_cast<Koopa*>(e->obj)) OnCollisionWithKoopa(e);
	if (dynamic_cast<CMario*>(e->obj)) OnCollisionWithMario(e);
}

void Koopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{

}

void Koopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{

}

void Koopa::OnCollisionWithMario(LPCOLLISIONEVENT e)
{
	if (e->ny != 0)
	{
		vy = 0;
	}
	return;
}


