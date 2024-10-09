CXX = g++						         # The C++ compiler command
CXXFLAGS = -std=c++14	 # The C++ compiler options (C++14, and warn all)

TARGET = p04_code_analyzer # Ejecutable

SRCS = p04_code_analyzer_main.cc analisis.cc # Archivos fuente

all: $(TARGET) # Regla por defecto

$(TARGET): $(OBJS) # Regla para compilar el ejecutable
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)