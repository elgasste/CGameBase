#if !defined( GAME_H )
#define GAME_H

#include "common.h"

typedef struct gmWindow_t gmWindow_t;
typedef struct gmClock_t gmClock_t;
typedef struct gmInputState_t gmInputState_t;
typedef struct gmInputHandler_t gmInputHandler_t;
typedef struct gmRenderObjects_t gmRenderObjects_t;
typedef struct gmRenderStates_t gmRenderStates_t;
typedef struct gmRenderer_t gmRenderer_t;
typedef struct gmMap_t gmMap_t;
typedef struct gmEntity_t gmEntity_t;

typedef struct gmGame_t
{
   gmWindow_t* window;
   gmClock_t* clock;
   gmInputState_t* inputState;
   gmInputHandler_t* inputHandler;
   gmRenderObjects_t* renderObjects;
   gmRenderStates_t* renderStates;
   gmRenderer_t* renderer;

   sfBool showDiagnostics;
   
   gmMap_t* map;

   gmEntity_t* entity;
   sfTexture* mapTilesetTexture;
   sfTexture* entitySpriteTexture;

   sfBool cheatNoClip;
}
gmGame_t;

gmGame_t* gmGame_Create();
void gmGame_Destroy( gmGame_t* game );
void gmGame_Run( gmGame_t* game );
void gmGame_Close( gmGame_t* game );
void gmGame_ShowDebugMessage( gmGame_t* game, const char* msg );

// game_loader.c
void gmGame_LoadData( gmGame_t* game );

// renderer.c
void gmGame_Render( gmGame_t* game );

#endif // GAME_H
