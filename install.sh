#!/bin/bash

# Salir si ocurre un error
set -e

# Compilar el código
echo "Compilando el código..."
make

# Verificar si el binario existe
if [ ! -f "cpu_temp" ]; then
    echo "Error: No se encontró el archivo compilado 'cpu_temp'."
    exit 1
fi

# Mover el binario a /usr/local/bin
echo "Moviendo el archivo compilado a /usr/local/bin..."
sudo mv cpu_temp /usr/local/bin/

# Asegurar permisos de ejecución
echo "Asegurando permisos de ejecución..."
sudo chmod +x /usr/local/bin/cpu_temp

# Crear un servicio de systemd para ejecutarlo al inicio (opcional)
echo "Creando un servicio de systemd para ejecutar al inicio..."
SERVICE_FILE=/etc/systemd/system/cpu_temp.service
sudo bash -c "cat > $SERVICE_FILE" <<EOL
[Unit]
Description=CPU Temp Monitor
After=network.target

[Service]
ExecStart=/usr/local/bin/cpu_temp
Restart=always

[Install]
WantedBy=multi-user.target
EOL

# Recargar systemd y habilitar el servicio
echo "Habilitando el servicio..."
sudo systemctl daemon-reload
sudo systemctl enable cpu_temp

echo "Instalación completada. El programa se ejecutará al inicio."