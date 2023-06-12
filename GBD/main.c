// Programa de inserção de dados, e depois buscas, tanto aleatória e sequencial...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define REG_SIZE 100 // tamanho fixo do registro
#define NSEQ_SIZE 4 // tamanho em bytes do campo NSEQ

typedef struct {
    int NSEQ;
    char TEXT[96];
} registro;

// função para gerar texto aleatório
void generate_random_text(char* text, int size) {
    int i;
    for (i = 0; i < size; i++) {
        text[i] = 'A' + rand() % 26; // gera letras maiúsculas aleatórias
    }
    text[size - 1] = '\0'; // adiciona o caractere nulo ao final da string
}

// operação CREATE_HEAP_FILE
void create_heap_file(int nro_de_registros, char* file_name) {
    int i;
    srand(time(NULL)); // inicializa a semente do gerador de números aleatórios

    // abre o arquivo para escrita binária
    FILE* file = fopen(file_name, "wb");
    if (file == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return;
    }

    // escreve os registros no arquivo
    for (i = 0; i < nro_de_registros; i++) {
        int nseq = i;
        char text[96];
        generate_random_text(text, 96);

        // cria o registro
        registro reg;
        reg.NSEQ = nseq;
        strncpy(reg.TEXT, text, sizeof(reg.TEXT) - 1);

        // escreve o registro no arquivo
        fwrite(&reg, sizeof(registro), 1, file);
    }

    // fecha o arquivo
    fclose(file);
}

// operação READ_RANDOM
void read_random(char* file_name, int nseq) {
    registro reg;
    int found = 0;

    // abre o arquivo para leitura binária
    FILE* file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // busca o registro com o NSEQ desejado
    while (!found && fread(&reg, sizeof(registro), 1, file) == 1) {
        if (reg.NSEQ == nseq) {
            found = 1;
            printf("Registro encontrado:\n");
            printf("NSEQ: %d\n", reg.NSEQ);
            printf("TEXT: %s\n", reg.TEXT);
        }
    }

    // fecha o arquivo
    fclose(file);

    // verifica se o registro não foi encontrado
    if (!found) {
        printf("Registro não encontrado!\n");
    }
}


void isrt_at_end(const char* filename) {
    // abre o arquivo no modo leitura e escrita
    FILE* file = fopen(filename, "rb+");
    if (file == NULL) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    // move o cursor para o final do arquivo
    fseek(file, 0, SEEK_END);

    // cria um novo registro com NSEQ = último NSEQ + 1
    int last_nseq = -1;
    fseek(file, -(int)(sizeof(int) + sizeof(char) * (REG_SIZE - NSEQ_SIZE)), SEEK_END);
    fread(&last_nseq, sizeof(int), 1, file);
    registro new_reg;
    new_reg.NSEQ = last_nseq + 1;
    generate_random_text(new_reg.TEXT, sizeof(new_reg.TEXT));

    // escreve o novo registro no final do arquivo
    fwrite(&new_reg, sizeof(registro), 1, file);

    // fecha o arquivo
    fclose(file);
}


void update_random(const char* filename, int nseq, const char* new_text) {
    // abre o arquivo no modo leitura e escrita
    FILE* file = fopen(filename, "rb+");
    if (file == NULL) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    // procura o registro com o NSEQ especificado
    bool found = false;
    registro reg;
    while (fread(&reg, sizeof(registro), 1, file)) {
        if (reg.NSEQ == nseq) {
            found = true;
            break;
        }
    }

    // atualiza o registro se encontrado
    if (found) {
        strncpy(reg.TEXT, new_text, sizeof(reg.TEXT) - 1);
        fseek(file, -((int)sizeof(registro)), SEEK_CUR);
        fwrite(&reg, sizeof(registro), 1, file);
    }

    // fecha o arquivo
    fclose(file);

    // verifica se o registro foi encontrado
    if (!found) {
        printf("Registro não encontrado!\n");
    }
}

void delete_random(const char* filename, int nseq) {
    // abre o arquivo no modo leitura e escrita
    FILE* file = fopen(filename, "rb+");
    if (file == NULL) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    // procura o registro com o NSEQ especificado
    bool found = false;
    registro reg;
    while (fread(&reg, sizeof(registro), 1, file)) {
        if (reg.NSEQ == nseq) {
            found = true;
            // marca o registro como excluído
            reg.NSEQ *= -1;
            fseek(file, -((int)sizeof(registro)), SEEK_CUR);
            fwrite(&reg, sizeof(registro), 1, file);
            break;
        }
    }

    // fecha o arquivo
    fclose(file);

    // verifica se o registro foi encontrado
    if (!found) {
        printf("Registro não encontrado!\n");
    }
}

