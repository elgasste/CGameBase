#include <string.h>

#include "battle.h"
#include "game.h"
#include "character.h"
#include "enemy.h"
#include "battle_stats.h"
#include "menus.h"
#include "renderer.h"
#include "render_objects.h"
#include "render_states.h"
#include "text_util.h"
#include "battle_sprite.h"

static void gmBattle_AttackEnemy( gmGame_t* game );

gmBattle_t* gmBattle_Create( gmGame_t* game )
{
   gmBattle_t* battle = (gmBattle_t*)gmAlloc( sizeof( gmBattle_t ), sfTrue );

   // TODO: we'll need an enemy generator at some point that reads from a repository
   gmBattleStats_t* enemyStats = (gmBattleStats_t*)gmAlloc( sizeof( gmBattleStats_t ), sfTrue );
   enemyStats->hitPoints = 20;
   enemyStats->magicPoints = 0;
   enemyStats->attackPower = 5;
   enemyStats->defensePower = 5;
   battle->enemy = gmEnemy_Create( "Bad Guyyyy", gmIndefiniteArticle_A, enemyStats, game->renderer->renderObjects->enemySpriteTexture );
   snprintf( battle->message,
             STRLEN_DEFAULT,
             STR_BATTLE_INTROFORMATTER,
             gmTextUtil_IndefiniteArticleFromEnum( battle->enemy->indefiniteArticle, sfTrue ),
             battle->enemy->name );
   battle->state = gmBattleState_Intro;
   gmRenderStates_StartTextScroll( game->renderer->renderStates->textScroll, (uint32_t)strlen( battle->message ), 0 );

   return battle;
}

void gmBattle_Destroy( gmBattle_t* battle )
{
   gmEnemy_Destroy( battle->enemy );

   gmFree( battle, sizeof( gmBattle_t ), sfTrue );
}

void gmBattle_Begin( gmGame_t* game )
{
   game->battle->state = gmBattleState_SelectAction;
   snprintf( game->battle->message, STRLEN_DEFAULT, STR_BATTLE_SELECTACTION );
   gmRenderStates_ResetMenu( game->renderer->renderStates->menu );
   game->menus->battleAction->selectedIndex = 0;
}

void gmBattle_ActionSelected( gmGame_t* game, gmMenuCommand_t command )
{
   switch ( command )
   {
      case gmMenuCommand_Attack:
         game->battle->state = gmBattleState_StartingAttack;
         gmBattle_AttackEnemy( game );
         snprintf( game->battle->message, STRLEN_DEFAULT, "You swing your comically oversized sword!" );
         gmRenderStates_StartTextScroll( game->renderer->renderStates->textScroll, (uint32_t)strlen( game->battle->message ), 0 );
         break;
      case gmMenuCommand_Guard:
         game->battle->state = gmBattleState_Result;
         snprintf( game->battle->message, STRLEN_DEFAULT, "You hid behind your shield so well that the enemy forgot you were even there, and ran off." );
         gmRenderStates_StartTextScroll( game->renderer->renderStates->textScroll, (uint32_t)strlen( game->battle->message ), 0 );
         break;
      case gmMenuCommand_Flee:
         game->battle->state = gmBattleState_Result;
         snprintf( game->battle->message, STRLEN_DEFAULT, "You got away, nice work. Now the bad guy can go kill someone else." );
         gmRenderStates_StartTextScroll( game->renderer->renderStates->textScroll, (uint32_t)strlen( game->battle->message ), 0 );
         break;
      default:
         gmExitWithError( STR_ERROR_INVALIDBATTLECOMMAND );
   }
}

void gmBattle_NextState( gmGame_t* game )
{
   sfBool enemyDeath = game->battle->enemy->battleStats->hitPoints == 0;

   switch ( game->battle->state )
   {
      case gmBattleState_StartingAttack:

         game->battle->state = enemyDeath ? gmBattleState_EnemyDeath : gmBattleState_EnemyDamage;
         gmRenderStates_StartEnemyDamage( game, enemyDeath );
         break;
      case gmBattleState_EnemyDamage:
         game->battle->state = gmBattleState_AttackResult;
         snprintf( game->battle->message, STRLEN_DEFAULT, "Miraculously, you didn't miss!" );
         gmRenderStates_StartTextScroll( game->renderer->renderStates->textScroll, (uint32_t)strlen( game->battle->message ), 0.8f );
         break;
      case gmBattleState_EnemyDeath:
         game->battle->state = gmBattleState_Result;
         snprintf( game->battle->message, STRLEN_DEFAULT, "The enemy has been reduced to a pile of gibs. It's really gross." );
         gmRenderStates_StartTextScroll( game->renderer->renderStates->textScroll, (uint32_t)strlen( game->battle->message ), 0 );
         break;
      case gmBattleState_AttackResult:
         game->battle->state = gmBattleState_SelectAction;
         snprintf( game->battle->message, STRLEN_DEFAULT, STR_BATTLE_SELECTACTION );
         break;
   }
}

void gmBattle_Tic( gmGame_t* game )
{
   gmBattleSprite_Tic( game->battle->enemy->battleSprite, game->clock );
}

void gmBattle_Close( gmGame_t* game )
{
   gmGame_EndEncounter( game );
}

static void gmBattle_AttackEnemy( gmGame_t* game )
{
   gmCharacter_t* player = game->player;
   gmEnemy_t* enemy = game->battle->enemy;

   if ( enemy->battleStats->hitPoints <= player->battleStats->attackPower )
   {
      enemy->battleStats->hitPoints = 0;
   }
   else
   {
      enemy->battleStats->hitPoints -= player->battleStats->attackPower;
   }
}
