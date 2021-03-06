#include "Spawn.h"
#include "Game.h"

void Spawn::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_SPRITE_SPAWN)->Draw(x, y);
	//RenderBoundingBox();
}

void Spawn::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - SPAWN_WIDTH / 2;
	top = y - SPAWN_HIGH / 2;
	right = left + SPAWN_WIDTH;
	bottom = top + SPAWN_HIGH;
}

void Spawn::CreateEnemies()
{
	if(objects.size() == 1) // Boss
		CGame::GetInstance()->GetCurrentScene()->AddObjectAt(objects[0], 10);
	else
	for (std::size_t i = 0; i < objects.size(); i++)
	{
		CGame::GetInstance()->GetCurrentScene()->AddObject(objects[i]);
	}
}

