// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 17/09/2024
// Archivo alfabeto.h
// Contiene la declaración de la clase Alfabeto

#pragma once

#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <vector>

class Alfabeto {
 public:
  Alfabeto() = default;            // Constructor por defecto
  Alfabeto(std::string simbolos);  // Constructor a partir de una string
  bool is_in(char simbolo);
  friend std::ostream& operator<<(
      std::ostream& out, const Alfabeto& a);  // Sobrecarga del operador de salida

 private:
  std::set<char> simbolos_;
};
