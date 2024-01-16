#include "battle.h"

gmBattle_t* gmBattle_Create()
{
   gmBattle_t* battle = (gmBattle_t*)gmAlloc( sizeof( gmBattle_t ), sfTrue );

   battle->state = gmBattleState_Intro;

   return battle;
}

void gmBattle_Destroy( gmBattle_t* battle )
{
   gmFree( battle, sizeof( gmBattle_t ), sfTrue );
}
