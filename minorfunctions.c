#include <ctype.h>
#include <stdio.h>

int tratar_nome(char *nome, char *nome_tratado){
    int i, j=0;
    int contador = 0;

    for (i = 0; i < 51; i++) {
        if(nome[i] == '\0' || nome[i] == '\n') {
            break;
        }

        if(nome[i] != 92 && nome[i] != 47 && nome[i] != 58 && nome[i] != 42 && nome[i] != 63
        && nome[i] != 34 && nome[i] != 60 && nome[i] != 62 && nome[i] != 124) {
            nome_tratado[j] = nome[i];
            j++;
        }
        else{
            contador++;
        }
        if(nome[i] = '\0') return contador;
    }

    for(int i = 0; nome_tratado[i]; i++) {
        nome_tratado[i] = tolower(nome_tratado[i]);
    }
}