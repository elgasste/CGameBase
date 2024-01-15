#if !defined( RENDERER_H )
#define RENDERER_H

#include "common.h"

typedef struct gmGame_t gmGame_t;

typedef struct gmRenderer_t
{
   sfFloatRect mapViewRect;
   sfVector2f mapViewPadding;
   sfVector2f mapTilePixelOffset;
   sfVector2u mapViewStart;
   sfVector2u mapViewEnd;
}
gmRenderer_t;

gmRenderer_t* gmRenderer_Create();
void gmRenderer_Destroy( gmRenderer_t* renderer );

#endif // RENDERER_H
