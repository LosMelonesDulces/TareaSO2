#ifndef DAEMON_HPP
#define DAEMON_HPP

#include <string>
#include <functional>

class Daemon {
public:
    Daemon(int intervalSeconds, int topTemp, const std::function<void(const std::string&)>& notifyCallback);
    void start();
    void stop();

private:
    int intervalSeconds; // Intervalo en segundos para medir la temperatura
    int topTemp;         // Umbral de temperatura máxima
    bool running;        // Estado del daemon
    std::function<void(const std::string&)> notifyCallback; // Callback para enviar notificaciones

    void monitorTemperature();
    int getCpuTemperature(); // Método para obtener la temperatura del CPU
};

#endif // DAEMON_HPP