#include "enemy.h"
#include "battle_stats.h"

gmEnemy_t* gmEnemy_Create( const char* name,
                           gmIndefiniteArticle_t indefiniteArticle,
                           gmBattleStats_t* battleStats )
{
   gmEnemy_t* enemy = (gmEnemy_t*)gmAlloc( sizeof( gmEnemy_t ), sfTrue );

   snprintf( enemy->name, STRLEN_SHORT, "%s", name );
   enemy->indefiniteArticle = indefiniteArticle;
   enemy->battleStats = battleStats;

   return enemy;
}

void gmEnemy_Destroy( gmEnemy_t* enemy )
{
   gmFree( enemy->battleStats, sizeof( gmBattleStats_t ), sfTrue );
   gmFree( enemy, sizeof( gmEnemy_t ), sfTrue );
}
