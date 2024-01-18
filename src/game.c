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
#include "battle.h"
#include "entity.h"
#include "entity_sprite.h"
#include "physics.h"
#include "random.h"

static void gmGame_Tic( gmGame_t* game );

gmGame_t* gmGame_Create()
{
   sfVector2f entityMapPos = { 256, 256 };
   sfVector2f entityMapHitBoxSize = { 52, 32 };
   sfVector2f entitySpriteOffset = { -6, -32 };

   gmGame_t* game = (gmGame_t*)gmAlloc( sizeof( gmGame_t ), sfTrue );

   game->window = gmWindow_Create();
   game->clock = gmClock_Create();
   game->inputState = gmInputState_Create();
   game->inputHandler = gmInputHandler_Create();
   game->physics = gmPhysics_Create();

   gmGame_LoadData( game );

   game->state = (gmGameState_t)0;
   game->renderer = gmRenderer_Create( game );

   game->battle = 0;

   game->showDiagnostics = sfFalse;
   game->cheatNoClip = sfFalse;
   game->cheatNoEncounters = sfFalse;

   // TODO: entities should be created on the fly, probably.
   // and gmGame_t should have a "controllable entity" pointer.
   game->entity = gmEntity_Create( entityMapPos,
                                   entityMapHitBoxSize,
                                   200.0f,
                                   entitySpriteOffset,
                                   game->renderer->renderObjects->entitySpriteTexture );
   gmEntity_SetDirection( game->entity, gmDirection_Down );
   game->physics->entityMapTileCache = gmMap_TileIndexFromPos( game->map, entityMapPos );

   return game;
}

void gmGame_Destroy( gmGame_t* game )
{
   gmEntity_Destroy( game->entity );
   gmMap_Destroy( game->map );
   gmMenus_Destroy( game->menus );
   gmRenderer_Destroy( game->renderer );
   gmPhysics_Destroy( game->physics );
   gmInputHandler_Destroy( game->inputHandler );
   gmInputState_Destroy( game->inputState );
   gmClock_Destroy( game->clock );
   gmWindow_Destroy( game->window );

   if ( game->battle )
   {
      gmBattle_Destroy( game->battle );
   }

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
   if ( state == gmGameState_OverworldMenu )
   {
      gmRenderStates_ResetMenu( game->renderer->renderStates->menu );
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

   if ( !game->cheatNoEncounters && tile->encounterRate > 0 && gmRandom_Percent() <= tile->encounterRate )
   {
      gmGame_StartEncounter( game );
   }
}

void gmGame_StartEncounter( gmGame_t* game )
{
   if ( game->battle )
   {
      gmBattle_Destroy( game->battle );
      game->battle = 0;
   }

   game->battle = gmBattle_Create( game );
   gmGame_SetState( game, gmGameState_Battle );
   gmRenderStates_StartScreenFade( game->renderer->renderStates->screenFade, sfTrue );
}

void gmGame_EndEncounter( gmGame_t* game )
{
   gmGame_SetState( game, gmGameState_Overworld );
   gmRenderStates_StartScreenFade( game->renderer->renderStates->screenFade, sfFalse );
}

static void gmGame_Tic( gmGame_t* game )
{
   if ( game->state == gmGameState_Overworld && !gmRenderer_IsBlockingPhysics( game->renderer ) )
   {
      gmPhysics_Tic( game );
   }

   gmRenderStates_Tic( game );
}

void gmGame_ShowDebugMessage( gmGame_t* game, const char* msg )
{
   gmDebugBarRenderState_t* state = game->renderer->renderStates->debugBar;

   snprintf( state->msgBuffer, state->msgBufferLen, "%s", msg );
   state->isVisible = sfTrue;
   state->elapsedSeconds = 0;
}
