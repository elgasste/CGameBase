#include "menus.h"
#include "render_states.h"

gmMenus_t* gmMenus_Create()
{
   gmMenus_t* menus = (gmMenus_t*)gmAlloc( sizeof( gmMenus_t ), sfTrue );

   menus->overworld = (gmMenu_t*)gmAlloc( sizeof( gmMenu_t ), sfTrue );
   menus->overworld->optionCount = 0;
   menus->overworld->selectedIndex = 0;

   menus->battleAction = (gmMenu_t*)gmAlloc( sizeof( gmMenu_t ), sfTrue );
   menus->battleAction->optionCount = 0;
   menus->battleAction->selectedIndex = 0;

   return menus;
}

void gmMenus_Destroy( gmMenus_t* menus )
{
   if ( menus->battleAction->optionCount > 0 )
   {
      gmFree( menus->battleAction->options, sizeof( gmMenuOption_t ) * menus->battleAction->optionCount, sfTrue );
   }

   if ( menus->overworld->optionCount > 0 )
   {
      gmFree( menus->overworld->options, sizeof( gmMenuOption_t ) * menus->overworld->optionCount, sfTrue );
   }

   gmFree( menus->battleAction, sizeof( gmMenu_t ), sfTrue );
   gmFree( menus->overworld, sizeof( gmMenu_t ), sfTrue );
   gmFree( menus, sizeof( gmMenus_t ), sfTrue );
}

void gmMenu_ScrollUp( gmMenu_t* menu, gmMenuRenderState_t* renderState )
{
   if ( menu->selectedIndex > 0 )
   {
      menu->selectedIndex--;
   }

   gmRenderStates_ResetMenu( renderState );
}

void gmMenu_ScrollDown( gmMenu_t* menu, gmMenuRenderState_t* renderState )
{
   if ( menu->selectedIndex < menu->optionCount - 1 )
   {
      menu->selectedIndex++;
   }

   gmRenderStates_ResetMenu( renderState );
}
