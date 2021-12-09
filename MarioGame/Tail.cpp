#include "Tail.h"
#include "Mario.h"
#include "Textures.h"
#include "AssetIDs.h"
#include "Goomba.h"
#include "DCoin.h"
#include "Koopa.h"
#include "QuestionBrick.h"
#include "Mushroom.h"
#include "RedKoopas.h"
#include "Brick.h"

void Tail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	//if (state == TAIL_STATE_HIT)
	//{
	//	left = x - TAIL_HIT_BBOX_WIDTH / 2;
	//	top = y - TAIL_HIT_BBOX_HEIGHT / 2;
	//	right = left + TAIL_HIT_BBOX_WIDTH;
	//	bottom = top + TAIL_HIT_BBOX_HEIGHT;
	//}
	//else
	{
		left = x - TAIL_BBOX_WIDTH / 2;
		top = y - TAIL_BBOX_HEIGHT / 2;
		right = left + TAIL_BBOX_WIDTH;
		bottom = top + TAIL_BBOX_HEIGHT;
	}
}

void Tail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (GetTickCount64() - hit_start > TAIL_DIE_TIMEOUT)
	{
		this->Delete();
		return;
	}

	if (x > xMario + 8)
	{
		vx = -TAIL_SPEED;
		//DebugOut(L">>>tail reverse direct to left>>> \n");
	}
	else if (x < xMario - 8)
	{
		vx = TAIL_SPEED;
		//DebugOut(L">>>tail reverse direct to right>>> \n");
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Tail::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_TAIL_INVISIBLE)->Render(x, y);
	RenderBoundingBox();
}

void Tail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (vx > 0)
	{
		if(goomba->GetState() == GOOMBA_STATE_WALKING)
			goomba->SetState(GOOMBA_STATE_HITTED_BYTAIL, 1);
		else 
			goomba->SetState(WINGGOOMBA_STATE_HITTED_BYTAIL, 1);
	}
		
	else
	{
		if (goomba->GetState() == GOOMBA_STATE_WALKING)
			goomba->SetState(GOOMBA_STATE_HITTED_BYTAIL, -1);
		else
			goomba->SetState(WINGGOOMBA_STATE_HITTED_BYTAIL, -1);
	}
}

void Tail::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
}

void Tail::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
}

void Tail::OnCollisionWithDCoin(LPCOLLISIONEVENT e)
{
}

void Tail::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
}

void Tail::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
}

void Tail::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
}

void Tail::OnCollisionWithRedKoopas(LPCOLLISIONEVENT e)
{
}

void Tail::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}


void Tail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<DCoin*>(e->obj))
		OnCollisionWithDCoin(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<Koopa*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<QuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<Mushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<RedKoopas*>(e->obj))
		OnCollisionWithRedKoopas(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);

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

//void Tail::SetAniId(int marioRaccoonAniID)
//{
//	if (this == NULL) return;
//
//	aniID = ID_ANI_TAIL_INVISIBLE;
//	
//}
//
//void Tail::SetPosition(float xMario, float yMario)
//{
//	if (this == NULL) return;
//
//	
//}
//
//void Tail::SetState(int state)
//{
//	CGameObject::SetState(state);
//	switch (state)
//	{
//	case TAIL_STATE_DECORATE:
//		
//		break;
//	case TAIL_STATE_RIGHT:
//		hit_start = GetTickCount64();
//		break;
//
//	}
//}
//
//void Tail::SetSpeed(float VxMario, float VyMario)
//{
//	if (this == NULL) return;
//	vx = vx + VxMario;
//	vy = vy + VyMario;
//}
//
//void Tail::SetXmario(const float xMario)
//{
//	if (this == NULL) return;
//	this->xMario = xMario;
//}
