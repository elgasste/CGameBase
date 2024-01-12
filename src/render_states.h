#if !defined( RENDER_STATES_H )
#define RENDER_STATES_H

#include "common.h"

typedef struct gmClock_t gmClock_t;

typedef struct gmDebugBarRenderState_t
{
   sfBool isVisible;
   float elapsedSeconds;
   float visibleSeconds;
   char* msgBuffer;
   size_t msgBufferLen;
}
gmDebugBarRenderState_t;

typedef struct gmRenderStates_t
{
   gmDebugBarRenderState_t* debugBar;
}
gmRenderStates_t;

gmRenderStates_t* gmRenderStates_Create();
void gmRenderStates_Destroy( gmRenderStates_t* states );
void gmRenderStates_Tic( gmRenderStates_t* states, gmClock_t* clock );

#endif // RENDER_STATES_H

