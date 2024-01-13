#if !defined( ENTITY_SPRITE_H )
#define ENTITY_SPRITE_H

#include "common.h"

typedef struct gmEntitySprite_t
{
   sfTexture* texture;
   sfSprite* sfmlSprite;
}
gmEntitySprite_t;

gmEntitySprite_t* gmEntitySprite_Create( sfTexture* texture );
void gmEntitySprite_Destroy( gmEntitySprite_t* sprite );
void gmEntitySprite_SetPosition( gmEntitySprite_t* sprite, sfVector2f pos );

#endif // ENTITY_SPRITE_H
