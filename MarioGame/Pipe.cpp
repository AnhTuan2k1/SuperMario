#include "Pipe.h"



void CPipe::Render()
{
	CSprites* s = CSprites::GetInstance();

	s->Get(idSprite)->Draw(x , y );
	//RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - height / 2;
	r = l + width;
	b = t + height;
}