// FILIPE A. N. SILVA 21260367

#include"bibliotecas.h"

cliente* menuClientes(cliente *v,guitarra *gui);
void listarClientes(cliente *lista);
cliente* adicionarClientes(cliente *lista);
cliente* eliminarCliente(cliente *lista,guitarra *gui);
void mostrarBanidos();
void mostrarEstdos(cliente *cli);
int calculaAtraso(data inicio,data fim);
void correLista(cliente *lista);
int verExisteCli(cliente* lista);