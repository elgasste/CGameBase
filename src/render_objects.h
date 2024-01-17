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
   sfConvexShape* largeDialogBackground;
   sfConvexShape* smallDialogBackground;
   sfConvexShape* actionMenuBackground;
   sfFont* font;
   sfText* text;
   float lineSpacing;
   sfVector2f largeDialogTextPos;
   float largeDialogTextWidth;
   sfVector2f smallDialogTextPos;
   float smallDialogTextWidth;
   sfVector2f actionMenuItemsPos;
}
gmBattleRenderObjects_t;

typedef struct gmRenderObjects_t
{
   gmDiagnosticsRenderObjects_t* diagnosticsRenderObjects;
   gmDebugBarRenderObjects_t* debugBarRenderObjects;
   gmMapRenderObjects_t* mapRenderObjects;
   gmOverworldMenuRenderObjects_t* overworldMenuRenderObjects;
   gmBattleRenderObjects_t* battleRenderObjects;

   sfTexture* mapTilesetTexture;
   sfTexture* entitySpriteTexture;
   sfRectangleShape* windowBackgroundRect;
   sfRectangleShape* entityRect;
}
gmRenderObjects_t;

gmRenderObjects_t* gmRenderObjects_Create();
void gmRenderObjects_Destroy( gmRenderObjects_t* renderObjects );

#endif // RENDER_OBJECTS_H
