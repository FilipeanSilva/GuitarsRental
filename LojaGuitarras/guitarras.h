// FILIPE A. N. SILVA 21260367
#include"bibliotecas.h"

guitarra* menuGuitarras(guitarra* vetor, cliente* vCliente);
void listarGuitarras(guitarra *vetor);
guitarra* adicionarGuitarra(guitarra *v);
void guitarrasAlugadas(guitarra *v,cliente *vCliente);
void historico(guitarra *vGui,cliente *vCli);
void arranjaGui(guitarra *gui);
guitarra* eliminaGui(guitarra *vetor);
int vverExisteGui(guitarra* gui);