#if !defined( MAP_H )
#define MAP_H

#include "common.h"

typedef struct gmMapTile_t
{
   sfBool passable;
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

#endif // MAP_H
