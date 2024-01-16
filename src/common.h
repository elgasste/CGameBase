#if !defined( COMMON_H )
#define COMMON_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>

#include "strings.h"

#define DEFAULT_STRLEN              512
#define SHORT_STRLEN                32

#define LOG_FILENAME                "log.txt"

#define WINDOW_WIDTH                1024
#define WINDOW_HEIGHT               768
#define WINDOW_BPP                  32
#define WINDOW_STYLE                sfTitlebar | sfClose

#define GAME_FPS                    60

#define GRAPHICS_SCALE              2

#define MAP_TILE_SIZE               64
#define MAP_TILE_PIXELS             32

#define DEBUG_FONT                  "consolas.ttf"
#define GAME_FONT                   "abaddon_bold.ttf"
#define GAME_FONT_SIZE              16
#define GAME_FONT_COLOR             sfColor_fromRGB( 224, 224, 224 )
#define DIALOG_BACKDROP_LIGHTCOLOR  sfColor_fromRGBA( 0, 0, 0, 192 )
#define DIALOG_BACKDROP_DARKCOLOR   sfColor_fromRGBA( 255, 255, 255, 24 )

#define MENU_CARAT_BLINKSECONDS     0.25f
#define MENU_LINESIZE               32.0f

#define CHEAT_NOCLIP                "dqclip"
#define CHEAT_NOENCOUNTER           "dqinvis"
#define CHEAT_CLEAR                 "dqclear"

#define TOGGLE_BOOL( x ) x = x ? sfFalse : sfTrue;

// globals
uint64_t g_memAllocated;
uint64_t g_memFreed;
uint64_t g_memCounter;
uint64_t g_maxMemCounter;
uint32_t g_sfmlObjectsCreated;
uint32_t g_sfmlObjectsDestroyed;
uint32_t g_sfmlObjectCounter;
uint32_t g_maxSfmlObjectCounter;

// logging and error handling
void gmLog_Clear();
void gmLog_Msg( const char* msg );
void gmLog_Newline();
void gmExitWithError( const char* msg );

// memory utilities
void* gmAlloc( size_t size, sfBool track );
void* gmCalloc( size_t count, size_t size, sfBool track );
void gmFree( void* obj, size_t size, sfBool track );

sfRenderWindow* gmRenderWindow_Create( sfVideoMode mode, const char* title, sfUint32 style, const sfContextSettings* settings );
sfClock* gmInnerClock_Create();
sfRectangleShape* gmRectangleShape_Create();
sfCircleShape* gmCircleShape_Create();
sfConvexShape* gmConvexShape_Create();
sfFont* gmFont_CreateFromFile( const char* filePath );
sfText* gmText_Create();
sfTexture* gmTexture_CreateFromFile( const char* filePath );
sfSprite* gmSprite_Create();

void gmRenderWindow_Destroy( sfRenderWindow* window );
void gmInnerClock_Destroy( sfClock* clock );
void gmRectangleShape_Destroy( sfRectangleShape* rect );
void gmCircleShape_Destroy( sfCircleShape* circle );
void gmConvexShape_Destroy( sfConvexShape* shape );
void gmFont_Destroy( sfFont* font );
void gmText_Destroy( sfText* text );
void gmTexture_Destroy( sfTexture* texture );
void gmSprite_Destroy( sfSprite* sprite );

#endif // COMMON_H
