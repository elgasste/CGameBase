#include <string.h>

#include "text_util.h"
#include "game.h"
#include "renderer.h"
#include "render_states.h"
#include "window.h"

void gmTextUtil_DrawWrappedScrollingText( gmGame_t* game,
                                          sfText* text,
                                          const char* str,
                                          sfVector2f pos,
                                          float width,
                                          float lineSpacing )
{
   gmTextScrollRenderState_t* scrollState = game->renderer->renderStates->textScroll;
   size_t strLen = scrollState->isScrolling ? scrollState->currentCharIndex : strlen( str );
   char* strLine = (char*)gmAlloc( sizeof( char ) * ( strLen + 1 ), sfTrue );
   size_t i;
   int32_t j, lastSpaceIndex = -1;

   for ( i = 0, j = 0; i < strLen; i++, j++ )
   {
      strLine[j] = str[i];
      strLine[j + 1] = '\0';

      sfText_setString( text, strLine );

      if ( sfText_getGlobalBounds( text ).width > width )
      {
         if ( str[i] == ' ' )
         {
            sfText_setString( text, strLine );
            sfText_setPosition( text, pos );
            gmWindow_DrawText( game->window, text );
            j = -1;
            pos.y += lineSpacing;
         }
         else
         {
            if ( lastSpaceIndex < 0 )
            {
               strLine[j] = '\0';
               sfText_setString( text, strLine );
               sfText_setPosition( text, pos );
               gmWindow_DrawText( game->window, text );
               i--;
               j = -1;
               pos.y += lineSpacing;
               lastSpaceIndex = -1;
            }
            else
            {
               strLine[j - ( i - lastSpaceIndex)] = '\0';
               sfText_setString( text, strLine );
               sfText_setPosition( text, pos );
               gmWindow_DrawText( game->window, text );
               i = lastSpaceIndex;
               j = -1;
               pos.y += lineSpacing;
               lastSpaceIndex = -1;
            }
         }
      }
      else if ( i == strLen - 1 )
      {
         sfText_setString( text, strLine );
         sfText_setPosition( text, pos );
         gmWindow_DrawText( game->window, text );
      }
      else if ( str[i] == ' ' )
      {
         lastSpaceIndex = (int32_t)i;
      }
   }

   gmFree( strLine, sizeof( char ) * ( strLen + 1 ), sfTrue );
}
