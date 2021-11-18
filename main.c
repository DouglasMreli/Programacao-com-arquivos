#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "arqtxt.h"

void Menu () {
    printf("Escolha uma das opcoes abaixo:\n");
    printf("    1. Criar um indice para um arquivo texto\n");
    printf("    2. Utilizar um indice para realizar buscas por palavras\n");
    printf("    3. Encerrar o programa:\n");
    printf(">> ");
}

void CriaIndice() {
    FILE *arq = AbreArquivo();
    
    char linha[250];
    int linha_atual = 0;
    do{
        fgets(linha, 250, arq);
        linha_atual++;
        
    }while(linha != NULL);

    fclose(arq);
}

int main() {
   
    int opcao = 0;
    while(opcao != 3) {
        Menu();
        scanf("%d", &opcao);

        if(opcao == 1) {
            CriaIndice();
        }
    }

   return 0;
}