#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <omp.h>
using namespace std;

int multiply(int number1, int number2)
{
  int result = 0;
  int i;
  #pragma omp parallel private(i)
  {
    printf("Process: %d\n", omp_get_thread_num());
    #pragma omp for
    for(i = 0; i < number2; i++)
    {
      result += number1;
      printf("\tIteration: %d || Process: %d || result: %d\n", i, omp_get_thread_num(), result);
    }
  }

  printf("----------------------------------\n");
  return result;
}

int divide(int number1, int number2)
{
  if(number2 == 0)
  {
    printf("División entre cero.\n");
    return 0;
  }

  int result = 0;

  #pragma omp parallel
  {
    printf("Process: %d\n", omp_get_thread_num());
    while(number1 >= number2)
    {
      number1 -= number2;
      result++;
      printf("\tNumber 1: %d || Process: %d || result: %d\n", number1, omp_get_thread_num(), result);
    }
  } 

  printf("Remainder: %d\n", number1);
  printf("-------------\n");
  return result;
}

int main(int argc, char** argv)
{
  int a, b;
  printf("Insert Integer 1: ");
  cin >> a;
  printf("Insert Integer 2: ");
  cin >> b;
  printf("----------------\n");

  printf("Number 1: %d; Number 2: %d\n", a, b);
  printf("--------------------------\n");
  printf("Multiplicación: %d\n", multiply(a, b));
  printf("------------------\n");
  printf("División: %d\n", divide(a, b));

  return 0;
}