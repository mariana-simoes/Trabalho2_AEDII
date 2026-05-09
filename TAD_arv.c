#include <stdio.h>
#include "TAD_arv.h"
#include <stdlib.h>
#include <string.h> 

/// ARVORE BINARIA ///

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


/* aqui, o arquivo será montado. Confesso que eu (por ora) não sei como isso é feito pq eu não
me lembro como que FILE funciona. Amnahã eu vejo (apagar esse comentário depois peloamordedeus)
    É usado o percurso em ordem, visto que ele escreve cada pacote em ordem crescente de ID (primeiro esquerda, dps direita).
*/

void montarArquivo (arv *raiz, FILE *arq) { // arquivo já estará aberto. A função não tem papel de abrir e nem fechar o file.
    if (raiz) { // caso base da recursão. Se for NULL, não acontece nada.
        montarArquivo (raiz -> esq, arq); // desce primeeiro pra subarvore esquerda. Todos os IDs à esquerda são menores, então eles serão escritos antes
        fprintf (arq, "Pacote %03d: %s\n", raiz -> id, raiz -> dado); // Escreve no arquivo o nó atual. Note que o primeiro argumento é o FILE * de destino.
        montarArquivo (raiz -> dir, arq); // desce para a subárvore direita, que tem IDs maiores.
    }
}