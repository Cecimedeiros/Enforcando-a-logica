#ifndef FORCA_H
#define FORCA_H

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
void desenhar_jogo(const char* display, int attempts, const char* wrong_letters, int wins);
void desenhar_boneco(int attempts, int x, int y);
int jogar_partida(const char* palavra, const char* dica, Jogo* jogo);

#endif