#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "../include/Forca.h"
#include "../include/Timer.h"
#include "../include/Screen.h"
#include "../include/Ranking.h"
#include "../include/Menu.h"

#define MAX_FRASES 100

int main() {
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
    jogo.partidas_concluidas=0;

    while (!sair) {
        
        screenClear();     
        screenSetColor(YELLOW, BLACK);

        opcao = exibir_menu();

        switch(opcao) {
            case 1: {
                
                int largura_tela = 80; 
                int centro = largura_tela / 2;

                char nome[50];
                int pontos = 0;
                
                jogo.vitorias = 0;
                jogo.partidas_concluidas = 0;
                char resposta;

                screenGotoxy(centro - 10, 18);
                printf("Digite seu nome: ");
                scanf("%s", nome);
                strcpy(jogo.nome, nome);


                do{
                    int indice = rand() % qtd_frases;
                    char* frase_original = originais[indice];
                    char* frase_equivalente = equivalentes[indice];

                    int resultado = jogar_partida(frase_equivalente, frase_original, &jogo);
                    jogo.partidas_concluidas++;

                    if (resultado == 1) {
                        const char* msg_vitoria = "🏆 Você acertou a frase equivalente! 🏆";
                        int x_vitoria = (MAXX - strlen(msg_vitoria)) / 2;
                        screenGotoxy(x_vitoria, MAXY - 14);
                        printf("%s", msg_vitoria);
                    } else {
                        int x_titulo = (MAXX - strlen("A proposição correta era:")) / 2;
                        screenGotoxy(x_titulo, MAXY - 16);
                        printf("A proposição correta era:");

                        int x_frase = (MAXX - strlen(frase_equivalente)) / 2;
                        screenGotoxy(x_frase, MAXY - 14);
                        printf("%s", frase_equivalente);
                        
                        
                    }
                      
                    screenGotoxy(20, MAXY - 6);
                    printf("🔎 Deseja jogar novamente? (S/N): ");
                    scanf(" %c", &resposta);

                } while (toupper(resposta)== 'S');

                salvar_pontuacao(nome,pontos); 
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
                int largura_tela = 80; 
                int centro = largura_tela / 2;
                
                screenGotoxy(centro - 27, 20);
                printf("❌ Opção inválida! Pressione ENTER para continuar.\n");
                getchar();
                getchar();
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