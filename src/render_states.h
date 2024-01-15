#if !defined( RENDER_STATES_H )
#define RENDER_STATES_H

#include "common.h"

typedef struct gmGame_t gmGame_t;

typedef struct gmDebugBarRenderState_t
{
   sfBool isVisible;
   float elapsedSeconds;
   float visibleSeconds;
   char* msgBuffer;
   size_t msgBufferLen;
}
gmDebugBarRenderState_t;

typedef struct gmMenuRenderState_t
{
   sfBool showCarat;
   float caratBlinkSeconds;
   float caratElapsedSeconds;
}
gmMenuRenderState_t;

typedef struct gmRenderStates_t
{
   gmDebugBarRenderState_t* debugBar;
   gmMenuRenderState_t* menu;
}
gmRenderStates_t;

gmRenderStates_t* gmRenderStates_Create();
void gmRenderStates_Destroy( gmRenderStates_t* states );
void gmRenderStates_ResetMenu( gmMenuRenderState_t* state );
void gmRenderStates_Tic( gmGame_t* game );

#endif // RENDER_STATES_H
