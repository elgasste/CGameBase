#if !defined( RENDER_OBJECTS_H )
#define RENDER_OBJECTS_H

#include "common.h"

typedef struct gmRenderer_t gmRenderer_t;

typedef struct gmDiagnosticsRenderObjects_t
{
   sfRectangleShape* backgroundRect;
   sfFont* font;
   sfText* text;
   sfVector2f textPosition;
   float lineSpacing;
}
gmDiagnosticsRenderObjects_t;

typedef struct gmDebugBarRenderObjects_t
{
   sfRectangleShape* backgroundRect;
   sfFont* font;
   sfText* text;
}
gmDebugBarRenderObjects_t;

typedef struct gmScreenFadeRenderObjects_t
{
   sfRectangleShape* screenRect;
   sfColor lightColor;
   sfColor darkColor;
}
gmScreenFadeRenderObjects_t;

typedef struct gmMapRenderObjects_t
{
   sfSprite* tileSprite;
}
gmMapRenderObjects_t;

typedef struct gmOverworldMenuRenderObjects_t
{
   sfConvexShape* backgroundShape;
   sfFont* font;
   sfText* text;
   sfVector2f menuPos;
   sfVector2f itemsOffset;
   sfVector2f caratOffset;
}
gmOverworldMenuRenderObjects_t;

typedef struct gmBattleRenderObjects_t
{
   sfConvexShape* statusDialogBackground;
   sfConvexShape* largeDialogBackground;
   sfConvexShape* smallDialogBackground;
   sfConvexShape* actionMenuBackground;
   sfFont* font;
   sfText* text;
   float lineSpacing;
   float largeDialogTextWidth;
   sfVector2f statusDialogTextPos;
   sfVector2f largeDialogTextPos;
   sfVector2f smallDialogTextPos;
   float smallDialogTextWidth;
   sfVector2f actionMenuItemsPos;
   sfVector2f actionMenuCaratOffset;
   sfVector2f enemyPos;
}
gmBattleRenderObjects_t;

typedef struct gmRenderObjects_t
{
   gmDiagnosticsRenderObjects_t* diagnostics;
   gmDebugBarRenderObjects_t* debugBar;
   gmScreenFadeRenderObjects_t* screenFade;
   gmMapRenderObjects_t* map;
   gmOverworldMenuRenderObjects_t* overworldMenu;
   gmBattleRenderObjects_t* battle;

   sfTexture* mapTilesetTexture;
   sfTexture* playerSpriteTexture;
   sfTexture* enemySpriteTexture;
   sfRectangleShape* windowBackgroundRect;
   sfRectangleShape* entityRect;
}
gmRenderObjects_t;

gmRenderObjects_t* gmRenderObjects_Create();
void gmRenderObjects_Destroy( gmRenderObjects_t* renderObjects );

#endif // RENDER_OBJECTS_H
