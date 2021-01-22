// FILIPE A. N. SILVA 21260367

#define TAM 50

typedef struct Data data;
typedef struct Aluguer aluguer;
typedef struct Guitarra guitarra;
typedef struct Cliente cliente;

struct Data {
    int dia;
    int mes;
    int ano;
};

struct Aluguer {
    int estado;
    int idGuitarra;
    data dataInicio;
    data dataEntrega;
    aluguer *prox;
};

struct Guitarra {
    int tam;
    int id;
    int precoDia;
    int valor;
    int estado;
    char nome[TAM];
};

struct Cliente {
    int nif;
    int nAlugueres;
    char nome[TAM];
    aluguer *alu;
    cliente *prox;
};


