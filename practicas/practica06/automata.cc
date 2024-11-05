// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Autómatas finitos
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 20/10/2024
// Archivo automata.cc
// Contiene la definición de la clase Automata

#include "automata.h"

Automata::Automata(Alfabeto alfabeto, int estados, int inicial,
                   std::vector<std::string> info_estados) {
  alfabeto_ = alfabeto;
  estados_.resize(estados);
  estado_arranque_ = inicial;
  for (std::string linea : info_estados) {
    std::istringstream stream(linea);
    int posicion;
    stream >> posicion;

    int accept;
    stream >> accept;
    estados_[posicion].aceptacion = accept;

    int n_transiciones;
    stream >> n_transiciones;
    estados_[posicion].transiciones.resize(n_transiciones);

    for (int i = 0; i < n_transiciones; ++i) {
      Transicion transicion;
      stream >> transicion.simbolo >> transicion.sig_estado;
      if (!alfabeto_.is_in(transicion.simbolo) && transicion.simbolo != '&') {
        std::cerr << "Error símbolo de transición no perteneciente al alfabeto"
                  << std::endl;
        exit(EXIT_SUCCESS);
      }
      estados_[posicion].transiciones[i] = transicion;
    }
  }
}

bool Automata::cadena_pertenece(Cadena string) {
  std::vector<int> estado_act;
  estado_act.push_back(estado_arranque_);
  std::string aux = string.get_cadena();

  // Transiciones
  for (int i = 0; i < aux.size(); i++) {
    estado_act = transicion_(estado_act, aux[i]);
  }

  // Comprobar si uno de los estados del conjunto actual es de aceptación
  for (int i = 0; i < estado_act.size(); i++) {
    if (estados_[estado_act[i]].aceptacion == 1) {
      return true;
    }
  }
  return false;
}

std::vector<int> Automata::transicion_(std::vector<int> est_act, char simbol) {
  // Comprobar epsilon-transiciones
  for (int i = 0; i < est_act.size(); i++) {
    for (int j = 0; j < estados_[est_act[i]].transiciones.size(); j++) {
      if (estados_[est_act[i]].transiciones[j].simbolo == '&' ) {
        // Evitar ciclos de epsilon-transiciones
        if (std::find(est_act.begin(), est_act.end(), 
                      estados_[est_act[i]].transiciones[j].sig_estado) == est_act.end()) {
          est_act.push_back(estados_[est_act[i]].transiciones[j].sig_estado);
        }
      }
    }
  }
  std::vector<int> estado_siguiente;
  for (int i = 0; i < est_act.size(); i++) {
    for (int j = 0; j < estados_[est_act[i]].transiciones.size(); j++) {
      if (estados_[est_act[i]].transiciones[j].simbolo == simbol) {
        estado_siguiente.push_back(
            estados_[est_act[i]].transiciones[j].sig_estado);
      }
    }
  }
  return estado_siguiente;
}

void Automata::estados_alcanzables() {
  std::vector<int> alcanzados;
  alcanzados.push_back(estado_arranque_);
  for (int i = 0; i < alcanzados.size(); i++) {
    for (int j = 0; j < estados_[alcanzados[i]].transiciones.size(); j++) {

      
      if (std::find(alcanzados.begin(), alcanzados.end(), 
                      estados_[alcanzados[i]].transiciones[j].sig_estado) == alcanzados.end()) {
          alcanzados.push_back(estados_[alcanzados[i]].transiciones[j].sig_estado);
        }
    }
  }
  std::cout << "\nEstados alcanzados: ";
  for (int i = 0; i < alcanzados.size(); i++) {
    std::cout << alcanzados[i] << " ";
  }
  std::cout << std::endl;
}