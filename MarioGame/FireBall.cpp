#include "FireBall.h"
#include "Mario.h"

void FireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIREBALL_BBOX_WIDTH / 2;
	top = y - FIREBALL_BBOX_HEIGHT / 2;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//if (y_initial < y < y_initial + 50)
	//{
	//	if (vy > 0)
	//		vy = FIREBALL_SPEED_SLOW;
	//	else
	//		vy = -FIREBALL_SPEED_SLOW;
	//}	

	//if (y > y_initial + 50)
	//{
	//	vy = FIREBALL_SPEED;
	//}

	if(y < y_initial)
		vy = FIREBALL_SPEED_SLOW;

	if (y > y_initial + FIREBALL_SCOPE_Y)
		vy = -FIREBALL_SPEED;

	if (state == FIREBALL_STATE_DELAY)
	{
		if (GetTickCount64() - delay_start > FIREBALL_TIME_DELAY)
			SetState(FIREBALL_STATE_MOVE);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void FireBall::Render()
{
	if (state == FIREBALL_STATE_DELAY) return;
	int aniId = ID_ANI_FIREBALL_UP;

	if (vy > 0)
		aniId = ID_ANI_FIREBALL_DOWN;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void FireBall::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void FireBall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
	{
		CMario* mario = dynamic_cast<CMario*>(e->obj);

		if (mario->getUntouchable() == 1) return;

		mario->StartUntouchable();
		mario->SetLevel(mario->GetLevel() - 1);
	}
}

void FireBall::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIREBALL_STATE_DELAY:
		vy = 0;
		delay_start = GetTickCount64();
		break;
	case FIREBALL_STATE_MOVE:
		vy = FIREBALL_SPEED_SLOW;
		break;

	}
}
