#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "palavra.h"
#include "indice.h"
#include "ocorrencia.h"

/* GRUPO: DOUGLAS MARELI E YUNGUER DVORAK */

INDICE *Lista_indice;

void Menu () {
    printf("Escolha uma das opcoes abaixo:\n");
    printf("    1. Processar um (novo) arquivo texto\n");
    printf("    2. Salvar um índice atual\n");
    printf("    3. Ler um arquivo de índice\n");
    printf("    4. Mostrar as informações de um índice\n");
    printf("    5. Encerrar o programa\n");
    printf(">> ");
}

void ProcessarArquivo() {
    printf("Digite o nome do arquivo: \n");
    char nome[20];
    scanf("%s", nome);

    int existe = verificarExistenciaArq(Lista_indice->arquivos, nome);
    if(existe) {
        printf("\n ----- Esse arquivo já foi processado -----\n");
        return;
    }

    InsereFimArq(Lista_indice->arquivos, nome);
    Lista_indice->qtdArquivos++;
    
    FILE *arq = AbreArquivoTXT(nome);
    char linha[250];
    int linha_atual = 0;

    while(fscanf(arq, " %[^\n]s", linha) > 0){
        linha_atual++;
       
        char *palavra = strtok(linha, " ");
        while( palavra != NULL) {
            if(ExisteNaLista(Lista_indice->palavras, palavra, Lista_indice->qtdArquivos, linha_atual) == 0) {
                InsereEmOrdemAlfabetica(Lista_indice->palavras, palavra, Lista_indice->qtdArquivos, linha_atual);
            }

            palavra = strtok(NULL, " ");
        }
        
    }
    
    fclose(arq);
}

/*void LerArquivoDat() {
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
*/
int main() {
    
    //lista_palavras = CriaLista();
    Lista_indice = CriaListaIndice();
    int opcao = 0;
    while(opcao != 5) {

        Menu();
        scanf("%d", &opcao);

        if(opcao == 1) {
            ProcessarArquivo();
            printf("\n ---------- INDICE CRIADO ----------\n");
        }else if(opcao == 2) {
            SalvarIndiceAtual(Lista_indice);
            printf("\n ---------- INDICE SALVO ----------\n");
        }else if(opcao == 3) {
            if(Lista_indice != NULL) {
                Lista_indice = DestruirListaIndice(Lista_indice);
            }
            if(Lista_indice == NULL) {
                printf("\n ---------- INDICE DESTRUIDO ----------\n");
            }
            /*if(lista_palavras != NULL) {
                lista_palavras = DestruirLista(lista_palavras);
            }
            
            LerArquivoDat();

            char palavra[50];
            printf("Digite a palavra que deseja buscar: ");
            scanf("%s",palavra);
            printf("\n");
            BuscaPalavra(lista_palavras, palavra);*/
            //lista_palavras = DestruirLista(lista_palavras);
        }

        printf("\n");
        system("pause");
        system("cls");
    }
    
    printf(" ---------- SAIU DO PROGRAMA ----------\n");
    return 0;

}
