#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "palavra.h"
#include "indice.h"
#include "ocorrencia.h"

/* GRUPO: DOUGLAS MARELI E YUNGUER DVORAK */

INDICE *indice;

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

    int existe = verificarExistenciaArq(indice->arquivos, nome);
    if(existe) {
        printf("\n ----- Esse arquivo já foi processado -----\n");
        return;
    }

    InsereFimArq(indice->arquivos, nome);
    indice->qtdArquivos++;
    
    FILE *arq = AbreArquivoTXT(nome);
    char linha[250];
    int linha_atual = 0;

    while(fscanf(arq, " %[^\n]s", linha) > 0){
        linha_atual++;
       
        char *palavra = strtok(linha, " ");
        while( palavra != NULL) {
            if(ExisteNaLista(indice->palavras, palavra, indice->qtdArquivos, linha_atual) == 0) {
                indice->qtdPalavras++;
                InsereEmOrdemAlfabetica(indice->palavras, palavra, indice->qtdArquivos, linha_atual);
            }

            palavra = strtok(NULL, " ");
        }
        
    }
    
    fclose(arq);
}

void LerArquivoDat() {

    FILE *arq = AbreArquivoDat();
    int ctArquivos;
    int ctPalavras, qtdCaracter, qtdOcorrencias;

    indice = CriaIndice();

    fread(&ctArquivos, sizeof(int), 1, arq);
    indice->qtdArquivos = ctArquivos;
    printf("Quantidade de arquivos: %d\n", ctArquivos);

    char nomeArq[50];
    for(int i = 0; i < ctArquivos; i++) {
        fread(&qtdCaracter, sizeof(int), 1, arq);
        fread(nomeArq, sizeof(char), qtdCaracter, arq);
        printf("Quantidade de caracter: %d\n", qtdCaracter);
        printf("Nome: %s\n", nomeArq);
        InsereFimArq(indice->arquivos, nomeArq);
    }

    fread(&ctPalavras, sizeof(int), 1, arq);
    printf("Quantidade de palavras: %d\n", ctPalavras);
   for(int i = 0; i < ctPalavras; i++) {
        char palavra[50];
        fread(&qtdCaracter, sizeof(int), 1, arq);
        printf(" --------------------------------- \n");
        fread(palavra, sizeof(char), qtdCaracter, arq);
        palavra[qtdCaracter] = '\0';
        fread(&qtdOcorrencias, sizeof(int), 1, arq);
        printf("Quantidade de caracteres: %d\n", qtdCaracter);
        printf("Palavra: %s\n", palavra);
        printf("Quantidade de ocorrencia em arquivos: %d\n", qtdOcorrencias);

        PALAVRA *plvr = CriaPalavraDoArqDat(palavra, qtdOcorrencias);

        for(int i = 0; i < qtdOcorrencias; i++) {
            int num, qtdOcorrenciasNoArq;
            fread(&num, sizeof(int), 1, arq);
            fread(&qtdOcorrenciasNoArq, sizeof(int), 1, arq);
            int *linhas = (int *) malloc (qtdOcorrenciasNoArq*sizeof(int));

            printf("  Numero arquivo: %d\n", num);
            printf("  Quantidade de ocorrencia no arquivo: %d\n", qtdOcorrenciasNoArq);
            printf("  Linhas: ");
            for(int i = 0; i < qtdOcorrenciasNoArq; i++) {
                fread(&linhas[i], sizeof(int), 1, arq);
                printf(" - %d", linhas[i]);
            }
            OCORRENCIA *ocr = CriaOcorrenciaDoArqDat(num, qtdOcorrenciasNoArq, linhas);
            InsereOcorrenciaExistente(plvr->ocorrencias, ocr);
            printf("\n");
             free(linhas); 
        }
        printf("\n");
        InserePalavraNoFim(indice->palavras, plvr);
    }
    printf(" --------------------------------- \n");

    fclose(arq);
}

int main() {
    
    //lista_palavras = CriaLista();
    indice = CriaIndice();
    int opcao = 0;
    while(opcao != 5) {
    
        Menu();
        scanf("%d", &opcao);

        if(opcao == 1) {
            ProcessarArquivo();
            printf("\n ---------- INDICE CRIADO ----------\n");
            printf("qtd arq: %d\n", indice->qtdArquivos);
        }else if(opcao == 2) {

            SalvarIndiceAtual(indice);
            printf("\n ---------- INDICE SALVO ----------\n");

        }else if(opcao == 3) {

            if(indice != NULL) {
                indice = DestruirListaIndice(indice);
            }
            
            LerArquivoDat();

        }else if(opcao == 4) {
            ImprimeIndice(indice);
        }else if (opcao == 5) {
            if(indice != NULL) {
                indice = DestruirListaIndice(indice);
            }else {
                free(indice);
            }
            printf(" ----- Indice Destruida -----\n");
        }

        printf("\n");
        system("pause");
        system("cls");
    }
    
    printf(" ---------- SAIU DO PROGRAMA ----------\n\n");
    return 0;

}
