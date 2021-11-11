#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_QUESTION_BRICK 7000
#define ID_ANI_QUESTION_BRICK_BOUNCED 7100

#define QUESTION_BRICK_BBOX_WIDTH 16
#define QUESTION_BRICK_BBOX_HEIGHT 16

#define QUESTION_BRICK_HEIGHT_BOUNCE 7
#define QUESTION_BRICK_SPEED_BOUNCE 0.01f

#define QUESTION_BRICK_STATE_BOUNCE 15
#define QUESTION_BRICK_STATE_STATIC 14
#define QUESTION_BRICK_STATE_BOUNCED 13


class QuestionBrick : public CGameObject {

	float ay;
	float y_initial;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

public:
    QuestionBrick(float x, float y) : CGameObject(x, y)
    {
        y_initial = y;
        ay = 0;
        SetState(QUESTION_BRICK_STATE_STATIC);
    }
    virtual void OnNoCollision(DWORD dt);
    virtual void SetState(int state);
    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b);
};


