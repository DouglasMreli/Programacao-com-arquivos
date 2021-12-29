#ifndef _PALAVRA_H_
#define _PALAVRA_H_

#include <string.h>
#include "ocorrencia.h"

typedef struct palavra {
    char letras[50]; //a palavra em questão
    int qtdOcorrencias; //quantidade de arquivos que possuem a palavra
    OCORRENCIA *ocorrencias; //lista contendo informações da ocorrência de uma palavra em um arquivo
    struct palavra *prox, *ant;//ponteiro para a próxima palavra encontrada em qualquer arquivo (em ordem alfabética)
}PALAVRA;

PALAVRA* CriaListaPalavra() {
    PALAVRA *sentinela = (PALAVRA *) malloc(sizeof(PALAVRA));
    sentinela->prox = sentinela;
    sentinela->ant = sentinela;
    return sentinela;
}

PALAVRA* CriaNovaPlavra(char *palavra, int arquivo, int linha) {
    PALAVRA *nova_palavra = (PALAVRA *)malloc(sizeof(PALAVRA));
    
    strcpy(nova_palavra->letras, palavra);
    nova_palavra->ocorrencias = CriaListaOcorrencia();
    nova_palavra->ocorrencias->prox = CriaOcorrencia(arquivo, linha);
    nova_palavra->qtdOcorrencias = 1;
    nova_palavra->prox = NULL;
    nova_palavra->ant = NULL;

    return nova_palavra;
}

PALAVRA* CriaPalavraDoArqDat(char *palavra, int qtdArquivo) {
    PALAVRA *nova_palavra = (PALAVRA *)malloc(sizeof(PALAVRA));
    
    strcpy(nova_palavra->letras, palavra);
    nova_palavra->ocorrencias = CriaListaOcorrencia();
    nova_palavra->qtdOcorrencias = qtdArquivo;
    nova_palavra->prox = NULL;
    nova_palavra->ant = NULL;

    return nova_palavra;
}

int ExisteNaLista(PALAVRA *lista, char *palavra, int arquivo, int linha) {
    PALAVRA *aux = lista->prox;
    
    while(aux != lista) {
        
        if(strcmp(aux->letras, palavra) == 0){
            if(MesmoArquivo(aux->ocorrencias, arquivo)) {
                AdicionaLinha(aux->ocorrencias, linha);
            }else{
                aux->qtdOcorrencias++;
                InsereOcorrenciaNoFim(aux->ocorrencias, arquivo, linha);
            }
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

void InsereEmOrdemAlfabetica(PALAVRA *lista, char *palavra, int arquivo, int linha) {
    PALAVRA *nova = CriaNovaPlavra(palavra, arquivo, linha);
    
    if(lista->prox == lista) {
        lista->prox = nova;
        lista->ant = nova;
        nova->prox = lista;
        nova->ant = lista;

    }else {
        PALAVRA *aux = lista->prox;
        int entrou = 0;

        while(aux != lista && !entrou) {
            if(strcmp(nova->letras, aux->letras) < 0) {
                nova->ant = aux->ant;
                nova->prox = aux;
                aux->ant->prox = nova;
                aux->ant = nova;
                entrou = 1;
            }
                aux = aux->prox;
        }
        // Adicionar no final da lista
        if(!entrou) {
            nova->ant = aux->ant;
            nova->prox = aux;
            aux->ant->prox = nova;
            aux->ant = nova;
        }
    }

}

void InserePalavraNoFim(PALAVRA *lista, PALAVRA *novo) {
    if(lista->prox != lista) {
        PALAVRA *aux = lista->prox;
        while(aux->prox != lista) {
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->ant = aux;
    }else{
        lista->prox = novo;
        novo->ant = lista;
    }
    novo->prox = lista;
    
}

void ImprimeListaPalavra(PALAVRA *lista) {
    if(lista == NULL) {
        printf("A lista está vazia.\n\n");
    }else{
        PALAVRA *aux = lista->prox;

        printf("------------ LISTA ------------\n");
        while(aux!= lista) {
            printf("Palavra: %s\n",aux->letras);
            printf("Quantidade de arquivos em que aparece: %d\n", aux->qtdOcorrencias);
            printf(" ----- Ocorrencias -----\n");
            ImprimeListaOcorrencia(aux->ocorrencias);
            printf("\n-------------------------------\n");
            aux = aux->prox;
        }
        
    }
}

PALAVRA* DestruirListaPalavras(PALAVRA* lista) {
    
    PALAVRA *aux = lista->prox;
    lista->ant->prox = NULL;
    while(aux != NULL) {
        aux->ocorrencias = DestruirListaOcorrencia(aux->ocorrencias); 
        free(aux);
        aux = aux->prox;
    }
    free(lista);
    return NULL;
}


#endif