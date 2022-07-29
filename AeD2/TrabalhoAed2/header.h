#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED


// header da fila + no

typedef struct No{
   char valor[20];
   struct No *prox;
} TipoNo;




typedef struct Fila{
   TipoNo *inicio, *fim;
   int tamanho;
} TipoFila;



void IniciaFila(TipoFila *fila);
int Vazia(TipoFila *fila);
void Enfileira(char *x, TipoFila *fila);
char* Desenfileira(TipoFila *fila);

// header do grafo

struct grafo {
   int NumVert;
   int NumArco;
   struct noVert *vertices;
};
typedef struct grafo *Grafo;

struct noVert {
   char vert[20];
   struct noVert *prox;
   struct noAdj *ladj;
};

struct noAdj {
   char vert[20];
   int custo;
   struct noAdj *prox;
};

struct visitaTempo{
  char vert[20];
  int tempoDescoberta;
  int tempoFinalizacao;
};

Grafo criarGrafo();
void inserirArco(Grafo G, char* v1, char* v2, int custo);
void inserirNovoVertice(Grafo G, char* nv);
int grauVertice(Grafo G, char* v);
void imprimirListaAdj(Grafo G);


void BuscaEmLargura(Grafo G, char *v, int K);
void BuscaEmProfundidade (Grafo G, char *v);
void BuscaInteracao(Grafo G,char *a,char *b, int K);
void PercursoProfundidadeTempo (Grafo G, char *v);
void BuscaForte(Grafo G, char *v);
int InteracaoForte(Grafo G, char*v, char *vitima);

// header da pilha

typedef struct Pilha{
 TipoNo *topo;
 int tamanho;
} TipoPilha;

void IniciaPilha(TipoPilha *pilha);
int VaziaPilha(TipoPilha *pilha);
void Empilha(char* x, TipoPilha *pilha);
char* Desempilha(TipoPilha *pilha);
char* Topo (TipoPilha *pilha);

#endif // HEADER_H_INCLUDED
