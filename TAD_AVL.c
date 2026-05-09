#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_AVL.h"

avl* criaAvl(int num){
    avl* nv = malloc(sizeof(avl));
    if(nv){
        nv->dado = num;
        nv->esq = NULL;
        nv->dir = NULL;
        nv->altura = 0;
    }
    return nv;
}

int maior(int a, int b){return (a>b)? a: b;}    

int alturaAvl(avl* no){
    if(no == NULL){return -1;}
    else{return no->altura;}
}

avl* rotacaoEsq(avl* no){
    avl *x ,*y;
        
    x = no->dir;
    y = x->esq;
    x->esq = no; 
    no->dir = y;

    no->altura = maior(alturaAvl(no->esq), alturaAvl(no->dir)) + 1;
    x->altura = maior(alturaAvl(x->esq), alturaAvl(x->dir)) + 1;

    return x;
}

avl* rotacaoDir(avl* no){
    avl *x ,*y;

    x= no->esq;
    y= x->dir;
    x->dir = no; 
    no->esq = y;
        
    no->altura = maior(alturaAvl(no->esq), alturaAvl(no->dir)) + 1;
    x->altura = maior(alturaAvl(x->esq), alturaAvl(x->dir)) + 1;
    
    return x;
}

avl* rotaDirEsq(avl* no){
    no->dir = rotacaoDir(no->dir);
    return rotacaoEsq(no);
}

avl* rotaEsqDir(avl* no){
    no->esq = rotacaoEsq(no->esq);
    return rotacaoDir(no);
}

int fatBalanco(avl* no){
    if(no){
        return (alturaAvl(no->esq) - alturaAvl(no->dir));
    }
    else{return 0;}
}

avl* balanceamento(avl*no){
    int fb = fatBalanco(no);
    //rotacao simples a esquerda
    if(fb < -1 && fatBalanco(no->dir) <= 0){
        no = rotacaoEsq(no);
    }
    //rotacao simples a direita
    else if(fb > 1 && fatBalanco(no->esq) >= 0){
        no = rotacaoDir(no);
    }        
    //rotacao dupla a esquerda
    else if(fb > 1 && fatBalanco(no->esq) < 0){
        no = rotaEsqDir(no);
    }
    //rotacao dupla a direita
    else if(fb < -1 && fatBalanco(no->dir) > 0){
        no = rotaDirEsq(no);
    }
    return no;
}
    //funcao de inserir tambem esta criando a arvore avl 
avl* inserir(avl*no, int num){
    if(no == NULL){return criaAvl(num);}
    else{
        if(num < no->dado){
            no->esq = inserir(no->esq, num);
        }
        else if(num > no->dado){
            no->dir = inserir(no->dir, num);
        }
    }
    no->altura = maior(alturaAvl(no->esq), alturaAvl(no->dir))+1;
    no = balanceamento(no);
    return(no);
}

avl* remover(avl* no, int num) {
    if (no == NULL) {
        return NULL;
    }

    if (num < no->dado) {
        no->esq = remover(no->esq, num);
    }
    else if (num > no->dado) {
        no->dir = remover(no->dir, num);
    }
    else {
        // Nó encontrado

        // Caso 1: folha
        if (no->esq == NULL && no->dir == NULL) {
            free(no);
            return NULL;
        }
        // Caso 2: dois filhos — substitui pelo predecessor (maior da esq)
        else if (no->esq != NULL && no->dir != NULL) {
            avl*aux;           
            aux = no->esq;
            while (aux->dir != NULL) { aux = aux->dir; }

            int predecessorValor = aux->dado;//  salva o valor
            no->dado = predecessorValor;
            no->esq = remover(no->esq, predecessorValor); //  remove certo
        }
        // Caso 3: um filho
        else {
            avl* aux = (no->esq != NULL) ? no->esq : no->dir;
            free(no);
            return aux;
        }
    }

    // Recalcula altura e rebalanceia (alcançado por todos os caminhos) 
    no->altura = maior(alturaAvl(no->esq), alturaAvl(no->dir)) + 1;
    no = balanceamento(no);
    return no;
}

void imprime(avl*no, int nivel){
    int i; 
    if(no){
        imprime(no->dir,nivel+1);
        printf("\n\n");
        for(i=0; i<nivel; i++){
            printf("%d", no->dado);
            imprime(no->esq,nivel+1);
        }
    }
}

void podaAvl(avl*no){
    if(no != NULL){
        podaAvl(no->esq);
        podaAvl(no->dir);
        free(no);
    }
}

avl* busca(avl*no, int num){ 
    avl *p = no;
    while (p != NULL && p->dado != num)
        p = (num < p->dado) ? p->esq : p->dir;
    return p;
}
