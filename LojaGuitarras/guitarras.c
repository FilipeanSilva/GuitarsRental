// FILIPE A. N. SILVA 21260367

#include"guitarras.h"

int vverExisteGui(guitarra* gui) {
    if (gui[0].id == 0) {
        puts("\nNao existe guitarras!");
        fim2();
        return 0;
    }
    return 1;
}

guitarra* adicionarGuitarra(guitarra *v) {
    int i;
    guitarra nova;
    char term;

    puts("\n\nMenu adicionar guitarra:");

    nova.estado = 0;
    nova.tam = v[0].tam + 1;

    if (v[0].id != 0) {
        puts("\nID's em uso:");
        for (i = 0; i < v[0].tam; i++)
            printf("- Id: %d\tNome: %s\n", v[i].id, v[i].nome);
    }

    printf("\nIntroduza o ID da nova guitarra (maior que 0): ");
    if (scanf("%10d%c", &nova.id, &term) != 2 || term != '\n') {
        printf("\a");
        puts("\nNumero introduzido invalido!\n");
        fim();
        return v;
    } else if (nova.id == 0) {
        return v;
    } else if (nova.id < 0 || nova.id > 2147483647) {
        printf("\a");
        puts("\nNumero introduzido invalido!\n");
        fim2();
        return v;
    }

    for (i = 0; i < v[0].tam; i++) {
        if (v[i].id == nova.id) {
            puts("\nO id introduzido ja se encontra em uso!\n");
            fim2();
            return v;
        }
    }

    printf("\nIntroduza o preco por dia: ");
    if (scanf("%10d%c", &nova.precoDia, &term) != 2 || term != '\n') {
        printf("\a");
        puts("\nNumero introduzido invalido!\n");
        fim();
        return v;
    } else if (nova.id == 0) {
        return v;
    } else if (nova.precoDia < 0 || nova.precoDia > 2147483647) {
        printf("\a");
        puts("\nNumero introduzido invalido!\n");
        fim2();
        return v;
    }

    printf("\nIntroduza o seu valor (maior que o preco por dia): ");
    if (scanf("%10d%c", &nova.valor, &term) != 2 || term != '\n') {
        printf("\a");
        puts("\nNumero introduzido invalido!\n");
        fim();
        return v;
    } else if (nova.valor < 0 || nova.valor > 2147483647) {
        printf("\a");
        puts("\nNumero introduzido invalido!\n");
        fim2();
        return v;
    }
    if (nova.valor == 0)
        return v;

    if (nova.valor <= nova.precoDia) {
        puts("\nValor invalido o preco por dia necessita ser maior que o valor da guitarra!\n");
        fim2();
        return v;
    }

    printf("\nIntroduza o nome da nova guitarra : ");
    scanf(" %49[^\n]", nova.nome);

    for (i = 0; nova.nome[i] = toupper(nova.nome[i]); i++);

    if (v[0].tam == 0) {
        v[0] = nova;
    } else {
        guitarra *auxGui = NULL;
        auxGui = realloc(v, (v[0].tam + 1) * sizeof (guitarra));
        if (auxGui == NULL) {
            puts("Erro a alocar memoria");
            fim2();
            return v;
        }
        v = auxGui;

        for (i = 0; i < nova.tam; i++)
            v[i].tam = nova.tam;

        for (i = nova.tam - 1;; i--) {
            if (v[i - 1].id > nova.id)
                v[i] = v[i - 1];
            else {
                v[i] = nova;
                break;
            }
        }
    }

    printf("\nA guitarra %s com ID:%d foi adicionada!\n", nova.nome, nova.id);

    fim();
    return v;
}

void historico(guitarra *vGui, cliente *vCli) {
    int i, tam = vGui[0].tam, atraso;
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    cliente *auxCli = vCli;
    aluguer *auxAlu;
    puts("\n\nHistorico das guitarras:");

    if (vverExisteGui(vGui) == 0)
        return;


    for (i = 0; i < tam; i++) {

        printf("- %s :\n", vGui[i].nome);

    	vCli = auxCli;
        while (vCli!=NULL) {
            auxAlu = vCli->alu;
            while (auxAlu!=NULL) {
                if ((auxAlu->idGuitarra == vGui[i].id) && (auxAlu->dataEntrega.ano != 0)) {
                    if (auxAlu->dataInicio.mes < auxAlu->dataEntrega.mes) {
                        for (i = 0; i < 12; i++)
                            if (i == auxAlu->dataInicio.mes) {
                                meses[i];
                                break;
                            }
                        atraso = meses[i] - auxAlu->dataInicio.dia + auxAlu->dataEntrega.dia;
                    } else
                        atraso = auxAlu->dataEntrega.dia - auxAlu->dataInicio.dia;

                    if (atraso > 7)
                        atraso = atraso - 7;
                    else
                        atraso = 0;

                    printf("\tCliente: %s  Datas: %d/%d/%d - %d/%d/%d  Atraso de entrega(dias): %d\n",
                            vCli->nome,
                            auxAlu->dataInicio.dia, auxAlu->dataInicio.mes, auxAlu->dataInicio.ano,
                            auxAlu->dataEntrega.dia, auxAlu->dataEntrega.mes, auxAlu->dataEntrega.ano,
                            atraso);
                }
                auxAlu = auxAlu->prox;
            }
            vCli = vCli->prox;
        }
        printf("\n");
    }

    fim2();
    return;
}

