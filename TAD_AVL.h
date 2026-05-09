#ifndef AVL_H
#define AVL_H

typedef struct avl { 
    int dado; 
    struct avl *esq;
    struct avl *dir;
    int altura;     // mostra em qual altura está uma folha
} avl; 

avl* criaAvl(int num);     
int maior(int a, int b);  

avl* rotacaoEsq(avl* no);
avl* rotacaoDir(avl* no);
avl* rotaDirEsq(avl* no);
avl* rotaEsqDir(avl* no);


int alturaAvl(avl* no); 
int fatBalanco(avl* no); 
avl* balanceamento(avl*no);
avl* inserir(avl*no, int num);
avl* remover(avl*no, int num);
void imprime(avl*no, int nivel);
void podaAvl(avl*no);
avl* busca(avl*no, int num);

#endif