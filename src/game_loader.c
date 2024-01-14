#include "game.h"
#include "map.h"
#include "entity.h"
#include "entity_sprite.h"

void gmGame_Load( gmGame_t* game )
{
   sfVector2f spriteMapPos = { 256, 256 };
   sfVector2f spriteMapHitBoxSize = { 52, 32 };
   sfVector2f spriteOffset = { -6, -32 };
   sfVector2u mapTileCount = { 16, 12 };
   uint32_t i;

   game->map = gmMap_Create( mapTileCount );

   for ( i = 0; i < mapTileCount.x * mapTileCount.y; i++ )
   {
      game->map->tiles[i].color = sfGreen;
      game->map->tiles[i].passable = sfTrue;
   }

   // top and bottom columns
   for ( i = 0; i < mapTileCount.x; i++ )
   {
      game->map->tiles[i].color = sfRed;
      game->map->tiles[i].passable = sfFalse;
      game->map->tiles[i + ( mapTileCount.x * ( mapTileCount.y - 1 ) )].color = sfRed;
      game->map->tiles[i + ( mapTileCount.x * ( mapTileCount.y - 1 ) )].passable = sfFalse;
   }

   // left and right columns
   for ( i = 1; i < mapTileCount.y - 1; i++ )
   {
      game->map->tiles[i * mapTileCount.x].color = sfRed;
      game->map->tiles[i * mapTileCount.x].passable = sfFalse;
      game->map->tiles[( i * mapTileCount.x ) + mapTileCount.x - 1].color = sfRed;
      game->map->tiles[( i * mapTileCount.x ) + mapTileCount.x - 1].passable = sfFalse;
   }

   // some random unpassable tiles
   game->map->tiles[( mapTileCount.x * 7 ) + 9].color = sfRed;
   game->map->tiles[( mapTileCount.x * 7 ) + 9].passable = sfFalse;
   game->map->tiles[( mapTileCount.x * 6 ) + 9].color = sfRed;
   game->map->tiles[( mapTileCount.x * 6 ) + 9].passable = sfFalse;
   game->map->tiles[( mapTileCount.x * 5 ) + 10].color = sfRed;
   game->map->tiles[( mapTileCount.x * 5 ) + 10].passable = sfFalse;
   game->map->tiles[( mapTileCount.x * 4 ) + 11].color = sfRed;
   game->map->tiles[( mapTileCount.x * 4 ) + 11].passable = sfFalse;
   game->map->tiles[( mapTileCount.x * 4 ) + 12].color = sfRed;
   game->map->tiles[( mapTileCount.x * 4 ) + 12].passable = sfFalse;
   game->map->tiles[( mapTileCount.x * 4 ) + 13].color = sfRed;
   game->map->tiles[( mapTileCount.x * 4 ) + 13].passable = sfFalse;

   // MUFFINS: make left and right sides unpassable

   game->entitySpriteTexture = gmTexture_CreateFromFile( "entity.png" );
   game->entity = gmEntity_Create( spriteMapPos, spriteMapHitBoxSize, 200.0f, spriteOffset, game->entitySpriteTexture );
   gmEntity_SetDirection( game->entity, gmDirection_Down );
}
