#include "Koopa.h"
#include "Goomba.h"
#include "Mario.h"
#include "RedKoopas.h"
#include "Brick.h"
#include "QuestionBrick.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "PlayScene.h"

void Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_HITTED_BYTAIL)
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
		if (state != KOOPA_STATE_SHELL_RUNNING && state != KOOPA_STATE_SHELL)
			y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		isRunning = false;
		break;
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		isRunning = false;
		break;
	case KOOPA_STATE_SHELL_RUNNING:
		vx = -KOOPA_RUNING_SPEED;
		isRunning = true;
		break;
	case KOOPA_STATE_DIE_BYKOOPAS:
		vy = -KOOPA_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		ay = KOOPA_GRAVITY;
		isRunning = false;
		break;
	}

	isDropping = false;
}

void Koopa::SetState(int state, int direct)
{
	switch (state)
	{
	case KOOPA_STATE_SHELL:
		hide_start = GetTickCount64();
		if (state != KOOPA_STATE_SHELL_RUNNING && state != KOOPA_STATE_SHELL)
			y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		isRunning = false;
		break;
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		isRunning = false;
		break;
	case KOOPA_STATE_SHELL_RUNNING:
		vx = -KOOPA_RUNING_SPEED * direct;
		this->ay = KOOPA_GRAVITY;
		isRunning = true;
		break;
	case KOOPA_STATE_HITTED_BYTAIL:
		vy = -KOOPA_JUMP_DEFLECT_SPEED;
		vx = KOOPA_JUMP_DEFLECT_SPEEDX * direct;
		ax = 0;
		ay = KOOPA_GRAVITY;
		hide_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		isRunning = false;
		break;

	//case KOOPA_STATE_DIE_BYKOOPAS:
	//	vy = -KOOPA_JUMP_DEFLECT_SPEED;
	//	vx = 0;
	//	ax = 0;
	//	break;
	}

	isDropping = false;
	CGameObject::SetState(state);
}

void Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_STATE_SHELL || state == KOOPA_STATE_HITTED_BYTAIL)
		&& (GetTickCount64() - hide_start > KOOPA_SHELL_TIMEOUT))
	{
		this->ax = 0;
		this->ay = KOOPA_GRAVITY;
		hide_start = -1;
		SetState(KOOPA_STATE_WALKING);
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		return;
	}

	if (state == KOOPA_STATE_HITTED_BYTAIL && (GetTickCount64() - hide_start > 400))
	{
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		SetState(KOOPA_STATE_SHELL);		
	}

	if (isDropping)
	{
		if (state == KOOPA_STATE_SHELL && (GetTickCount64() - dropped_start > 500))
		{
			vx = 0;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Koopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING;
	if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_HITTED_BYTAIL)
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
	if (dynamic_cast<CBrick*>(e->obj)) OnCollisionWithBrick(e);
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

	if (state == KOOPA_STATE_SHELL_RUNNING)
	if (mushroom->GetState() == MUSHROOM_STATE_HIDE && e->nx != 0)
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (mario->GetLevel() == MARIO_LEVEL_SMALL)
			mushroom->SetState(MUSHROOM_STATE_BOUNCE);
		else
		{
			mushroom->Delete();
			float xx, yy;
			mushroom->GetPosition(xx, yy);
			CGame::GetInstance()->GetCurrentScene()->AddObject(new Leaf(xx, yy));
		}
	}
}

void Koopa::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);

	if (e->nx != 0)
	{
		if (GetState() == REDKOOPA_STATE_SHELL_RUNNING && brick->Isbreak())
		{
			brick->SetState(BRICK_STATE_BREAK);
		}
	}
}

