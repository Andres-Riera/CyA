// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Autómatas finitos
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 20/10/2024
// Archivo alfabeto.cc
// Contiene la definición de la clase Alfabeto

#include "alfabeto.h"

Alfabeto::Alfabeto(std::string simbolos) {
  for (int i = 0; i < simbolos.size(); i++) {
    assert(simbolos[i] != '&');
    if (simbolos[i] != ' '){
      simbolos_.insert(simbolos[i]);
    }
  }
}

bool Alfabeto::is_in(char a) {
  return simbolos_.find(a) != simbolos_.end();
}

std::ostream& operator<<(std::ostream& out, const Alfabeto& a) {
  out << '{';
  for (auto i = a.simbolos_.begin(); i != a.simbolos_.end(); i++) {
    out << *i;
    if (std::next(i) != a.simbolos_.end()) {
      out << ", ";
    }
  }
  out << '}';
  return out;
}