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

Cadena::Cadena(std::string cadena, std::string alphabet) : 
              longitud_(cadena.size()), alfabeto_(alphabet) {
  if (cadena != "&") {
    for (int i = 0; i < cadena.size(); i++) {
      cadena_.push_back(cadena[i]);
    }
  } else {
    cadena_.resize(0);
    longitud_ = 0;
  }
}

Cadena::Cadena(std::string cadena, Alfabeto alphabet) : 
              longitud_(cadena.size()), alfabeto_(alphabet) {
  if (cadena != "&") {
    for (int i = 0; i < cadena.size(); i++) {
      cadena_.push_back(cadena[i]);
    }
  } else {
    cadena_.resize(0);
    longitud_ = 0;
  }
  
}

Cadena Cadena::inversa() {
  std::string cadena;
  cadena.resize(longitud_);
  for (int i = 0; i < cadena_.size(); i++) {
    cadena[i] = cadena_[cadena_.size() - 1 - i];
  }
  Cadena inversa {cadena, alfabeto_};
  return inversa;
}

void Cadena::prefijos(std::ofstream& archivo) {
  archivo << "{&";
  if (cadena_.size() != 0) {
    archivo << ", ";
  }
  int i {0};
  while (i != cadena_.size()) {
    i++;
    for (int j = 0; j < i; j++) {
      archivo << cadena_[j];
    }
    if (i != cadena_.size()) {
      archivo << ", ";
    }
  }
  archivo << '}';
}

void Cadena::sufijos(std::ofstream& archivo) {
  archivo << "{&";
  if (cadena_.size() != 0) {
    archivo << ", ";
  }
  int i {longitud_};
  while (i != 0) {
    i--;
    for (int j = i; j < longitud_; j++) {
      archivo << cadena_[j];
    }
    if (i != 0) {
      archivo << ", ";
    }
  }
  archivo << '}';
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

// modificación

Cadena Cadena::potencia(int n) {
  std::string cadena;
  cadena.resize(longitud_ * n);
  int aux {0};
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < longitud_; j++) {
      cadena[aux++] = cadena_[j];
    }
  }
  Cadena potencia(cadena, alfabeto_);
  return potencia;
}