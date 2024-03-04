#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define MAX_POP 10


int ligacoes[MAX][MAX];
// vertices[1][0,1,1,0,1] significa que o vertice 1 tem ligacao com o vertice 2,3 e 5

// ESTRUTURA DO CROMOSSOMO QUE GUARDA AS CORES USADAS E A FITNESS
// SE O CROMOSSOMO POR EX É: [1,3,4,5] SIGNIFICA QUE ELE USOU A COR 1 NO VERTICE 1, A 3 NO VERTICE 2 E ASSIM POR DIANTE
struct cromossomo
{
    int vetor[MAX];
    int fitness;
};


void iniciarVetorAleatoriamente(struct cromossomo *cromossomo) {
    int i;
    for (i = 0; i < MAX; i++) {
        cromossomo->vetor[i] = rand() % MAX; // COLOCA DE 0 A MAX-1 COMO COR!
    }
}




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
        if (cores[cromossomo.vetor[i]] == 0)
        {
            cores[cromossomo.vetor[i]] = 1; // AQUI EU COLOCO 1 PARA A COR QUE ESTA NA POSICAO VETOR[I] NO CORES[MAX] OU SEJA, SE EM VETOR[I] TEM UM 3, NA POSICAO CORES[3] AGORA TERA UM 1!
            fitness += 2; // PUNE EM 2 POR UTILIZAR UMA COR NAO DETECTADA
        }
        else
            fitness += 1; // AQUI PENSO EM TIRAR ESSA PUNICAO PADRAO.
    }

    return fitness;
}

int main() {
    int i, j;
    struct cromossomo cromossomos[MAX_POP];

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

    // MOSTRAR AS LIGACOES DO VETOR...
    printf("\nLigacoes armazenadas no vetor:\n");
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
        iniciarVetorAleatoriamente(&cromossomos[i]);
        cromossomos[i].fitness = calcularFitness(cromossomos[i], ligacoes);
        printf("Cromossomo: ");
        for (j = 0; j<MAX; j++)
        {
            printf("%d" ,cromossomos[i].vetor[j]);
        }
        printf(" fitness do cromossomo: %d\n", cromossomos[i].fitness);

    }

    return 0;
}

