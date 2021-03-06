#include "RedKoopas.h"

#include "Goomba.h"
#include "Mario.h"
#include "Koopa.h"
#include "Rectangle.h"
#include "QuestionBrick.h"
#include "Mushroom.h"
#include "Platform.h"
#include "Brick.h"
#include "Pipe.h"
#include "PlayScene.h"
#include "Leaf.h"

void RedKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == REDKOOPA_STATE_SHELL || state == REDKOOPA_STATE_HITTED_BYTAIL)
	{
		left = x - KOOPA_BBOX_WIDTH_SHELL / 2;
		top = y - KOOPA_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPA_BBOX_WIDTH_SHELL;
		bottom = top + KOOPA_BBOX_HEIGHT_SHELL;
	}
	else if (state == REDKOOPA_STATE_SHELL_RUNNING)
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


void RedKoopas::SetState(int state)
{
	switch (state)
	{
	case REDKOOPA_STATE_SHELL:		
		hide_start = GetTickCount64();
		if (!isRunning && state != REDKOOPA_STATE_SHELL)
			y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		//DebugOut(L">>> RedKoopas 1 >>> \n");
		isRunning = false;
		break;
	case REDKOOPA_STATE_WALKING_LEFT:
		isRunning = false;
		vx = -KOOPA_WALKING_SPEED;
		//DebugOut(L">>> RedKoopas 2 >>> \n");
		break;
	case REDKOOPA_STATE_WALKING_RIGHT:
		isRunning = false;
		//DebugOut(L">>> RedKoopas 3 >>> \n");
		vx = KOOPA_WALKING_SPEED;
		break;
	case REDKOOPA_STATE_SHELL_RUNNING:
		isRunning = true;

		//DebugOut(L">>> RedKoopas 4 >>> \n");
		vx = -KOOPA_RUNING_SPEED;
		break;
	case REDKOOPA_STATE_DIE_BYKOOPAS:
		isRunning = false;
		//DebugOut(L">>> RedKoopas 5 >>> \n");
		vy = -KOOPA_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		ay = KOOPA_GRAVITY;
		break;
	}

	isDropping = false;
	CGameObject::SetState(state);
}

void RedKoopas::SetState(int state, int direct)
{
	switch (state)
	{
	case REDKOOPA_STATE_SHELL:
		hide_start = GetTickCount64();
		if (!isRunning && state != REDKOOPA_STATE_SHELL)
			y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		isRunning = false;
		break;
	case REDKOOPA_STATE_WALKING_LEFT:
		isRunning = false;
		vx = -KOOPA_WALKING_SPEED;
		break;
	case REDKOOPA_STATE_WALKING_RIGHT:
		isRunning = false;
		vx = KOOPA_WALKING_SPEED;
		break;
	case REDKOOPA_STATE_SHELL_RUNNING:
		isRunning = true;
		vx = -KOOPA_RUNING_SPEED * direct;
		this->ay = KOOPA_GRAVITY;
		break;
	case REDKOOPA_STATE_HITTED_BYTAIL:
		isRunning = false;
		vy = -KOOPA_JUMP_DEFLECT_SPEED;
		vx = KOOPA_JUMP_DEFLECT_SPEEDX * direct;
		ax = 0;
		ay = KOOPA_GRAVITY;
		hide_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
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

void RedKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == REDKOOPA_STATE_SHELL || state == REDKOOPA_STATE_HITTED_BYTAIL)
		&& (GetTickCount64() - hide_start > KOOPA_SHELL_TIMEOUT)) 
	{
		this->ax = 0;
		this->ay = KOOPA_GRAVITY;
		hide_start = -1;
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		SetState(REDKOOPA_STATE_WALKING_LEFT);
		return;
	}

	if (state == REDKOOPA_STATE_HITTED_BYTAIL && (GetTickCount64() - hide_start > 400))
	{
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		SetState(REDKOOPA_STATE_SHELL);
	}


	//reverse direct if reaching the rectangle's end. 
	if(state == REDKOOPA_STATE_WALKING_RIGHT || state == REDKOOPA_STATE_WALKING_LEFT)

		if (vx < 0)
		{
			if (x < rectangleX)
			{
				SetState(REDKOOPA_STATE_WALKING_RIGHT);
				//DebugOut(L">>> RedKoopas 6 >>> \n");
			}
		}
		else
		{
			if (x > rectangleWidth)
			{
				SetState(REDKOOPA_STATE_WALKING_LEFT);
				//DebugOut(L">>> RedKoopas 7 >>> \n");
			}
		}
	if (isDropping)
	{
		if (state == REDKOOPA_STATE_SHELL && (GetTickCount64() - dropped_start > 500))
		{
			vx = 0;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void RedKoopas::Render()
{
	int aniId = ID_ANI_REDKOOPA_WALKING_LEFT;
	if (state == REDKOOPA_STATE_SHELL || state == REDKOOPA_STATE_HITTED_BYTAIL)
	{
		aniId = ID_ANI_REDKOOPA_SHELL;
	}
	else if (state == REDKOOPA_STATE_SHELL_RUNNING)
	{
		aniId = ID_ANI_REDKOOPA_SHELL;
	}
	else if (state == REDKOOPA_STATE_WALKING_RIGHT)
	{
		aniId = ID_ANI_REDKOOPA_WALKING_RIGHT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void RedKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void RedKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CRectangle*>(e->obj))
		OnCollisionWithRectangle(e);
	if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatform(e);
	if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	if (dynamic_cast<CPipe*>(e->obj))
		OnCollisionWithPipe(e);
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

	if (dynamic_cast<CGoomba*>(e->obj)) 
		OnCollisionWithGoomba(e);
	 if (dynamic_cast<Koopa*>(e->obj))
		OnCollisionWithKoopa(e);
	 if (dynamic_cast<CMario*>(e->obj)) 
		OnCollisionWithMario(e);
	 if (dynamic_cast<RedKoopas*>(e->obj)) 
		OnCollisionWithRedKoopa(e);
	 if (dynamic_cast<QuestionBrick*>(e->obj)) 
		OnCollisionWithQuestionBrick(e);
	 if (dynamic_cast<Mushroom*>(e->obj))
		 OnCollisionWithMushroom(e);
}

void RedKoopas::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (GetState() == REDKOOPA_STATE_SHELL_RUNNING)
	{
		goomba->SetState(GOOMBA_STATE_DIE_BYKOOPAS);
	}
}

void RedKoopas::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	Koopa* koopas = dynamic_cast<Koopa*>(e->obj);
	if (GetState() == KOOPA_STATE_SHELL_RUNNING)
	{
		koopas->SetState(KOOPA_STATE_DIE_BYKOOPAS);
	}
}

