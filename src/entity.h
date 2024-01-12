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

}
gmEntity_t;

#endif // ENTITY_H
