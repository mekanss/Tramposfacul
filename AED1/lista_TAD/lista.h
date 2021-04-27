typedef struct lista *Lista;
Lista cria_lista();
int lista_vazia(Lista);
int lista_cheia(Lista);
int insere_elem(Lista,float);
int remove_elem(Lista,float);
int remove_impar(Lista);
void limpa_lista(Lista);
float get_posicao(Lista,int);
float pega_maior(Lista);
int tamanho_lista(Lista);
Lista inverte_lista(Lista,Lista);
Lista funde_lista(Lista,Lista,Lista);

