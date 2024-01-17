#if !defined( RENDERER_H )
#define RENDERER_H

#include "common.h"

typedef struct gmRenderObjects_t gmRenderObjects_t;
typedef struct gmRenderStates_t gmRenderStates_t;
typedef struct gmGame_t gmGame_t;

typedef struct gmRenderer_t
{
   gmRenderObjects_t* renderObjects;
   gmRenderStates_t* renderStates;

   sfFloatRect mapViewRect;
   sfVector2f mapViewPadding;
   sfVector2f mapTilePixelOffset;
   sfVector2u mapViewStart;
   sfVector2u mapViewEnd;
}
gmRenderer_t;

gmRenderer_t* gmRenderer_Create();
void gmRenderer_Destroy( gmRenderer_t* renderer );
void gmRenderer_Render( gmGame_t* game );

#endif // RENDERER_H
