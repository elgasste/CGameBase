#include "render_objects.h"
#include "game.h"
#include "menus.h"

static gmDiagnosticsRenderObjects_t* gmDiagnosticsRenderObjects_Create();
static gmDebugBarRenderObjects_t* gmDebugBarRenderObjects_Create();
static gmMapRenderObjects_t* gmMapRenderObjects_Create( gmGame_t* game );
static gmOverworldMenuRenderObjects_t* gmOverworldMenuRenderObjects_Create();
static void gmDiagnosticsRenderObjects_Destroy( gmDiagnosticsRenderObjects_t* objects );
static void gmDebugBarRenderObjects_Destroy( gmDebugBarRenderObjects_t* objects );
static void gmMapRenderObjects_Destroy( gmMapRenderObjects_t* objects );
static void gmMenuRenderObjects_Destroy( gmOverworldMenuRenderObjects_t* objects );

gmRenderObjects_t* gmRenderObjects_Create( gmGame_t* game )
{
   sfVector2f windowBackgroundSize = { WINDOW_WIDTH, WINDOW_HEIGHT };
   sfVector2f windowBackgroundPosition = { 0, 0 };

   gmRenderObjects_t* renderObjects = (gmRenderObjects_t*)gmAlloc( sizeof( gmRenderObjects_t ), sfTrue );
   renderObjects->diagnosticsRenderObjects = gmDiagnosticsRenderObjects_Create();
   renderObjects->debugBarRenderObjects = gmDebugBarRenderObjects_Create();
   renderObjects->mapRenderObjects = gmMapRenderObjects_Create( game );
   renderObjects->overworldMenuRenderObjects = gmOverworldMenuRenderObjects_Create();

   renderObjects->windowBackgroundRect = gmRectangleShape_Create();
   sfRectangleShape_setSize( renderObjects->windowBackgroundRect, windowBackgroundSize );
   sfRectangleShape_setPosition( renderObjects->windowBackgroundRect, windowBackgroundPosition );
   sfRectangleShape_setFillColor( renderObjects->windowBackgroundRect, sfBlack );

   renderObjects->entityRect = gmRectangleShape_Create();
   sfRectangleShape_setFillColor( renderObjects->entityRect, sfBlue );

   return renderObjects;
}

static gmDiagnosticsRenderObjects_t* gmDiagnosticsRenderObjects_Create()
{
   sfVector2f backgroundSize = { 180, 64 };
   sfVector2f backgroundPos = { WINDOW_WIDTH - backgroundSize.x, 0 };

   gmDiagnosticsRenderObjects_t* objects = (gmDiagnosticsRenderObjects_t*)gmAlloc( sizeof( gmDiagnosticsRenderObjects_t ), sfTrue );

   objects->backgroundRect = gmRectangleShape_Create();
   sfRectangleShape_setSize( objects->backgroundRect, backgroundSize );
   sfRectangleShape_setPosition( objects->backgroundRect, backgroundPos );
   sfRectangleShape_setFillColor( objects->backgroundRect, sfBlue );
   objects->font = gmFont_CreateFromFile( DEBUG_FONT );
   objects->textPosition.x = WINDOW_WIDTH - backgroundSize.x + 8;
   objects->text = gmText_Create();
   sfText_setFont( objects->text, objects->font );
   sfText_setCharacterSize( objects->text, 12 );
   sfText_setFillColor( objects->text, sfWhite );
   objects->lineSpacing = sfFont_getLineSpacing( objects->font, sfText_getCharacterSize( objects->text ) );

   return objects;
}

