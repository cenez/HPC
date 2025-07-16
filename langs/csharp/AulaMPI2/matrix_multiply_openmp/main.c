/* Para compilar e usar este programa: no console ao lado proceder:
  compilar:
   gcc -fopenmp *.h *.c -o main
  executar:
   ./main
  limpar tela:
   clear */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include "lista.h"
#include "matrix_file_util.h"

#ifdef _OPENMP
#define ID omp_get_thread_num()
#define SIZE omp_get_num_threads()
#else
ID = 0
SIZE = 1
#endif

double **multiply(double **A, double **B, int a_rows, int b_cols, int n) {
    //a_rows = Linha A, b_cols = Coluna B, n = Coluna A e Linha B
    double **C = create_matrix(a_rows, b_cols);
    int i, j, k;

    #pragma omp parallel for firstprivate(A,B) private(i,j,k) num_threads(4)
    for (i = 0; i < a_rows; i++) {
        for (j = 0; j < b_cols; j++) {
            C[i][j] = 0;
            for (k = 0; k < n; k++) {
               C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

double **multiplyNMatrixFromList(LISTA *lista, int *linha, int *coluna){
  // linha, coluna são ponteiros para a dimensão final de C
  if(lista->head==NULL) return NULL;
  double **C = lista->head->matrix; // C recebe primeira matriz da lista
  int a_rows = lista->head->lin;
  NO no = lista->head;
  for (; no->next!=NULL; ) { // C * cada próxima matriz B da lista.
    double **B = no->next->matrix;
    int b_lin = no->next->lin;
    int b_col = no->next->col;
    C = multiply(C, B, a_rows, b_col, b_lin);
    no = no->next;
    *coluna = b_col;
  }
  *linha = a_rows;
  return C;
}

int main(int argc, char ** argv){
  int n = 100;
  char fname[n];
  char *target =  (char *) malloc(sizeof(char) * n);
  if (argc==2) {
    strcpy(fname, "matrix");
    char flen[15];
    int nlen = strlen(argv[1]);
    for (int i=0; i<nlen; i++){
      flen[i] = ((char *) argv[1])[i];
    }
    char fext[] = ".txt";
    strcat(fname, flen);
    strcat(fname, fext);
    for (int i = 0; i < strlen(fname); i++){
      target[i] = fname[i];
    }
    printf("File Name: %s; strlen: %ld\n", target, strlen(target));
  }
  char *path = "matrix4.txt"; // arquivo fonte com os dados das matrizes
  
  LISTA lista;
  lista = nova();
  
  if (argc == 2) carregar_lista(&lista, target);
  else carregar_lista(&lista, path);
  
  int a, b;
  double **C = multiplyNMatrixFromList(&lista, &a, &b);
  imprime(C, a, b);
  printf("dimensão final C: %d . %d\n", a, b);
  delete_matrix(C, a, b);
  free_lista_e_matrizes(&lista);
  free(target);
  return 0;
}

/* Exemplo:
  A = |1 2|
      |0 1|

  B = |1 2 3|
      |0 2 1|

  C = |1 6 5| = A x B
      |0 2 1|
*/
