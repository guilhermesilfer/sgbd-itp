#include <stdio.h>
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

    tratar_nome(nome, nome_tratado);
    
    printf("%s\n", nome); 
    printf("%s\n", nome_tratado);

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
    
    printf("Lista de Tabelas Disponíveis:\n");
    listar_tabelas();

    printf("Digite apenas o nome da tabela que deseja excluir: \n");
    scanf(" %[^\n]", nome);
    tratar_nome(nome, nome_tratado);

    FILE *lista;

    lista = fopen("Tabelas/lista.txt", "a");
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
            i++;
        }
    }
    fclose(lista);
}