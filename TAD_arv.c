#include <stdio.h>
#include "TAD_arv.h"

/// ARVORE BINARIA ///

Arv* inicializa(Arv*raiz)
{
    raiz = NULL;
}

Arv* insereArv(int tam)
{

}

void podaArv()
{

}

char buscaArv()
{

}

void preFix(Arv*raiz)
{
    if(raiz){
        printf("c",raiz->dado);
        preFix(raiz->esq);
        preFix(raiz->dir);
    }
}
void Fix(Arv*raiz)
{
    if(raiz){
        Fix(raiz->esq);
        printf("c",raiz->dado);
        Fix(raiz->dir);
    }
}
void posFix(Arv*raiz)
{
    if(raiz){
        posFix(raiz->esq);
        posFix(raiz->dir);
        printf("c",raiz->dado);
    }
}


