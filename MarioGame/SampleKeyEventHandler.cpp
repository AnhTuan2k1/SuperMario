#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"
#include "Portal.h"
#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	if (mario->GetState() == MARIO_STATE_HIT) return;

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		float x, y;
		mario->GetPosition(x, y);
		CPortal::AccessMoneyZone(x,y);
		break;
	case DIK_UP:
		float xx, yy;
		mario->GetPosition(xx, yy);
		CPortal::Switch(xx, yy);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_FLY);
		mario->SetState(MARIO_STATE_JUMP);
		mario->StartSlowdown();
		float xxx, yyy;
		mario->GetPosition(xxx, yyy);
		CPortal::ChooseScene(xxx, yyy);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACCOON);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	case DIK_A: 
		if (mario->GetLevel() == 3 && mario->GetState() != MARIO_STATE_HIT)
			mario->SetState(MARIO_STATE_HIT);
		break;

	case DIK_D:
		if (mario->IsHoldingShell())
			mario->DropShell();
		else mario->GetShell();
		break;

	case DIK_RETURN:
		float xxxx, yyyy;
		mario->GetPosition(xxxx, yyyy);
		CPortal::ChooseScene(xxxx, yyyy);
		break;

	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		if (CGame::GetInstance()->GetCurrentSceneID() == 3)
			mario->SetState(MARIO_STATE_DOWN_RELEASE);
		break;
		break;
	case DIK_A:
		mario->EndLoadPower();
		break;
	case DIK_RIGHT:
		if (mario->GetIsLoadingPower()) mario->EndLoadPower();
		break;
	case DIK_LEFT:
		if (mario->GetIsLoadingPower()) mario->EndLoadPower();
		break;

	case DIK_UP:
		if (CGame::GetInstance()->GetCurrentSceneID() == 3)
			mario->SetState(MARIO_STATE_UP_RELEASE);
		break;

	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	
	if (CGame::GetInstance()->GetCurrentSceneID() == 3)
	{
		if (game->IsKeyDown(DIK_UP))
		{
			mario->SetState(MARIO_STATE_UP);
		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			mario->SetState(MARIO_STATE_DOWN);
		}
	}

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			mario->StartLoadPower();
		}
			
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
		{			
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
			mario->StartLoadPower();
		}
			
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else if (mario->GetState() == MARIO_STATE_HIT) return;
	else
		mario->SetState(MARIO_STATE_IDLE);
}