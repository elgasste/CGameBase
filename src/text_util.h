#if !defined( TEXT_UTIL_H )
#define TEXT_UTIL_H

#include "common.h"

typedef struct gmWindow_t gmWindow_t;

void gmTextUtil_DrawWrappedText( gmWindow_t* window,
                                 sfText* text,
                                 const char* str,
                                 sfVector2f pos,
                                 float width,
                                 float lineSpacing );

#endif // TEXT_UTIL_H
