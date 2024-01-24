#include "battle_sprite.h"
#include "clock.h"

gmBattleSprite_t* gmBattleSprite_Create( sfTexture* texture, float frameSeconds,
                                         uint32_t idleFrames, uint32_t attackFrames, uint32_t damageFrames, uint32_t deathFrames )
{
   sfIntRect textureRect = { 0, 0, 64, 64 };
   sfVector2f scale = { GRAPHICS_SCALE, GRAPHICS_SCALE };

   gmBattleSprite_t* sprite = (gmBattleSprite_t*)gmAlloc( sizeof( gmBattleSprite_t ), sfTrue );

   sprite->sfmlSprite = gmSprite_Create();

   sfSprite_setTexture( sprite->sfmlSprite, texture, sfFalse );
   sfSprite_setTextureRect( sprite->sfmlSprite, textureRect );
   sfSprite_scale( sprite->sfmlSprite, scale );

   sprite->frameSeconds = frameSeconds;
   sprite->elapsedSeconds = 0;

   sprite->idleFrames = idleFrames;
   sprite->attackFrames = attackFrames;
   sprite->damageFrames = damageFrames;
   sprite->deathFrames = deathFrames;

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

      if ( textureRect.left >= (int32_t)( textureRect.width * sprite->idleFrames ) )
      {
         textureRect.left = 0;
      }
   }

   sfSprite_setTextureRect( sprite->sfmlSprite, textureRect );
}
