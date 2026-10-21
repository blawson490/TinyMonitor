#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include "version.h"

struct MemoryInfo {
    unsigned long long total_mib = 0;
    unsigned long long used_mib = 0;
    unsigned long long available_mib = 0;

    bool totalMemoryValid = false;
    bool availableMemoryValid = false;
    bool usedMemoryValid = false;
};

std::string get_hostname() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        return "Unable to resolve host name";
    }
    hostname[sizeof(hostname) - 1] = '\0';
    return std::string(hostname);
}

int uptime_in_hours() {
    std::ifstream uptimeFile("/proc/uptime");

    if (!uptimeFile.is_open()) {
        return -1;
    }

    double uptimeSeconds = 0.0;
    int uptimeHours = 0;
    
    if (uptimeFile >> uptimeSeconds) {
        int uptimeMinutes = uptimeSeconds / 60;
        uptimeHours = uptimeMinutes / 60;
    } else {

        return -1;
    }

    return uptimeHours;
}

MemoryInfo get_mem_info() {
    MemoryInfo memory;

    std::ifstream memoryFile("/proc/meminfo");
    if (!memoryFile.is_open()) {
        std::cerr << "Unable to open file '/proc/meminfo' \n";
        return memory;
    }
    
    unsigned long long memTotal = 0;
    unsigned long long memAvailable = 0;
    bool memTotalValid = false;
    bool memAvailableValid = false;
    
    std::string line;
    bool found = false;

    while (!found && (std::getline(memoryFile, line))) {
        std::istringstream lineStream(line);

        std::string key;

        if (std::getline(lineStream, key, ':')) {
            if (key == "MemTotal") {
                if (lineStream >> memTotal) {
                    memTotalValid = true;
                }
            } else if (key == "MemAvailable") {
                if (lineStream >> memAvailable) {
                    memAvailableValid = true;
                }
            }
        }

        if (memTotalValid && memAvailableValid) {
            found = true;
        }
    }

    if (memTotalValid) {
        memory.total_mib = memTotal / 1024;
        memory.totalMemoryValid = true;
    }
    if (memAvailableValid) {
        memory.available_mib = memAvailable / 1024;
        memory.availableMemoryValid = true;
        if (memTotalValid && memTotal >= memAvailable){
            memory.used_mib = (memTotal - memAvailable) / 1024;
            memory.usedMemoryValid = true;
        }
    }

    return memory;
}


int main() {
    std::string hostname = get_hostname();
    bool online = true;
    int uptimeHours = uptime_in_hours();
    MemoryInfo memory = get_mem_info();

    std::string onlineString = online ? "true" : "false";
    std::string upTimeHoursString = (uptimeHours != -1) ? std::to_string(uptimeHours) + "h": "Unavailable";

    std::string memoryString;

    if (memory.usedMemoryValid && memory.totalMemoryValid) {
        // if both are valid
        memoryString = std::to_string(memory.used_mib) + " MiB / " + std::to_string(memory.total_mib) + " MiB";
    } 
    else if (memory.totalMemoryValid && !memory.usedMemoryValid) {
        // if only total is valid
        memoryString = std::to_string(memory.total_mib) + " MiB of total memory, Used memory unavailable.";
    }
    else {
        // neither are valid
        memoryString = "Unable to get Used, Available, or Total memory usage.";
    }

    std::cout << "TinyMonitor™ v"<< PRODUCT_VERSION << "\n";
    std::cout << "Hostname: " << hostname << "\n";
    std::cout << "Online: " << onlineString << "\n";
    std::cout << "Uptime: " << upTimeHoursString << "\n";
    std::cout << "Memory: " << memoryString << std::endl;
    return 0;
}
