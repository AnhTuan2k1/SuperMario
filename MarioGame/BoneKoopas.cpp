#include "BoneKoopas.h"

void BoneKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == BONEKOOPA_STATE_DIE )
	{
		left = x - BONEKOOPA_DIE_BBOX_WIDTH / 2;
		top = y - BONEKOOPA_DIE_BBOX_HEIGHT / 2;
		right = left + BONEKOOPA_DIE_BBOX_WIDTH;
		bottom = top + BONEKOOPA_DIE_BBOX_HEIGHT;
	}
	else if (state == BONEKOOPA_STATE_WALKING)
	{
		left = x - BONEKOOPA_BBOX_WIDTH / 2;
		top = y - BONEKOOPA_BBOX_HEIGHT / 2;
		right = left + BONEKOOPA_BBOX_WIDTH;
		bottom = top + BONEKOOPA_BBOX_HEIGHT;
	}

}

void BoneKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	if (state == BONEKOOPA_STATE_DIE && GetTickCount64() - die_start > BONEKOOPA_DIE_TIMEOUT)
	{
		die_start = -1;
		SetState(BONEKOOPA_STATE_WALKING);
		y -= (BONEKOOPA_BBOX_HEIGHT - BONEKOOPA_DIE_BBOX_HEIGHT) / 2;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void BoneKoopas::Render()
{
	int aniId = ID_ANI_BONEKOOPA_WALKING_RIGHT;
	if (state == BONEKOOPA_STATE_WALKING)
	{
		if (vx < 0)
			aniId = ID_ANI_BONEKOOPA_WALKING_LEFT;
	}
	else if (state == BONEKOOPA_STATE_DIE)
	{
		//if (nx > 0)
		//	aniId = ID_ANI_BONEKOOPA_DIE_RIGHT;
		//else
		//	aniId = ID_ANI_BONEKOOPA_DIE_LEFT;

		if (iswalkingright)
			aniId = ID_ANI_BONEKOOPA_DIE_RIGHT;
		else
			aniId = ID_ANI_BONEKOOPA_DIE_LEFT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void BoneKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void BoneKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = -vx;
		iswalkingright = !iswalkingright;
	}
}

void BoneKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BONEKOOPA_STATE_WALKING:
		vx = -BONEKOOPA_WALKING_SPEED;
		iswalkingright = false;
		break;

	case BONEKOOPA_STATE_DIE:
		vx = 0;
		die_start = GetTickCount64();
		y -= (BONEKOOPA_BBOX_HEIGHT - BONEKOOPA_DIE_BBOX_HEIGHT) / 2;
		break;
	}
}
