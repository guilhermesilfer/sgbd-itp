#include <stdio.h>
#include <string.h>
#include <errno.h>

void criar_tabela(){
    char nome[31];
    printf("Digite o nome da tabela: \n");
    fgets(nome, sizeof(nome), stdin);

    nome[strcspn(nome, "\n")] = '\0';

    printf("%s", nome);

    FILE* tabela;
    tabela = fopen("example.txt", "w");

    if(tabela == NULL){
        printf("Error: %s\n", strerror(errno));
        return;
    }

    fclose(tabela);
    if(fclose(tabela) != 0) {
        printf("Erro ao fechar o arquivo: %s\n", strerror(errno));
    }
    else {
        printf("Sucesso ao fechar o arquivo");
    }

    return;
}

void listar_tabelas(){


}