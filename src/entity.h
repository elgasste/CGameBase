#if !defined( ENTITY_H )
#define ENTITY_H

#include "common.h"
#include "direction.h"

typedef struct gmEntitySprite_t gmEntitySprite_t;

typedef struct gmEntity_t
{
   sfVector2f mapPos;
   sfVector2f mapHitBoxSize;
   sfVector2f velocity;
   gmDirection_t direction;
   gmEntitySprite_t* sprite;
   sfVector2f spriteOffset;

}
gmEntity_t;

gmEntity_t* gmEntity_Create( sfVector2f mapPos,
                             sfVector2f mapHitBoxSize,
                             sfVector2f spriteOffset,
                             sfTexture* spriteTexture );
void gmEntity_Destroy( gmEntity_t* entity );

#endif // ENTITY_H
