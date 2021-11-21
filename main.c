#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "palavra.h"
#include "arqtxt.h"

LISTA *lista_palavras;

void Menu () {
    printf("Escolha uma das opcoes abaixo:\n");
    printf("    1. Criar um indice para um arquivo texto\n");
    printf("    2. Utilizar um indice para realizar buscas por palavras\n");
    printf("    3. Encerrar o programa:\n");
    printf(">> ");
}

void CriaIndice() {
    FILE *arq = AbreArquivoTXT();
    
    char linha[250];
    int linha_atual = 0;

    while(fscanf(arq, " %[^\n]s", linha) > 0){
        linha_atual++;
        
        char *palavra = strtok(linha, " ");
        while( palavra != NULL) {
            printf("palavra atual: %s\n",palavra);
            if(ExisteNaLista(lista_palavras, palavra, linha_atual) == 0) {
                PALAVRA *nova_palavra = CriaNovaPlavra(palavra, linha_atual);
                lista_palavras = InsereEmOrdemAlfabetica(lista_palavras, nova_palavra);
            }

            palavra = strtok(NULL, " ");
        }
        
        
    }

    fclose(arq);
}

int main() {
   
    lista_palavras = CriaLista();

    int opcao = 0;
    while(opcao != 3) {
        Menu();
        scanf("%d", &opcao);

        if(opcao == 1) {
            CriaIndice();
        }else if(opcao == 2) {
            ImprimeLista(lista_palavras);
        }
    }

   return 0;
}