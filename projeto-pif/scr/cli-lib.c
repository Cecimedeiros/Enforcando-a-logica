#include "../include/cli-lib.h"
#include <stdlib.h>
#include <string.h>

char** processamento_palavras(const char* filename, int* qtd_palavras){
    int qtd_palavras=0;

    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("Erro ao abrir frasesOriginais.txt\n");
        return NULL;
    }

    char **palavras= malloc(100 * sizeof(char*));
    if (palavras==NULL){
        printf("Erro de memória.\n");
        return NULL;
    }
    char buffer[100];
    while(fgets(buffer, 100, file)){
        buffer[strcspn(buffer, "\n")]='\0';
        if (strlen(buffer)==0){
            continue;
        }
        palavras[*qtd_palavras]=malloc(strlen(buffer)+1);
        strcpy(palavras[*qtd_palavras], buffer);
        (*qtd_palavras)++;
    }
    fclose(file);
    return palavras;
}


