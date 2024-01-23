#if !defined( WINDOW_H )
#define WINDOW_H

#include "common.h"

typedef struct gmInputState_t gmInputState_t;

typedef struct gmWindow_t
{
   sfRenderWindow* sfmlWindow;
   sfBool wantToClose;
}
gmWindow_t;

gmWindow_t* gmWindow_Create();
void gmWindow_Destroy( gmWindow_t* window );
void gmWindow_Display( gmWindow_t* window );
void gmWindow_Close( gmWindow_t* window );
void gmWindow_HandleEvents( gmWindow_t* window, gmInputState_t* inputState );
void gmWindow_DrawRectangleShape( gmWindow_t* window, sfRectangleShape* rect );
void gmWindow_DrawText( gmWindow_t* window, sfText* text );
sfBool gmWindow_IsOpen( gmWindow_t* window );

#endif // WINDOW_H
