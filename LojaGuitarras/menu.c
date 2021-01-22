// FILIPE A. N. SILVA 21260367

#include    "menu.h"
#include    "atualizaFicheiros.h"

void menu(guitarra *vGui, cliente *vCli) {
    int menu, entrou = 0;
    char term;

	do {
        if (entrou == 0) {
            printf("Bem vindo ao sistema de gerencia de \"Guitarras p'Alugar\"\n");
            entrou = 1;
        }
        puts("Menu:");
        puts("1- Guitarras");
        puts("2- Clientes");
        puts("3- Alugueres");
        puts("0- Sair");
        printf("Opcao: ");
        if (scanf(" %2d%c", &menu, &term) != 2 || term != '\n')
            menu = -1;
        else if (menu < 0 || menu > 3)
            menu = -2;

        if (menu == 1) {
            printf("\n\n");
            vGui = menuGuitarras(vGui, vCli);
            putchar('\n');
        } else if (menu == 2) {
            printf("\n\n");
            vCli = menuClientes(vCli,vGui);
            putchar('\n');
        } else if (menu == 3) {
            printf("\n\n");
            vCli = menuAlugueres(vGui, vCli);
            putchar('\n');
        } else if (menu == 0) {
            atualizaFicheiros(vGui, vCli);
            return;
        } else {
            putchar('\a');
            printf("\nOpcao errada!\n");
            if (menu == -2)
                fim2();
            if (menu == -1)
                fim();
        }
    } while (1);
}