// FILIPE A. N. SILVA 21260367

#include"clientes.h"

int calculaAtraso(data inicio, data fim) {
	int tempoAlu = 0;
	data auxData;
	verificaBissexto(fim.ano);
	if ((inicio.mes != fim.mes) || (inicio.ano != fim.ano)) {
		auxData = inicio;
		while (1) {
			if (auxData.ano == fim.ano && auxData.mes == fim.mes && auxData.dia == fim.dia)
				return tempoAlu;
			else if (auxData.dia > meses[(auxData.mes) - 1] - 1) {
				auxData.dia = 1;
				auxData.mes += 1;
			}
			else if (auxData.mes > 12) {
				auxData.mes = 1;
				auxData.ano += 1;
			}
			else
				auxData.dia += 1;

			tempoAlu++;
		}
	}
	else
		tempoAlu = fim.dia - inicio.dia;

	if (tempoAlu == 0)
		tempoAlu = 1;

	return tempoAlu;
}

void correLista(cliente* lista) {
	cliente* correrLista = lista;
	while (correrLista != NULL) {
		printf("- NIF: %d\tNome: %s\n", correrLista->nif, correrLista->nome);
		correrLista = correrLista->prox;
	}
}

int verExisteCli(cliente* cli) {
	if (cli == NULL) {
		puts("\nNao existe clientes!");
		fim2();
		return 0;
	}
	return 1;
}

cliente* adicionarClientes(cliente* lista) {
	cliente novo, * aux = NULL, * auxNovo = NULL;
	puts("\n\nMenu adicionar clientes:");

	aux = lista;
	char term;

	if (lista != NULL) {
		puts("NIF's em uso:");
		correLista(lista);
	}

	printf("\nIntroduza o NIF: ");
	if (scanf("%10d%c", &novo.nif, &term) != 2 || term != '\n') {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim();
		return lista;
	}
	else if (novo.nif == 0) {
		return lista;
	}
	else if (novo.nif < 100000000 || novo.nif > 9999999999) {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim2();
		return lista;
	}


	FILE* f;
	cliente banido;
	f = fopen(FicheiroBanidos, "rb");
	if (f == NULL) {
		puts("Erro a criar o ficheiro banidos!");
		exit(1);
	}
	while (fread(&banido, sizeof(cliente), 1, f) == 1)
		if (banido.nif == novo.nif) {
			puts("\nO cliente introduzido foi banido, nao podera ser adicionado!\n");
			fim2();
			return lista;
		}
	fclose(f);

	while (aux != NULL) {
		if (aux->nif == novo.nif) {
			puts("\nJa existe um cliente com o nif introduzido!\n");
			fim2();
			return lista;
		}
		aux = aux->prox;
	}

	auxNovo = malloc(sizeof(cliente));
	if (auxNovo == NULL) {
		printf("\nErro a alocar memoria!\n");
		fim2();
		return lista;
	}

	printf("\nIntroduza o nome do novo cliente: ");
	scanf(" %49[^\n]", novo.nome);

	int i;
	int x = strlen(novo.nome);
	for (i = 0; i < x; i++) {
		if ((isalpha(novo.nome[i]) && novo.nome[i - 1] == ' ') || i == 0) {
			novo.nome[i] = toupper(novo.nome[i]);
		}
	}

	*auxNovo = novo;

	auxNovo->alu = NULL;
	auxNovo->prox = NULL;
	auxNovo->nAlugueres = 0;

	cliente* inicioLista = lista, * auxLista = NULL;

	if (inicioLista == NULL)
		lista = auxNovo;
	else {
		auxLista = inicioLista;
		while (auxLista->prox != NULL)
			auxLista = auxLista->prox;
		auxLista->prox = auxNovo;
	}

	printf("\nO cliente %s com NIF %d foi adicionado!\n", novo.nome, novo.nif);

	fim();
	return lista;
}

cliente* eliminarCliente(cliente* lista, guitarra* gui) {
	cliente* atual, * anterior = NULL;
	int nif, i;
	atual = lista;
	char term;

	puts("Menu eliminar cliente:\n");

	if (verExisteCli(lista) == 0)
		return lista;


	puts("Clientes ativos:");
	correLista(lista);

	printf("\nIntroduza o NIF do cliente a eliminar: ");
	if (scanf("%10d%c", &nif, &term) != 2 || term != '\n') {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		return lista;
	}
	else if (nif == 0) {
		return lista;
	}
	else if (nif < 100000000 || nif > 9999999999) {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		return lista;
	}


	cliente* correrLista = lista;
	while (correrLista != NULL) {
		if (correrLista->nif == nif)
			break;
		correrLista = correrLista->prox;
	}
	if (correrLista == NULL) {
		puts("\nNenhum cliente foi encontrado com o NIF introduzido!");
		fim2();
		return lista;
	}


	aluguer* alu = correrLista->alu, * auxAlu = NULL;
	while (alu != NULL) {
		if (alu->dataEntrega.ano == 0)
			for (i = 0; i < gui[0].tam; i++)
				if ((gui[i].id == alu->idGuitarra) && (gui[i].estado == 1))
					gui[i].estado = 0;

		auxAlu = alu;
		alu = alu->prox;
		free(auxAlu);
	}

	while (atual != NULL && (atual->nif != nif)) {
		anterior = atual;
		atual = atual->prox;
	}
	if (anterior == NULL)
		lista = atual->prox;
	else
		anterior->prox = atual->prox;

	printf("\n- O cliente %s foi eliminado!\n", atual->nome);

	free(atual);

	fim2();
	return lista;
}

