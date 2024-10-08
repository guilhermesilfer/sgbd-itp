#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void remove_newline_from_string(char* str) {
    if (str[strlen(str) - 1] =='\n') {
        str[strlen(str) - 1] = '\0';
    }
}

int count_cols(char* filepath) {
    FILE* Table = fopen(filepath, "r");
    if(Table == NULL) printf("in count_cols: Erro ao abrir o arquivo");
    char first_line[100] = "";
    fgets(first_line, 100, Table);
    
    int cols = 0;
    for(int i = 0; i < strlen(first_line); i++) {
        if(first_line[0] == '\0') return cols;
        if(first_line[i] == ',') {
            cols++;
        }
    }
    cols++;

    fclose(Table);

    return cols;
}

//Imprime a tabela
void print_table(char* filepath, int cols) {
    FILE* Table = fopen(filepath, "r");
    char buffer[1000];
    int count = 0;
    int second_line_detect = 1;
    int ok = true;

    printf("\n");

    while(fgets(buffer, 1000, Table)) {
        remove_newline_from_string(buffer);
        char* token = strtok(buffer, ",\n");
        while(token != NULL) {

            //Alinhamento
            int token_size = strlen(token);
            int space_amount = 15 - token_size;
            
            if(second_line_detect <= cols || second_line_detect > cols*2) {
                printf("%s", token);
                for(int i = 0; i < space_amount; i++) printf(" ");
                printf("|");
            }
            else if(ok == true) {
                for(int j = 0; j < cols; j++) printf("----------------");
                printf("\n");
                ok = false;
            }
            second_line_detect++;

            token = strtok(NULL, ",\n");
            if (token == NULL) printf("\n");
        }
    }

    fclose(Table);
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
