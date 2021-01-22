// FILIPE A. N. SILVA 21260367

#include"alugueres.h"

int maxAluguer, valorGuitarraBarata, nrGuibarata;
data* dataAtual;

data* dataHoje(cliente* vCli) {

	cliente* auxCli = vCli;
	
	time_t t = time(NULL);
	const struct tm tm = *localtime(&t);

	const int dia = tm.tm_mday;
	const int mes = tm.tm_mon + 1;
	const int ano = tm.tm_year + 1900;

	printf("%d-%d-%d", ano, mes, dia);

	while (auxCli != NULL) {
		aluguer* auxAluguer = auxCli->alu;
		while (auxAluguer != NULL) {
			if (auxAluguer->dataEntrega.dia == 0) {
				if (auxAluguer->dataInicio.ano > ano) {
					printf("\a");
					printf("\nData introduzida invalida !\n\n");
					fim2();
					return NULL;
				}
				else if ((auxAluguer->dataInicio.mes > mes) && (auxAluguer->dataInicio.ano == ano)) {
					printf("\a");
					printf("\nData introduzida invalida !\n\n");
					fim2();
					return NULL;
				}
				else if ((auxAluguer->dataInicio.dia > dia) && (auxAluguer->dataInicio.mes == mes) && (auxAluguer->dataInicio.ano == ano)) {
					printf("\a");
					printf("\nData introduzida invalida !\n\n");
					fim2();
					return NULL;
				}
			}
			else {
				if (auxAluguer->dataEntrega.ano > ano) {
					printf("\a");
					printf("\nData introduzida invalida !\n\n");
					fim2();
					return NULL;
				}
				else if ((auxAluguer->dataEntrega.mes > mes) && (auxAluguer->dataEntrega.ano == ano)) {
					printf("\a");
					printf("\nData introduzida invalida !\n\n");
					fim2();
					return NULL;
				}
				else if ((auxAluguer->dataEntrega.dia > dia) && (auxAluguer->dataEntrega.mes == mes) && (auxAluguer->dataEntrega.ano == ano)) {
					printf("\a");
					printf("\nData introduzida invalida !\n\n");
					fim2();
					return NULL;
				}
			}
			auxAluguer = auxAluguer->prox;
		}
		auxCli = auxCli->prox;
	}

	data* dataHoje = malloc(sizeof(data));
	if (dataHoje == NULL) {
		puts("Erro a alocar memoria ! ");
		fim2();
		return NULL;
	}
	dataHoje->ano = ano;
	dataHoje->mes = mes;
	dataHoje->dia = dia;

	return dataHoje;
}

