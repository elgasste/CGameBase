#if !defined( INPUT_STATE_H )
#define INPUT_STATE_H

#include "common.h"

typedef struct gmInputState_t
{
   sfBool* keysPressed;
   sfBool* keysReleased;
   sfBool keyWasPressed;
   sfKeyCode lastPressedKey;
}
gmInputState_t;

gmInputState_t* gmInputState_Create();
void gmInputState_Destroy( gmInputState_t* inputState );
void gmInputState_SetKeyPressed( gmInputState_t* inputState, sfKeyCode keyCode );
void gmInputState_SetKeyReleased( gmInputState_t* inputState, sfKeyCode keyCode );
void gmInputState_Reset( gmInputState_t* inputState );

sfBool gmInputState_WasKeyPressed( gmInputState_t* inputState, sfKeyCode keyCode );
sfBool gmInputState_WasKeyReleased( gmInputState_t* inputState, sfKeyCode keyCode );
sfBool gmInputState_IsKeyDown( sfKeyCode keyCode );
sfBool gmInputState_IsAnyKeyDown();

#endif // INPUT_STATE_H
