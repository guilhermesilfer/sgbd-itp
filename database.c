#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>

#include "utils.h"

//Cria uma tabela e insere informações
void criar_tabela() {
    char table_name[51];
    char filename[51];
    char filepath[59] = "tabelas/";
    
    //Pega o nome da tabela
    printf("Digite o nome da tabela:\n");
    fflush(stdin);
    scanf("%[^\n]s", table_name);
    printf("%s", table_name);

    //Trata table_name em filename criando o nome do arquivo
    tratar_nome(table_name, filename); //TODO use english names only!
    strcat(filepath, filename);
    printf("\ntable_name: %s |", table_name);
    printf(" csv: %s |", filename);
    printf(" filepath: %s\n\n", filepath);

    //Início da impressao dos dados
    int cols = 0;
    printf("Quantas colunas existirao na tabela:\n");
    scanf("%d", &cols);

    char col_names[cols][15];
    int col_types[cols];

    //Leitura das colunas
    printf("======== Escreva a seguir os nomes das colunas ========\n");
    for(int i = 0; i < cols; i++) {
        if(i == 0)
            printf("Digite a coluna que sera a chave primaria (Deve ser do tipo inteiro sem sinal):\n");
        if(i == 1)
            printf("Digite as outras colunas:\n");
        scanf("%s", col_names[i]);
    }

    //Leitura dos tipos
    for(int i = 0; i < cols; i++) {
        printf("Digite o numero do tipo dessa coluna: %s\n", col_names[i]);
        printf("1 - char | 2 - int | 3 - float | 4 - double\n");
        int choice = 0;
        while(true) {
            scanf("%d", &choice);
            if(choice != 1 && choice != 2 && choice != 3 && choice != 4) {
                printf("Digite um numero que corresponda a um tipo\n");
            } else {
                break;
            }
        }
        col_types[i] = choice;
    }

    //Início da criação do arquivo da tabela
    FILE* Table;
    Table = fopen(filepath, "w");

    //Checagem da abertura do arquivo
    if(Table == NULL) {
        printf("Erro na criacao do arquivo\n\n");
        return;
    }
    else {
        printf("Sucesso na criacao do arquivo\n\n");
    }

    //Escrever dados
    for(int i = 0; i < cols; i++) {
        fprintf(Table, "%s", col_names[i]);
        (i == cols - 1) ? fprintf(Table, "\n") : fprintf(Table, ",");
    }
    for(int i = 0; i < cols; i++) {
        fprintf(Table, "%d", col_types[i]);
        (i == cols - 1) ? fprintf(Table, "\n") : fprintf(Table, ",");
    }

    //Fechamento do arquivo
    if(fclose(Table) != 0) {
        printf("Erro ao fechar o arquivo\n");
        return;
    }
    else {
        printf("Sucesso ao fechar o arquivo\n");
    }

    //Abertura da lista de tabelas
    FILE* lista_de_tabelas;
    lista_de_tabelas = fopen("tabelas/lista.txt", "a");
    strcat(table_name, "\n");
    fprintf(lista_de_tabelas, table_name);

    //Fechamento da lista de tabelas
    fclose(lista_de_tabelas);

    return;
}

//Lista todas as tabelas existentes
void listar_tabelas() {
    FILE *lista;
    lista = fopen("tabelas/lista.txt", "r");
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
            printf("\n[%d]: %s", i, line2);
            printf("------------------------");
            i++;
        }
    }
    fclose(lista);
    return;
}

