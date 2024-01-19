#if !defined( GAME_H )
#define GAME_H

#include "common.h"
#include "enums.h"

typedef struct gmWindow_t gmWindow_t;
typedef struct gmClock_t gmClock_t;
typedef struct gmInputState_t gmInputState_t;
typedef struct gmInputHandler_t gmInputHandler_t;
typedef struct gmRenderer_t gmRenderer_t;
typedef struct gmPhysics_t gmPhysics_t;
typedef struct gmMenus_t gmMenus_t;
typedef struct gmMap_t gmMap_t;
typedef struct gmBattle_t gmBattle_t;
typedef struct gmCharacter_t gmCharacter_t;

typedef struct gmGame_t
{
   gmWindow_t* window;
   gmClock_t* clock;
   gmInputState_t* inputState;
   gmInputHandler_t* inputHandler;
   gmRenderer_t* renderer;
   gmPhysics_t* physics;

   sfBool showDiagnostics;
   
   gmMenus_t* menus;
   gmMap_t* map;
   gmBattle_t* battle;

   gmCharacter_t* player;

   sfBool cheatNoClip;
   sfBool cheatNoEncounters;

   gmGameState_t state;
}
gmGame_t;

gmGame_t* gmGame_Create();
void gmGame_Destroy( gmGame_t* game );
void gmGame_Run( gmGame_t* game );
void gmGame_Close( gmGame_t* game );
void gmGame_ShowDebugMessage( gmGame_t* game, const char* msg );
void gmGame_SetState( gmGame_t* game, gmGameState_t state );
void gmGame_ExecuteMenuCommand( gmGame_t* game, gmMenuCommand_t command );
void gmGame_RollEncounter( gmGame_t* game, uint32_t mapTileIndex );
void gmGame_StartEncounter( gmGame_t* game );
void gmGame_EndEncounter( gmGame_t* game );

// game_loader.c
void gmGame_LoadData( gmGame_t* game );

#endif // GAME_H
