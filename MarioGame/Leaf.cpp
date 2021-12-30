#include "Leaf.h"
#include "debug.h"
#include "Brick.h"
#include "Mario.h"

void Leaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - LEAF_BBOX_WIDTH / 2;
	top = y - LEAF_BBOX_HEIGHT / 2;
	right = left + LEAF_BBOX_WIDTH;
	bottom = top + LEAF_BBOX_HEIGHT;
}

void Leaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	if (y < y_initial - LEAF_HEIGHT_BOUNCE && GetState() == LEAF_STATE_BOUNCE)
	{
		SetState(LEAF_STATE_MOVING);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Leaf::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_SPRITE_LEAF)->Draw(x, y);
}

void Leaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	if (state == LEAF_STATE_MOVING &&
		(x > x_initial + LEAF_MOVEMENT_SCOPE || x < x_initial - LEAF_MOVEMENT_SCOPE))
	{
		vx = -vx;
	}
}

void Leaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (dynamic_cast<CMario*>(e->obj))
	//	OnCollisionWithMario(e);
}

//void Leaf::OnCollisionWithMario(LPCOLLISIONEVENT e)
//{
//	CMario* mario = dynamic_cast<CMario*>(e->obj);
//
//	mario->SetLevel(MARIO_LEVEL_RACCOON);
//}

Leaf::Leaf(float x, float y) :CGameObject(x, y)
{
	this->vx = 0;
	this->ay = 0;
	y_initial = y;
	x_initial = x;
	SetState(LEAF_STATE_BOUNCE);
}

void Leaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_BOUNCE:
		vy = -LEAF_SPEED_BOUNCE;
		vx = 0;
		vx = 0;
		DebugOut(L">>>leaf bounce>>> \n");
		break;
	case LEAF_STATE_MOVING:
		vy = 0;
		ay = LEAF_GRAVITY;
		vx = LEAF_SPEED;

		break;

	}
}
