#include "daemon.hpp"
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>

Daemon::Daemon(int intervalSeconds, int topTemp, const std::function<void(const std::string&)>& notifyCallback)
    : intervalSeconds(intervalSeconds), topTemp(topTemp), running(false), notifyCallback(notifyCallback) {
}

void Daemon::start() {
    if (running) return;
    
    running = true;
    std::thread monitorThread(&Daemon::monitorTemperature, this);
    monitorThread.detach();
}

void Daemon::stop() {
    running = false;
}

void Daemon::monitorTemperature() {
    while (running) {
        int temp = getCpuTemperature();

        std::cout << "Current CPU temperature: " << temp << "°C" << std::endl; // Se cambia por logger
        
        if (temp > topTemp) {
            std::string message = "Warning: CPU temperature (" + std::to_string(temp) + "°C) exceeds threshold (" + std::to_string(topTemp) + "°C)";
            notifyCallback(message);
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(intervalSeconds));
    }
}

int Daemon::getCpuTemperature() {
    // On Linux systems, CPU temperature can be read from /sys/class/thermal/thermal_zone*/temp
    int maxTemp = 0;
    
    try {
        for (const auto& entry : std::filesystem::directory_iterator("/sys/class/thermal/")) {
            std::string path = entry.path().string();
            if (path.find("thermal_zone") != std::string::npos) {
                std::ifstream tempFile(path + "/temp");
                if (tempFile.is_open()) {
                    int temp;
                    tempFile >> temp;
                    // Temperature is usually in millidegrees Celsius
                    temp /= 1000;
                    maxTemp = std::max(maxTemp, temp);
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error reading CPU temperature: " << e.what() << std::endl;
    }
    
    return maxTemp;
}