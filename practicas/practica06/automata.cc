#include "automata.h"

Automata::Automata(Alfabeto alfabeto, int estados, int inicial,
                   std::vector<std::string> info_estados) {
  alfabeto_ = alfabeto;
  estados_.resize(estados);
  estado_arranque_ = inicial;
  for (std::string linea : info_estados) {
        std::istringstream stream(linea);
        int aux;
        stream >> aux;
        int accept;
        stream >> accept;
        estados_[aux].aceptacion = accept;
        int n_transiciones;
        stream >> n_transiciones;
        estados_[aux].transiciones.resize(n_transiciones);
        for (int i = 0; i < n_transiciones; ++i) {
            Transicion transicion;
            stream >> transicion.simbolo >> transicion.sig_estado;
            estados_[aux].transiciones[i] = transicion;
        }
    }
}

bool Automata::cadena_pertenece(Cadena string) {
  int estado_act = estado_arranque_;
  std::string aux = string.get_cadena();
  for (int i = 0; i < aux.size(); i++) {
    estado_act = transicion_(estado_act, aux[i]);
  }
  return estados_[estado_act].aceptacion;
}

int Automata::transicion_(int est_act, char simbol) {
  int estado_siguiente = -1;
  for (int i = 0; i < estados_[est_act].transiciones.size(); i++) {
    if (estados_[est_act].transiciones[i].simbolo == simbol) {
      estado_siguiente = estados_[est_act].transiciones[i].sig_estado;
    }
  }
  return estado_siguiente;
}