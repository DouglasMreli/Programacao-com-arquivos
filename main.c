#include <stdio.h>
#include <stdlib.h>

#include "palavra.h"
#include "lista.h"


void Menu () {
    printf("Escolha uma das opcoes abaixo:\n");
    printf("    1. Criar um indice para um arquivo texto\n");
    printf("    2. Utilizar um indice para realizar buscas por palavras\n");
    printf("    3. Encerrar o programa:\n");
    printf(">> ");
}

int main() {
   
    int opcao = 0;
    while(opcao != 3) {
        Menu();
        scanf("%d", &opcao);
    }

   return 0;
}