#if !defined( CHARACTER_H )
#define CHARACTER_H

#include "common.h"

typedef struct gmEntity_t gmEntity_t;

typedef struct gmCharacter_t
{
   gmEntity_t* entity;
}
gmCharacter_t;

gmCharacter_t* gmCharacter_Create( gmEntity_t* entity );
void gmCharacter_Destroy( gmCharacter_t* character );

#endif // CHARACTER_H
