// FILIPE A. N. SILVA 21260367

#include"iniciaCliente.h"

void criaFichCli() {
    char* aux;
    char* auxNome = (char*)malloc(strlen(FicheiroClientes) + 1);
    strcpy(auxNome, FicheiroClientes);
    aux = strtok(auxNome, "\\");
    char* nomePasta = (char*)malloc(strlen(aux) + 1);
    strcpy(nomePasta, aux);

    if (stat(nomePasta, &info) != 0) {
        int check = mkdir(nomePasta, 0777);
        if (check) {
            printf("Nao foi possivel criar a diretoria ficheiros texto\n");
            exit(1);
        }
    }

    strcpy(auxNome, FicheiroClientes);
    aux = strchr(auxNome, '\\') + 1;
    char* nomeFicheiro = (char*)malloc(strlen(aux) + 1);
    strcpy(nomeFicheiro, aux);


    FILE *f;
    f = fopen(FicheiroClientes, "wt");
    if (f == NULL) {
        puts("Erro a criar ficheiro clientes!");
        exit(1);
    }
    return;
}

cliente* preencheCliente() {
    char linha[TAM];
    int i;

    cliente *lista = NULL, *novoCli = NULL, *auxLista = NULL;
    cliente novo;

    aluguer* novoAlu = NULL, *aux = NULL;

    FILE *f;
    f = fopen(FicheiroClientes, "rt");
    if (f == NULL) {
        criaFichCli();
        return lista;
    }

    int entrou = 0;
    while (fscanf(f, "%d %d %[^\n]", &novo.nif, &novo.nAlugueres, novo.nome) == 3) {
        novo.alu = NULL;
        novo.prox = NULL;

        novoCli = malloc(sizeof (cliente));
        if (novoCli == NULL) {
            printf("Erro a alocar memoria!");
            return lista;
        }

        *novoCli = novo;

        if (entrou == 0)
            lista = novoCli;

        if (lista == NULL)
            lista = novoCli;
        else {
            auxLista = lista;
            while (auxLista->prox != NULL)
                auxLista = auxLista->prox;
            auxLista->prox = novoCli;
        }

        aux = novoCli->alu;

        for (i = 0; i < novoCli->nAlugueres; i++) {

            novoAlu = malloc(sizeof (aluguer));
            if (novoAlu == NULL) {
                printf("Erro a alocar memoria!");
                return lista;
            }

            novoAlu->prox = NULL;

            fscanf(f, "%d %d", &novoAlu->idGuitarra, &novoAlu->estado);

            fgets(linha, TAM, f);

            if (sscanf(linha, "%d %d %d %d %d %d", &novoAlu->dataInicio.dia, &novoAlu->dataInicio.mes, &novoAlu->dataInicio.ano,
                    &novoAlu->dataEntrega.dia, &novoAlu->dataEntrega.mes, &novoAlu->dataEntrega.ano) != 6)
                novoAlu->dataEntrega.dia = novoAlu->dataEntrega.mes = novoAlu->dataEntrega.ano = 0;

            if (novoCli->alu == NULL)
                novoCli->alu = novoAlu;
            else
                aux->prox = novoAlu;

            aux = novoAlu;
        }
    }

    fclose(f);
    return lista;
}

cliente* eliminaBanidos(cliente *lista, int nif, guitarra *gui) {
    cliente *atual, *anterior = NULL;
    atual = lista;

    cliente *correLista = lista;
    aluguer *alu = NULL, *auxAlu = NULL;
    int i;
    while (correLista != NULL) {
        if (correLista->nif == nif) {
            alu = correLista->alu;
            while (alu != NULL) {
                if (alu->dataEntrega.ano == 0)
                    for (i = 0; i < gui[0].tam; i++)
                        if ((gui[i].id == alu->idGuitarra)&&(gui[i].estado == 1))
                            gui[i].estado = 0;

                auxAlu = alu;
                alu = alu->prox;
                free(auxAlu);
            }
        }
        correLista = correLista->prox;
    }

    while (atual != NULL && (atual->nif != nif)) {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL)
        lista = atual->prox;
    else
        anterior->prox = atual->prox;

    printf("- O cliente %s  novamente banido!\n", atual->nome);

    free(atual);
    return lista;
}

cliente* verificaBanidos(cliente *vec, guitarra *gui) {
    FILE *f;
    cliente banido;

    f = fopen("ficheiro_binario\\banidos.dat", "rb");
    if (f == NULL) {
        return vec;
    }

    int entrou = 0;
    cliente* auxCli = vec;
    while (fread(&banido, sizeof (cliente), 1, f) == 1) {
        auxCli = vec;
        while (auxCli != NULL) {
            if (auxCli->nif == banido.nif) {
                if (entrou == 0)
                    puts("Existem clientes banidos no ficheiro dos clientes!\n");
                entrou = 1;
                vec = eliminaBanidos(vec, auxCli->nif, gui);
                auxCli = vec;
            }

            if (auxCli == NULL) {
                fim2();
                return vec;
            }
            auxCli = auxCli->prox;
        }
    }


    fclose(f);
    if (entrou == 1)
        fim2();
    return vec;
}

cliente* iniciaCli(guitarra *gui) {
    cliente *vec = NULL;

    vec = preencheCliente();

    if (vec != NULL)
        vec = verificaBanidos(vec, gui);
    return vec;
}