static gmDebugBarRenderObjects_t* gmDebugBarRenderObjects_Create()
{
   sfVector2f backgroundSize = { 250, 16 };
   sfVector2f backgroundPos = { 10, 10 };
   sfVector2f textPos = { 14, 10 };

   gmDebugBarRenderObjects_t* objects = (gmDebugBarRenderObjects_t*)gmAlloc( sizeof( gmDebugBarRenderObjects_t ), sfTrue );

   objects->backgroundRect = gmRectangleShape_Create();
   sfRectangleShape_setSize( objects->backgroundRect, backgroundSize );
   sfRectangleShape_setPosition( objects->backgroundRect, backgroundPos );
   sfRectangleShape_setFillColor( objects->backgroundRect, sfWhite );
   objects->font = gmFont_CreateFromFile( DEBUG_FONT );
   objects->text = gmText_Create();
   sfText_setFont( objects->text, objects->font );
   sfText_setCharacterSize( objects->text, 12 );
   sfText_setFillColor( objects->text, sfBlack );
   sfText_setPosition( objects->text, textPos );

   return objects;
}

static gmMapRenderObjects_t* gmMapRenderObjects_Create( gmGame_t* game )
{
   sfVector2f tilesetScale = { GRAPHICS_SCALE, GRAPHICS_SCALE };

   gmMapRenderObjects_t* objects = (gmMapRenderObjects_t*)gmAlloc( sizeof( gmMapRenderObjects_t ), sfTrue );

   objects->tileSprite = gmSprite_Create();
   sfSprite_setTexture( objects->tileSprite, game->mapTilesetTexture, sfFalse );
   sfSprite_scale( objects->tileSprite, tilesetScale );

   return objects;
}

static gmOverworldMenuRenderObjects_t* gmOverworldMenuRenderObjects_Create()
{
   sfVector2f textScale = { GRAPHICS_SCALE, GRAPHICS_SCALE };
   sfVector2f pos, size;
   float w = 256, h = 142, cornerRadius = 10;
   gmOverworldMenuRenderObjects_t* objects = (gmOverworldMenuRenderObjects_t*)gmAlloc( sizeof( gmOverworldMenuRenderObjects_t ), sfTrue );

   objects->menuPos.x = 64;
   objects->menuPos.y = 64;
   objects->itemsOffset.x = 48;
   objects->itemsOffset.y = 32;
   objects->caratOffset.x = -32;
   objects->caratOffset.y = 0;

   objects->backgroundRects[0] = gmRectangleShape_Create();
   objects->backgroundRects[1] = gmRectangleShape_Create();
   objects->backgroundRects[2] = gmRectangleShape_Create();
   objects->cornerRounds[0] = gmCircleShape_Create();
   objects->cornerRounds[1] = gmCircleShape_Create();
   objects->cornerRounds[2] = gmCircleShape_Create();
   objects->cornerRounds[3] = gmCircleShape_Create();

   // left side
   pos.x = objects->menuPos.x;
   pos.y = objects->menuPos.y + cornerRadius;
   size.x = cornerRadius;
   size.y = h - ( 2 * cornerRadius );
   sfRectangleShape_setPosition( objects->backgroundRects[0], pos );
   sfRectangleShape_setSize( objects->backgroundRects[0], size );
   sfRectangleShape_setFillColor( objects->backgroundRects[0], sfBlack );

   // middle
   pos.x = objects->menuPos.x + cornerRadius;
   pos.y = objects->menuPos.y;
   size.x = w - ( cornerRadius * 2 );
   size.y = h;
   sfRectangleShape_setPosition( objects->backgroundRects[1], pos );
   sfRectangleShape_setSize( objects->backgroundRects[1], size );
   sfRectangleShape_setFillColor( objects->backgroundRects[1], sfBlack );

   // right side
   pos.x = objects->menuPos.x + ( w - cornerRadius );
   pos.y = objects->menuPos.y + cornerRadius;
   size.x = cornerRadius;
   size.y = h - ( 2 * cornerRadius );
   sfRectangleShape_setPosition( objects->backgroundRects[2], pos );
   sfRectangleShape_setSize( objects->backgroundRects[2], size );
   sfRectangleShape_setFillColor( objects->backgroundRects[2], sfBlack );

   // upper-left corner
   pos.x = objects->menuPos.x;
   pos.y = objects->menuPos.y;
   sfCircleShape_setPosition( objects->cornerRounds[0], pos );
   sfCircleShape_setRadius( objects->cornerRounds[0], cornerRadius );
   sfCircleShape_setFillColor( objects->cornerRounds[0], sfBlack );

   // upper-right corner
   pos.x = objects->menuPos.x + w - ( cornerRadius * 2 );
   pos.y = objects->menuPos.y;
   sfCircleShape_setPosition( objects->cornerRounds[1], pos );
   sfCircleShape_setRadius( objects->cornerRounds[1], cornerRadius );
   sfCircleShape_setFillColor( objects->cornerRounds[1], sfBlack );

   // lower-left corner
   pos.x = objects->menuPos.x;
   pos.y = objects->menuPos.y + h - ( cornerRadius * 2 );
   sfCircleShape_setPosition( objects->cornerRounds[2], pos );
   sfCircleShape_setRadius( objects->cornerRounds[2], cornerRadius );
   sfCircleShape_setFillColor( objects->cornerRounds[2], sfBlack );

   // lower-right corner
   pos.x = objects->menuPos.x + w - ( cornerRadius * 2 );
   pos.y = objects->menuPos.y + h - ( cornerRadius * 2 );
   sfCircleShape_setPosition( objects->cornerRounds[3], pos );
   sfCircleShape_setRadius( objects->cornerRounds[3], cornerRadius );
   sfCircleShape_setFillColor( objects->cornerRounds[3], sfBlack );

   objects->font = gmFont_CreateFromFile( GAME_FONT );
   objects->text = gmText_Create();
   sfText_setFont( objects->text, objects->font );
   sfText_setCharacterSize( objects->text, GAME_FONT_SIZE );
   sfText_scale( objects->text, textScale );
   sfText_setFillColor( objects->text, sfWhite );

   return objects;
}

