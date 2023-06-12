#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>



int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}


int knapsack(int n, int weight[], int value[], int capacity) { // Metodo Bruto com Recursao
    if (n == 0 || capacity == 0) {
        return 0; // Caso base
    }

    if (weight[n - 1] > capacity) {
        return knapsack(n - 1, weight, value, capacity); // Superou Peso
    } else {
        return max(value[n - 1] + knapsack(n - 1, weight, value, capacity - weight[n - 1]), knapsack(n - 1, weight, value, capacity)); // Senao, testa outro
    }
}


int knapsackMatriz(int n, int weight[], int value[], int capacity) {
    int i, w;
    int matrix[n + 1][capacity + 1]; // Gerando a Matriz
                                    // Aqui iremos popular a Matriz, colocando os valores de combinações em cada
                                    // casa, de modo a evitar a recombinação.
                                    // O que iremos retornar, ''Matrix[n][capacity]'' é quando a matrix fez o caminho
                                    // com a capacidade máxima
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                matrix[i][w] = 0;
            else if (weight[i - 1] <= w)
                matrix[i][w] = fmax(value[i - 1] + matrix[i - 1][w - weight[i - 1]], matrix[i - 1][w]);
            else
                matrix[i][w] = matrix[i - 1][w];
        }
    }

    return matrix[n][capacity];
}

int knapsackDinamica(int n, int weight[], int value[], int capacity) {
    int i, j;
    int K[2][capacity + 1]; // Gerando Matriz de 2

    for (i = 0; i <= n; i++) {
        for (j = 0; j <= capacity; j++) {
            if (i == 0 || j == 0) {
                K[i % 2][j] = 0;
            } else if (weight[i - 1] <= j) {
                K[i % 2][j] = max(value[i - 1] + K[(i - 1) % 2][j - weight[i - 1]], K[(i - 1) % 2][j]);
            } else {
                K[i % 2][j] = K[(i - 1) % 2][j];
            }
        }
    }

    return K[n % 2][capacity];
}


int knapsackAprox(int n, int weight[], int value[], int capacity) {
    int i, j, ord = 0;
    float density[n]; // Criando vetor densidade
    for (i = 0; i < n; i++)
        density[i] = (float)value[i] / weight[i]; // Colocando os valores no vetor
    for (i = 0; i < n; i++) { // Aqui, agora vamos ordenar o vetor PESO e VALOR baseado na densidade
        for (j = i + 1; j < n; j++) {
            if (density[i] < density[j]) {
                float temp = density[i];
                density[i] = density[j];
                density[j] = temp;

                int temp2 = weight[i];
                weight[i] = weight[j];
                weight[j] = temp2;

                int temp3 = value[i];
                value[i] = value[j];
                value[j] = temp3;
            }
        }
    }
    for (i = 0; i < n; i++) {
        if (weight[i] <= capacity) { // Por fim, iremos agora ir somando os valores mais caros, e retirando seus pesos.
            ord += value[i];
            capacity -= weight[i];
        } else {
            ord += density[i] * capacity;
            break;
        }
    }
    return ord;
}



int main() {
    int n =100;
    int i;
    srand(0);
    int capacity = 300;
    int weight[n];
    int value[n];

    for (i = 0; i < n; i++)
    {
        weight[i] = rand() % capacity;
        value[i] = rand() % capacity*10;
    }


    // KNAPSACK COM MATRIZ
    clock_t start = clock();
    int maxValue = knapsackMatriz(n, weight, value, capacity);
    double time_taken = (double)(clock() - start) / CLOCKS_PER_SEC;

    // KNAPSACK COM FORÇA BRUTA
    clock_t start2 = clock();
    int maxValue2 = knapsack(n, weight, value, capacity);
    double time_taken2 = (double)(clock() - start2) / CLOCKS_PER_SEC;

    // KNAPSACK DINAMICA
    clock_t start3 = clock();
    int maxValue3 = knapsackDinamica(n, weight, value, capacity);
    double time_taken3 = (double)(clock() - start3) / CLOCKS_PER_SEC;

    //KNAPSACK 3 APROXIMAÇÂO
    clock_t start4 = clock();
    int maxValue4 = knapsackAprox(n, weight, value, capacity);
    double time_taken4 = (double)(clock() - start4) / CLOCKS_PER_SEC;




    printf("Valor Maximo Matriz: %d\n", maxValue);
    printf("Tempo Matriz: %f Ms\n", time_taken);
    printf("Valor Maximo Forca Bruta: %d\n", maxValue2);
    printf("Tempo Forca Bruta: %f Ms\n", time_taken2);
    printf("Valor Maximo Dinamica: %d\n", maxValue3);
    printf("Tempo Dinamica: %f Ms\n", time_taken3);
    printf("Valor Maximo Aproximacao: %d\n", maxValue4);
    printf("Tempo Aprox: %f Ms\n", time_taken4);


    return 0;
}

// Nota, o aproximação ta dando erro.
