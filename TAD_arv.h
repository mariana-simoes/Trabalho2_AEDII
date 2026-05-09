#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>

#define TAM 64

typedef struct arv {
    int id; // identifica o pacote
    char dado[TAM];
    struct arv* esq;
    struct arv* dir;
} arv; 

// ARVORE BINARIA

arv* inicializa(void);
arv* insereArv(arv *raiz, int id, const char *dado); // onde, id, ponteiro para o dado
arv* podaArv(arv *raiz); // aqui, toda a árvore é liberada
arv* buscaArv(arv *raiz, int id); // onde e qual dado quer buscar


/* Percursos da árvore binária. Única diferença entre elas é só quando
a raiz é visitada em relação aos filhos*/

void preFixComDado(arv*raiz); // pré ordem (raiz -> esquerda -> direita). Visita o nó antes dos filhos
void preFixSemDado(arv*raiz);
void centralComDado(arv*raiz); // em ordem (esquerda -> raiz -> direita). Visita o nó entre os filhos. Produz os elementos na ord. crescente
void centralSemDado(arv*raiz);
void posFixComDado(arv*raiz); // pós ordem (esquerda -> direita -> raiz). Visita o nó depois dos filhos. Útil para liberar a árvore.
void posFixSemDado(arv*raiz);

void montarArquivo (arv *raiz, FILE *arq);

int alturaArv(arv *raiz); // retorna a altura da árvore

#endif