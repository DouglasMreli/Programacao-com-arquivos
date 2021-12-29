#ifndef _INDICE_H_
#define _INDICE_H_

#include <stdio.h>
#include <string.h>
#include "arq.h"
#include "palavra.h"

typedef struct indice{
    int qtdArquivos; 
    struct arquivo *arquivos; 
    int qtdPalavras;
    PALAVRA *palavras;
}INDICE;

FILE* AbreArquivoDat() {
    FILE *arq;
    arq = fopen("indice.dat", "rb");

    if(arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(0);
    }

    return arq;
}

INDICE* CriaIndice() {
    INDICE* novo_indice = (INDICE*)malloc(sizeof(INDICE));

    novo_indice->qtdArquivos = 0;
    novo_indice->qtdPalavras = 0;
    novo_indice->arquivos = CriaListaArq();
    novo_indice->palavras = CriaListaPalavra();

    return novo_indice; 
}

void SalvarIndiceAtual(INDICE* lista) {
    FILE *arq = fopen("indice.dat", "wb");
    
    int qtdArquivos = lista->qtdArquivos;
    ARQUIVO *auxArq = lista->arquivos;

    fwrite(&qtdArquivos, sizeof(int), 1, arq);
    auxArq = auxArq->prox;
    while(auxArq != lista->arquivos) {
        int tamanhoNome = strlen(auxArq->nomeArquivo) + 1;
        fwrite(&tamanhoNome ,sizeof(int), 1, arq);
        fwrite(&auxArq->nomeArquivo, sizeof(char), tamanhoNome, arq);
        auxArq = auxArq->prox;
    }

    int qtdPalavras = lista->qtdPalavras;
    PALAVRA *auxPlvr = lista->palavras;
    
    fwrite(&qtdPalavras, sizeof(int), 1, arq);
    auxPlvr = auxPlvr->prox;
    while(auxPlvr != lista->palavras) {
        int tamanhoPalavra = strlen(auxPlvr->letras) + 1;
        fwrite(&tamanhoPalavra , sizeof(int), 1, arq);
        fwrite(&auxPlvr->letras, sizeof(char), tamanhoPalavra, arq);
        fwrite(&auxPlvr->qtdOcorrencias, sizeof(int), 1, arq);

        OCORRENCIA *auxOc = auxPlvr->ocorrencias;
        auxOc = auxOc->prox;
        while(auxOc != NULL) {
            fwrite(&auxOc->arquivo, sizeof(int), 1, arq);
            fwrite(&auxOc->qtdOcorrencias, sizeof(int), 1, arq);
            for(int i =0; i < auxOc->qtdOcorrencias; i++) {
                fwrite(&auxOc->linhas[i], sizeof(int), 1, arq);
            }
            auxOc = auxOc->prox;
        } 

        auxPlvr = auxPlvr->prox;
    }

    fclose(arq);
}

void ImprimeIndice(INDICE *indice) {
    printf(" Quantidade de arquivos: %d\n", indice->qtdArquivos);
    printf(" ----- ARQUIVOS -----\n");
    ImprimeListaArq(indice->arquivos);
    ImprimeListaPalavra(indice->palavras);
}

INDICE* DestruirListaIndice(INDICE *indice) {
    
    indice->palavras = DestruirListaPalavras(indice->palavras);
    indice->arquivos = DestruirListaArquivos(indice->arquivos);
    free(indice);
        
    return NULL;
}

#endif
