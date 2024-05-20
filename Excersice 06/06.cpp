#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main (int argc, char** argv)
{
  int wr, ws, i, result = 0, sum = 0;
  double x, y;
  float pi, begin, end;

  int points = 100000000;

  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &wr);
  MPI_Comm_size(MPI_COMM_WORLD, &ws);
  
  MPI_Barrier(MPI_COMM_WORLD);
  begin = MPI_Wtime();
  
  srand(time(NULL) * wr);
  
  for (i = wr; i < points; i += ws)
  {
    x = rand() / (RAND_MAX + 1.0);
    y = rand() / (RAND_MAX + 1.0);
    if(x * x + y * y <1.0)
    {
      result++;
    }
  }
  printf("\tResult: %d in Process %d\n", result, wr);
  
  MPI_Reduce(&result, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  
  MPI_Barrier(MPI_COMM_WORLD);
  end = MPI_Wtime();
  
  if (wr == 0)
  {
    pi = 4 * ((float)sum / (float)points);
    printf("Sum: %d || Time: %fs || PI: %f\n", sum, end - begin, pi);
  }
  
  MPI_Finalize();
  
  return 0;
}