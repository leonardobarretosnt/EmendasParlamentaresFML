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
    int QtdEmendas = 0;
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
        if (valor < menorValor && valor > 0) {
            menorValor = valor;
            strncpy(autorMenor, colunas[2], TAM_AUTOR - 1);
            autorMenor[TAM_AUTOR - 1] = '\0';

            
        }
        QtdEmendas++;
    }

    printf("%s eh o autor da maior emenda de R$ %.2lf\n", autorMaior, maiorValor);
    printf("%s eh o autor da menor emenda de R$ %.2lf\n", autorMenor, menorValor);
    printf("%d eh a quantidade total de emendas", QtdEmendas);

    fclose(arquivo);
    return 0;
}
