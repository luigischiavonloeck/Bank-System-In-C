#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "listade.h"

void criaLista(ListaDE *lt){
     lt->inicio = NULL;
     lt->fim = NULL;
     lt->n = 0;
}

int incluiNoInicio(ListaDE *lt, Conta d){
    Nodo *pAux;
    pAux = (Nodo *) malloc (sizeof (Nodo));
    if (pAux == NULL)
       return(FALTOU_MEMORIA);
    else {
       pAux->info = d;
       pAux->prox = lt->inicio;
       pAux->ant = NULL;
       
       if (lt->n == 0)
          lt->fim = pAux;
       else
          lt->inicio->ant = pAux;  

       lt->inicio = pAux;
       lt->n++;
       return(SUCESSO);
    }
}

void exibe(ListaDE lt){
     Nodo *pAux;
     pAux = lt.inicio;
     printf("\nExibindo a Lista de contas no sistema\n");
     while (pAux != NULL) {
        printf("----------------------------------------------------\n");
        printf("| Codigo: %d\n|\n| Nome: %s \n|\n| Saldo da conta corrente: %.2f\n|\n| Saldo investido na poupanca: %.2f\n|\n| Senha: %d\n", pAux->info.cod, pAux->info.usuario, pAux->info.saldoC, pAux->info.saldoP, pAux->info.senha);
        printf("----------------------------------------------------\n");
        pAux = pAux->prox;
     }
}

int quantidadeDeNodos(ListaDE lt){
   return lt.n;
}

int estaVazia(ListaDE lt){
   if(lt.n==0){
      return 1;
   } else {
      return 0;
   }
}

int excluiDoInicio(ListaDE *lt, Conta *d){
   Nodo *pAux;
    if(lt->n==0){
        return LISTA_VAZIA;
    } else {
        *d = lt->inicio->info;
        pAux = lt->inicio;
        lt->inicio = lt->inicio->prox;
        (lt->n==1)?(lt->fim=NULL):(lt->inicio->ant = NULL);
        lt->n--;
        free(pAux);
        return SUCESSO;
    }
}

int incluiNoFim(ListaDE *lt, Conta d){
   Nodo *pAux;
    pAux = (Nodo *) malloc (sizeof (Nodo));
    if (pAux == NULL){
      return(FALTOU_MEMORIA);
    } else {
       pAux->info = d;
       pAux->ant = lt->fim;
       pAux->prox = NULL;
       
       if (lt->n == 0){
          lt->inicio = pAux;
       } else {
          lt->fim->prox = pAux;  
       }

       lt->fim = pAux;
       lt->n++;
       return(SUCESSO);
    }
}

int excluiDoFim(ListaDE *lt, Conta *d){
   Nodo *pAux;
    if(lt->n==0){
        return LISTA_VAZIA;
    } else {
        *d = lt->fim->info;
        pAux = lt->fim;
        lt->fim = lt->fim->ant;
        (lt->n==1)?(lt->inicio=NULL):(lt->fim->prox = NULL);
        lt->n--;
        free(pAux);
        return SUCESSO;
    }
}

int incluiDepois(ListaDE *lt, Conta d, int cod){
   Nodo *pAux, *pTemp;

   pAux = lt->inicio;
   while(pAux->info.cod!=cod && pAux->prox!=NULL){
      pAux = pAux->prox;
    }
   if (pAux->info.cod!=cod){
      return CODIGO_INEXISTENTE;
    } else {
        pTemp = (Nodo *) malloc (sizeof(Nodo));
        if(pTemp==NULL){
            return FALTOU_MEMORIA;
        } 
        if(pAux->prox == NULL){
            incluiNoFim(lt, d);
            return SUCESSO;
        } else {
            pTemp->prox = pAux->prox;
            pTemp->ant = pAux;
            pAux->prox = pTemp;
            pTemp->info = d;
            pTemp->prox->ant = pTemp;
            lt->n++;
            return SUCESSO;
    }
    }
}

