#include "game.h"
#include "window.h"
#include "clock.h"
#include "input_state.h"
#include "renderer.h"
#include "render_states.h"

static void gmGame_Tic( gmGame_t* game );

gmGame_t* gmGame_Create()
{
   gmGame_t* game = (gmGame_t*)gmAlloc( sizeof( gmGame_t ), sfTrue );

   game->window = gmWindow_Create();
   game->clock = gmClock_Create();
   game->inputState = gmInputState_Create();
   game->renderer = gmRenderer_Create();

   game->showDiagnostics = sfFalse;

   return game;
}

void gmGame_Destroy( gmGame_t* game )
{
   gmRenderer_Destroy( game->renderer );
   gmInputState_Destroy( game->inputState );
   gmClock_Destroy( game->clock );
   gmWindow_Destroy( game->window );

   gmFree( game, sizeof( gmGame_t ), sfTrue );
}

void gmGame_Run( gmGame_t* game )
{
   while ( gmWindow_IsOpen( game->window ) )
   {
      gmClock_StartFrame( game->clock );

      gmInputState_Reset( game->inputState );
      gmWindow_HandleEvents( game->window, game->inputState );
      gmGame_HandleInput( game );
      gmGame_Tic( game );
      gmRenderer_Render( game );

      if ( game->window->wantToClose )
      {
         gmGame_Close( game );
      }

      gmClock_EndFrame( game->clock );
   }
}

static void gmGame_Tic( gmGame_t* game )
{
   gmRenderStates_Tic( game->renderer->renderStates, game->clock );
}

void gmGame_Close( gmGame_t* game )
{
   gmWindow_Close( game->window );
}

void gmGame_ShowDebugMessage( gmGame_t* game, const char* msg )
{
   gmDebugBarRenderState_t* state = game->renderer->renderStates->debugBar;

   snprintf( state->msgBuffer, state->msgBufferLen, "%s", msg );
   state->isVisible = sfTrue;
   state->elapsedSeconds = 0;
}
