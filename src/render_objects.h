#if !defined( RENDERER_H )
#define RENDERER_H

#include "common.h"

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
   sfRectangleShape* tileRect;
}
gmMapRenderObjects_t;

typedef struct gmRenderObjects_t
{
   gmDiagnosticsRenderObjects_t* diagnosticsRenderObjects;
   gmDebugBarRenderObjects_t* debugBarRenderObjects;
   gmMapRenderObjects_t* mapRenderObjects;

   sfRectangleShape* windowBackgroundRect;

   sfRectangleShape* entityRect;
}
gmRenderObjects_t;

gmRenderObjects_t* gmRenderObjects_Create();
void gmRenderObjects_Destroy( gmRenderObjects_t* renderObjects );

#endif // RENDERER_H

