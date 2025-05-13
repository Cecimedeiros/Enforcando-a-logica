#include <stdio.h>
#include <stdlib.h>
#include "../include/screen.h"

void screenSetColor(screenColor fg, screenColor bg) {
#ifdef _WIN32
    // Para Windows
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, fg + (bg * 16));  // Cores de 16 bits
#else
    // Para Unix/Linux
    const char* fgColors[] = {
        "30", "31", "32", "33", "34", "35", "36", "37",
        "90", "91", "92", "93", "94", "95", "96", "97"
    };
    const char* bgColors[] = {
        "40", "41", "42", "43", "44", "45", "46", "47",
        "100", "101", "102", "103", "104", "105", "106", "107"
    };
    
    printf("%s[%s;%sm", ESC, fgColors[fg], bgColors[bg]);
#endif
}

