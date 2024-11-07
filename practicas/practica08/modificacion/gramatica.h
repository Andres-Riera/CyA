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
// Este archivo contiene la declaración de la clase Gramatica y de la función IsIn

#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct Produccion {
  char no_terminal_;
  std::string regla_;

  bool operator<(const Produccion& other) const;
};

std::ostream& operator<<(std::ostream& out, const Produccion& produccion);

class Gramatica {
 public:
  Gramatica(std::set<char> terminales, std::set<char> no_terminales,
            std::set<Produccion> producciones, char simbolo): terminales_(terminales),
            no_terminales_(no_terminales), producciones_(producciones), 
            simbolo_arranque_(simbolo) {}
  // Devuelve la gramática transformada en forma nomal de Chomsky
  Gramatica Chomsky();
  friend std::ostream& operator<<(std::ostream& out,
                                  const Gramatica& gramatica);
  // modificación
  bool EsLinealPorLaDerecha();

 private:
  std::set<char> terminales_;
  std::set<char> no_terminales_;
  std::set<Produccion> producciones_;
  char simbolo_arranque_;
};

bool IsIn(char simbolo, std::set<char> conjunto);