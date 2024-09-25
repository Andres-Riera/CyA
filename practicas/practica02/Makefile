CXX = g++						         # The C++ compiler command
CXXFLAGS = -std=c++14	 # The C++ compiler options (C++14, and warn all)

TARGET = p02_strings # Ejecutable

SRCS = p02_strings_main.cc alfabeto.cc cadena.cc # Archivos fuente

all: $(TARGET) # Regla por defecto

$(TARGET): $(OBJS) # Regla para compilar el ejecutable
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)