#include "DCoin.h"

void DCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	
	if (GetTickCount64() - bounce_start > DCOIN_BOUNCE_TIMEOUT && GetState() == DCOIN_STATE_BOUNCE)
	{
		SetState(DCOIN_STATE_STATIC);
		bounce_start = -1;
		bounce_times--;
		if (bounce_times < 1)
		{
			this->Delete();
		}

	}


	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void DCoin::OnNoCollision(DWORD dt)
{
	y += vy * dt;
	if (y < y_initial - DCOIN_HEIGHT_BOUNCE)
	{
		y = y_initial - DCOIN_HEIGHT_BOUNCE;
	}
}

void DCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case DCOIN_STATE_BOUNCE:
		bounce_start = GetTickCount64();
		ay = -DCOIN_SPEED_BOUNCE;
		break;
	case DCOIN_STATE_STATIC:
		ay = 0;
		vy = 0;
		y = y_initial;
		break;
	}
}