//Cria um registro/linha na tabela escolhida
void criar_linha_tabela() {
    printf("Digite o nome da tabela que deseja criar uma nova linha:");
    printf("Lista de tabelas:");
    listar_tabelas();
    
    char name[51] = "";
    fflush(stdin);
    printf("\n");
    scanf("%[^\n]s", name);

    
    char filepath[59] = "tabelas/";
    strcat(name, ".csv");
    strcat(filepath, name);

    FILE* Table = fopen(filepath, "r");
    
    char buffer[1000] = "";

    int cols = count_cols(filepath);
    char data[cols][15];

    fgets(buffer, 1000, Table);
    fclose(Table);
    printf("\n%s\n", buffer);

    printf("Digite as informacoes da linha em cada coluna\n\n");
    int counter = 0;
    for(int i = 0; i < strlen(buffer); i++) {
        if(buffer[i] != ',' && i != strlen(buffer) - 1)
            printf("%c", buffer[i]);
        else if (i == strlen(buffer) - 1) {
            printf(": ");
            scanf("%s", data[counter]);
            counter++;
        }
        else {
            printf(": ");
            scanf("%s", data[counter]);
            counter++;
        }
        if(counter == cols) break;
    }

    fflush(stdin);

    Table = fopen(filepath, "a");

    //fprintf(Table, "Jesus");


    for(int i = 0; i < cols; i++) {
        fprintf(Table, data[i]);
        (i == cols - 1) ? fprintf(Table, "\n") : fprintf(Table, ",");
    }

    //for(int i = 0; i < cols; i++) {
    //    fprintf(Table, "%s", col_names[i]);
    //    (i == cols - 1) ? fprintf(Table, "\n") : fprintf(Table, ",");
    //}

    fclose(Table);
//======================================================================================
    //char nome[51];
    //char nome_tratado[51];
    //char caminho_tabelas[59] = "tabelas/";
    //char *result;
    //char line[51];

    //printf("Lista de tabelas disponiveis:\n");
    //listar_tabelas();
    //printf("\nDigite o nome da tabela em que deseja criar uma nova linha: \n");
    //scanf(" %[^\n]", &nome);
    //if(strlen(nome) > 50) {
    //    printf("O nome deve ter ate de 50 caracteres");
    //    return;
    //}
    //tratar_nome(nome, nome_tratado);
    //strcat(caminho_tabelas, nome_tratado);

    //FILE* tabela = fopen(caminho_tabelas, "r+");
    //if (tabela == NULL) {
    //    printf("\nErro ao abrir o arquivo: %s\n", strerror(errno));
    //    return;
    //}
    //if(tabela){
    //    char line[51];
    //    char dado[5];
    //    fgets(line, 51, tabela);
    //while(!feof(tabela)){
    //    result = fgets(line, 51, tabela);
    //    if(!result){
    //        printf("\nDigite: %s", line);
    //        scanf(" %[^\n]", &dado);
    //        strcat(dado, "\n");
    //        fputs(dado, tabela);
    //        fclose(tabela);
    //        break;
    //    }
    //}
    //return;
    //}
    //else{
    //    printf("Essa tabela nao existe!\n");
    //    return;
    //}
    
}

//Lista todos os dados de uma tabela
void listar_dados_tabela(){
    char table_name[51];
    char filename[51];
    char filepath[59] = "tabelas/";
    //char *result;
    //char line[51];
    listar_tabelas();
    printf("Digite o nome da tabela que deseja ver:\n");
    scanf(" %[^\n]s", table_name);
    tratar_nome(table_name, filename);
    strcat(filepath, filename);

    FILE* tabela = fopen(filepath, "r");
    if(tabela){
        fclose(tabela);
        int cols;
        cols = count_cols(filepath);
        print_table(filepath, cols);
    }
    else {
        printf("Essa tabela nao exite! %s\n", strerror(errno));
        return;
    }
}

