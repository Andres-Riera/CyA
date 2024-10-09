/**  Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Computabilidad y Algoritmia
  * Curso: 2º
  * Práctica 2: Cadenas y lenguajes
  * Autor: Andrés David Riera Rivera
  * Correo: alu0101618654@ull.edu.es
  * Fecha: 06/10/2024
  * Archivo analisis.cc
  * Contiene la definición de la clase y los métodos a utilizar para el análisis
  */

#include "analisis.h"

// Constructor de la clase Analisis
Analisis::Analisis(std::ifstream& archivo_entrada, std::string 
nombre) {
  nombre_ = nombre;
  main_ = false;
  n_double_ = 0;
  n_for_ = 0;
  n_int_ = 0;
  n_while_ = 0;
  std::string linea;
  int n_linea{0};
  while(std::getline(archivo_entrada, linea)) {
    n_linea++;
    std::regex line_comment("\\s*\\/\\/.*");
    std::regex multi_linecomment("\\s*\\/\\*.*");
    std::regex variable("\\s*(int|double)\\s\\S+\\s?[=\\(\\{]?\\s?\\d*.?\\d*[\\)\\}]?;.*");
    std::regex bucle("\\s*(for|while|switch)\\s?\\(.*\\).*");
    std::regex main_true("\\S*\\s*main\\s?\\(.*\\)\\s?\\{?");
    if (std::regex_match(linea, line_comment)) {
      add_comentario_(linea, n_linea, n_linea);
    } else if (std::regex_match(linea, multi_linecomment)) {
      int i = n_linea;
      std::string aux = linea;  
      std::regex multiline_comment_end("\\s*\\*\\/\\.*");
      while(!std::regex_match(linea, multiline_comment_end)) {
        std::getline(archivo_entrada, linea);
        aux += "\n" + linea;
        n_linea++;
      }
      add_comentario_(aux, i, n_linea);
    } else if (std::regex_match(linea, main_true)) {
      main_ = true;
    } else if (std::regex_match(linea, bucle)) {
      add_bucle_(linea, n_linea);
    } else if (std::regex_match(linea, variable)) {
      add_variable_(linea, n_linea);
    } 
  }
}

// Añade un comentario
void Analisis::add_comentario_(std::string comentario, int inicio, int fin) {
  Datos aux;
  aux.dato = comentario;
  aux.linea_inicio = inicio;
  aux.linea_fin = fin;
  comentarios_.push_back(aux);
}

// Añade una variable
void Analisis::add_variable_(std::string tipo, int linea) {
  Datos aux;
  aux.linea_inicio = linea;
  if (tipo.find("int ") != std::string::npos) {
    std::regex aux2("int ");
    tipo = std::regex_replace(tipo, aux2, "");
    aux2 = ";";
    tipo = std::regex_replace(tipo, aux2, "");
    std::regex multiple_spaces("\\s\\s+");
    tipo = std::regex_replace(tipo, multiple_spaces, "");
    aux.dato = tipo;
    aux.linea_fin = 0; 
    n_int_++;
  } else {
    std::regex aux2("double ");
    tipo = std::regex_replace(tipo, aux2, "");
    aux2 = ";";
    tipo = std::regex_replace(tipo, aux2, "");
    std::regex multiple_spaces("\\s\\s+");
    tipo = std::regex_replace(tipo, multiple_spaces, "");
    aux.dato = tipo; 
    aux.linea_fin = 1;
    n_double_++;
  }
  variables_.push_back(aux);
}


// Añade un bucle o un switch
void Analisis::add_bucle_(std::string bucle, int linea) {
  Datos aux;
  if (bucle.find("for") != std::string::npos) {
   aux.dato = "for"; 
   aux.linea_fin = 0;
   n_for_++;
  } else if (bucle.find("while") != std::string::npos){
    aux.dato = "while"; 
    aux.linea_fin = 1;
    n_while_++;
  } else {
    std::regex var1("switch\\s?\\(");
    aux.dato = std::regex_replace(bucle, var1, "");
    std::regex var2("\\).*");
    aux.dato = std::regex_replace(aux.dato, var2, "");
    std::regex multiple_spaces("\\s\\s+");
    aux.dato = std::regex_replace(aux.dato, multiple_spaces, "");
    aux.linea_fin = 2;
  }
  aux.linea_inicio = linea;
  bucles_.push_back(aux);
}

// Sobrecarga del operador de salida
std::ostream& operator<<(std::ostream& out, const Analisis& a) {
  out << "PROGRAM: " << a.nombre_ << "\n";
  if (a.comentarios_.size() > 0 && a.comentarios_[0].linea_inicio == 1) {
    out << "\nDESCRIPTION:\n" << a.comentarios_[0].dato << "\n";
  }

  out << "\nVARIABLES:\n";
  for(Datos aux : a.variables_) {
    if (aux.linea_fin == 0) {
      out << "[Line " << aux.linea_inicio << "] INT: " << aux.dato << "\n";
    } else {
      out << "[Line " << aux.linea_inicio << "] DOUBLE: " << aux.dato << "\n";
    }
  }

  out << "\nSTATEMENTS:\n";
  for(Datos aux : a.bucles_) {
    out << "[Line " << aux.linea_inicio << "]";
    if (aux.linea_fin == 0) {
      out << " LOOP: for\n";
    } else if (aux.linea_fin == 1) {
      out << " LOOP: while\n";
    } else {
      out << " SWITCH: " << aux.dato << "\n";
    }
  }

  out << "\nMAIN:\n";
  if(a.main_) {
    out << "True\n";
  } else {
    out << "False\n";
  }
  
  out << "\nCOMMENTS:\n";
  for (Datos aux : a.comentarios_){
    if (aux.linea_inicio == 1) {
      if (aux.linea_fin == 1) {
        out << "[Line 1]: DESCRIPTION\n";
      } else {
        out << "[Lines 1-" << aux.linea_fin << "] DESCRIPTION\n";
      }
    } else {
      if (aux.linea_inicio == aux.linea_fin) {
        out << "[Line " << aux.linea_inicio << "] " << aux.dato << "\n";
      } else {
        out << "[Lines " << aux.linea_inicio << "-" << aux.linea_fin << "] " << aux.dato << "\n";
      }
    }
  }
  return out;
}
