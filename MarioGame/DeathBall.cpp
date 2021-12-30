#include "DeathBall.h"
#include "Mario.h"

void DeathBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - DEATHBALL_BBOX_WIDTH / 2;
	top = y - DEATHBALL_BBOX_HEIGHT / 2;
	right = left + DEATHBALL_BBOX_WIDTH;
	bottom = top + DEATHBALL_BBOX_HEIGHT;
}

void DeathBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void DeathBall::Render()
{
	CSprites* s = CSprites::GetInstance();

	s->Get(ID_SPRITE_DEATHBALL)->Draw(x, y);
}

void DeathBall::OnNoCollision(DWORD dt)
{
	time += DEATHBALL_SPEED * dt;

	x = centerX + cos(time) * DEATHBALL_RADIUS;
	y = centerY + sin(time) * DEATHBALL_RADIUS;

}

void DeathBall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (dynamic_cast<CMario*>(e->obj))
	//{
	//	CMario* mario = dynamic_cast<CMario*>(e->obj);
	//	if (mario->getUntouchable() == 1) return;

	//	mario->StartUntouchable();
	//	mario->SetLevel(mario->GetLevel() - 1);
	//}
}
