#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

#define MAX_COLUNAS 30
#define TAM_LINHA 2048
#define TAM_AUTOR 501

int main() {
    FILE *arquivo = fopen("C:/Universidade/TrabalhoDeLincoln/EmendasParlamentaresFML/EmendasParlamentaresFML/EmendasParlamentares_PorFavorecido.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo csv!\n");
        return 1;
    }

    char linha[TAM_LINHA];
    char *colunas[MAX_COLUNAS];
    char autorMaior[TAM_AUTOR] = "";
    char autorMenor[TAM_AUTOR] = "";
    double maiorValor = -DBL_MAX;
    double menorValor = DBL_MAX;
    int primeira = 1;

    fgets(linha, sizeof(linha), arquivo); // ignora cabecalho

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int i = 0;
        char *token = strtok(linha, ";\n");

        while (token != NULL && i < MAX_COLUNAS) {
            // remove aspas do inicio/fim do campo, se existirem
            if (*token == '\"') {
                token++;
                char *p = strchr(token, '\"');
                if (p != NULL) {
                    *p = '\0';
                }
            }
            colunas[i] = token;
            i++;
            token = strtok(NULL, ";\n");
        }

        // pula linhas mal formadas (sem colunas suficientes)
        if (i <= 12) {
            continue;
        }

        // 10 - estado
        // 12 - valor com virgula
        char *virgula = strchr(colunas[12], ',');
        if (virgula != NULL) {
            *virgula = '.';
        }
        double valor = strtod(colunas[12], NULL);

        if (primeira) {
            maiorValor = menorValor = valor;
            strncpy(autorMaior, colunas[2], TAM_AUTOR - 1);
            strncpy(autorMenor, colunas[2], TAM_AUTOR - 1);
            primeira = 0;
        }

        if (valor > maiorValor) {
            maiorValor = valor;
            strncpy(autorMaior, colunas[2], TAM_AUTOR - 1);
            autorMaior[TAM_AUTOR - 1] = '\0';
        }
        if (valor < menorValor) {
            menorValor = valor;
            strncpy(autorMenor, colunas[2], TAM_AUTOR - 1);
            autorMenor[TAM_AUTOR - 1] = '\0';
        }
    }

    printf("%s eh o autor da maior emenda de R$ %.2lf\n", autorMaior, maiorValor);
    printf("%s eh o autor da menor emenda de R$ %.2lf\n", autorMenor, menorValor);

    fclose(arquivo);
    return 0;
}
/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    FILE *arquivo = fopen("C:/Universidade/TrabalhoDeLincoln/EmendasParlamentaresFML/EmendasParlamentaresFML/EmendasParlamentares.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo csv!\n");
        return 1;
    }

    char linha[2048];     
    char *colunas[25];
    char autorMaior[501];
    char autorMenor[501];
    double maiorValor = 0;
    double menorValor = 0;
    
    fgets(linha, sizeof(linha), arquivo); //ignora cabecalho

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int i = 0;

        char *token = strtok(linha, ";\n");

        while (token != NULL) {
            token++;
            char *p = strchr(token, '\"');
            *p = '\0';
            colunas[i] = token;
            i++;
            token = strtok(NULL, ";\n");
        }

        //colunas estao prontas
        //10 - estado
        //12 - valor com virgula
        
        char *p = strchr(colunas[12], ',');
        *p = '.';
        double valor = strtod(colunas[12], NULL);
        printf("%lf", valor);
        if (valor > maiorValor){
            maiorValor = valor;
            strcpy(autorMaior, colunas[2]);
            puts("A");
            //printf("%s eh o autor da maior emenda de R$ %.2lf\n", autor, maiorValor);
        }

        if (valor < menorValor){
            menorValor = valor;
            strcpy(autorMenor, colunas[2]);
            puts("B");
            //printf("%s eh o autor da maior emenda de R$ %.2lf\n", autor, menorValor);
        }
    }

    printf("%s eh o autor da maior emenda de R$ %.2lf\n", autorMaior, maiorValor);
    printf("%s eh o autor da menor emenda de R$ %.2lf\n", autorMenor, menorValor);

    fclose(arquivo);
    return 0;
}
    */