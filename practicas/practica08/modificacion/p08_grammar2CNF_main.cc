// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 04/11/2024
// Archivo p08_grammar2CNF_main.cc : Programa cliente
// El programa lee un archivo .gra recibido como parametro que contiene una
// gramática simplificada e imprime en otro archivo .gra, también recibido como
// parametro de entrada, la gramática dada en forma normal de Chomsky
// Bugs: El programa solo puede manejar hasta 26 símbolos no terminales (Esto es
//       debido a que los símbolos no terminales se representan mediante un
//       char). Es posible que el programa funcione incorrectamente si hay algún
//       símbolo terminal que sea una letra en mayúscula. Si no se especifica el
//       número correcto de terminales o no terminales el programa no funcionará
//       correctamente.

#include <fstream>

#include "gramatica.h"
#include "tools.h"

int main(int argc, char* argv[]) {
  Usage(argc, argv);
  std::ifstream grammar_in{argv[1]};
  if (!grammar_in) {
    std::cerr << "Error al abrir el archivo de entrada.\n";
    return 1;
  }
  int linea{0};
  char terminal;
  std::set<char> terminales;
  int i;
  grammar_in >> i;
  linea++;
  for (int j = 0; j < i; j++) {
    grammar_in >> terminal;
    terminales.insert(terminal);
    linea++;
  }

  char no_terminal;
  std::set<char> no_terminales;
  grammar_in >> i;
  linea++;
  bool first{1};
  char arranque;
  for (int j = 0; j < i; j++) {
    grammar_in >> no_terminal;
    if (first) {
      arranque = no_terminal;
      first = 0;
    }
    no_terminales.insert(no_terminal);
    linea++;
  }

  std::set<Produccion> producciones;
  grammar_in >> i;
  linea++;
  std::string aux;
  for (int j = 0; j < i; j++) {
    grammar_in >> no_terminal;
    grammar_in >> aux;
    linea++;
    if (aux.size() == 1) {
      if (IsIn(aux[0], no_terminales)) {
        std::cerr << "Error en línea " << linea
                  << ": producción unitaria detectada\n";
        return 1;
      } else if (aux[0] == '&' && no_terminal != arranque) {
        std::cerr << "Error en línea " << linea
                  << ": producción vacía detectada\n";
        return 1;
      }
    }
    for (int k = 0; k < aux.size(); k++) {
      if (aux[k] != '&') {
        if (!IsIn(aux[k], no_terminales) && !IsIn(aux[k], terminales)) {
          std::cerr << "Error en línea " << linea << ": símbolo inválido\n";
          return 1;
        }
      } else if (aux[k] == '&' && aux.size() > 1) {
        std::cerr << "Error en línea " << linea << ": símbolo inválido\n";
        return 1;
      }
    }
    Produccion regla;
    regla.no_terminal_ = no_terminal;
    regla.regla_ = aux;
    producciones.insert(regla);
  }
  Gramatica grammar{terminales, no_terminales, producciones, arranque};
  if(grammar.EsLinealPorLaDerecha()) {
    std::cout << "This grammar is right-linear" << std::endl;
  } else {
    std::cout << "This grammar is not right-linear" << std::endl;
  }
  Gramatica x = grammar.Chomsky();
  std::ofstream grammar_out(argv[2]);
  grammar_out << x;
  return 0;
}