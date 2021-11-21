#ifndef _ARQTXT_H_
#define _ARQTXT_H_

#include <stdio.h>
#include <stdlib.h>

FILE* AbreArquivoTXT() {
    printf("Digite o nome do arquivo: \n");
    char nome[20];
    scanf("%s", nome);

    FILE *arq;
    arq = fopen(nome, "r");

    if(arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(0);
    }

    return arq;
}


#endif