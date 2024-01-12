#include "game.h"
#include "input_state.h"
#include "entity.h"

#define ENTITY_MAX_VELOCITY 256

void gmGame_HandleInput( gmGame_t* game )
{
   gmEntity_t* entity = game->entity;

   if ( gmInputState_WasKeyPressed( game->inputState, sfKeyEscape ) )
   {
      gmGame_Close( game );
      return;
   }

   if ( gmInputState_WasKeyPressed( game->inputState, sfKeyD ) )
   {
      TOGGLE_BOOL( game->showDiagnostics );

      if ( game->showDiagnostics )
      {
         gmGame_ShowDebugMessage( game, STR_DEBUG_DIAGNOSTICSON );
      }
      else
      {
         gmGame_ShowDebugMessage( game, STR_DEBUG_DIAGNOSTICSOFF );
      }
   }

   sfBool leftIsDown = gmInputState_IsKeyDown( sfKeyLeft );
   sfBool upIsDown = gmInputState_IsKeyDown( sfKeyUp );
   sfBool rightIsDown = gmInputState_IsKeyDown( sfKeyRight );
   sfBool downIsDown = gmInputState_IsKeyDown( sfKeyDown );

   if ( leftIsDown && !rightIsDown )
   {
      entity->velocity.x = -ENTITY_MAX_VELOCITY;

      if ( upIsDown || downIsDown )
      {
         entity->velocity.x *= 0.707f;
      }
   }
   if ( upIsDown && !downIsDown )
   {
      entity->velocity.y = -ENTITY_MAX_VELOCITY;

      if ( leftIsDown || rightIsDown )
      {
         entity->velocity.y *= 0.707f;
      }
   }
   if ( rightIsDown && !leftIsDown )
   {
      entity->velocity.x = ENTITY_MAX_VELOCITY;

      if ( upIsDown || rightIsDown )
      {
         entity->velocity.x *= 0.707f;
      }
   }
   if ( downIsDown && !upIsDown )
   {
      entity->velocity.y = ENTITY_MAX_VELOCITY;

      if ( leftIsDown || rightIsDown )
      {
         entity->velocity.y *= 0.707f;
      }
   }
}
