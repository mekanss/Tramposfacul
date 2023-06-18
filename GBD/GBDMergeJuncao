#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

// Definição da estrutura para a tabela Aluno
typedef struct {
    int SEQ_ALUNO;
    char CODIGO_CURSO[4];
    char NOME_ALUNO[34];
} Aluno;

// Definição da estrutura para a tabela Curso
typedef struct {
    int SEQ_CURSO;
    char CODIGO_CURSO[4];
    char NOME_CURSO[18];
} Curso;

// Função merge para o merge sort
void merge(Aluno* arr_aluno, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Arrays temporários para armazenar as metades esquerda e direita
    Aluno* left_arr = (Aluno*)malloc(n1 * sizeof(Aluno));
    Aluno* right_arr = (Aluno*)malloc(n2 * sizeof(Aluno));

    // Copiando os elementos para os arrays temporários
    for (i = 0; i < n1; i++) {
        left_arr[i] = arr_aluno[left + i];
    }
    for (j = 0; j < n2; j++) {
        right_arr[j] = arr_aluno[mid + 1 + j];
    }

    // Merge das metades esquerda e direita
    i = 0; // Índice para a metade esquerda
    j = 0; // Índice para a metade direita
    k = left; // Índice para o array original

    while (i < n1 && j < n2) {
        if (strcmp(left_arr[i].CODIGO_CURSO, right_arr[j].CODIGO_CURSO) <= 0) {
            arr_aluno[k] = left_arr[i];
            i++;
        } else {
            arr_aluno[k] = right_arr[j];
            j++;
        }
        k++;
    }

    // Copiando os elementos restantes da metade esquerda, se houver
    while (i < n1) {
        arr_aluno[k] = left_arr[i];
        i++;
        k++;
    }

    // Copiando os elementos restantes da metade direita, se houver
    while (j < n2) {
        arr_aluno[k] = right_arr[j];
        j++;
        k++;
    }

    // Liberando a memória alocada para os arrays temporários
    free(left_arr);
    free(right_arr);
}

// Função merge sort para ordenar a tabela Aluno
void merge_sort(Aluno* arr_aluno, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordenando a metade esquerda
        merge_sort(arr_aluno, left, mid);

        // Ordenando a metade direita
        merge_sort(arr_aluno, mid + 1, right);

        // Realizando o merge das duas metades
        merge(arr_aluno, left, mid, right);
    }
}

// Função merge para o merge sort da tabela Curso
void merge_curso(Curso* arr_curso, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Arrays temporários para armazenar as metades esquerda e direita
    Curso* left_arr = (Curso*)malloc(n1 * sizeof(Curso));
    Curso* right_arr = (Curso*)malloc(n2 * sizeof(Curso));

    // Copiando os elementos para os arrays temporários
    for (i = 0; i < n1; i++) {
        left_arr[i] = arr_curso[left + i];
    }
    for (j = 0; j < n2; j++) {
        right_arr[j] = arr_curso[mid + 1 + j];
    }

    // Merge das metades esquerda e direita
    i = 0; // Índice para a metade esquerda
    j = 0; // Índice para a metade direita
    k = left; // Índice para o array original

    while (i < n1 && j < n2) {
        if (strcmp(left_arr[i].CODIGO_CURSO, right_arr[j].CODIGO_CURSO) <= 0) {
            arr_curso[k] = left_arr[i];
            i++;
        } else {
            arr_curso[k] = right_arr[j];
            j++;
        }
        k++;
    }

    // Copiando os elementos restantes da metade esquerda, se houver
    while (i < n1) {
        arr_curso[k] = left_arr[i];
        i++;
        k++;
    }

    // Copiando os elementos restantes da metade direita, se houver
    while (j < n2) {
        arr_curso[k] = right_arr[j];
        j++;
        k++;
    }

    // Liberando a memória alocada para os arrays temporários
    free(left_arr);
    free(right_arr);
}

void merge_sort_curso(Curso* arr_curso, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordenando a metade esquerda
        merge_sort_curso(arr_curso, left, mid);

        // Ordenando a metade direita
        merge_sort_curso(arr_curso, mid + 1, right);

        // Realizando o merge das metades ordenadas
        merge_curso(arr_curso, left, mid, right);
    }
}


