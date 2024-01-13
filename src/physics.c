#include "physics.h"
#include "game.h"
#include "entity.h"
#include "entity_sprite.h"
#include "clock.h"

#define COLLISION_PADDING 0.0001f

void gmPhysics_Tic( gmGame_t* game )
{
   gmEntity_t* entity = game->entity;

   entity->mapPos.x += entity->velocity.x * game->clock->frameDelta;
   entity->mapPos.y += entity->velocity.y * game->clock->frameDelta;

   if ( entity->mapPos.x <= 0 )
   {
      entity->mapPos.x = COLLISION_PADDING;
   }
   else if ( entity->mapPos.x + entity->mapHitBoxSize.x >= WINDOW_WIDTH )
   {
      entity->mapPos.x = WINDOW_WIDTH - entity->mapHitBoxSize.x - COLLISION_PADDING;
   }

   if ( entity->mapPos.y <= 0 )
   {
      entity->mapPos.y = COLLISION_PADDING;
   }
   else if ( entity->mapPos.y + entity->mapHitBoxSize.y >= WINDOW_HEIGHT )
   {
      entity->mapPos.y = WINDOW_HEIGHT - entity->mapHitBoxSize.y - COLLISION_PADDING;
   }

   gmEntity_Tic( entity, game->clock );

   entity->velocity.x = 0;
   entity->velocity.y = 0;
}
