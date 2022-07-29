#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main()
{
    Grafo grafo;
    grafo = criarGrafo();
    char a[10];
    char b[10];
    char v[50][50];
    int x = 0;
    int z = 0;
    int K;
    int op;

    char str1[30], str2[30], str[100], num[10];
    int peso, i = 0, y = 0;
    FILE *arquivo;

    arquivo = fopen("texto.txt", "rt");

    if(arquivo == NULL){
        printf("Arquivo de textos nao foi aberto!");
    }else {
        printf("Arquivo de textos foi aberto!");
    }
    while(fgets(str, 100, arquivo) != NULL){
        i = 0;
        while(str[i] != ' '){
            str1[y] = str[i];
            i++;
            y++;
        }
        str1[y] = '\0';
        y = 0;
        i++;
        while(str[i] != ' '){
            str2[y] = str[i];
            i++;
            y++;
        }
        str2[y] = '\0';
        y = 0;
        i++;
        while(str[i] != '\0'){
            num[y] = str[i];
            i++;
            y++;
        }
        y = 0;
        i = 0;
        z = 0;

        peso = atoi(num);
        while (z != -1)
        {
            for (i = 0; i<x ; i++)
            {
                if (strcmp(str1,v[i]) == 0)
                    z = -1;
            }

            if (z == 0)
            {
                strcpy(v[x],str1);
                x++;
                z = -1;
            }
        }
        inserirNovoVertice(grafo, str1);
        inserirNovoVertice(grafo, str2);
        inserirArco(grafo, str1, str2, peso);
    }
    while (op != 6)
    {
        printf("\nMenu:");
        printf("\n[1]Mostrar Lista de Adjacencia");
        printf("\n[2]Procurar todos os usuarios com mais de K interacoes");
        printf("\n[3]Mostrar todos os caminhos com N passos");
        printf("\n[4]Mostrar todos fortemente conectado com usuario X");
        printf("\n[5]Buscar o menor caminho entre 2 usuarios");
        printf("\n[6]Sair");
        printf("\nEscolha: ");
        scanf("%d" ,&op);
        switch(op)
            {
            case 1:
                imprimirListaAdj(grafo);
                break;
            case 2:
                printf("Qual o nome do usuario que deseja checar?: ");
                setbuf(stdin,NULL);
                gets(a);
                printf("Qual o numero de interacoes que deseja?: ");
                scanf("%d" ,&K);
                BuscaEmLargura(grafo, a,K);
                for (i = 0; i<x ; i++)
                {
                    BuscaInteracao(grafo,a,v[i],K);
                }
                break;
            case 3:
                printf("Qual o nome do usuario que deseja checar?: ");
                setbuf(stdin,NULL);
                gets(a);
                BuscaEmProfundidade(grafo,a);
                printf("\nAinda em construcao!");
                break;
            case 4:
                printf("Qual o nome do usuario que deseja checar?: ");
                setbuf(stdin,NULL);
                gets(a);
                BuscaForte(grafo,a);
                break;
            case 5:
                printf("Digite o nome dos dois usuarios que deseja ver a distancia minima: ");
                setbuf(stdin,NULL);
                gets(a);
                printf("Agora digite o outro usuario: ");
                setbuf(stdin,NULL);
                gets(b);
                printf("Ainda em construcao!");
                break;
            case 6:
                fclose(arquivo);
                exit(0);
            default :
                printf("Opcao errada!");
                break;

        }
    }
    return 0;
}
