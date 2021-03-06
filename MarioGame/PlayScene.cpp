#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Rectangle.h"
#include "Pipe.h"
#include "Koopa.h"
#include "DCoin.h"
#include "QuestionBrick.h"
#include "Mushroom.h"
#include "Spawn.h"
#include "RedKoopas.h"
#include "LandScape.h"
#include "Pbutton.h"
#include "FireBall.h"
#include "BoneKoopas.h"
#include "DeathBall.h"
#include "Lava.h"
#include "Thorn.h"
#include "Boss.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (std::size_t i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y); break;
	case OBJECT_TYPE_WINGGOOMBA: obj = new CGoomba(x, y, WINGGOOMBA_STATE_WALKING); break;
	case OBJECT_TYPE_KOOPAS: obj = new Koopa(x, y); break;
	case OBJECT_TYPE_REDKOOPAS: obj = new RedKoopas(x, y); break;
	case OBJECT_TYPE_BONEKOOPAS: obj = new BoneKoopas(x, y); break;
	case OBJECT_TYPE_DEATHBALL: obj = new DeathBall(x, y); break;
	case OBJECT_TYPE_LAVA: obj = new Lava(x, y); break;
	case OBJECT_TYPE_THORN: obj = new Thorn(x, y); break;

	case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
	case OBJECT_TYPE_BRICK_BREAK: obj = new CBrick(x, y, true); break;
	case OBJECT_TYPE_QUESTION_BRICK: obj = new QuestionBrick(x, y); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;
	case OBJECT_TYPE_DCOIN: obj = new DCoin(x, y); break;
	case OBJECT_TYPE_D1COIN: obj = new D1Coin(x, y); break;
	case OBJECT_TYPE_MUSHROOM: obj = new Mushroom(x, y); break;
	case OBJECT_TYPE_PBUTTON: obj = new Pbutton(x, y); break;
	case OBJECT_TYPE_FIREBALL: obj = new FireBall(x, y); break;
	case OBJECT_TYPE_BOSS: obj = new Boss(x, y); break;
	case OBJECT_TYPE_FIREBALL_DELAY: obj = new FireBall(x, y, true); break;
	//case OBJECT_TYPE_POWERBAR: obj = new PowerBar(x, y); break;

	case OBJECT_TYPE_PIPE: 
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int sprite_id = atoi(tokens[5].c_str());

		obj = new CPipe(x, y, cell_width, cell_height, sprite_id); 
		break;
	}
	case OBJECT_TYPE_LANDSCAPE:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int sprite_id = atoi(tokens[5].c_str());

		obj = new LandScape(x, y, cell_width, cell_height, sprite_id);
		break;
	}

	case OBJECT_TYPE_RECTANGLE:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int sprite_id = atoi(tokens[5].c_str());
		obj = new CRectangle(x, y, cell_width, cell_height, sprite_id);

		break;
	}

	case OBJECT_TYPE_SPAWN:
	{
		
		vector<LPGAMEOBJECT> objectsSpawn;

		CGameObject* objSPawn = NULL;
		for (std::size_t i = 3; i < tokens.size()-1;)
		{
			int typetype = (int)atof(tokens[i].c_str());
			float xxx = (float)atof(tokens[i+1].c_str());
			float yyy = (float)atof(tokens[i+2].c_str());
			switch (typetype)
			{
			case OBJECT_TYPE_GOOMBA: objSPawn = new CGoomba(xxx, yyy); break;
			case OBJECT_TYPE_WINGGOOMBA: objSPawn = new CGoomba(xxx, yyy, WINGGOOMBA_STATE_WALKING); break;
			case OBJECT_TYPE_KOOPAS: objSPawn = new Koopa(xxx, yyy); break;
			case OBJECT_TYPE_REDKOOPAS: objSPawn = new RedKoopas(xxx, yyy); break;
			case OBJECT_TYPE_BOSS: objSPawn = new Boss(xxx, yyy); break;
			}
			objectsSpawn.push_back(objSPawn);

			i += 3;

		}	
		obj = new Spawn(x, y, objectsSpawn);
		break;
	}

	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		break;
	}
	case OBJECT_TYPE_PORTAL_REWARD:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id, true);
		break;
	}
	


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void LoadPawn()
{

}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}


void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;
	// Update camera to follow mario
	float cx, cy;
	float xx, yy;
	player->GetPosition(cx, cy);
	player->GetPosition(xx, yy);


	CGame* game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2.0f;
	cy -= game->GetBackBufferHeight() / 2.0f;

	if (id == 2)
	{
		if (cx < 0) cx = 0;
		if (cx > 2254) cx = 2254;

		if (yy > 400)
			CGame::GetInstance()->SetCamPos(cx, 460);
		else
			CGame::GetInstance()->SetCamPos(cx, 0.0f/*cy*/);

		PurgeDeletedObjects();
		return;
	}
	if (id == 3 || id == 4) //map
	{
		CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
		PurgeDeletedObjects();
		return;
	}

	if (cx < 0) cx = 0;
	if (cx > 2700) player->SetPosition(2700.0f + game->GetBackBufferWidth() / 2.0f, yy);
	if (cy < -250) cy = -250;
	if (cy > 0) cy = 0;


	if (dynamic_cast<CMario*>(player)->IsInHiddenZone())
		CGame::GetInstance()->SetCamPos(HIDDEN_ZONE_X - 32, HIDDEN_ZONE_Y + 15);
	else CGame::GetInstance()->SetCamPos(cx, cy);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (std::size_t i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CPlayScene::Unload()
{
	for (std::size_t i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

void CPlayScene::AddObject(CGameObject* object)
{
	objects.push_back(object);
}


void CPlayScene::AddObjectAt(CGameObject* object, int position)
{
	std::vector<LPGAMEOBJECT>::iterator it;

	objects.insert(objects.begin() + position, object);
}

CGameObject* CPlayScene::getObject(int index)
{
	return objects[index];
}

int CPlayScene::NumberObject()
{
	return objects.size();
}


bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}