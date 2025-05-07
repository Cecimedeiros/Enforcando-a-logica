#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "../include/cli-lib.h"

int main() {
    srand(time(NULL));

    int qtd_palavras = 0;
    char** palavras = processamento_palavras("../frasesOriginais.txt", &qtd_palavras);

    if (palavras == NULL || qtd_palavras == 0) {
        printf("Erro ao carregar as palavras.\n");
        return 1;
    }

    int sair = 0;
    Jogo jogo;
    jogo.vitorias = 0;

    while (!sair) {
        char* palavra = sortear_palavra((const char**)palavras, qtd_palavras);

        int resultado = jogar_partida(palavra, &jogo);

        printf("\nDeseja jogar novamente? (S/N): ");
        char opcao;
        scanf(" %c", &opcao);

        if (toupper(opcao) != 'S') {
            sair = 1;
        }
    }

    for (int i = 0; i < qtd_palavras; i++) {
        free(palavras[i]);
    }
    free(palavras);

    return 0;
}