int excluiNodo(ListaDE *lt, Conta *d, int cod){
   Nodo *pAux;

    if(lt->inicio==NULL){
        return LISTA_VAZIA;
    } else {
        pAux = lt->inicio;
        while(pAux->info.cod!=cod && pAux->prox!=NULL){
            pAux = pAux->prox;
        }
        if (pAux->info.cod!=cod){
            return CODIGO_INEXISTENTE;
        } else {
            if(pAux->prox == NULL){
                excluiDoFim(lt,d);
                return SUCESSO;
            }
            if (pAux->ant == NULL){
                excluiDoInicio(lt,d);
                return SUCESSO;
            }
            if(lt->n==1){
                *d = pAux->info;
                lt->inicio=NULL;
                lt->fim=NULL;
                lt->n--;
                free(pAux);
                return SUCESSO;
            } else {
                *d = pAux->info;
                pAux->ant->prox = pAux->prox;
                pAux->prox->ant = pAux->ant;
                lt->n--;
                free(pAux);
                return SUCESSO;
            }
        }
    }
}

int consultaPorCodigo(ListaDE lt, Conta *d, int cod){
    Nodo *pAux;
    
    if(lt.inicio==NULL){
       return CODIGO_INEXISTENTE; 
    }
    pAux = lt.inicio;
    while(pAux->info.cod!=cod && pAux->prox!=NULL){
        pAux = pAux->prox;
    }
    if (pAux->info.cod!=cod){
        return CODIGO_INEXISTENTE;
    } else {
        *d = pAux->info;
        return SUCESSO;
    }
}

void lerArquivo(ListaDE *lt){
   FILE *stream;
	char nomeArq[10];
	Conta d;

	strcpy(nomeArq,"dados.txt");

	if((stream=fopen(nomeArq,"r"))==NULL){
		printf("Nao foi possivel abrir %s\n", nomeArq);
	} else {
		criaLista(lt);
	while (fscanf(stream,"%d %s %f %f %d\n",&d.cod,&d.usuario,&d.saldoC,&d.saldoP,&d.senha)!=EOF){
		incluiNoFim(lt,d);
	}
	fclose(stream);
	printf("Importacao Realizada com Sucesso!\n");
	}
}

void gravaArquivo(ListaDE lt){
   FILE *stream;
    Nodo *pAux;
    pAux = lt.inicio;
	char nomeArq[10];

	strcpy(nomeArq,"dados.txt");

	if((stream=fopen(nomeArq,"w"))==NULL){
		printf("Nao foi possivel abrir %s\n", nomeArq);
	} else {
		while(pAux!=NULL){
		fprintf(stream,"%d %s %.2f %.2f %d\n",pAux->info.cod,pAux->info.usuario,pAux->info.saldoC,pAux->info.saldoP,pAux->info.senha);
        pAux = pAux->prox;
		}
	fclose(stream);
	printf("Gravacao Realizada com Sucesso!\n");
	}
}

