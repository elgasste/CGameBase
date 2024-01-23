#if !defined( TEXT_UTIL_H )
#define TEXT_UTIL_H

#include "common.h"
#include "enums.h"

typedef struct gmGame_t gmGame_t;

void gmTextUtil_DrawWrappedScrollingText( gmGame_t* game,
                                          sfText* text,
                                          const char* str,
                                          sfVector2f pos,
                                          float width,
                                          float lineSpacing );
const char* gmTextUtil_IndefiniteArticleFromEnum( gmIndefiniteArticle_t article, sfBool lower );

#endif // TEXT_UTIL_H
