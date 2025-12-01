#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h> // To use usleep

int main() {
    std::string spinner [] = {"|", "/", "-", "\\"};

    // Loops twenty times
    for (int i = 0; i < 20; i++) {
        std::cout << "\rLoading " << spinner[i % 4];
        std::cout.flush(); // Forces output

    // Pauses for miliseconds (200), like using async 
        usleep(200000);
    }

    std::cout << "\rDone!  " << std::endl;
    return 0;
}
