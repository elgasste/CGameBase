#include "entity.h"
#include "entity_sprite.h"

gmEntity_t* gmEntity_Create( sfVector2f mapPos,
                             sfVector2f mapHitBoxSize,
                             float maxVelocity,
                             sfVector2f spriteOffset,
                             sfTexture* spriteTexture )
{
   sfVector2f spritePos = { mapPos.x + spriteOffset.x, mapPos.y + spriteOffset.y };

   gmEntity_t* entity = (gmEntity_t*)gmAlloc( sizeof( gmEntity_t ), sfTrue );

   entity->mapPos = mapPos;
   entity->mapHitBoxSize = mapHitBoxSize;
   entity->velocity.x = 0;
   entity->velocity.y = 0;
   entity->maxVelocity = maxVelocity;
   entity->direction = (gmDirection_t)0;
   entity->spriteOffset = spriteOffset;

   entity->sprite = gmEntitySprite_Create( spriteTexture, 4, 0.15f );
   gmEntitySprite_SetPosition( entity->sprite, spritePos );
   gmEntitySprite_SetDirection( entity->sprite, entity->direction );

   return entity;
}

void gmEntity_Destroy( gmEntity_t* entity )
{
   gmEntitySprite_Destroy( entity->sprite );

   gmFree( entity, sizeof( gmEntity_t ), sfTrue );
}

void gmEntity_Tic( gmEntity_t* entity, gmClock_t* clock )
{
   if ( entity->velocity.x != 0 || entity->velocity.y != 0 )
   {
      gmEntitySprite_Tic( entity->sprite, entity->direction, clock );
   }
   else
   {
      gmEntitySprite_Stop( entity->sprite );
   }
}

void gmEntity_SetDirection( gmEntity_t* entity, gmDirection_t direction )
{
   entity->direction = direction;
   gmEntitySprite_SetDirection( entity->sprite, direction );
}
