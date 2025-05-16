#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/Forca.h"
#include "../include/Timer.h"
#include "../include/Screen.h"
#include "../include/Keyboard.h"
#include "../include/Ranking.h"

#define MAX_FRASES 100

int main() {
    #ifdef _WIN32
    system("chcp 65001 > nul" );
    #endif
    
    screenSetColor(YELLOW, BLACK);

    int opcao;

    int qtd_frases = 0;
    char** originais = processamento_palavras("frasesOriginais.txt", &qtd_frases);
    char** equivalentes = processamento_palavras("frasesEquivalentes.txt", &qtd_frases);

    if (originais == NULL || equivalentes == NULL || qtd_frases == 0) {
        screenGotoxy(5, 5);
        printf("Erro ao carregar as frases. Verifique os arquivos .txt\n");
        screenDestroy();
        return 1;
    }

    int sair = 0;
    Jogo jogo;
    jogo.vitorias = 0;
    jogo.tentativas = 0;

    while (!sair) {
        
        screenClear();     
        screenSetColor(YELLOW, BLACK);

        opcao = exibir_menu();

        switch(opcao) {
            case 1: {
                char nome[50];
                int pontos = 0;

                printf("Digite seu nome: ");
                scanf("%s", nome);

                int indice = rand() % qtd_frases;
                char* frase_original = originais[indice];
                char* frase_equivalente = equivalentes[indice];

                
                int resultado = jogar_partida(frase_equivalente, frase_original, &jogo);
                screenGotoxy(5, MAXY - 4);
                if (resultado == 1) {
                    printf("Muito bem! Você descobriu a proposição equivalente.\n");
                    pontos +=1;          
                       
                } else {
                    printf("A proposição correta era: %s\n", frase_equivalente);
                    pontos= 0;
                }
                salvar_pontuacao(nome,pontos);   
                screenGotoxy(5, MAXY - 2);
                printf("\nDeseja jogar novamente? (S/N): ");
                char resposta;
                scanf(" %c", &resposta);
                if (toupper(resposta) != 'S') {
                    sair = 1;
                }
                break;
            }
            case 2:{
                exibir_ranking();
                break;
            }
            case 3:{
                sair = 1;
                break;
            }
            default:{
                printf("Opção inválida!\n");
                break;
            }
        }
    }    
    for (int i = 0; i < qtd_frases; i++) {
        free(originais[i]);
        free(equivalentes[i]);
    }
    free(originais);
    free(equivalentes);
    screenDestroy();

    return 0;
}

