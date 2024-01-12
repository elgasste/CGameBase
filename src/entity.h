#if !defined( ENTITY_H )
#define ENTITY_H

#include "common.h"

typedef struct gmEntity_t
{
   sfVector2f mapPos;
   sfVector2f mapHitBoxSize;
   sfVector2f velocity;
}
gmEntity_t;

#endif // ENTITY_H
