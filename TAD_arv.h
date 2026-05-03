#ifndef ARVORE_H
#define ARVORE_H

typedef struct{ 
    char dado; 
    Arv* esq;
    Arv* dir;
} Arv; 

/// ARVORE BINARIA ///

Arv* inicializa();
Arv* criaArv(int tam);
void podaArv();
void imprime();
char buscaArv();

//inserção

void preFix();
void Fix();
void posFix();

//

/// AVL ///

#endif