#include "battle.h"

gmBattle_t* gmBattle_Create()
{
   gmBattle_t* battle = (gmBattle_t*)gmAlloc( sizeof( gmBattle_t ), sfTrue );

   battle->state = gmBattleState_Intro;

   sprintf_s( battle->message, DEFAULT_STRLEN, "You've encountered an enemy, probably!" );

   return battle;
}

void gmBattle_Destroy( gmBattle_t* battle )
{
   gmFree( battle, sizeof( gmBattle_t ), sfTrue );
}
