#include "Pipe.h"



void CPipe::Render()
{
	CSprites* s = CSprites::GetInstance();

	s->Get(ID_SPRITE_PIPE)->Draw(x + PIPE_WIDTH / 2, y + PIPE_HIGHT / 2);
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + PIPE_WIDTH;
	b = t + PIPE_HIGHT;
}