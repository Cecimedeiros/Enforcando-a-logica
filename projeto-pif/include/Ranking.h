#ifndef RANKING_H
#define RANKING_H

typedef struct {
    char nome[50];
    int pontos;
} Jogador;

int exibir_menu();
void salvar_pontuacao(char nome[], int pontos);
void exibir_ranking();

#endif