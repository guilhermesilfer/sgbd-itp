#include <stdio.h>
#include <stdlib.h>

#include "database.h"

//imprime o menu e captura a ação escolhida
void menu(int op) {
    printf("\nSelecione um numero de 1 a 7 para prosseguir:\n\n");
    printf("1 - Criar uma tabela\n");
    printf("2 - Listar todas as tabelas\n");
    printf("3 - Criar uma nova linha na tabela\n");
    printf("4 - Listar todos os dados de uma tabela\n");
    printf("5 - Pesquisar valor em uma tabela\n");
    printf("6 - Apagar uma linha de uma taebla\n");
    printf("7 - Apagar uma tabela\n");
    
    scanf("%d", &op);

    switch (op){
    case 1:
        criar_tabela();
        break;

    case 2:
        break;

    case 3:
        break;

    case 4:
        break;

    case 5:
        break;

    case 6:
        break;
        
    case 7:
        break;
    
    default: printf("Por favor selecione uma das opcoes validas!");
        exit(1);
        break;
    }

    return;
}
