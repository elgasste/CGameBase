#if !defined( ENUMS_H )
#define ENUMS_H

#include "common.h"

typedef enum
{
   gmIndefiniteArticle_A = 0,
   gmIndefiniteArticle_An
}
gmIndefiniteArticle_t;

typedef enum
{
   gmDirection_Left = 0,
   gmDirection_Up,
   gmDirection_Right,
   gmDirection_Down
}
gmDirection_t;

typedef enum
{
   gmGameState_Overworld,
   gmGameState_OverworldMenu,
   gmGameState_Battle
}
gmGameState_t;

typedef enum
{
   gmBattleState_Intro,
   gmBattleState_SelectAction,
   gmBattleState_Result
}
gmBattleState_t;

typedef enum gmMenuCommand_t
{
   gmMenuCommand_Quit = 0,
   gmMenuCommand_CloseMenu,

   gmMenuCommand_Attack,
   gmMenuCommand_Guard,
   gmMenuCommand_Flee
}
gmMenuCommand_t;

#endif
