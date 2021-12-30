#include "Mushroom.h"
#include "AssetIDs.h"
#include "debug.h"
#include "Pipe.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Mario.h"

Mushroom::Mushroom(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	y_initial = y;
	SetState(MUSHROOM_STATE_HIDE);
	DebugOut(L">>> MUSHROOM 4 >>> \n");
}

void Mushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}


void Mushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void Mushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<Koopa*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void Mushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (y < y_initial - MUSHROOM_HEIGHT_BOUNCE && GetState() == MUSHROOM_STATE_BOUNCE)
	{
		SetState(MUSHROOM_STATE_MOVING);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void Mushroom::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_SPRITE_RED_MUSHROOM)->Draw(x, y);
	//RenderBoundingBox();
}

void Mushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_BOUNCE:
		y -= 3;
		vy = -MUSHROOM_SPEED_BOUNCE;
		vx = 0;
		ax = 0;
		DebugOut(L">>> MUSHROOM 1 >>> \n");
		break;
	case MUSHROOM_STATE_MOVING:
		vy = 0;
		this->ay = MUSHROOM_GRAVITY;
		if (GetTickCount64() % 2 == 0)
			vx = MUSHROOM_SPEED;
		else vx = -MUSHROOM_SPEED;
		
		DebugOut(L">>> MUSHROOM 2 >>> \n");
		break;

	}
}
