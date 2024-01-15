#include "game.h"
#include "window.h"
#include "clock.h"
#include "input_state.h"
#include "render_objects.h"
#include "render_states.h"
#include "renderer.h"
#include "map.h"
#include "entity.h"
#include "entity_sprite.h"
#include "physics.h"

static void gmGame_Tic( gmGame_t* game );

gmGame_t* gmGame_Create()
{
   gmGame_t* game = (gmGame_t*)gmAlloc( sizeof( gmGame_t ), sfTrue );

   game->window = gmWindow_Create();
   game->clock = gmClock_Create();
   game->inputState = gmInputState_Create();

   gmGame_LoadData( game );

   game->renderObjects = gmRenderObjects_Create( game );
   game->renderStates = gmRenderStates_Create();
   game->renderer = gmRenderer_Create();

   game->showDiagnostics = sfFalse;

   return game;
}

void gmGame_Destroy( gmGame_t* game )
{
   gmEntity_Destroy( game->entity );
   gmTexture_Destroy( game->entitySpriteTexture );
   gmTexture_Destroy( game->mapTilesetTexture );
   gmMap_Destroy( game->map );
   gmRenderer_Destroy( game->renderer );
   gmRenderStates_Destroy( game->renderStates );
   gmRenderObjects_Destroy( game->renderObjects );
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
      gmGame_Render( game );

      if ( game->window->wantToClose )
      {
         gmGame_Close( game );
      }

      gmClock_EndFrame( game->clock );
   }
}

void gmGame_Close( gmGame_t* game )
{
   gmWindow_Close( game->window );
}

static void gmGame_Tic( gmGame_t* game )
{
   gmPhysics_Tic( game );
   gmRenderStates_Tic( game->renderStates, game->clock );
}

void gmGame_ShowDebugMessage( gmGame_t* game, const char* msg )
{
   gmDebugBarRenderState_t* state = game->renderStates->debugBar;

   snprintf( state->msgBuffer, state->msgBufferLen, "%s", msg );
   state->isVisible = sfTrue;
   state->elapsedSeconds = 0;
}
