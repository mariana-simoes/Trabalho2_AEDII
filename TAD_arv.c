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
    /* caso id == raiz->id, então temos uma duplicata, logo, ignora */

    return raiz;
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



/* percursos da árvore ebaaaaaaa
    Notar que a ordem dos prints importam aqui
*/

void preFix(arv*raiz)
{
    if(raiz){
        printf("[%d:\"%s\"] ", raiz -> id, raiz -> dado); // %d para o int e o %s para a string
        preFix(raiz->esq);
        preFix(raiz->dir);
    }
}

void inFix(arv*raiz) // aqui é o em ordem, que mostra a ordem crescente de ID
{
    if(raiz){
        inFix(raiz->esq);
        printf("[%d:\"%s\"] ", raiz -> id, raiz -> dado);
        inFix(raiz->dir);
    }

}
void posFix(arv*raiz)
{
    if(raiz){
        posFix(raiz->esq);
        posFix(raiz->dir);
        printf("[%d:\"%s\"] ", raiz -> id, raiz -> dado);
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


/*

Ela é chamada na main assim:

FILE *arq = fopen("arquivo_montado.txt", "w");  // abre
if (arq != NULL) {                               // sempre verificar!
    montarArquivo(raiz, arq);                    // escreve tudo
    fclose(arq);                                 // fecha
}

*/



