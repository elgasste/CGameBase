#if !defined( ENEMY_H )
#define ENEMY_H

#include "common.h"
#include "enums.h"

typedef struct gmBattleStats_t gmBattleStats_t;
typedef struct gmBattleSprite_t gmBattleSprite_t;

typedef struct gmEnemy_t
{
   char name[STRLEN_SHORT];
   gmIndefiniteArticle_t indefiniteArticle;
   gmBattleStats_t* battleStats;
   gmBattleSprite_t* battleSprite;

}
gmEnemy_t;

gmEnemy_t* gmEnemy_Create( const char* name,
                           gmIndefiniteArticle_t indefiniteArticle,
                           gmBattleStats_t* battleStats,
                           sfTexture* spriteTexture );
void gmEnemy_Destroy( gmEnemy_t* enemy );

#endif // ENEMY_H
