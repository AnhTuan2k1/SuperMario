#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20


#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_WINGGOOMBA	8
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_DCOIN 9
#define OBJECT_TYPE_D1COIN 13
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_RECTANGLE 6
#define OBJECT_TYPE_PIPE 7
#define OBJECT_TYPE_QUESTION_BRICK	10
#define OBJECT_TYPE_MUSHROOM	11
#define OBJECT_TYPE_SPAWN	12
#define OBJECT_TYPE_REDKOOPAS 14
#define OBJECT_TYPE_BRICK_BREAK 15
#define OBJECT_TYPE_LANDSCAPE 16
#define OBJECT_TYPE_PBUTTON 17
#define OBJECT_TYPE_POWERBAR 18
#define OBJECT_TYPE_FIREBALL 19
#define OBJECT_TYPE_FIREBALL_DELAY 20
#define OBJECT_TYPE_BONEKOOPAS 21
#define OBJECT_TYPE_DEATHBALL 22
#define OBJECT_TYPE_LAVA 23
#define OBJECT_TYPE_THORN 24
#define OBJECT_TYPE_BOSS 25
#define OBJECT_TYPE_PORTAL	50
#define OBJECT_TYPE_PORTAL_REWARD	51

#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)
#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)
#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_HOLD (ID_SPRITE_MARIO + 700)
#define ID_SPRITE_MARIO_HOLD_WALK (ID_SPRITE_MARIO_HOLD + 20)
#define ID_SPRITE_MARIO_HOLD_WALK_LEFT (ID_SPRITE_MARIO_HOLD_WALK + 1)
#define ID_SPRITE_MARIO_HOLD_WALK_RIGHT (ID_SPRITE_MARIO_HOLD_WALK + 5)
#define ID_SPRITE_MARIO_HOLD_IDLE (ID_SPRITE_MARIO + 10)
#define ID_SPRITE_MARIO_HOLD_IDLE_LEFT (ID_SPRITE_MARIO_HOLD_IDLE + 1)
#define ID_SPRITE_MARIO_HOLD_IDLE_RIGHT (ID_SPRITE_MARIO_HOLD_IDLE + 5)




#define ID_SPRITE_MARIO_RACCOON (ID_SPRITE_MARIO + 4000)
#define ID_SPRITE_MARIO_RACCOON_IDLE (ID_SPRITE_MARIO_RACCOON + 100)
#define ID_SPRITE_MARIO_RACCOON_IDLE_LEFT (ID_SPRITE_MARIO_RACCOON_IDLE + 10)
#define ID_SPRITE_MARIO_RACCOON_IDLE_RIGHT (ID_SPRITE_MARIO_RACCOON_IDLE + 20)

#define ID_SPRITE_MARIO_RACCOON_WALKING (ID_SPRITE_MARIO_RACCOON + 200)
#define ID_SPRITE_MARIO_RACCOON_WALKING_LEFT (ID_SPRITE_MARIO_RACCOON_WALKING + 10)
#define ID_SPRITE_MARIO_RACCOON_WALKING_RIGHT (ID_SPRITE_MARIO_RACCOON_WALKING + 20)
#define ID_SPRITE_MARIO_RACCOON_RUNNING (ID_SPRITE_MARIO_RACCOON + 300)
#define ID_SPRITE_MARIO_RACCOON_RUNNING_LEFT (ID_SPRITE_MARIO_RACCOON_RUNNING + 10)
#define ID_SPRITE_MARIO_RACCOON_RUNNING_RIGHT (ID_SPRITE_MARIO_RACCOON_RUNNING + 20)
#define ID_SPRITE_MARIO_RACCOON_JUMP (ID_SPRITE_MARIO_RACCOON + 400)
#define ID_SPRITE_MARIO_RACCOON_JUMP_WALK (ID_SPRITE_MARIO_RACCOON_JUMP + 10)
#define ID_SPRITE_MARIO_RACCOON_JUMP_WALK_LEFT (ID_SPRITE_MARIO_RACCOON_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_RACCOON_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_RACCOON_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_RACCOON_JUMP_RUN (ID_SPRITE_MARIO_RACCOON_JUMP + 20)
#define ID_SPRITE_MARIO_RACCOON_JUMP_RUN_LEFT (ID_SPRITE_MARIO_RACCOON_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_RACCOON_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_RACCOON_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_RACCOON_SIT (ID_SPRITE_MARIO_RACCOON + 500)
#define ID_SPRITE_MARIO_RACCOON_SIT_LEFT (ID_SPRITE_MARIO_RACCOON_SIT + 10)
#define ID_SPRITE_MARIO_RACCOON_SIT_RIGHT (ID_SPRITE_MARIO_RACCOON_SIT + 20)
#define ID_SPRITE_MARIO_RACCOON_BRACE (ID_SPRITE_MARIO_RACCOON + 600)
#define ID_SPRITE_MARIO_RACCOON_BRACE_LEFT (ID_SPRITE_MARIO_RACCOON_BRACE + 10)
#define ID_SPRITE_MARIO_RACCOON_BRACE_RIGHT (ID_SPRITE_MARIO_RACCOON_BRACE + 20)

