#pragma once

#include "GameObject.h"

#define ID_SPRITE_WELCOME_1 171001
#define ID_SPRITE_WELCOME_2 171002
#define ID_SPRITE_WELCOME_3 171003
#define ID_SPRITE_WELCOME_4 171000

#define WELCOME_SPEED 0.1f

class LandScape : public  CGameObject
{
	float width;
	float height;
	int idSprite;

	virtual int IsBlocking() { return 0; }

public:
	LandScape(float x, float y, float cell_width, float cell_height, int idSprite) : CGameObject(x, y)
	{
		width = cell_width;
		height = cell_height;
		this->idSprite = idSprite;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		if (idSprite == ID_SPRITE_WELCOME_1)
		{
			y -= WELCOME_SPEED * dt;
			if (y < -120)
			{
				CGame::GetInstance()->GetCurrentScene()->AddObject(new LandScape(x, y, 323, 135, ID_SPRITE_WELCOME_3));
				this->Delete();
			}
				
		}
		if (idSprite == ID_SPRITE_WELCOME_3)
		{
			if (y < 60)
				y += WELCOME_SPEED * dt;
			if (y >= 60)
			{
				CGame::GetInstance()->GetCurrentScene()->AddObject(new LandScape(150, 110, 322, 224, ID_SPRITE_WELCOME_4));

				CGame::GetInstance()->GetCurrentScene()->AddObject(new Koopa(x + 300, y));
				CGame::GetInstance()->GetCurrentScene()->AddObject(new Koopa(x + 330, y));
				CGame::GetInstance()->GetCurrentScene()->AddObject(new Koopa(x + 360, y));

				CGame::GetInstance()->GetCurrentScene()->AddObject(new CGoomba(x + 100, y));
				CGame::GetInstance()->GetCurrentScene()->AddObject(new CGoomba(x + 250, y, WINGGOOMBA_STATE_WALKING));
				CGame::GetInstance()->GetCurrentScene()->AddObject(new Koopa(x + 150, y - 2000));
				CGame::GetInstance()->GetCurrentScene()->AddObject(new RedKoopas(x + 10, y));
				this->Delete();
			}
				
		}
			
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(idSprite)->Draw(x, y);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - width / 2;
		t = y - height / 2;
		r = l + width;
		b = t + height;
	}
};