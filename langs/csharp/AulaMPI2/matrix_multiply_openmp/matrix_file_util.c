#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "lista.h"
#include "matrix_file_util.h"

#define LINE_MAX 0xFFFFF

double **create_matrix(int l, int c){
    double **M = malloc (sizeof(double*) * l);
	for (int i = 0; i < l; ++i) M[i] = malloc (sizeof(double) * c);
    return M;
}
void delete_matrix(double **M, int l, int c){
	for (int i = 0; i < l; ++i){
		free(M[i]);
	}
	free(M);
}
void imprime(double **A, int l, int c){
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            printf("%.2f ", A[i][j]);
        }
        printf("\n");
    }
}

void carregar_lista(LISTA *lista, char *path){
  double **m;
  int N = 0, value = 0, i, j;
  int a = 0, b=0; // dimensao a x b
  char line[LINE_MAX], *sp, seps[] = " \r\n\t";
  FILE *fp = fopen (path, "r");
  if (fp == NULL) return;
  fseek (fp, 0, SEEK_SET); // reposiciona o ponteiro
  while (fgets(line, LINE_MAX, fp) != NULL) {
    sp = strtok (line, seps);
    for (; sp; ) {
      if(strcmp(sp,"N") == 0){
        sp = strtok (NULL, seps);
        N = atoi(sp);
      }
      else if(strcmp(sp,"DIM") == 0){
        sp = strtok (NULL, seps);
        a = atoi(sp);
        sp = strtok (NULL, seps);
        b = atoi(sp);
        m = create_matrix(a, b);
        i = -1;
        j = 0;
        add(lista, (MATRIX) m, a, b);
      }
      else {
        value = atoi(sp);
        m[i][j++] = value;
      }
      sp = strtok (NULL, seps);
    }
    j = 0;
    i++;
  }
  fclose(fp);
}

