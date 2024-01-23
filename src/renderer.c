#include "game.h"
#include "render_objects.h"
#include "render_states.h"
#include "window.h"
#include "clock.h"
#include "time_util.h"

static void gmRenderer_DrawDiagnostics( gmGame_t* game );
static void gmRenderer_DrawDebugBar( gmGame_t* game );

void gmGame_Render( gmGame_t* game )
{
   gmWindow_DrawRectangleShape( game->window, game->renderObjects->windowBackgroundRect );

   gmRenderer_DrawDebugBar( game );

   if ( game->showDiagnostics )
   {
      gmRenderer_DrawDiagnostics( game );
   }

   gmWindow_Display( game->window );
}

static void gmRenderer_DrawDiagnostics( gmGame_t* game )
{
   char msg[STRLEN_DEFAULT];
   char timeStr[STRLEN_SHORT];
   gmDiagnosticsRenderObjects_t* objects = game->renderObjects->diagnosticsRenderObjects;

   gmWindow_DrawRectangleShape( game->window, objects->backgroundRect );

   objects->textPosition.y = 4;
   sfText_setPosition( objects->text, objects->textPosition );
   snprintf( msg, STRLEN_DEFAULT, STR_FRAMERATEFORMATTER, GAME_FPS );
   sfText_setString( objects->text, msg );
   gmWindow_DrawText( game->window, objects->text );

   objects->textPosition.y += objects->lineSpacing;
   sfText_setPosition( objects->text, objects->textPosition );
   snprintf( msg, STRLEN_DEFAULT, STR_TOTALFRAMESFORMATTER, game->clock->totalFrameCount );
   sfText_setString( objects->text, msg );
   gmWindow_DrawText( game->window, objects->text );

   objects->textPosition.y += objects->lineSpacing;
   sfText_setPosition( objects->text, objects->textPosition );
   snprintf( msg, STRLEN_DEFAULT, STR_LAGFRAMESFORMATTER, game->clock->lagFrameCount );
   sfText_setString( objects->text, msg );
   gmWindow_DrawText( game->window, objects->text );

   objects->textPosition.y += objects->lineSpacing;
   sfText_setPosition( objects->text, objects->textPosition );
   dmTimeUtil_FormatTime( timeStr, STRLEN_SHORT, (int32_t)( game->clock->realTotalDurationMicro / 1000000 ) );
   snprintf( msg, STRLEN_DEFAULT, STR_ELAPSEDTIMEFORMATTER, timeStr );
   sfText_setString( objects->text, msg );
   gmWindow_DrawText( game->window, objects->text );
}

static void gmRenderer_DrawDebugBar( gmGame_t* game )
{
   gmDebugBarRenderState_t* state = game->renderStates->debugBar;
   gmDebugBarRenderObjects_t* objects = game->renderObjects->debugBarRenderObjects;

   if ( state->isVisible )
   {
      sfText_setString( objects->text, state->msgBuffer );

      gmWindow_DrawRectangleShape( game->window, objects->backgroundRect );
      gmWindow_DrawText( game->window, objects->text );
   }
}
