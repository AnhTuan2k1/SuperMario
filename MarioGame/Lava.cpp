#include "Lava.h"
#include "Mario.h"


void Lava::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
	{
		CMario* mario = dynamic_cast<CMario*>(e->obj);

		mario->SetState(MARIO_STATE_DIE);
	}
}

void Lava::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_SPRITE_PIPE)->Render(x, y);
}

void Lava::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Lava::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LAVA_WIDTH / 2;
	t = y - LAVA_HIGHT / 2;
	r = l + LAVA_WIDTH;
	b = t + LAVA_HIGHT;
}
