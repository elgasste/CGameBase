#include "clock.h"

gmClock_t* gmClock_Create()
{
   gmClock_t* clock = (gmClock_t*)gmAlloc( sizeof( gmClock_t ), sfTrue );

   clock->innerClock = gmInnerClock_Create();
   clock->frameDelta = 1.0f / GAME_FPS;
   clock->maxFrameDurationMicro = (sfInt64)( (double)clock->frameDelta * 1000000 );
   clock->totalFrameCount = 0;
   clock->lagFrameCount = 0;

   clock->absoluteStartMicro = sfClock_getElapsedTime( clock->innerClock ).microseconds;
   clock->realTotalDurationMicro = 0;

   return clock;
}

void gmClock_Destroy( gmClock_t* clock )
{
   gmInnerClock_Destroy( clock->innerClock );

   gmFree( clock, sizeof( gmClock_t ), sfTrue );
}

void gmClock_StartFrame( gmClock_t* clock )
{
   clock->frameStartTime = sfClock_getElapsedTime( clock->innerClock );
}

void gmClock_EndFrame( gmClock_t* clock )
{
   sfTime frameEndTime = sfClock_getElapsedTime( clock->innerClock );
   sfTime sleepTime = { 0 };
   sfInt64 frameDurationMicro = frameEndTime.microseconds - clock->frameStartTime.microseconds;

   clock->totalFrameCount++;
   clock->realTotalDurationMicro = frameEndTime.microseconds - clock->absoluteStartMicro;

   if ( frameDurationMicro > clock->maxFrameDurationMicro )
   {
      clock->lagFrameCount++;
   }
   else
   {
      sleepTime.microseconds = clock->maxFrameDurationMicro - frameDurationMicro;
      sfSleep( sleepTime );
   }
}
