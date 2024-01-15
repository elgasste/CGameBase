#include <string.h>

#include "input_handler.h"
#include "game.h"
#include "input_state.h"
#include "entity.h"

static void gmInputHandler_CheckCheats( gmGame_t* game );
static void gmInputHandler_ApplyCheat( gmGame_t* game );

gmInputHandler_t* gmInputHandler_Create()
{
   gmInputHandler_t* inputHandler = (gmInputHandler_t*)gmAlloc( sizeof( gmInputHandler_t ), sfTrue );

   inputHandler->cheatString[0] = '\0';

   return inputHandler;
}

void gmInputHandler_Destroy( gmInputHandler_t* inputHandler )
{
   gmFree( inputHandler, sizeof( gmInputHandler_t ), sfTrue );
}

void gmInputHandler_HandleInput( gmGame_t* game )
{
   char debugMsg[SHORT_STRLEN];
   gmEntity_t* entity = game->entity;

   if ( gmInputState_WasKeyPressed( game->inputState, sfKeyEscape ) )
   {
      gmGame_Close( game );
      return;
   }

   if ( gmInputState_WasKeyPressed( game->inputState, sfKeyF8 ) )
   {
      TOGGLE_BOOL( game->showDiagnostics );
      sprintf_s( debugMsg, SHORT_STRLEN, STR_DEBUG_DIAGNOSTICSFORMATTER, game->showDiagnostics ? STR_ON : STR_OFF );
      gmGame_ShowDebugMessage( game, debugMsg );
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

   gmInputHandler_CheckCheats( game );
}

static void gmInputHandler_CheckCheats( gmGame_t* game )
{
   int cheatStringLength, i, l, lastIndex, matchCount;
   static const char* cheats[] = {
      CHEAT_NOCLIP,
      CHEAT_CLEAR
   };
   static int cheatCount = (int)( sizeof( cheats ) / sizeof( const char* ) );
   gmInputHandler_t* inputHandler = game->inputHandler;

   if ( !game->inputState->keyWasPressed )
   {
      return;
   }

   cheatStringLength = (int)strlen( inputHandler->cheatString );
   inputHandler->cheatString[cheatStringLength] = (char)( game->inputState->lastPressedKey + 97 );
   cheatStringLength++;
   inputHandler->cheatString[cheatStringLength] = '\0';

   matchCount = cheatCount;
   lastIndex = cheatStringLength - 1;

   for ( i = 0; i < cheatCount; i++ )
   {
      l = (int)strlen( cheats[i] );

      if ( lastIndex >= l || cheats[i][lastIndex] != inputHandler->cheatString[lastIndex] )
      {
         matchCount--;
      }
      else if ( cheatStringLength == l && !strcmp( cheats[i], inputHandler->cheatString ) )
      {
         gmInputHandler_ApplyCheat( game );
         return;
      }
   }

   if ( matchCount == 0 )
   {
      inputHandler->cheatString[0] = '\0';
   }
}

static void gmInputHandler_ApplyCheat( gmGame_t* game )
{
   char cheatMsg[SHORT_STRLEN];
   char* cheat = game->inputHandler->cheatString;

   if ( !strcmp( cheat, CHEAT_NOCLIP ) )
   {
      TOGGLE_BOOL( game->cheatNoClip );
      sprintf_s( cheatMsg, SHORT_STRLEN, STR_CHEAT_NOCLIPFORMATTER, game->cheatNoClip ? STR_ON : STR_OFF );
      gmGame_ShowDebugMessage( game, cheatMsg );
   }
   else if ( !strcmp( cheat, CHEAT_CLEAR ) )
   {
      game->cheatNoClip = sfFalse;
      gmGame_ShowDebugMessage( game, STR_CHEAT_CLEARED );
   }

   cheat[0] = '\0';
}
