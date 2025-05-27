# TareaSO2

## Descripción del Proyecto
Este proyecto es un monitor de temperatura del CPU que funciona como un daemon en sistemas Linux. El programa lee la temperatura del CPU desde los archivos del sistema (`/sys/class/thermal/thermal_zone*/temp`) y registra las temperaturas en un archivo de log. Además, genera alertas si la temperatura supera un umbral definido.

También incluye un programa de prueba (`cpu_stress`) que genera carga en el CPU para simular escenarios de alta temperatura.

## Requisitos
- Sistema operativo Linux.
- Compilador `g++`.
- Herramientas de desarrollo como `make`.

## Archivos Principales
- `daemon.cpp` y `daemon.hpp`: Implementación del daemon que monitorea la temperatura del CPU.
- `main.cpp`: Punto de entrada del programa.
- `dummy.cpp`: Programa para generar carga en el CPU.
- `Makefile`: Archivo para compilar y ejecutar el proyecto.
- `install.sh`: Script para instalar el programa y configurarlo para que se ejecute al inicio del sistema.

## Instrucciones de Uso

### Compilación
Para compilar el proyecto, utiliza el comando:
```
make
```
Esto generará el ejecutable principal `cpu_temp`.

### Instalación
Para instalar el programa y configurarlo para que se ejecute automáticamente al inicio del sistema, ejecuta:
```
sudo ./install.sh
```
Esto compilará el programa (si no está compilado), moverá el ejecutable a `/usr/local/bin` y configurará un servicio de `systemd` para que se ejecute al inicio.

### Ejecución
Puedes ejecutar el programa manualmente con:
```
make run
```
Esto ejecutará el archivo `cpu_temp` y comenzará a monitorear la temperatura del CPU.

### Programa de Prueba (CPU Stress)
El proyecto incluye un programa adicional (`cpu_stress`) para generar carga en el CPU. Esto es útil para probar el comportamiento del monitor de temperatura bajo condiciones de alta carga.

#### Compilar el programa de prueba
Para compilar el programa de prueba, utiliza:
```
make dummy
```

#### Ejecutar el programa de prueba
Para ejecutar el programa de prueba, utiliza:
```
make run-dummy
```
Esto ejecutará el programa `cpu_stress`, que generará carga en todos los núcleos del CPU durante un tiempo predeterminado (por defecto, 60 segundos).

### Limpieza
Para eliminar los archivos generados durante la compilación, utiliza:
```
make clean
```

## Notas
- El programa registra las temperaturas en un archivo llamado `daemon.log`.
- Puedes personalizar el intervalo de monitoreo y el umbral de temperatura al ejecutar el programa manualmente. Por ejemplo:
```
./cpu_temp 10 70
```
Esto configurará un intervalo de 10 segundos y un umbral de 70°C.

## Comandos Resumidos
- `make`: Compila el proyecto.
- `make run`: Ejecuta el monitor de temperatura (`cpu_temp`).
- `make dummy`: Compila el programa de prueba (`cpu_stress`).
- `make run-dummy`: Ejecuta el programa de prueba (`cpu_stress`).
- `make clean`: Limpia los archivos generados.
- `sudo ./install.sh`: Instala el programa y lo configura para ejecutarse al inicio.

¡Disfruta monitoreando la temperatura de tu CPU!