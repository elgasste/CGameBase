#include <string.h>

#include "character.h"
#include "entity.h"
#include "battle_stats.h"

gmCharacter_t* gmCharacter_Create( const char* name, gmEntity_t* entity, gmBattleStats_t* battleStats )
{
   gmCharacter_t* character = (gmCharacter_t*)gmAlloc( sizeof( gmCharacter_t ), sfTrue );

   snprintf( character->name, NAME_STRLEN, "%s", name );
   character->entity = entity;
   character->battleStats = battleStats;

   return character;
}

void gmCharacter_Destroy( gmCharacter_t* character )
{
   gmEntity_Destroy( character->entity );

   gmFree( character->battleStats, sizeof( gmBattleStats_t ), sfTrue );
   gmFree( character, sizeof( gmCharacter_t ), sfTrue );
}
