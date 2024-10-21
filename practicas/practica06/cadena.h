// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Autómatas finitos
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 20/10/2024
// Archivo cadena.h
// Contiene la declaración de la clase Cadena

#pragma once

#include <fstream>
#include <vector>

#include "alfabeto.h"

class Cadena {
 public:
  Cadena() = default; // Constructor por defecto
  Cadena(std::string cadena, Alfabeto alphabet); // Constructor a partir de una string y un Alfabeto
  Alfabeto mostrar_alfabeto() { return alfabeto_;} // Devuelve el alfabeto al que pertenece la cadena
  std::string get_cadena(); // Devuelve la cadena en tipo std::string
  int get_longitud() { return longitud_; } // Devuelve la longitud de la cadena
  friend std::ostream& operator<<(std::ostream& out, const Cadena& a); // Sobrecarga del operador de salida para la clase Cadena
  
 private:
  std::vector<char> cadena_;
  Alfabeto alfabeto_;
  int longitud_;
};