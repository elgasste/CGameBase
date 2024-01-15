#include "render_objects.h"
#include "game.h"

static gmDiagnosticsRenderObjects_t* gmDiagnosticsRenderObjects_Create();
static gmDebugBarRenderObjects_t* gmDebugBarRenderObjects_Create();
static gmMapRenderObjects_t* gmMapRenderObjects_Create( gmGame_t* game );
static void gmDiagnosticsRenderObjects_Destroy( gmDiagnosticsRenderObjects_t* objects );
static void gmDebugBarRenderObjects_Destroy( gmDebugBarRenderObjects_t* objects );
static void gmMapRenderObjects_Destroy( gmMapRenderObjects_t* objects );

gmRenderObjects_t* gmRenderObjects_Create( gmGame_t* game )
{
   sfVector2f windowBackgroundSize = { WINDOW_WIDTH, WINDOW_HEIGHT };
   sfVector2f windowBackgroundPosition = { 0, 0 };

   gmRenderObjects_t* renderObjects = (gmRenderObjects_t*)gmAlloc( sizeof( gmRenderObjects_t ), sfTrue );
   renderObjects->diagnosticsRenderObjects = gmDiagnosticsRenderObjects_Create();
   renderObjects->debugBarRenderObjects = gmDebugBarRenderObjects_Create();
   renderObjects->mapRenderObjects = gmMapRenderObjects_Create( game );

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

void gmRenderObjects_Destroy( gmRenderObjects_t* objects )
{
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
