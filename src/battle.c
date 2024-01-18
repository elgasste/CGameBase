#include <string.h>

#include "battle.h"
#include "game.h"
#include "renderer.h"
#include "render_states.h"

gmBattle_t* gmBattle_Create( gmGame_t* game )
{
   gmBattle_t* battle = (gmBattle_t*)gmAlloc( sizeof( gmBattle_t ), sfTrue );

   snprintf( battle->message, DEFAULT_STRLEN, "You've encountered an enemy, probably!" );
   battle->state = gmBattleState_Intro;
   gmRenderStates_StartTextScroll( game->renderer->renderStates->textScroll, (uint32_t)strlen( battle->message ) );

   return battle;
}

void gmBattle_Destroy( gmBattle_t* battle )
{
   gmFree( battle, sizeof( gmBattle_t ), sfTrue );
}

void gmBattle_Begin( gmGame_t* game )
{
   snprintf( game->battle->message, DEFAULT_STRLEN, "Figure out what to do, and figure it out fast, you idiot! SELECT SOMETHING NOW, AND DO IT FAST!!" );
   game->battle->state = gmBattleState_SelectAction;
   gmRenderStates_StartTextScroll( game->renderer->renderStates->textScroll, (uint32_t)strlen( game->battle->message ) );
}

void gmBattle_ActionSelected( gmGame_t* game )
{
   snprintf( game->battle->message, DEFAULT_STRLEN, "Whatever you did, it must have worked." );
   game->battle->state = gmBattleState_Result;
   gmRenderStates_StartTextScroll( game->renderer->renderStates->textScroll, (uint32_t)strlen( game->battle->message ) );
}

void gmBattle_Close( gmGame_t* game )
{
   gmGame_EndEncounter( game );
}
