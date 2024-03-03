#include <stdio.h>
#include <string.h>

#define TAMANHO_MAXIMO 500
#define MAX_ID_LENGTH 20
#define MAX_SYMBOLS 40

char tabela_de_simb[MAX_SYMBOLS][MAX_ID_LENGTH + 1];

// VENDO SE JA EXISTE O TAL DO ID
int existe_na_tabela(char *identificador) {
    int i;
    for (i = 0; i < MAX_SYMBOLS; i++) {
        if (strcmp(tabela_de_simb[i], identificador) == 0) {
            return 1;
        }
    }
    return 0;
}

// SE NAO EXISTE, ADICIONA NA TABELA
int adicionar_na_tabela(char *identificador) {
    int i;
    for (i = 0; i < MAX_SYMBOLS; i++) {
        if (tabela_de_simb[i][0] == '\0') { // SE TA VAZIO??
            strcpy(tabela_de_simb[i], identificador);
            return 1;
        }
    }
    return 0;
}


void processar_identificador(char *conteudo, int tamanho) {
    char identificador[MAX_ID_LENGTH + 1]; // CARACTERE NULO, TALVEZ ISSO DAQUI NAO PRECISA
    strncpy(identificador, conteudo, tamanho);
    identificador[tamanho] = '\0'; // TALVEZ ISSO NAO PRECISA

    if (!existe_na_tabela(identificador)) {
        if (!adicionar_na_tabela(identificador)) {
            printf("Tabela de simbolos cheia!\n");
        }
    }

    printf(" identificador: %s\n", identificador);
}


