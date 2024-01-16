#include "random.h"

uint32_t gmRandom_UInt32( uint32_t min, uint32_t max )
{
   // min and max inclusive
   return ( (uint32_t)rand() % ( ( max + 1 ) - min ) ) + min;
}

uint8_t gmRandom_Percent()
{
   return (uint8_t)rand() % 101;
}
