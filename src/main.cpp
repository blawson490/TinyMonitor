#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>

std::string get_hostname() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        return hostname;
    };

    return "Error: Unable to retrieve hostname.";
}

int uptime_in_hours() {
    std::ifstream uptimeFile("/proc/uptime");

    if (!uptimeFile.is_open()) {
        std::cerr << "Error: Could not open /proc/uptime" << std::endl;
        return -1;
    };

    double uptimeSeconds = 0.0;
    int uptimeHours = 0;
    
    if (uptimeFile >> uptimeSeconds) {
        int uptimeMinutes = uptimeSeconds / 60;
        uptimeHours = uptimeMinutes / 60;
    } else {
        std::cerr << "Error: Failed to parse /proc/uptime" << std::endl;
        return -1;
    };

    return uptimeHours;
}

int main() {
    bool online = true;
    int uptime = 24;

    std::cout << "TinyMonitor v0.1™ \n";
    std::cout << "Hostname: " << get_hostname() << "\n";
    std::cout << "Online: " << (online ? "true" : "false") << "\n";
    std::cout << "Uptime: " << uptime_in_hours() << "h\n";
    return 0;
}
