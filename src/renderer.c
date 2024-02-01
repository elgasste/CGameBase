#include "renderer.h"
#include "game.h"
#include "render_objects.h"
#include "render_states.h"
#include "window.h"
#include "clock.h"
#include "time_util.h"
#include "map.h"
#include "character.h"
#include "enemy.h"
#include "entity.h"
#include "entity_sprite.h"
#include "battle_sprite.h"
#include "menus.h"
#include "battle.h"
#include "text_util.h"
#include "battle_stats.h"

static void gmRenderer_DrawDiagnostics( gmGame_t* game );
static void gmRenderer_DrawDebugBar( gmGame_t* game );
static void gmRenderer_SetMapView( gmGame_t* game );
static void gmRenderer_DrawMap( gmGame_t* game );
static void gmRenderer_DrawMapEntities( gmGame_t* game );
static void gmRenderer_DrawOverworldMenu( gmGame_t* game );
static void gmRenderer_DrawBattle( gmGame_t* game );
static void gmRenderer_DrawBattleStatusDialog( gmGame_t* game );
static void gmRenderer_DrawBattleActionMenu( gmGame_t* game );
static void gmRenderer_DrawBattleLargeDialog( gmGame_t* game );
static void gmRenderer_DrawBattleSmallDialog( gmGame_t* game );
static void gmRenderer_DrawBattleEnemy( gmGame_t* game );

gmRenderer_t* gmRenderer_Create( gmGame_t* game )
{
   gmRenderer_t* renderer = (gmRenderer_t*)gmAlloc( sizeof( gmRenderer_t ), sfTrue );

   renderer->renderObjects = gmRenderObjects_Create( renderer );
   renderer->renderStates = gmRenderStates_Create();

   renderer->mapViewRect.width = WINDOW_WIDTH;
   renderer->mapViewRect.height = WINDOW_HEIGHT;

   renderer->currentGameState = game->state;
   renderer->lastGameState = renderer->currentGameState;

   return renderer;
}

void gmRenderer_Destroy( gmRenderer_t* renderer )
{
   gmRenderStates_Destroy( renderer->renderStates );
   gmRenderObjects_Destroy( renderer->renderObjects );

   gmFree( renderer, sizeof( gmRenderer_t ), sfTrue );
}

void gmRenderer_Render( gmGame_t* game )
{
   float fadePercentage;
   gmRenderer_t* renderer = game->renderer;
   gmScreenFadeRenderState_t* fadeRenderState = renderer->renderStates->screenFade;
   gmScreenFadeRenderObjects_t* fadeRenderObjects = renderer->renderObjects->screenFade;

   gmGameState_t gameState;

   gmWindow_DrawRectangleShape( game->window, renderer->renderObjects->windowBackgroundRect );

   if ( game->state != renderer->currentGameState )
   {
      renderer->lastGameState = renderer->currentGameState;
      renderer->currentGameState = game->state;
   }

   gameState = fadeRenderState->isFadingOut ? renderer->lastGameState : game->state;

   switch ( gameState )
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
      case gmGameState_Battle:
         gmRenderer_DrawBattle( game );
         break;
   }

   if ( fadeRenderState->isFading )
   {
      fadePercentage = fadeRenderState->isPaused ? 1.0f : fadeRenderState->elapsedSeconds / fadeRenderState->fadeSeconds;

      if ( fadeRenderState->isFadingIn )
      {
         fadePercentage = 1.0f - fadePercentage;
      }

      if ( fadeRenderState->light )
      {
         fadeRenderObjects->lightColor.a = (sfUint8)( 255 * fadePercentage );
         sfRectangleShape_setFillColor( fadeRenderObjects->screenRect, fadeRenderObjects->lightColor );
      }
      else
      {
         fadeRenderObjects->darkColor.a = (sfUint8)( 255 * fadePercentage );
         sfRectangleShape_setFillColor( fadeRenderObjects->screenRect, fadeRenderObjects->darkColor );
      }
      
      gmWindow_DrawRectangleShape( game->window, fadeRenderObjects->screenRect );
   }
   
   gmRenderer_DrawDebugBar( game );

   if ( game->showDiagnostics )
   {
      gmRenderer_DrawDiagnostics( game );
   }

   gmWindow_Display( game->window );
}

