#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "lista.h"
#include "palavra.h"
#include "arq.h"

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
            if(ExisteNaLista(lista_palavras, palavra, linha_atual) == 0) {
                PALAVRA *nova_palavra = CriaNovaPlavra(palavra, linha_atual);
                lista_palavras = InsereEmOrdemAlfabetica(lista_palavras, nova_palavra);
                free(nova_palavra);
            }

            palavra = strtok(NULL, " ");
        }
        
    }

    fclose(arq);
}

void GeraIndiceDat() {
    FILE *arq;
    arq = fopen("indice.dat", "wb");
    int ctPalavras = QtdPalavras(lista_palavras);
    LISTA *aux = lista_palavras->prox;
    fwrite(&ctPalavras, sizeof(int), 1, arq);
    while(aux != lista_palavras) {
        int tamanho = strlen(aux->palavra.letras) + 1;
        fwrite(&tamanho, sizeof(int), 1, arq);
        fwrite(&aux->palavra.letras, sizeof(char), tamanho, arq);
        fwrite(&aux->palavra.qtdOcorrencias, sizeof(int), 1, arq);
        fwrite(aux->palavra.linhas, sizeof(int), aux->palavra.qtdOcorrencias, arq);

        aux = aux->prox;
    }

    fclose(arq);
}

void LerArquivoDat() {
    FILE *arq = AbreArquivoDat();
    int ctPalavras, qtdCaracter, qtdOcorrencias;

    lista_palavras = CriaLista();

    fread(&ctPalavras, sizeof(int), 1, arq);
    printf("Quantidade de palavras: %d\n", ctPalavras);

    while(fread(&qtdCaracter, sizeof(int), 1, arq) > 0){
        char palavra[50];
        printf(" --------------------------------- \n");
        fread(palavra, sizeof(char), qtdCaracter, arq);
        fread(&qtdOcorrencias, sizeof(int), 1, arq);
        printf("Quantidade de caracteres: %d\n", qtdCaracter);
        printf("Palavra: %s\n", palavra);
        printf("Quantidade de ocorrencia: %d\n", qtdOcorrencias);
        int *linhas = (int *) malloc (qtdOcorrencias*sizeof(int));
        printf("Linhas: ");
        for(int i = 0; i < qtdOcorrencias; i++) {
            fread(&linhas[i], sizeof(int), 1, arq);
            printf(" - %d", linhas[i]);
        }
        printf("\n");

        PALAVRA *nova_palavra = CriaNovaPlavra(palavra, linhas[0]);
        
        if(qtdOcorrencias > 1) {
            insereLinhas(nova_palavra, linhas, qtdOcorrencias);
        }
        free(linhas);        
        lista_palavras = InsereEmOrdemAlfabetica(lista_palavras, nova_palavra);
    }
    printf(" --------------------------------- \n");

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
            GeraIndiceDat();
            printf("\n ---------- INDICE CRIADO ----------\n");
        }else if(opcao == 2) {
            if(lista_palavras != NULL) {
                printf("entrou\n");
                lista_palavras = DestruirLista(lista_palavras);
            }
            
            LerArquivoDat();

            char palavra[50];
            printf("Digite a palavra que deseja buscar: ");
            scanf("%s",palavra);
            printf("\n");
            BuscaPalavra(lista_palavras, palavra);
        }else if(opcao == 3) {
            lista_palavras = DestruirLista(lista_palavras);
            printf(" ---------- LISTA DESTRUIDA ----------\n");
        }else if(opcao == 4) {
            ImprimeLista(lista_palavras);
        }

        printf("\n");
        system("pause");
        system("cls");
    }

    printf(" ---------- SAIU DO PROGRAMA ----------\n");
    return 0;

}
