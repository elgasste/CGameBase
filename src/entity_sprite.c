#include "entity_sprite.h"
#include "clock.h"

gmEntitySprite_t* gmEntitySprite_Create( sfTexture* texture, uint32_t frames, float frameSeconds )
{
   sfIntRect textureRect = { 0, 0, 32, 32 };
   sfVector2f scale = { GRAPHICS_SCALE, GRAPHICS_SCALE };

   gmEntitySprite_t* sprite = (gmEntitySprite_t*)gmAlloc( sizeof( gmEntitySprite_t ), sfTrue );

   sprite->sfmlSprite = gmSprite_Create();

   sfSprite_setTexture( sprite->sfmlSprite, texture, sfFalse );
   sfSprite_setTextureRect( sprite->sfmlSprite, textureRect );
   sfSprite_scale( sprite->sfmlSprite, scale );

   sprite->frames = frames;
   sprite->frameSeconds = frameSeconds;
   sprite->elapsedSeconds = 0;

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

void gmEntitySprite_SetDirection( gmEntitySprite_t* sprite, gmDirection_t direction )
{
   sfIntRect textureRect = sfSprite_getTextureRect( sprite->sfmlSprite );
   textureRect.top = (int32_t)direction * textureRect.height;
   sfSprite_setTextureRect( sprite->sfmlSprite, textureRect );
}

void gmEntitySprite_Tic( gmEntitySprite_t* sprite, gmDirection_t direction, gmClock_t* clock )
{
   sfIntRect textureRect = sfSprite_getTextureRect( sprite->sfmlSprite );
   textureRect.top = (int32_t)direction * textureRect.height;

   sprite->elapsedSeconds += clock->frameDelta;

   while ( sprite->elapsedSeconds > sprite->frameSeconds )
   {
      sprite->elapsedSeconds -= sprite->frameSeconds;
      textureRect.left += textureRect.width;

      if ( textureRect.left >= (int32_t)( textureRect.width * sprite->frames ) )
      {
         textureRect.left = 0;
      }
   }

   sfSprite_setTextureRect( sprite->sfmlSprite, textureRect );
}

void gmEntitySprite_Stop( gmEntitySprite_t* sprite )
{
   sfIntRect textureRect = sfSprite_getTextureRect( sprite->sfmlSprite );
   textureRect.left = 0;
   sfSprite_setTextureRect( sprite->sfmlSprite, textureRect );
   sprite->elapsedSeconds = 0;
}
