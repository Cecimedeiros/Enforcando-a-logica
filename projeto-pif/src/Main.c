#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
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

    srand(time(NULL));

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

                int largura_tela = 80; 
                int centro = largura_tela / 2;

                screenGotoxy(centro - 10, 18);
                printf("Digite seu nome: ");
                scanf("%s", nome);

                int indice = rand() % qtd_frases;
                char* frase_original = originais[indice];
                char* frase_equivalente = equivalentes[indice];

                
                int resultado = jogar_partida(frase_equivalente, frase_original, &jogo);
                int x_frase = (MAXX - strlen(frase_equivalente)) / 2;
                int y_frase = MAXY - 14;

                if (resultado == 1) {
                    screenGotoxy(20, MAXY - 14);
                    printf("🏆 Você acertou a frase equivalente! 🏆");
                    pontos +=1;          
                }
                else {
                    char msg[256];
                    sprintf(msg, "A proposição correta era: %s", frase_equivalente);

                    screenGotoxy(5, MAXY - 13);
                    printf("%s", msg);

                    pontos = 0;
                }
                salvar_pontuacao(nome,pontos);   
                screenGotoxy(20, MAXY - 6);
                printf("🔎 Deseja jogar novamente? (S/N): ");
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

