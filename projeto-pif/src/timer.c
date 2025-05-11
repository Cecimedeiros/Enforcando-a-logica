#include "../include/timer.h"
#include <stdio.h>
#include <unistd.h>

void time(int segundos){
    segundos= 120;
    for (int i= segundos; i>0; i--){
        printf("Tempo restante: %d segundos...\n", i);
        sleep(1);
    }
    printf("Tempo encerrado!\n");
}