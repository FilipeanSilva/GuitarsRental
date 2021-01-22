// FILIPE A. N. SILVA 21260367

#include"iniciaGuitarra.h"

void verificaFicheiroBinario()
{
	char* aux;
	char* auxNome = (char*)malloc(strlen(FicheiroBanidos) + 1);
	strcpy(auxNome, FicheiroBanidos);
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

	strcpy(auxNome, FicheiroBanidos);
	aux = strchr(auxNome, '\\') + 1;
	char* nomeFicheiro = (char*)malloc(strlen(aux) + 1);
	strcpy(nomeFicheiro, aux);

	FILE* f;
	f = fopen(FicheiroBanidos, "rb");
	if (f == NULL) {
		char* criaFicheiro = (char*)malloc(strlen(nomePasta) + strlen("\\") + strlen(nomeFicheiro) + 1);
		criaFicheiro = strcpy(criaFicheiro, nomePasta);
		criaFicheiro = strcat(criaFicheiro, "\\");
		criaFicheiro = strcat(criaFicheiro, nomeFicheiro);
		if (criaFicheiro == NULL)
		{
			puts("Erro a criar o ficheiro banidos!");
			exit(1);
		}

		f = fopen(criaFicheiro, "wb");
		if (f == NULL) {
			puts("Erro a criar o ficheiro banidos!");
			exit(1);
		}
		FicheiroBanidos = (char*)malloc(strlen(criaFicheiro) + 1);
		FicheiroBanidos = strcpy(FicheiroBanidos, criaFicheiro);
	}
	fclose(f);
}

void criaFichGui() {
	char* aux;
	char* auxNome = (char*)malloc(strlen(FicheiroGuitarras) + 1);
	strcpy(auxNome, FicheiroGuitarras);
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

	strcpy(auxNome, FicheiroGuitarras);
	aux = strchr(auxNome, '\\') + 1;
	char* nomeFicheiro = (char*)malloc(strlen(aux) + 1);
	strcpy(nomeFicheiro, aux);
	
	FILE* f;
	f = fopen(FicheiroGuitarras, "rt");
	if (f == NULL) {
			char* criaFicheiro = (char*)malloc(strlen(nomePasta) + strlen("\\") + strlen(nomeFicheiro) + 1);
			criaFicheiro = (char*)malloc(strlen(nomePasta) + strlen("\\") + strlen(nomeFicheiro) + 1);
			criaFicheiro = strcpy(criaFicheiro, nomePasta);
			criaFicheiro = strcat(criaFicheiro, "\\");
			criaFicheiro = strcat(criaFicheiro, nomeFicheiro);
			if (criaFicheiro == NULL)
			{
				puts("Erro a criar o ficheiro guitarras!");
				exit(1);
			}

			f = fopen(criaFicheiro, "wt");
			if (f == NULL) {
				puts("Erro a criar o ficheiro guitarras!");
				exit(1);
			}
			FicheiroGuitarras = (char*)malloc(strlen(criaFicheiro) + 1);
			FicheiroGuitarras = strcpy(FicheiroGuitarras, criaFicheiro);
	}
	fclose(f);
	return;
}

int contaGuitarras() {
	int id, precoDia, valor, estado, conta = 0;
	char nome[TAM];

	FILE* f;
	f = fopen(FicheiroGuitarras, "rt");
	if (f == NULL) {
		criaFichGui();
		return 0;
	}
	else {
		while (fscanf(f, " %d %d %d %d %[^\n]", &id, &precoDia, &valor, &estado, nome) == 5) {
			conta++;
		}
	}


	fclose(f);
	return conta;
}

guitarra* criaVetGui(int contaGui) {
	guitarra* aux;
	int i;

	aux = malloc(sizeof(guitarra) * contaGui);
	if (aux == NULL) {
		puts("erro a criar vetor guitarras!");
		return NULL;
	}

	for (i = 0; i < contaGui; i++)
		aux[i].tam = contaGui;

	return aux;
}

void preencheGuitarra(guitarra* vetGui) {
	int id, precoDia, valor, estado, i;
	char nome[TAM];

	FILE* f;
	f = fopen("ficheiros_texto\\guitarras.txt", "rt");
	if (f == NULL) {
		printf("Erro a abrir ficheiro guitarras!");
		return;
	}
	else {
		for (i = 0; fscanf(f, " %d %d %d %d %[^\n]s", &id, &precoDia, &valor, &estado, nome) == 5; i++) {

			vetGui[i].id = id;
			vetGui[i].precoDia = precoDia;
			vetGui[i].valor = valor;
			vetGui[i].estado = estado;
			strcpy(vetGui[i].nome, nome);
		}
	}

	fclose(f);
	return;
}

guitarra* vetGuiCriaVetGuiNovo() {
	guitarra* aux;

	aux = malloc(sizeof(guitarra));
	if (aux == NULL) {
		puts("erro a criar vetor guitarras!");
		return NULL;
	}

	aux[0].estado = 0;
	aux[0].id = 0;
	strcpy(aux[0].nome, "NULL");
	aux[0].precoDia = 0;
	aux[0].tam = 0;
	aux[0].valor = 0;

	return aux;
}

guitarra* iniciaGui() {
	int contaGui;
	guitarra* vetGui;

	verificaFicheiroBinario();

	contaGui = contaGuitarras();
	if (contaGui == 0) {
		vetGui = vetGuiCriaVetGuiNovo();
	}
	else {
		vetGui = criaVetGui(contaGui);
		preencheGuitarra(vetGui);
	}

	return vetGui;
}