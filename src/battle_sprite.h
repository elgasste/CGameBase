#if !defined( BATTLE_SPRITE_H )
#define BATTLE_SPRITE_H

#include "common.h"

typedef struct gmClock_t gmClock_t;

typedef struct gmBattleSprite_t
{
   sfTexture* texture;
   sfSprite* sfmlSprite;

   float frameSeconds;
   float elapsedSeconds;

   uint32_t idleFrames;
   uint32_t attackFrames;
   uint32_t damageFrames;
   uint32_t deathFrames;
}
gmBattleSprite_t;

gmBattleSprite_t* gmBattleSprite_Create( sfTexture* texture, float frameSeconds,
                                         uint32_t idleFrames, uint32_t attackFrames, uint32_t damageFrames, uint32_t deathFrames );
void gmBattleSprite_Destroy( gmBattleSprite_t* sprite );
void gmBattleSprite_SetPosition( gmBattleSprite_t* sprite, sfVector2f pos );
void gmBattleSprite_Tic( gmBattleSprite_t* sprite, gmClock_t* clock );

#endif // BATTLE_SPRITE_H
