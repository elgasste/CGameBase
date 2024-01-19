#if !defined( RANDOM_H )
#define RANDOM_H

#include "common.h"

void gmRandom_Seed();
uint32_t gmRandom_UInt32( uint32_t min, uint32_t max );
uint8_t gmRandom_Percent();

#endif
