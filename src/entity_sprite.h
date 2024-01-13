#if !defined( ENTITY_SPRITE_H )
#define ENTITY_SPRITE_H

#include "common.h"
#include "direction.h"

typedef struct gmClock_t gmClock_t;

typedef struct gmEntitySprite_t
{
   sfTexture* texture;
   sfSprite* sfmlSprite;
   uint16_t frames;
   float frameSeconds;
   float elapsedSeconds;
}
gmEntitySprite_t;

gmEntitySprite_t* gmEntitySprite_Create( sfTexture* texture, uint16_t frames, float frameSeconds );
void gmEntitySprite_Destroy( gmEntitySprite_t* sprite );
void gmEntitySprite_SetPosition( gmEntitySprite_t* sprite, sfVector2f pos );
void gmEntitySprite_SetDirection( gmEntitySprite_t* sprite, gmDirection_t direction );
void gmEntitySprite_Tic( gmEntitySprite_t* sprite, gmDirection_t direction, gmClock_t* clock );
void gmEntitySprite_Stop( gmEntitySprite_t* sprite );

#endif // ENTITY_SPRITE_H
