//#include "PowerBar.h"
//#include "Mario.h"
//
//void PowerBar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	float cx, cy;
//	
//	CGame::GetInstance()->GetCamPos(cx,cy);
//
//	CGame* game = CGame::GetInstance();
//	cy += game->GetBackBufferHeight() - 5;
//	cx += 20;
//
//	x = cx;
//	y = cy;
//
//
//	for (int i = 0; i < CGame::GetInstance()->GetCurrentScene()->NumberObject(); i++)
//	{
//		if (dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->getObject(i)))
//		{
//			power = dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->getObject(i))->GetPower();
//		}
//	}
//
//
//	CCollision::GetInstance()->Process(this, dt, coObjects);
//}
//
//void PowerBar::Render()
//{
//	//CAnimations* animations = CAnimations::GetInstance();
//
//
//	//if (power == MARIO_POWER_MAX)
//	//{
//	//	for (int i = 0; i < power; i++)
//	//	{
//	//		animations->Get(ID_ANI_POWER_BAR_MAX)->Render(x + i * 13, y);
//	//	}
//	//}
//	//else
//	//{
//	//	for (int i = 0; i < MARIO_POWER_MAX; i++)
//	//	{
//	//		animations->Get(ID_ANI_SPRITE_POWER_BAR_EMPTY)->Render(x + i * 13, y);
//	//	}
//
//	//	for (int i = 0; i < power; i++)
//	//	{
//	//		animations->Get(ID_ANI_SPRITE_POWER_BAR_FILLED)->Render(x + i * 13, y);
//	//	}
//	//}
//}
