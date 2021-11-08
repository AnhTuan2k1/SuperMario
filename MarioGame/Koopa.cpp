#include "Koopa.h"
#include "Goomba.h"
#include "Mario.h"
#include "RedKoopas.h"
#include "Brick.h"
#include "QuestionBrick.h"
#include "Mushroom.h"

void Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_SHELL)
	{
		left = x - KOOPA_BBOX_WIDTH_SHELL / 2;
		top = y - KOOPA_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPA_BBOX_WIDTH_SHELL;
		bottom = top + KOOPA_BBOX_HEIGHT_SHELL;
	}
	else if (state == KOOPA_STATE_SHELL_RUNNING)
	{
		left = x - KOOPA_BBOX_WIDTH_SHELL / 2;
		top = y - KOOPA_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPA_BBOX_WIDTH_SHELL;
		bottom = top + KOOPA_BBOX_HEIGHT_SHELL;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}


void Koopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_SHELL:
		hide_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_SHELL_RUNNING:
		vx = -KOOPA_RUNING_SPEED;
		break;
	case KOOPA_STATE_DIE_BYKOOPAS:
		vy = -KOOPA_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		ay = KOOPA_GRAVITY;
		break;
	}
}

void Koopa::SetState(int state, int direct)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_SHELL:
		hide_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_SHELL_RUNNING:
		vx = -KOOPA_RUNING_SPEED * direct;
		this->ay = KOOPA_GRAVITY;
		break;
	//case KOOPA_STATE_DIE_BYKOOPAS:
	//	vy = -KOOPA_JUMP_DEFLECT_SPEED;
	//	vx = 0;
	//	ax = 0;
	//	break;
	}
}

void Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_STATE_SHELL) && (GetTickCount64() - hide_start > KOOPA_SHELL_TIMEOUT))
	{
		this->ax = 0;
		this->ay = KOOPA_GRAVITY;
		hide_start = -1;
		SetState(KOOPA_STATE_WALKING);
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Koopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING;
	if (state == KOOPA_STATE_SHELL)
	{
		aniId = ID_ANI_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_SHELL_RUNNING)
	{
		aniId = ID_ANI_KOOPA_SHELL;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void Koopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void Koopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		if (e->ny < 0 && e->obj->IsBlocking())
		{
			vy = 0;
			return;
		}
		vy = 0;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = -vx;
		}

	if (dynamic_cast<CGoomba*>(e->obj)) OnCollisionWithGoomba(e);
	if (dynamic_cast<Koopa*>(e->obj)) OnCollisionWithKoopa(e);
	if (dynamic_cast<CMario*>(e->obj)) OnCollisionWithMario(e);
	if (dynamic_cast<RedKoopas*>(e->obj)) OnCollisionWithRedKoopa(e);
	if (dynamic_cast<QuestionBrick*>(e->obj)) OnCollisionWithQuestionBrick(e);
	if (dynamic_cast<Mushroom*>(e->obj)) OnCollisionWithMushroom(e);
}

void Koopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (GetState() == KOOPA_STATE_SHELL_RUNNING)
	{
		goomba->SetState(GOOMBA_STATE_DIE_BYKOOPAS);
	}
}

void Koopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	Koopa* koopas = dynamic_cast<Koopa*>(e->obj);
	if (GetState() == KOOPA_STATE_SHELL_RUNNING)
	{
		koopas->SetState(KOOPA_STATE_DIE_BYKOOPAS);
	}
}

void Koopa::OnCollisionWithMario(LPCOLLISIONEVENT e)
{
	//if (e->ny >= 0)
	//{
	//	vy = 0;
	//	return;
	//}
}

void Koopa::OnCollisionWithRedKoopa(LPCOLLISIONEVENT e)
{
	RedKoopas* redkoopas = dynamic_cast<RedKoopas*>(e->obj);
	if (GetState() == REDKOOPA_STATE_SHELL_RUNNING)
	{
		redkoopas->SetState(REDKOOPA_STATE_DIE_BYKOOPAS);
	}
}

void Koopa::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	QuestionBrick* questionBrick = dynamic_cast<QuestionBrick*>(e->obj);
	if (questionBrick->GetState() == QUESTION_BRICK_STATE_STATIC && GetState() == KOOPA_STATE_SHELL_RUNNING)
	{
		questionBrick->SetState(QUESTION_BRICK_STATE_BOUNCED);
	}
}

void Koopa::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	Mushroom* mushroom = dynamic_cast<Mushroom*>(e->obj);

	if (mushroom->GetState() == MUSHROOM_STATE_HIDE && nx != 0)
	{
		mushroom->SetState(MUSHROOM_STATE_BOUNCE);
	}
}

