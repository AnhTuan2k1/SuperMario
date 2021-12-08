#include "Tail.h"
#include "Mario.h"
#include "Textures.h"
#include "AssetIDs.h"

void Tail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TAIL_STATE_HIT)
	{
		left = x - TAIL_HIT_BBOX_WIDTH / 2;
		top = y - TAIL_HIT_BBOX_HEIGHT / 2;
		right = left + TAIL_HIT_BBOX_WIDTH;
		bottom = top + TAIL_HIT_BBOX_HEIGHT;
	}
	else
	{
		left = x - TAIL_BBOX_WIDTH / 2;
		top = y - TAIL_BBOX_HEIGHT / 2;
		right = left + TAIL_BBOX_WIDTH;
		bottom = top + TAIL_BBOX_HEIGHT;
	}
}

void Tail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void Tail::Render()
{
	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}

void Tail::OnNoCollision(DWORD dt)
{
	// change position follow mario
}

void Tail::OnCollisionWith(LPCOLLISIONEVENT e)
{

}


//CMario* Tail::GetMario()
//{
//	for (int i = 0; i < CGame::GetInstance()->GetCurrentScene()->NumberObject(); i++)
//	{
//		if (dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->getObject(i)))
//		{
//			return dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->getObject(i));
//		}
//	}
//}

void Tail::SetAniId(int marioRaccoonAniID)
{
	if (this == NULL) return;

	aniID = ID_ANI_TAIL_IDLE_RIGHT;
	if (marioRaccoonAniID == ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT)
		aniID = ID_ANI_TAIL_JUMP_RUN_RIGHT;
	else if (marioRaccoonAniID == ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT)
		aniID = ID_ANI_TAIL_JUMP_RUN_LEFT;
	else if (marioRaccoonAniID == ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT)
		aniID = ID_ANI_TAIL_JUMP_WALK_RIGHT;
	else if (marioRaccoonAniID == ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT)
		aniID = ID_ANI_TAIL_JUMP_WALK_LEFT;
	else if (marioRaccoonAniID == ID_ANI_MARIO_RACCOON_SIT_RIGHT)
		aniID = ID_ANI_TAIL_SIT_RIGHT;
	else if (marioRaccoonAniID == ID_ANI_MARIO_RACCOON_SIT_LEFT)
		aniID = ID_ANI_TAIL_SIT_LEFT;
	else if (marioRaccoonAniID == ID_ANI_MARIO_RACCOON_IDLE_RIGHT)
		aniID = ID_ANI_TAIL_IDLE_RIGHT;
	else if (marioRaccoonAniID == ID_ANI_MARIO_RACCOON_IDLE_LEFT)
		aniID = ID_ANI_TAIL_IDLE_LEFT;
	else if (marioRaccoonAniID == ID_ANI_MARIO_RACCOON_BRACE_RIGHT)
		aniID = ID_ANI_TAIL_BRACE_RIGHT;
	else if (marioRaccoonAniID == ID_ANI_MARIO_RACCOON_RUNNING_RIGHT)
		aniID = ID_ANI_TAIL_RUNNING_RIGHT;
	else if (marioRaccoonAniID == ID_ANI_MARIO_RACCOON_WALKING_RIGHT)
		aniID = ID_ANI_TAIL_WALKING_RIGHT;
	else if (marioRaccoonAniID == ID_ANI_MARIO_RACCOON_BRACE_LEFT)
		aniID = ID_ANI_TAIL_BRACE_LEFT;
	else if (marioRaccoonAniID == ID_ANI_MARIO_RACCOON_RUNNING_LEFT)
		aniID = ID_ANI_TAIL_RUNNING_LEFT;
	else if (marioRaccoonAniID == ID_ANI_MARIO_RACCOON_WALKING_LEFT)
		aniID = ID_ANI_TAIL_WALKING_LEFT;
}

void Tail::SetPosition(float xMario, float yMario)
{
	if (this == NULL) return;

	if (aniID == ID_ANI_TAIL_RUNNING_RIGHT)
	{
		this->x = xMario - 5;
		this->y = yMario + 7;
	}

	else if (aniID == ID_ANI_TAIL_RUNNING_LEFT)
	{
		this->x = xMario + 5 /*MARIO_BIG_RACCOON_BBOX_WIDTH - (float)TAIL_BBOX_WIDTH / 2*/;
		this->y = yMario + 7 /*(float)MARIO_BIG_RACCOON_BBOX_HEIGHT / 2 - (float)TAIL_BBOX_HEIGHT / 2*/;
	}

	else if (aniID == ID_ANI_TAIL_IDLE_LEFT)
	{
		this->x = xMario + 10;
		this->y = yMario + 9;
	}
	else if (aniID == ID_ANI_TAIL_IDLE_RIGHT)
	{
		this->x = xMario - 10;
		this->y = yMario + 9;
	}

	else if (aniID == ID_ANI_TAIL_WALKING_LEFT)
	{
		this->x = xMario + 10;
		this->y = yMario + 8;
	}
	else if ( aniID == ID_ANI_TAIL_WALKING_RIGHT)
	{
		this->x = xMario - 9;
		this->y = yMario + 8;
	}

	else if ( aniID == ID_ANI_TAIL_JUMP_WALK_LEFT)
	{
		this->x = xMario + 10;
		this->y = yMario + 8;
	}
	else if ( aniID == ID_ANI_TAIL_JUMP_WALK_RIGHT)
	{
		this->x = xMario - 9;
		this->y = yMario + 8;
	}

	else if (aniID == ID_ANI_TAIL_SIT_LEFT)
	{
		this->x = xMario + 5;
		this->y = yMario + 7;
	}
	else if ( aniID == ID_ANI_TAIL_SIT_RIGHT)
	{
		this->x = xMario - 5;
		this->y = yMario + 7;
	}

	else if (aniID == ID_ANI_TAIL_JUMP_RUN_LEFT)
	{
		this->x = xMario + 5;
		this->y = yMario + 7 ;
	}
	else if (aniID == ID_ANI_TAIL_JUMP_RUN_RIGHT)
	{
		this->x = xMario - 5;
		this->y = yMario + 7;
	}

	else
	{
		this->x = xMario - TAIL_BBOX_WIDTH;
		this->y = yMario - (float)TAIL_BBOX_HEIGHT / 2;
	}

}

void Tail::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case TAIL_STATE_DECORATE:
		
		break;
	case TAIL_STATE_HIT:
		
		break;

	}
}

void Tail::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(50);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - TAIL_BBOX_WIDTH / 2 + rect.right / 2;

	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}
