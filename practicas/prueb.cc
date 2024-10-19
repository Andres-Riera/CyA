#include <iostream>
#include <sstream>
#include <string>

int main() {
    // Cadena de texto que simula la entrada de un archivo
    std::string datos = "123 456 789\nHola Mundo\n3.14159";
    
    // Crear un flujo de entrada basado en la cadena
    std::istringstream flujo(datos);
    
    // Leer datos como si fuera de un archivo
    int num1, num2, num3;
    std::string palabra1, palabra2;
    double numeroDecimal;
    
    // Leer los tres números enteros
    flujo >> num1 >> num2 >> num3;
    std::cout << "Numeros leidos: " << num1 << ", " << num2 << ", " << num3 << std::endl;
    
    // Leer las dos palabras
    flujo >> palabra1 >> palabra2;
    std::cout << "Palabras leidas: " << palabra1 << " " << palabra2 << std::endl;
    
    // Leer el número decimal
    flujo >> numeroDecimal;
    std::cout << "Numero decimal leido: " << numeroDecimal << std::endl;
    
    return 0;
}
