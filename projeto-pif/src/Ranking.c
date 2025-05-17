#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Ranking.h"
#include "../include/Keyboard.h"
#include "../include/Screen.h"


int exibir_menu() {
    screenInit(0);
    screenDrawBorders();

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
    FILE *arquivo = fopen("ranking.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "%s %d\n", nome, pontos);
        fclose(arquivo);
    } else {
        printf("Erro ao salvar pontuação!\n");
    }
}

void exibir_ranking() {
    screenClear();
    screenInit(0);
    screenDrawBorders();
    char* nomearq = "ranking.txt";
    FILE *arquivo = fopen(nomearq, "r");
    
    if (arquivo == NULL) {
        printf("Ranking ainda não disponível.\n");
        printf("\n➡️ Pressione ENTER para continuar...");
        getchar(); 
        getchar();
        return;
    }
    
    Jogador jogador;
    int entrou = 0;

    int largura_tela = 80; 
    int centro = largura_tela / 2;
    int linha = 6;
    
    screenGotoxy(centro - 12, 4);
    printf("===== 🏆 RANKING 🏆 =====");
    
    while (fscanf(arquivo, "%s %d", jogador.nome, &jogador.pontos) == 2) {
        char linha_texto[100];
        
        snprintf(linha_texto, sizeof(linha_texto), "%s - %d pontos", jogador.nome, jogador.pontos);

        int tam = strlen(linha_texto);
        int pos_x = centro - tam / 2;

        screenGotoxy(pos_x, linha);
        printf("%s", linha_texto);

        linha++;

        entrou = 1;
    }
    
    if (!entrou) {
        screenGotoxy(centro - 17, 10);
        printf("❌ Nenhum jogador encontrado no ranking! ");
    }
    
    fclose(arquivo);
    screenGotoxy(centro - 17, 18);
    printf("➡️ Pressione ENTER para continuar...");
    getchar(); 
    getchar(); 

}
