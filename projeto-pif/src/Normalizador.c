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

char remover_acento_utf8(unsigned char c1, unsigned char c2) {
    if (c1 == 0xC3) {
        switch (c2) {
            // A e á à â ã ä
            case 0xA1: case 0xA0: case 0xA2: case 0xA3: case 0xA4:
                return 'a';
            // E é è ê ë
            case 0xA9: case 0xA8: case 0xAA: case 0xAB:
                return 'e';
            // I í ì î ï
            case 0xAD: case 0xAC: case 0xAE: case 0xAF:
                return 'i';
            // O ó ò ô õ ö
            case 0xB3: case 0xB2: case 0xB4: case 0xB5: case 0xB6:
                return 'o';
            // U ú ù û ü
            case 0xBA: case 0xB9: case 0xBB: case 0xBC:
                return 'u';
            // Ç ç
            case 0xA7:
                return 'c';
        }
    }
    return 0; 
}

void normalizar(const char* entrada, char* saida) {
    int i = 0;
    while (entrada[i]) {
        saida[i] = remover_acento(tolower((unsigned char)entrada[i]));
        i++;
    }
    saida[i] = '\0';
}
