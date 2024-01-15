#include "game.h"
#include "render_objects.h"
#include "render_states.h"
#include "window.h"
#include "clock.h"
#include "time_util.h"
#include "map.h"
#include "entity.h"
#include "entity_sprite.h"

static void gmRenderer_DrawDiagnostics( gmGame_t* game );
static void gmRenderer_DrawMap( gmGame_t* game );
static void gmRenderer_DrawEntities( gmGame_t* game );
static void gmRenderer_DrawDebugBar( gmGame_t* game );

void gmGame_Render( gmGame_t* game )
{
   gmWindow_DrawRectangleShape( game->window, game->renderObjects->windowBackgroundRect );

   gmRenderer_DrawMap( game );
   gmRenderer_DrawEntities( game );
   gmRenderer_DrawDebugBar( game );

   if ( game->showDiagnostics )
   {
      gmRenderer_DrawDiagnostics( game );
   }

   gmWindow_Display( game->window );
}

static void gmRenderer_DrawDiagnostics( gmGame_t* game )
{
   char msg[DEFAULT_STRLEN];
   char timeStr[SHORT_STRLEN];
   gmDiagnosticsRenderObjects_t* objects = game->renderObjects->diagnosticsRenderObjects;

   gmWindow_DrawRectangleShape( game->window, objects->backgroundRect );

   objects->textPosition.y = 4;
   sfText_setPosition( objects->text, objects->textPosition );
   snprintf( msg, DEFAULT_STRLEN, STR_FRAMERATEFORMATTER, GAME_FPS );
   sfText_setString( objects->text, msg );
   gmWindow_DrawText( game->window, objects->text );

   objects->textPosition.y += objects->lineSpacing;
   sfText_setPosition( objects->text, objects->textPosition );
   snprintf( msg, DEFAULT_STRLEN, STR_TOTALFRAMESFORMATTER, game->clock->totalFrameCount );
   sfText_setString( objects->text, msg );
   gmWindow_DrawText( game->window, objects->text );

   objects->textPosition.y += objects->lineSpacing;
   sfText_setPosition( objects->text, objects->textPosition );
   snprintf( msg, DEFAULT_STRLEN, STR_LAGFRAMESFORMATTER, game->clock->lagFrameCount );
   sfText_setString( objects->text, msg );
   gmWindow_DrawText( game->window, objects->text );

   objects->textPosition.y += objects->lineSpacing;
   sfText_setPosition( objects->text, objects->textPosition );
   dmTimeUtil_FormatTime( timeStr, SHORT_STRLEN, (int32_t)( game->clock->realTotalDurationMicro / 1000000 ) );
   snprintf( msg, DEFAULT_STRLEN, STR_ELAPSEDTIMEFORMATTER, timeStr );
   sfText_setString( objects->text, msg );
   gmWindow_DrawText( game->window, objects->text );
}

static void gmRenderer_DrawMap( gmGame_t* game )
{
   uint32_t row, col;
   gmMapRenderObjects_t* objects = game->renderObjects->mapRenderObjects;
   gmMap_t* map = game->map;
   gmMapTile_t* tile;
   sfVector2f tilePos;
   sfIntRect textureRect = { 0, 0, MAP_TILE_PIXELS, MAP_TILE_PIXELS };
   sfVector2u textureSize = sfTexture_getSize( game->mapTilesetTexture );
   sfVector2u textureTileCount = { textureSize.x / MAP_TILE_PIXELS, textureSize.y / MAP_TILE_PIXELS };

   for ( row = 0; row < map->tileCount.y; row++ )
   {
      for ( col = 0; col < map->tileCount.x; col++ )
      {
         tile = &( map->tiles[( row * map->tileCount.x ) + col] );
         tilePos.x = (float)col * MAP_TILE_SIZE;
         tilePos.y = (float)row * MAP_TILE_SIZE;
         textureRect.left = ( tile->textureIndex % textureTileCount.x ) * MAP_TILE_PIXELS;
         textureRect.top = ( tile->textureIndex / textureTileCount.x ) * MAP_TILE_PIXELS;

         sfSprite_setTextureRect( objects->tileSprite, textureRect );
         sfSprite_setPosition( objects->tileSprite, tilePos );

         gmWindow_DrawSprite( game->window, objects->tileSprite );
      }
   }
}

static void gmRenderer_DrawEntities( gmGame_t* game )
{
   sfVector2f spritePos = { game->entity->mapPos.x + game->entity->spriteOffset.x,
                            game->entity->mapPos.y + game->entity->spriteOffset.y };

   gmEntitySprite_SetPosition( game->entity->sprite, spritePos );
   gmWindow_DrawEntitySprite( game->window, game->entity->sprite );
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
