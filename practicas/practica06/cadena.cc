// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 17/09/2024
// Archivo cadena.cc
// Contiene la definición de la clase Cadena

#include "cadena.h"

Cadena::Cadena(std::string cadena, Alfabeto alphabet) : 
              longitud_(cadena.size()), alfabeto_(alphabet) {
  if (cadena != "&") {
    for (int i = 0; i < cadena.size(); i++) {
      assert(alphabet.is_in(cadena[i]));
      cadena_.push_back(cadena[i]);
    }
  } else {
    cadena_.resize(0);
    longitud_ = 0;
  }
  
}

std::string Cadena::get_cadena() {
  if (cadena_.size() == 0) {
    std::string vacia = "&";
    return vacia;
  }
  std::string string = "";
  for (char i : cadena_) {
    string += i;
  }
  return string;
}

std::ostream& operator<<(std::ostream& out, const Cadena& a) {
  if (a.longitud_ == 0) {
    out << '&';
  }
  for (int i = 0; i < a.longitud_; i++) {
    out << a.cadena_[i];
  }
  return out;
}