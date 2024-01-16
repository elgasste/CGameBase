#include "game.h"
#include "window.h"
#include "clock.h"
#include "input_state.h"
#include "input_handler.h"
#include "render_objects.h"
#include "render_states.h"
#include "renderer.h"
#include "menus.h"
#include "map.h"
#include "entity.h"
#include "entity_sprite.h"
#include "physics.h"
#include "random.h"

static void gmGame_Tic( gmGame_t* game );

gmGame_t* gmGame_Create()
{
   gmGame_t* game = (gmGame_t*)gmAlloc( sizeof( gmGame_t ), sfTrue );

   game->window = gmWindow_Create();
   game->clock = gmClock_Create();
   game->inputState = gmInputState_Create();
   game->inputHandler = gmInputHandler_Create();
   game->physics = gmPhysics_Create();

   gmGame_LoadData( game );

   game->renderObjects = gmRenderObjects_Create( game );
   game->renderStates = gmRenderStates_Create();
   game->renderer = gmRenderer_Create();

   game->showDiagnostics = sfFalse;
   game->cheatNoClip = sfFalse;

   return game;
}

void gmGame_Destroy( gmGame_t* game )
{
   gmEntity_Destroy( game->entity );
   gmTexture_Destroy( game->entitySpriteTexture );
   gmTexture_Destroy( game->mapTilesetTexture );
   gmMap_Destroy( game->map );
   gmMenus_Destroy( game->menus );
   gmRenderer_Destroy( game->renderer );
   gmRenderStates_Destroy( game->renderStates );
   gmRenderObjects_Destroy( game->renderObjects );
   gmPhysics_Destroy( game->physics );
   gmInputHandler_Destroy( game->inputHandler );
   gmInputState_Destroy( game->inputState );
   gmClock_Destroy( game->clock );
   gmWindow_Destroy( game->window );

   gmFree( game, sizeof( gmGame_t ), sfTrue );
}

void gmGame_Run( gmGame_t* game )
{
   game->state = gmGameState_Overworld;

   while ( gmWindow_IsOpen( game->window ) )
   {
      gmClock_StartFrame( game->clock );

      gmInputState_Reset( game->inputState );
      gmWindow_HandleEvents( game->window, game->inputState );
      gmInputHandler_HandleInput( game );
      gmGame_Tic( game );
      gmRenderer_Render( game );

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

void gmGame_SetState( gmGame_t* game, gmGameState_t state )
{
   // TODO: whatever validation checks need to be done
   if ( state == gmGameState_OverworldMenu )
   {
      gmRenderStates_ResetMenu( game->renderStates->menu );
      game->menus->overworld->selectedIndex = 0;
   }

   game->state = state;
}

void gmGame_ExecuteMenuCommand( gmGame_t* game, gmMenuCommand_t command )
{
   switch ( command )
   {
      case gmMenuCommand_Quit:
         gmGame_Close( game );
         break;
      case gmMenuCommand_CloseMenu:
         if ( game->state == gmGameState_OverworldMenu )
         {
            gmGame_SetState( game, gmGameState_Overworld );
         }
         break;
   }
}

void gmGame_RollEncounter( gmGame_t* game, uint32_t mapTileIndex )
{
   gmMapTile_t* tile = &( game->map->tiles[mapTileIndex] );

   if ( tile->encounterRate > 0 && gmRandom_Percent() <= tile->encounterRate )
   {
      // TODO: generate an encounter and switch to battle state
   }
}

static void gmGame_Tic( gmGame_t* game )
{
   if ( game->state == gmGameState_Overworld )
   {
      gmPhysics_Tic( game );
   }

   gmRenderStates_Tic( game );
}

void gmGame_ShowDebugMessage( gmGame_t* game, const char* msg )
{
   gmDebugBarRenderState_t* state = game->renderStates->debugBar;

   snprintf( state->msgBuffer, state->msgBufferLen, "%s", msg );
   state->isVisible = sfTrue;
   state->elapsedSeconds = 0;
}