#define ID_SPRITE_MARIO_RACCOON_HOLD (ID_SPRITE_MARIO_RACCOON + 700)

#define ID_SPRITE_MARIO_RACCOON_HOLD_WALK (ID_SPRITE_MARIO_RACCOON + 10)
#define ID_SPRITE_MARIO_RACCOON_HOLD_WALK_LEFT (ID_SPRITE_MARIO_RACCOON_HOLD_WALK + 1)
#define ID_SPRITE_MARIO_RACCOON_HOLD_WALK_RIGHT (ID_SPRITE_MARIO_RACCOON_HOLD_WALK + 7)
#define ID_SPRITE_MARIO_RACCOON_HOLD_IDLE (ID_SPRITE_MARIO_RACCOON_HOLD + 20)
#define ID_SPRITE_MARIO_RACCOON_HOLD_IDLE_LEFT (ID_SPRITE_MARIO_RACCOON_HOLD_IDLE + 1)
#define ID_SPRITE_MARIO_RACCOON_HOLD_IDLE_RIGHT (ID_SPRITE_MARIO_RACCOON_HOLD_IDLE + 2)

#define ID_SPRITE_MARIO_RACCOON_FALL (ID_SPRITE_MARIO_RACCOON + 800)
#define ID_SPRITE_MARIO_RACCOON_FALL_LEFT (ID_SPRITE_MARIO_RACCOON_FALL + 10)
#define ID_SPRITE_MARIO_RACCOON_FALL_RIGHT (ID_SPRITE_MARIO_RACCOON_FALL + 20)

#define ID_SPRITE_MARIO_RACCOON_HIT (ID_SPRITE_MARIO_RACCOON + 800)
#define ID_SPRITE_MARIO_RACCOON_HIT_LEFT (ID_SPRITE_MARIO_RACCOON_FLY + 60)
#define ID_SPRITE_MARIO_RACCOON_HIT_RIGHT (ID_SPRITE_MARIO_RACCOON_FLY + 70)

#define ID_SPRITE_MARIO_RACCOON_FLY (ID_SPRITE_MARIO_RACCOON + 900)
#define ID_SPRITE_MARIO_RACCOON_FLY_UP (ID_SPRITE_MARIO_RACCOON_FLY + 10)
#define ID_SPRITE_MARIO_RACCOON_FLY_DOWN (ID_SPRITE_MARIO_RACCOON_FLY + 20)

#define ID_SPRITE_MARIO_RACCOON_FLY_UP_RIGHT (ID_SPRITE_MARIO_RACCOON_FLY_UP + 2)
#define ID_SPRITE_MARIO_RACCOON_FLY_UP_LEFT (ID_SPRITE_MARIO_RACCOON_FLY_UP + 6)
#define ID_SPRITE_MARIO_RACCOON_FLY_DOWN_RIGHT (ID_SPRITE_MARIO_RACCOON_FLY_DOWN + 2)
#define ID_SPRITE_MARIO_RACCOON_FLY_DOWN_LEFT (ID_SPRITE_MARIO_RACCOON_FLY_DOWN + 6)




// tail
#define ID_SPRITE_TAIL (ID_SPRITE_MARIO + 5000)
#define ID_SPRITE_TAIL_IDLE (ID_SPRITE_TAIL + 100)
#define ID_SPRITE_TAIL_IDLE_LEFT (ID_SPRITE_TAIL_IDLE + 10)
#define ID_SPRITE_TAIL_IDLE_RIGHT (ID_SPRITE_TAIL_IDLE + 20)

