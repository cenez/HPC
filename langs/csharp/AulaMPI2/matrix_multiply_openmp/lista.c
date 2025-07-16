#include <stdio.h>
#include <malloc.h>
#include "lista.h"
void initialize(LISTA *lista){
	lista->head = NULL;
	lista->len = 0;
}
void printDIM(LISTA *lista){
	NO nulo = lista->head;
	printf("Lista: ");
	while(nulo!=NULL) {
		printf("%i.%i ", nulo->lin, nulo->col);
		nulo = nulo->next;
	}
	printf("\n");
}
bool add(LISTA *lista, MATRIX matrix, int lin, int col){
    if(lista==NULL) return false;
    int x = lista->len;
    if(lista->head==NULL){
        lista->head = (NO) malloc(sizeof(ELEMENTO));
        lista->head->matrix = matrix;
        lista->len++;
        lista->head->lin = lin;
        lista->head->col = col;
        lista->head->next = NULL;
        return true;
    }
	NO no = lista->head;
	while(no->next!=NULL)
		no = no->next;
	no->next = (NO) malloc(sizeof(ELEMENTO));
	no->next->matrix = matrix;
    no->next->lin = lin;
    no->next->col = col;
    no->next->next = NULL;
	lista->len++;
	return true;
}
void apaga_matrix(MATRIX V, int l, int c){
    for (int i = 0; i < l; ++i){
        free(V[i]);
    }
    free(V);
}
void free_lista_e_matrizes(LISTA *lista){
	NO nulo = lista->head;
	while (nulo != NULL){
		NO apagar = nulo;
		nulo = nulo->next;
		apaga_matrix(apagar->matrix, apagar->lin, apagar->col);
		free(apagar);
	}
	lista->head = NULL;
	lista->len = 0;
}
LISTA nova() {
	LISTA l;
	initialize(&l);
	return l;
}

