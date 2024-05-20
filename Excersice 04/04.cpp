#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "omp.h"
using namespace std;

int main(int argc, char** argv)
{
  int n = 8, a[n][n], b[n], c[n], c_aux = 1;
  for(int i = 1; i <= n; i++)
  {
    b[i - 1] = i;
    for(int j = 1; j <= n; j++)
    {
      a[i - 1][j -1 ] = c_aux;
      c_aux++;
    }
  }

  printf("Vector n:\n\t");
  for(int i = 0; i < 8; i++)
  {
    printf("| %d ", b[i]);
  }
  printf("|\n");

  printf("Matriz n*n:\n");
  for(int i = 0; i < 8; i++)
  {
    printf("\t");
    for(int j = 0; j < 8; j++)
    {
      printf("| %d", a[i][j]);
    }
    printf("|\n");
  }

  #pragma omp parallel for
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      printf("Process: %d || i: %d || j: %d\n", omp_get_thread_num(), i, j);
      c[i] += a[i][j] * b[j];
    }
  }
  printf("----------------------\n");
  printf("Matriz nxn * Vector n:\n");
  for(int i = 0; i < n; i++)
  {
    printf("\t");
    printf("| %d ", c[i]);
    printf("|\n");
  }

  return 0;
}