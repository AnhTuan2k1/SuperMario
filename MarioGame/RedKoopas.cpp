#include "RedKoopas.h"

#include "Goomba.h"
#include "Mario.h"
#include "Koopa.h"
#include "Rectangle.h"

void RedKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == REDKOOPA_STATE_SHELL)
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
	CGameObject::SetState(state);
	switch (state)
	{
	case REDKOOPA_STATE_SHELL:
		hide_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		DebugOut(L">>> RedKoopas 1 >>> \n");
		break;
	case REDKOOPA_STATE_WALKING_LEFT:
		vx = -KOOPA_WALKING_SPEED;
		DebugOut(L">>> RedKoopas 2 >>> \n");
		break;
	case REDKOOPA_STATE_WALKING_RIGHT:
		DebugOut(L">>> RedKoopas 3 >>> \n");
		vx = KOOPA_WALKING_SPEED;
		break;
	case REDKOOPA_STATE_SHELL_RUNNING:
		DebugOut(L">>> RedKoopas 4 >>> \n");
		vx = -KOOPA_RUNING_SPEED;
		break;
	case REDKOOPA_STATE_DIE_BYKOOPAS:
		DebugOut(L">>> RedKoopas 5 >>> \n");
		vy = -KOOPA_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		ay = KOOPA_GRAVITY;
		break;
	}
}

void RedKoopas::SetState(int state, int direct)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case REDKOOPA_STATE_SHELL:
		hide_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case REDKOOPA_STATE_WALKING_LEFT:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case REDKOOPA_STATE_WALKING_RIGHT:
		vx = KOOPA_WALKING_SPEED;
		break;
	case REDKOOPA_STATE_SHELL_RUNNING:
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

void RedKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == REDKOOPA_STATE_SHELL) && (GetTickCount64() - hide_start > KOOPA_SHELL_TIMEOUT))
	{
		this->ax = 0;
		this->ay = KOOPA_GRAVITY;
		hide_start = -1;
		SetState(REDKOOPA_STATE_WALKING_LEFT);
		return;
	}

	//reverse direct if reaching the rectangle's end. 
	if(state == REDKOOPA_STATE_WALKING_RIGHT || state == REDKOOPA_STATE_WALKING_LEFT)

		if (vx < 0)
		{
			if (x < rectangleX - rectangleWidth/2)
			{
				SetState(REDKOOPA_STATE_WALKING_RIGHT);
				DebugOut(L">>> RedKoopas 6 >>> \n");
			}
		}
		else
		{
			if (x > rectangleX + rectangleWidth/2)
			{
				SetState(REDKOOPA_STATE_WALKING_LEFT);
				DebugOut(L">>> RedKoopas 7 >>> \n");
			}
		}
	

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void RedKoopas::Render()
{
	int aniId = ID_ANI_REDKOOPA_WALKING_LEFT;
	if (state == REDKOOPA_STATE_SHELL)
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
	else if (dynamic_cast<Koopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CMario*>(e->obj)) 
		OnCollisionWithMario(e);
	else if (dynamic_cast<RedKoopas*>(e->obj)) 
		OnCollisionWithRedKoopa(e);
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
	if (dynamic_cast<CRectangle*>(e->obj))
	{
		CRectangle* rectangle = dynamic_cast<CRectangle*>(e->obj);
		rectangleX = rectangle->getX();
		rectangleWidth = rectangle->getWidth();
	}	
}


