#include "Thorn.h"
#include "Mario.h"

void Thorn::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
	{
		CMario* mario = dynamic_cast<CMario*>(e->obj);

		if (mario->getUntouchable() == 1) return;

		mario->StartUntouchable();
		mario->SetLevel(mario->GetLevel() - 1);
	}
}

void Thorn::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void Thorn::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_SPRITE_PIPE)->Draw(x, y);
}

void Thorn::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (y > init_y + THORN_HIGHT_SCOPE)
		vy = -THORN_SPEED;
	else if (y < init_y)
		vy = THORN_SPEED;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Thorn::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - THORN_WIDTH / 2;
	t = y - THORN_HIGHT / 2;
	r = l + THORN_WIDTH;
	b = t + THORN_HIGHT;
}

void Thorn::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case THORN_STATE_STATIC:
		vy = 0;
		break;
	case THORN_STATE_MOVE:
		vy = THORN_SPEED;
		break;

	}
}
