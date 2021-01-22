// FILIPE A. N. SILVA 21260367

#include    "bibliotecas.h"
#include    "iniciaCliente.h"
#include    "iniciaGuitarra.h"
#include    "menu.h"

void inicia()
{
	FicheiroGuitarras = (char*)malloc(strlen("ficheiros_texto\\guitarras.txt") + 1);
	if (FicheiroGuitarras == NULL)
	{
		puts("Erro a alocar memoria nas guitarras");
	}
	FicheiroGuitarras = strcpy(FicheiroGuitarras, "ficheiros_texto\\guitarras.txt");

	FicheiroBanidos = (char*)malloc(strlen("ficheiro_binario\\banidos.dat") + 1);
	if (FicheiroBanidos == NULL)
	{
		puts("Erro a alocar memoria nos banidos");
	}
	FicheiroBanidos = strcpy(FicheiroBanidos, "ficheiro_binario\\banidos.dat");

	FicheiroClientes = (char*)malloc(strlen("ficheiros_texto\\clientes.txt") + 1);
	if (FicheiroClientes == NULL)
	{
		puts("Erro a alocar memoria nos clientes");
	}
	FicheiroClientes = strcpy(FicheiroClientes, "ficheiros_texto\\clientes.txt");
}

int main() {
	guitarra* vetGui = NULL;
	cliente* vetCli = NULL;

	inicia();

	vetGui = iniciaGui();
	vetCli = iniciaCli(vetGui);

	menu(vetGui, vetCli);

	return 0;
}