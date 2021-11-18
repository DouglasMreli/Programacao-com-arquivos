#ifndef _LISTA_H_
#define _LISTA_H_

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
    return NULL;
}

int ExisteNaLista(LISTA *lista, char *palavra) {
    LISTA *aux = lista->prox;

    while(aux != lista) {
        if(strcmp(aux->palavra.letras, palavra))
            return 1;
        aux = aux->prox;
    }

    return 0;
}


#endif