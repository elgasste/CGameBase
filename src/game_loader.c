#include "game.h"
#include "map.h"
#include "entity.h"
#include "entity_sprite.h"
#include "random.h"

void gmGame_LoadData( gmGame_t* game )
{
   sfVector2f spriteMapPos = { 256, 256 };
   sfVector2f spriteMapHitBoxSize = { 52, 32 };
   sfVector2f spriteOffset = { -6, -32 };
   sfVector2u mapTileCount = { 16, 12 };
   uint32_t i, tileIndex;
   gmMap_t* map;

   game->map = gmMap_Create( mapTileCount );
   map = game->map;

   // default to grass
   for ( i = 0; i < mapTileCount.x * mapTileCount.y; i++ )
   {
      map->tiles[i].textureIndex = 0;
      map->tiles[i].passable = sfTrue;
   }

   // randomly generate some trees
   for ( i = 0; i < 30; i++ )
   {
      tileIndex = gmRandom_UInt32( 0, mapTileCount.x * mapTileCount.y );
      map->tiles[tileIndex].textureIndex = 25;
      map->tiles[tileIndex].passable = sfFalse;
   }

   game->mapTilesetTexture = gmTexture_CreateFromFile( "map_tileset.png" );
   game->entitySpriteTexture = gmTexture_CreateFromFile( "entity.png" );

   game->entity = gmEntity_Create( spriteMapPos, spriteMapHitBoxSize, 200.0f, spriteOffset, game->entitySpriteTexture );
   gmEntity_SetDirection( game->entity, gmDirection_Down );
}