//Pesquisar valor em uma tabela
void pesquisar_valor(){
    char table_name[51];
    char filename[51];
    char filepath[59] = "tabelas/";

    printf("Digite o nome da tabela em que deseja procurar um valor:\n");
    scanf("%s", &table_name);
    tratar_nome(table_name, filename);
    strcat(filepath, filename);

    FILE* Table = fopen(filepath, "r");
    if(Table){
        char line[1000];
        char coluna, valor;
        int tipo;
        printf("Colunas disponíveis:\n");
        fgets(line, 1000, Table);
        printf("%s\n", line);
        fclose(Table);
        Table = fopen(filepath, "r");

        printf("\nDigite o nome da coluna em que deseja pesquisar por um valor:\n");
        scanf("%[^\n]s", &coluna);
        printf("Digite o valor que deseja buscar na coluna %s da tabela:\n", coluna);
        scanf("%[^\n]s", &valor);
        printf("Selecione uma das opcoes abaixo para prosseguir:\n");
        printf("[1] -> valores maior que o valor informado\n");
        printf("[2] -> valores maior ou igual que o valor informado\n");
        printf("[3] -> valores igual o valor informado\n");
        printf("[4] -> valores menor que o valor informado\n");
        printf("[5] -> valores menor ou igual que o valor informado\n");
        printf("[6] -> valores próximo ao valor informado\n");
        scanf("%d", &tipo);
        
        switch (tipo) {
        case 1:

            break;
        
        case 2:

            break;

        case 3:

            break;

        case 4:

            break;

        default:
            printf("Essa opcao nao existe!");
            return;
        }
    }
    else{
        printf("Essa tabela nao existe! %s\n", strerror(errno));
        return;
    }
}

//Apagar linha em uma tabela
void apagar_linha(){
    char table_name[51];
    char filename[51];
    char filepath[59] = "tabelas/";
    
    printf("Tabelas diponiveis:\n");
    listar_tabelas();
    printf("Digite o nome da tabela em que deseja excluir um registro:\n");
    scanf(" %[^\n]", &table_name);
    tratar_nome(table_name, filename);
    strcat(filepath, filename);
    
    FILE* tabela = fopen(filepath, "r");

    if(tabela){
        FILE* tabelarecebe = fopen("tabelas/tabelarecebe.csv", "w");
        char line[1000];
        char *result;
        while(!feof(tabela)){
            result = fgets(line, 1000, tabela);
            if(result) fputs(line, tabelarecebe);
        }
        fclose(tabelarecebe);
        fclose(tabela);

        tabela = fopen(filepath, "r");
        tabelarecebe = fopen("tabelas/tabelarecebe.csv", "r");
        FILE* tabelateste = fopen("tabelas/tabelateste.csv", "w");

        char *result2;
        char chavep[] = "";
        printf("Digite a chave primaria da linha que deseja excluir:\n");
        scanf(" %[^\n]", &chavep);

        while(!feof(tabela)){
            result = fgets(line, strlen(chavep), tabela);
            if(result && line != chavep){
                result2 = fgets(line, 1000, tabelarecebe);
                fputs(line, tabelateste);
            }
            fgets(line, 1000, tabela);
        }
        fclose(tabela);
        fclose(tabelarecebe);
        fclose(tabelateste);
        remove("tabelas/tabelarecebe.csv");
        tabela = fopen(filepath, "w");
        tabelateste = fopen("tabelas/tabelateste.csv", "r");

        char *result3;
        while(!feof(tabelateste)){
            result3 = fgets(line, 1000, tabelateste);
            if(result3) fputs(line, tabela);
        }
        fclose(tabela);
        fclose(tabelateste);
        remove("tabelas/tabelateste.csv");
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
    char caminho_tabelas[59] = "tabelas/";
    char line[51];
    char *result;

    FILE *lista;

    lista = fopen("tabelas/lista.txt", "r");
    
    if(lista == NULL) {
        printf("Nao existem tabelas a serem exibidas no momento. (%s)\n", strerror(errno));
        return;
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

    lista = fopen("tabelas/lista.txt", "r");
    FILE* lista_teste = fopen("tabelas/listateste.txt", "w");

    printf("Lista de tabelas Disponiveis:\n");
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
        lista_teste = fopen("tabelas/listateste.txt", "r");
        lista = fopen("tabelas/lista.txt", "w");

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
        remove("tabelas/listateste.txt");
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
