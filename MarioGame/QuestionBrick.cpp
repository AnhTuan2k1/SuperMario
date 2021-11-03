#include "QuestionBrick.h"

void QuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_QUESTION_BRICK)->Render(x, y);
	//RenderBoundingBox();
}

void QuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTION_BRICK_BBOX_WIDTH / 2;
	t = y - QUESTION_BRICK_BBOX_HEIGHT / 2;
	r = l + QUESTION_BRICK_BBOX_WIDTH;
	b = t + QUESTION_BRICK_BBOX_HEIGHT;
}

void QuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void QuestionBrick::OnNoCollision(DWORD dt)
{
	y += vy * dt;
	if (y < y_initial - QUESTION_BRICK_HEIGHT_BOUNCE)
	{
		ay = QUESTION_BRICK_SPEED_BOUNCE;
		isbounce = true;
	}

	if (y > y_initial)
	{
		if (isbounce)
		{
			SetState(QUESTION_BRICK_STATE_STATIC);
			isbounce = false;
		}	
	}
}

void QuestionBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTION_BRICK_STATE_BOUNCE:
		ay = -QUESTION_BRICK_SPEED_BOUNCE;
		break;
	case QUESTION_BRICK_STATE_STATIC:
		ay = 0;
		vy = 0;
		y = y_initial;
		break;
	}
}