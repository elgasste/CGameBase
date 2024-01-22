#include "render_states.h"
#include "renderer.h"
#include "game.h"
#include "clock.h"
#include "battle.h"

static gmDebugBarRenderState_t* gmDebugBarRenderState_Create();
static gmMenuRenderState_t* gmMenuRenderState_Create();
static gmScreenFadeRenderState_t* gmScreenFadeRenderState_Create();
static gmTextScrollRenderState_t* gmTextScrollRenderState_Create();
static void gmDebugBarRenderState_Destroy( gmDebugBarRenderState_t* state );
static void gmMenuRenderState_Destroy( gmMenuRenderState_t* state );
static void gmScreenFadeRenderState_Destroy( gmScreenFadeRenderState_t* state );
static void gmTextScrollRenderState_Destroy( gmTextScrollRenderState_t* state );
static void gmRenderStates_TicDebugBar( gmDebugBarRenderState_t* state, gmClock_t* clock );
static sfBool gmRenderStates_TicScreenFade( gmScreenFadeRenderState_t* state, gmClock_t* clock );
static sfBool gmRenderStates_TicTextScroll( gmTextScrollRenderState_t* state, gmClock_t* clock );
static void gmRenderStates_TicMenu( gmGame_t* game );

gmRenderStates_t* gmRenderStates_Create()
{
   gmRenderStates_t* states = (gmRenderStates_t*)gmAlloc( sizeof( gmRenderStates_t ), sfTrue );

   states->debugBar = gmDebugBarRenderState_Create();
   states->menu = gmMenuRenderState_Create();
   states->screenFade = gmScreenFadeRenderState_Create();
   states->textScroll = gmTextScrollRenderState_Create();

   return states;
}

static gmDebugBarRenderState_t* gmDebugBarRenderState_Create()
{
   gmDebugBarRenderState_t* state = (gmDebugBarRenderState_t*)gmAlloc( sizeof( gmDebugBarRenderState_t ), sfTrue );

   state->isVisible = sfFalse;
   state->visibleSeconds = 3;
   state->elapsedSeconds = 0;
   state->msgBuffer = (char*)gmCalloc( STRLEN_DEFAULT, sizeof( char ), sfTrue );
   state->msgBufferLen = STRLEN_DEFAULT;

   return state;
}

static gmMenuRenderState_t* gmMenuRenderState_Create()
{
   gmMenuRenderState_t* state = (gmMenuRenderState_t*)gmAlloc( sizeof( gmMenuRenderState_t ), sfTrue );

   state->caratBlinkSeconds = MENU_CARAT_BLINKSECONDS;
   gmRenderStates_ResetMenu( state );

   return state;
}

static gmScreenFadeRenderState_t* gmScreenFadeRenderState_Create()
{
   gmScreenFadeRenderState_t* state = (gmScreenFadeRenderState_t*)gmAlloc( sizeof( gmScreenFadeRenderState_t ), sfTrue );

   state->fadeSeconds = 0.4f;
   state->pauseSeconds = 0.1f;
   gmRenderStates_ResetScreenFade( state );

   return state;
}

static gmTextScrollRenderState_t* gmTextScrollRenderState_Create()
{
   gmTextScrollRenderState_t* state = (gmTextScrollRenderState_t*)gmAlloc( sizeof( gmTextScrollRenderState_t ), sfTrue );

   state->letterSeconds = 0.012f;
   gmRenderStates_ResetTextScroll( state );

   return state;
}

void gmRenderStates_Destroy( gmRenderStates_t* states )
{
   gmTextScrollRenderState_Destroy( states->textScroll );
   gmScreenFadeRenderState_Destroy( states->screenFade );
   gmMenuRenderState_Destroy( states->menu );
   gmDebugBarRenderState_Destroy( states->debugBar );

   gmFree( states, sizeof( gmRenderStates_t ), sfTrue );
}

static void gmDebugBarRenderState_Destroy( gmDebugBarRenderState_t* state )
{
   gmFree( state->msgBuffer, sizeof( char ) * state->msgBufferLen, sfTrue );

   gmFree( state, sizeof( gmDebugBarRenderState_t ), sfTrue );
}

static void gmMenuRenderState_Destroy( gmMenuRenderState_t* state )
{
   gmFree( state, sizeof( gmMenuRenderState_t ), sfTrue );
}