void listarGuitarras(guitarra *gui) {
    puts("\n\nLista das guitarras existentes:");
    int i, tam = 0, tamMax = 0;

    if (vverExisteGui(gui) == 0)
        return;


    for (i = 0; i < gui[0].tam; i++) {
        tam = strlen(gui[i].nome);
        if (tam > tamMax)
            tamMax = tam;
    }

    tamMax += 8;

    int nrT = 0;
    char tab[50];
    int maxT = tamMax / 8;

    for (i = 0; i < gui[0].tam; i++) {
        tam = strlen(gui[i].nome) + 8;

        nrT = maxT - (tam / 8);

        strcpy(tab, "\t");
        for (int j = 0; j != nrT; j++)
            strcat(tab, "\t");

        printf("- Nome: %s%sID: %d\tEstado: %d   Preco/dia: %d\tValor: %d", gui[i].nome, tab, gui[i].id, gui[i].estado, gui[i].precoDia, gui[i].valor);

        putchar('\n');
    }

    fim2();
    return;
}

void guitarrasAlugadas(guitarra *vGui, cliente *vCli) {
    int i, tam = vGui[0].tam;
    cliente *auxCli = vCli;
    aluguer *auxAlu;

    puts("\n\nMenu guitarras atualmente alugadas:\n");

    if (vverExisteGui(vGui) == 0)
        return;

    for (i = 0; i < tam; i++) {

        vCli = auxCli;

        while (vCli != NULL) {
            auxAlu = vCli->alu;
            while (auxAlu != NULL) {
                if ((auxAlu->idGuitarra == vGui[i].id) && (auxAlu->dataEntrega.ano == 0)) {
                    printf("- ID: %d\tNome: %s\tPreco/Dia: %d\tValor: %d\tCliente: %s\tNIF: %d\n", vGui[i].id, vGui[i].nome,
                            vGui[i].precoDia, vGui[i].valor, vCli->nome, vCli->nif);
                }
                auxAlu = auxAlu->prox;
            }
            vCli = vCli->prox;
        }
    }

    fim2();
    return;
}

void arranjaGui(guitarra *gui) {
    puts("\n\nMenu arranjar guitarras:");

    if (vverExisteGui(gui) == 0)
        return;

    int i, entrou = 0;
    for (i = 0; i < gui[0].tam; i++)
        if (gui[i].estado == 2)
            entrou = 1;
    if (entrou == 0) {
        puts("\nNao existem guitarras danificadas!\n");
        fim2();
        return;
    }

    puts("\nGuitarras danificadas:\n");
    for (i = 0; i < gui[0].tam; i++)
        if (gui[i].estado == 2)
            printf("- ID: %d \tNome: %s\n", gui[i].id, gui[i].nome);

    int id;
    char term;
    printf("\nIntroduza o ID da guitarra arranjada: ");
    if (scanf("%10d%c", &id, &term) != 2 || term != '\n') {
        printf("\a");
        puts("\nNumero introduzido invalido!\n");
        fim();
        return;
    } else if (id < 0 || id > 2147483647) {
        printf("\a");
        puts("\nNumero introduzido invalido!\n");
        fim2();
        return;
    }
    if (id == 0)
        return;

    entrou = 0;
    for (i = 0; i < gui[0].tam; i++)
        if ((gui[i].estado == 2)&&(gui[i].id == id)) {
            entrou = 1;
            gui[i].estado = 0;
            break;
        }
    if (entrou == 0) {
        printf("\a");
        puts("O ID introduzido nao pertence a nenhuma guitarra danificada!\n");
        fim2();
        return;
    }

    printf("\nA guitarra %s foi arranjada!\n", gui[i].nome);

    fim2();
    return;
}

guitarra * menuGuitarras(guitarra *vetor, cliente * vCliente) {
    int menu;
    char term;

    do {
        puts("Menu Guitarras\n");
        puts("Caso queira sair a qualquer momento digite 0 !");
        puts("1- Adicionar uma guitarra ao stock");
        puts("2- Historico das guitarras");
        puts("3- Listar todas as guitarras");
        puts("4- Listar guitarras alugadas");
        puts("5- Arranjar guitarras danificadas");
        puts("0- Voltar ao menu inicial");
        printf("Opcao: ");
        if (scanf("%2d%c", &menu, &term) != 2 || term != '\n')
            menu = -1;
        else if (menu < 0 || menu > 6)
            menu = -2;

        if (menu == 1) {
            putchar('\n');
            vetor = adicionarGuitarra(vetor);
            putchar('\n');
        } else if (menu == 2) {
            putchar('\n');
            historico(vetor, vCliente);
            putchar('\n');
        } else if (menu == 3) {
            putchar('\n');
            listarGuitarras(vetor);
            putchar('\n');
        } else if (menu == 4) {
            putchar('\n');
            guitarrasAlugadas(vetor, vCliente);
            putchar('\n');
        } else if (menu == 5) {
            putchar('\n');
            arranjaGui(vetor);
            putchar('\n');
        }  else if (menu == 0) {
            printf("\n\n");
            return vetor;
        } else {
            putchar('\a');
            printf("\nOpcao errada!");
            if (menu == -1)
                fim();
            if (menu == -2)
                fim2();
        }
    } while (1);
}