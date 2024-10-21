// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Autómatas finitos
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 20/10/2024
// Archivo p06_automata_simulator_main.cc : Programa cliente
// El programa lee un archivo con el que crea un autómata finito con el que
// informa si las cadenas leídas de otro archivo son aceptadas o rechazadas

#include "automata.h"
#include "tools.h"

int main(int argc, char* argv[]) {
  Usage(argc, argv);
  std::ifstream automata_file{argv[1]};
  if (!automata_file) {
    std::cerr << "Error al abrir el archivo del autómata.\n";
    return 1;
  }
  
  std::string simbolos;
  std::getline(automata_file, simbolos);
  Alfabeto alphabet(simbolos);
  int n_estados;
  automata_file >> n_estados;
  int arranque;
  automata_file >> arranque;

  std::vector<std::string> info_estados;
  std::string linea;
  while (std::getline(automata_file, linea)) {
    if (!linea.empty()) {
      info_estados.push_back(linea);
    }
  }
  Automata automata_obj(alphabet, n_estados, arranque, info_estados);

  std::ifstream cadenas{argv[2]};
  if (!cadenas) {
    std::cerr << "Error al abrir el archivo de cadenas.\n";
    return 1;
  }

  std::string aux;
  while (std::getline(cadenas, aux)) {
    Cadena cadena_A(aux, alphabet);
    std::cout << cadena_A << " --- ";
    if (automata_obj.cadena_pertenece(cadena_A)) {
      std::cout << " Accepted\n";
    } else {
      std::cout << " Rejected\n";
    }
  }

  return 0;
}