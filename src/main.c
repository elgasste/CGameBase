#include "game.h"

int main()
{
   char memStr[STRLEN_DEFAULT];

   g_memAllocated = 0;
   g_memFreed = 0;
   g_memCounter = 0;
   g_maxMemCounter = 0;
   g_sfmlObjectsCreated = 0;
   g_sfmlObjectsDestroyed = 0;
   g_sfmlObjectCounter = 0;
   g_maxSfmlObjectCounter = 0;

   gmLog_Clear();

   printf( STR_CONSOLE_LOADING );
   gmLog_Msg( STR_MAIN_LOADINGGAME );
   gmGame_t* game = gmGame_Create();
   printf( STR_CONSOLE_HAVEFUN );

   gmLog_Msg( STR_MAIN_RUNNINGGAME );
   gmGame_Run( game );

   printf( STR_CONSOLE_CLEANINGUP );
   gmLog_Msg( STR_MAIN_GAMECLOSED );
   gmGame_Destroy( game );
   printf( STR_CONSOLE_BURRITO );

   snprintf( memStr, STRLEN_DEFAULT, "%s: %llu", STR_MAIN_MEMALLOCATED, g_memAllocated );
   gmLog_Msg( memStr );
   snprintf( memStr, STRLEN_DEFAULT, "%s: %llu", STR_MAIN_MEMFREED, g_memFreed );
   gmLog_Msg( memStr );
   snprintf( memStr, STRLEN_DEFAULT, "%s: %llu", STR_MAIN_MEMMAX, g_maxMemCounter );
   gmLog_Msg( memStr );
   snprintf( memStr, STRLEN_DEFAULT, "%s: %u", STR_MAIN_SFMLOBJCREATED, g_sfmlObjectsCreated );
   gmLog_Msg( memStr );
   snprintf( memStr, STRLEN_DEFAULT, "%s: %u", STR_MAIN_SFMLOBJDESTROYED, g_sfmlObjectsDestroyed );
   gmLog_Msg( memStr );
   snprintf( memStr, STRLEN_DEFAULT, "%s: %u", STR_MAIN_SFMLOBJMAX, g_maxSfmlObjectCounter );
   gmLog_Msg( memStr );
   gmLog_Newline();

   return 0;
}
