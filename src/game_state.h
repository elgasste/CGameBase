#if !defined( GAME_STATE_H )
#define GAME_STATE_H

#include "common.h"

typedef enum gmGameState_t
{
   gmGameState_Overworld,
   gmGameState_OverworldMenu,
   gmGameState_Battle
}
gmGameState_t;

#endif // GAME_STATE_H
