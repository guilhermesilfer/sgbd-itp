#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "minorfunctions.h"

//Caso 1 do menu
void criar_tabela(){
    char nome[51];
    nome[0] = '\0';
    char caminho_tabelas[59] = "Tabelas/";
    char nome_tratado[51];
 
    printf("Digite o nome da tabela: \n");
    scanf(" %[^\n]", nome);

    int contador = tratar_nome(nome, nome_tratado);
    int t_nome = strlen(nome);
    
    printf("%s\n", nome); 
    
    for(int i = 0; i < t_nome - contador; i++){
        printf("%c", nome_tratado[i]);
    }

    printf("%d\n", contador);

    strcat(caminho_tabelas, nome_tratado);
    strcat(caminho_tabelas, ".txt");

    FILE* lista_de_tabelas;
    lista_de_tabelas = fopen("Tabelas/lista.txt", "a");
    strcat(nome, "\n");
    fprintf(lista_de_tabelas, nome);
    fclose(lista_de_tabelas);

    FILE* tabela;
    tabela = fopen(pathFile, "w");

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

//Caso 2 do Menu
void listar_tabelas(){
    FILE* lista;
    lista = fopen("Tabelas/lista.txt", "r");
    
    while (fscanf(lista, "%s") != EOF) {

    }
}