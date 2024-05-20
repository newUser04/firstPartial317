#include <iostream>

void add(int* number1, int* number2, int* result)
{
  *result = *number1 + *number2;
}

void subtract(int* number1, int* number2, int* result)
{
  *result = *number1 - *number2;
}

void multiply(int* number1, int* number2, int* result)
{
  *result = 0;
  for(int i = 0; i < *number2; i++)
  {
    add(&*result, &*number1, &*result);
  }
}

void divide(int* number1, int* number2, int* result)
{   
  *result = 0;
  if(*number2 == 0)
  {
    std::cout << "Error de División entre Cero." << std::endl;
    return;
  }
  while(*number1 >= *number2)
  {
    *result = *result + 1;
    subtract(&*number1, &*number2, &*number1);
  }
}


int main() {
  int a;
  int b;
  int c;

  std::cout << "Ingresar Entero 1: ";
  std::cin >> a;
  std::cout << "Ingresar Entero 2: ";
  std::cin >> b;
  std::cout << "--------------------" << std::endl;

  std::cout << "Número 1: " << a << "; Número 2: " << b << std::endl;
  std::cout << "---------------------------------" << std::endl;

  add(&a, &b, &c);
  std::cout << "Addition: " << c << std::endl;

  subtract(&a, &b, &c); 
  std::cout << "Subtraction: " << c << std::endl;

  multiply(&a, &b, &c);
  std::cout << "Multiplication: " << c << std::endl;

  divide(&a, &b, &c);
  std::cout << "Division: " << c << "; Resto: " << a <<std::endl;
  std::cout << "----------------------------" << std::endl;

  std::cout << "Número 1: " << a << "; Número 2: " << b << std::endl;

  return 0;
}