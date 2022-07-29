#include "header.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>


struct noVert* inserirVertice(struct noVert *ini, char* val){
  struct noVert* novoVertice;
  novoVertice = (struct noVert*) malloc (sizeof(struct noVert));
  strcpy(novoVertice->vert, val);
  novoVertice->prox = ini;
  novoVertice->ladj = NULL;
  return novoVertice;
}

int existeVertice(Grafo G, char* novo) {
   struct noVert *nv;
   if (G == NULL) return 0;
   for (nv = G->vertices; nv!=NULL; nv = nv->prox)
      if(strcmp(nv->vert, novo) == 0)
         return 1;
   return 0;
}


void inserirNovoVertice(Grafo G, char* nv){
   if (!existeVertice(G,nv)){
      G->vertices = inserirVertice(G->vertices,nv);
      G->NumVert++;
   }
}


Grafo criarGrafo() {
   Grafo G;
   G = (Grafo) malloc(sizeof (Grafo));
   if (G!=NULL){
     G->NumArco = 0;
     G->NumVert = 0;
     G->vertices = NULL;
   }
   return G;
}


struct noAdj* inserirAdjacencia(char* vdest, struct noAdj *l, int ct){
   struct noAdj *novo = (struct noAdj*) malloc(sizeof (struct noAdj));
   if (novo != NULL){
     strcpy(novo->vert,vdest);
     novo->custo = ct;
     novo->prox = l;
   }
   return novo;
}


void inserirArco(Grafo G, char* v1, char* v2,int custo) {
   struct noVert *v;
   struct noAdj *z;
   if (G == NULL) return;
   for (v = G->vertices; v != NULL; v = v->prox)
      if (strcmp(v->vert, v1) == 0 ) { // achou o vértice para inserir a adjacência
         for(z = v->ladj; z!= NULL; z = z->prox)
             if (strcmp(z->vert, v2) == 0) return;  // o arco já existe, retornar!
         v->ladj = inserirAdjacencia(v2,v->ladj,custo);
         G->NumArco++;
         break;
      }
}

void imprimirListaAdj(Grafo G) {
   struct noVert *nv;
   struct noAdj *na;
   if (G == NULL) return;
   printf("\n\nLista de Adjacencias:");
   for (nv = G->vertices; nv!=NULL; nv = nv->prox) {
      printf("\n\t%s: ",nv->vert);
      for (na = nv->ladj; na != NULL; na = na->prox)
          printf("(%s %d)",na->vert, na->custo);
   }
}

int grauVertice(Grafo G, char* v) {
   struct noVert *nv;
   struct noAdj *na;
   int cont = 0;
   if (G == NULL) return 0;
   for (nv = G->vertices; nv!=NULL; nv = nv->prox) {
      if(strcmp(v, nv->vert) == 0){
         for (na = nv->ladj; na != NULL; na = na->prox)
             cont = cont + 1;  // grau de saída
      }
      else{
         for (na = nv->ladj; na != NULL; na = na->prox)
             if(strcmp(v, na->vert) == 0)
               cont = cont + 1; // grau de entrada
      }
   }
   return cont;
}







int FoiVisitado(char *vert, char **vet, int tam){
  int i;
  for (i = 0; i<=tam; i++){
    if(strcmp(vet[i], vert) == 0)
       return 1;
  }
  return 0;
}

int imprimeVisita(char **vet, int tam){
  int i;
  printf("\nOrdem da visita: ");
  for (i = 0; i<=tam; i++){
     printf("(%s) ", vet[i]);
  }
  return 0;
}


