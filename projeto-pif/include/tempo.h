#ifndef TEMPO_H
#define TEMPO_H

#include <pthread.h>

extern int tempo_ativo;
extern time_t tempo_final;

void iniciar_cronometro(int duracao_segundos);
int tempo_restante();
void* atualizar_tempo(void* arg);

#endif