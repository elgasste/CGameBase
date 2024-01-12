#include "window.h"
#include "input_state.h"

gmWindow_t* gmWindow_Create()
{
   sfVideoMode videoMode = { WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP };
   gmWindow_t* window = (gmWindow_t*)gmAlloc( sizeof( gmWindow_t ), sfTrue );

   window->innerWindow = gmRenderWindow_Create( videoMode, STR_WINDOW_TITLE, WINDOW_STYLE, 0 );

   sfRenderWindow_setKeyRepeatEnabled( window->innerWindow, sfFalse );
   window->wantToClose = sfFalse;

   return window;
}

void gmWindow_Destroy( gmWindow_t* window )
{
   gmRenderWindow_Destroy( window->innerWindow );

   gmFree( window, sizeof( gmWindow_t ), sfTrue );
}

void gmWindow_Display( gmWindow_t* window )
{
   sfRenderWindow_display( window->innerWindow );
}

void gmWindow_Close( gmWindow_t* window )
{
   sfRenderWindow_close( window->innerWindow );
}

void gmWindow_HandleEvents( gmWindow_t* window, gmInputState_t* inputState )
{
   sfEvent e;

   while ( sfRenderWindow_pollEvent( window->innerWindow, &e ) )
   {
      switch ( e.type )
      {
         case sfEvtClosed:
            window->wantToClose = sfTrue;
            break;
         case sfEvtKeyPressed:
            gmInputState_SetKeyPressed( inputState, e.key.code );
            break;
         case sfEvtKeyReleased:
            gmInputState_SetKeyReleased( inputState, e.key.code );
            break;
      }
   }
}

void gmWindow_DrawRectangleShape( gmWindow_t* window, sfRectangleShape* rect )
{
   sfRenderWindow_drawRectangleShape( window->innerWindow, rect, 0 );
}

void gmWindow_DrawText( gmWindow_t* window, sfText* text )
{
   sfRenderWindow_drawText( window->innerWindow, text, 0 );
}

sfBool gmWindow_IsOpen( gmWindow_t* window )
{
   return sfRenderWindow_isOpen( window->innerWindow );
}