static void gmScreenFadeRenderState_Destroy( gmScreenFadeRenderState_t* state )
{
   gmFree( state, sizeof( gmScreenFadeRenderState_t ), sfTrue );
}

static void gmTextScrollRenderState_Destroy( gmTextScrollRenderState_t* state )
{
   gmFree( state, sizeof( gmTextScrollRenderState_t ), sfTrue );
}

void gmRenderStates_ResetMenu( gmMenuRenderState_t* state )
{
   state->showCarat = sfTrue;
   state->caratElapsedSeconds = 0;
}

void gmRenderStates_ResetScreenFade( gmScreenFadeRenderState_t* state )
{
   state->isFading = sfFalse;
   state->isFadingOut = sfFalse;
   state->isPaused = sfFalse;
   state->isFadingIn = sfFalse;
   state->elapsedSeconds = 0;
}

void gmRenderStates_StartScreenFade( gmScreenFadeRenderState_t* state, sfBool light )
{
   gmRenderStates_ResetScreenFade( state );
   state->light = light;
   state->isFading = sfTrue;
   state->isFadingOut = sfTrue;
}

void gmRenderStates_ResetTextScroll( gmTextScrollRenderState_t* state )
{
   state->isScrolling = sfFalse;
   state->elapsedSeconds = 0;
   state->currentCharIndex = 0;
}

void gmRenderStates_StartTextScroll( gmTextScrollRenderState_t* state, uint32_t charCount )
{
   gmRenderStates_ResetTextScroll( state );
   state->charCount = charCount;
   state->isScrolling = sfTrue;
}

void gmRenderStates_Tic( gmGame_t* game )
{
   gmRenderStates_TicDebugBar( game->renderer->renderStates->debugBar, game->clock );

   if ( gmRenderStates_TicScreenFade( game->renderer->renderStates->screenFade, game->clock ) )
   {
      return;
   }
   else if ( gmRenderStates_TicTextScroll( game->renderer->renderStates->textScroll, game->clock ) )
   {
      return;
   }

   gmRenderStates_TicMenu( game );
}

static void gmRenderStates_TicDebugBar( gmDebugBarRenderState_t* state, gmClock_t* clock )
{
   if ( state->isVisible )
   {
      state->elapsedSeconds += clock->frameDelta;

      if ( state->elapsedSeconds > state->visibleSeconds )
      {
         state->isVisible = sfFalse;
         state->elapsedSeconds = 0;
      }
   }
}

static sfBool gmRenderStates_TicScreenFade( gmScreenFadeRenderState_t* state, gmClock_t* clock )
{
   if ( state->isFading )
   {
      state->elapsedSeconds += clock->frameDelta;

      if ( state->elapsedSeconds > state->fadeSeconds )
      {
         state->elapsedSeconds = 0;

         if ( state->isFadingOut )
         {
            state->isFadingOut = sfFalse;
            state->isPaused = sfTrue;
         }
         else if ( state->isPaused )
         {
            state->isPaused = sfFalse;
            state->isFadingIn = sfTrue;
         }
         else
         {
            gmRenderStates_ResetScreenFade( state );
         }
      }

      return sfTrue;
   }

   return sfFalse;
}

static sfBool gmRenderStates_TicTextScroll( gmTextScrollRenderState_t* state, gmClock_t* clock )
{
   if ( state->isScrolling )
   {
      state->elapsedSeconds += clock->frameDelta;

      while ( state->elapsedSeconds > state->letterSeconds )
      {
         state->elapsedSeconds -= state->letterSeconds;
         state->currentCharIndex++;

         if ( state->currentCharIndex == state->charCount )
         {
            gmRenderStates_ResetTextScroll( state );
            break;
         }
      }

      return sfTrue;
   }

   return sfFalse;
}

static void gmRenderStates_TicMenu( gmGame_t* game )
{
   gmRenderStates_t* states = game->renderer->renderStates;

   if ( game->state == gmGameState_OverworldMenu ||
        ( game->state == gmGameState_Battle && game->battle->state == gmBattleState_SelectAction ) )
   {
      states->menu->caratElapsedSeconds += game->clock->frameDelta;

      while( states->menu->caratElapsedSeconds > states->menu->caratBlinkSeconds )
      {
         TOGGLE_BOOL( states->menu->showCarat );
         states->menu->caratElapsedSeconds -= states->menu->caratBlinkSeconds;
      }
   }
}
