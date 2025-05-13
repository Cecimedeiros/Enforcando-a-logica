#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "../include/tempo.h"

time_t tempo_final;
int tempo_ativo = 0;

void iniciar_cronometro(int duracao_segundos) {
    tempo_final = time(NULL) + duracao_segundos;  
}
int tempo_restante() {
    int restante = (int)(tempo_final - time(NULL));
    return restante > 0 ? restante : 0;  
}
void* atualizar_tempo(void* arg){
    static int resultado = 0;

    while (tempo_ativo) {
        int restante = tempo_restante();
        int min = restante / 60;
        int seg = restante % 60;

        printf("\rTempo restante: %02d:%02d ", min, seg);
        fflush(stdout);  

        if (restante <= 0) {
            tempo_ativo = 0;
            printf("\nTempo encerrado! Aperte 'Ctrl' + 'C' para finalizar o programa. \n");
            break;
        }
            
        sleep(1);  
    }
    
    
    return NULL;
}


