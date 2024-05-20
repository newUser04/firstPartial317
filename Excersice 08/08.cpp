#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "omp.h"

int main() {
  int np = omp_get_max_threads();
  int n;

  printf("Processors: %d\n", np);
  printf("--------------\n");

  printf("Ingress N: ");
  scanf("%d", &n);
  printf("---------\n");

  int result[np][n];

  #pragma omp parallel shared(result)
  {
    int p = omp_get_thread_num();
    int from = p * n;
    int to = (p + 1) * n;
    int l = 0;

    printf("Process: %d || From: %d || To: %d\n", p, from + 1, to);

    for (int k = from; k < to; k++)
    {
      result[p][l] = 2 * (k + 1);
      printf("\tValue: %d, Row: %d, Col: %d\n", result[p][l], p, l);
      l++;
    }
  }
  
  printf("---------------------------------\n");

  for (int i = 0; i < np; i++)
  {
    printf("\t| ");
    for (int j = 0; j < n; j++)
    {
      printf(" %d |", result[i][j]);
    }
    printf("\n");
  }

  return 0;
}