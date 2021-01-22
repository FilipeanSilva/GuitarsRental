// FILIPE A. N. SILVA 21260367

#ifndef BIBLIOTECAS_H
#define BIBLIOTECAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include"estruturas.h"
#define TAM 50

struct stat info;
void fim();
void fim2();
int meses[12];
void bissexto() ;
void nBissexto();
void verificaBissexto(int ano) ;
char* FicheiroGuitarras;
char* FicheiroClientes;
char* FicheiroBanidos;
#endif // BIBLIOTECAS_H