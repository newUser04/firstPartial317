#include <mpi.h>
#include <stdio.h>
#include <iostream> 
#include <cmath>
#include <math.h>

int binet(int n) {
  float sqrt5 = sqrt(5);
  float phi = (sqrt5 + 1) / 2;
  int result = (int)((pow(phi, (n + 1))) / sqrt5 + 0.5);
  return result;
}

int main(int argc, char** argv) {

  MPI_Init(&argc, &argv);

  int wr, ws, n;
  MPI_Comm_rank(MPI_COMM_WORLD, &wr);
  MPI_Comm_size(MPI_COMM_WORLD, &ws);

  if (wr == 0)
  {
    printf("Ingress N: \n");
    scanf("%d", &n);
    printf("-----------\n");
  }

  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  int MASTER = 0;

  int limit = n / ws;
  int rest = 0;
  int globalRest = n % ws;

  if(wr == ws - 1)
  {
    rest = n % ws;
  }

  int from = wr * limit;
  int to = ((wr + 1) * limit) + rest;
  int j = 0;

  int* v = (int*)malloc(sizeof(int) * n);
  for (int i = from; i < to; i++)
  {
    v[j] = binet(i);
    j++;
  }
  j = 0;
  printf("Vector in SLAVE PROCESS %d:\n\t", wr);
  for (int i = from; i < to; i++)
  {
    printf("| %d ", v[j]);
    j++;
  }
  printf("|\n");

  if(wr == MASTER)
  {
    int SLAVE_COUNTS[ws];
    int SLAVE[ws];
    for (int i = 0; i < (ws - 1); i++)
    {
      SLAVE_COUNTS[i] = limit;
      SLAVE[i] = i * limit;
    }
    SLAVE_COUNTS[ws - 1] = limit + globalRest;
    SLAVE[ws - 1] = ((ws - 1) * limit);

    int* buffer = (int*)calloc(n, sizeof(int));
    MPI_Gatherv(v, (limit + rest), MPI_INT, buffer, SLAVE_COUNTS, SLAVE, MPI_INT, MASTER, MPI_COMM_WORLD);

    printf("MASTER PROCESS result:\n\t");
    for (int i = 0; i < n; i++)
    {
      printf("| %d ", buffer[i]);
    }
    printf("|\n");
    free(buffer);
  }
  else
  {
    MPI_Gatherv(v, (limit + rest), MPI_INT, NULL, NULL, NULL, MPI_INT, MASTER, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return 0;
}