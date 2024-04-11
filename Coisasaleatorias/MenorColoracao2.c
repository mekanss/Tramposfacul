#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 23 // tamanho da matriz que sera lida do txt
#define MAX_POP 50
#define MAX_GERACOES 50
#define MUT_CHANCE 5
#define seed 1234


int ligacoes[MAX][MAX];
// vertices[1][0,1,1,0,1] significa que o vertice 1 tem ligacao com o vertice 2,3 e 5

// ESTRUTURA DO CROMOSSOMO QUE GUARDA AS CORES USADAS E A FITNESS
// SE O CROMOSSOMO POR EX É: [1,3,4,5] SIGNIFICA QUE ELE USOU A COR 1 NO VERTICE 1, A 3 NO VERTICE 2 E ASSIM POR DIANTE
struct cromossomo
{
    int vetor[MAX];
    int fitness;
};

int calcularFitness(struct cromossomo cromossomo, int ligacoes[MAX][MAX]) {
    int fitness = 0;
    int i,j;
    int cores[MAX] = {0}; // NO PIOR CASO, O NUMERO DE CORES É O MESMO DE VERTICES, LOGO MAX = CORES, E ELAS VAO DE 0-9

    // ITERAR SOBRE O VETOR
    for (i = 0; i < MAX; i++)
    {
        // VERIFICANDO SE A COR DO VERTICE E IGUAL A UMA DOS LIGADOS
        for (j = i + 1; j < MAX; j++) { // ESSE i + 1 É APENAS PQ [1][1] É LIGACAO CONSIGO MESMO, AI É MENOS EFICIENTE.
            if (ligacoes[i][j] == 1 && cromossomo.vetor[i] == cromossomo.vetor[j]) { // SE FOR 1 NA MATRIZ (TEM LIGACAO) E A COR ENTRE ESSES 2 VERTICES (I E J) FOREM IGUAIS...
                fitness += 1000; // PUNICAO NA FITNESS POR TER COR IGUAL
            }
        }

        // COMO É COLORIR MINIMAMENTE, CADA COR NOVA TEM UMA PENALIDADE
        if (cores[cromossomo.vetor[i]] != 1)
        {
            cores[cromossomo.vetor[i]] = 1; // AQUI EU COLOCO 1 PARA A COR QUE ESTA NA POSICAO VETOR[I] NO CORES[MAX] OU SEJA, SE EM VETOR[I] TEM UM 3, NA POSICAO CORES[3] AGORA TERA UM 1!
            fitness += 1; // PUNE EM 1 POR UTILIZAR UMA COR NAO DETECTADA
        }
    }

    return fitness;
}

void iniciarVetorAleatoriamente(struct cromossomo *cromossomo, int ligacoes[MAX][MAX]) {
    int i;
    do
    {
        for (i = 0; i < MAX; i++)
        {
            cromossomo->vetor[i] = rand() % MAX; // COLOCA DE 0 A MAX-1 COMO COR!
        }
    } while (calcularFitness(*cromossomo,ligacoes) > 1000);
}







