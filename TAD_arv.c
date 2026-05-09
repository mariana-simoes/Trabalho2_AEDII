#include <stdio.h>
#include "TAD_arv.h"
#include <stdlib.h>
#include <string.h> 

arv* inicializa(void)
{
    return NULL;
}

arv* insereArv(arv *raiz, int id, const char *dado) {
    if (raiz == NULL) {
        arv *novo = (arv*) malloc(sizeof(arv));
        
        novo->id  = id;
        strncpy(novo->dado, dado, TAM - 1);
        novo->dado[TAM - 1] = '\0';
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    if (id < raiz->id)
        raiz->esq = insereArv(raiz->esq, id, dado);
    else if (id > raiz->id)
        raiz->dir = insereArv(raiz->dir, id, dado);
    //caso id == raiz->id, então temos uma duplicata, logo, ignora

    return raiz;
}

//retorna a altura da árvore (número de níveis - 1)
int alturaArv(arv *raiz) {
    if (raiz == NULL) return -1;
    int altEsq = alturaArv(raiz->esq);
    int altDir = alturaArv(raiz->dir);
    return 1 + (altEsq > altDir ? altEsq : altDir);
}

arv* podaArv(arv *raiz) {
    if (raiz != NULL) {
        raiz -> esq = podaArv (raiz -> esq);
        raiz -> dir = podaArv (raiz -> dir);
        free (raiz);
    }
    return NULL;
}


arv* buscaArv(arv *raiz, int id) {
    if (raiz == NULL || raiz -> id == id) {
         return raiz;
    }
       
    if (id < raiz -> id) {
        return buscaArv (raiz -> esq, id);
    }
    return buscaArv(raiz -> dir, id);
}

//percursos da árvore 
void preFixComDado(arv*raiz){
    if(raiz){
        printf("[%d:\"%s\"] ", raiz -> id, raiz -> dado);
        preFixComDado(raiz->esq);
        preFixComDado(raiz->dir);
    }
}

void preFixSemDado(arv*raiz){
    if(raiz){
        printf("%d ", raiz->id);
        preFixSemDado(raiz->esq);
        preFixSemDado(raiz->dir);
    }
}

// aqui é o em ordem, que mostra a ordem crescente de ID
void centralComDado(arv*raiz){
    if(raiz){
        centralComDado(raiz->esq);
        printf("[%d:\"%s\"] ", raiz -> id, raiz -> dado);
        centralComDado(raiz->dir);
    }
}

void centralSemDado(arv*raiz){
    if(raiz){
        centralSemDado(raiz->esq);
        printf("%d ", raiz->id);
        centralSemDado(raiz->dir);
    }
}

void posFixComDado(arv*raiz)
{
    if(raiz){
        posFixComDado(raiz->esq);
        posFixComDado(raiz->dir);
        printf("[%d:\"%s\"] ", raiz -> id, raiz -> dado);
    }
}

void posFixSemDado(arv*raiz)
{
    if(raiz){
        posFixSemDado(raiz->esq);
        posFixSemDado(raiz->dir);
        printf("%d ", raiz -> id);
    }
}

void montarArquivo (arv *raiz, FILE *arq) { 
    if (raiz) { 
        montarArquivo (raiz -> esq, arq); 
        fprintf (arq, "Pacote %03d: %s\n", raiz -> id, raiz -> dado); 
        montarArquivo (raiz -> dir, arq); 
    }
}