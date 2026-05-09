#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TAD_arv.h"
#include <locale.h>

#define qtd_pacotes 20 // pacotes únicos
#define qtd_duplicatas 10 // retransmissões (pacotes extras)
#define arquivo_saida "arquivo_montado.txt"

static const char *conteudo[] = {
    "a", "b", "c", "d", "e",
    "f", "g", "h", "i", "j",
    "k", "l", "m", "n", "o",
    "p", "q", "r", "s", "t"
};

// simulação de pacotes que chegam "quase" na ordem certa
static void embaralhar(int *v, int n) { // int *v -> primeiro elemento do vetor
    for (int i = 0; i < n; i++) {
        v[i] = i + 1; 
    } 

    int trocas = n / 4; // ~25 % de desordem
    for (int t = 0; t < trocas; t++) { 
        int a = rand() % n;
        int b = rand() % n;
        int tmp = v[a]; v[a] = v[b]; v[b] = tmp;
    }
}

int main () {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand((unsigned) time(NULL));

    arv *raiz = inicializa();

    // IDs dos pacotes em ordem de chegada (parcialmente ordenada)
    int ids[qtd_pacotes];
    embaralhar(ids, qtd_pacotes);

    int limDup = (qtd_pacotes * qtd_duplicatas) / 100;
    int dupEnviadas = 0; 

    printf("SIMULAÇÃO DE RECEPÇÃO DE PACOTES\n\n");

    for (int i = 0; i < qtd_pacotes; i++) {
        int id = ids[i];
        const char *dado = conteudo[id - 1];  // id vai de 1 até 20

        printf("ID=%03d  dado=\"%s\"\n", id, dado);
        raiz = insereArv(raiz, id, dado);

        // retransmissão: ocasionalmente reenviar um pacote já recebido
        //  limite / contador a relação de dupEnviadas e limDup
        if (dupEnviadas < limDup && i > 0 && rand() % 3 == 0) {
            int idDup = ids[rand() % i];   /* escolhe um dos já recebidos */
            printf("  ↺ Retransmissão  ID=%03d (duplicata — descartada)\n", idDup);
            raiz = insereArv(raiz, idDup, conteudo[idDup - 1]);
            dupEnviadas++;
        }
    }

    //mostra os percursos
    printf("\nPré-ordem\n");
    preFixComDado(raiz);

    printf("\n\n Em-ordem (= arquivo montado)\n");
    centralComDado(raiz);

    printf("\n\nPós-ordem\n");
    posFixComDado(raiz);
    printf("\n");

    //exemplo
    int alvo = ids[qtd_pacotes / 2];
    arv *encontrado = buscaArv(raiz, alvo); // Faz uma busca binária com o valor alvo

    // Operador ternário - condição ? valor_se_verdadeiro : valor_se_falso
    printf("\nBusca pelo pacote ID=%03d: %s\n",alvo, encontrado ? "ENCONTRADO" : "não encontrado");
    
    FILE *arq = fopen(arquivo_saida, "w");
    if (arq == NULL) {
        fprintf(stderr, "Erro ao criar '%s'.\n", arquivo_saida);
    } else {
        fprintf(arq, "=== Arquivo montado a partir dos pacotes recebidos ===\n\n");
        montarArquivo(raiz, arq);
        fclose(arq);
        printf("\nArquivo '%s' gerado com sucesso!\n", arquivo_saida);
    }

    raiz = podaArv(raiz);
    return 0;
}