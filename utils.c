#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_newline_from_string(char* str) {
    if (str[strlen(str) - 1] =='\n') {
        str[strlen(str) - 1] = '\0';
    }
}

//Imprime a tabela
void print_table(int num, int cols) {
    FILE* Table = fopen("tabelas/tabela.csv", "r");
    char buffer[1000];

    if(num == 0) {
        while(fgets(buffer, 1000, Table)) {
            remove_newline_from_string(buffer);
            char* token = strtok(buffer, ",\n");

            while(token != NULL) {
                printf("%s", token);
                token = strtok(NULL, ",\n"); //must be the last command of this while()
                if (token == NULL) printf("\n");
                else printf(" | ");
            }
        }
    }
    else if(num == 1) {
    }

    fclose(Table);
}

//Usuário seleciona o tipo da coluna
void select_type(FILE* Table) {
    char buffer[1000];
    int num = 0;
    while(fgets(buffer, 1000, Table)) {
        remove_newline_from_string(buffer);
        char* token = strtok(buffer, ",\n");
        printf("Buffer: %s\nToken: %s\n", buffer, token);
        while(token != NULL) {
            printf("entrou\n");
            printf("Qual o tipo dessa coluna?: %s\n", token);
            printf("1 - char\n2 - int\n3 - float\n4 - double\n");
            while(num != 1 || num != 2 || num != 3 || num != 4) {
                scanf("%d", num);
                if(num != 1 && num != 2 && num != 3 && num != 4)
                    printf("Digite um numero que corresponda ao tipo\n");
            }
            fprintf(Table, "%d,", num);
            token = strtok(NULL, ",\n"); //must be the last command of this while()
            if (token == NULL) printf("\n");
        }
    }
}

char find_type(int num) {

}

//Essa função trata o nome dado pelo usuário para o arquivo da tabela
void tratar_nome(char *nome, char *nome_tratado){
    int i, j=0;

    for (i = 0; i < 51; i++) {
        if(nome[i] == '\0' || nome[i] == '\n') {
            nome_tratado[j] = '\0';
            break;
        }

        if(nome[i] != 92 && nome[i] != 47 && nome[i] != 58 && nome[i] != 42 && nome[i] != 63
        && nome[i] != 34 && nome[i] != 60 && nome[i] != 62 && nome[i] != 124) {
            nome_tratado[j] = nome[i];
            j++;
        }
    }

    for(i = 0; i < j; i++){
        if(nome_tratado[i] == '\0') {
            break;
        }
        if(nome_tratado[i] >= 65 && nome_tratado[i] <= 90){
            nome_tratado[i] = (nome_tratado[i] + 32);
        }
    }
    strcat(nome_tratado, ".csv");
}
