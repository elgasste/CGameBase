#include <string.h>

#include "battle.h"
#include "game.h"
#include "enemy.h"
#include "battle_stats.h"
#include "menus.h"
#include "renderer.h"
#include "render_states.h"
#include "text_util.h"

gmBattle_t* gmBattle_Create( gmGame_t* game )
{
   gmBattle_t* battle = (gmBattle_t*)gmAlloc( sizeof( gmBattle_t ), sfTrue );

   // TODO: we'll need an enemy generator at some point that reads from a repository
   gmBattleStats_t* enemyStats = (gmBattleStats_t*)gmAlloc( sizeof( gmBattleStats_t ), sfTrue );
   enemyStats->hitPoints = 15;
   enemyStats->magicPoints = 0;
   enemyStats->attackPower = 5;
   enemyStats->defensePower = 5;
   battle->enemy = gmEnemy_Create( "Bad Guyyyy", gmIndefiniteArticle_A, enemyStats );
   snprintf( battle->message,
             STRLEN_DEFAULT,
             STR_BATTLE_INTROFORMATTER,
             gmTextUtil_IndefiniteArticleFromEnum( battle->enemy->indefiniteArticle, sfTrue ),
             battle->enemy->name );
   battle->state = gmBattleState_Intro;
   gmRenderStates_StartTextScroll( game->renderer->renderStates->textScroll, (uint32_t)strlen( battle->message ) );

   return battle;
}

void gmBattle_Destroy( gmBattle_t* battle )
{
   gmEnemy_Destroy( battle->enemy );

   gmFree( battle, sizeof( gmBattle_t ), sfTrue );
}

void gmBattle_Begin( gmGame_t* game )
{
   snprintf( game->battle->message, STRLEN_DEFAULT, STR_BATTLE_SELECTACTION );
   game->battle->state = gmBattleState_SelectAction;
   gmRenderStates_ResetMenu( game->renderer->renderStates->menu );
   game->menus->battleAction->selectedIndex = 0;
}

void gmBattle_ActionSelected( gmGame_t* game, gmMenuCommand_t command )
{
   switch ( command )
   {
      case gmMenuCommand_Attack:
         snprintf( game->battle->message, STRLEN_DEFAULT, "Your brutal attack has left the enemy in tiny pieces, well done." );
         break;
      case gmMenuCommand_Guard:
         snprintf( game->battle->message, STRLEN_DEFAULT, "You hid behind your shield so well that the enemy forgot you were even there, and ran off." );
         break;
      case gmMenuCommand_Flee:
         snprintf( game->battle->message, STRLEN_DEFAULT, "You got away, nice work. Now the bad guy can go kill someone else." );
         break;
      default:
         gmExitWithError( STR_ERROR_INVALIDBATTLECOMMAND );
   }

   game->battle->state = gmBattleState_Result;
   gmRenderStates_StartTextScroll( game->renderer->renderStates->textScroll, (uint32_t)strlen( game->battle->message ) );
}

void gmBattle_Close( gmGame_t* game )
{
   gmGame_EndEncounter( game );
}
