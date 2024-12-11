CXX = g++						         # The C++ compiler command
CXXFLAGS = -std=c++14	 # The C++ compiler options (C++14, and warn all)

TARGET = p11_emst # Ejecutable

SRCS = emst_main.cpp point_types.cpp sub_tree.cpp bosque.cpp # Archivos fuente

all: clean $(TARGET) # Regla por defecto

$(TARGET): $(SRCS) # Regla para compilar el ejecutable
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)