#include "Rectangle.h"

void CRectangle::Render()
{
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteId)->Draw(x + width / 2, y + hight / 2);
}

void CRectangle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + width;
	b = t + hight;
}
