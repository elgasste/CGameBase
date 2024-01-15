#if !defined( WINDOW_H )
#define WINDOW_H

#include "common.h"

typedef struct gmInputState_t gmInputState_t;
typedef struct gmEntitySprite_t gmEntitySprite_t;

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
void gmWindow_DrawCircleShape( gmWindow_t* window, sfCircleShape* circle );
void gmWindow_DrawConvexShape( gmWindow_t* window, sfConvexShape* shape );
void gmWindow_DrawText( gmWindow_t* window, sfText* text );
void gmWindow_DrawSprite( gmWindow_t* window, sfSprite* sprite );
void gmWindow_DrawEntitySprite( gmWindow_t* window, gmEntitySprite_t* sprite );
sfBool gmWindow_IsOpen( gmWindow_t* window );

#endif // WINDOW_H
