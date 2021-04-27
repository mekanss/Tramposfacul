#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 20
// A ESCOLHA DO ENCADEAMENTO COM CABEÇALHO FOI FEITA POIS:
// NAO EXISTE UM NUMERO FIXO DE ELEMENTOS
// O CABEÇALHO TEM UMA VARIAVEL QUE GUARDA O TAMANHO QUE VAI SER USADO PARA A SOMA DOS POLINOMIOS


struct no
{
    int potencia;
    int coeficiente;
    struct no *prox;
};

Lista cria_lista()
{
    Lista cab;
    cab = (Lista)malloc(sizeof(struct no));
    if (cab != NULL)
    {
        cab->prox=NULL;
        cab->potencia=0;
    }
    return cab;
}

int lista_vazia(Lista lst)
{
    if(lst->prox == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int insere_elem(Lista lst, int pot, int coef)
{
    Lista N=(Lista)malloc(sizeof(struct no));
    if (N==NULL)
    {
        return 0;
    }
    N->potencia=pot;
    N->coeficiente=coef;
    Lista aux=lst;
    while (aux->prox !=NULL && aux->prox->potencia <=pot)
    {
        aux=aux->prox;
        if (aux->potencia == pot)
        {
            aux->coeficiente=coef+aux->coeficiente;
            return 1;
        }
    }
    N->prox=aux->prox;
    aux->prox = N;
    lst->potencia++;
    return 1;
}


int remove_elem(Lista lst, int elem)
{
    if(lista_vazia(lst)==1)
    {
        return 0;
    }
    Lista aux = lst;
    while (aux->prox != NULL && aux->prox->potencia > elem)
        aux=aux->prox;
    if(aux->prox == NULL || aux->prox->potencia < elem)
        return 0;
    Lista aux2 = aux->prox;
    aux->prox = aux2->prox;
    free(aux2);
    lst->potencia--;
    return 1;


    return 1;
}

void limpa_lista(Lista lst)
{
    lst->prox=NULL;
    free(lst);
    lst=NULL;
}

int get_pos(Lista lst, int pos, int *coef, int *pot)
{
   int i;
   if(lista_vazia(lst)==1)
    {
        return 0;
    }
    Lista aux = lst;
    for (i=0;i<=pos;i++)
    {
        aux = aux->prox;
    }
    if (aux == NULL)
    {
        return 0;
    }
    *coef=aux->coeficiente;
    *pot=aux->potencia;
    return 1;
}


void remove_pos(Lista lst, int pos)
{
   int i;
   if(lista_vazia(lst)==1)
    {
        return;
    }
    Lista aux = lst;
    for (i=0;i<pos;i++)
    {
        aux = aux->prox;
    }
    Lista aux2 = aux->prox;
    aux->prox = aux2->prox;
    free(aux2);
    lst->potencia--;
}

int soma_polinomio(Lista lst,int X)
{
    int i;
    int soma;
    int somares=0;
    if(lista_vazia(lst)==1)
    {
        return 0;
    }
    Lista aux = lst;
    for (i=0;i<lst->potencia;i++)
    {
        soma=pow(X,aux->prox->potencia)*aux->prox->coeficiente;
        somares=soma+somares;
        aux=aux->prox;
    }
    return somares;
}
