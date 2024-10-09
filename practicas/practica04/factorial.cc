/**
2 * Universidad de La Laguna
3 * Escuela Superior de Ingenieria y Tecnologia
4 * Informatica Basica
5 *
6 * @brief Ejercicios de programacion
7 * Version 1: Funcion factorial
8 *
9 * @see https :// github .com/IB -   -  / IB -class -code - examples /
*/
 
# include <iostream>
# include <cassert>
 
  // Returns the factorial of the argument
int Factorial (int number ) {
  switch ( number ) {
  case 0:
  case 1:
  return 1;
  default :
  int factorial = 1;
  for (int i = 1; i <= number ; ++ i ) {
  factorial *= i ;
  }
  return factorial ;
  }
  }

int main () {
  std :: cout << " Introduzca el numero de factoriales a calcular : ";
  int limit ;
  std :: cin >> limit ;
  for (int i = 1; i <= limit ; ++ i ) {
  std :: cout << i << "! = " << ( double ) Factorial ( i ) << std :: endl ;
  }
  }
