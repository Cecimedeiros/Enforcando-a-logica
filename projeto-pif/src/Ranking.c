#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Ranking.h"
#include "../include/Screen.h"

int exibir_menu() {
    screenInit(1);

    int largura_tela = 80; 
    int centro = largura_tela / 2;
    int opcao;

    screenGotoxy(centro - 12, 4);
    printf(" 🧠 MENU PRINCIPAL 🧠 ");

    screenGotoxy(centro - 10, 8);
    printf("[1] 👩‍💻 Jogar ");

    screenGotoxy(centro - 12, 10);
    printf("[2] 📊 Ver Ranking ");

    screenGotoxy(centro - 9, 12);
    printf("[3] 👣 Sair ");

    screenGotoxy(centro - 12, 16);
    printf(" Escolha uma opção: ");
    scanf("%d", &opcao);

    return opcao;
}

void salvar_pontuacao(char nome[], int pontos) {
    int largura_tela = 80; 
    int centro = largura_tela / 2;

    FILE *arquivo = fopen("ranking.txt", "r");
    if (arquivo == NULL) {
        FILE *novo = fopen("ranking.txt", "w");
        if (novo != NULL) {
            fprintf(novo, "%s %d\n", nome, pontos);
            fclose(novo);
        } else {
            screenGotoxy(centro - 9, 12);
            printf("Erro ao criar arquivo de ranking!\n");
        }
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        screenGotoxy(centro - 9, 12);
        printf("Erro ao criar arquivo temporário!\n");
        fclose(arquivo);
        return;
    }

    Jogador jogador;
    int encontrado = 0;

    while (fscanf(arquivo, "%49s %d", jogador.nome, &jogador.pontos) == 2) {
        if (strcmp(jogador.nome, nome) == 0) {
            jogador.pontos += pontos;
            encontrado = 1;
        }
        fprintf(temp, "%s %d\n", jogador.nome, jogador.pontos);
    }

    if (!encontrado) {
        fprintf(temp, "%s %d\n", nome, pontos);
    }

    fclose(arquivo);
    fclose(temp);

    if (remove("ranking.txt") != 0) {
        screenGotoxy(centro - 9, 12);
        printf("Erro ao remover arquivo antigo!\n");
        return;
    }
    if (rename("temp.txt", "ranking.txt") != 0) {
        screenGotoxy(centro - 9, 12);
        printf("Erro ao renomear arquivo temporário!\n");
    }
}

void ordenar_ranking(Jogador* ranking, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ranking[j].pontos > ranking[i].pontos) {
                Jogador temp = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = temp;
            }
        }
    }
}

void exibir_ranking() {

    screenInit(1);
    
    int largura_tela = 80; 
    int centro = largura_tela / 2;
    int linha = 6;

    FILE *arquivo = fopen("ranking.txt", "r");
    
    if (arquivo == NULL) {
        screenGotoxy(centro - 9, 12);
        printf("Ranking ainda não disponível.\n");
        screenGotoxy(centro - 17, 18);
        printf("\n➡️ Pressione ENTER para continuar...");
        getchar(); 
        getchar();
        return;
    }
    
    Jogador ranking[100];
    int total = 0;

    while (fscanf(arquivo, "%49s %d", ranking[total].nome, &ranking[total].pontos) == 2) {
        total++;
        if (total >= 100) break;
    }

    fclose(arquivo);

    ordenar_ranking(ranking, total);

    screenGotoxy(centro - 12, 4);
    printf("===== 🏆 RANKING 🏆 =====");

    if (total == 0) {
        screenGotoxy(centro - 17, 10);
        printf("❌ Nenhum jogador encontrado no ranking! ");
    } else {
        for (int i = 0; i < total; i++) {
            char linha_texto[100];
            snprintf(linha_texto, sizeof(linha_texto), "%s - %d pontos", ranking[i].nome, ranking[i].pontos);
            int tam = strlen(linha_texto);
            int pos_x = centro - tam / 2;
            screenGotoxy(pos_x, linha++);
            printf("%s", linha_texto);
        }
    }

    screenGotoxy(centro - 17, 18);
    printf("➡️ Pressione ENTER para continuar...");
    getchar(); 
    getchar(); 
}