sfBool gmRenderer_IsBlockingPhysics( gmRenderer_t* renderer )
{
   return renderer->renderStates->screenFade->isFading || renderer->renderStates->textScroll->isScrolling;
}

sfBool gmRenderer_IsBlockingInput( gmRenderer_t* renderer )
{
   return renderer->renderStates->screenFade->isFading ||
          renderer->renderStates->textScroll->isScrolling ||
          renderer->renderStates->enemyDamage->isRunning;
}

void gmRenderer_TryUnblockingInput( gmRenderer_t* renderer )
{
   if ( !renderer->renderStates->screenFade->isFading && renderer->renderStates->textScroll->isScrolling )
   {
      gmRenderStates_ResetTextScroll( renderer->renderStates->textScroll );
   }
}

static void gmRenderer_DrawDiagnostics( gmGame_t* game )
{
   char msg[STRLEN_DEFAULT];
   char timeStr[STRLEN_DEFAULT];
   gmDiagnosticsRenderObjects_t* objects = game->renderer->renderObjects->diagnostics;

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
   gmDebugBarRenderState_t* state = game->renderer->renderStates->debugBar;
   gmDebugBarRenderObjects_t* objects = game->renderer->renderObjects->debugBar;

   if ( state->isVisible )
   {
      sfText_setString( objects->text, state->msgBuffer );

      gmWindow_DrawRectangleShape( game->window, objects->backgroundRect );
      gmWindow_DrawText( game->window, objects->text );
   }
}

static void gmRenderer_SetMapView( gmGame_t* game )
{
   gmEntity_t* entity = game->player->entity;
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
      renderer->mapTilePixelOffset.x = -( renderer->mapViewRect.left - (float)( (int32_t)renderer->mapViewRect.left / MAP_TILE_SIZE ) * MAP_TILE_SIZE );
      renderer->mapViewEnd.x = map->tileCount.x;
      renderer->mapViewStart.x = renderer->mapViewEnd.x - (uint32_t)( renderer->mapViewRect.width / MAP_TILE_SIZE ) - 1;
   }
   else
   {
      renderer->mapTilePixelOffset.x = -( renderer->mapViewRect.left - (float)( (int32_t)renderer->mapViewRect.left / MAP_TILE_SIZE ) * MAP_TILE_SIZE );
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
      renderer->mapTilePixelOffset.y = -( renderer->mapViewRect.top - (float)( (int32_t)renderer->mapViewRect.top / MAP_TILE_SIZE ) * MAP_TILE_SIZE );
      renderer->mapViewEnd.y = map->tileCount.y;
      renderer->mapViewStart.y = renderer->mapViewEnd.y - (uint32_t)( renderer->mapViewRect.height / MAP_TILE_SIZE ) - 1;
   }
   else
   {
      renderer->mapTilePixelOffset.y = -( renderer->mapViewRect.top - (float)( (int32_t)renderer->mapViewRect.top / MAP_TILE_SIZE ) * MAP_TILE_SIZE );
      renderer->mapViewStart.y = (uint32_t)( renderer->mapViewRect.top / MAP_TILE_SIZE );
      renderer->mapViewEnd.y = renderer->mapViewStart.y + (uint32_t)( renderer->mapViewRect.height / MAP_TILE_SIZE ) + 1;
   }
}

