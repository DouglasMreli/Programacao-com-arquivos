#ifndef _PALAVRA_H_
#define _PALAVRA_H_

#include <string.h>

typedef struct palavra
{
    char letras[50];
    int qtdOcorrencias;
    int *linhas;
}PALAVRA;

PALAVRA* CriaNovaPlavra(char *palavra, int linha) {
    PALAVRA *nova_palavra = (PALAVRA *)malloc(sizeof(PALAVRA));

    strcpy(nova_palavra->letras, palavra);
    nova_palavra->qtdOcorrencias = 1;

    nova_palavra->linhas = malloc(sizeof(int));
    nova_palavra->linhas[0] = linha;
    
    return nova_palavra;
}

void insereLinhas(PALAVRA *palavra, int *vetor, int qtdOcorrencias) {
    palavra->qtdOcorrencias = qtdOcorrencias;
    palavra->linhas = realloc(palavra->linhas, sizeof(palavra->qtdOcorrencias));
    for(int i = 1; i < qtdOcorrencias; i++) {
        palavra->linhas[i] = vetor[i];
    }
}

void AdicionaLinha(PALAVRA *palavra, int linha) {
    palavra->linhas = realloc(palavra->linhas, sizeof(palavra->qtdOcorrencias));
    palavra->linhas[palavra->qtdOcorrencias - 1] = linha;
}


#endif