#pragma once

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
           std::vector<std::string> info_estados);
  bool cadena_pertenece(Cadena string);

 private:
  Alfabeto alfabeto_;
  std::vector<Estado> estados_;
  int estado_arranque_;
  int transicion_(int est_act, char simbol);
};