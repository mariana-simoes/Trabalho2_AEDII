#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>

#define TAM 64

typedef struct arv {
    int id; 
    char dado[TAM];
    struct arv* esq;
    struct arv* dir;
} arv; 

arv* inicializa(void);
arv* insereArv(arv *raiz, int id, const char *dado); 
arv* podaArv(arv *raiz); 
arv* buscaArv(arv *raiz, int id); 

void preFixComDado(arv*raiz); 
void preFixSemDado(arv*raiz);
void centralComDado(arv*raiz);
void centralSemDado(arv*raiz);
void posFixComDado(arv*raiz); 
void posFixSemDado(arv*raiz);

void montarArquivo (arv *raiz, FILE *arq);

int alturaArv(arv *raiz); 

#endif