void logo(){
    //system("cls");
    printf("                                                                                                                           \n");
   printf("                                                                                                                          \n");
   printf("BBBBBBBBBBBBBBBBB                 AAA                 NNNNNNNN        NNNNNNNN          CCCCCCCCCCCCC       OOOOOOOOO     \n");
   printf("B::::::::::::::::B               A:::A                N:::::::N       N::::::N       CCC::::::::::::C     OO:::::::::OO   \n");
   printf("B::::::BBBBBB:::::B             A:::::A               N::::::::N      N::::::N     CC:::::::::::::::C   OO:::::::::::::OO \n");
   printf("BB:::::B     B:::::B           A:::::::A              N:::::::::N     N::::::N    C:::::CCCCCCCC::::C  O:::::::OOO:::::::O\n");
   printf("  B::::B     B:::::B          A:::::::::A             N::::::::::N    N::::::N   C:::::C       CCCCCC  O::::::O   O::::::O\n");
   printf("  B::::B     B:::::B         A:::::A:::::A            N:::::::::::N   N::::::N  C:::::C                O:::::O     O:::::O\n");
   printf("  B::::BBBBBB:::::B         A:::::A A:::::A           N:::::::N::::N  N::::::N  C:::::C                O:::::O     O:::::O\n");
   printf("  B:::::::::::::BB         A:::::A   A:::::A          N::::::N N::::N N::::::N  C:::::C                O:::::O     O:::::O\n");
   printf("  B::::BBBBBB:::::B       A:::::A     A:::::A         N::::::N  N::::N:::::::N  C:::::C                O:::::O     O:::::O\n");
   printf("  B::::B     B:::::B     A:::::AAAAAAAAA:::::A        N::::::N   N:::::::::::N  C:::::C                O:::::O     O:::::O\n");
   printf("  B::::B     B:::::B    A:::::::::::::::::::::A       N::::::N    N::::::::::N  C:::::C                O:::::O     O:::::O\n");
   printf("  B::::B     B:::::B   A:::::AAAAAAAAAAAAA:::::A      N::::::N     N:::::::::N   C:::::C       CCCCCC  O::::::O   O::::::O\n");
   printf("BB:::::BBBBBB::::::B  A:::::A             A:::::A     N::::::N      N::::::::N    C:::::CCCCCCCC::::C  O:::::::OOO:::::::O\n");
   printf("B:::::::::::::::::B  A:::::A               A:::::A    N::::::N       N:::::::N     CC:::::::::::::::C   OO:::::::::::::OO \n");
   printf("B::::::::::::::::B  A:::::A                 A:::::A   N::::::N        N::::::N       CCC::::::::::::C     OO:::::::::OO   \n");
   printf("BBBBBBBBBBBBBBBBB  AAAAAAA                   AAAAAAA  NNNNNNNN         NNNNNNN          CCCCCCCCCCCCC       OOOOOOOOO     \n");
   printf("                                                                                                                          \n\n\n");
}

void exibeConta(Conta d){
    printf("-------- Conta do banco --------\n\n");
    printf("Conta: %d\n\nNome: %s\n\nSaldo da conta corrente: R$%.2f\n\nSaldo investido na poupanca: R$%.2f\n\nSenha: %d\n\n",d.cod,d.usuario,d.saldoC,d.saldoP,d.senha);
    printf("--------------------------------\n\n");
}

void lerBackup(ListaDE *lt){
   FILE *stream;
	char nomeArq[10];
	Conta d;

	strcpy(nomeArq,"backup.txt");

	if((stream=fopen(nomeArq,"r"))==NULL){
		printf("Nao foi possivel abrir %s\n", nomeArq);
	} else {
		criaLista(lt);
	while (fscanf(stream,"%d %s %f %f %d\n",&d.cod,&d.usuario,&d.saldoC,&d.saldoP,&d.senha)!=EOF){
		incluiNoFim(lt,d);
	}
	fclose(stream);
	printf("Importacao Realizada com Sucesso!\n");
	}
}

void gravaBackup(ListaDE lt){
   FILE *stream;
    Nodo *pAux;
    pAux = lt.inicio;
	char nomeArq[10];

	strcpy(nomeArq,"backup.txt");

	if((stream=fopen(nomeArq,"w"))==NULL){
		printf("Nao foi possivel abrir %s\n", nomeArq);
	} else {
		while(pAux!=NULL){
		fprintf(stream,"%d %s %.2f %.2f %d\n",pAux->info.cod,pAux->info.usuario,pAux->info.saldoC,pAux->info.saldoP,pAux->info.senha);
        pAux = pAux->prox;
		}
	fclose(stream);
	printf("Gravacao Realizada com Sucesso!\n");
	}
}

int alteraConta(ListaDE lt, Conta d, int cod){
    Nodo *pAux;
    
    pAux = lt.inicio;
    while(pAux->info.cod!=cod && pAux->prox!=NULL){
        pAux = pAux->prox;
    }
    if (pAux->info.cod!=cod){
        printf("Erro na operacao!\n\n");
        return CODIGO_INEXISTENTE;
    } else {
        //return &pAux;
        pAux->info = d;
        printf("Operacao realizada com sucesso!\n\n");
        return SUCESSO;
    }
}