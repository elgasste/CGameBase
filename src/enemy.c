#include "enemy.h"
#include "battle_stats.h"
#include "battle_sprite.h"

gmEnemy_t* gmEnemy_Create( const char* name,
                           gmIndefiniteArticle_t indefiniteArticle,
                           gmBattleStats_t* battleStats,
                           sfTexture* spriteTexture )
{
   gmEnemy_t* enemy = (gmEnemy_t*)gmAlloc( sizeof( gmEnemy_t ), sfTrue );

   snprintf( enemy->name, STRLEN_SHORT, "%s", name );
   enemy->indefiniteArticle = indefiniteArticle;
   enemy->battleStats = battleStats;
   enemy->battleSprite = gmBattleSprite_Create( spriteTexture, 0.1f, 8, 8, 7, 7, gmBattleSpriteState_Idle );

   return enemy;
}

void gmEnemy_Destroy( gmEnemy_t* enemy )
{
   gmBattleSprite_Destroy( enemy->battleSprite );

   gmFree( enemy->battleStats, sizeof( gmBattleStats_t ), sfTrue );
   gmFree( enemy, sizeof( gmEnemy_t ), sfTrue );
}
