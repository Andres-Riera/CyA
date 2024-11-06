// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 04/11/2024
// Archivo tools.h
// Contiene la función Usage

#pragma once

#include <iostream>

// Esta función se encarga de verificar que los parámetros sean correctos y
// proporciona ayuda al usuario en caso de que haya algún error con estos
void Usage(int argc, char *argv[]) {
  if (argc == 2) {
    std::string parameter{argv[1]};
    if (parameter == "--help") {
      std::cerr
          << "El programa recibe como parámetros un archivo .gra de "
             "entrada que contiene la información de una gramática\n"
             "y un archivo .gra de salida en el que se imprimirá "
             "la gramática en forma normal de Chomsky" << std::endl;
      exit(EXIT_SUCCESS);
    }
  }

  if (argc != 3) {
    std::cerr << "Modo de empleo: " << argv[0] << " input.gra output.gra"
              << std::endl;
    std::cerr << "Pruebe " << argv[0] << " --help para más información"
              << std::endl;
    exit(EXIT_SUCCESS);
  }
}