#include <stdio.h>
#include <string.h>

#include "minorfunctions.h"

int main() {
    char table_name[51];
    char filename[51];
    char filepath[59] = "tabelas/";
    
    //Pega o nome da tabela
    printf("Digite o nome da tabela:\n");
    scanf("%50[^\n]", table_name);

    //Trata table_name em filename criando o nome do arquivo
    tratar_nome(table_name, filename);
    strcat(filepath, filename);
    printf("\ntable_name: %s |", table_name);
    printf(" csv: %s |", filename);
    printf(" filepath: %s\n\n", filepath);

    //Início da criação do arquivo da tabela
    FILE* Table;
    Table = fopen(filepath, "w+");

    //Checagem da abertura do arquivo
    if(Table == NULL) {
        printf("Erro na criacao do arquivo\n\n");
        return -1;
    }
    else {
        printf("Sucesso na criacao do arquivo\n\n");
    }

    //Início da impressao da data
    int cols = 0;
    printf("Quantas colunas existirao na tabela:\n");
    scanf("%d", &cols);

    //Escreve os nomes das colunas
    printf("======== Escreva a seguir os nomes das colunas ========\n");
    for(int i = 0; i < cols; i++) {
        if(i == 0)
            printf("Digite a coluna que sera a chave primaria (Deve ser do tipo inteiro sem sinal):\n");
        if(i == 1)
            printf("Digite as outras colunas:\n");
        char col_name[21] = "";
        scanf("%s", col_name);
        fprintf(Table, "%s", col_name);
        (i == cols - 1) ? fprintf(Table, "\n") : fprintf(Table, ",");
    }

    //Escreve os tipos das colunas
    //for(int i = 0; i < cols; i++) {

    //}

    print_table(filepath, &cols);

    if(fclose(Table) != 0) {
        printf("Erro ao fechar o arquivo\n");
        return -1;
    }
    else {
        printf("Sucesso ao fechar o arquivo\n");
        return 0;
    }
    //Fim da criação do arquivo da tabela
}