// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 04/11/2024
// Archivo gramatica.cc
// Este archivo contiene las definiciones de las funciones y métodos declarados
// en el archivo "gramatica.h"

#include "gramatica.h"

Gramatica Gramatica::Chomsky() {
  std::set<Produccion> productions;
  std::set<char> non_terminals{no_terminales_};
  std::set<char> terminals{terminales_};
  // Primer bucle del algoritmo
  std::map<char, char>
      simbolos_no_terminales;  // Nuevas producciones del tipo A -> a
  for (Produccion i : producciones_) {
    Produccion aux{i};
    if (aux.regla_.size() > 1) {
      for (int j = 0; j < aux.regla_.size(); j++) {
        // Si el símbolo es terminal entonces lo sustituimos por un no terminal
        if (IsIn(aux.regla_[j], terminals)) {
          // Si no tiene un no terminal asignado entonces creamos uno
          if (simbolos_no_terminales.find(aux.regla_[j]) ==
              simbolos_no_terminales.end()) {
            char new_no_terminal{'A'};
            // Buscamos un nuevo símbolo no terminal que no esté en uso
            while (IsIn(new_no_terminal, non_terminals)) {
              new_no_terminal += 1;
              if (new_no_terminal > 'Z') {
                std::cerr << "Error: Límite de no terminales sobrepasado"
                          << std::endl;
                exit(EXIT_SUCCESS);
              }
            }
            // Creamos una nueva producción para el símbolo terminal
            Produccion aux2;
            aux2.no_terminal_ = new_no_terminal;
            aux2.regla_ = std::string(1, aux.regla_[j]);
            // Añadimos la nueva producción
            productions.insert(aux2);
            non_terminals.insert(new_no_terminal);
            simbolos_no_terminales[aux.regla_[j]] = new_no_terminal;
          }
          aux.regla_[j] = simbolos_no_terminales[aux.regla_[j]];
        }
      }
    }
    productions.insert(aux);
  }

  // Segundo bucle del algoritmo
  for (Produccion i : productions) {
    if (i.regla_.size() >= 3) {
      std::string regla_actual = i.regla_;
      // Reducción de la producción a 2 símbolos
      while (regla_actual.size() > 2) {
        char nuevo_no_terminal = 'A';
        // Buscar un nuevo símbolo no terminal que no esté en uso
        while (IsIn(nuevo_no_terminal, non_terminals)) {
          nuevo_no_terminal += 1;
          if (nuevo_no_terminal > 'Z') {
            std::cerr << "Error: Límite de no terminales sobrepasado"
                      << std::endl;
            exit(EXIT_SUCCESS);
          }
        }
        non_terminals.insert(nuevo_no_terminal);
        // Crear una nueva producción para los dos últimos caracteres
        Produccion nueva_produccion;
        nueva_produccion.no_terminal_ = nuevo_no_terminal;
        nueva_produccion.regla_ = regla_actual.substr(regla_actual.size() - 2);
        // Insertamos la nueva producción en el conjunto de producciones
        productions.insert(nueva_produccion);
        // Actualizamos la regla actual para que termine con el nuevo no
        // terminal
        regla_actual =
            regla_actual.substr(0, regla_actual.size() - 2) + nuevo_no_terminal;
      }
      // Añadimos la producción acortada y reemplazamos la anterior
      Produccion produccion_final;
      produccion_final.no_terminal_ = i.no_terminal_;
      produccion_final.regla_ = regla_actual;
      productions.erase(i);
      productions.insert(produccion_final);
    }
  }
  return Gramatica(terminals, non_terminals, productions);
}

// Devuelve true si el símbolo se encuentra en el conjunto
bool IsIn(char simbolo, std::set<char> conjunto) {
  return conjunto.find(simbolo) != conjunto.end();
}
// Sobrecarga del operador de salida para la clase Gramatica
std::ostream& operator<<(std::ostream& out, const Gramatica& gramatica) {
  out << gramatica.terminales_.size() << "\n";
  for (char i : gramatica.terminales_) {
    out << i << "\n";
  }
  out << gramatica.no_terminales_.size() << "\n";
  for (char i : gramatica.no_terminales_) {
    out << i << "\n";
  }
  out << gramatica.producciones_.size() << "\n";
  for (Produccion i : gramatica.producciones_) {
    out << i.no_terminal_ << " " << i.regla_ << "\n";
  }
  return out;
}

// Sobrecarga del operador < para el orden del set de Producciones
bool Produccion::operator<(const Produccion& other) const {
  // Priorizar al no terminal S en el set
  if (no_terminal_ == 'S' && other.no_terminal_ != 'S') {
    return true;
  }
  if (no_terminal_ != 'S' && other.no_terminal_ == 'S') {
    return false;
  }
  // En caso de que ninguno sea S entonces se ordena por orden alfabético
  if (no_terminal_ != other.no_terminal_) {
    return no_terminal_ < other.no_terminal_;
  }
  // Si los no terminales son iguales se ordena por la regla
  return regla_ < other.regla_;
}

std::ostream& operator<<(std::ostream& out, const Produccion& produccion) {
  out << produccion.no_terminal_ << " -> " << produccion.regla_ << "\n";
  return out;
}