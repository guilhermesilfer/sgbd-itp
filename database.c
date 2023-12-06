#include <stdio.h>
#include <string.h>
#include <errno.h>

//Caso 1 do menu
void criar_tabela(){
    char nome[31];
    printf("Digite o nome da tabela: \n");
    scanf("%s", nome);
    //fgets(nome, 31, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    strcat(nome, ".txt");
    printf("%c", nome[4]);
    printf("%s", nome);


    FILE* tabela;
    tabela = fopen("exemplo.txt", "w");
    if (tabela == NULL) {
        printf("Error ao abrir o arquivo: %s\n", strerror(errno));
        return;
    }

    fprintf(tabela, "testando");
    int fcloseResult = 1;
    fcloseResult = fclose(tabela);

    printf("%d\n", fcloseResult);

    if(fcloseResult != 0) {
        printf("Erro ao fechar o arquivo: %s\n", strerror(errno));
    }
    else {
        printf("Sucesso ao fechar o arquivo");
    }

    return;
}

//Caso 2 do Menu
void listar_tabelas(){


}