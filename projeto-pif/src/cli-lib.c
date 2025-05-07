#include "../include/cli-lib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


#define MAX_WORDS 100
#define MAX_WORD_SIZE 20
#define MAX_ATTEMPTS 6


char** processamento_palavras(const char* filename, int* qtd_palavras){
    
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("Erro ao abrir frasesOriginais.txt\n");
        return NULL;
    }

    char **palavras= malloc(100 * sizeof(char*));
    if (palavras==NULL){
        printf("Erro de memória.\n");
        return NULL;
    }
    char buffer[100];
    while(fgets(buffer, 100, file)){
        buffer[strcspn(buffer, "\n")]='\0';
        if (strlen(buffer)==0){
            continue;
        }
        palavras[*qtd_palavras]=malloc(strlen(buffer)+1);
        strcpy(palavras[*qtd_palavras], buffer);
        (*qtd_palavras)++;
    }
    fclose(file);
    return palavras;
}

char* sortear_palavra(const char** words, int count){
    return (char*) words[rand() % count];
}

void desenhar_jogo(const char* display, int attempts, const char* wrong_letters, int wins) {
    printf("Placar: %d\n", wins);
    printf("Palavra: %s\n", display);
    printf("Tentativas restantes: %d\n", MAX_ATTEMPTS - attempts);
    printf("Letras erradas: %s\n", wrong_letters);
    desenhar_boneco(attempts);
}

void desenhar_boneco(int attempts){
    printf("\n");
    printf(" +----+\n");
    printf(" |    |\n");
    printf(" %c    |\n", (attempts > 0) ? 'O' : ' ');
    printf("%c%c%c   |\n",
           (attempts > 2) ? '/' : ' ',
           (attempts > 1) ? '|' : ' ',
           (attempts > 3) ? '\\' : ' ');
    printf(" %c %c  |\n",
           (attempts > 4) ? '/' : ' ',
           (attempts > 5) ? '\\' : ' ');
    printf("      |\n");
    printf("=========\n");
}

int jogar_partida(const char* palavra, Jogo* jogo){
    int tamanho = strlen(palavra);
    char* exibicao = malloc(tamanho + 1);
    for (int i = 0; i < tamanho; i++) {
        exibicao[i] = '_';
    }
    exibicao[tamanho] = '\0';
    
    jogo->tentativas = 0;
    jogo->acertos = 0;
    char letras_erradas[27] = "";
    
    while (jogo->tentativas < MAX_ATTEMPTS && jogo->acertos < tamanho) {
        system("cls");
        desenhar_jogo(exibicao, jogo->tentativas, letras_erradas, jogo->vitorias);
    
        printf("\nDigite uma letra: ");
        char tentativa;
        scanf(" %c", &tentativa);
        tentativa = toupper(tentativa);
    
        if (!isalpha(tentativa)) continue;
    
        int ja_usou = 0;
        for (int i = 0; i < tamanho; i++) {
            if (tentativa == exibicao[i]) {
                ja_usou = 1;
                break;
            }
        }
        for (int i = 0; letras_erradas[i] != '\0'; i++) {
            if (tentativa == letras_erradas[i]) {
                ja_usou = 1;
                break;
            }
        }
        if (ja_usou) continue;
    
        int acertou = 0;
        for (int i = 0; i < tamanho; i++) {
            if (toupper(palavra[i]) == tentativa) {
                exibicao[i] = tentativa;
                acertou = 1;
                jogo->acertos++;
            }
        }
    
        if (!acertou) {
            int len = strlen(letras_erradas);
            letras_erradas[len] = tentativa;
            letras_erradas[len + 1] = '\0';
            jogo->tentativas++;
        }
    }
    
    system("cls");
    desenhar_jogo(exibicao, jogo->tentativas, letras_erradas, jogo->vitorias);
    free(exibicao);
    
    if (jogo->acertos == tamanho) {
        printf("\nParabéns! Você venceu!\n");
        jogo->vitorias++;
        return 1;
    } else {
        printf("\nVocê perdeu! A palavra era: %s\n", palavra);
        return -1;
    }
}