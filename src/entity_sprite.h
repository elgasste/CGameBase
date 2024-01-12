#if !defined( ENTITY_SPRITE_H )
#define ENTITY_SPRITE_H

#include "common.h"

typedef struct gmEntitySprite_t
{
   sfTexture* texture;
   sfSprite* sfmlSprite;
}
gmEntitySprite_t;

#endif // ENTITY_SPRITE_H