int varredura_sequencial(char *filename, int page_size) {
    FILE *fp;
    int i = 0;
    registro *buffer;
    int valid_records = 0, pages_read = 0;
    clock_t start_time, end_time;
    double total_time;

    // abrindo o arquivo para leitura em modo binário
    if ((fp = fopen(filename, "rb")) == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // alocando memória para o buffer de leitura
    buffer = (registro*) malloc(page_size * REG_SIZE);
    if (buffer == NULL) {
        printf("Erro ao alocar memória para o buffer.\n");
        exit(1);
    }

    // iniciando a contagem do tempo de processamento
    start_time = clock();

    // lendo as páginas do arquivo
    while (!feof(fp)) {
        int records_read = fread(buffer, REG_SIZE, page_size, fp);
        pages_read++;

        // verificando se os registros lidos são válidos
        for (i = 0; i < records_read; i++) {
            if (buffer[i].NSEQ >= 0) {
                valid_records++;
            }
        }
    }

    // finalizando a contagem do tempo de processamento
    end_time = clock();

    // calculando o tempo total de processamento
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    // fechando o arquivo e liberando a memória alocada
    fclose(fp);
    free(buffer);

    // imprimindo os resultados
    printf("Quantidade de registros válidos: %d\n", valid_records);
    printf("Número de páginas lidas: %d\n", pages_read);
    printf("Tempo de processamento: %lf segundos\n", total_time);

    return valid_records;
}

void acesso_aleatorio(char *filename, int num_records) {
    FILE *fp;
    registro buffer;
    int i;
    int valid_reads = 0, invalid_reads = 0, random_key, total_reads;
    clock_t start_time, end_time;
    double total_time;

    // abrindo o arquivo para leitura em modo binário
    if ((fp = fopen(filename, "rb")) == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // iniciando a contagem do tempo de acesso aleatório
    start_time = clock();

    // realizando o acesso aleatório aos registros do arquivo
    srand(time(NULL)); // inicializando a semente do gerador de números aleatórios
    for (i = 0; i < num_records; i++) {
        // gerando uma chave aleatória
        random_key = rand() % num_records;

        // posicionando o ponteiro de leitura do arquivo no registro escolhido
        fseek(fp, random_key * REG_SIZE, SEEK_SET);

        // lendo o registro escolhido
        total_reads++;
        fread(&buffer, REG_SIZE, 1, fp);

        // verificando se o registro lido é válido
        if (buffer.NSEQ >= 0) {
            valid_reads++;
        } else {
            invalid_reads++;
        }
    }

    // finalizando a contagem do tempo de acesso aleatório
    end_time = clock();

    // calculando o tempo total de acesso aleatório
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    // fechando o arquivo
    fclose(fp);

    // imprimindo os resultados
    printf("Tempo de acesso aleatório: %lf segundos\n", total_time);
    printf("Quantidade de leituras de registros válidos: %d\n", valid_reads);
    printf("Quantidade de leituras de registros inválidos: %d\n", invalid_reads);
    printf("Total de leituras realizadas: %d\n", total_reads);
}



int main() {
    srand(time(NULL)); // inicializa a semente aleatória
    char filename[] = "heapfile.bin"; // alterado para array de char
    int nseq = 0;
    int option = 0;

    printf("Escolha uma opcao:\n");
    printf("1 - Criar arquivo com n registros\n");
    printf("2 - Ler registro aleatorio do arquivo\n");
    printf("3 - Inserir registro no final do arquivo\n");
    printf("4 - Atualizar um registro\n");
    printf("5 - Deletar um registro\n");
    printf("6 - Fazer testes\n");
    printf("7 - Fazer testes aleatorios\n");
    printf("Opcao: ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            // cria um arquivo com nseq registros
            printf("Digite o numero de registros: ");
            scanf("%d", &nseq);
            create_heap_file(nseq, filename);
            printf("Arquivo criado com sucesso\n");
            break;
        case 2:
            // lê um registro aleatório do arquivo
            printf("Digite o NSEQ do registro a ser lido: ");
            scanf("%d", &nseq);
            read_random(filename, nseq);
            break;
        case 3:
            // insere registro aleatorio no fim do arquivo
            isrt_at_end(filename);
            break;
        case 4:
            // atualiza um registro com novo texto
            printf("Digite o NSEQ do registro a ser atualizado: ");
            scanf("%d", &nseq);
            char new_text[REG_SIZE];
            printf("Digite o novo texto: ");
            scanf("%s", new_text);
            update_random(filename, nseq, new_text);
            printf("Registro atualizado com sucesso\n");
            break;
        case 5:
            // deleta um registro
            printf("Digite o NSEQ do registro a ser deletado: ");
            scanf("%d", &nseq);
            delete_random(filename, nseq);
            printf("Registro deletado com sucesso\n");
            break;
        case 6:
            printf("Experimento com blocos de 1 registro:\n");
            varredura_sequencial("heapfile.bin", 1);
            printf("\n");
            printf("Experimento com blocos de 1.000 registros:\n");
            varredura_sequencial("heapfile.bin", 1000);
            printf("\n");
            break;
        case 7:
            printf("Experimento com 70000000 registros:\n");
            acesso_aleatorio("heapfile.bin", 70000000);
            printf("\n");
            break;
        default:
            printf("Opcao invalida\n");
            break;
    }


    return 0;
}
