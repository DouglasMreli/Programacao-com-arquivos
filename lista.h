#ifndef _LISTA_H_
#define _LISTA_H_

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
int ExisteNaLista(LISTA *lista, char *palavra, int linha) {
    LISTA *aux = lista->prox;
    
    while(aux != lista) {
        
        if(strcmp(aux->palavra.letras, palavra) == 0){
            printf("sim\n");
            aux->palavra.qtdOcorrencias++;
            AdicionaLinha(&aux->palavra, linha);
            return 1;
        }
        aux = aux->prox;
    }
    printf("nao\n");
    return 0;
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
            printf("COMPARACAO: %s com %s\n",aux->palavra.letras, palavra);
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


#endif