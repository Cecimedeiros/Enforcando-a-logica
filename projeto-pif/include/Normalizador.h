#ifndef NORMALIZADOR_H
#define NORMALIZADOR_H

char remover_acento(char c); 
char remover_acento_utf8(unsigned char c1, unsigned char c2);
void normalizar(const char* entrada, char* saida);

#endif
