#pragma once
#include "GameObject.h"


#define ID_ANI_RECTANGLE 55559
class CRectangle : public CGameObject
{
private:
	float width;
	float hight;
	int spriteId;

public:
	CRectangle(float x, float y, float width, float hight, int id) : CGameObject(x, y)
	{
		this->width = width;
		this->hight = hight;
		spriteId = id;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void DirectBlocking(int& left, int& top, int& right, int& bottom)
	{
		left = right = bottom = 0;
		top = 1;
	}
};

