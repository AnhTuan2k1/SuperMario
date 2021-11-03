#pragma once
#include "Coin.h"

#define DCOIN_HEIGHT_BOUNCE 48
#define DCOIN_BOUNCE_TIMEOUT 300
#define DCOIN_BOUNCE_TIMES 10
#define DCOIN_SPEED_BOUNCE 0.01f

#define DCOIN_STATE_BOUNCE 15
#define DCOIN_STATE_STATIC 14

class DCoin :
    public CCoin
{
    float ay;
    ULONGLONG bounce_start;
    int bounce_times;
    float y_initial;
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

public:
    DCoin(float x, float y, int times = DCOIN_BOUNCE_TIMES) : CCoin(x, y)
    { 
        y_initial = y;
        ay = 0;
        bounce_start = -1; 
        bounce_times = times;
        SetState(DCOIN_STATE_STATIC);
    }
    virtual void OnNoCollision(DWORD dt);
    virtual void SetState(int state);
};

