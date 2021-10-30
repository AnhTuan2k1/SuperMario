#pragma once

#include "GameObject.h"

#define PIPE_WIDTH 27
#define PIPE_HIGHT 39
#define ID_SPRITE_PIPE 80000
class CPipe : public  CGameObject
{
public:
	CPipe(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

