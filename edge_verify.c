// ================================================= //
// Exemplo de implementacao Grafos                   //
// Conecta e desconecta                              //
// Profa Fabiana Lorenzi                             //
// Estruturas de Dados I                             //
// ================================================= //

#include <stdio.h>
#include <conio.h>
#include <malloc.h>

// fila para os adjacentes e pilha para o caminho...
struct nodo
{
 int dado;
 struct nodo *prox;
};

// lista dos vertices
struct vertice
{
 int v;
 struct vertice *prox_v;
 struct adjacente *prox_a;
};

// lista dos adjacentes
struct adjacente
{
 int a;
 struct adjacente *prox;
};

void conecta (struct vertice **grafo, int vo, int vd);
void mostra_grafo(struct vertice *grafo);
void desconecta_grafo(struct vertice **grafo);

// ==================================================
// Procedimento para conectar vertice - adjacente
// ==================================================
void conecta (struct vertice **grafo, int vo, int vd)
 {
  // declaracao das variaveis locais
   struct vertice *aux;
   struct vertice *ant;
   struct adjacente *vadj;
   struct adjacente *antd;
   int achou=0;
   int achoud;

   if (*grafo == NULL) // se grafo estiver vazio....
   {
     aux = (struct vertice *) malloc(sizeof(struct vertice));
     if (aux)
     {
       aux->v=vo;
       aux->prox_v=NULL;
       vadj = (struct adjacente *) malloc(sizeof(struct adjacente));
       vadj->a=vd;
       vadj->prox=NULL;
       aux->prox_a = vadj;
       (*grafo)=aux;
     }
    }
   else {       // se grafo estiver algum valor...
     aux=*grafo;
     ant=aux;
     while (aux) // procura vertice
     {
       if (aux->v == vo)
       {
	  achou=1; // achou o vertice no grafo...
	  // procura adjacente
	  vadj=aux->prox_a;
	  antd=vadj;
	  achoud = 0;
	  while ((vadj) && (achoud==0))
	  {
	    if (vadj->a == vd)
	    {
	      printf("Arco ja existe !!!\n");
	      achoud=1;
	    }
	    else
	    {
	      antd=vadj;
	      vadj=vadj->prox;
	    }
	  }
	  if (achoud==0)
	  {
	    vadj = (struct adjacente *) malloc(sizeof(struct adjacente));
	    vadj->a=vd;
	    vadj->prox=NULL;
	    antd->prox= vadj;
	  }
       }
       ant=aux;
       aux=aux->prox_v;
     }
     if (achou==0) // se o vertice ainda nao existe no grafo.. entao insere-o
     {
       aux = (struct vertice *) malloc(sizeof(struct vertice));
       aux->v=vo;
       aux->prox_v=NULL;
       vadj = (struct adjacente *) malloc(sizeof(struct adjacente));
       vadj->a=vd;
       vadj->prox=NULL;
       aux->prox_a = vadj;
       ant->prox_v=aux; // nao passa o endereco de aux para ant->prox.. pq ?
     }
   }
 }



// ===============================
// Procedimento para desenfileirar
// ===============================
int desenfileira (struct nodo **fila)
{
 struct nodo *aux;
 int valor=0;

 aux=*fila;
 (*fila)=(*fila)->prox;
 valor=aux->dado;
 free(aux);

 return valor;
}

// ===============================
// Procedimento para liberar nodos
// ===============================
int libera (struct nodo **fila)
{
 struct nodo *aux;

 aux = *fila;
 while (aux != NULL)  // Lista de adjacentes...
  {
    (*fila)=(*fila)->prox;
    free(aux);
    aux=*fila;
  }
}


// =============================================
// procedimento para mostrar o conteudo do grafo
// =============================================
void mostra_grafo(struct vertice *grafo)
{
 struct vertice *aux;
 struct adjacente *auxd;
// clrscr();
 aux=grafo;
 while (aux) // Lista de vertices...
 {
  printf("\n");
  printf("Vertice-> %i\n",aux->v);
  auxd=aux->prox_a;
  while (auxd != NULL)  // Lista de adjacentes...
  {
    printf("Adjacente-> %i\n",auxd->a);
    auxd=auxd->prox;
  }
  aux=aux->prox_v;
 }
  getch();
}

// ===============================================
// procedimento para liberar todo grafo da memoria
// ===============================================
void desconecta_grafo(struct vertice **grafo)
{
 struct vertice *aux;
 struct adjacente *auxd, *desd;

 aux=*grafo;
 while (aux != NULL) // Percorre lista de vertices...
 {
  printf("Desconectando vertice-> %i\n",aux->v);
  auxd=aux->prox_a;
  while (auxd != NULL)  // Lista de adjacentes...
  {
    printf("Desconectando adjacente-> %i\n",auxd->a);
    desd=auxd->prox;
    free(auxd);
    auxd=desd;
  }
  (*grafo)=(*grafo)->prox_v;
  free(aux);
  aux=(*grafo);
  printf("\n");
 }
 printf("Grafo desconectado !!!");
}

// Verifica se o arco existe no arco.
// Retorna 1 se for verdadeiro
int existe_arco(struct vertice *grafo, int vo, int vd)
{
  struct vertice *aux;
  struct adjacente *aux2;

  aux = grafo;

  while(aux != NULL)
  {
    printf("check 1\n");
    if(aux->v == vo)
    {
      printf("check 2\n");
      aux2 = aux->prox_a;
      while(aux2 != NULL)
      {
        printf("check 3\n");
        if(aux2->a == vd)
        {
          printf("check 4\n");
          return 1;
        }
        aux2 = aux2->prox;
      }
    }
    aux = aux->prox_v;
  }
  return 0;
}

/* ================== */
/* programa principal */
/* ================== */

void main()
{
  int vdestino, vorigem, x, a, existe;
  struct vertice *g=NULL, *end;
  struct adjacente *adj;
  struct nodo *lvisitados=NULL, *fila=NULL, *caminho=NULL;


  do{
    printf("\nInforme o Vertice Origem. : ");
    scanf("%d",&vorigem);
    if (vorigem != 0)
    {
      printf("\nInforme o Vertice Destino : ");
      scanf("%d",&vdestino);
      if (vdestino != 0)
      conecta(&g, vorigem, vdestino);
    } 
  }
  while (vorigem!=0);
  mostra_grafo(g);

  // Chamada da funcao que verifica a existencia do arco.
  printf("\nVerificar existencia do arco");
  printf("\nInforme o Vertice Origem. : ");
  scanf("%d",&vorigem);
  printf("\nInforme o Vertice Destino. : ");
  scanf("%d",&vdestino);

  existe = existe_arco(g, vorigem, vdestino);
  if(existe == 1){
    printf("O arco existe.\n");
  }
  else
  {
    printf("O arco nao existe\n");
  }
  

  while (vorigem!=0);
  desconecta_grafo(&g);
  getch();

}

