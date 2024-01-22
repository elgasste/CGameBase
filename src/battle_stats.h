#if !defined( BATTLE_STATS_H )
#define BATTLE_STATS_H

#include "common.h"

typedef struct gmBattleStats_t
{
   uint32_t hitPoints;
   uint32_t magicPoints;
   uint32_t attackPower;
   uint32_t defensePower;
}
gmBattleStats_t;

#endif // BATTLE_STATS_H
