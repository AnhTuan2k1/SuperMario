#pragma once
#include "GameObject.h"

#define SPAWN_HIGH 310
#define SPAWN_WIDTH 1
#define SPAWN_STATE_INITIALIZED 235
#define SPAWN_STATE_UNINITIALIZED 236
#define ID_SPRITE_SPAWN 12345
class Spawn : public CGameObject
{

	vector<LPGAMEOBJECT> objects;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }

public:
	Spawn(float x, float y, vector<LPGAMEOBJECT> objects)
	{
		this->x = x;
		this->y = 0;
		this->objects = objects;
	}
	CGameObject* getObjectAt(int index) { return objects[index]; }
	void Update(DWORD dt) {}
	virtual void Render();
	void CreateEnemies();
};

