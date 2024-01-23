#include "battle_sprite.h"
#include "clock.h"

gmBattleSprite_t* gmBattleSprite_Create( sfTexture* texture, uint32_t frames, float frameSeconds )
{
   sfIntRect textureRect = { 0, 0, 64, 64 };
   sfVector2f scale = { GRAPHICS_SCALE, GRAPHICS_SCALE };

   gmBattleSprite_t* sprite = (gmBattleSprite_t*)gmAlloc( sizeof( gmBattleSprite_t ), sfTrue );

   sprite->sfmlSprite = gmSprite_Create();

   sfSprite_setTexture( sprite->sfmlSprite, texture, sfFalse );
   sfSprite_setTextureRect( sprite->sfmlSprite, textureRect );
   sfSprite_scale( sprite->sfmlSprite, scale );

   sprite->frames = frames;
   sprite->frameSeconds = frameSeconds;
   sprite->elapsedSeconds = 0;

   return sprite;
}

void gmBattleSprite_Destroy( gmBattleSprite_t* sprite )
{
   gmSprite_Destroy( sprite->sfmlSprite );

   gmFree( sprite, sizeof( gmBattleSprite_t ), sfTrue );
}

void gmBattleSprite_SetPosition( gmBattleSprite_t* sprite, sfVector2f pos )
{
   sfSprite_setPosition( sprite->sfmlSprite, pos );
}

void gmBattleSprite_Tic( gmBattleSprite_t* sprite, gmClock_t* clock )
{
   sfIntRect textureRect = sfSprite_getTextureRect( sprite->sfmlSprite );

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
