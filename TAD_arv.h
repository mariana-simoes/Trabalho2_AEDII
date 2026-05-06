#ifndef ARVORE_H
#define ARVORE_H

typedef struct{ 
    char dado; 
    Arv* esq;
    Arv* dir;
} Arv; 

/// ARVORE BINARIA ///

Arv* inicializa(Arv*raiz);
Arv* insereArv(int tam);
void podaArv();
char buscaArv();


void preFix(Arv*raiz);
void Fix(Arv*raiz);
void posFix(Arv*raiz);


#endif