void RedKoopas::OnCollisionWithMario(LPCOLLISIONEVENT e)
{
	//if (e->ny >= 0)
	//{
	//	vy = 0;
	//	return;
	//}
}

void RedKoopas::OnCollisionWithRedKoopa(LPCOLLISIONEVENT e)
{
	RedKoopas* redkoopas = dynamic_cast<RedKoopas*>(e->obj);
	if (GetState() == REDKOOPA_STATE_SHELL_RUNNING)
	{
		redkoopas->SetState(REDKOOPA_STATE_DIE_BYKOOPAS);
	}
}

void RedKoopas::OnCollisionWithRectangle(LPCOLLISIONEVENT e)
{
	CRectangle* rectangle = dynamic_cast<CRectangle*>(e->obj);
	float left, top, bottom, right;

	rectangle->GetBoundingBox(left, top, right, bottom);
	rectangleX = left;
	rectangleWidth = right;
}

void RedKoopas::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	float left,top, bottom, right;

	platform->GetBoundingBox(left, top, right, bottom);
	rectangleX = left;
	rectangleWidth = right;
}

void RedKoopas::OnCollisionWithPipe(LPCOLLISIONEVENT e)
{
	CPipe* pipe = dynamic_cast<CPipe*>(e->obj);
	float left, top, bottom, right;

	pipe->GetBoundingBox(left, top, right, bottom);
	rectangleX = left;
	rectangleWidth = right;
}

void RedKoopas::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	float left, top, bottom, right;

	brick->GetBoundingBox(left, top, right, bottom);
	rectangleX = left;
	rectangleWidth = right;

	if (e->nx != 0)
	{
		if (GetState() == REDKOOPA_STATE_SHELL_RUNNING && brick->Isbreak())
		{
			brick->SetState(BRICK_STATE_BREAK);
		}
	}

}

void RedKoopas::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	QuestionBrick* questionBrick = dynamic_cast<QuestionBrick*>(e->obj);
	if (questionBrick->GetState() == QUESTION_BRICK_STATE_STATIC && GetState() == KOOPA_STATE_SHELL_RUNNING)
	{
		questionBrick->SetState(QUESTION_BRICK_STATE_BOUNCED);
	}
}

void RedKoopas::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{	
	Mushroom* mushroom = dynamic_cast<Mushroom*>(e->obj);

	if(state = REDKOOPA_STATE_SHELL_RUNNING)
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


