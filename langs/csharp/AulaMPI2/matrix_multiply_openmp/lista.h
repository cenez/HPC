#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#define true 1
#define false 0
typedef int bool;
typedef double** MATRIX;

typedef struct _aux {
	MATRIX matrix;
	int lin;
	int col;
	struct _aux *next;
}ELEMENTO, *NO;
typedef struct {
	NO head;
	int len;
} LISTA;

void initialize(LISTA *lista);
void printDIM(LISTA *lista);
bool add(LISTA *lista, MATRIX matrix, int lin, int col);
void free_lista_e_matrizes(LISTA *lista);
LISTA nova();

#endif // LISTA_H_INCLUDED

