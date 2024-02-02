#include "battle_sprite.h"
#include "clock.h"

gmBattleSprite_t* gmBattleSprite_Create( sfTexture* texture, float frameSeconds,
                                         uint32_t idleFrames, uint32_t attackFrames, uint32_t damageFrames, uint32_t deathFrames,
                                         gmBattleSpriteState_t state )
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

   sprite->stateFrames[0] = idleFrames;
   sprite->stateFrames[1] = attackFrames;
   sprite->stateFrames[2] = damageFrames;
   sprite->stateFrames[3] = deathFrames;
   sprite->stateFrames[4] = 1;

   sprite->state = state;

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

void gmBattleSprite_SetState( gmBattleSprite_t* sprite, gmBattleSpriteState_t state )
{
   sfIntRect textureRect = sfSprite_getTextureRect( sprite->sfmlSprite );
   textureRect.left = 0;
   textureRect.top = (int32_t)state * textureRect.height;

   sprite->state = state;
   sprite->elapsedSeconds = 0;
   sfSprite_setTextureRect( sprite->sfmlSprite, textureRect );
}

void gmBattleSprite_Tic( gmBattleSprite_t* sprite, gmClock_t* clock )
{
   uint32_t stateIndex = (uint32_t)sprite->state;
   sfIntRect textureRect = sfSprite_getTextureRect( sprite->sfmlSprite );
   textureRect.top = (int32_t)sprite->state * textureRect.height;

   if ( stateIndex > 4 )
   {
      gmExitWithError( STR_ERROR_BATTLESPRITEINDEX );
      return;
   }

   sprite->elapsedSeconds += clock->frameDelta;

   while ( sprite->elapsedSeconds > sprite->frameSeconds )
   {
      sprite->elapsedSeconds -= sprite->frameSeconds;
      textureRect.left += textureRect.width;

      if ( textureRect.left >= (int32_t)( textureRect.width * sprite->stateFrames[stateIndex] ) )
      {
         textureRect.left = 0;
      }
   }

   sfSprite_setTextureRect( sprite->sfmlSprite, textureRect );
}
