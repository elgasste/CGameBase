#if !defined( CLOCK_H )
#define CLOCK_H

#include "common.h"

typedef struct gmClock_t
{
   sfClock* sfmlClock;

   float frameDeltaSeconds;
   sfInt64 maxFrameDurationMicro;
   sfTime frameStartTime;
   uint32_t totalFrameCount;
   uint32_t lagFrameCount;

   sfInt64 absoluteStartMicro;
   sfInt64 realTotalDurationMicro;
}
gmClock_t;

gmClock_t* gmClock_Create();
void gmClock_Destroy( gmClock_t* clock );
void gmClock_StartFrame( gmClock_t* clock );
void gmClock_EndFrame( gmClock_t* clock );

#endif // CLOCK_H
