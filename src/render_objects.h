#if !defined( RENDER_OBJECTS_H )
#define RENDER_OBJECTS_H

#include "common.h"

typedef struct gmGame_t gmGame_t;

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
   sfRectangleShape* backgroundRects[3];
   sfCircleShape* cornerRounds[4];
   sfFont* font;
   sfText* text;
   sfVector2f menuPos;
   sfVector2f itemsOffset;
   sfVector2f caratOffset;
}
gmOverworldMenuRenderObjects_t;

typedef struct gmRenderObjects_t
{
   gmDiagnosticsRenderObjects_t* diagnosticsRenderObjects;
   gmDebugBarRenderObjects_t* debugBarRenderObjects;
   gmMapRenderObjects_t* mapRenderObjects;
   gmOverworldMenuRenderObjects_t* overworldMenuRenderObjects;

   sfRectangleShape* windowBackgroundRect;

   sfRectangleShape* entityRect;
}
gmRenderObjects_t;

gmRenderObjects_t* gmRenderObjects_Create( gmGame_t* game );
void gmRenderObjects_Destroy( gmRenderObjects_t* renderObjects );

#endif // RENDER_OBJECTS_H

