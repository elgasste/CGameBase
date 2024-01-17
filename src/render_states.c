#include "render_states.h"
#include "renderer.h"
#include "game.h"
#include "clock.h"

static gmDebugBarRenderState_t* gmDebugBarRenderState_Create();
static gmMenuRenderState_t* gmMenuRenderState_Create();
static gmScreenFadeRenderState_t* gmScreenFadeRenderState_Create();
static void gmDebugBarRenderState_Destroy( gmDebugBarRenderState_t* state );
static void gmMenuRenderState_Destroy( gmMenuRenderState_t* state );
static void gmScreenFadeRenderState_Destroy( gmScreenFadeRenderState_t* state );

gmRenderStates_t* gmRenderStates_Create()
{
   gmRenderStates_t* states = (gmRenderStates_t*)gmAlloc( sizeof( gmRenderStates_t ), sfTrue );

   states->debugBar = gmDebugBarRenderState_Create();
   states->menu = gmMenuRenderState_Create();
   states->screenFade = gmScreenFadeRenderState_Create();

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

void gmRenderStates_Destroy( gmRenderStates_t* states )
{
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

void gmRenderStates_StartFade( gmScreenFadeRenderState_t* state, sfBool light )
{
   gmRenderStates_ResetScreenFade( state );
   state->light = light;
   state->isFading = sfTrue;
   state->isFadingOut = sfTrue;
}

void gmRenderStates_Tic( gmGame_t* game )
{
   gmRenderStates_t* states = game->renderer->renderStates;
   gmClock_t* clock = game->clock;

   if ( states->debugBar->isVisible )
   {
      states->debugBar->elapsedSeconds += clock->frameDelta;

      if ( states->debugBar->elapsedSeconds > states->debugBar->visibleSeconds )
      {
         states->debugBar->isVisible = sfFalse;
         states->debugBar->elapsedSeconds = 0;
      }
   }

   if ( states->screenFade->isFading )
   {
      states->screenFade->elapsedSeconds += clock->frameDelta;

      if ( states->screenFade->elapsedSeconds > states->screenFade->fadeSeconds )
      {
         states->screenFade->elapsedSeconds = 0;

         if ( states->screenFade->isFadingOut )
         {
            states->screenFade->isFadingOut = sfFalse;
            states->screenFade->isPaused = sfTrue;
         }
         else if ( states->screenFade->isPaused )
         {
            states->screenFade->isPaused = sfFalse;
            states->screenFade->isFadingIn = sfTrue;
         }
         else
         {
            gmRenderStates_ResetScreenFade( states->screenFade );
         }
      }

      return;
   }

   if ( game->state == gmGameState_OverworldMenu )
   {
      states->menu->caratElapsedSeconds += clock->frameDelta;

      while( states->menu->caratElapsedSeconds > states->menu->caratBlinkSeconds )
      {
         TOGGLE_BOOL( states->menu->showCarat );
         states->menu->caratElapsedSeconds -= states->menu->caratBlinkSeconds;
      }
   }
}
