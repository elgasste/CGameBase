#include "game.h"
#include "input_state.h"

void gmInputHandler_HandleInput( gmGame_t* game )
{
   if ( gmInputState_WasKeyPressed( game->inputState, sfKeyEscape ) )
   {
      gmGame_Close( game );
   }
   else if ( gmInputState_WasKeyPressed( game->inputState, sfKeyF8 ) )
   {
      TOGGLE_BOOL( game->showDiagnostics );

      if ( game->showDiagnostics )
      {
         gmGame_ShowDebugMessage( game, STR_DEBUG_DIAGNOSTICSON );
      }
      else
      {
         gmGame_ShowDebugMessage( game, STR_DEBUG_DIAGNOSTICSOFF );
      }
   }
}