void BuscaEmLargura(Grafo G, char * v, int K){
   struct noVert *nv;
   struct noAdj *na;
   char **visitados, *vt;
   TipoFila *fila;
   int i=0, cont = 0;
   //Iniciar o vetor de visitados com 'nao' para todos os vértices
   visitados = malloc (G->NumVert * sizeof (char *)) ;
   for (i=0; i < G->NumVert; i++){
      visitados[i] = malloc (20 * sizeof (char)) ;
      strcpy(visitados[i], "NAO");
   }

   // anotar como visitado o vértice de origem (busca)

   //Iniciar a fila e inserir o vértice de origem
   fila = (TipoFila *) malloc (sizeof(TipoFila));
   IniciaFila(fila);
   Enfileira(v,fila);

   while(!Vazia(fila)){
       vt = Desenfileira(fila);
       for (nv = G->vertices; nv!=NULL; nv = nv->prox)
       {
            if(strcmp(vt, nv->vert) == 0)
                 for (na = nv->ladj; na != NULL; na = na->prox)
                {
                      if (na->custo < K)
                      {
                        ;
                      }
                      else if (FoiVisitado(na->vert,visitados,cont)==0)
                      {
                           strcpy(visitados[cont],na->vert);
                           cont++;
                      }
                 }
        }

   }
   printf("\nSeguem os usuarios que %s visita, e que tem acima de %d interacoes: " ,v,K);
     for (i = 0; i<=cont-1; i++)
    {
     printf("[%s] ", visitados[i]);
    }
   //imprimeVisita(visitados,cont-1);
   free(fila);
}


void BuscaForte(Grafo G, char* v){
   struct noVert *nv;
   struct noAdj *na;
   char **visitados, *vt;
   TipoFila *fila;
   int i=0, cont = 0, z = 0;
   //Iniciar o vetor de visitados com 'nao' para todos os vértices
   visitados = malloc (G->NumVert * sizeof (char *)) ;
   for (i=0; i < G->NumVert; i++){
      visitados[i] = malloc (20 * sizeof (char)) ;
      strcpy(visitados[i], "NAO");
   }

   // anotar como visitado o vértice de origem (busca)
   strcpy(visitados[cont], v);

   //Iniciar a fila e inserir o vértice de origem
   fila = (TipoFila *) malloc (sizeof(TipoFila));
   IniciaFila(fila);
   Enfileira(v,fila);

   while(!Vazia(fila)){
       vt = Desenfileira(fila);
       for (nv = G->vertices; nv!=NULL; nv = nv->prox)
            if(strcmp(vt, nv->vert) == 0)
                 for (na = nv->ladj; na != NULL; na = na->prox)
                      if (FoiVisitado(na->vert,visitados,cont)==0){
                           cont++;
                           strcpy(visitados[cont],na->vert);
                      }
   }
   for (i = 0; i <= cont ; i++)
   {
       z = InteracaoForte(G, visitados[i],v) + z;
   }
   if (z == 0)
    printf("O usuario %s nao tem interacoes fortes com ninguem" ,v);
   free(fila);
}


int InteracaoForte(Grafo G, char*v, char *vitima)
{
struct noVert *nv;
   struct noAdj *na;
   char **visitados, *vt;
   TipoFila *fila;
   int i=0, cont = 0, z=0;
   //Iniciar o vetor de visitados com 'nao' para todos os vértices
   visitados = malloc (G->NumVert * sizeof (char *)) ;
   for (i=0; i < G->NumVert; i++){
      visitados[i] = malloc (20 * sizeof (char)) ;
      strcpy(visitados[i], "NAO");
   }

   // anotar como visitado o vértice de origem (busca)
   strcpy(visitados[cont], v);

   //Iniciar a fila e inserir o vértice de origem
   fila = (TipoFila *) malloc (sizeof(TipoFila));
   IniciaFila(fila);
   Enfileira(v,fila);

   while(!Vazia(fila)){
       vt = Desenfileira(fila);
       for (nv = G->vertices; nv!=NULL; nv = nv->prox)
            if(strcmp(vt, nv->vert) == 0)
                 for (na = nv->ladj; na != NULL; na = na->prox)
                      if (FoiVisitado(na->vert,visitados,cont)==0 && strcmp(na->vert,vitima) == 0)
                        {
                        printf("\n%s e %s tem uma interacao forte!" ,v,vitima);
                        z = 1;
                      }

   }
   free(fila);
   return z;
}



