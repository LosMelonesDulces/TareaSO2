#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include <cmath>

std::atomic<bool> running(true);

void stress_function() {
    // Variables that won't be optimized away
    volatile double result = 1.0;
    
    // Perform heavy calculations in a loop
    while (running) {
        for (int i = 0; i < 10000; i++) {
            result = std::sin(result) + std::cos(result * 1.1) + std::sqrt(result + 1.2);
            result = std::pow(result, 1.01);
            
            // Prevent result from growing too large
            if (result > 10000.0)
                result = 1.0;
        }
    }
}

int main(int argc, char* argv[]) {
    int seconds = 60;  // Default runtime of 60 seconds
    
    // Parse command line arguments
    if (argc > 1) {
        seconds = std::atoi(argv[1]);
    }
    
    // Get number of cores
    unsigned int num_cores = std::thread::hardware_concurrency();
    std::cout << "Detected " << num_cores << " CPU cores" << std::endl;
    std::cout << "Running CPU stress test for " << seconds << " seconds..." << std::endl;
    
    // Create threads (one per core)
    std::vector<std::thread> threads;
    for (unsigned int i = 0; i < num_cores; ++i) {
        threads.push_back(std::thread(stress_function));
    }
    
    // Run for specified duration
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    
    // Stop threads
    running = false;
    
    // Join threads
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "CPU stress test completed" << std::endl;
    return 0;
}