#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/Forca.h"
#include "../include/Timer.h"
#include "../include/Screen.h"
#include "../include/Keyboard.h"

#define MAX_FRASES 100

int main() {
    #ifdef _WIN32
    system("chcp 65001 > nul" );
    #endif
    
    screenSetColor(YELLOW, BLACK);
    keyboardInit();
    printf("Jogo iniciado. Pressione 'ç' para sair.\n");

    int qtd_frases = 0;
    char** originais = processamento_palavras("frasesOriginais.txt", &qtd_frases);
    char** equivalentes = processamento_palavras("frasesEquivalentes.txt", &qtd_frases);

    if (originais == NULL || equivalentes == NULL || qtd_frases == 0) {
        screenGotoxy(5, 5);
        printf("Erro ao carregar as frases. Verifique os arquivos .txt\n");
        screenDestroy();
        return 1;
    }

    int sair = 0;
    Jogo jogo;
    jogo.vitorias = 0;

    while (!sair) {
        
        screenClear();     
        screenSetColor(YELLOW, BLACK);

        int indice = rand() % qtd_frases;
        char* frase_original = originais[indice];
        char* frase_equivalente = equivalentes[indice];

        
        int resultado = jogar_partida(frase_equivalente, frase_original, &jogo);
        if (resultado == 1) {
            printf("Muito bem! Você descobriu a proposição equivalente.\n");
        } else {
            printf("A proposição correta era: %s\n", frase_equivalente);
        }

        printf("\nDeseja jogar novamente? (S/N): ");
        char opcao;
        scanf(" %c", &opcao);

        if (toupper(opcao) != 'S') {
            sair = 1;
        }
    }

    for (int i = 0; i < qtd_frases; i++) {
        free(originais[i]);
        free(equivalentes[i]);
    }
    free(originais);
    free(equivalentes);

    screenDestroy();
    keyboardDestroy();
    return 0;
}
