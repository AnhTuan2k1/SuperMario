#include "Brick.h"

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBrick::OnNoCollision(DWORD dt)
{
	// handle go up and down
	y += vy * dt;
	if (y < y_initial - BRICK_HEIGHT_BOUNCE)
	{
		ay = BRICK_SPEED_BOUNCE;
	}

	if (y > y_initial)
	{
		if (bounce_times == 0)
			SetState(BRICK_STATE_ROCK);
		else
			SetState(BRICK_STATE_STATIC);
	}
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_STATE_BOUNCE:
		ay = -BRICK_SPEED_BOUNCE;
		bounce_times--;
		break;
	case BRICK_STATE_STATIC:
		ay = 0;
		vy = 0;
		y = y_initial;
		break;
	case BRICK_STATE_ROCK:
		ay = 0;
		vy = 0;
		y = y_initial;
		break;
	}
}

void CBrick::Render()
{
	int animations = ID_ANI_BRICK_CLASSICAL;
	if (state == BRICK_STATE_BOUNCE)
	{
		animations = ID_ANI_BRICK_CLASSICAL;
	}
	else if (state == BRICK_STATE_STATIC)
	{
		animations = ID_ANI_BRICK_CLASSICAL;
	}
	else if (state == BRICK_STATE_ROCK)
	{
		animations = ID_ANI_ROCK_BRICK_CLASSICAL;
	}

	CAnimations::GetInstance()->Get(animations)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}