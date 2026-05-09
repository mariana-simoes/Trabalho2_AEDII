#ifndef TAD_VETOR_H
#define TAD_VETOR_H

typedef struct {
    int *dados;
    int tamanho;
} Vetor;

Vetor* criarVetor(int tamanho);
void freeVetor(Vetor *vetor);
int randGrande();
void preencherDesordenado(Vetor *vetor);
void preencherOrdenado(Vetor *vetor);
void copiarVetor(Vetor *origem, Vetor *destino);
int obterValor(Vetor *vetor, int indice);
int buscaSequencialEmVetor(Vetor *vetor, int alvo);
int buscaBinaria(Vetor *vetor, int alvo);
void troca(int *a, int *b);
void bubbleSort(Vetor *vet);
void selectionSort(Vetor *vet);
void insertionSort(Vetor *vet);
void merge(Vetor *vet, int inicio, int meio, int fim);
void mergeSort(Vetor* vet, int inicio, int fim);
int particiona(Vetor* vet, int inicio, int fim);
void quickSort(Vetor* vet, int inicio, int fim);

#endif
