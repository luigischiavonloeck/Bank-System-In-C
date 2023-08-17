#ifndef listade_H
#define listade_H

#define SUCESSO 0
#define LISTA_VAZIA 1
#define FALTOU_MEMORIA 2
#define CODIGO_INEXISTENTE 3

typedef struct {
        int cod;
        char usuario[20];
        float saldoC,saldoP;
        int senha;
} Conta;
        
typedef struct nodo Nodo;

struct nodo {
       Conta info;
       Nodo *ant;
       Nodo *prox;
};

typedef struct {
        Nodo *inicio;
        Nodo *fim;
        int n;
} ListaDE;

void logo();
void criaLista(ListaDE *lt);
int incluiNoInicio(ListaDE *lt, Conta d);
void exibe(ListaDE lt);
void exibeConta(Conta d);
int quantidadeDeNodos(ListaDE lt);
int estaVazia(ListaDE lt);
int excluiDoInicio(ListaDE *lt, Conta *d);
int incluiNoFim(ListaDE *lt, Conta d);
int excluiDoFim(ListaDE *lt, Conta *d);
int incluiDepois(ListaDE *lt, Conta d, int cod);
int excluiNodo(ListaDE *lt, Conta *d, int cod);
int consultaPorCodigo(ListaDE lt, Conta *d, int cod);
void lerArquivo(ListaDE *lt);
void gravaArquivo(ListaDE lt);
void lerBackup(ListaDE *lt);
void gravaBackup(ListaDE lt);
int alteraConta(ListaDE lt, Conta d, int cod);


#endif
