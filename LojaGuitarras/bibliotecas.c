#include "bibliotecas.h"

void fim() {
    putchar('\n');
    printf("\nPrima qualquer tecla: ");
    while ((getchar()) != '\n');
    while ((getchar()) != '\n');
    printf("\n\n");
    return;
}

void fim2() {
    putchar('\n');
    printf("\nPrima qualquer tecla: \n");
    while ((getchar()) != '\n');
    printf("\n\n");
    return;
}

void bissexto() {
    meses[0] = 31;
    meses[1] = 29;
    meses[2] = 31;
    meses[3] = 30;
    meses[4] = 31;
    meses[5] = 30;
    meses[6] = 31;
    meses[7] = 31;
    meses[8] = 30;
    meses[9] = 31;
    meses[10] = 30;
    meses[11] = 31;
}

void nBissexto() {
    meses[0] = 31;
    meses[1] = 28;
    meses[2] = 31;
    meses[3] = 30;
    meses[4] = 31;
    meses[5] = 30;
    meses[6] = 31;
    meses[7] = 31;
    meses[8] = 30;
    meses[9] = 31;
    meses[10] = 30;
    meses[11] = 31;
}

void verificaBissexto(int ano) {

    if (((ano % 4 == 0) && (ano % 100 != 0)) || (ano % 400 == 0))
        bissexto();
    else
        nBissexto();
}