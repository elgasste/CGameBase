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
   char strLine[STRLEN_DEFAULT];
   uint32_t strLen = (uint32_t)strlen( str );
   uint32_t substrEndIndex = scrollState->isScrolling ? scrollState->currentCharIndex : strLen;
   uint32_t lineStartIndex, curIndex, writeIndex, cutoffIndex, lastSpaceIndex;

   sfText_setPosition( text, pos );

   for ( lineStartIndex = 0, curIndex = 0, cutoffIndex = 0, lastSpaceIndex = 0; curIndex < strLen; curIndex++ )
   {
      writeIndex = curIndex - lineStartIndex;
      strLine[writeIndex] = str[curIndex];

      if ( str[curIndex] == ' ' || curIndex == strLen - 1 )
      {
         if ( str[curIndex] == ' ' )
         {
            strLine[writeIndex] = '\0';
         }
         else
         {
            strLine[writeIndex + 1] = '\0';
         }

         sfText_setString( text, strLine );

         if ( sfText_getGlobalBounds( text ).width > width )
         {
            if ( lastSpaceIndex <= lineStartIndex )
            {
               // the entire line is one word
               curIndex = cutoffIndex + 1;
            }
            else
            {
               // the line has multiple words
               curIndex = lastSpaceIndex;
            }

            if ( substrEndIndex < curIndex )
            {
               strLine[substrEndIndex - lineStartIndex + 1] = '\0';
               sfText_setString( text, strLine );
               gmWindow_DrawText( game->window, text );
               break;
            }
            // this check is only here to get around a compiler warning
            else if ( curIndex >= lineStartIndex )
            {
               strLine[curIndex - lineStartIndex] = '\0';
               sfText_setString( text, strLine );
               gmWindow_DrawText( game->window, text );
            }

            if ( str[curIndex] != ' ' && str[curIndex] != '\0' )
            {
               curIndex--;
            }

            lineStartIndex = curIndex + 1;
            pos.y += lineSpacing;
            sfText_setPosition( text, pos );
         }
         else
         {
            if ( curIndex > substrEndIndex )
            {
               strLine[substrEndIndex - lineStartIndex + 1] = '\0';
               sfText_setString( text, strLine );
               gmWindow_DrawText( game->window, text );
               break;
            }
            else if ( curIndex == strLen - 1 )
            {
               gmWindow_DrawText( game->window, text );
            }
            else
            {
               strLine[writeIndex] = ' ';
               lastSpaceIndex = writeIndex;
            }
         }
      }
      else if ( cutoffIndex <= lineStartIndex )
      {
         strLine[writeIndex + 1] = '\0';
         sfText_setString( text, strLine );

         if ( sfText_getGlobalBounds( text ).width > width )
         {
            cutoffIndex = curIndex - 1;
         }
      }
   }
}

const char* gmTextUtil_IndefiniteArticleFromEnum( gmIndefiniteArticle_t article, sfBool lower )
{
   switch ( article )
   {
      case gmIndefiniteArticle_A:
         return lower ? STR_INDEFINITE_LOWERA : STR_INDEFINITE_UPPERA;
      case gmIndefiniteArticle_An:
         return lower ? STR_INDEFINITE_LOWERAN : STR_INDEFINITE_UPPERAN;
      default:
         return "";
   }
}