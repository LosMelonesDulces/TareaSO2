# Compilador y flags
CC = g++
CFLAGS = -Wall -Wextra -g

# Archivos fuente
SRCS = daemon.cpp main.cpp
# Archivos objeto (reemplaza .c por .o)
OBJS = $(SRCS:.c=.o)

# Ejecutable
TARGET = cpu_temp
DUMMY_TARGET = cpu_stress

# Regla por defecto
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regla para archivos .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(OBJS) $(TARGET) $(DUMMY_TARGET)

run: $(TARGET)
	./$(TARGET)

# Regla para compilar dummy.cpp
dummy: dummy.cpp
	$(CC) $(CFLAGS) -O0 -std=c++11 -pthread dummy.cpp -o $(DUMMY_TARGET)

run-dummy: dummy
	./$(DUMMY_TARGET)

.PHONY: all clean dummy run-dummy