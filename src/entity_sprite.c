#include "entity_sprite.h"

gmEntitySprite_t* gmEntitySprite_Create( sfTexture* texture )
{
   sfIntRect textureRect = { 0, 0, 32, 32 };
   sfVector2f scale = { 2, 2 };

   gmEntitySprite_t* sprite = (gmEntitySprite_t*)gmAlloc( sizeof( gmEntitySprite_t ), sfTrue );

   sprite->sfmlSprite = gmSprite_Create();

   sfSprite_setTexture( sprite->sfmlSprite, texture, sfFalse );
   sfSprite_setTextureRect( sprite->sfmlSprite, textureRect );
   sfSprite_scale( sprite->sfmlSprite, scale );

   return sprite;
}

void gmEntitySprite_Destroy( gmEntitySprite_t* sprite )
{
   gmSprite_Destroy( sprite->sfmlSprite );

   gmFree( sprite, sizeof( gmEntitySprite_t ), sfTrue );
}

void gmEntitySprite_SetPosition( gmEntitySprite_t* sprite, sfVector2f pos )
{
   sfSprite_setPosition( sprite->sfmlSprite, pos );
}
