#pragma once

#include "GameObject.h"
#include "Mario.h"

/*
	Object that triggers scene switching
*/

#define HIDDEN_ZONE_Y 250
#define HIDDEN_ZONE_X 2460
#define EXIT_HIDDEN_ZONE_Y 120
#define EXIT_HIDDEN_ZONE_X 2445

class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 
	float width;
	float height; 

public:
	CPortal(float l, float t, float r, float b, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 0; }

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
