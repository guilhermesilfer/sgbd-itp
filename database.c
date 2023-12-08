#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "minorfunctions.h"

//Caso 1 do Menu (Criar uma tabela)
void criar_tabela(){
    char nome[51];
    char nome_tratado[51];
    char caminho_tabelas[59] = "Tabelas/";
 
    printf("Digite o nome da tabela: \n");
    scanf(" %[^\n]", nome);

    if(strlen(nome) > 50) {
        printf("O nome deve ter ate de 50 caracteres");
        return;
    }

    tratar_nome(nome, nome_tratado);

    strcat(caminho_tabelas, nome_tratado);
    strcat(caminho_tabelas, ".txt");

    FILE* lista_de_tabelas;
    lista_de_tabelas = fopen("Tabelas/lista.txt", "a");
    strcat(nome, "\n");
    fprintf(lista_de_tabelas, nome);
    fclose(lista_de_tabelas);

    FILE* tabela;
    tabela = fopen(caminho_tabelas, "w");

    if (tabela == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", strerror(errno));
        return;
    }

    fprintf(tabela, "testando");

    if (fclose(tabela) != 0) {
        printf("Erro ao fechar o arquivo: %s\n", strerror(errno));
    }
    else {
        printf("Sucesso ao fechar o arquivo\n");
    }
}

//Caso 2 do Menu (Listar todas as tabelas)
void listar_tabelas(){
    FILE *lista;

    lista = fopen("Tabelas/lista.txt", "r");
    if (lista == NULL) {
        printf("Não existem tabelas a serem exibidas no momento. (%s)\n", strerror(errno));
        return;
    }

    char Linha[51];
    char *result;
    int i = 1;
    while (!feof(lista)) {
        result = fgets(Linha, 51, lista);
        if(result) {
            printf("\nTABELA %d: %s", i, Linha);
            printf("-------------------------\n");
            i++;
        }
    }
    fclose(lista);
}

//Caso 3 do Menu (Criar uma lista ou registro em uma tabela)
void criar_linha_tabela(){
    
}

//Caso 7 do Menu (Apagar uma tabela)
void apagar_tabela(){
    char nome[51];
    char nome_tratado[51];
    char caminho_tabelas[59] = "Tabelas/";
    char Linha[51];
    char *result;


    FILE *lista;

    lista = fopen("Tabelas/lista.txt", "r");
    
    if(lista == NULL) {
        printf("Nao existem tabelas a serem exibidas no momento. (%s)\n", strerror(errno));
        return;
        exit(1);
    }

    while (!feof(lista)) {
        result = fgets(Linha, 51, lista);
        if(result) {
             break;
        }
        else {
            printf("Nao existem tabelas a serem exibidas no momento.");
            exit(2);
        }
    }
    fclose(lista);
    lista = fopen("Tabelas/lista.txt", "r");

    printf("Lista de Tabelas Disponiveis:\n");
    listar_tabelas();
    int i = 1, j;
    printf("\nDigite o numero da tabela que deseja excluir: \n");
    scanf("%d", j);

    while (!feof(lista)) {
        result = fgets(Linha, 51, lista);
        if(result) {
            i++;
        }
    }
    printf("%d\n", i);
    fclose(lista);

    lista = fopen("Tabelas/lista.txt", "a");

    if(j>i || j<1){
        printf("Essa tabela nao existe!");
        return;
    }
    else{
        for(i = 0; i<j;i++) {
        fgets(Linha, 51, lista);
        }
        printf("%s", Linha);
        fclose(lista);
    }

    

    /*tratar_nome(nome, nome_tratado);
    strcat(nome_tratado, ".txt");
    strcat(caminho_tabelas, nome_tratado);

    if((remove(caminho_tabelas) == 0)) {
        char nd[2] = "\n";
        
        
        fclose(lista);
        printf("\nNova Lista de Tabelas:\n");
        listar_tabelas();
        return;
    }
    else{
        printf("\nEssa tabela nao existe.\n");
        return;
    }*/

    return;
}