#define ID_SPRITE_TAIL_WALKING (ID_SPRITE_TAIL + 200)
#define ID_SPRITE_TAIL_WALKING_LEFT (ID_SPRITE_TAIL_WALKING + 10)
#define ID_SPRITE_TAIL_WALKING_RIGHT (ID_SPRITE_TAIL_WALKING + 20)
#define ID_SPRITE_TAIL_RUNNING (ID_SPRITE_TAIL + 300)
#define ID_SPRITE_TAIL_RUNNING_LEFT (ID_SPRITE_TAIL_RUNNING + 10)
#define ID_SPRITE_TAIL_RUNNING_RIGHT (ID_SPRITE_TAIL_RUNNING + 20)
#define ID_SPRITE_TAIL_JUMP (ID_SPRITE_TAIL + 400)
#define ID_SPRITE_TAIL_JUMP_WALK (ID_SPRITE_TAIL_JUMP + 10)
#define ID_SPRITE_TAIL_JUMP_WALK_LEFT (ID_SPRITE_TAIL_JUMP_WALK + 2)
#define ID_SPRITE_TAIL_JUMP_WALK_RIGHT (ID_SPRITE_TAIL_JUMP_WALK + 6)
#define ID_SPRITE_TAIL_JUMP_RUN (ID_SPRITE_TAIL_JUMP + 20)
#define ID_SPRITE_TAIL_JUMP_RUN_LEFT (ID_SPRITE_TAIL_JUMP_RUN + 2)
#define ID_SPRITE_TAIL_JUMP_RUN_RIGHT (ID_SPRITE_TAIL_JUMP_RUN + 6)
#define ID_SPRITE_TAIL_SIT (ID_SPRITE_TAIL + 500)
#define ID_SPRITE_TAIL_SIT_LEFT (ID_SPRITE_TAIL_SIT + 10)
#define ID_SPRITE_TAIL_SIT_RIGHT (ID_SPRITE_TAIL_SIT + 20)
#define ID_SPRITE_TAIL_BRACE (ID_SPRITE_TAIL + 600)
#define ID_SPRITE_TAIL_BRACE_LEFT (ID_SPRITE_TAIL_BRACE + 10)
#define ID_SPRITE_TAIL_BRACE_RIGHT (ID_SPRITE_TAIL_BRACE + 20)
#define ID_SPRITE_TAIL_HOLD (ID_SPRITE_TAIL + 700)
#define ID_SPRITE_TAIL_HOLD_LEFT (ID_SPRITE_TAIL_WALKING + 10)
#define ID_SPRITE_TAIL_HOLD_RIGHT (ID_SPRITE_TAIL_WALKING + 20)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

#define ID_SPRITE_MARIO_SMALL_HOLD (ID_SPRITE_MARIO_SMALL + 700)
#define ID_SPRITE_MARIO_SMALL_HOLD_WALK (ID_SPRITE_MARIO_SMALL_HOLD + 20)
#define ID_SPRITE_MARIO_SMALL_HOLD_WALK_LEFT (ID_SPRITE_MARIO_SMALL_HOLD_WALK + 1)
#define ID_SPRITE_MARIO_SMALL_HOLD_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_HOLD_WALK + 5)
#define ID_SPRITE_MARIO_SMALL_HOLD_IDLE (ID_SPRITE_MARIO_SMALL + 10)
#define ID_SPRITE_MARIO_SMALL_HOLD_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_HOLD_IDLE + 1)
#define ID_SPRITE_MARIO_SMALL_HOLD_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_HOLD_IDLE + 5)

#pragma endregion 

#define ID_SPRITE_YELLOW_BRICK_0 20000
#define ID_SPRITE_YELLOW_BRICK_1 21000
#define ID_SPRITE_YELLOW_BRICK_2 22000
#define ID_SPRITE_YELLOW_BRICK_3 23000
#define ID_SPRITE_YELLOW_BRICK_4 24000

#define ID_SPRITE_PBUTTON 28000

#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)
#define ID_SPRITE_WINGGOOMBA_WALK (ID_SPRITE_GOOMBA + 3000)

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)

#define ID_SPRITE_LAND 60000

#define ID_SPRITE_RECTANGLE 70000
#define ID_SPRITE_RECTANGLE_2 71000


#define ID_SPRITE_PIPE 80000

#define ID_SPRITE_KOOPA 90000
#define ID_SPRITE_KOOPA_WALK (ID_SPRITE_KOOPA + 1000)
#define ID_SPRITE_KOOPA_SHELL (ID_SPRITE_KOOPA + 2000)

#define ID_SPRITE_QUESTION_BRICK 100000
#define ID_SPRITE_QUESTION_BRICK_1 101000
#define ID_SPRITE_QUESTION_BRICK_2 102000
#define ID_SPRITE_QUESTION_BRICK_3 103000
#define ID_SPRITE_QUESTION_BRICK_4 104000

#define ID_SPRITE_RED_MUSHROOM 111000
#define ID_SPRITE_GREEN_MUSHROOM 112000
#define ID_SPRITE_HIDE_MUSHROOM 113000
#define ID_SPRITE_LEAF 114000

#define ID_SPRITE_SPAWN 12345

#define ID_SPRITE_LANSCAPE 120000

#define ID_SPRITE_TRAP 130000
//#define ID_SPRITE_FIREBALL 131000
//#define ID_SPRITE_DEATHBALL 132000
//#define ID_SPRITE_THORN 133000
//#define ID_SPRITE_LAVA 134000

#define ID_SPRITE_BOSS 140000
#define ID_SPRITE_BONEKOOPAS 150000