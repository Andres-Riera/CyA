CXX = g++						         # The C++ compiler command
CXXFLAGS = -std=c++14	 # The C++ compiler options (C++14, and warn all)

TARGET = p02_strings # Ejecutable

SRCS = p02_strings_main.cc alfabeto.cc cadena.cc # Archivos fuente

all: $(TARGET) # Regla por defecto

clean:
	rm -f $(TARGET)

git:
	git add .
	git commit -m "Cambios"
	git push