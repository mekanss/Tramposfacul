#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TAM_POPULACAO 50
#define TAXA_CRUZAMENTO 0.7
#define NUM_GERACOES 30
#define NUM_DESCENDENTES 26

struct cromossomo
{
    int vetor[16]; // vetor binario
    double valorConvertido; // valor que o vetor binario representa
    double aptidao; // aptidao baseado na funcao
};

// prototipos
void gerarPopulacaoInicial(struct cromossomo populacao[]);
double calcularAptidao(double valorConvertido);
double binarioParaNumero(int vetorBinario[], int tamanho);
void cruzamento(int pai1[], int pai2[], int filho1[], int filho2[]);
void substituirSeMelhor(struct cromossomo populacao[], double aptidaoFilho1, double aptidaoFilho2, int filho1[], int filho2[]);
double calcularDesvioPadrao(struct cromossomo populacao[], double mediaAptidao);

int main()
{
    struct cromossomo populacao[TAM_POPULACAO];
    int i;
    int geracao = 0;
    double melhorAptidao = 0.0;
    double aptidaoTotal = 0.0;
    double mediaAptidao = 0.0;

    // geracao da pop inicial, e seu fitness
    gerarPopulacaoInicial(populacao);
    for (i = 0; i < TAM_POPULACAO; i++)
    {
        populacao[i].valorConvertido = binarioParaNumero(populacao[i].vetor, 16);
        populacao[i].aptidao = calcularAptidao(populacao[i].valorConvertido);
        if (populacao[i].aptidao > melhorAptidao)
            melhorAptidao = populacao[i].aptidao;
    }

    while (geracao != NUM_GERACOES)
    {
        aptidaoTotal = 0.0;
        mediaAptidao = 0.0;
        // cruzamento acontece aqui
        for (i = 0; i < NUM_DESCENDENTES / 2; i++) // Aqui eu divido por 2, ja que em cada crossover tenho 2 filhos
        {
            // pegar 2 pais aleatorios
            int indicePai1 = rand() % TAM_POPULACAO;
            int indicePai2 = rand() % TAM_POPULACAO;

            // funcao de geracao de filho
            int filho1[16], filho2[16];
            cruzamento(populacao[indicePai1].vetor, populacao[indicePai2].vetor, filho1, filho2);

            // aptidao
            double aptidaoFilho1 = calcularAptidao(binarioParaNumero(filho1, 16));
            double aptidaoFilho2 = calcularAptidao(binarioParaNumero(filho2, 16));

            // chamada da funcao de substituicao
            substituirSeMelhor(populacao, aptidaoFilho1, aptidaoFilho2, filho1, filho2);

            // Se a aptidao de algum filho for melhor, atualzia
            if (aptidaoFilho1 > melhorAptidao)
                melhorAptidao = aptidaoFilho1;
            if (aptidaoFilho2 > melhorAptidao)
                melhorAptidao = aptidaoFilho2;
        }

        // percorre os cromossomos e calcula a media, podia ser mais eficiente
        for (i = 0; i < TAM_POPULACAO; i++)
        {
            aptidaoTotal = aptidaoTotal + populacao[i].aptidao;
        }
        mediaAptidao = aptidaoTotal / TAM_POPULACAO;

        // devio padrao
        double desvioPadrao = calcularDesvioPadrao(populacao, mediaAptidao);

        // resultados dessa geracao
        printf("Geracao %d:\n", geracao + 1);
        printf("Tamano POP: %d\n", TAM_POPULACAO);
        printf("Quantidade de filhos por geracao: %d\n", NUM_DESCENDENTES);
        printf("Melhor Aptidao: %.6f\n", melhorAptidao);
        printf("Media de Aptidao: %.6f\n", mediaAptidao);
        printf("Desvio Padrao: %.6f\n", desvioPadrao);
        printf("--------------------------\n");

        // proxima geracao
        geracao++;
    }

    return 0;
}

void gerarPopulacaoInicial(struct cromossomo populacao[])
{
    int i, j;
    for (i = 0; i < TAM_POPULACAO; i++)
    {
        for (j = 0; j < 16; j++)
        {
            populacao[i].vetor[j] = rand() % 2;
        }
    }
}

double calcularAptidao(double valorConvertido) // aqui colocamos a funcaozinha que desejamos calcular
{
    return valorConvertido * sin(10 * M_PI * valorConvertido) + 1;
}

double binarioParaNumero(int vetorBinario[], int tamanho) // transformar o vetor binario em um numero entre -1 e 2
{
    int decimal = 0;
    int i;
    for (i = 0; i < tamanho; i++)
    {
        decimal += vetorBinario[i] * pow(2, tamanho - i - 1);
    }
    return -1.0 + (3.0 / (pow(2, tamanho) - 1)) * decimal;
}

void cruzamento(int pai1[], int pai2[], int filho1[], int filho2[])
{
    int i;
    int pontoCruzamento = rand() % 16; // gerar o ponto de cruzamento sendo aleatorio

    // Filho 1
    for (i = 0; i < pontoCruzamento; i++)
    {
        filho1[i] = pai1[i];
    }
    for (i = pontoCruzamento; i < 16; i++)
    {
        filho1[i] = pai2[i];
    }

    // Filho 2
    for (i = 0; i < pontoCruzamento; i++)
    {
        filho2[i] = pai2[i];
    }
    for (i = pontoCruzamento; i < 16; i++)
    {
        filho2[i] = pai1[i];
    }
}

void substituirSeMelhor(struct cromossomo populacao[], double aptidaoFilho1, double aptidaoFilho2, int filho1[], int filho2[])
{
    int i, j;
    int filho1Substituido = 0; // 0 = filhos nao substituiram um pai
    int filho2Substituido = 0;

    // percorrimento
    for (i = 0; i < TAM_POPULACAO; i++)
    {
        // se o filho ja substituiu um pai, ele nao substitui mais outro pai
        if (filho1Substituido == 0 && aptidaoFilho1 > populacao[i].aptidao)
        {
            // Substituir pai por filho1
            for (j = 0; j < 16; j++)
            {
                populacao[i].vetor[j] = filho1[j];
            }
            populacao[i].aptidao = aptidaoFilho1;
            populacao[i].valorConvertido = binarioParaNumero(filho1, 16);
            filho1Substituido = 1;
        }

        if (filho2Substituido == 0 && aptidaoFilho2 > populacao[i].aptidao)
        {
            for (j = 0; j < 16; j++)
            {
                populacao[i].vetor[j] = filho2[j];
            }
            populacao[i].aptidao = aptidaoFilho2;
            populacao[i].valorConvertido = binarioParaNumero(filho2, 16);
            filho2Substituido = 1;
        }

        // se ambos ja substituiram um pai, sai do loop
        if (filho1Substituido && filho2Substituido)
        {
            break;
        }
    }
}

double calcularDesvioPadrao(struct cromossomo populacao[], double mediaAptidao)
{
    double somaDiferencasAoQuadrado = 0.0;
    int i;
    for (i = 0; i < TAM_POPULACAO; i++)
    {
        somaDiferencasAoQuadrado += pow(populacao[i].aptidao - mediaAptidao, 2);
    }
    if (TAM_POPULACAO <= 1)
    {
        return 0.0; // no divisao por zero
    }
    return sqrt(somaDiferencasAoQuadrado / (TAM_POPULACAO - 1));
}
