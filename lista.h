#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdlib.h>
#include <string.h>
#include "palavra.h"

typedef struct lista{
    PALAVRA palavra;
    struct lista *prox;
    struct lista *ant;
}LISTA;

LISTA* CriaLista() {
    LISTA *sentinela = (LISTA *) malloc(sizeof(LISTA));
    sentinela->prox = sentinela;
    sentinela->ant = sentinela;
    return sentinela;
}

/* Se a palavra existir na lista, a função incrementa a qtdOcorrencias 
 da palavra, adiciona uma linha e retorna 1. Caso não exista, retorna 0 */
 /*
int ExisteNaLista(LISTA *lista, char *palavra, int linha) {
    LISTA *aux = lista->prox;
    
    while(aux != lista) {
        
        if(strcmp(aux->palavra.letras, palavra) == 0){
            aux->palavra.qtdOcorrencias++;
            AdicionaLinha(&aux->palavra, linha);
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}
*/
// Função que encontra a palavra e mostra ela na tela
/*void BuscaPalavra(LISTA *lista, char *palavra) {
    LISTA *aux = lista->prox;
    
    while(aux != lista) {
        
        if(strcmp(aux->palavra.letras, palavra) == 0){
            printf("\n ---------- PALAVRA ENCONTRADA ---------- \n");
            printf("Palavra: %s\n", aux->palavra.letras);
            printf("Quantidade de Ocorrencias: %d\n", aux->palavra.qtdOcorrencias);
            printf("Linhas em que aparece: ");
            for(int i = 0; i < aux->palavra.qtdOcorrencias; i++) {
                printf(" %d -", aux->palavra.linhas[i]);
            }
            printf("\n ----------------------------------------\n");
            return;
        }
        aux = aux->prox;
    }

    printf(" ---------- PALAVRA NAO ENCONTRADA ---------- \n");
}

LISTA* InsereEmOrdemAlfabetica(LISTA *lista, PALAVRA *palavra) {
    LISTA *nova = (LISTA *) malloc (sizeof(LISTA));
    nova->palavra = *palavra;

    if(lista->prox == lista) {
        lista->prox = nova;
        lista->ant = nova;
        nova->prox = lista;
        nova->ant = lista;

    }else {
        LISTA *aux = lista->prox;
        int entrou = 0;

        while(aux != lista && !entrou) {
            if(strcmp(palavra->letras, aux->palavra.letras) < 0) {
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

    return lista;
}

void ImprimeLista(LISTA *lista) {
    if(lista == NULL) {
        printf("A lista está vazia.\n\n");
    }else{
        LISTA *aux = lista->prox;

        printf("------------ LISTA ------------\n");
        while(aux!= lista) {
            printf("Palavra: %s\n", aux->palavra.letras);
            printf("Quantidade de Ocorrencias: %d\n", aux->palavra.qtdOcorrencias);
            printf("Linhas em que aparece: ");
            for(int i = 0; i < aux->palavra.qtdOcorrencias; i++) {
                printf(" %d -", aux->palavra.linhas[i]);
            }
            printf("\n\n");
            aux = aux->prox;
        }
        printf("-------------------------------\n");
    }
}

int QtdPalavras(LISTA *lista) {

    LISTA *aux = lista->prox;
    int ct = 0;
    while (aux != lista)
    {
        ct++;
        aux = aux->prox;
    }
    
    return ct;
}

LISTA* DestruirLista(LISTA *lista) {    
    LISTA *aux = lista;
    lista->ant->prox = NULL;
    while(aux != NULL) {
        lista = lista->prox;
        free(aux->palavra.linhas);
        free(aux);
        aux = lista;
    }
    return NULL;
}*/

#endif
