#ifndef AVL_H
#define AVL_H

/// ARVORE AVL ///

typedef struct{ 
    int dado; 
    avl* esq;
    avl* dir;
    int altura;     // mostra em qual altura está uma folha
} avl; 

avl* criaAvl(int num);     //Assim como na binaria a árvore é iniciada com a raiz preenchida 
int maior(int a, int b);    //Usado para comparar nós entre si,usada nas rotações

/// ROTAÇÕES ///

avl* rotacaoEsq(avl* no);
avl* rotacaoDir(avl* no);
avl* rotaDirEsq(avl* no);
avl* rotaEsqDir(avl* no);

////////////////

int alturaAvl(avl* no);    //funcao tambem aplicada no fator de balanceamento 
int fatBalanco(avl* no);   //ideal que fique entre 1 e -1, se não é preciso rotações
avl* balanceamento(avl*no);
avl* inserir(avl*no, int num);
avl* remover(avl*no, int num);
void imprime(avl*no, int nivel);

#endif