#include <iostream>

int main() {
    std::string hostname = "LawsonServer";
    bool online = true;
    int uptime = 24;

    std::cout << "TinyMonitor v0.1™ \n";
    std::cout << "Hostname: " << hostname << "\n";
    std::cout << "Online: " << (online ? "true" : "false") << "\n";
    std::cout << "Uptime: " << uptime << "h\n";
    return 0;
}
