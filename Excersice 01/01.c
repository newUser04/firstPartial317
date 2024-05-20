#include <stdio.h>

void add(int *number1, int *number2, int*result)
{
  *result = *number1 + *number2;
}

void subtract(int *number1, int *number2, int*result)
{
  *result = *number1 - *number2;
}

void multiply(int *number1, int *number2, int*result)
{
  *result = 0;
  for(int i = 0; i < *number2; i++)
  {
    add(&*result, &*number1, &*result);
  }
}

void divide(int *number1, int *number2, int *result)
{
  *result = 0;
  if(*number2 == 0) return;

  while(*number1 >= *number2)
  {
    (*result)++;
    subtract(&*number1, &*number2, &*number1);
  }

}

void main()
{
  int a;
  int b;
  int c;

  printf("Ingresar Entero Positivo 1: ");
  scanf("%d", &a);
  printf("Ingresar Entero Positivo 2: ");
  scanf("%d", &b);
  printf("-----------------------------\n");

  printf("Número 1: %d; Número 2: %d\n", a, b);
  printf("--------------------------\n");

  add(&a, &b, &c);
  printf("Adición: %d\n", c);

  subtract(&a, &b, &c);
  printf("Resta: %d\n", c);

  multiply(&a, &b, &c);
  printf("Multiplicación: %d\n", c);

  divide(&a, &b, &c);
  printf("División: %d; Resto: %d\n", c, a);
  printf("-----------------------\n");

  printf("Número 1: %d; Número 2: %d\n", a, b);
}