// Função para realizar a junção natural
void juncao_natural(Aluno* tabela_aluno, int tamanho_aluno, Curso* tabela_curso, int tamanho_curso) {

    // Ordenando a tabela Aluno pelo CODIGO_CURSO usando o merge sort
    merge_sort(tabela_aluno, 0, tamanho_aluno - 1);

    // Ordenando a tabela Curso pelo CODIGO_CURSO usando o merge sort
    merge_sort_curso(tabela_curso, 0, tamanho_curso - 1);

    // Realizando a junção natural
    int pos_aluno = 0, pos_curso = 0;
    while (pos_aluno < tamanho_aluno && pos_curso < tamanho_curso) {
        if (strcmp(tabela_aluno[pos_aluno].CODIGO_CURSO, tabela_curso[pos_curso].CODIGO_CURSO) < 0) {
            pos_aluno++;
        } else if (strcmp(tabela_aluno[pos_aluno].CODIGO_CURSO, tabela_curso[pos_curso].CODIGO_CURSO) > 0) {
            pos_curso++;
        } else {
            // Encontrou uma correspondência de CODIGO_CURSO
            printf("SEQ_ALUNO: %d, NOME_ALUNO: %s, NOME_CURSO: %s\n",
                tabela_aluno[pos_aluno].SEQ_ALUNO,
                tabela_aluno[pos_aluno].NOME_ALUNO,
                tabela_curso[pos_curso].NOME_CURSO);

            pos_aluno++;
            pos_curso++;
        }
    }
}

int main() {
        // Abrindo os arquivos para escrita
    FILE* file_alunoW = fopen("Tabela1.txt", "w");
    FILE* file_cursoW = fopen("Tabela2.txt", "w");
    int i;

    if (file_alunoW == NULL || file_cursoW == NULL) {
        printf("Erro ao abrir os arquivos para escrita.\n");
        return 1;
    }

    // Definindo o número de registros
    int tamanho_aluno = 5;
    int tamanho_curso = 3;

    // Escrevendo o número de registros nos arquivos
    fprintf(file_alunoW, "%d\n", tamanho_aluno);
    fprintf(file_cursoW, "%d\n", tamanho_curso);

    // Populando o arquivo da tabela Aluno
    fprintf(file_alunoW, "1 ABC Aluno1\n");
    fprintf(file_alunoW, "2 DEF Aluno2\n");
    fprintf(file_alunoW, "3 ABC Aluno3\n");
    fprintf(file_alunoW, "4 GHI Aluno4\n");
    fprintf(file_alunoW, "5 JKL Aluno5\n");

    // Populando o arquivo da tabela Curso
    fprintf(file_cursoW, "1 ABC Curso1\n");
    fprintf(file_cursoW, "2 DEF Curso2\n");
    fprintf(file_cursoW, "3 GHI Curso3\n");

    // Fechando os arquivos
    fclose(file_alunoW);
    fclose(file_cursoW);

    printf("Os arquivos foram populados com sucesso!\n");

    // Abrindo os arquivos de entrada
    FILE* file_aluno = fopen("Tabela1.txt", "r");
    FILE* file_curso = fopen("Tabela2.txt", "r");

    if (file_aluno == NULL || file_curso == NULL) {
        printf("Erro ao abrir os arquivos de entrada.\n");
        return 1;
    }

    // Alocando memória para as tabelas
    Aluno* tabela_aluno = (Aluno*)malloc(tamanho_aluno * sizeof(Aluno));
    Curso* tabela_curso = (Curso*)malloc(tamanho_curso * sizeof(Curso));

    // Lendo os registros da tabela Aluno
    for (i = 0; i < tamanho_aluno; i++) {
        fscanf(file_aluno, "%d %s %[^\n]", &tabela_aluno[i].SEQ_ALUNO, tabela_aluno[i].CODIGO_CURSO, tabela_aluno[i].NOME_ALUNO);
    }

    // Lendo os registros da tabela Curso
    for (i = 0; i < tamanho_curso; i++) {
        fscanf(file_curso, "%d %s %[^\n]", &tabela_curso[i].SEQ_CURSO, tabela_curso[i].CODIGO_CURSO, tabela_curso[i].NOME_CURSO);
    }

    // Fechando os arquivos de entrada
    fclose(file_aluno);
    fclose(file_curso);

    // Chamando a função de junção natural
    juncao_natural(tabela_aluno, tamanho_aluno, tabela_curso, tamanho_curso);

    // Liberando a memória alocada
    free(tabela_aluno);
    free(tabela_curso);

    return 0;
}
