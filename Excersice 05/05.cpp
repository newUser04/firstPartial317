#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  MPI_Init(NULL, NULL);
  int wr, ws;
  MPI_Comm_rank(MPI_COMM_WORLD, &wr);
  MPI_Comm_size(MPI_COMM_WORLD, &ws);

  int n = 4, c_aux = 1, i, j;
  int* m = (int*)malloc(sizeof(int) * n * n);
  int* v = (int*)malloc(sizeof(int) * n);
  int* r = (int*)malloc(sizeof(int) * n);
  int* p = (int*)malloc(sizeof(int) * 3);
  // RECEIVE FROM THE LOWER PROCESS AND SEND TO THE HIGHER PROCESS. TAKE CARE
  // OF THE SPECIAL CASE WHEN YOU ARE THE FIRST PROCESS TO PREVENT DEADLOCK.
  if (wr != 0)
  {
    MPI_Recv(m, n * n, MPI_INT, wr - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(v, n, MPI_INT, wr - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(r, n, MPI_INT, wr - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(p, 5, MPI_INT, wr - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("P %d received from P %d received:\n", wr, wr - 1);
    for (i = 1; i <= n; i++)
    {
      printf("\t| %d |\n", r[i - 1]);
    }
    if (p[2] <= n)
    {
      // GUARD PARAMETERS
      if (p[2] == 0 || n == p[1] + p[0] + p[3])
      {
        p[2] = n;
      }
      for (i = p[1]; i < p[2]; i++)
      {
        for (j = 0; j < n; j++)
        {
          r[i] += m[p[4]] * v[j];
          p[4]++;
        }
      }
    }
    p[1] = p[2];
    p[2] = p[1] + p[0];
  }
  else
  {
    // CREATED MATRIX, VECTOR AND RESULT IN PROCESS "0" WIHT SIZE "N"
    printf("Vector initialized in P %d:\n", wr);
    printf("\t");
    for (i = 1; i <= n; i++)
    {
      v[i - 1] = i;
      r[i - 1] = 0;
      printf("| %d ", v[i - 1]);
    }
    printf("|\n");
    printf("Matriz initialized in P %d:\n", wr);
    for (i = 1; i <= n; i++)
    {
      printf("\t");
      for (j = 1; j <= n; j++)
      {
        m[c_aux - 1] = c_aux;
        printf("| %d ", m[c_aux - 1]);
        c_aux++;
      }
      printf("|\n");
    }
    p[0] = n / ws;
    p[1] = 0;
    p[2] = p[1] + p[0];
    p[3] = n % ws;
    p[4] = 0;
  }
  // MULTIPLY
  MPI_Send(m, n * n, MPI_INT, (wr + 1) % ws, 0, MPI_COMM_WORLD);
  MPI_Send(v, n, MPI_INT, (wr + 1) % ws, 0, MPI_COMM_WORLD);
  MPI_Send(r, n, MPI_INT, (wr + 1) % ws, 0, MPI_COMM_WORLD);
  MPI_Send(p, 5, MPI_INT, (wr + 1) % ws, 0, MPI_COMM_WORLD);

  // NOW PROCESS 0 CAN RECEIVE FORM THE LAST PROCESS. THIS MAKES SURE THAT AT
  // LEAST ONE MPI_SEND IS INITIALIZED BEFORE ALL MPI_RECVS (AGAIN, TO PREVENT
  // DEADLOCK)
  if (wr == 0)
  {
    MPI_Recv(m, n * n, MPI_INT, ws - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(v, n, MPI_INT, ws - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(r, n, MPI_INT, ws - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(p, 5, MPI_INT, ws - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("P %d received from P %d received:\n", wr, ws - 1);
    for (i = 1; i <= n; i++)
    {
      printf("\t| %d |\n", r[i - 1]);
    }
    if (p[2] <= n)
    {
      // GUARD PARAMETERS
      if (p[2] == 0 || n == p[1] + p[0] + p[3])
      {
        p[2] = n;
      }
      for (i = p[1]; i < p[2]; i++)
      {
        for (j = 0; j < n; j++)
        {
          r[i] += m[p[4]] * v[j];
          p[4]++;
        }
      }
    }
    p[1] = p[2];
    p[2] = p[1] + p[0];
    printf("Final processing of %d:\n", wr);
    for (i = 1; i <= n; i++)
    {
      printf("\t| %d |\n", r[i - 1]);
    }
  }

  free(v);
  free(m);
  free(r);
  free(p);
  MPI_Finalize();
  return 0;
}