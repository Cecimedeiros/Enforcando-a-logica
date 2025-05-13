#include "../include/cli-lib.h"
#include "../include/normalizador.h"
#include "../include/tempo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "screen.h"

int x= 5, y=5, largura= 30, altura= 10;

#include <pthread.h>
#include <unistd.h>

#define MAX_FRASES 100
#define MAX_ATTEMPTS 6

char** processamento_palavras(const char* filename, int* qtd_frases) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir %s\n", filename);
        return NULL;
    }

    char** frases = malloc(MAX_FRASES * sizeof(char*));
    if (frases == NULL) {
        fclose(file);
        return NULL;
    }

    char buffer[256];
    *qtd_frases = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) == 0) continue;

        frases[*qtd_frases] = malloc(strlen(buffer) + 1);
        strcpy(frases[*qtd_frases], buffer);
        (*qtd_frases)++;
    }

    fclose(file);
    return frases;
}

void desenhar_boneco(int tentativas) {

    printf("\n");
    printf(" +----+\n");
    printf(" |    |\n");
    printf(" %c    |\n", (tentativas >= 1) ? 'O' : ' ');
    printf("%c%c%c   |\n",
        (tentativas >= 3) ? '/' : ' ',
        (tentativas >= 2) ? '|' : ' ',
        (tentativas >= 4) ? '\\' : ' ');
    printf("%c %c   |\n",
        (tentativas >= 5) ? '/' : ' ',
        (tentativas >= 6) ? '\\' : ' ');
    printf("      |\n");
    printf("=========\n");
}

void desenhar_jogo(const char* exibicao, int tentativas, const char* erradas, int vitorias) {
    
    desenhar_boneco(tentativas);
    printf("\nPontos: %d\n", vitorias);
    printf("Letras erradas: %s\n", erradas);
    printf("Chances restante de errar: %d\n", MAX_ATTEMPTS - tentativas);
    printf("\nFrase equivalente: %s\n\n", exibicao);
    
}

int verificar_equivalencia(const char* original, const char* tentativa) {
    FILE* arquivo = fopen("../frasesEquivalentes.txt", "r");
    if (!arquivo) return 0;

    char linha_original[256];
    char linha_equivalente[256];

    while (fgets(linha_original, sizeof(linha_original), arquivo)) {
        linha_original[strcspn(linha_original, "\n")] = '\0';

        if (fgets(linha_equivalente, sizeof(linha_equivalente), arquivo)) {
            linha_equivalente[strcspn(linha_equivalente, "\n")] = '\0';

            if (strcmp(original, linha_original) == 0) {
                fclose(arquivo);
                return strcmp(tentativa, linha_equivalente) == 0;
            }
        }
    }

    fclose(arquivo);
    return 0;
}

int jogar_partida(const char* frase_equivalente, const char* frase_original, Jogo* jogo) {
    
    int tamanho = strlen(frase_equivalente);
    char* exibicao = malloc(tamanho + 1);

    int total_para_acertar = 0;
    for (int i = 0; i < tamanho; i++) {
        if (frase_equivalente[i] == ' ' || frase_equivalente[i] == ',' || frase_equivalente[i] == '.' || frase_equivalente[i] == '-') {
            exibicao[i] = frase_equivalente[i];
        } else {
            exibicao[i] = '_';
            total_para_acertar++;
        }
    }
    exibicao[tamanho] = '\0';

    jogo->tentativas = 0;
    jogo->acertos = 0;
    char erradas[50] = "";
    
    iniciar_cronometro(120);
    tempo_ativo = 1;  
    pthread_t thread_tempo;
    pthread_create(&thread_tempo, NULL, atualizar_tempo, NULL);

    while (jogo->tentativas < MAX_ATTEMPTS && jogo->acertos < total_para_acertar) {
        
        screenClear();

        printf("\n🩻 ENFORCANDO A LÓGICA: Acerte a frase equivalente da original jogando forca!\n");
        printf("\nFrase original: %s\n\n", frase_original);
        desenhar_jogo(exibicao, jogo->tentativas, erradas, jogo->vitorias);


        char tentativa;
        scanf(" %c", &tentativa);
        tentativa = tolower(tentativa);
        char tentativa_normalizada = remover_acento(tentativa);

        int ja_usou = 0;
        for (int i = 0; i < tamanho; i++) {
            if (tolower(remover_acento(exibicao[i])) == tentativa_normalizada) {
                ja_usou = 1;
                break;
            }
        }
        for (int i = 0; erradas[i] != '\0'; i++) {
            if (tolower(erradas[i]) == tentativa_normalizada) {
                ja_usou = 1;
                break;
            }
        }
        if (ja_usou) continue;

        int acertou = 0;
        for (int i = 0; i < tamanho; i++) {
            if (remover_acento(tolower(frase_equivalente[i])) == tentativa_normalizada && exibicao[i] == '_') {
                exibicao[i] = frase_equivalente[i];
                jogo->acertos++;
                acertou = 1;
            }
        }

        if (!acertou) {
            int len = strlen(erradas);
            erradas[len] = tentativa;
            erradas[len + 1] = '\0';
            jogo->tentativas++;
        }
    }
    tempo_ativo = 0; 
    pthread_join(thread_tempo, NULL);

    screenClear();
    desenhar_jogo(exibicao, jogo->tentativas, erradas, jogo->vitorias);
    free(exibicao);

    if (jogo->acertos == total_para_acertar) {
        screenClear();
        printf("\nParabéns! Você acertou a frase equivalente!\n");
        jogo->vitorias++;

        return 1;
    } else {
        screenClear();
        printf("\nVocê perdeu!\n");
        return -1;
    }

}
