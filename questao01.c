#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "TAD_arv.h"
#include "TAD_vetor.h"

#define N 20  // quantidade de elementos do vetor e da árvore

int main(void) {
    setlocale(LC_ALL, "pt_BR.UTF-8"); 
    
    srand(time(NULL));

    //srand(42); -> semente fixa (geraria sempre a mesma árvore)
    
    Vetor *vet = criarVetor(N);

    //vou usar valores entre 100-999 para ids legíveis
    int usados[N];
    int cnt = 0;
    while (cnt < N) {
        int val = rand() % 900 + 100;
        int dup = 0;
        for (int k = 0; k < cnt; k++) {
            if (usados[k] == val) { dup = 1; break; }
        }
        if (!dup) {
            vet->dados[cnt] = val;
            usados[cnt]     = val;
            cnt++;
        }
    }

    // inserir elementos
    arv *raiz = inicializa();
    for (int i = 0; i < N; i++) {
        char dado[TAM];
        snprintf(dado, TAM, "pct%03d", vet->dados[i]);
        raiz = insereArv(raiz, vet->dados[i], dado);
    }

     //informações da árvore
    printf("Informações da árvore\n");
    printf("Número de nós: %d\n", N);
    printf("Altura: %d\n\n", alturaArv(raiz));

    //caminhamentos
    printf("Caminhamento Pré-Fixado (raiz -> esq -> dir)\n");
    preFixSemDado(raiz);
    printf("\n\n");

    printf("Caminhamento Central (esq -> raiz -> dir)\n");
    printf("(exibe em ordem crescente)\n");
    centralSemDado(raiz);
    printf("\n\n");

    printf("Caminhamento Pós-Fixado (esq -> dir -> raiz)\n");
    posFixSemDado(raiz);
    printf("\n\n");

    //liberar memória
    raiz = podaArv(raiz);
    freeVetor(vet);

    return 0;
}
