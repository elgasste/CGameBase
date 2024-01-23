#include "physics.h"
#include "game.h"
#include "character.h"
#include "entity.h"
#include "entity_sprite.h"
#include "clock.h"
#include "map.h"

#define COLLISION_PADDING 0.01f

gmPhysics_t* gmPhysics_Create()
{
   gmPhysics_t* physics = (gmPhysics_t*)gmAlloc( sizeof( gmPhysics_t ), sfTrue );

   physics->entityMapTileCache = 0;

   return physics;
}

void gmPhysics_Destroy( gmPhysics_t* physics )
{
   gmFree( physics, sizeof( gmPhysics_t ), sfTrue );
}

void gmPhysics_Tic( gmGame_t* game )
{
   gmEntity_t* entity = game->player->entity;
   sfVector2f newPos = entity->mapPos;
   sfVector2f mapSize = { (float)( game->map->tileCount.x * MAP_TILE_SIZE ),
                          (float)( game->map->tileCount.y * MAP_TILE_SIZE ) };
   sfVector2f entityCenterPos;
   uint32_t startRow, endRow, startCol, endCol, row, col;
   gmMapTile_t* tile;
   uint32_t newTileIndex;

   newPos.x += entity->velocity.x * game->clock->frameDelta;

   if ( newPos.x <= 0 )
   {
      newPos.x = COLLISION_PADDING;
   }
   else if ( newPos.x + entity->mapHitBoxSize.x >= mapSize.x )
   {
      newPos.x = mapSize.x - entity->mapHitBoxSize.x - COLLISION_PADDING;
   }
   else if ( newPos.x != entity->mapPos.x && !game->cheatNoClip )
   {
      startRow = (uint32_t)( newPos.y / MAP_TILE_SIZE );
      endRow = (uint32_t)( ( newPos.y + entity->mapHitBoxSize.y ) / MAP_TILE_SIZE );
      col = ( newPos.x < entity->mapPos.x )
         ? (uint32_t)( newPos.x / MAP_TILE_SIZE )
         : (uint32_t)( ( newPos.x + entity->mapHitBoxSize.x ) / MAP_TILE_SIZE );

      for ( row = startRow; row <= endRow; row++ )
      {
         tile = &( game->map->tiles[( row * game->map->tileCount.x ) + col] );

         if ( !tile->passable )
         {
            newPos.x = ( newPos.x < entity->mapPos.x )
               ? ( ( col + 1 ) * MAP_TILE_SIZE ) + COLLISION_PADDING
               : ( col * MAP_TILE_SIZE ) - entity->mapHitBoxSize.x - COLLISION_PADDING;
            break;
         }
      }
   }

   newPos.y += entity->velocity.y * game->clock->frameDelta;

   if ( newPos.y <= 0 )
   {
      newPos.y = COLLISION_PADDING;
   }
   else if ( newPos.y + entity->mapHitBoxSize.y >= mapSize.y )
   {
      newPos.y = mapSize.y - entity->mapHitBoxSize.y - COLLISION_PADDING;
   }
   else if ( newPos.y != entity->mapPos.y && !game->cheatNoClip )
   {
      startCol = (uint32_t)( newPos.x / MAP_TILE_SIZE );
      endCol = (uint32_t)( ( newPos.x + entity->mapHitBoxSize.x ) / MAP_TILE_SIZE );
      row = ( newPos.y < entity->mapPos.y )
         ? (uint32_t)( newPos.y / MAP_TILE_SIZE )
         : (uint32_t)( ( newPos.y + entity->mapHitBoxSize.y ) / MAP_TILE_SIZE );

      for ( col = startCol; col <= endCol; col++ )
      {
         tile = &( game->map->tiles[( row * game->map->tileCount.x ) + col] );

         if ( !tile->passable )
         {
            newPos.y = ( newPos.y < entity->mapPos.y )
               ? ( ( row + 1 ) * MAP_TILE_SIZE ) + COLLISION_PADDING
               : ( row * MAP_TILE_SIZE ) - entity->mapHitBoxSize.y - COLLISION_PADDING;
            break;
         }
      }
   }

   entity->mapPos = newPos;
   gmEntity_Tic( entity, game->clock );
   entity->velocity.x = 0;
   entity->velocity.y = 0;

   entityCenterPos.x = entity->mapPos.x + ( entity->mapHitBoxSize.x / 2 );
   entityCenterPos.y = entity->mapPos.y + ( entity->mapHitBoxSize.y / 2 );
   newTileIndex = gmMap_TileIndexFromPos( game->map, entityCenterPos );

   if ( newTileIndex != game->physics->entityMapTileCache )
   {
      game->physics->entityMapTileCache = newTileIndex;
      gmGame_RollEncounter( game, newTileIndex );
   }
}
