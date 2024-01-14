#include "game.h"
#include "input_state.h"
#include "entity.h"

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
      entity->velocity.x = -entity->maxVelocity;

      if ( upIsDown || downIsDown )
      {
         entity->velocity.x *= 0.707f;
      }

      if ( !( upIsDown && entity->direction == gmDirection_Up ) &&
           !( downIsDown && entity->direction == gmDirection_Down ) )
      {
         entity->direction = gmDirection_Left;
      }
   }

   if ( upIsDown && !downIsDown )
   {
      entity->velocity.y = -entity->maxVelocity;

      if ( leftIsDown || rightIsDown )
      {
         entity->velocity.y *= 0.707f;
      }

      if ( !( leftIsDown && entity->direction == gmDirection_Left ) &&
           !( rightIsDown && entity->direction == gmDirection_Right ) )
      {
         entity->direction = gmDirection_Up;
      }
   }

   if ( rightIsDown && !leftIsDown )
   {
      entity->velocity.x = entity->maxVelocity;

      if ( upIsDown || downIsDown )
      {
         entity->velocity.x *= 0.707f;
      }

      if ( !( upIsDown && entity->direction == gmDirection_Up ) &&
           !( downIsDown && entity->direction == gmDirection_Down ) )
      {
         entity->direction = gmDirection_Right;
      }
   }

   if ( downIsDown && !upIsDown )
   {
      entity->velocity.y = entity->maxVelocity;

      if ( leftIsDown || rightIsDown )
      {
         entity->velocity.y *= 0.707f;
      }

      if ( !( leftIsDown && entity->direction == gmDirection_Left ) &&
           !( rightIsDown && entity->direction == gmDirection_Right ) )
      {
         entity->direction = gmDirection_Down;
      }
   }
}
