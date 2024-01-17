#if !defined( PHYSICS_H )
#define PHYSICS_H

#include "common.h"

typedef struct gmGame_t gmGame_t;

typedef struct gmPhysics_t
{
   uint32_t entityMapTileCache;
}
gmPhysics_t;

gmPhysics_t* gmPhysics_Create();
void gmPhysics_Destroy( gmPhysics_t* physics );
void gmPhysics_Tic( gmGame_t* game );

#endif // PHYSICS_H
