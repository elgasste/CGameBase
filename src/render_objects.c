#include "render_objects.h"
#include "menus.h"

static gmDiagnosticsRenderObjects_t* gmDiagnosticsRenderObjects_Create();
static gmDebugBarRenderObjects_t* gmDebugBarRenderObjects_Create();
static gmScreenFadeRenderObjects_t* gmScreenFadeRenderObjects_Create();
static gmMapRenderObjects_t* gmMapRenderObjects_Create( sfTexture* mapTilesetTexture );
static gmOverworldMenuRenderObjects_t* gmOverworldMenuRenderObjects_Create();
static gmBattleRenderObjects_t* gmBattleRenderObjects_Create();
static void gmDiagnosticsRenderObjects_Destroy( gmDiagnosticsRenderObjects_t* objects );
static void gmDebugBarRenderObjects_Destroy( gmDebugBarRenderObjects_t* objects );
static void gmScreenFadeRenderObjects_Destroy( gmScreenFadeRenderObjects_t* objects );
static void gmMapRenderObjects_Destroy( gmMapRenderObjects_t* objects );
static void gmOverworldMenuRenderObjects_Destroy( gmOverworldMenuRenderObjects_t* objects );
static void gmBattleRenderObjects_Destroy( gmBattleRenderObjects_t* objects );
static void gmRenderObjects_BuildDialogBackground( sfConvexShape* shape,
                                                   float x, float y,
                                                   float w, float h,
                                                   float cornerRadius,
                                                   sfColor color );

