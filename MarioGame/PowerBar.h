#pragma once
#include "GameObject.h"




#define ID_ANI_SPRITE_POWER_BAR_EMPTY 120121
#define ID_ANI_SPRITE_POWER_BAR_FILLED 120122
#define ID_ANI_POWER_BAR_MAX 120120

class PowerBar : public  CGameObject
{
	virtual int IsBlocking() { return 0; }
	int power;

public:
	PowerBar(float x, float y) : CGameObject(x, y)
	{
		power = 0;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - 13.f / 2;
		t = y - 6.f / 2;
		r = l + 13;
		b = t + 6;
	}
};

