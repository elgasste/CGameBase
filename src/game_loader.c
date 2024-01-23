#include <string.h>

#include "game.h"
#include "menus.h"
#include "map.h"
#include "entity.h"
#include "entity_sprite.h"
#include "physics.h"
#include "random.h"

void gmGame_LoadData( gmGame_t* game )
{
   sfVector2u mapTileCount = { 56, 56 };
   uint32_t i, tileIndex;
   gmMap_t* map;

   game->menus = gmMenus_Create();

   game->menus->overworld->optionCount = 2;
   game->menus->overworld->options = (gmMenuOption_t*)gmAlloc( sizeof( gmMenuOption_t ) * 2, sfTrue );
   game->menus->overworld->options[0].command = gmMenuCommand_CloseMenu;
   snprintf( game->menus->overworld->options[0].label, STRLEN_SHORT, STR_MENU_CLOSEMENU );
   game->menus->overworld->options[1].command = gmMenuCommand_Quit;
   snprintf( game->menus->overworld->options[1].label, STRLEN_SHORT, STR_MENU_QUITGAME );

   game->menus->battleAction->optionCount = 3;
   game->menus->battleAction->options = (gmMenuOption_t*)gmAlloc( sizeof( gmMenuOption_t ) * 3, sfTrue );
   game->menus->battleAction->options[0].command = gmMenuCommand_Attack;
   snprintf( game->menus->battleAction->options[0].label, STRLEN_SHORT, STR_MENU_ATTACK );
   game->menus->battleAction->options[1].command = gmMenuCommand_Guard;
   snprintf( game->menus->battleAction->options[1].label, STRLEN_SHORT, STR_MENU_GUARD );
   game->menus->battleAction->options[2].command = gmMenuCommand_Flee;
   snprintf( game->menus->battleAction->options[2].label, STRLEN_SHORT, STR_MENU_FLEE );

   game->map = gmMap_Create( mapTileCount );
   map = game->map;

   // default to grass
   for ( i = 0; i < mapTileCount.x * mapTileCount.y; i++ )
   {
      map->tiles[i].textureIndex = 0;
      map->tiles[i].passable = sfTrue;
      map->tiles[i].encounterRate = 0;
   }

   // randomly generate some trees
   for ( i = 0; i < 100; i++ )
   {
      tileIndex = gmRandom_UInt32( 0, mapTileCount.x * mapTileCount.y );
      map->tiles[tileIndex].textureIndex = 25;
      map->tiles[tileIndex].passable = sfFalse;
   }

   // grass tiles can have enemies
   for ( i = 0; i < mapTileCount.x * mapTileCount.y; i++ )
   {
      if ( map->tiles[i].textureIndex == 0 )
      {
         map->tiles[i].encounterRate = 5;
      }
   }
}
