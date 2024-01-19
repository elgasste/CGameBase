#include "character.h"
#include "entity.h"

gmCharacter_t* gmCharacter_Create( gmEntity_t* entity )
{
   gmCharacter_t* character = (gmCharacter_t*)gmAlloc( sizeof( gmCharacter_t ), sfTrue );

   character->entity = entity;

   return character;
}

void gmCharacter_Destroy( gmCharacter_t* character )
{
   gmEntity_Destroy( character->entity );

   gmFree( character, sizeof( gmCharacter_t ), sfTrue );
}
