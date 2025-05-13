#ifndef CLI_LIB_H
#define CLI_LIB_H

typedef struct {
    int tentativas;
    int acertos;
    int vitorias;
} Jogo;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


char** processamento_palavras(const char* filename, int* qtdpalavras);
char* sortear_palavra(const char** words, int count);
void desenhar_jogo(const char* display, int attempts, const char* wrong_letters, int wins);
void desenhar_boneco(int attempts);
int jogar_partida(const char* palavra, const char* dica, Jogo* jogo);
int verificar_equivalencia(const char* original, const char* tentativa);

#endif