typedef struct no* Lista;
Lista cria_lista();
int lista_vazia(Lista);
int get_pos(Lista, int, int *, int*);
int insere_elem(Lista,int,int);
int remove_elem(Lista,int);
void limpa_lista(Lista);
void remove_pos(Lista, int);
int soma_polinomio(Lista,int);
