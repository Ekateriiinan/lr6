#include "observer.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>

void ConsoleObserver::onKill(const std::string& killer, const std::string& victim, 
                            const std::string& killerType, const std::string& victimType) {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    std::cout << std::put_time(std::localtime(&time), "[%Y-%m-%d %H:%M:%S] ");
    std::cout << killerType << " " << killer << " killed " << victimType << " " << victim << std::endl;
}

FileObserver::FileObserver(const std::string& filename) : filename(filename) {}

void FileObserver::onKill(const std::string& killer, const std::string& victim, 
                         const std::string& killerType, const std::string& victimType) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        
        file << std::put_time(std::localtime(&time), "[%Y-%m-%d %H:%M:%S] ");
        file << killerType << " " << killer << " killed " << victimType << " " << victim << std::endl;
        file.close();
    }
}