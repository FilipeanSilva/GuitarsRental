// FILIPE A. N. SILVA 21260367

#include"bibliotecas.h"
#include <time.h>

cliente* menuAlugueres(guitarra* vGui, cliente* vCli);
cliente* criaAluguer(guitarra* gui, cliente* cli);
data* dataHoje(cliente* vCli);
data dataPrevistaEntrega(data* dataAtual);
void listarTodosAlugueres(cliente* lista);
void listarAlugueresAtuais(cliente* cli);
cliente* concluiAluguer(guitarra* gui, cliente* cli);
cliente* banir(cliente* lista,cliente* cli,guitarra *gui);
int alterarMaxAlu(int maxAluguer);
int guitarrasbaratas(int valorGuitarraBarata);
int calculaTempo(aluguer* auxAlu, data* dataAtual);
cliente* banimentoAuto(cliente* lista,data* dataAtual,guitarra* gui);
cliente* encontraNif(cliente *lista, int nif);
aluguer* novoAluguer(aluguer *inicio,aluguer* novo);
int nrGuitarrasbaratas(int nrGuibarata);
int VerExisteCli(cliente* lista);;