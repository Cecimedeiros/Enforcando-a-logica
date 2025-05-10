#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "../include/cli-lib.h"

#define MAX_FRASES 100

int main() {
    system("chcp 65001 > nul");  
    srand(time(NULL));  

    int qtd_frases = 0;
    char** originais = processamento_palavras("../frasesOriginais.txt", &qtd_frases);
    char** equivalentes = processamento_palavras("../frasesEquivalentes.txt", &qtd_frases);

    if (originais == NULL || equivalentes == NULL || qtd_frases == 0) {
        printf("Erro ao carregar as frases. Verifique os arquivos .txt\n");
        return 1;
    }

    int sair = 0;
    Jogo jogo;
    jogo.vitorias = 0;

    while (!sair) {
        int indice = rand() % qtd_frases;
        char* frase_original = originais[indice];
        char* frase_equivalente = equivalentes[indice];

        printf("\nProposição lógica: %s\n", frase_original);
        printf("Tente adivinhar sua forma equivalente jogando forca!\n");

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

    return 0;
}
