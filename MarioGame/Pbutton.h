#pragma once

#include "GameObject.h"

#define ID_SPRITE_PBUTTON_BOUNCED 28001
#define ID_SPRITE_PBUTTON_ACTIVED 28002
#define ID_ANI_PBUTTON_BRICK 10000

#define BRICK_BBOX_WIDTH 15
#define BRICK_BBOX_HEIGHT 15

#define PBUTTON_BOUNCED_BBOX_WIDTH 15
#define PBUTTON_BOUNCED_BBOX_HEIGHT 27

#define PBUTTON_ACTIVED_BBOX_WIDTH 15
#define PBUTTON_ACTIVED_BBOX_HEIGHT 18

#define PBUTTON_STATE_BOUNCED 154
#define BRICK_STATE_ACTIVED 144
#define PBUTTON_STATE_BRICK 133

#define DCOIN_BOUNCE_TIMES 5
#define PBUTTON_TRANSFORM_TIME 7000

class Pbutton : public CGameObject
{
	ULONGLONG transform_start;
	virtual void OnNoCollision(DWORD dt);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
public:
    Pbutton(float x, float y) : CGameObject(x, y)
    {
		transform_start = -1;
		SetState(PBUTTON_STATE_BRICK);
    }
	virtual void SetState(int state);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void TransformBricktoCoin();
	void TransformCointoBrick();
};

