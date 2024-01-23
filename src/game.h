#if !defined( GAME_H )
#define GAME_H

#include "common.h"

typedef struct gmWindow_t gmWindow_t;
typedef struct gmClock_t gmClock_t;
typedef struct gmInputState_t gmInputState_t;
typedef struct gmRenderer_t gmRenderer_t;

typedef struct gmGame_t
{
   gmWindow_t* window;
   gmClock_t* clock;
   gmInputState_t* inputState;
   gmRenderer_t* renderer;

   sfBool showDiagnostics;
}
gmGame_t;

gmGame_t* gmGame_Create();
void gmGame_Destroy( gmGame_t* game );
void gmGame_Run( gmGame_t* game );
void gmGame_Close( gmGame_t* game );
void gmGame_ShowDebugMessage( gmGame_t* game, const char* msg );

// input_handler.c
void gmGame_HandleInput( gmGame_t* game );

#endif // GAME_H
