#if !defined( ENTITY_H )
#define ENTITY_H

#include "common.h"
#include "enums.h"

typedef struct gmEntitySprite_t gmEntitySprite_t;
typedef struct gmClock_t gmClock_t;

typedef struct gmEntity_t
{
   sfVector2f mapPos;
   sfVector2f mapHitBoxSize;
   sfVector2f velocity;
   float maxVelocity;
   gmDirection_t direction;
   gmEntitySprite_t* sprite;
   sfVector2f spriteOffset;

}
gmEntity_t;

gmEntity_t* gmEntity_Create( sfVector2f mapPos,
                             sfVector2f mapHitBoxSize,
                             float maxVelocity,
                             sfVector2f spriteOffset,
                             sfTexture* spriteTexture );
void gmEntity_Destroy( gmEntity_t* entity );
void gmEntity_Tic( gmEntity_t* entity, gmClock_t* clock );
void gmEntity_SetDirection( gmEntity_t* entity, gmDirection_t direction );

#endif // ENTITY_H
