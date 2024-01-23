#if !defined( INPUT_HANDLER_H )
#define INPUT_HANDLER_H

#include "common.h"

typedef struct gmGame_t gmGame_t;

typedef struct gmInputHandler_t
{
   char cheatString[STRLEN_SHORT];
}
gmInputHandler_t;

gmInputHandler_t* gmInputHandler_Create();
void gmInputHandler_Destroy( gmInputHandler_t* inputHandler );
void gmInputHandler_HandleInput( gmGame_t* game );

#endif // INPUT_HANDLER_H