void gmRenderObjects_Destroy( gmRenderObjects_t* objects )
{
   gmMenuRenderObjects_Destroy( objects->overworldMenuRenderObjects );
   gmMapRenderObjects_Destroy( objects->mapRenderObjects );
   gmDebugBarRenderObjects_Destroy( objects->debugBarRenderObjects );
   gmDiagnosticsRenderObjects_Destroy( objects->diagnosticsRenderObjects );

   gmRectangleShape_Destroy( objects->entityRect );
   gmRectangleShape_Destroy( objects->windowBackgroundRect );

   gmFree( objects, sizeof( gmRenderObjects_t ), sfTrue );
}

void gmDiagnosticsRenderObjects_Destroy( gmDiagnosticsRenderObjects_t* objects )
{
   gmText_Destroy( objects->text );
   gmFont_Destroy( objects->font );
   gmRectangleShape_Destroy( objects->backgroundRect );

   gmFree( objects, sizeof( gmDiagnosticsRenderObjects_t ), sfTrue );
}

static void gmDebugBarRenderObjects_Destroy( gmDebugBarRenderObjects_t* objects )
{
   gmText_Destroy( objects->text );
   gmFont_Destroy( objects->font );
   gmRectangleShape_Destroy( objects->backgroundRect );

   gmFree( objects, sizeof( gmDebugBarRenderObjects_t ), sfTrue );
}

static void gmMapRenderObjects_Destroy( gmMapRenderObjects_t* objects )
{
   gmSprite_Destroy( objects->tileSprite );

   gmFree( objects, sizeof( gmMapRenderObjects_t ), sfTrue );
}

static void gmMenuRenderObjects_Destroy( gmOverworldMenuRenderObjects_t* objects )
{
   gmText_Destroy( objects->text );
   gmFont_Destroy( objects->font );
   gmRectangleShape_Destroy( objects->backgroundRects[0] );
   gmRectangleShape_Destroy( objects->backgroundRects[1] );
   gmRectangleShape_Destroy( objects->backgroundRects[2] );
   gmCircleShape_Destroy( objects->cornerRounds[0] );
   gmCircleShape_Destroy( objects->cornerRounds[1] );
   gmCircleShape_Destroy( objects->cornerRounds[2] );
   gmCircleShape_Destroy( objects->cornerRounds[3] );

   gmFree( objects, sizeof( gmOverworldMenuRenderObjects_t ), sfTrue );
}
