#include "map.h"

gmMap_t* gmMap_Create( sfVector2u tileCount )
{
   gmMap_t* map = (gmMap_t*)gmAlloc( sizeof( gmMap_t ), sfTrue );

   map->tileCount = tileCount;
   map->tiles = (gmMapTile_t*)gmAlloc( sizeof( gmMapTile_t ) * tileCount.x * tileCount.y, sfTrue );

   return map;
}

void gmMap_Destroy( gmMap_t* map )
{
   gmFree( map->tiles, sizeof( gmMapTile_t ) * map->tileCount.x * map->tileCount.y, sfTrue );

   gmFree( map, sizeof( gmMap_t ), sfTrue );
}

uint32_t gmMap_TileIndexFromPos( gmMap_t* map, sfVector2f pos )
{
   return ( (uint32_t)( pos.y / MAP_TILE_SIZE ) * map->tileCount.x ) + (uint32_t)( pos.x / MAP_TILE_SIZE );
}
