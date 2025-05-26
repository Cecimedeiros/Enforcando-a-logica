#include <ctype.h>
#include "../include/Normalizador.h"

char remover_acento(char c) {
    switch ((unsigned char)c) {
        case 0xE1: case 0xE0: case 0xE2: case 0xE3: case 0xE4:
        case 0xC1: case 0xC0: case 0xC2: case 0xC3: case 0xC4:
            return 'a';
        case 0xE9: case 0xE8: case 0xEA: case 0xEB:
        case 0xC9: case 0xC8: case 0xCA: case 0xCB:
            return 'e';
        case 0xED: case 0xEC: case 0xEE: case 0xEF:
        case 0xCD: case 0xCC: case 0xCE: case 0xCF:
            return 'i';
        case 0xF3: case 0xF2: case 0xF4: case 0xF5: case 0xF6:
        case 0xD3: case 0xD2: case 0xD4: case 0xD5: case 0xD6:
            return 'o';
        case 0xFA: case 0xF9: case 0xFB: case 0xFC:
        case 0xDA: case 0xD9: case 0xDB: case 0xDC:
            return 'u';
        case 0xE7: case 0xC7:
            return 'c';
        default:
            return c;
    }
}

void normalizar(const char* entrada, char* saida) {
    int i = 0;
    while (entrada[i]) {
        saida[i] = remover_acento(tolower((unsigned char)entrada[i]));
        i++;
    }
    saida[i] = '\0';
}
