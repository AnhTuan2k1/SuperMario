#pragma once

#include "GameObject.h"

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