#if !defined( RENDER_STATES_H )
#define RENDER_STATES_H

#include "common.h"

typedef struct gmGame_t gmGame_t;

typedef struct gmDebugBarRenderState_t
{
   sfBool isVisible;
   float elapsedSeconds;
   float visibleSeconds;
   char* msgBuffer;
   size_t msgBufferLen;
}
gmDebugBarRenderState_t;

typedef struct gmMenuRenderState_t
{
   sfBool showCarat;
   float caratBlinkSeconds;
   float caratElapsedSeconds;
}
gmMenuRenderState_t;

typedef struct gmScreenFadeRenderState_t
{
   sfBool isFading;
   sfBool isFadingOut;
   sfBool isPaused;
   sfBool isFadingIn;
   sfBool light;
   float fadeSeconds;
   float pauseSeconds;
   float elapsedSeconds;
}
gmScreenFadeRenderState_t;

typedef struct gmTextScrollRenderState_t
{
   sfBool isScrolling;
   uint32_t charCount;
   uint32_t currentCharIndex;
   float letterSeconds;
   float elapsedSeconds;
}
gmTextScrollRenderState_t;

typedef struct gmRenderStates_t
{
   gmDebugBarRenderState_t* debugBar;
   gmMenuRenderState_t* menu;
   gmScreenFadeRenderState_t* screenFade;
   gmTextScrollRenderState_t* textScroll;
}
gmRenderStates_t;

gmRenderStates_t* gmRenderStates_Create();
void gmRenderStates_Destroy( gmRenderStates_t* states );
void gmRenderStates_ResetMenu( gmMenuRenderState_t* state );
void gmRenderStates_ResetScreenFade( gmScreenFadeRenderState_t* state );
void gmRenderStates_StartScreenFade( gmScreenFadeRenderState_t* state, sfBool light );
void gmRenderStates_ResetTextScroll( gmTextScrollRenderState_t* state );
void gmRenderStates_StartTextScroll( gmTextScrollRenderState_t* state, uint32_t charCount );
void gmRenderStates_Tic( gmGame_t* game );

#endif // RENDER_STATES_H
