/**  Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Computabilidad y Algoritmia
  * Curso: 2º
  * Práctica 2: Cadenas y lenguajes
  * Autor: Andrés David Riera Rivera
  * Correo: alu0101618654@ull.edu.es
  * Fecha: 06/10/2024
  * Archivo analisis.h
  * Contiene la declaración de la clase a utilizar para el análisis y la struct Datos
  */

#pragma once

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>


struct Datos {
  int linea_inicio;
  int linea_fin; // en caso de variables o bucles será 0 si es int o for y 1 si es double o while (2 si se trata de un switch)
  std::string dato;
};


class Analisis {
 public:
  Analisis(std::ifstream& archivo_entrada, std::string nombre);
  friend std::ostream& operator<<(std::ostream& out, const Analisis& a);
 private:
  std::string nombre_;
  std::vector<Datos> comentarios_; 
  std::vector<Datos> variables_;
  std::vector<Datos> bucles_;
  bool main_;

  int n_for_;
  int n_while_;
  int n_int_;
  int n_double_;

  void add_comentario_(std::string comentario, int inicio, int fin);
  void add_variable_(std::string tipo, int linea);
  void add_bucle_(std::string bucle, int linea);
};
