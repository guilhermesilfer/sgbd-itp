#include <stdio.h>
#include <string.h>
#include <errno.h>

//Caso 1 do menu
void criar_tabela(){
    char nome[31];
    nome[0] = '\0';

    printf("Digite o nome da tabela: \n");

    scanf(" %[^\n]", nome);

    strcat(nome, ".txt");

    printf("%s\n", nome);

    FILE* tabela;
    tabela = fopen(nome, "w");

    if (tabela == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", strerror(errno));
        return;
    }

    fprintf(tabela, "testando");

    if (fclose(tabela) != 0) {
        printf("Erro ao fechar o arquivo: %s\n", strerror(errno));
    } else {
        printf("Sucesso ao fechar o arquivo\n");
    }
}

//Caso 2 do Menu
void listar_tabelas(){


}