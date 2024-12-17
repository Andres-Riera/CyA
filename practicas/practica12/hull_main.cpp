#include <fstream>

#include "point_set.hpp"

int main() {
  CyA::point p;
  CyA::point_vector vec_p;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> p.first >> p.second;
    vec_p.push_back(p);
  }
  CyA::point_set resultado(vec_p);
  resultado.quickHull();
  resultado.write(std::cout);

  std::ofstream dot_file("output_mod.dot");
  resultado.write_hull(dot_file);
}