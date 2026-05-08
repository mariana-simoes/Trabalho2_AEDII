#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TAD_arv.h"
#include <locale.h>

#define qtd_pacotes 20 // aqui, seriam os pacotes únicos
#define qtd_duplicatas 10 // Aqui, seriam as retransmissões (pacotes extras)
#define arquivo_saida "arquivo_montado.txt"

static const char *conteudo[] = {
    "a", "b", "c", "d", "e",
    "f", "g", "h", "i", "j",
    "k", "l", "m", "n", "o",
    "p", "q", "r", "s", "t"
};

// Aqui, simulam pacotes que chegam "quase" na ordem certa. Ordena e depois randomiza em 25%.
static void embaralhar(int *v, int n) { // int *v seria o primeiro elemento do vetor, enquanto n é o seu tamanho
    // começa ordenado
    for (int i = 0; i < n; i++) {
        v[i] = i + 1; // o vetor é preenchido aqui. Começa com i + 1 pq os IDs começam do 1, e não do 0
    } 

    int trocas = n / 4;           // ~25 % de desordem
    for (int t = 0; t < trocas; t++) { // Sorteia dois índices aleatórios entre 0 e n-1. O % faz com que o resultado fique dentro dos limites do vetor
        int a = rand() % n;
        int b = rand() % n;
        int tmp = v[a]; v[a] = v[b]; v[b] = tmp; // ocorre a troca em si.
    }
}



int main () {
    setlocale(LC_ALL, "");
    srand((unsigned) time(NULL));

    arv *raiz = inicializa();

    // IDs dos pacotes em ordem de chegada (parcialmente ordenada)
    int ids[qtd_pacotes];
    embaralhar(ids, qtd_pacotes);


    // quantas duplicatas serão enviadas durante a simulação. É uma regra de três pra converter a porcentagem em número
    int limDup = (qtd_pacotes * qtd_duplicatas) / 100;
    int dupEnviadas = 0; // É um contador que começa em zero e é incrementado toda vez que uma duplicata é enviada.
     // É comparado com limDup no loop para garantir que o número de retransmissões não ultrapasse o limite calculado

    printf("SIMULAÇÃO DE RECEPÇÃO DE PACOTES\n\n");

    // Essa parte ficou bem confusa... Tive que pesquisar bastante, mas confesso que não
    // entendi muito bem... Até a apresentação, eu entendo (apagar esse comentário depois)

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
            // Envia a duplicata
            dupEnviadas++;
        }
    }

    // Mostra os percursos
    printf("\nPré-ordem\n");
    preFix(raiz);

    printf("\n\n Em-ordem (= arquivo montado)\n");
    inFix(raiz);

    printf("\n\nPós-ordem\n");
    posFix(raiz);
    printf("\n");

    // EXEMPLOOOOOOOOOO AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA //
    // Pega o elemento do meio do vetor de IDs como alvo de busca como exemplo. Com qtd_pacotes sendo 20, teremos ids[10]
    int alvo = ids[qtd_pacotes / 2];
    arv *encontrado = buscaArv(raiz, alvo); // Faz uma busca binária com o valor alvo. Se encontrar, armazena o valor no "encontrado".

    // Operador ternário - - - - condição ? valor_se_verdadeiro : valor_se_falso
    printf("\nBusca pelo pacote ID=%03d: %s\n",alvo, encontrado ? "ENCONTRADO" : "não encontrado");

    
    /* ── gera arquivo montado ── */
    FILE *arq = fopen(arquivo_saida, "w");
    if (arq == NULL) {
        fprintf(stderr, "Erro ao criar '%s'.\n", arquivo_saida);
    } else {
        fprintf(arq, "=== Arquivo montado a partir dos pacotes recebidos ===\n\n");
        montarArquivo(raiz, arq);
        fclose(arq);
        printf("\nArquivo '%s' gerado com sucesso!\n", arquivo_saida);
    }

    /* ── libera memória ── */
    raiz = podaArv(raiz);
    return 0;
}