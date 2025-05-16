#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Ranking.h"
#include "../include/Keyboard.h"


int exibir_menu() {
    int opcao;
    printf("===== MENU PRINCIPAL =====\n");
    printf("1 - Jogar\n");
    printf("2 - Ver Ranking\n");
    printf("3 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    return opcao;
}

void salvar_pontuacao(char nome[], int pontos) {
    FILE *arquivo = fopen("ranking.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "%s %d\n", nome, pontos);
        fclose(arquivo);
    } else {
        printf("Erro ao salvar pontuação!\n");
    }
}

void exibir_ranking() {

    char* nomearq = "ranking.txt";
    FILE *arquivo = fopen(nomearq, "r");
    
    if (arquivo == NULL) {
        printf("Ranking ainda não disponível.\n");
        printf("\nPressione ENTER para continuar...");
        getchar(); 
        getchar();
        return;
    }
    
    Jogador jogador;
    int entrou = 0;
    
    printf("\n===== RANKING =====\n");
    
    while (fscanf(arquivo, "%s %d", jogador.nome, &jogador.pontos) == 2) {
        printf("%s - %d pontos\n", jogador.nome, jogador.pontos);
        entrou = 1;
    }
    
    if (!entrou) {
        printf("Nenhum jogador encontrado no ranking.\n");
    }
    
    fclose(arquivo);
    
    printf("\nPressione ENTER para continuar...");
    getchar(); 
    getchar(); 

}
