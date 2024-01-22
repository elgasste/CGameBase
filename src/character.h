#if !defined( CHARACTER_H )
#define CHARACTER_H

#include "common.h"

typedef struct gmEntity_t gmEntity_t;
typedef struct gmBattleStats_t gmBattleStats_t;

typedef struct gmCharacter_t
{
   char name[NAME_STRLEN];
   gmEntity_t* entity;
   gmBattleStats_t* battleStats;
}
gmCharacter_t;

gmCharacter_t* gmCharacter_Create( const char* name, gmEntity_t* entity, gmBattleStats_t* battleStats );
void gmCharacter_Destroy( gmCharacter_t* character );

#endif // CHARACTER_H
