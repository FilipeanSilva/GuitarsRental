// FILIPE A. N. SILVA 21260367

#include"atualizaFicheiros.h"

void atualizaGuitarras(guitarra *gui) {
    int i;
    FILE *f;
    f = fopen(FicheiroGuitarras, "wt");
    if (f == NULL) {
        printf("Erro a abrir ficheiro guitarras!");
        return;
    } else {
        for (i = 0; i < gui[0].tam; i++) {
            fprintf(f, "%d\t%d\t%d\t%d\t%s", gui[i].id, gui[i].precoDia, gui[i].valor, gui[i].estado, gui[i].nome);
            if (i != ((gui[i].tam) - 1)) {
                fprintf(f, "\n");
            }
        }
    }

    fclose(f);
    free(gui);
    return;
}

void atualizaClientes(cliente *cli) {
    FILE *f;
    f = fopen(FicheiroClientes, "wt");
    if (f == NULL) {
        printf("Erro a abrir ficheiro Clientes!");
        return;
    }
    int entrou;
    cliente* auxCli = cli, *freeCli;
    
    while (auxCli != NULL) {
        aluguer* auxAluguer, * freeAlu;
        fprintf(f, "%d\t%d\t%s", auxCli->nif, auxCli->nAlugueres, auxCli->nome);
        auxAluguer = auxCli->alu;
        entrou = 0;

        while (auxAluguer != NULL) {
            if (entrou == 0) {
                fprintf(f, "\n");
            }
            entrou = 1;
            if (auxAluguer->dataEntrega.dia == 0) {
                fprintf(f, "%d   %d\t%02d  %02d  %02d", auxAluguer->idGuitarra, auxAluguer->estado,
                        auxAluguer->dataInicio.dia, auxAluguer->dataInicio.mes, auxAluguer->dataInicio.ano);

            } else {
                fprintf(f, "%d   %d\t%02d  %02d  %02d\t%02d  %02d  %02d", auxAluguer->idGuitarra, auxAluguer->estado,
                        auxAluguer->dataInicio.dia, auxAluguer->dataInicio.mes, auxAluguer->dataInicio.ano,
                        auxAluguer->dataEntrega.dia, auxAluguer->dataEntrega.mes, auxAluguer->dataEntrega.ano);
            }
            if (auxAluguer->prox != NULL) {
                fprintf(f, "\n");
                //printf("\n");
            }
            freeAlu = auxAluguer;
            auxAluguer = auxAluguer->prox;
            free(freeAlu);
        }

        if (auxCli->prox != NULL) {
            fprintf(f, "\n\n");
            // printf("\n\n");
        }
        freeCli = auxCli;
        auxCli = auxCli->prox;
        free(freeCli);
    }
    putchar('\n');
    fclose(f);
    return;
}

void atualizaFicheiros(guitarra *gui, cliente * cli) {
    atualizaGuitarras(gui);
    atualizaClientes(cli);
}