int calculaTempo(aluguer* auxAlu, data* dataAtual) {
	int tempoAlu = 0;
	data auxData;
	if ((auxAlu->dataInicio.mes != dataAtual->mes) || (auxAlu->dataInicio.ano != dataAtual->ano)) {
		auxData = auxAlu->dataInicio;
		while (1) {
			if (auxData.ano == dataAtual->ano && auxData.mes == dataAtual->mes && auxData.dia == dataAtual->dia) {
				return tempoAlu;
			}
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
		tempoAlu = dataAtual->dia - auxAlu->dataInicio.dia;
	if (tempoAlu == 0)
		tempoAlu = 1;

	return tempoAlu;
}

data dataPrevistaEntrega(data* dataInicio) {
	int mesEntrega = dataInicio->mes - 1;
	data dataEntrega;

	if ((dataInicio->dia + 7) > meses[mesEntrega])
		if ((mesEntrega == 11) && (dataInicio->dia + 7) > meses[mesEntrega]) {
			dataEntrega.ano = dataInicio->ano + 1;
			dataEntrega.mes = 1;
			dataEntrega.dia = dataInicio->dia + 7 - meses[mesEntrega];
		}
		else {
			dataEntrega.ano = dataInicio->ano;
			dataEntrega.mes = dataInicio->mes + 1;
			dataEntrega.dia = dataInicio->dia + 7 - meses[mesEntrega];
		}
	else {
		dataEntrega.ano = dataInicio->ano;
		dataEntrega.mes = dataInicio->mes;
		dataEntrega.dia = dataInicio->dia + 7;
	}

	return dataEntrega;
}

cliente* banir(cliente* lista, cliente* cli, guitarra* gui) {
	FILE* f;
	cliente banir = *cli;
	int i;

	f = fopen(FicheiroBanidos, "ab");
	if (f == NULL) {
		puts("\nErro a abrir ficheiro binario!\n");
		return lista;
	}

	if ((fwrite(&banir, sizeof(cliente), 1, f)) != 1) {
		puts("\nErro a escrever no ficheiro binario!\n");
		return lista;
	}

	fclose(f);

	cliente* atual, * anterior = NULL;
	int nif;
	atual = lista;

	nif = cli->nif;

	while (atual != NULL && (atual->nif != nif)) {
		anterior = atual;
		atual = atual->prox;
	}
	if (atual == NULL) {
		puts("Nao existe nenhum cliente com o nome introduzido!");
		return lista;
	}

	if (anterior == NULL)
		lista = atual->prox;
	else
		anterior->prox = atual->prox;


	aluguer* alu = atual->alu, * auxAlu = NULL;

	while (alu != NULL) {
		if (alu->dataEntrega.ano == 0)
			for (i = 0; i < gui[0].tam; i++)
				if ((gui[i].id == alu->idGuitarra) && (gui[i].estado == 1))
					gui[i].estado = 0;

		auxAlu = alu;
		alu = alu->prox;
		free(auxAlu);
	}

	free(atual);

	return lista;
}

// SE O N ALUGUERES É 0 FOI BANIMENTO POR TEMPO SE FOR 1 É BANIMENTO POR DANIFICAR GUITARRAS
cliente* banimentoAuto(cliente* cli, data* dataAtual, guitarra* gui) {
	cliente* auxCli = NULL;
	aluguer* auxAlu = NULL;
	int entrou, totalAtraso, atraso;

	auxCli = cli;
	while (auxCli != NULL) {
		totalAtraso = 0;
		entrou = 0;
		auxAlu = auxCli->alu;
		while (auxAlu != NULL) {
			if (auxAlu->dataEntrega.ano == 0) {
				atraso = calculaTempo(auxAlu, dataAtual);
				if (atraso > 7) {
					atraso -= 7;
					totalAtraso += atraso;
					if (totalAtraso > 20) {
						putchar('\n');
						printf("- O cliente %s foi banido!\n", auxCli->nome);
						auxCli->nAlugueres = 0;
						cli = banir(cli, auxCli, gui);
						auxCli = cli;
						entrou = 1;
						break;
					}
				}
			}
			auxAlu = auxAlu->prox;
		}
		if (entrou == 0)
			auxCli = auxCli->prox;
	}

	putchar('\n');

	return cli;
}

aluguer* novoAluguer(aluguer* inicio, aluguer* novo) {
	aluguer* auxLista = NULL;
	aluguer* inicioLista = inicio;

	if (inicioLista == NULL)
		inicio = novo;
	else {
		auxLista = inicioLista;
		while (auxLista->prox != NULL)
			auxLista = auxLista->prox;
		auxLista->prox = novo;
	}
	return inicio;
}

int VerExisteCli(cliente* cli) {
	if (cli == NULL) {
		puts("\nNao existe clientes!");
		fim2();
		return 0;
	}
	return 1;
}

cliente* criaAluguer(guitarra* gui, cliente* cli) {
	int nif;
	int entrou = 0, i;
	char term;

	puts("\nMenu criar Aluguer:");

	if (VerExisteCli(cli) == 0)
		return cli;

	if (gui[0].id == 0) {
		puts("\nNao existe guitarras!");
		fim2();
		return cli;
	}

	entrou = 0;
	for (i = 0; i < gui[0].tam; i++)
		if (gui[i].estado == 0) {
			entrou = 1;
			break;
		}

	if (entrou != 1) {
		puts("\nNao existe guitarras disponiveis!");
		fim2();
		return cli;
	}

	cliente* correLista = cli;
	if (correLista == NULL) {
		puts("\nNao existem clientes para efetuar aluguer!");
		fim2();
		return cli;
	}

	puts("\nClientes:");

	while (correLista != NULL) {
		printf("- NIF: %d\tNome: %s\n", correLista->nif, correLista->nome);
		correLista = correLista->prox;
	}

	printf("\n- Introduza o NIF do cliente que tenciona um novo aluguer: ");
	if (scanf("%10d%c", &nif, &term) != 2 || term != '\n') {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim();
		return cli;
	}
	if (nif == 0) {
		return cli;
	}
	if (nif < 100000000 || nif > 9999999999) {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim2();
		return cli;
	}

	cliente* aux = cli;
	while (aux != NULL) {
		if (aux->nif == nif)
			break;
		aux = aux->prox;
	}

	if (aux == NULL) {
		printf("\a");
		puts("\nO cliente introduzido nao existe !\n");
		fim2();
		return cli;
	}

	aluguer* auxAluguer = NULL;
	int contaAluguer = 0;
	auxAluguer = aux->alu;
	while (auxAluguer != NULL) {
		if ((auxAluguer->dataInicio.dia != 0) && (auxAluguer->dataEntrega.dia == 0))
			contaAluguer++;
		auxAluguer = auxAluguer->prox;
	}

	if (contaAluguer >= maxAluguer) {
		printf("\nO cliente %s tem atualmente %d guitarras alugadas sendo %d o limite maximo permitido !\n\n", aux->nome, contaAluguer, maxAluguer);
		fim2();
		return cli;
	}

	puts("\nGuitarras disponiveis:");
	for (i = 0; i < gui[0].tam; i++)
		if (gui[i].estado == 0)
			printf("- ID:%d\t%s\n", gui[i].id, gui[i].nome);


	int ID;
	printf("\nIntroduza o ID da guitarra a alugar: ");
	if (scanf("%10d%c", &ID, &term) != 2 || term != '\n') {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim();
		return cli;
	}
	else if (ID == 0) {
		return NULL;
	}
	else if (ID < 0 || ID > 2147483647) {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim2();
		return cli;
	}
	entrou = 0;
	for (i = 0; i < gui[0].tam; i++)
		if (gui[i].id == ID) {
			entrou = 1;
			break;
		}
	if ((entrou != 1) || (gui[i].estado == 2)) {
		printf("\a");
		puts("\nO Id introduzido nao existe!\n");
		fim2();
		return cli;
	}
	if (gui[i].estado == 1) {
		puts("\nA guitarra introduzida encontra-se alugada!\n");
		fim2();
		return cli;
	}


	auxAluguer = aux->alu;
	contaAluguer = 0;
	while (auxAluguer != NULL) {
		if ((auxAluguer->dataInicio.dia != 0) && (auxAluguer->dataEntrega.dia != 0))
			contaAluguer++;
		auxAluguer = auxAluguer->prox;
	}

	if ((gui[i].valor > valorGuitarraBarata) && (contaAluguer < nrGuibarata)) {
		printf("\nO cliente nao pode alugar a guitarra, o seu valor e %d euros, necessita de ter pelo menos "
			"%d guitarras baratas alugadas(menos que %d euros)!\n\n",
			gui[i].valor, nrGuibarata, valorGuitarraBarata);
		fim2();
		return cli;
	}


	data dataEntrega = dataPrevistaEntrega(dataAtual);


	printf("\nA guitarra deve ser devolvida ate a seguinte data: %d/%d/%d\n", dataEntrega.dia, dataEntrega.mes, dataEntrega.ano);
	printf("Caso a guitarra seja entregue no 7 Dia tera um custo de: %d euros\n\n", gui[i].precoDia * 7);

	aluguer* novoAlu = NULL;
	novoAlu = malloc(sizeof(aluguer));
	if (novoAlu == NULL) {
		printf("Erro a alocar memoria!");
		fim2();
		return cli;
	}

	novoAlu->prox = NULL;
	novoAlu->estado = 1;
	novoAlu->idGuitarra = ID;
	novoAlu->dataInicio = *dataAtual;
	novoAlu->dataEntrega.dia = 0;
	novoAlu->dataEntrega.mes = 0;
	novoAlu->dataEntrega.ano = 0;
	aux->nAlugueres += 1;

	aux->alu = novoAluguer(aux->alu, novoAlu);

	gui[i].estado = 1;

	fim2();
	return cli;
}

cliente* concluiAluguer(guitarra* gui, cliente* cli) {
	int i, entrou;
	char term;

	puts("\nMenu concluir Aluguer:");

	if (VerExisteCli(cli) == 0)
		return cli;

	entrou = 0;

	cliente* correLista = cli;
	aluguer* correAlu = correLista->alu;
	while (correLista != NULL) {
		while (correAlu != NULL) {
			if (correAlu->dataEntrega.ano == 0) {
				entrou = 1;
				break;
			}
			correAlu = correAlu->prox;
		}
		if (entrou == 1)
			break;

		correLista = correLista->prox;
	}
	if (correLista == NULL) {
		puts("\nNao existem alugueres por concluir!");
		fim2();
		return cli;
	}

	puts("\nGuitarras alugadas:");
	for (i = 0; i < gui[0].tam; i++)
		if (gui[i].estado == 1)
			printf("- ID: %d \tNome: %s\n", gui[i].id, gui[i].nome);

	int ID;
	printf("\nIntroduza o ID da guitarra a concluir o aluguer: ");
	if (scanf("%10d%c", &ID, &term) != 2 || term != '\n') {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim();
		return cli;
	}
	else if (ID == 0) {
		return cli;
	}
	else if (ID < 0 || ID > 2147483647) {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim();
		return cli;
	}
	entrou = 0;
	for (i = 0; i < gui[0].tam; i++)
		if ((gui[i].id == ID) && (gui[i].estado == 1)) {
			entrou = 1;
			break;
		}
	if (entrou != 1) {
		printf("\a");
		puts("\nA guitarra introduzida nao se encontra alugada!\n");
		fim();
		return cli;

	}
	else if (gui[i].estado == 0 || gui[i].estado == 2) {
		puts("\nO Id introduzido nao existe!\n");
		fim();
		return cli;
	}


	cliente* auxCli = cli;
	aluguer* auxAlu = NULL, * aluAnterior = NULL;
	entrou = 0;
	while (auxCli != NULL) {
		auxAlu = auxCli->alu;
		while (auxAlu != NULL) {
			if ((auxAlu->idGuitarra == ID) && (auxAlu->dataEntrega.ano == 0)) {
				entrou = 1;
				break;
			}
			aluAnterior = auxAlu;
			auxAlu = auxAlu->prox;
		}
		if (entrou == 1)
			break;
		auxCli = auxCli->prox;
	}

	int menuDanificada, danificada = 0;

	puts("\nA guitarra encontra-se danificada?");
	puts("1 - Sim");
	puts("2 - Nao");
	printf("Escolha: ");
	if (scanf("%2d%c", &menuDanificada, &term) != 2 || term != '\n') {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim();
		return cli;
	}
	else if (menuDanificada == 0) {
		return cli;
	}
	else if (menuDanificada < 0 || menuDanificada > 2) {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim2();
		return cli;
	}
	if (menuDanificada == 1) {
		danificada = 1;
		aluguer* auxAlu2 = auxCli->alu;
		entrou = 0;
		gui[i].estado = 2;
		//CALCULA QUANTAS GUITARRAS DANIFICADAS O CLIENTE JA DANIFICOU
		while (auxAlu2 != NULL) {
			if (auxAlu2->estado == 2)
				entrou += 1;
			auxAlu2 = auxAlu2->prox;
		}

		if (entrou == 3) {
			printf("\n- O cliente %s foi banido pois ja danificou mais de 3 guitarras\n", auxCli->nome);
			auxCli->nAlugueres = 1;
			cli = banir(cli, auxCli, gui);
			fim2();
			return cli;
		}
		printf("\nO cliente tem de pagar um multa por dano no valor de: %d euros\n", gui[i].valor);
	}
	else if (menuDanificada != 2) {
		printf("\a");
		puts("\nResposta Incorreta!\n");
		fim2();
		return cli;
	}

	int tempoAlu, tempoAtraso;

	tempoAtraso = tempoAlu = calculaTempo(auxAlu, dataAtual);

	if (tempoAtraso > 7) {
		tempoAtraso -= 7;
		int multa = 10;
		printf("\nO cliente tem de pagar uma multa no valor de %d euros por ter entrego com %d dias de atraso\n", tempoAtraso * multa, tempoAtraso);
	}

	int custo;
	custo = tempoAlu * gui[i].precoDia;
	printf("\nCusto do aluguer: %d\n", custo);

	auxAlu->dataEntrega = *dataAtual;

	if (danificada == 1) {
		auxAlu->estado = 2;
	}
	else {
		gui[i].estado = 0;
		auxAlu->estado = 1;
	}

	fim2();
	return cli;
}

void listarTodosAlugueres(cliente* cli) {
	cliente* aux = cli;
	aluguer* auxAluguer = NULL;

	puts("\nMenu listar alugueres atuais e concluidos:\n");

	if (VerExisteCli(cli) == 0)
		return;

	while (aux != NULL) {
		printf("- %s:\n", aux->nome);

		auxAluguer = aux->alu;
		while (auxAluguer != NULL) {
			if (auxAluguer->dataEntrega.ano != 0)
				printf("\tDataInicio: %02d/%02d/%1d\tDataEntrega: %02d/%02d/%02d\n", auxAluguer->dataInicio.dia, auxAluguer->dataInicio.mes, auxAluguer->dataInicio.ano,
					auxAluguer->dataEntrega.dia, auxAluguer->dataEntrega.mes, auxAluguer->dataEntrega.ano);
			else
				printf("\tDataInicio: %02d/%02d/%02d\n", auxAluguer->dataInicio.dia, auxAluguer->dataInicio.mes, auxAluguer->dataInicio.ano);
			auxAluguer = auxAluguer->prox;
		}
		printf("\n");
		aux = aux->prox;
	}

	fim2();
	return;
}

void listarAlugueresAtuais(cliente* cli) {
	cliente* aux = cli;
	aluguer* auxAluguer = NULL;
	data dataPrevista;
	int atraso;

	puts("\nMenu alugueres a decorrer:\n");

	if (VerExisteCli(cli) == 0)
		return;

	while (aux != NULL) {
		printf("- %s:\n", aux->nome);
		auxAluguer = aux->alu;
		while (auxAluguer != NULL) {
			if (auxAluguer->dataEntrega.ano == 0) {

				dataPrevista = dataPrevistaEntrega(&auxAluguer->dataInicio);
				atraso = calculaTempo(auxAluguer, dataAtual);
				if (atraso > 7)
					atraso -= 7;
				else
					atraso = 0;
				printf("\tID: %d\tInicio: %02d/%02d/%1d\tEntrega prevista: %02d/%02d/%02d\tAtraso: %d\n", auxAluguer->idGuitarra, auxAluguer->dataInicio.dia, auxAluguer->dataInicio.mes, auxAluguer->dataInicio.ano,
					dataPrevista.dia, dataPrevista.mes, dataPrevista.ano, atraso);
			}
			auxAluguer = auxAluguer->prox;
		}
		printf("\n");
		aux = aux->prox;
	}

	fim2();
	return;
}

int alterarMaxAlu(int maxAluguer) {
	int max;
	char term;

	puts("\nMenu alterar maximo alugueres:\n");

	printf("Introduza o numero max de alugueres: ");
	if (scanf("%10d%c", &max, &term) != 2 || term != '\n') {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim();
		return maxAluguer;
	}
	else if (max < 1 || max > 2147483647) {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim2();
		return maxAluguer;
	}
	else
		printf("\nNovo numero maximo de alugueres: %d\n", max);

	fim2();
	return max;
}

int guitarrasbaratas(int valorGuitarraBarata) {
	int max;
	char term;

	puts("\nMenu alterar valor guitarras baratas:\n");

	printf("Introduza o valor a considerar por guitarras baratas: ");
	if (scanf("%10d%c", &max, &term) != 2 || term != '\n') {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim();
		return valorGuitarraBarata;
	}
	else if (max < 1 || max > 2147483647) {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim2();
		return valorGuitarraBarata;
	}
	printf("\nNovo valor guitarras baratas: %d\n", max);

	fim2();
	return max;
}

int nrGuitarrasbaratas(int nrGuibarata) {
	int max;
	char term;

	puts("\nMenu alterar nr de guitarras baratas necessarias para aluguer de uma cara:\n");

	printf("Introduza o valor a considerar por guitarras baratas: ");
	if (scanf("%10d%c", &max, &term) != 2 || term != '\n') {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim();
		return nrGuibarata;
	}
	else if (max < 0 || max > 2147483647) {
		printf("\a");
		puts("\nNumero introduzido invalido!\n");
		fim2();
		return nrGuibarata;
	}
	else
		printf("\nNovo numero de guitarras baratas necessarias para aluguer de uma cara: %d\n", max);

	fim2();
	return max;
}

cliente* menuAlugueres(guitarra* vGui, cliente* vCli) {
	int menu, auxMaxAluguer = 5, auxValorGuitarraBarata = 500, auxNrGuiBarata = 6;
	cliente* novoV = NULL;
	char term;

	valorGuitarraBarata = auxValorGuitarraBarata;
	maxAluguer = auxMaxAluguer;
	nrGuibarata = auxNrGuiBarata;

	dataAtual = dataHoje(vCli);
	if (dataAtual == NULL) {
		return vCli;
	}

	vCli = banimentoAuto(vCli, dataAtual, vGui);

	do {
		printf("Menu Alugueres\n");
		puts("1- Criar aluguer");
		puts("2- Concluir um aluguer");
		puts("3- Lista de todos os alugueres");
		puts("4- Lista de alugueres a decorrer");
		puts("5- Alterar max. alugueres");
		puts("6- Alterar o valor considerado por guitarras baratas");
		puts("7- Alterar o nr minimo de guitarras baratas a alugar");
		puts("0- Voltar ao menu inicial");
		printf("Opcao: ");
		if (scanf("%2d%c", &menu, &term) != 2 || term != '\n')
			menu = -1;
		else if (menu < 0 || menu > 7)
			menu = -2;

		if (menu == 1) {
			putchar('\n');
			vCli = criaAluguer(vGui, vCli);
			putchar('\n');
		}
		else if (menu == 2) {
			putchar('\n');
			vCli = concluiAluguer(vGui, vCli);
			putchar('\n');
		}
		else if (menu == 3) {
			putchar('\n');
			listarTodosAlugueres(vCli);
			putchar('\n');
		}
		else if (menu == 4) {
			putchar('\n');
			listarAlugueresAtuais(vCli);
			putchar('\n');
		}
		else if (menu == 5) {
			putchar('\n');
			maxAluguer = alterarMaxAlu(maxAluguer);
			putchar('\n');
		}
		else if (menu == 6) {
			putchar('\n');
			valorGuitarraBarata = guitarrasbaratas(valorGuitarraBarata);
			putchar('\n');
		}
		else if (menu == 7) {
			putchar('\n');
			nrGuibarata = nrGuitarrasbaratas(nrGuibarata);
			putchar('\n');
		}
		else if (menu == 0) {
			printf("\n\n");
			return vCli;
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