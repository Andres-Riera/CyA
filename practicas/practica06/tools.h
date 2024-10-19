// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 06/10/2024
// Archivo tools.h
// Contiene la función Usage

#pragma once

#include <iostream>

// Esta función se encarga de verificar que los parámetros sean correctos y proporciona ayuda al usuario en caso de que
// haya algún error con estos
void Usage(int argc, char *argv[]) {
  if (argc == 2) {
    std::string parameter{argv[1]};
    if (parameter == "--help") {
      std::cout << "El programa recibe como parámetros un archivo .cc de entrada y el nombre del archivo de salida"
                << "e imprime en este último\nun análisis del codigo .cc dado" << std::endl;
      exit(EXIT_SUCCESS);
    }
  }

  if (argc != 3) {
    std::cout << "Modo de empleo: " << argv[0] << " filein.cc fileout.txt" << std::endl;
    std::cout << "Pruebe " << argv[0] << " --help para más información" << std::endl;
    exit(EXIT_SUCCESS);
  }
}