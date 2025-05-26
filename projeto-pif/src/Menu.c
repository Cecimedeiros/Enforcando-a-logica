#include <stdio.h>
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