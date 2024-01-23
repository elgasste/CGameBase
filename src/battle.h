#if !defined( BATTLE_H )
#define BATTLE_H

#include "common.h"
#include "enums.h"

typedef struct gmEnemy_t gmEnemy_t;
typedef struct gmGame_t gmGame_t;

typedef struct gmBattle_t
{
   gmBattleState_t state;
   gmEnemy_t* enemy;
   char message[STRLEN_DEFAULT];
}
gmBattle_t;

gmBattle_t* gmBattle_Create( gmGame_t* game );
void gmBattle_Destroy( gmBattle_t* battle );
void gmBattle_Begin( gmGame_t* game );
void gmBattle_ActionSelected( gmGame_t* game, gmMenuCommand_t command );
void gmBattle_Tic( gmGame_t* game );
void gmBattle_Close( gmGame_t* game );

#endif // BATTLE_H
