#include "daemon.hpp"
#include <iostream>
#include <csignal>
#include <atomic>
#include <thread>
#include <chrono>

// Global flag for program termination
std::atomic<bool> running(true);

// Signal handler
void signalHandler(int signal) {
    std::cout << "Received signal " << signal << ", shutting down..." << std::endl;
    running = false;
}

// Notification callback function
void notificationHandler(const std::string& message) {
    std::cout << message << std::endl;
    
    // You could extend this to send desktop notifications, emails, etc.
    // For example, on Linux you could use:
    // system(("notify-send 'CPU Temperature Alert' '" + message + "'").c_str());
}

int main(int argc, char* argv[]) {
    // Set up signal handling
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);
    
    // Default settings
    int checkInterval = 5;  // Check every 5 seconds
    int tempThreshold = 60; // Alert if temperature exceeds this threshold (in °C)
    
    // Parse command-line arguments if provided
    if (argc > 1) checkInterval = std::stoi(argv[1]);
    if (argc > 2) tempThreshold = std::stoi(argv[2]);
    
    std::cout << "CPU Temperature Monitor" << std::endl;
    std::cout << "Check interval: " << checkInterval << " seconds" << std::endl;
    std::cout << "Temperature threshold: " << tempThreshold << "°C" << std::endl;
    std::cout << "Press Ctrl+C to exit" << std::endl;
    
    // Create and start the daemon
    Daemon tempMonitor(checkInterval, tempThreshold, notificationHandler);
    tempMonitor.start();
    
    // Keep the program running until terminated
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    // Stop the daemon
    tempMonitor.stop();
    std::cout << "Temperature monitor stopped" << std::endl;
    
    return 0;
}