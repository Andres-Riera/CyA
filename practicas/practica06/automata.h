// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Autómatas finitos
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 20/10/2024
// Archivo automata.h
// Contiene la declaración de la clase Automata

#pragma once

#include <algorithm>
#include <sstream>

#include "alfabeto.h"
#include "cadena.h"

struct Transicion {
  char simbolo;
  int sig_estado;
};

struct Estado {
  int aceptacion;  // 0 si no es de aceptación o 1 si lo es
  std::vector<Transicion> transiciones;
};

class Automata {
 public:
  Automata(Alfabeto alfabeto, int estados, int arranque,
           std::vector<std::string> info_estados);  // Constructor de la clase
  bool cadena_pertenece(Cadena string);  // Devuelve true si la Cadena es
                                         // reconocida por el automata
 private:
  Alfabeto alfabeto_;
  std::vector<Estado> estados_;
  int estado_arranque_;
  std::vector<int> transicion_(std::vector<int> est_act,
                               char simbol);  // Realiza las transiciones
};