static void gmRenderer_DrawMap( gmGame_t* game )
{
   gmRenderer_t* renderer = game->renderer;
   gmMap_t* map = game->map;
   uint32_t tileRow, tileCol, row, col;
   gmMapRenderObjects_t* objects = game->renderer->renderObjects->map;
   gmMapTile_t* tile;
   sfVector2f tilePos = { 0, 0 };
   sfIntRect textureRect = { 0, 0, MAP_TILE_PIXELS, MAP_TILE_PIXELS };
   sfVector2u textureSize = sfTexture_getSize( game->renderer->renderObjects->mapTilesetTexture );
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
   gmEntity_t* entity = game->player->entity;
   sfVector2f spritePos;

   spritePos.x = ( renderer->mapViewPadding.x > 0 )
      ? entity->mapPos.x + entity->spriteOffset.x + renderer->mapViewPadding.x
      : entity->mapPos.x + entity->spriteOffset.x - renderer->mapViewRect.left;
   spritePos.y = ( renderer->mapViewPadding.y > 0 )
      ? entity->mapPos.y + entity->spriteOffset.y + renderer->mapViewPadding.y
      : entity->mapPos.y + entity->spriteOffset.y - renderer->mapViewRect.top;

   gmEntitySprite_SetPosition( entity->sprite, spritePos );
   gmWindow_DrawEntitySprite( game->window, entity->sprite );
}

static void gmRenderer_DrawOverworldMenu( gmGame_t* game )
{
   sfVector2f pos;
   gmOverworldMenuRenderObjects_t* objects = game->renderer->renderObjects->overworldMenu;
   gmMenuRenderState_t* renderState = game->renderer->renderStates->menu;
   gmMenu_t* menu = game->menus->overworld;
   uint32_t i;

   gmWindow_DrawConvexShape( game->window, objects->backgroundShape );

   for ( i = 0; i < menu->optionCount; i++ )
   {
      if ( menu->selectedIndex == i && renderState->showCarat )
      {
         pos.x = objects->menuPos.x + objects->itemsOffset.x + objects->caratOffset.x;
         pos.y = objects->menuPos.y + objects->itemsOffset.y + objects->caratOffset.y + ( i * MENU_LINESIZE );
         sfText_setPosition( objects->text, pos );
         sfText_setString( objects->text, STR_MENU_CARAT );
         gmWindow_DrawText( game->window, objects->text );
      }

      pos.x = objects->menuPos.x + objects->itemsOffset.x;
      pos.y = objects->menuPos.y + objects->itemsOffset.y + ( i * MENU_LINESIZE );
      sfText_setPosition( objects->text, pos );
      sfText_setString( objects->text, menu->options[i].label );
      gmWindow_DrawText( game->window, objects->text );
   }
}

static void gmRenderer_DrawBattle( gmGame_t* game )
{
   switch ( game->battle->state )
   {
      case gmBattleState_Intro:
         gmRenderer_DrawBattleLargeDialog( game );
         gmRenderer_DrawBattleEnemy( game );
         break;
      case gmBattleState_StartingAttack:
         gmRenderer_DrawBattleStatusDialog( game );
         gmRenderer_DrawBattleLargeDialog( game );
         gmRenderer_DrawBattleEnemy( game );
         break;
      case gmBattleState_EnemyDamage:
         gmRenderer_DrawBattleStatusDialog( game );
         gmRenderer_DrawBattleLargeDialog( game );
         gmRenderer_DrawBattleEnemy( game );
         break;
      case gmBattleState_Result:
         gmRenderer_DrawBattleStatusDialog( game );
         gmRenderer_DrawBattleLargeDialog( game );
         gmRenderer_DrawBattleEnemy( game );
         break;
      case gmBattleState_SelectAction:
         gmRenderer_DrawBattleStatusDialog( game );
         gmRenderer_DrawBattleActionMenu( game );
         gmRenderer_DrawBattleSmallDialog( game );
         gmRenderer_DrawBattleEnemy( game );
         break;
   }
}

