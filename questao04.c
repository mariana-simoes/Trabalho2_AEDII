
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_arv.h"
#include "TAD_AVL.h"
#include <locale.h>
#include "estatisticas.h"

#define N 1000000
#define EXECUCOES 10  
#define CONSULTAS 30 


//Gera um vetor de elementos unicos a partir de uma seed
static void gerarElementos(int v[], int n, int seed){
    for(int i = 0; i < n; i++){
    v[i] = i;
}
    srand(seed);
    for(int i=n-1; i>0; i--){
        int j = rand() % (i+1);
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}

int main(){
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // acumuladores entre execuções, de tempo e altura das árvores
    double tCriacaoAVL[EXECUCOES], tCriacaoBST[EXECUCOES];
    double tBuscaAVL [EXECUCOES], tBuscaBST [EXECUCOES];
    int altAVL [EXECUCOES], altBST [EXECUCOES];

    // gerando sequencia de N elementos
    int *elementos = malloc(N * sizeof(int)); //vetor com o tamanho de N
    gerarElementos(elementos, N, 42); //preenche o vetor

    //posiciona 30 chaves de busca igualmente espaçadas no vetor, logo sempre existem nas árvores. 
    int chaves[CONSULTAS];
    for (int i = 0; i < CONSULTAS; i++){
        chaves[i] = elementos[(long)i * N / CONSULTAS];
        // a operacao é convertida para long para evitar overflow

    }
   
    //10 repetições
   for (int exec = 0; exec < EXECUCOES; exec++) {
 
        printf("Execução %2d \n", exec + 1);
 
        //Criação da AVL
        avl *raizAVL = NULL;
        double t0 = tempoAtual();
        for (int i = 0; i < N; i++)
            raizAVL = inserir(raizAVL, elementos[i]);
        tCriacaoAVL[exec] = tempoAtual() - t0;
        altAVL[exec] = (raizAVL != NULL) ? raizAVL->altura : -1;
 
        //Criação da binária
        arv *raizBST = inicializa();
        t0 = tempoAtual();
        for (int i = 0; i < N; i++) {
            char buf[TAM];
            snprintf(buf, TAM, "%d", elementos[i]);   //dado = repr. textual
            raizBST = insereArv(raizBST, elementos[i], buf);
        }
        tCriacaoBST[exec] = tempoAtual() - t0;
        altBST[exec] = alturaArv(raizBST);

        //30 buscas na AVL
        double temposBAVL[CONSULTAS];
        for (int c = 0; c < CONSULTAS; c++) {
            t0 = tempoAtual();
            (void) busca(raizAVL, chaves[c]);
            temposBAVL[c] = tempoAtual() - t0;
        }
        double mBAVL = media(temposBAVL, CONSULTAS);
        double dBAVL = desvioPadrao(temposBAVL, CONSULTAS, mBAVL);
        tBuscaAVL[exec] = mBAVL;
 
        // 30 buscas na BST
        double temposBBST[CONSULTAS];
        for (int c = 0; c < CONSULTAS; c++) {
            t0 = tempoAtual();
            (void) buscaArv(raizBST, chaves[c]);
            temposBBST[c] = tempoAtual() - t0;
        }
        double mBBST = media(temposBBST, CONSULTAS);
        double dBBST = desvioPadrao(temposBBST, CONSULTAS, mBBST);
        tBuscaBST[exec] = mBBST;
 
        //Relatório da execução 
        printf("  Criação  AVL : %9.3f ms  |  altura = %d\n",
               tCriacaoAVL[exec] * 1e3, altAVL[exec]);
        printf("  Criação  BST : %9.3f ms  |  altura = %d\n",
               tCriacaoBST[exec] * 1e3, altBST[exec]);
        printf("  Busca    AVL : média = %.4f µs  dp = %.4f µs  (%d consultas)\n",
               mBAVL * 1e6, dBAVL * 1e6, CONSULTAS);
        printf("  Busca    BST : média = %.4f µs  dp = %.4f µs  (%d consultas)\n\n",
               mBBST * 1e6, dBBST * 1e6, CONSULTAS);
 
        //libera memória antes da próxima rodada
        podaAvl(raizAVL);
        podaArv(raizBST);
    }

    //RESUMO FINAL (média ± dp entre as 10 execuções)
    double mCrAVL = media(tCriacaoAVL, EXECUCOES);
    double mCrBST = media(tCriacaoBST, EXECUCOES);
    double mBuAVL = media(tBuscaAVL, EXECUCOES);
    double mBuBST = media(tBuscaBST, EXECUCOES);
 
    double dCrAVL = desvioPadrao(tCriacaoAVL, EXECUCOES, mCrAVL);
    double dCrBST = desvioPadrao(tCriacaoBST, EXECUCOES, mCrBST);
    double dBuAVL = desvioPadrao(tBuscaAVL, EXECUCOES, mBuAVL);
    double dBuBST = desvioPadrao(tBuscaBST, EXECUCOES, mBuBST);
 
    /* altura mínima e máxima ao longo das execuções */
    int minAltAVL = altAVL[0], maxAltAVL = altAVL[0];
    int minAltBST = altBST[0], maxAltBST = altBST[0];
    for (int i = 1; i < EXECUCOES; i++) {
        if (altAVL[i] < minAltAVL) minAltAVL = altAVL[i];
        if (altAVL[i] > maxAltAVL) maxAltAVL = altAVL[i];
        if (altBST[i] < minAltBST) minAltBST = altBST[i];
        if (altBST[i] > maxAltBST) maxAltBST = altBST[i];
    }

    printf(" RESUMO FINAL\n");
 
    printf("\nAltura (min – max nas %d execuções):\n", EXECUCOES);
    printf("AVL: %d – %d\n", minAltAVL, maxAltAVL);
    printf("BST: %d – %d\n", minAltBST, maxAltBST);
 
    printf("\nTempo de criação — média ± dp  (ms):\n");
    printf("AVL: %9.3f ± %.3f\n", mCrAVL * 1e3, dCrAVL * 1e3);
    printf("BST: %9.3f ± %.3f\n", mCrBST * 1e3, dCrBST * 1e3);
    printf("→ A BST é %.2fx %s que a AVL na criação.\n",
           (mCrAVL > mCrBST) ? mCrAVL / mCrBST : mCrBST / mCrAVL,
           (mCrAVL > mCrBST) ? "mais rápida" : "mais lenta");
 
    printf("\nTempo de busca (média das 30 consultas) — média ± dp  (µs):\n");
    printf("AVL : %9.4f ± %.4f\n", mBuAVL * 1e6, dBuAVL * 1e6);
    printf("BST : %9.4f ± %.4f\n", mBuBST * 1e6, dBuBST * 1e6);
    printf("→ A AVL é %.2fx %s que a BST na busca.\n",
           (mBuBST > mBuAVL) ? mBuBST / mBuAVL : mBuAVL / mBuBST,
           (mBuBST > mBuAVL) ? "mais rápida" : "mais lenta");
 
    free(elementos);
    return 0;
}