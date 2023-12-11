#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "minorfunctions.h"

//Caso 1 do Menu (Criar uma tabela)
void criar_tabela() {
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

    FILE* tabela;
    tabela = fopen(caminho_tabelas, "w");

    if (tabela == NULL) {
        printf("\nErro ao abrir o arquivo: %s\n", strerror(errno));
        return;
    }
    else {
        printf("\nSucesso ao abrir o arquivo");
    }

    if (fclose(tabela) != 0) {
        printf("\nErro ao fechar o arquivo: %s\n", strerror(errno));
    }
    else {
        printf("\nSucesso ao fechar o arquivo\n");
    }

    FILE* lista_de_tabelas;
    lista_de_tabelas = fopen("Tabelas/lista.txt", "a");
    strcat(nome, "\n");
    fprintf(lista_de_tabelas, nome);
    fclose(lista_de_tabelas);
}

//Caso 2 do Menu (Listar todas as tabelas)
void listar_tabelas() {
    FILE *lista;
    lista = fopen("Tabelas/lista.txt", "r");
    if (lista == NULL) {
        printf("Não existem tabelas a serem exibidas no momento. (%s)\n", strerror(errno));
        return;
    }
    char Linha[51];
    int i = 1;
    char *result;
    while (!feof(lista)) {
        result = fgets(Linha, 51, lista);
        if(result) {
            break;
        }
        else {
            printf("Nao existem tabelas a serem exibidas no momento.\n");
            fclose(lista);
            return;
        }
    }

    fclose(lista);
    lista = fopen("Tabelas/lista.txt", "r");
    char Linha2[51];
    i = 1;
    char *result2;

    while (!feof(lista)) {
        result2 = fgets(Linha2, 51, lista);
        if(result2) {
            printf("\nTABELA %d: %s", i, Linha2);
            printf("------------------------");
            i++;
        }
    }
    fclose(lista);
    return;
}

//Caso 3 do Menu (Criar uma lista ou registro em uma tabela)
void criar_linha_tabela() {
    
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
            printf("Nao existem tabelas a serem exibidas no momento.\n");
            return;
        }
    }
    fclose(lista);

    lista = fopen("Tabelas/lista.txt", "r");
    FILE* lista_teste = fopen("Tabelas/listateste.txt", "w");

    printf("Lista de Tabelas Disponiveis:\n");
    listar_tabelas();
    printf("\nDigite apenas o nome da tabela que deseja excluir: \n");
    scanf(" %[^\n]", nome);
    tratar_nome(nome, nome_tratado);
    strcat(nome, "\n");

    int i = 1;
    while (!feof(lista)) {
        result = fgets(Linha, 51, lista);
        if(result) {
            if(strcmp(nome, Linha)==0) {
                strcat(nome_tratado, ".txt");
                strcat(caminho_tabelas, nome_tratado);
                remove(caminho_tabelas);
                i = 0;
            }
            else {
                fputs(Linha, lista_teste);
            }
        }
    }
    if(i == 0) {
        fclose(lista_teste);
    fclose(lista);
    lista_teste = fopen("Tabelas/listateste.txt", "r");
    lista = fopen("Tabelas/lista.txt", "w");

    char Line[51];
    char *resut;
    while (!feof(lista_teste)) {
        resut = fgets(Line, 51, lista_teste);
        if(resut) {
            fputs(Line, lista);
        }
    }
    fclose(lista);
    fclose(lista_teste);
    remove("Tabelas/listateste.txt");
    printf("\nNova Lista de Tabelas:\n");
    listar_tabelas();
    return;
    }
    else {
        fclose(lista);
        fclose(lista_teste);
        printf("Essa tabela nao existe!\n");
        return;
    }
}
