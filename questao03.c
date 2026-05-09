#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>
#include "TAD_arv.h"
#include "estatisticas.h"
#include "TAD_vetor.h"

#define N 1000000

int main(){
    setlocale(LC_ALL,"");
    srand(time(NULL));

    arv* raiz = inicializa();
    Vetor* vet_elementos = criarVetor(N), *vet_ordenado = criarVetor(N);
    preencherDesordenado(vet_elementos);
    
    copiarVetor(vet_elementos,vet_ordenado);
    quickSort(vet_ordenado,0,N-1);
    
    double tempos_arvore[30];
    double tempos_vetor[30];

    for(int i = 0; i < N; i++){
        int elementoArv = vet_elementos->dados[i];
        raiz = insereArv(raiz,elementoArv,"");
    }
    
    for(int i = 0; i < 15; i++){
        int indice = rand() % N;
        int elementoBuscado = vet_elementos->dados[indice];
        double inicio = tempoAtual();
        
        buscaArv(raiz,elementoBuscado);
        
        double fim = tempoAtual();
        double tempo_total = fim - inicio;
        
        tempos_arvore[i] = tempo_total;
        inicio = tempoAtual();
        
        buscaBinaria(vet_ordenado,elementoBuscado);
        
        fim = tempoAtual();
        tempo_total = fim - inicio;
        tempos_vetor[i] = tempo_total;

    }
    for(int i = 0; i < 15; i++){
        int elementoBuscado = randGrande();
        double inicio = tempoAtual();
        
        buscaArv(raiz,elementoBuscado);

        double fim = tempoAtual();
        double tempo_total = fim - inicio;
        
        tempos_arvore[i+15] = tempo_total;
        
        inicio = tempoAtual();
        buscaBinaria(vet_ordenado,elementoBuscado);
        fim = tempoAtual();

        tempo_total = fim - inicio;
        tempos_vetor[i+15] = tempo_total;
    }
    for(int i = 0; i < 30; i++){
        printf("Tempos de busca %d:\n\n    Tempo %d Arvore: %.15lf    Tempo %d Vetor: %.15lf\n\n\n",i+1,i+1,tempos_arvore[i],i+1,tempos_vetor[i]);
    }
    double media_arvore = media(tempos_arvore,30);
    double media_vetor = media(tempos_vetor,30);

    printf("Media da arvore: %.15lf\n",media_arvore);
    printf("Media do vetor: %.15lf\n",media_vetor);

    podaArv(raiz);
    freeVetor(vet_elementos);
    freeVetor(vet_ordenado);
}