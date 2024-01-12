#include "window.h"
#include "input_state.h"

gmWindow_t* gmWindow_Create()
{
   sfVideoMode videoMode = { WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP };
   gmWindow_t* window = (gmWindow_t*)gmAlloc( sizeof( gmWindow_t ), sfTrue );

   window->sfmlWindow = gmRenderWindow_Create( videoMode, STR_WINDOW_TITLE, WINDOW_STYLE, 0 );

   sfRenderWindow_setKeyRepeatEnabled( window->sfmlWindow, sfFalse );
   window->wantToClose = sfFalse;

   return window;
}

void gmWindow_Destroy( gmWindow_t* window )
{
   gmRenderWindow_Destroy( window->sfmlWindow );

   gmFree( window, sizeof( gmWindow_t ), sfTrue );
}

void gmWindow_Display( gmWindow_t* window )
{
   sfRenderWindow_display( window->sfmlWindow );
}

void gmWindow_Close( gmWindow_t* window )
{
   sfRenderWindow_close( window->sfmlWindow );
}

void gmWindow_HandleEvents( gmWindow_t* window, gmInputState_t* inputState )
{
   sfEvent e;

   while ( sfRenderWindow_pollEvent( window->sfmlWindow, &e ) )
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
   sfRenderWindow_drawRectangleShape( window->sfmlWindow, rect, 0 );
}

void gmWindow_DrawText( gmWindow_t* window, sfText* text )
{
   sfRenderWindow_drawText( window->sfmlWindow, text, 0 );
}

sfBool gmWindow_IsOpen( gmWindow_t* window )
{
   return sfRenderWindow_isOpen( window->sfmlWindow );
}
