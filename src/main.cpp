#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

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

int main() {
    std::string hostname = get_hostname();
    bool online = true;
    int uptimeHours = uptime_in_hours();

    std::string onlineString = online ? "true" : "false";
    std::string upTimeHoursString = (uptimeHours != -1) ? std::to_string(uptimeHours) : "Unavailable";

    std::cout << "TinyMonitor v0.1™ \n";
    std::cout << "Hostname: " << hostname << "\n";
    std::cout << "Online: " << onlineString << "\n";
    std::cout << "Uptime: " << upTimeHoursString << "h\n";
    return 0;
}
