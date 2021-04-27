// RAPHAEL AZAMBUJA SILVA MACEDO 2021
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


void imprime_lista(Lista lst)
{
    int i=0;
    int coef;
    int pot;
    if(lista_vazia(lst)==1)
    {
        printf("\nA lista esta vazia.");
    }
    while(get_pos(lst,i,&coef,&pot) != 0)
    {
        if (pot==0)
        {
            if(coef>0)
            {
                printf("+%ix " ,coef);
                i++;
            }
            else
            {
                printf("%ix " ,coef);
                i++;
            }
        }
        else
        {
            if (coef>0)
            {
                printf("+%ix^%i " ,coef,pot);
                i++;
            }
            else
            {
                printf("%ix^%i " ,coef,pot);
                i++;
            }
        }
    }

}


int main()
{
int i;
int pot;
int coef;
int X;
int k;
int soma;
do
{
    printf("\nDigite a opcao que desejas\n");
    printf("\n[0] Inicializar lista");
    printf("\n[1] Inserir elemento");
    printf("\n[2] Remover elemento");
    printf("\n[3] Imprimir lista");
    printf("\n[4] Limpa lista");
    printf("\n[5] Calcular polinomio para determinado X");
    printf("\n[6] Sair\n");
    scanf("%i", &i);
    switch (i)
    {
    case (0):
        printf("Lista criada com sucesso! ");
        Lista lst=cria_lista();
        break;
    case (1):
        printf("\nDigite primeiramente, a potencia do termo: ");
        scanf("%i" ,&pot);
        printf("Agora, digite o coeficiente: ");
        scanf("%i" ,&coef);
        insere_elem(lst,pot,coef);
        break;
    case (2):
        printf("\nDesejas remover o elemento por:\n[0]Posicao\n[1]Valor\n");
        scanf("%i" ,&k);
        switch(k)
        {
            case(0):
                printf("\nDigite a pos do elemento que deseja remover:");
                scanf("%i" ,&pot);
                remove_pos(lst,pot);
                break;
            case (1):
                printf("\nDigite a potencia que deseja remover: ");
                scanf("%i" ,&pot);
                remove_elem(lst,pot);
                break;
        }
        break;
    case (3):
        imprime_lista(lst);
        break;
    case (4):
        limpa_lista(lst);
        break;
    case(5):
        printf("Digite o X para o qual quer calcular o polinomio: ");
        scanf("%i" ,&X);
        soma=soma_polinomio(lst,X);
        printf("\nA soma do polinomio eh: %i" ,soma);
        break;
    case (6):
        exit(0);
    }
}while  (i!=6);
    return 0;
}
