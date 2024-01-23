#if !defined( BATTLE_SPRITE_H )
#define BATTLE_SPRITE_H

#include "common.h"

typedef struct gmClock_t gmClock_t;

typedef struct gmBattleSprite_t
{
   sfTexture* texture;
   sfSprite* sfmlSprite;
   uint32_t frames;
   float frameSeconds;
   float elapsedSeconds;
}
gmBattleSprite_t;

gmBattleSprite_t* gmBattleSprite_Create( sfTexture* texture, uint32_t frames, float frameSeconds );
void gmBattleSprite_Destroy( gmBattleSprite_t* sprite );
void gmBattleSprite_SetPosition( gmBattleSprite_t* sprite, sfVector2f pos );
void gmBattleSprite_Tic( gmBattleSprite_t* sprite, gmClock_t* clock );

#endif // BATTLE_SPRITE_H