gmRenderObjects_t* gmRenderObjects_Create()
{
   sfVector2f windowBackgroundSize = { WINDOW_WIDTH, WINDOW_HEIGHT };
   sfVector2f windowBackgroundPosition = { 0, 0 };

   gmRenderObjects_t* renderObjects = (gmRenderObjects_t*)gmAlloc( sizeof( gmRenderObjects_t ), sfTrue );

   // TODO: define these filenames somewhere?
   renderObjects->mapTilesetTexture = gmTexture_CreateFromFile( "resources/textures/tiles/map_tileset.png" );
   renderObjects->playerSpriteTexture = gmTexture_CreateFromFile( "resources/textures/sprites/player.png" );
   renderObjects->enemySpriteTexture = gmTexture_CreateFromFile( "resources/textures/sprites/enemy.png" );

   renderObjects->diagnostics = gmDiagnosticsRenderObjects_Create();
   renderObjects->debugBar = gmDebugBarRenderObjects_Create();
   renderObjects->screenFade = gmScreenFadeRenderObjects_Create();
   renderObjects->map = gmMapRenderObjects_Create( renderObjects->mapTilesetTexture );
   renderObjects->overworldMenu = gmOverworldMenuRenderObjects_Create();
   renderObjects->battle = gmBattleRenderObjects_Create();

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

static gmScreenFadeRenderObjects_t* gmScreenFadeRenderObjects_Create()
{
   sfVector2f v = { 0, 0 };

   gmScreenFadeRenderObjects_t* objects = (gmScreenFadeRenderObjects_t*)gmAlloc( sizeof( gmScreenFadeRenderObjects_t ), sfTrue );

   objects->screenRect = gmRectangleShape_Create();

   sfRectangleShape_setPosition( objects->screenRect, v );
   v.x = WINDOW_WIDTH;
   v.y = WINDOW_HEIGHT;
   sfRectangleShape_setSize( objects->screenRect, v );

   objects->lightColor = sfWhite;
   objects->darkColor = sfBlack;

   return objects;
}

static gmMapRenderObjects_t* gmMapRenderObjects_Create( sfTexture* mapTilesetTexture)
{
   sfVector2f tilesetScale = { GRAPHICS_SCALE, GRAPHICS_SCALE };

   gmMapRenderObjects_t* objects = (gmMapRenderObjects_t*)gmAlloc( sizeof( gmMapRenderObjects_t ), sfTrue );

   objects->tileSprite = gmSprite_Create();
   sfSprite_setTexture( objects->tileSprite, mapTilesetTexture, sfFalse );
   sfSprite_scale( objects->tileSprite, tilesetScale );

   return objects;
}

static gmOverworldMenuRenderObjects_t* gmOverworldMenuRenderObjects_Create()
{
   sfVector2f textScale = { GRAPHICS_SCALE, GRAPHICS_SCALE };
   gmOverworldMenuRenderObjects_t* objects = (gmOverworldMenuRenderObjects_t*)gmAlloc( sizeof( gmOverworldMenuRenderObjects_t ), sfTrue );

   objects->menuPos.x = 64;
   objects->menuPos.y = 64;
   objects->itemsOffset.x = 48;
   objects->itemsOffset.y = 32;
   objects->caratOffset.x = -32;
   objects->caratOffset.y = 0;

   objects->backgroundShape = gmConvexShape_Create();
   gmRenderObjects_BuildDialogBackground( objects->backgroundShape,
                                          objects->menuPos.x, objects->menuPos.y,
                                          256, 150,
                                          16,
                                          DIALOG_BACKDROP_LIGHTCOLOR );

   objects->font = gmFont_CreateFromFile( GAME_FONT );
   objects->text = gmText_Create();
   sfText_setFont( objects->text, objects->font );
   sfText_setCharacterSize( objects->text, GAME_FONT_SIZE );
   sfText_scale( objects->text, textScale );
   sfText_setFillColor( objects->text, GAME_FONT_COLOR );

   return objects;
}

static gmBattleRenderObjects_t* gmBattleRenderObjects_Create()
{
   sfVector2f textScale = { GRAPHICS_SCALE, GRAPHICS_SCALE };

   gmBattleRenderObjects_t* objects = (gmBattleRenderObjects_t*)gmAlloc( sizeof( gmBattleRenderObjects_t ), sfTrue );

   objects->statusDialogBackground = gmConvexShape_Create();
   gmRenderObjects_BuildDialogBackground( objects->statusDialogBackground,
                                          32, 32,
                                          288, 192,
                                          16,
                                          DIALOG_BACKDROP_DARKCOLOR );

   objects->largeDialogBackground = gmConvexShape_Create();
   gmRenderObjects_BuildDialogBackground( objects->largeDialogBackground,
                                          32, WINDOW_HEIGHT - 32 - 192,
                                          WINDOW_WIDTH - 64, 192,
                                          16,
                                          DIALOG_BACKDROP_DARKCOLOR );

   objects->smallDialogBackground = gmConvexShape_Create();
   gmRenderObjects_BuildDialogBackground( objects->smallDialogBackground,
                                          WINDOW_WIDTH - 640 - 32, WINDOW_HEIGHT - 32 - 192,
                                          640, 192,
                                          16,
                                          DIALOG_BACKDROP_DARKCOLOR );

   objects->actionMenuBackground = gmConvexShape_Create();
   gmRenderObjects_BuildDialogBackground( objects->actionMenuBackground,
                                          32, WINDOW_HEIGHT - 32 - 192,
                                          288, 192,
                                          16,
                                          DIALOG_BACKDROP_DARKCOLOR );

   objects->font = gmFont_CreateFromFile( GAME_FONT );
   objects->text = gmText_Create();
   sfText_setFont( objects->text, objects->font );
   sfText_setCharacterSize( objects->text, GAME_FONT_SIZE );
   sfText_scale( objects->text, textScale );
   sfText_setFillColor( objects->text, GAME_FONT_COLOR );

   objects->lineSpacing = 40;
   objects->statusDialogTextPos.x = 64;
   objects->statusDialogTextPos.y = 64;
   objects->largeDialogTextPos.x = 64;
   objects->largeDialogTextPos.y = WINDOW_HEIGHT - 192;
   objects->largeDialogTextWidth = WINDOW_WIDTH - 64 - 64;
   objects->smallDialogTextPos.x = WINDOW_WIDTH - 640;
   objects->smallDialogTextPos.y = WINDOW_HEIGHT - 192;
   objects->smallDialogTextWidth = 640 - 64;
   objects->actionMenuItemsPos.x = 96;
   objects->actionMenuItemsPos.y = WINDOW_HEIGHT - 192;
   objects->actionMenuCaratOffset.x = -32;
   objects->actionMenuCaratOffset.y = 0;
   objects->enemyPos.x = ( WINDOW_WIDTH / 2 ) - 64;
   objects->enemyPos.y = 320;

   return objects;
}

void gmRenderObjects_Destroy( gmRenderObjects_t* objects )
{
   gmBattleRenderObjects_Destroy( objects->battle );
   gmOverworldMenuRenderObjects_Destroy( objects->overworldMenu );
   gmMapRenderObjects_Destroy( objects->map );
   gmScreenFadeRenderObjects_Destroy( objects->screenFade );
   gmDebugBarRenderObjects_Destroy( objects->debugBar );
   gmDiagnosticsRenderObjects_Destroy( objects->diagnostics );

   gmRectangleShape_Destroy( objects->entityRect );
   gmRectangleShape_Destroy( objects->windowBackgroundRect );

   gmTexture_Destroy( objects->enemySpriteTexture );
   gmTexture_Destroy( objects->playerSpriteTexture );
   gmTexture_Destroy( objects->mapTilesetTexture );

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

static void gmScreenFadeRenderObjects_Destroy( gmScreenFadeRenderObjects_t* objects )
{
   gmRectangleShape_Destroy( objects->screenRect );

   gmFree( objects, sizeof( gmScreenFadeRenderObjects_t ), sfTrue );
}

static void gmMapRenderObjects_Destroy( gmMapRenderObjects_t* objects )
{
   gmSprite_Destroy( objects->tileSprite );

   gmFree( objects, sizeof( gmMapRenderObjects_t ), sfTrue );
}

static void gmOverworldMenuRenderObjects_Destroy( gmOverworldMenuRenderObjects_t* objects )
{
   gmText_Destroy( objects->text );
   gmFont_Destroy( objects->font );
   gmConvexShape_Destroy( objects->backgroundShape );

   gmFree( objects, sizeof( gmOverworldMenuRenderObjects_t ), sfTrue );
}

static void gmBattleRenderObjects_Destroy( gmBattleRenderObjects_t* objects )
{
   gmText_Destroy( objects->text );
   gmFont_Destroy( objects->font );
   gmConvexShape_Destroy( objects->actionMenuBackground );
   gmConvexShape_Destroy( objects->smallDialogBackground );
   gmConvexShape_Destroy( objects->largeDialogBackground );
   gmConvexShape_Destroy( objects->statusDialogBackground );

   gmFree( objects, sizeof( gmBattleRenderObjects_t ), sfTrue );
}

static void gmRenderObjects_BuildDialogBackground( sfConvexShape* shape,
                                                   float x, float y,
                                                   float w, float h,
                                                   float cornerRadius,
                                                   sfColor color )
{
   sfVector2f pt = { x, y };

   sfConvexShape_setPointCount( shape, 8 );
   sfConvexShape_setPosition( shape, pt );
   sfConvexShape_setFillColor( shape, color );

   pt.x = cornerRadius;
   pt.y = 0;
   sfConvexShape_setPoint( shape, 0, pt );
   pt.x = w - cornerRadius;
   sfConvexShape_setPoint( shape, 1, pt );
   pt.x = w;
   pt.y = cornerRadius;
   sfConvexShape_setPoint( shape, 2, pt );
   pt.y = h - cornerRadius;
   sfConvexShape_setPoint( shape, 3, pt );
   pt.x = w - cornerRadius;
   pt.y = h;
   sfConvexShape_setPoint( shape, 4, pt );
   pt.x = cornerRadius;
   sfConvexShape_setPoint( shape, 5, pt );
   pt.x = 0;
   pt.y = h - cornerRadius;
   sfConvexShape_setPoint( shape, 6, pt );
   pt.y = cornerRadius;
   sfConvexShape_setPoint( shape, 7, pt );
}
