// RAPHAEL AZAMBUJA SILVA MACEDO 2021
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define MAX 31

void imprime_lista(Lista lst)
{
    int i;
    float j;
    if(lst==NULL)
    {
        printf("Lista vazia.");
        return;
    }
    printf("\nA lista impressa e:\n");
    for (i=0;i<tamanho_lista(lst);i++)
    {
        j=get_posicao(lst,i);
        printf("%f ",j);
    }
    printf("\n");
}



int main()
{
    int n;
    int tam;
    float elemento;
    while (n!=0)
    {
        printf("Digite a opcao que desejas:\n");
        printf("[1] Cria lista.\n");
        printf("[2] Insere elemento.\n");
        printf("[3] Imprime a lista.\n");
        printf("[4] Remove impar.\n");
        printf("[5] Pegar o maior da lista.\n");
        printf("[6] Tamanho da lista.\n");
        printf("[7] Esvaziar lista.\n");
        printf("[8] Inverter lista.\n");
        printf("[9] Concatenar listas.\n");
        printf("[10] Remove elem.\n");
        printf("[0] Sair.\n");
        scanf("%i",&n);
        switch(n)
        {
            case 1: ;
                Lista lst=cria_lista();
                break;
            case 2:
                printf("\nDigite o elem que deseja inserir: ");
                scanf("%f",&elemento);
                insere_elem(lst,elemento);
                break;
            case 3:
                imprime_lista(lst);
                break;
            case 4:
                remove_impar(lst);
                break;
            case 5:
                elemento=pega_maior(lst);
                printf("\nO maior elem eh: %f\n" ,elemento);
                break;
            case 6:
                tam=tamanho_lista(lst);
                printf("\nO tamanho da lista eh: %i\n" ,tam);
                break;
            case 7:
                limpa_lista(lst);
                break;
            case 8: ;
                Lista lst2=cria_lista();
                inverte_lista(lst,lst2);
                imprime_lista(lst2);
                break;
            case 9: ;
                Lista lst3=cria_lista();
                funde_lista(lst,lst2,lst3);
                imprime_lista(lst3);
                break;
            case 10:
                printf("\nDigite o elemento que desejas remover: ");
                scanf("%f",&elemento);
                remove_elem(lst,elemento);
                break;
        }
    }










    return 0;
}



