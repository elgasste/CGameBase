#if !defined( MENUS_H )
#define MENUS_H

#include "common.h"

typedef enum gmMenuCommand_t
{
   gmMenuCommand_Quit = 0,
   gmMenuCommand_CloseMenu
}
gmMenuCommand_t;

typedef struct gmMenuOption_t
{
   char label[SHORT_STRLEN];
   gmMenuCommand_t command;
}
gmMenuOption_t;

typedef struct gmMenu_t
{
   gmMenuOption_t* options;
   uint16_t optionCount;
   uint16_t selectedIndex;
}
gmMenu_t;

typedef struct gmMenus_t
{
   gmMenu_t* overworld;
}
gmMenus_t;

gmMenus_t* gmMenus_Create();
void gmMenus_Destroy( gmMenus_t* menus );

#endif // MENUS_H