void mostrarEstdos(cliente* lista) {
	puts("\nMenu mostar estado:\n");

	if (verExisteCli(lista) == 0)
		return;

	int nif;
	char term;

	correLista(lista);

	printf("\nIntroduza NIF do cliente que pretende consultar: ");
	if (scanf("%10d%c", &nif, &term) != 2 || term != '\n') {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		putchar('\n');
		return;
	}
	else if (nif == 0) {
		return;
	}
	else if (nif < 100000000 || nif > 9999999999) {
		printf("\a");
		puts("\nNIF invalido!\n");
		putchar('\n');
		return;
	}

	cliente* cli = lista;
	while (cli != NULL) {
		if (cli->nif == nif)
			break;

		cli = cli->prox;
	}
	if (cli == NULL) {
		puts("\nNenhum cliente foi encontrado com o NIF introduzido!");
		fim();
		return;
	}

	int contaGui = 0, contaDani = 0, atraso, contaAtraso = 0, contaAlu;
	aluguer* auxAlu = cli->alu;
	while (auxAlu != NULL) {
		if (auxAlu->estado == 0)
			contaGui++;

		if (auxAlu->estado == 2)
			contaDani++;

		if (auxAlu->dataEntrega.ano != 0) {
			atraso = calculaAtraso(auxAlu->dataInicio, auxAlu->dataEntrega);
			if (atraso > 7)
				contaAtraso++;
		}

		auxAlu = auxAlu->prox;
	}

	contaAlu = cli->nAlugueres - contaGui;
	printf("\n- %s:\n\n", cli->nome);
	printf("- Guitarras que detem: %d\n- Nr de alugueres: %d\n- Nr de entregas com atraso: %d\n- Nr de guitarras danificadas: %d\n", contaGui, contaAlu, contaAtraso, contaDani);

	fim2();
	return;
}

void listarClientes(cliente* lista) {
	puts("\nMenu clientes ativos:\n");
	int  tam = 0, tamMax = 0;

	if (verExisteCli(lista) == 0)
		return;

	cliente* cli = lista;
	while (cli != NULL) {
		tam = strlen(cli->nome);
		if (tam > tamMax)
			tamMax = tam;
		cli = cli->prox;
	}

	tamMax += 8;

	int nrT = 0;
	char tab[50];
	int maxT = tamMax / 8;

	cli = lista;
	while (cli != NULL) {
		tam = strlen(cli->nome) + 8;

		nrT = maxT - (tam / 8);

		strcpy(tab, "\t");
		for (int j = 0; j != nrT; j++)
			strcat(tab, "\t");

		printf("- Nome: %s%sNIF: %d\n", cli->nome, tab, cli->nif);

		putchar('\n');
		cli = cli->prox;
	}

	fim2();
	return;
}

void mostrarBanidos() {
	puts("\nMenu clientes banidos:");
	FILE* f;
	cliente banido;
	f = fopen("ficheiro_binario\\banidos.dat", "rb");
	if (f == NULL) {
		puts("\nNao existe clientes Banidos!\n");
		fim2();
		return;
	}

	while (fread(&banido, sizeof(cliente), 1, f) == 1) {
		if (banido.nAlugueres == 1)
			printf("\n- NIF: %d\tNome: %s\tMotivo: Guitarras danificadas\n", banido.nif, banido.nome);
		if (banido.nAlugueres == 0)
			printf("\n- NIF: %d\tNome: %s\tMotivo: Atraso na entrega\n", banido.nif, banido.nome);
	}

	fclose(f);

	fim2();
	return;
}

cliente* menuClientes(cliente* v, guitarra* gui) {
	int menu;
	char term;

	do {
		puts("Menu Clientes:\n");
		puts("Caso queira sair a qualquer momento digite 0 !");
		puts("1- Adicionar cliente");
		puts("2- Remover cliente");
		puts("3- Mostrar estados");
		puts("4- Listar clientes ativos");
		puts("5- Listar clientes banidos");
		puts("0- Voltar ao menu inicial");
		printf("Opcao: ");
		if (scanf("%2d%c", &menu, &term) != 2 || term != '\n')
			menu = -1;
		else if (menu < 0 || menu > 5)
			menu = -2;

		if (menu == 1) {
			putchar('\n');
			v = adicionarClientes(v);
		}
		else if (menu == 2) {
			putchar('\n');
			v = eliminarCliente(v, gui);
			putchar('\n');
		}
		else if (menu == 3) {
			putchar('\n');
			mostrarEstdos(v);
			putchar('\n');
		}
		else if (menu == 4) {
			putchar('\n');
			listarClientes(v);
			putchar('\n');
		}
		else if (menu == 5) {
			putchar('\n');
			mostrarBanidos();
			putchar('\n');
		}
		else if (menu == 0) {
			printf("\n\n");
			return v;
		}
		else {
			putchar('\a');
			printf("\nOpcao errada!");
			if (menu == -2)
				fim2();
			if (menu == -1)
				fim();
		}
	} while (1);
}