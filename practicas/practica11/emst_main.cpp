#include <fstream>

#include "bosque.hpp"

int main(int argc, char* argv[]) {
  bool dot = false;
  if (argc > 1) {
    std::string arg1 = argv[1];
    if (arg1 == "-d") {
      dot = true;
    }
  }

  CyA::point_vector puntos;
  std::cin >> puntos;

  EMST::point_set resultado(puntos);
  
  resultado.EMST();
  resultado.write_tree(std::cout);
  if (dot) {
    std::ofstream dot_file("output.dot");
    resultado.write(dot_file);
  }
  return 0;
}