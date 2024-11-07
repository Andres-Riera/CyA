CXX = g++						         # The C++ compiler command
CXXFLAGS = -std=c++14	 # The C++ compiler options (C++14, and warn all)

TARGET = p08_grammar2CNF # Ejecutable

SRCS = p08_grammar2CNF_main.cc gramatica.cc # Archivos fuente

all: clean $(TARGET) # Regla por defecto

$(TARGET): $(SRCS) # Regla para compilar el ejecutable
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)