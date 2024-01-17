#include "battle.h"
#include "game.h"

gmBattle_t* gmBattle_Create()
{
   gmBattle_t* battle = (gmBattle_t*)gmAlloc( sizeof( gmBattle_t ), sfTrue );

   sprintf_s( battle->message, DEFAULT_STRLEN, "You've encountered an enemy, probably!" );
   battle->state = gmBattleState_Intro;

   return battle;
}

void gmBattle_Destroy( gmBattle_t* battle )
{
   gmFree( battle, sizeof( gmBattle_t ), sfTrue );
}

void gmBattle_Begin( gmBattle_t* battle )
{
   sprintf_s( battle->message, DEFAULT_STRLEN, "Figure out what to do, and figure it out fast, you idiot! SELECT SOMETHING NOW, AND DO IT FAST!!" );
   battle->state = gmBattleState_SelectAction;
}

void gmBattle_ActionSelected( gmBattle_t* battle )
{
   sprintf_s( battle->message, DEFAULT_STRLEN, "Whatever you did, it must have worked." );
   battle->state = gmBattleState_Result;
}

void gmBattle_Close( gmGame_t* game )
{
   gmGame_CloseEncounter( game );
}
