#if !defined( MENUS_H )
#define MENUS_H

#include "common.h"
#include "menu_command.h"

typedef struct gmMenuRenderState_t gmMenuRenderState_t;

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
void gmMenu_ScrollUp( gmMenu_t* menu, gmMenuRenderState_t* renderState );
void gmMenu_ScrollDown( gmMenu_t* menu, gmMenuRenderState_t* renderState );

#endif // MENUS_H
