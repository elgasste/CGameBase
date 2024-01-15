#include "renderer.h"
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
static void gmRenderer_SetMapView( gmGame_t* game );
static void gmRenderer_DrawMap( gmGame_t* game );
static void gmRenderer_DrawMapEntities( gmGame_t* game );
static void gmRenderer_DrawOverworldMenu( gmGame_t* game );
static void gmRenderer_DrawDebugBar( gmGame_t* game );

gmRenderer_t* gmRenderer_Create()
{
   gmRenderer_t* renderer = (gmRenderer_t*)gmAlloc( sizeof( gmRenderer_t ), sfTrue );

   renderer->mapViewRect.width = WINDOW_WIDTH;
   renderer->mapViewRect.height = WINDOW_HEIGHT;

   return renderer;
}

void gmRenderer_Destroy( gmRenderer_t* renderer )
{
   gmFree( renderer, sizeof( gmRenderer_t ), sfTrue );
}

void gmRenderer_Render( gmGame_t* game )
{
   gmWindow_DrawRectangleShape( game->window, game->renderObjects->windowBackgroundRect );

   switch ( game->state )
   {
      case gmGameState_Overworld:
         gmRenderer_SetMapView( game );
         gmRenderer_DrawMap( game );
         gmRenderer_DrawMapEntities( game );
         break;
      case gmGameState_OverworldMenu:
         gmRenderer_SetMapView( game );
         gmRenderer_DrawMap( game );
         gmRenderer_DrawMapEntities( game );
         gmRenderer_DrawOverworldMenu( game );
         break;
   }
   if ( game->state == gmGameState_Overworld )
   {
      gmRenderer_SetMapView( game );
      gmRenderer_DrawMap( game );
      gmRenderer_DrawMapEntities( game );
   }
   
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

static void gmRenderer_SetMapView( gmGame_t* game )
{
   gmEntity_t* entity = game->entity;
   gmRenderer_t* renderer = game->renderer;
   gmMap_t* map = game->map;
   sfVector2f mapSize = { (float)( map->tileCount.x * MAP_TILE_SIZE ), (float)( map->tileCount.y * MAP_TILE_SIZE ) };
   sfVector2f entityCenter = { entity->mapPos.x + ( entity->mapHitBoxSize.x / 2 ),
      entity->mapPos.y + ( entity->mapHitBoxSize.y / 2 ) };

   renderer->mapViewRect.left = entityCenter.x - ( WINDOW_WIDTH / 2 );
   renderer->mapViewRect.top = entityCenter.y - ( WINDOW_HEIGHT / 2 );

   if ( mapSize.x < renderer->mapViewRect.width )
   {
      renderer->mapViewPadding.x = ( renderer->mapViewRect.width - mapSize.x ) / 2;
      renderer->mapTilePixelOffset.x = 0;
      renderer->mapViewStart.x = 0;
      renderer->mapViewEnd.x = map->tileCount.x - 1;
   }
   else if ( renderer->mapViewRect.left < 0 )
   {
      renderer->mapViewRect.left = 0;
      renderer->mapViewPadding.x = 0;
      renderer->mapTilePixelOffset.x = 0;
      renderer->mapViewStart.x = 0;
      renderer->mapViewEnd.x = (uint32_t)( renderer->mapViewRect.width / MAP_TILE_SIZE ) + 1;
   }
   else if ( ( renderer->mapViewRect.left + renderer->mapViewRect.width ) >= mapSize.x )
   {
      renderer->mapViewRect.left = mapSize.x - renderer->mapViewRect.width - 1;
      renderer->mapViewPadding.x = 0;
      renderer->mapTilePixelOffset.x = -( renderer->mapViewRect.left - (float)( (int)renderer->mapViewRect.left / MAP_TILE_SIZE ) * MAP_TILE_SIZE );
      renderer->mapViewEnd.x = map->tileCount.x;
      renderer->mapViewStart.x = renderer->mapViewEnd.x - (uint32_t)( renderer->mapViewRect.width / MAP_TILE_SIZE ) - 1;
   }
   else
   {
      renderer->mapTilePixelOffset.x = -( renderer->mapViewRect.left - (float)( (int)renderer->mapViewRect.left / MAP_TILE_SIZE ) * MAP_TILE_SIZE );
      renderer->mapViewStart.x = (uint32_t)( renderer->mapViewRect.left / MAP_TILE_SIZE );
      renderer->mapViewEnd.x = renderer->mapViewStart.x + (uint32_t)( renderer->mapViewRect.width / MAP_TILE_SIZE ) + 1;
   }

   if ( mapSize.y < renderer->mapViewRect.height )
   {
      renderer->mapViewPadding.y = ( renderer->mapViewRect.height - mapSize.y ) / 2;
      renderer->mapTilePixelOffset.y = 0;
      renderer->mapViewStart.y = 0;
      renderer->mapViewEnd.y = map->tileCount.y - 1;
   }
   else if ( renderer->mapViewRect.top < 0 )
   {
      renderer->mapViewRect.top = 0;
      renderer->mapViewPadding.y = 0;
      renderer->mapTilePixelOffset.y = 0;
      renderer->mapViewStart.y = 0;
      renderer->mapViewEnd.y = (uint32_t)( renderer->mapViewRect.height / MAP_TILE_SIZE ) + 1;
   }
   else if ( ( renderer->mapViewRect.top + renderer->mapViewRect.height ) >= mapSize.y )
   {
      renderer->mapViewRect.top = mapSize.y - renderer->mapViewRect.height - 1;
      renderer->mapViewPadding.y = 0;
      renderer->mapTilePixelOffset.y = -( renderer->mapViewRect.top - (float)( (int)renderer->mapViewRect.top / MAP_TILE_SIZE ) * MAP_TILE_SIZE );
      renderer->mapViewEnd.y = map->tileCount.y;
      renderer->mapViewStart.y = renderer->mapViewEnd.y - (uint32_t)( renderer->mapViewRect.height / MAP_TILE_SIZE ) - 1;
   }
   else
   {
      renderer->mapTilePixelOffset.y = -( renderer->mapViewRect.top - (float)( (int)renderer->mapViewRect.top / MAP_TILE_SIZE ) * MAP_TILE_SIZE );
      renderer->mapViewStart.y = (uint32_t)( renderer->mapViewRect.top / MAP_TILE_SIZE );
      renderer->mapViewEnd.y = renderer->mapViewStart.y + (uint32_t)( renderer->mapViewRect.height / MAP_TILE_SIZE ) + 1;
   }
}

static void gmRenderer_DrawMap( gmGame_t* game )
{
   gmRenderer_t* renderer = game->renderer;
   gmMap_t* map = game->map;
   uint32_t tileRow, tileCol, row, col;
   gmMapRenderObjects_t* objects = game->renderObjects->mapRenderObjects;
   gmMapTile_t* tile;
   sfVector2f tilePos = { 0, 0 };
   sfIntRect textureRect = { 0, 0, MAP_TILE_PIXELS, MAP_TILE_PIXELS };
   sfVector2u textureSize = sfTexture_getSize( game->mapTilesetTexture );
   sfVector2u textureTileCount = { textureSize.x / MAP_TILE_PIXELS, textureSize.y / MAP_TILE_PIXELS };

   for ( row = 0, tileRow = renderer->mapViewStart.y; tileRow <= renderer->mapViewEnd.y; row++, tileRow++ )
   {
      for ( col = 0, tileCol = renderer->mapViewStart.x; tileCol <= renderer->mapViewEnd.x; col++, tileCol++ )
      {
         tile = &( map->tiles[( tileRow * map->tileCount.x ) + tileCol] );

         tilePos.x = ( (float)col * MAP_TILE_SIZE ) + renderer->mapTilePixelOffset.x + renderer->mapViewPadding.x;
         tilePos.y = ( (float)row * MAP_TILE_SIZE ) + renderer->mapTilePixelOffset.y + renderer->mapViewPadding.y;
         textureRect.left = ( tile->textureIndex % textureTileCount.x ) * MAP_TILE_PIXELS;
         textureRect.top = ( tile->textureIndex / textureTileCount.x ) * MAP_TILE_PIXELS;

         sfSprite_setTextureRect( objects->tileSprite, textureRect );
         sfSprite_setPosition( objects->tileSprite, tilePos );

         gmWindow_DrawSprite( game->window, objects->tileSprite );
      }
   }
}

static void gmRenderer_DrawMapEntities( gmGame_t* game )
{
   gmRenderer_t* renderer = game->renderer;
   sfVector2f spritePos;

   spritePos.x = ( renderer->mapViewPadding.x > 0 )
      ? game->entity->mapPos.x + game->entity->spriteOffset.x + renderer->mapViewPadding.x
      : game->entity->mapPos.x + game->entity->spriteOffset.x - renderer->mapViewRect.left;
   spritePos.y = ( renderer->mapViewPadding.y > 0 )
      ? game->entity->mapPos.y + game->entity->spriteOffset.y + renderer->mapViewPadding.y
      : game->entity->mapPos.y + game->entity->spriteOffset.y - renderer->mapViewRect.top;

   gmEntitySprite_SetPosition( game->entity->sprite, spritePos );
   gmWindow_DrawEntitySprite( game->window, game->entity->sprite );
}

static void gmRenderer_DrawOverworldMenu( gmGame_t* game )
{
   sfVector2f pos;
   gmOverworldMenuRenderObjects_t* objects = game->renderObjects->overworldMenuRenderObjects;
   gmMenuRenderState_t* renderState = game->renderStates->menu;

   if ( renderState->showCarat )
   {
      // TODO: the menu items themselves have to come from somewhere
      pos.x = objects->menuPos.x + objects->itemsOffset.x + objects->caratOffset.x;
      pos.y = objects->menuPos.y + objects->itemsOffset.y + objects->caratOffset.y;
      sfText_setPosition( objects->text, pos );
      sfText_setString( objects->text, STR_MENU_CARAT );
      gmWindow_DrawText( game->window, objects->text );
   }
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
