#include <stdio.h>

int main() {
    FILE *arquivoEntrada, *arquivoSaida;
    char nomeArquivoEntrada[100], nomeArquivoSaida[100];
    char caractere;

    // Obtém o nome do arquivo de entrada do usuário
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", nomeArquivoEntrada);

    // Obtém o nome do arquivo de saída do usuário
    printf("Digite o nome do arquivo de saída: ");
    scanf("%s", nomeArquivoSaida);

    // Abre o arquivo de entrada para leitura
    arquivoEntrada = fopen(nomeArquivoEntrada, "r");
    if (arquivoEntrada == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    // Abre o arquivo de saída para escrita
    arquivoSaida = fopen(nomeArquivoSaida, "w");
    if (arquivoSaida == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        fclose(arquivoEntrada);
        return 1;
    }

    // Lê caracteres do arquivo de entrada, remove espaços em branco e escreve no arquivo de saída
    while ((caractere = fgetc(arquivoEntrada)) != EOF) {
        if (caractere != ' ') {
            fputc(caractere, arquivoSaida);
        }
    }

    // Fecha os arquivos
    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    printf("Caracteres removidos com sucesso. Verifique o arquivo de saída.\n");

    return 0;
}