void BuscaEmProfundidade (Grafo G, char* v) {
   struct noVert *nv;
   struct noAdj *na;
   char **visitados, *vt;
   TipoPilha *pilha;
   int i=0, cont = 0;

   //Iniciar o vetor de visitados com 'nao' para todos os vértices
   visitados = malloc (G->NumVert * sizeof (char *)) ;
   for (i=0; i<G->NumVert; i++){
      visitados[i] = malloc (20 * sizeof (char)) ;
      strcpy(visitados[i], "NAO");
   }
   //Iniciar a fila e inserir o vértice de origem
   pilha = (TipoPilha *) malloc (sizeof(TipoPilha));
   IniciaPilha(pilha);
   Empilha(v,pilha);

   while(!VaziaPilha(pilha)){
       vt = Desempilha(pilha);
       if (FoiVisitado(vt,visitados,cont)==0){
          strcpy(visitados[cont],vt);
          cont++;
          for (nv = G->vertices; nv!=NULL; nv = nv->prox)
              if(strcmp(vt, nv->vert) == 0)
                 for (na = nv->ladj; na != NULL; na = na->prox)
                      if (FoiVisitado(na->vert,visitados,cont)==0){
                           Empilha(na->vert,pilha);
                      }
       }
   }
   imprimeVisita(visitados,cont-1);
   free(pilha);
}

void BuscaInteracao(Grafo G,char *vitima,char *v,int K)
{
   struct noVert *nv;
   struct noAdj *na;
   char **visitados, *vt;
   TipoFila *fila;
   int i=0, cont = 0;
   //Iniciar o vetor de visitados com 'nao' para todos os vértices
   visitados = malloc (G->NumVert * sizeof (char *)) ;
   for (i=0; i < G->NumVert; i++){
      visitados[i] = malloc (20 * sizeof (char)) ;
      strcpy(visitados[i], "NAO");
   }

   // anotar como visitado o vértice de origem (busca)

   //Iniciar a fila e inserir o vértice de origem
   fila = (TipoFila *) malloc (sizeof(TipoFila));
   IniciaFila(fila);
   Enfileira(v,fila);

   while(!Vazia(fila)){
       vt = Desenfileira(fila);
       for (nv = G->vertices; nv!=NULL; nv = nv->prox)
       {
            if(strcmp(vt, nv->vert) == 0)
                 for (na = nv->ladj; na != NULL; na = na->prox)
                {
                      if (na->custo < K)
                      {
                        ;
                      }
                      else if (FoiVisitado(na->vert,visitados,cont)==0 && strcmp(vitima,na->vert)==0)
                      {
                            strcpy(visitados[cont],na->vert);
                            cont++;
                      }
                 }
        }

   }
   if (cont == 0)
        free(fila);
   else
   {
    printf("\nO usuario %s tem interacao acima de %d com %s" ,v,K,vitima);
    free(fila);
   }
}













int MarcaVisitaTempo(char *vt, int pos, char tipo, struct visitaTempo *vet, int tam){
  int i;
  for (i = 0; i<tam; i++){
    if(strcmp(vet[i].vert, vt) == 0){
         if (tipo == 'D'){
             vet[i].tempoDescoberta = pos;
             return 1;
         }
         else{
             if (vet[i].tempoFinalizacao == -1){
                 vet[i].tempoFinalizacao = pos;
                 return 1;
             }
             else return 0;
         }
    }
  }
  return 0;
}

int FoiVisitadoTempo(char* vert, struct visitaTempo *vet, int tam){
  int i;
  for (i = 0; i<tam; i++){
    if((strcmp(vet[i].vert,vert) == 0) && (vet[i].tempoDescoberta != -1))
       return 1;
  }
  return 0;
}

int imprimeVisitaTempo(struct visitaTempo *vet, int tam){
  int i;
  for (i = 0; i<tam; i++){
     printf("\n(%s) Descoberta: %d, Finalizacao: %d",
         vet[i].vert, vet[i].tempoDescoberta, vet[i].tempoFinalizacao);
  }
  return 0;
}


