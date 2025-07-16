#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED
#include "lista.h"

/* Exemplo de arquivo de entrada:
N 2
DIM 2 2
1 2
0 1
DIM 2 3
1 2 3
0 2 1
*/
//Carrega lista, dado um arquivo de entrada. 
void carregar_lista(LISTA *lista, char *path);

// Cria deleta e imprime matriz
double **create_matrix(int l, int c);
void delete_matrix(double **M, int l, int c);
void imprime(double **A, int l, int c);

#endif // ARQUIVO_H_INCLUDED

