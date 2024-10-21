// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Autómatas finitos
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 20/10/2024
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
      std::cout << "El programa recibe como parámetros un archivo .fa de "
                   "entrada que contiene la información de un autómata finito\n"
                   "y un archivo .txt que contiene las cadenas a ser "
                   "analizadas por el autómata dado e imprime si estas cadenas\n"
                << "son aceptadas o rechazadas" << std::endl;
      exit(EXIT_SUCCESS);
    }
  }

  if (argc != 3) {
    std::cout << "Modo de empleo: " << argv[0] << " input.fa input.txt"
              << std::endl;
    std::cout << "Pruebe " << argv[0] << " --help para más información"
              << std::endl;
    exit(EXIT_SUCCESS);
  }
}