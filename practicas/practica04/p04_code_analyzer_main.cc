/**  Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Computabilidad y Algoritmia
  * Curso: 2º
  * Práctica 2: Cadenas y lenguajes
  * Autor: Andrés David Riera Rivera
  * Correo: alu0101618654@ull.edu.es
  * Fecha: 06/10/2024
  * Archivo p04_code_analyzer_main.cc: programa cliente.
  * Contiene la función main del proyecto que usa las clases Alfabeto y Cadena
  * para operar con ficheros usando los métodos de la clase Cadena
  */

#include <iostream>
#include <fstream>
#include <regex>

#include "analisis.h"
#include "tools.h"

int main(int argc, char* argv[]) {
  Usage(argc, argv);
  std::ifstream archivo_entrada{argv[1]};
  if (!archivo_entrada) {
    std::cerr << "Error al abrir el archivo de entrada.\n";
    return 1;
  }
  std::string nombre_entrada{argv[1]};
  std::string nombre_salida{argv[2]};
  std::ofstream archivo_salida(nombre_salida);
  Analisis analisis{archivo_entrada, nombre_entrada};
  archivo_salida << analisis;
  return 0;
}