#pragma once

#include "GameObject.h"
#include "Mario.h"
#include "Thorn.h"

/*
	Object that triggers scene switching
*/

#define HIDDEN_ZONE_Y 250
#define HIDDEN_ZONE_X 2460
#define EXIT_HIDDEN_ZONE_Y 120
#define EXIT_HIDDEN_ZONE_X 2445
#define A_ZONE_Y 600
#define A_ZONE_X 1180
#define B_ZONE_Y 130
#define B_ZONE_X 1970

//sprites in landscape
#define ID_SPRITE_MUSHROOM_REWARD 123001
#define ID_SPRITE_FLOWER_REWARD 123002
#define ID_SPRITE_STAR_REWARD 123003
#define ID_ANI_REWARD 123000

#define REWARD_BBOX_WIDTH 15
#define REWARD_BBOX_HEIGHT 15

class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 
	float width;
	float height;
	bool isSwitchScene;

public:
	CPortal(float l, float t, float r, float b, int scene_id);
	CPortal(float l, float t, float r, float b, int scene_id, bool isreward);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 0; }
	int IsSwitchScene() { return isSwitchScene; }

	static void AccessMoneyZone(float x, float y)
	{
		if (x > 2375 && x < 2390 && y < -190 && y > -220)
		{
			for (int i = 0; i < CGame::GetInstance()->GetCurrentScene()->NumberObject(); i++)
			{
				if (dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->getObject(i)))
				{
					CMario* mario = dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->getObject(i));
					mario->SetPosition(HIDDEN_ZONE_X, HIDDEN_ZONE_Y);
					mario->AccessHiddenZone();
				}
			}
		}
	}

	static void SwitchToA(float x, float y)
	{
		if (x > 1740 && x < 1760 && y < 165 && y > 145)
		{
			for (int i = 0; i < CGame::GetInstance()->GetCurrentScene()->NumberObject(); i++)
			{
				if (dynamic_cast<Thorn*>(CGame::GetInstance()->GetCurrentScene()->getObject(i)))
				{
					Thorn* thorn = dynamic_cast<Thorn*>(CGame::GetInstance()->GetCurrentScene()->getObject(i));
					thorn->SetState(THORN_STATE_MOVE);
				}
		
				else if (dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->getObject(i)))
				{
					CMario* mario = dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->getObject(i));
					mario->SetPosition(A_ZONE_X, A_ZONE_Y);
				}
				
			}
		}
	}
	static void SwitchToB(float x, float y)
	{
		if (x > 1635 && x < 1650 && y < 650 && y > 620)
		{
			for (int i = 0; i < CGame::GetInstance()->GetCurrentScene()->NumberObject(); i++)
			{
				if (dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->getObject(i)))
				{
					CMario* mario = dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->getObject(i));
					mario->SetPosition(B_ZONE_X, B_ZONE_Y);
				}
			}
		}
	}

	static void Switch(float x, float y)
	{
		if (CGame::GetInstance()->GetCurrentSceneID() == 2)
		{
			SwitchToA(x, y);
			SwitchToB(x, y);
		}
	}



	//float x, y;
		//mario->GetPosition(x, y);

	//if (x > 2375 && x < 2390 && y < -190 && y > -220)
	//{
	//	for (int i = 0; i < CGame::GetInstance()->GetCurrentScene()->NumberObject(); i++)
	//	{
	//		if (dynamic_cast<CPortal*>(CGame::GetInstance()->GetCurrentScene()->getObject(i)))
	//		{
	//			CPortal* portal = dynamic_cast<CPortal*>(CGame::GetInstance()->GetCurrentScene()->getObject(i));
	//			if (portal->GetSceneId() == 2)
	//			{
	//				CGame::GetInstance()->InitiateSwitchScene(portal->GetSceneId());
	//			}

	//		}
	//	}
	//}
};
