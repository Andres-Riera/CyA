#include "automata.h"
#include "tools.h"

int main(int argc, char* argv[]) {
  Usage(argc, argv);
  std::ifstream automata_file {argv[1]};
  if (!automata_file) {
    std::cerr << "Error al abrir el archivo de entrada.\n";
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

  std::ifstream cadenas {argv[2]};
  if (!cadenas) {
    std::cerr << "Error al abrir el archivo de entrada.\n";
    return 1;
  }

  std::string aux;
  while (std::getline(cadenas, aux)) {
    Cadena cadena_A(aux, alphabet);
    std::cout << cadena_A << " --- ";
    if (automata_obj.cadena_pertenece(cadena_A)) {
      std::cout << " aceptada\n";
    } else {
      std::cout << " rechazada\n";
    }
  }
  
  return 0;
}