#include "Rectangle.h"

void CRectangle::Render()
{
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteId)->Draw(x , y);
}

void CRectangle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - hight / 2;
	r = l + width;
	b = t + hight;
}
