#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main (int argc, char** argv)
{
  MPI_Init(&argc, &argv);
  int ws, wr, n;
  MPI_Comm_size(MPI_COMM_WORLD, &ws);
  MPI_Comm_rank(MPI_COMM_WORLD, &wr);

  if (wr == 0)
  {
    printf("Ingress N: \n");
    scanf("%d", &n);
    printf("-----------\n");
  }

  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  int root = 0;

  int from = wr * n;
  int to = (wr + 1) * n;
  int j = 0;

  int* v = (int*)malloc(sizeof(int) * n);
  for (int i = from; i < to; i++)
  {
    v[j] = (i + 1) * 2;
    j++;
  }
  j = 0;
  printf("Vector in Process %d:\n\t", wr);
  for (int i = from; i < to; i++)
  {
    printf("| %d ", v[j]);
    j++;
  }
  printf("|\n");

  if(wr == root)
  {
    int counts[ws];
    int displacements[ws];
    for (int i = 0; i < ws; i++)
    {
      counts[i] = n;
      displacements[i] = i * n;
    }

    int* buffer = (int*)calloc(n * ws, sizeof(int));
    MPI_Gatherv(v, n, MPI_INT, buffer, counts, displacements, MPI_INT, root, MPI_COMM_WORLD);

    printf("Every Vectors in Process %d\n\t", root);
    for (int i = 0; i < n * ws; i++)
    {
      printf("| %d ", buffer[i]);
    }
    printf("|\n");
    free(buffer);
  }
  else
  {
    MPI_Gatherv(v, n, MPI_INT, NULL, NULL, NULL, MPI_INT, root, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return 0;
}
