#include "render_states.h"
#include "clock.h"

static gmDebugBarRenderState_t* gmDebugBarRenderState_Create();
static void gmDebugBarRenderState_Destroy( gmDebugBarRenderState_t* state );

gmRenderStates_t* gmRenderStates_Create()
{
   gmRenderStates_t* states = (gmRenderStates_t*)gmAlloc( sizeof( gmRenderStates_t ), sfTrue );

   states->debugBar = gmDebugBarRenderState_Create();

   return states;
}

static gmDebugBarRenderState_t* gmDebugBarRenderState_Create()
{
   gmDebugBarRenderState_t* state = (gmDebugBarRenderState_t*)gmAlloc( sizeof( gmDebugBarRenderState_t ), sfTrue );

   state->isVisible = sfFalse;
   state->visibleSeconds = 3;
   state->elapsedSeconds = 0;
   state->msgBuffer = (char*)gmCalloc( DEFAULT_STRLEN, sizeof( char ), sfTrue );
   state->msgBufferLen = DEFAULT_STRLEN;

   return state;
}

void gmRenderStates_Destroy( gmRenderStates_t* states )
{
   gmDebugBarRenderState_Destroy( states->debugBar );

   gmFree( states, sizeof( gmRenderStates_t ), sfTrue );
}

static void gmDebugBarRenderState_Destroy( gmDebugBarRenderState_t* state )
{
   gmFree( state->msgBuffer, sizeof( char ) * state->msgBufferLen, sfTrue );

   gmFree( state, sizeof( gmDebugBarRenderState_t ), sfTrue );
}

void gmRenderStates_Tic( gmRenderStates_t* states, gmClock_t* clock )
{
   if ( states->debugBar->isVisible )
   {
      states->debugBar->elapsedSeconds += clock->frameDelta;

      if ( states->debugBar->elapsedSeconds > states->debugBar->visibleSeconds )
      {
         states->debugBar->isVisible = sfFalse;
         states->debugBar->elapsedSeconds = 0;
      }
   }
}
