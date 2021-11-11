#pragma once

#include "GameObject.h"

//#define PIPE_WIDTH 31
//#define PIPE_HIGHT 47
//#define ID_SPRITE_PIPE 80000
class CPipe : public  CGameObject
{
	float width;
	float height;
	int idSprite;


public:
	CPipe(float x, float y, float cell_width, float cell_height, int idSprite) : CGameObject(x, y) 
	{
		width = cell_width;
		height = cell_height;
		this->idSprite = idSprite;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