static void gmRenderer_DrawBattleStatusDialog( gmGame_t* game )
{
   gmBattleRenderObjects_t* objects = game->renderer->renderObjects->battle;
   sfVector2f pos = { objects->statusDialogTextPos.x, objects->statusDialogTextPos.y };
   char hpStr[STRLEN_SHORT];

   gmWindow_DrawConvexShape( game->window, objects->statusDialogBackground );
   sfText_setPosition( objects->text, pos );
   sfText_setString( objects->text, game->player->name );
   gmWindow_DrawText( game->window, objects->text );
   pos.y += objects->lineSpacing;
   sfText_setPosition( objects->text, pos );
   snprintf( hpStr, STRLEN_SHORT, STR_BATTLE_HITPOINTSFORMATTER, game->player->battleStats->hitPoints );
   sfText_setString( objects->text, hpStr );
   gmWindow_DrawText( game->window, objects->text );
   pos.y += objects->lineSpacing;
   sfText_setPosition( objects->text, pos );
   snprintf( hpStr, STRLEN_SHORT, STR_BATTLE_MAGPOINTSFORMATTER, game->player->battleStats->magicPoints );
   sfText_setString( objects->text, hpStr );
   gmWindow_DrawText( game->window, objects->text );
}

static void gmRenderer_DrawBattleActionMenu( gmGame_t* game )
{
   gmBattleRenderObjects_t* objects = game->renderer->renderObjects->battle;
   gmMenu_t* actionMenu = game->menus->battleAction;
   gmMenuRenderState_t* actionMenuState = game->renderer->renderStates->menu;
   sfVector2f pos;
   uint32_t i;

   gmWindow_DrawConvexShape( game->window, objects->actionMenuBackground );

   for ( i = 0; i < actionMenu->optionCount; i++ )
   {
      if ( actionMenu->selectedIndex == i && actionMenuState->showCarat )
      {
         pos.x = objects->actionMenuItemsPos.x + objects->actionMenuCaratOffset.x;
         pos.y = objects->actionMenuItemsPos.y + objects->actionMenuCaratOffset.y + ( i * MENU_LINESIZE );
         sfText_setPosition( objects->text, pos );
         sfText_setString( objects->text, STR_MENU_CARAT );
         gmWindow_DrawText( game->window, objects->text );
      }

      pos.x = objects->actionMenuItemsPos.x;
      pos.y = objects->actionMenuItemsPos.y + ( i * MENU_LINESIZE );
      sfText_setPosition( objects->text, pos );
      sfText_setString( objects->text, actionMenu->options[i].label );
      gmWindow_DrawText( game->window, objects->text );
   }
}

static void gmRenderer_DrawBattleLargeDialog( gmGame_t* game )
{
   gmBattleRenderObjects_t* objects = game->renderer->renderObjects->battle;

   gmWindow_DrawConvexShape( game->window, objects->largeDialogBackground );

   if ( game->battle->state == gmBattleState_Intro && game->renderer->renderStates->screenFade->isFading )
   {
      // if we don't do this, the first character of the message will appear early
      return;
   }

   sfText_setString( objects->text, game->battle->message );
   gmTextUtil_DrawWrappedScrollingText( game,
                                        objects->text,
                                        game->battle->message,
                                        objects->largeDialogTextPos,
                                        objects->largeDialogTextWidth,
                                        objects->lineSpacing );
}

static void gmRenderer_DrawBattleSmallDialog( gmGame_t* game )
{
   gmBattleRenderObjects_t* objects = game->renderer->renderObjects->battle;

   gmWindow_DrawConvexShape( game->window, objects->smallDialogBackground );
   sfText_setString( objects->text, game->battle->message );
   gmTextUtil_DrawWrappedScrollingText( game,
                                        objects->text,
                                        game->battle->message,
                                        objects->smallDialogTextPos,
                                        objects->smallDialogTextWidth,
                                        objects->lineSpacing );
}

static void gmRenderer_DrawBattleEnemy( gmGame_t* game )
{
   gmBattleSprite_SetPosition( game->battle->enemy->battleSprite, game->renderer->renderObjects->battle->enemyPos );
   gmWindow_DrawBattleSprite( game->window, game->battle->enemy->battleSprite );
}
