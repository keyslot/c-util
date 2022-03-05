/* *
 * Lista circular,  @keyslot  
 * */
#include <stdio.h>
#include <stdlib.h>
 
struct Nodo{
	int id;
	int dato;
	struct Nodo *sig;
};

struct Lista{
	struct Nodo *raiz;
	int nodos;
};

typedef struct Nodo Nodo;
typedef struct Lista Lista;
Lista *crearLista(void);
void destruirLista(Lista **creada);
void agregarNodo(Lista **creada, int dato);
void demuestra(Lista *creada,Nodo *nodo,char *info);

int main(void) {
	puts("rapida ejecucion...");
        Lista *lista = crearLista();
	int i = 0;
	/* 10 nodos */
	for (i=65; i < 75; i++)
	     agregarNodo(&lista,i);
	destruirLista(&lista);
	return 0;
}


Lista *
crearLista(void)
{        
	 Lista *lista = malloc(sizeof(Lista));
	 /* exit if !lista .... */
	 lista->raiz = NULL;
	 lista->nodos = 0;
	 printf("Lista %p creada!\n",lista);
	 return lista;
}

void
destruirLista(Lista **ptr) 
{	
	/* exit if !ptr || !*ptr  */
	Nodo *aux = NULL;
	Nodo *existe = (*ptr)->raiz->sig;
	printf("Nodos: %d\n",(*ptr)->nodos);
        while(existe){
	      aux = existe->sig;
	      demuestra(*ptr,existe,"liberado");
              free(existe);
	      if(aux == (*ptr)->raiz) 
		 break;
	      existe = aux;
	}
	demuestra(*ptr,(*ptr)->raiz,"liberado");
	printf("Lista %p destruida!\n",*ptr);
        free(*ptr);
	*ptr = NULL;
}

void
agregarNodo(Lista **ptr,int dato) 
{
	Nodo *nuevo = malloc(sizeof(Nodo));
	/* exit if !nuevo */
	nuevo->dato = dato;
	nuevo->id = (*ptr)->nodos++;
	nuevo->sig = (*ptr)->raiz; 
	(*ptr)->raiz = nuevo; 
	demuestra(*ptr,nuevo,"creado");
}

void
demuestra(Lista *lista,Nodo *nodo,char *info)
{
        printf("Lista %p | nodo %d (%p) | dato %c | %s\n",
	       lista,nodo->id,nodo,nodo->dato,info);
}

