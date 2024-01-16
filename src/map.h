#if !defined( MAP_H )
#define MAP_H

#include "common.h"

typedef struct gmMapTile_t
{
   uint32_t textureIndex;
   sfBool passable;
   uint8_t encounterRate;
}
gmMapTile_t;

typedef struct gmMap_t
{
   gmMapTile_t* tiles;
   sfVector2u tileCount;
}
gmMap_t;

gmMap_t* gmMap_Create( sfVector2u tileCount );
void gmMap_Destroy( gmMap_t* map );
uint32_t gmMap_TileIndexFromPos( gmMap_t* map, sfVector2f pos );

#endif // MAP_H
