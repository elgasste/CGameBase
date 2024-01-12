#include "input_state.h"

gmInputState_t* gmInputState_Create()
{
   gmInputState_t* inputState = (gmInputState_t*)gmAlloc( sizeof( gmInputState_t ), sfTrue );

   inputState->keysPressed = (sfBool*)gmCalloc( sfKeyCount, sizeof( sfBool ), sfTrue );
   inputState->keysReleased = (sfBool*)gmCalloc( sfKeyCount, sizeof( sfBool ), sfTrue );
   inputState->keyWasPressed = sfFalse;
   inputState->lastPressedKey = sfKeyCount;

   return inputState;
}

void gmInputState_Destroy( gmInputState_t* inputState )
{
   gmFree( inputState->keysPressed, sizeof( sfBool) * sfKeyCount, sfTrue );
   gmFree( inputState->keysReleased, sizeof( sfBool ) * sfKeyCount, sfTrue );
   gmFree( inputState, sizeof( gmInputState_t ), sfTrue );
}

void gmInputState_Reset( gmInputState_t* inputState )
{
   int i;

   for ( i = 0; i < (int)sfKeyCount; i++ )
   {
      inputState->keysPressed[i] = sfFalse;
      inputState->keysReleased[i] = sfFalse;
      inputState->keyWasPressed = sfFalse;
   }
}

void gmInputState_SetKeyPressed( gmInputState_t* inputState, sfKeyCode keyCode )
{
   if ( keyCode >= 0 && keyCode < sfKeyCount )
   {
      inputState->keysPressed[keyCode] = sfTrue;
      inputState->keyWasPressed = sfTrue;
      inputState->lastPressedKey = keyCode;
   }
}

void gmInputState_SetKeyReleased( gmInputState_t* inputState, sfKeyCode keyCode )
{
   if ( keyCode >= 0 && keyCode < sfKeyCount )
   {
      inputState->keysReleased[keyCode] = sfTrue;
   }
}

sfBool gmInputState_WasKeyPressed( gmInputState_t* inputState, sfKeyCode keyCode )
{
   return ( keyCode >= 0 && keyCode < sfKeyCount ) ? inputState->keysPressed[keyCode] : sfFalse;
}

sfBool gmInputState_WasKeyReleased( gmInputState_t* inputState, sfKeyCode keyCode )
{
   return ( keyCode >= 0 && keyCode < sfKeyCount) ? inputState->keysReleased[keyCode] : sfFalse;
}

sfBool gmInputState_IsKeyDown( sfKeyCode keyCode )
{
   return keyCode >= 0 ? sfKeyboard_isKeyPressed( keyCode ) : sfFalse;
}

sfBool gmInputState_IsAnyKeyDown()
{
   int i;

   for ( i = 0; i < (int)sfKeyCount; i++ )
   {
      if ( sfKeyboard_isKeyPressed( i ) )
      {
         return sfTrue;
      }
   }

   return sfFalse;
}