int main() {
    FILE *arquivo;
    char conteudo[TAMANHO_MAXIMO];
    int tamanho_arquivo;
    int i = 0;
    int z = 0;
    int j;
    char temp[MAX_ID_LENGTH];
    int estado = 0;

    // Abre o arquivo para leitura
    arquivo = fopen("arquivo.txt", "r");

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Lê o conteúdo do arquivo para a string
    tamanho_arquivo = fread(conteudo, sizeof(char), TAMANHO_MAXIMO, arquivo);

    // Fecha o arquivo
    fclose(arquivo);

    // Uma mudança sacana pra esse algoritmo funcionar
    conteudo[tamanho_arquivo] = ' ';
    // AQUI QUE ESSA BOMBA ACONTECE MAIS DE MIL LINHAS DE AMOR
    while (i < tamanho_arquivo+1) {
        //printf("\n Estado atual eh: %d" ,estado);
        if (estado == 0) {
            if (conteudo[i] >= '0' && conteudo[i] <= '9') {
                estado = 1;
                i++;
            }
            else if (conteudo[i] == ':')
                estado = 6;
            else if (conteudo[i] == ';')
                estado = 7;
            else if (conteudo[i] == '(')
                estado = 8;
            else if (conteudo[i] == ')')
                estado = 9;
            else if (conteudo[i] == '<') {
                estado = 14;
                i++;
            }
            else if (conteudo[i] == '%') {
                estado = 12;
                i++;
            }
            else if (conteudo[i] == '>') {
                estado = 18;
                i++;
            }
            else if (conteudo[i] == '=')
                estado = 21;
            else if (conteudo[i] == '\'') {
                estado = 57;
                i++;
            }
            else if (conteudo[i] == '-') {
                estado = 10;
                i++;
            }
            else if (conteudo[i] == 'a') {
                estado = 71;
                i++;
            }
            else if (conteudo[i] == '+')
                estado = 56;
            else if (conteudo[i] == '^')
                estado = 55;
            else if (conteudo[i] == '/') {
                estado = 49;
                i++;
            }
            else if (conteudo[i] == '*') {
                estado = 52;
                i++;
            }
            else if (conteudo[i] == 'p') {
                estado = 39;
                i++;
            }
            else if (conteudo[i] == 'c') {
                estado = 29;
                i++;
            }
            else if (conteudo[i] == 'i') {
                estado = 34;
                i++;
            }
            else if (conteudo[i] == 'f') {
                estado = 22;
                i++;
            }
            else if (conteudo[i] == 's') {
                estado = 60;
                i++;
            }
            else if (conteudo[i] == 'r') {
                estado = 75;
                i++;
            }
            else if(conteudo[i] == 'e') {
                estado = 82;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z')) {
                estado = 27;
                i++;
            }
            else if (conteudo[i] == ' ')
                i++;
            else{
                printf("Caractere nao aceito!");
                return 0;
            }
        }
        else if (estado == 1) {
            if (conteudo[i] >= '0' && conteudo[i] <= '9') {
                estado = 1;
                i++;
            }
            else if (conteudo[i] == '.') {
                estado = 2;
                i++;
            }
            else {
                estado = 5;
            }
        }
        else if (estado == 2) {
            if (conteudo[i] >= '0' && conteudo[i] <= '9') {
                estado = 3;
                i++;
            }
            else {
                printf("Erro no estado 2!");
                return 0;
            }
        }
        else if (estado == 3) {
            if (conteudo[i] >= '0' && conteudo[i] <= '9') {
                estado = 3;
                i++;
            }
            else {
                estado = 4;
            }

        }
        else if (estado == 4) {
            printf(" constante_float");
            estado = 0;
        }
        else if (estado == 5) {
            printf(" constante_int");
            estado = 0;
        }
        else if (estado == 6)
        {
            printf(" doispts");
            estado = 0;
            i++;
        }
        else if (estado == 7)
        {
            printf(" pt_virgula");
            estado = 0;
            i++;
        }
        else if (estado == 8)
        {
            printf(" parentese_esq");
            estado = 0;
            i++;
        }
        else if (estado == 9)
        {
            printf(" parentese_dir");
            estado = 0;
            i++;
        }
        else if(estado == 10)
        {
            if (conteudo[i] == '>')
                estado = 94;
            else
                estado = 11;
        }
        else if (estado == 11)
        {
            printf(" operador(SUB)");
            estado = 0;
        }
        else if (estado == 94)
        {
            printf(" declaracao_var");
            estado = 0;
            i++;
        }
        else if (estado == 12)
        {
            while (conteudo[i] != '%')
            {
                i++;
                if (i == TAMANHO_MAXIMO)
                {
                    printf("\nErro no estado 12! Nao existe outro simbolo de comentario.");
                    return 0;
                }
            }
            estado = 13;
        }
        else if (estado == 13)
        {
            i++;
            estado = 0;
        }
        else if (estado == 14)
        {
            if (conteudo[i] == '-')
                estado = 15;
            else if (conteudo[i] == '=')
                estado = 16;
            else
                estado = 17;
        }
        else if (estado == 15)
        {
            printf(" atribuicao");
            estado = 0;
            i++;
        }
        else if (estado == 16)
        {
            printf(" relop(LE)");
            estado = 0;
            i++;
        }
        else if (estado == 17)
        {
            printf(" relop(LT)");
            estado = 0;
        }
        else if (estado == 18)
        {
            if (conteudo[i] == '=')
                estado = 19;
            else
                estado = 20;
        }
        else if (estado == 19)
        {
            printf(" relop(GE)");
            estado = 0;
            i++;
        }
        else if (estado == 20)
        {
            printf(" relop(GT)");
            estado = 0;
        }
        else if (estado == 21)
        {
            printf(" relop(EQ)");
            estado = 0;
            i++;
        }
        else if (estado == 22)
        {
            if (conteudo[i] == 'l')
            {
                estado = 23;
                i++;
            }
            else if (conteudo[i] == 'a')
            {
                estado = 67;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 22");
                return 0;
            }
        }
        else if (estado == 23)
        {
            if (conteudo[i] == 'o')
            {
                estado = 24;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 23");
                return 0;
            }
        }
        else if (estado == 24)
        {
            if (conteudo[i] == 'a')
            {
                estado = 25;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 24");
                return 0;
            }
        }
        else if (estado == 25)
        {
            if (conteudo[i] == 't')
            {
                estado = 26;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 25");
                return 0;
            }
        }
        else if (estado == 26)
        {
            if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
                estado = 28;
        }
        else if (estado == 27)
        {
            if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
                estado = 38;
        }
        else if (estado == 28)
        {
            printf(" tipo(float)");
            estado = 0;
        }
        else if(estado == 29)
        {
            if (conteudo[i] == 'h')
            {
                estado = 30;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 29");
                return 0;
            }
        }
        else if (estado == 30)
        {
            if (conteudo[i] == 'a')
            {
                estado = 31;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 30");
                return 0;
            }
        }
        else if (estado == 31)
        {
            if (conteudo[i] == 'r')
            {
                estado = 32;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 31");
                return 0;
            }
        }
        else if (estado == 32)
        {
            if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
                estado = 33;
        }
        else if (estado == 33)
        {
            printf(" tipo(char)");
            estado = 0;
        }
        else if (estado == 34)
        {
            if (conteudo[i] == 'n')
            {
                estado = 35;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 34");
                return 0;
            }
        }
        else if (estado == 35)
        {
            if (conteudo[i] == 't')
            {
                estado = 36;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 35");
                return 0;
            }
        }
        else if (estado == 36)
        {
            if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
                estado = 37;
        }
        else if (estado==37)
        {
            printf(" tipo(int)");
            estado = 0;
        }
        else if (estado==38) // AQUI VERIFICA SE È ID
        {
            j = i-1;
            while ((conteudo[j] >= 'a' && conteudo[j] <= 'z') || (conteudo[j] >= 'A' && conteudo[j] <= 'Z'))
            {
                j--;
            }
            for (j = j+1; j < i; j++)
            {
                temp[z] = conteudo[j];
                z++;
            }
            processar_identificador(temp,z); // AQUI PROCESSA O ID E ARMAZENA NA TABELA!
            z = 0;
            estado = 0;
        }
        else if (estado == 39)
        {
            if (conteudo[i] == 'r')
            {
                estado = 40;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else{
                printf("\nErro no estado 39");
                return 0;
            }
        }
        else if (estado == 40)
        {
            if (conteudo[i] == 'o')
            {
                estado = 41;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 40");
                return 0;
            }
        }
        else if (estado == 41)
        {
            if (conteudo[i] == 'g')
            {
                estado = 42;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 41");
                return 0;
            }
        }
        else if (estado == 42)
        {
            if (conteudo[i] == 'r')
            {
                estado = 43;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 42");
                return 0;
            }
        }
        else if (estado == 43)
        {
            if (conteudo[i] == 'a')
            {
                estado = 44;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 43");
                return 0;
            }
        }
        else if (estado == 44)
        {
            if (conteudo[i] == 'm')
            {
                estado = 45;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 44");
                return 0;
            }
        }
        else if (estado == 45)
        {
            if (conteudo[i] == 'a')
            {
                estado = 46;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 45");
                return 0;
            }
        }
        else if (estado == 46)
        {
            if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
                estado = 48;
        }
        else if (estado == 48)
        {
            estado = 0;
            printf(" programa");
        }
        else if (estado == 49)
        {
            if (conteudo[i] == '*')
            {
                estado = 51;
            }
            else
                estado = 50;
        }
        else if (estado == 50)
        {
            estado = 0;
            printf(" operador(DIV)");
        }
        else if (estado == 51)
        {
            estado = 0;
            printf(" inicio");
            i++;
        }
        else if (estado == 52)
        {
            if (conteudo[i] == '/')
            {
                estado = 54;
            }
            else
                estado = 53;
        }
        else if (estado == 53)
        {
            estado = 0;
            printf(" operador(MUL)");
        }
        else if (estado == 54)
        {
            estado = 0;
            printf(" fim");
            i++;
        }
        else if (estado == 55)
        {
            estado = 0;
            printf(" operador(POW)");
            i++;
        }
        else if (estado == 56)
        {
            estado = 0;
            printf(" operador(SUM)");
            i++;
        }
        else if (estado == 57)
        {
            if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 58;
                i++;
            }
            else
            {
                printf("\nErro no estado 57!");
                return 0;
            }
        }
        else if (estado == 58)
        {
            if (conteudo[i] == '\'')
            {
                estado = 59;
            }
            else
            {
                printf("\nErro no estado 58!");
                return 0;
            }
        }
        else if (estado == 59)
        {
            estado = 0;
            i++;
            printf(" constante_char()");
        }
        else if (estado == 60)
        {
            if (conteudo[i] == 'e')
            {
                estado = 61;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 60");
                return 0;
            }
        }
        else if (estado == 61)
        {
            if (conteudo[i] == 'n')
            {
                estado = 63;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 62;
                i++;
            }
            else
            {
                estado = 27;
                i++;
            }
        }
        else if (estado == 62)
        {
            estado = 0;
            printf(" se");
        }
        else if (estado == 63)
        {
            if (conteudo[i] == 'a')
            {
                estado = 64;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 63");
                return 0;
            }
        }
        else if (estado == 64)
        {
            if (conteudo[i] == 'o')
            {
                estado = 65;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 64");
                return 0;
            }
        }
        else if (estado == 65)
        {
            if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                estado = 66;
            }
        }
        else if (estado == 66)
        {
            estado = 0;
            printf(" senao");
        }
        else if (estado == 67)
        {
            if (conteudo[i] == 'c')
            {
                estado = 68;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 67");
                return 0;
            }
        }
        else if (estado == 68)
        {
            if (conteudo[i] == 'a')
            {
                estado = 69;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 68");
                return 0;
            }
        }
        else if (estado == 69)
        {
            if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                estado = 70;
            }
        }
        else if (estado == 70)
        {
            estado = 0;
            printf(" faca");
        }
        else if (estado == 71)
        {
            if (conteudo[i] == 't')
            {
                estado = 72;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 71");
                return 0;
            }
        }
        else if (estado == 72)
        {
            if (conteudo[i] == 'e')
            {
                estado = 73;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 72");
                return 0;
            }
        }
        else if (estado == 73)
        {
            if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                estado = 74;
            }
        }
        else if (estado == 74)
        {
            estado = 0;
            printf(" ate");
        }
        else if (estado == 75)
        {
            if (conteudo[i] == 'e')
            {
                estado = 76;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 76");
                return 0;
            }
        }
        else if (estado == 76)
        {
            if (conteudo[i] == 'p')
            {
                estado = 77;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 76");
                return 0;
            }
        }
        else if (estado == 77)
        {
            if (conteudo[i] == 'i')
            {
                estado = 78;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 77");
                return 0;
            }
        }
        else if (estado == 78)
        {
            if (conteudo[i] == 't')
            {
                estado = 79;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 78");
                return 0;
            }
        }
        else if (estado == 79)
        {
            if (conteudo[i] == 'a')
            {
                estado = 80;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 79");
                return 0;
            }
        }
        else if (estado == 80)
        {
            if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                estado = 81;
            }
        }
        else if (estado == 81)
        {
            estado = 0;
            printf(" repita");
        }
        else if (estado == 82)
        {
            if (conteudo[i] == 'n')
            {
                estado = 83;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 82");
                return 0;
            }
        }
        else if (estado == 83)
        {
            if (conteudo[i] == 't')
            {
                estado = 84;
                i++;
            }
            else if (conteudo[i] == 'q')
            {
                estado = 87;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 83");
                return 0;
            }
        }
        else if (estado == 84)
        {
            if (conteudo[i] == 'a')
            {
                estado = 85;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 85");
                return 0;
            }
        }
        else if (estado == 85)
        {
            if (conteudo[i] == 'o')
            {
                estado = 86;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 85");
                return 0;
            }
        }
        else if (estado == 86)
        {
            if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                estado = 94;
            }
        }
        else if (estado == 94)
        {
            estado = 0;
            printf(" entao");
        }
        else if (estado == 87)
        {
            if (conteudo[i] == 'u')
            {
                estado = 88;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 87");
                return 0;
            }
        }
        else if (estado == 88)
        {
            if (conteudo[i] == 'a')
            {
                estado = 89;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 88");
                return 0;
            }
        }
        else if (estado == 89)
        {
            if (conteudo[i] == 'n')
            {
                estado = 90;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 89");
                return 0;
            }
        }
        else if (estado == 90)
        {
            if (conteudo[i] == 't')
            {
                estado = 91;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 90");
                return 0;
            }
        }
        else if (estado == 91)
        {
            if (conteudo[i] == 'o')
            {
                estado = 92;
                i++;
            }
            else if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                printf("\nErro no estado 91");
                return 0;
            }
        }
        else if (estado == 92)
        {
            if ((conteudo[i] >= 'a' && conteudo[i] <= 'z') || (conteudo[i] >= 'A' && conteudo[i] <= 'Z'))
            {
                estado = 27;
                i++;
            }
            else
            {
                estado = 93;
            }
        }
        else if (estado == 93)
        {
            estado = 0;
            printf(" enquanto");
        }

    }

    printf("\n");
    for (i = 0; i < tamanho_arquivo; i++) {
        printf("%c", conteudo[i]);
    }

    return 0;
}
