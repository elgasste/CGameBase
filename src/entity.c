#include "entity.h"
#include "entity_sprite.h"

gmEntity_t* gmEntity_Create( sfVector2f mapPos,
                             sfVector2f mapHitBoxSize,
                             sfVector2f spriteOffset,
                             sfTexture* spriteTexture )
{
   sfVector2f spritePos = { mapPos.x + spriteOffset.x, mapPos.y + spriteOffset.y };

   gmEntity_t* entity = (gmEntity_t*)gmAlloc( sizeof( gmEntity_t ), sfTrue );

   entity->mapPos = mapPos;
   entity->mapHitBoxSize = mapHitBoxSize;
   entity->velocity.x = 0;
   entity->velocity.y = 0;
   entity->direction = (gmDirection_t)0;
   entity->spriteOffset = spriteOffset;

   entity->sprite = gmEntitySprite_Create( spriteTexture );
   gmEntitySprite_SetPosition( entity->sprite, spritePos );

   return entity;
}

void gmEntity_Destroy( gmEntity_t* entity )
{
   gmEntitySprite_Destroy( entity->sprite );

   gmFree( entity, sizeof( gmEntity_t ), sfTrue );
}