void PercursoProfundidadeTempo (Grafo G, char* v) {
   struct noVert *nv;
   struct noAdj *na;
   struct visitaTempo *visitados;
   TipoPilha *pilha;
   char *vt;
   int tam=0, cont = 0, finaliza, r;

   //Iniciar o vetor de visitados com -1 para todos os vértices
   visitados = (struct visitaTempo *) malloc (G->NumVert * sizeof (struct visitaTempo));
   for (nv=G->vertices; nv!=NULL; nv=nv->prox){
      strcpy(visitados[tam].vert, nv->vert);
      visitados[tam].tempoDescoberta = -1;
      visitados[tam].tempoFinalizacao = -1;
      tam++;
   }
   //Iniciar a fila e inserir o vértice de origem
   pilha = (TipoPilha *) malloc (sizeof(TipoPilha));
   IniciaPilha(pilha);
   Empilha(v,pilha);

   while(!VaziaPilha(pilha)){
       vt = Topo(pilha);
       if (FoiVisitadoTempo(vt,visitados,tam)==0){
          MarcaVisitaTempo(vt, cont++, 'D', visitados,tam);
          //cont++;
          for (nv = G->vertices; nv!=NULL; nv = nv->prox)
              if(strcmp(vt, nv->vert) == 0){
                 finaliza = 1;
                 for (na = nv->ladj; na != NULL; na = na->prox)
                      if (FoiVisitadoTempo(na->vert,visitados,tam)==0){
                           Empilha(na->vert,pilha);
                           finaliza = 0;
                      }
                 if (finaliza == 1){
                     r = MarcaVisitaTempo(vt,cont,'F',visitados,tam);
                     if (r == 1) cont++;
                     vt = Desempilha(pilha);
                 }
              }
       }
       else {
           r = MarcaVisitaTempo(vt,cont,'F',visitados,tam);
           if (r == 1) cont++;
           vt = Desempilha(pilha);
       }
   }
   imprimeVisitaTempo(visitados,tam);
   free(pilha);
}


//=========================================== FIM DO GRAFO //

void IniciaFila(TipoFila *fila){
   fila->inicio = NULL;
   fila->fim = NULL;
   fila->tamanho=0;
}

int Vazia(TipoFila *fila){
   return (fila->inicio == NULL);
}

void Enfileira(char *x, TipoFila *fila){
   TipoNo *aux;
   aux = (TipoNo *) malloc(sizeof(TipoNo));
   strcpy(aux->valor,x);
   aux->prox=NULL;
   if (Vazia(fila)){
      fila->inicio=aux;
      fila->fim=aux;
   }
   else {
      fila->fim->prox = aux;
      fila->fim = aux;
   }
   fila->tamanho++;
}

char* Desenfileira(TipoFila *fila){
   TipoNo *q;
   char *v = malloc(20 * sizeof(char));
   if (Vazia(fila)) {
      printf("Fila esta vazia\n");
      return 0;
   }
   q = fila->inicio;
   strcpy(v, fila->inicio->valor);
   fila->inicio = fila->inicio->prox;
   free(q);
   fila->tamanho--;
   return v;
}

//============================== FIM DA FILA //

void IniciaPilha(TipoPilha *pilha){
 pilha->topo = NULL;
 pilha->tamanho = 0;
}

int VaziaPilha(TipoPilha *pilha){
 return (pilha->topo == NULL);
}

char* Topo (TipoPilha *pilha){
 if (pilha==NULL)
    return "";
 return pilha->topo->valor;
}


void Empilha(char *x, TipoPilha *pilha){
 TipoNo *aux;
 if (pilha==NULL)
    return;
 aux = (TipoNo *) malloc(sizeof(TipoNo));
 strcpy(aux->valor,x);
 aux->prox = pilha->topo;
 pilha->topo = aux;
 pilha->tamanho++;
}

char* Desempilha(TipoPilha *pilha){
   char *v = malloc(20 * sizeof(char));
   TipoNo *no;
   if (pilha==NULL)
      return "";
   no = pilha->topo;
   strcpy(v, no->valor);
   pilha->topo = no->prox;
   pilha->tamanho--;
   free(no);
  return v;
}

//============================== FIM DA PILHA //

