#include "Pbutton.h"
#include "Brick.h"
#include "Coin.h"

void Pbutton::Render()
{
	if (state == PBUTTON_STATE_BRICK)
	{
		CAnimations::GetInstance()->Get(ID_ANI_PBUTTON_BRICK)->Render(x, y);
	}
	else if (state == PBUTTON_STATE_BOUNCED)
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_PBUTTON_BOUNCED)->Draw(x, y);
	}
	else if (state == BRICK_STATE_ACTIVED)
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_PBUTTON_ACTIVED)->Draw(x, y);
	}

	//RenderBoundingBox();
}

void Pbutton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == PBUTTON_STATE_BRICK)
	{
		l = x - BRICK_BBOX_WIDTH / 2;
		t = y - BRICK_BBOX_HEIGHT / 2;
		r = l + BRICK_BBOX_WIDTH;
		b = t + BRICK_BBOX_HEIGHT;
	}
	else if (state == PBUTTON_STATE_BOUNCED)
	{
		l = x - BRICK_BBOX_WIDTH / 2;
		t = y - BRICK_BBOX_HEIGHT / 2;
		r = l + BRICK_BBOX_WIDTH;
		b = t + BRICK_BBOX_HEIGHT;

		t = t - (PBUTTON_BOUNCED_BBOX_HEIGHT - BRICK_BBOX_HEIGHT) + 10;
	}
	else if (state == BRICK_STATE_ACTIVED)
	{
		l = x - PBUTTON_ACTIVED_BBOX_WIDTH / 2;
		t = y - PBUTTON_ACTIVED_BBOX_HEIGHT / 2;
		r = l + PBUTTON_ACTIVED_BBOX_WIDTH;
		b = t + PBUTTON_ACTIVED_BBOX_HEIGHT;
	}
}

void Pbutton::OnNoCollision(DWORD dt)
{
	
}

void Pbutton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if(state == BRICK_STATE_ACTIVED)
	if (GetTickCount64() - transform_start > PBUTTON_TRANSFORM_TIME)
	{
		TransformCointoBrick();
		transform_start = -1;
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Pbutton::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PBUTTON_STATE_BRICK:

		break;
	case PBUTTON_STATE_BOUNCED:
		y -= 5;
		break;
	case BRICK_STATE_ACTIVED:
		transform_start = GetTickCount64();
		TransformBricktoCoin();
		break;
	}

}

void Pbutton::TransformBricktoCoin()
{
	for (int i = 0; i < CGame::GetInstance()->GetCurrentScene()->NumberObject(); i++)
	{
		if (dynamic_cast<CBrick*>(CGame::GetInstance()->GetCurrentScene()->getObject(i)))
		{
			CBrick* brick = dynamic_cast<CBrick*>(CGame::GetInstance()->GetCurrentScene()->getObject(i));

			float xx, yy;
			brick->GetPosition(xx, yy);

			if (xx > 2050 && xx < 2250 && yy > 140 && yy < 180)
			{
				brick->Delete();
				CGame::GetInstance()->GetCurrentScene()->AddObject(new CCoin(xx, yy));
			}

		}
	}
}

void Pbutton::TransformCointoBrick()
{
	for (int i = 0; i < CGame::GetInstance()->GetCurrentScene()->NumberObject(); i++)
	{
		if (dynamic_cast<CCoin*>(CGame::GetInstance()->GetCurrentScene()->getObject(i)))
		{
			CCoin* coin = dynamic_cast<CCoin*>(CGame::GetInstance()->GetCurrentScene()->getObject(i));

			float xx, yy;
			coin->GetPosition(xx, yy);

			if (xx > 2050 && xx < 2250 && yy > 140 && yy < 180)
			{
				coin->Delete();
				CGame::GetInstance()->GetCurrentScene()->AddObject(new CBrick(xx, yy, true));
			}

		}
	}
}
