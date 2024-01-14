#include "game.h"
#include "map.h"
#include "entity.h"
#include "entity_sprite.h"

void gmGame_Load( gmGame_t* game )
{
   sfVector2f spriteMapPos = { 256, 256 };
   sfVector2f spriteMapHitBoxSize = { 52, 32 };
   sfVector2f spriteOffset = { -6, -32 };
   sfVector2u mapTileCount = { 16, 12 };

   game->map = gmMap_Create( mapTileCount );

   game->entitySpriteTexture = gmTexture_CreateFromFile( "entity.png" );
   game->entity = gmEntity_Create( spriteMapPos, spriteMapHitBoxSize, 200.0f, spriteOffset, game->entitySpriteTexture );
   gmEntity_SetDirection( game->entity, gmDirection_Down );
}
