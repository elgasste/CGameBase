#if !defined( BATTLE_H )
#define BATTLE_H

#include "common.h"

typedef struct gmGame_t gmGame_t;

typedef enum gmBattleState_t
{
   gmBattleState_Intro,
   gmBattleState_SelectAction,
   gmBattleState_Result
}
gmBattleState_t;

typedef struct gmBattle_t
{
   gmBattleState_t state;
   char message[DEFAULT_STRLEN];
}
gmBattle_t;

gmBattle_t* gmBattle_Create();
void gmBattle_Destroy( gmBattle_t* battle );
void gmBattle_Begin( gmBattle_t* battle );
void gmBattle_ActionSelected( gmBattle_t* battle );
void gmBattle_Close( gmGame_t* game );

#endif // BATTLE_H
