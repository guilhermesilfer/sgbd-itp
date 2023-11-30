#include <stdio.h>
#include <stdlib.h>

#include "menu.h"

int main(){
    int op;

	imprimir_menu();

    scanf("%d", &op);

    switch (op){
    case 1:
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

    return 0;
}