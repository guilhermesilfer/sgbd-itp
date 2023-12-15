#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>

#include "minorfunctions.h"

//Cria uma tabela e insere informações
void criar_tabela() {
    char nome[51];
    char nome_tratado[51];
    char caminho_tabelas[59] = "Tabelas/";
 
    printf("Digite o nome da tabela: \n");
    scanf("%50[^\n]", nome);

    if(strlen(nome) > 50) {
        printf("O nome deve ter ate 50 caracteres");
        return;
    }

    tratar_nome(nome, nome_tratado);

    strcat(caminho_tabelas, nome_tratado);
    strcat(caminho_tabelas, ".txt");

    getchar();

    FILE* tabela;
    tabela = fopen(caminho_tabelas, "w+");

    if (tabela == NULL) {
        printf("\nErro ao abrir o arquivo: %s\n", strerror(errno));
        return;
    }
    else {
        printf("\nSucesso ao abrir o arquivo\n\n");
        char chavep[21];
        int cols = 1;
        int stop = false;

        printf("Quantas colunas existirao na tabela?\n");
        scanf("%d", &cols);
        printf("\n%d\n", cols);

        for(int i = 0; i < cols; i++) {
            printf("Qual o nome da coluna que sera a chave primaria:\n");
            while(stop == false) {
                fgets(chavep, sizeof(chavep), stdin);
                //scanf("%[^\n]", chavep);
                chavep[strcspn(chavep, "\n")] = '\0';
                if(chavep[0] != '\0') {
                    stop = true;
                }
            }
            printf("chegou aqui\n");
        }
        //fputs(chavep, tabela);
        //fputs("\n", tabela);
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

    return;
}

//Lista todas as tabelas existentes
void listar_tabelas() {
    FILE *lista;
    lista = fopen("Tabelas/lista.txt", "r");
    if (lista == NULL) {
        printf("Não existem tabelas a serem exibidas no momento. (%s)\n", strerror(errno));
        return;
    }

    char line[51];
    int i = 1;
    char *result;
    while (!feof(lista)) {
        result = fgets(line, 51, lista);
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
    char line2[51];
    i = 1;
    char *result2;

    while (!feof(lista)) {
        result2 = fgets(line2, 51, lista);
        if(result2) {
            printf("\nTABELA %d: %s", i, line2);
            printf("------------------------");
            i++;
        }
    }
    fclose(lista);
    return;
}

//Cria um registro/linha na tabela escolhida
void criar_linha_tabela() {
    char nome[51];
    char nome_tratado[51];
    char caminho_tabelas[59] = "Tabelas/";
    char *result;
    char line[51];

    printf("Lista de tabelas disponiveis:\n");
    listar_tabelas();
    printf("\nDigite o nome da tabela em que deseja criar uma nova linha: \n");
    scanf(" %[^\n]", &nome);
    if(strlen(nome) > 50) {
        printf("O nome deve ter ate de 50 caracteres");
        return;
    }
    tratar_nome(nome, nome_tratado);
    strcat(caminho_tabelas, nome_tratado);
    strcat(caminho_tabelas, ".txt");

    FILE* tabela = fopen(caminho_tabelas, "r+");
    if (tabela == NULL) {
        printf("\nErro ao abrir o arquivo: %s\n", strerror(errno));
        return;
    }
    if(tabela){
        char line[51];
        char dado[5];
        fgets(line, 51, tabela);
    while(!feof(tabela)){
        result = fgets(line, 51, tabela);
        if(!result){
            printf("\nDigite: %s", line);
            scanf(" %[^\n]", &dado);
            strcat(dado, "\n");
            fputs(dado, tabela);
            fclose(tabela);
            break;
        }
    }
    return;
    }
    else{
        printf("Essa tabela nao existe!\n");
        return;
    }
    
}

//Lista todos os dados de uma tabela
void listar_dados_tabela(){
    char nome[51];
    char nome_tratado[51];
    char caminho_tabelas[59] = "Tabelas/";
    char *result;
    char line[51];

    printf("Digite o nome da tabela que deseja ver:\n");
    scanf(" %[^\n]", &nome);
    tratar_nome(nome, nome_tratado);
    strcat(nome_tratado, ".txt");
    strcat(caminho_tabelas, nome_tratado);

    FILE* tabela = fopen(caminho_tabelas, "r");

    if(tabela) {
        result = fgets(line, 51, tabela);
        printf("%s", line);
        fgets(line, 51, tabela);
        while(!feof(tabela)){
            result = fgets(line, 51, tabela);
            if(result){
                printf("%s", line);
            }
        }
        return;
    }
    else{
        printf("Essa tabela não existe!\n%s", strerror(errno));
        return;
    }
}

//Pesquisar valor em uma tabela


//Apagar linha em uma tabela
void apagar_linha(){
    char nome[51];
    char nome_tratado[51];
    char caminho_tabelas[59] = "Tabelas/";
    
    printf("Tabelas diponiveis:\n");
    listar_tabelas();
    printf("Digite o nome da tabela em que deseja excluir um registro:\n");
    scanf(" %[^\n]", &nome);
    tratar_nome(nome, nome_tratado);
    strcat(nome_tratado, ".txt");
    strcat(caminho_tabelas, nome_tratado);
    
    FILE* tabela = fopen(caminho_tabelas, "r");

    if(tabela){
        FILE* tabelarecebe = fopen("Tabelas/tabelarecebe.txt", "w");
        char line[1000];
        char *result;
        while(!feof(tabela)){
            result = fgets(line, 1000, tabela);
            if(result) fputs(line, tabelarecebe);
        }
        fclose(tabelarecebe);
        fclose(tabela);

        tabela = fopen(caminho_tabelas, "r");
        tabelarecebe = fopen("Tabelas/tabelarecebe.txt", "r");
        FILE* tabelateste = fopen("Tabelas/tabelateste.txt", "w");

        char line[1000] = "";
        char *result2;
        char line2[1000] = "";
        char linha[1000];
        char chavep[] = "";
        printf("Digite a chave primaria da linha que deseja excluir:\n");
        scanf(" %[^\n]", &chavep);

        while(!feof(tabela)){
            result = fgets(line, strlen(chavep), tabela);
            if(result && line != chavep){
                result2 = fgets(line2, 1000, tabelarecebe);
                fputs(line2, tabelateste);
            }
            fgets(linha, 1000, tabela);
        }
        fclose(tabela);
        fclose(tabelarecebe);
        fclose(tabelateste);
        remove(tabelarecebe);
        tabela = fopen(caminho_tabelas, "w");
        tabelateste = fopen("Tabelas/tabelateste.txt", "r");

        char line[1000] = "";
        char *result3;
        while(!feof(tabelateste)){
            result3 = fgets(line, 1000, tabelateste);
            if(result3) fputs(line, tabela);
        }
        fclose(tabela);
        fclose(tabelateste);
        remove(tabelateste);
        return;
    }
    else{
        printf("Essa tabela não existe!\n%s",strerror(errno));
        return;
    }
}

//Apagar uma tabela
void apagar_tabela(){
    char nome[51];
    char nome_tratado[51];
    char caminho_tabelas[59] = "Tabelas/";
    char line[51];
    char *result;

    FILE *lista;

    lista = fopen("Tabelas/lista.txt", "r");
    
    if(lista == NULL) {
        printf("Nao existem tabelas a serem exibidas no momento. (%s)\n", strerror(errno));
        return;
        exit(1);
    }

    while (!feof(lista)) {
        result = fgets(line, 51, lista);
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
        result = fgets(line, 51, lista);
        if(result) {
            if(strcmp(nome, line)==0) {
                strcat(nome_tratado, ".txt");
                strcat(caminho_tabelas, nome_tratado);
                remove(caminho_tabelas);
                i = 0;
            }
            else {
                fputs(line, lista_teste);
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
