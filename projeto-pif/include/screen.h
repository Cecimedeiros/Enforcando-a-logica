
/**
 * screen.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdio.h>
#include <string.h>

// Terminal control sequences
#define ESC            "\033"
#define NORMALTEXT     "[0m"
#define BOLDTEXT       "[1m"
#define ITALICTEXT     "[3m"
#define BLINKTEXT      "[5m"
#define REVERSETEXT    "[7m"
#define HOMECURSOR     "[f"
#define SHOWCURSOR     "[?25h"
#define HIDECURSOR     "[?25l"
#define CLEARSCREEN    "[2J"

// BOX Drawing - Unix like terminals
#define BOX_ENABLE     "(0"
#define BOX_DISABLE    "(B"
#define BOX_VLINE      0x78
#define BOX_HLINE      0x71
#define BOX_UPLEFT     0x6C
#define BOX_UPRIGHT    0x6B
#define BOX_DWNLEFT    0x6D
#define BOX_DWNRIGHT   0x6A
#define BOX_CROSS      0x6E
#define BOX_TLEFT      0X74
#define BOX_TRIGHT     0X75
#define BOX_TUP        0X77
#define BOX_TDOWN      0X76

#define BOX_DIAMOND    0x60
#define BOX_BLOCK      0x61
#define BOX_DOT        0x7E

// screen constants
#define SCRSTARTX      3      // Initial and final screen positions for the game
#define SCRENDX        95     // It means the area that can be drawn 
#define SCRSTARTY      1
#define SCRENDY        43

#define MINX           1      // min screen horizontal pos
#define MINY           1      // min screen vertical pos
#define MAXX           100     // max screen horizontal pos
#define MAXY           34    // max screen vertical pos


typedef enum {BLACK, RED, GREEN, BROWN, BLUE, MAGENTA, CYAN, LIGHTGRAY,
        DARKGRAY, LIGHTRED, LIGHTGREEN, YELLOW, LIGHTBLUE, 
        LIGHTMAGENTA, LIGHTCYAN, WHITE} screenColor; 

static inline void screenHomeCursor()
{
    printf("%s%s", ESC, HOMECURSOR);
}

static inline void screenClear()
{
    screenHomeCursor();
    printf("%s%s", ESC, CLEARSCREEN);
}

void screenSetColor(screenColor fg, screenColor bg);


#endif /* __SCREEN_H__ */