// CROSSOVER
void crossover(struct cromossomo *populacao, int tamanhoPopulacao, int ligacoes[MAX][MAX]) {
    int i, j;
    int indice_pai1, indice_pai2;

    // PEGAR 2 PAIS RANDONS QUE NAO SEJAM IGUAIS
    indice_pai1 = rand() % tamanhoPopulacao;
    do {
        indice_pai2 = rand() % tamanhoPopulacao;
    } while (indice_pai1 == indice_pai2);

    // COMPARA E MANTEM O QUE TEM MENOR FITNESS JA QUE QUEREMOS MINIMIZAR O PROBLEMA (TORNEIO)
    if (populacao[indice_pai1].fitness > populacao[indice_pai2].fitness) {
        indice_pai1 = indice_pai2;
    }

    // QUEREMOS 2 PAIS...
    for (i = 1; i < tamanhoPopulacao / 2; i++) {
        do {
            j = rand() % tamanhoPopulacao;
        } while (j == indice_pai1 || j == indice_pai2);

        if (populacao[j].fitness < populacao[indice_pai1].fitness) {
            indice_pai1 = j;
        }
    }

    // CRUZAMENTO ALEATORIO, AQUI NO ARTIGO O CARA VERIFICAVA SE O CRUZAMENTO ERA VALIDO, OU SEJA TESTAVA O FITNESS ANTES
    int pontoCorte = rand() % MAX;

    // CRIANDO 2 CHILDS
    struct cromossomo filho1, filho2;
    for (i = 0; i < pontoCorte; i++) {
        filho1.vetor[i] = populacao[indice_pai1].vetor[i];
        filho2.vetor[i] = populacao[indice_pai2].vetor[i];
    }
    for (i = pontoCorte; i < MAX; i++) {
        filho1.vetor[i] = populacao[indice_pai2].vetor[i];
        filho2.vetor[i] = populacao[indice_pai1].vetor[i];
    }

    // METER RADIAÇÂO NAS CHILDREN (MUTACAO COM MUT_CHANCE)
    for (i = 0; i < MAX; i++) {
        if (rand() % 100 < MUT_CHANCE) { // VER SE ROLA MUTACAO
            if (rand() % 2 == 0 && filho1.vetor[i] < MAX - 1) { // POR FIM 50% DE CHANCE QUE AUMENTA EM 1 O VALOR
                filho1.vetor[i]++;
            } else if (filho1.vetor[i] > 0) { // OU DIMINUI EM 1
                filho1.vetor[i]--;
            }
        }
        if (rand() % 100 < MUT_CHANCE) { // MUTACAO NO SEGUINDO FILHO AGORA, SEPA Q DAVA PRA SER MAIS EFICIENTE
            if (rand() % 2 == 0 && filho2.vetor[i] < MAX - 1) {
                filho2.vetor[i]++;
            } else if (filho2.vetor[i] > 0) {
                filho2.vetor[i]--;
            }
        }
    }

    // CALCULAR O FITGraças aos padrões e estratégias usadas nesse algoritmo, um bom resultado foi conseguido, como mostram as próximas imagens (figure 6-10) em famosos grafos, como o myciel3 e myciel4. No caso do primeiro, a execução demorou 0,443 segundos, no segundo 1,443. No entanto, o tempo para achar o ótimo foi menor ainda, visto que não foi a geração final.

Além disso, essa matriz genérica foi utilizada em duas versões: 10x10 e 30x30. Ambas estarão disponíveis no github mencionado.
    filho1.fitness = calcularFitness(filho1, ligacoes);
    filho2.fitness = calcularFitness(filho2, ligacoes);

    // SUBSTITUIR O CARA COM MAIOR FITNESS (O PIOR) PELO MELHOR FILHO
    int indice_maior_fitness = 0;
    for (i = 1; i < tamanhoPopulacao; i++) {
        if (populacao[i].fitness > populacao[indice_maior_fitness].fitness) {
            indice_maior_fitness = i;
        }
    }
    if (filho1.fitness < filho2.fitness) {
        populacao[indice_maior_fitness] = filho1;
    } else {
        populacao[indice_maior_fitness] = filho2;
    }
}

int main() {
    int i, j;
    int geracoes = 0;
    struct cromossomo cromossomos[MAX_POP];
    srand(seed);

    // ABRIR ARQUIVO E PRINTAR AS COISAS
    FILE *arquivo;
    arquivo = fopen("matriz.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // LENDO MATRIZ DO ARQUIVO
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            fscanf(arquivo, "%d", &ligacoes[i][j]);
        }
    }

    // FECHAR ARQUIVO
    fclose(arquivo);

    // PRINT NA MATRIZ
    printf("\nMatriz de adjacencia lida:\n");
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            printf("%d ", ligacoes[i][j]);
        }
        printf("\n");
    }

    // MOSTRAR AS LIGACOES DO VERTICES...
    printf("\nLigacoes dos vertices:\n");
    for (i = 0; i < MAX; i++) {
        printf("vertices[%d][", i+1);
        for (j = 0; j < MAX; j++) {
            if (ligacoes[i][j] == 1) {
                printf("%d, ", j+1);
            }
        }
        printf("\b\b]\n");
    }

    // AQUI QUE A MAGIA ACONTECE...
    for (i = 0; i < MAX; i++)
    {
        iniciarVetorAleatoriamente(&cromossomos[i], ligacoes);
        cromossomos[i].fitness = calcularFitness(cromossomos[i], ligacoes);
        printf("Cromossomo: ");
        for (j = 0; j<MAX; j++)
        {
            printf("%d" ,cromossomos[i].vetor[j]);
        }
        printf(" fitness do cromossomo: %d\n", cromossomos[i].fitness);
    }


    // CRUZAMENTO
    while (geracoes < MAX_GERACOES)
    {
        printf("Geracao: %d\n" ,geracoes+1);
        // CROSSOVER ROLA MAX/2 VEZES, OU SEJA TEREMOS MAX/2 CHILDREN
        for (i = 0; i < MAX / 2; i++) {
            crossover(cromossomos, MAX, ligacoes);
        }

        printf("Populacao apos crossover:\n");
        for (i = 0; i < MAX; i++) {
            printf("Cromossomo: ");
            for (j = 0; j<MAX; j++)
            {
                printf("%d " ,cromossomos[i].vetor[j]);
            }
            printf(" - Fitness: %d\n", cromossomos[i].fitness);
        }
        geracoes++;
    }

    return 0;
}

