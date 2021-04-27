#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 31


struct lista
{
    float n[MAX];
    int FIM;
};

Lista cria_lista()
{
    Lista lst;
    lst = (Lista)malloc(sizeof(struct lista));
    if (lst != NULL)
    {
        lst->FIM=0;
    }
    return lst;
}

int lista_vazia(Lista lst)
{
    if (lst->FIM == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

int lista_cheia(Lista lst)
{
    if(lst->FIM==MAX)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int insere_elem(Lista lst, float elem)
{
    if(lst==NULL || lista_cheia(lst)==1)
    {
        return 0;
    }
    lst->n[lst->FIM] = elem;
    lst->FIM++;
    return 1;
}


int remove_elem(Lista lst, float elem)
{
    int i;
    int Aux =0;
    if(lst==NULL || lista_vazia(lst)==1)
    {
        return 0;
    }
    while (Aux < lst->FIM && lst->n[Aux]!=elem)
    {
        Aux++;
    }
    if (Aux == lst->FIM)
    {
        printf("\nO elemento nao existe\n");
        return 0;
    }
    for (i=Aux+1; i<lst->FIM;i++)
    {
        lst->n[i-1] = lst->n[i];
    }
    lst->FIM--;
    return 1;
}

void limpa_lista(Lista lst)
{
    lst=NULL;
    free(lst);
}

float get_posicao(Lista lst, int i)
{
    return lst->n[i];
}

int remove_impar(Lista lst)
{
    int i;
    int j;
    if(lst==NULL || lista_vazia(lst)==1)
    {
        return 0;
    }
    for (i=0;i<lst->FIM;i++)
    {
        if (fmod(lst->n[i],2)!=0 || lst->n[i]==1)
        {
            for (j=i;j<lst->FIM;j++)
            {
                lst->n[j] = lst->n[j+1];
            }
            lst->FIM--;
            i--;
        }
    }
    return 1;
}





float pega_maior(Lista lst)
{
    int i;
    float Aux=0;
    if(lst==NULL || lista_vazia(lst)==1)
    {
        return 0;
    }
    for (i=0;i<lst->FIM;i++)
    {
        if (lst->n[i]>Aux)
        {
            Aux=lst->n[i];
        }
    }
    return Aux;
}

int tamanho_lista(Lista lst)
{
    int tamanho;
    if(lst==NULL || lista_vazia(lst)==1)
    {
        return 0;
    }
    tamanho = lst->FIM;
    return tamanho;
}


Lista inverte_lista(Lista lst,Lista lst2)
{
    int i;
    if(lst==NULL || lista_vazia(lst)==1 || lst2==NULL)
    {
        return 0;
    }
    for (i=0;i<lst->FIM;i++)
    {
        lst2->n[i]=lst->n[lst->FIM-i-1];
    }
    lst2->FIM=lst->FIM;
    return lst2;
}

Lista funde_lista(Lista lst,Lista lst2,Lista lst3)
{
    int i;
    int j=0;
    if (lst->FIM + lst2->FIM > MAX)
    {
        return 0;
    }

    for (i=0;i<lst->FIM;i++)
    {
        lst3->n[j]=lst->n[i];
        lst3->n[j+1]=lst2->n[i];
        j=j+2;
    }
    lst3->FIM=lst->FIM+lst2->FIM;
    return lst3;
}
