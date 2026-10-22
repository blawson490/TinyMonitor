#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <format>
#include <unistd.h>
#include "version.h"
using namespace std;

enum class StorageUnit { MiB, GiB };

struct MemoryInfo {
    unsigned long long total = 0;
    unsigned long long used = 0;
    unsigned long long available = 0;

    bool total_mem_valid = false;
    bool available_mem_valid = false;
    bool used_mem_valid = false;
};

double convertTo(unsigned long long size, StorageUnit targetUnit) {
    switch (targetUnit) {
        case StorageUnit::MiB:
            return size / 1024.0;
        case StorageUnit::GiB:
            return size / (1024.0 * 1024.0);
    }
    return 0.0;
}

// Passing istream as reference so we don't need to create copy of stream (Optimizations) and can build tests
int uptime_in_hours(istream& stream) {
    if (!stream) {
        cerr << "Unable to read stream. \n";
        return -1;
    }

    double uptimeSeconds = 0.0;
    int uptime_hours = 0;
    
    if (stream >> uptimeSeconds) {
        int uptimeMinutes = uptimeSeconds / 60;
        uptime_hours = uptimeMinutes / 60;
    } else {
        
        return -1;
    }
    
    return uptime_hours;
}

// Passing istream as reference so we don't need to create copy of stream (Optimizations) and can build tests
MemoryInfo get_mem_info_from_stream(istream& stream ) {
    MemoryInfo memory;

    if (!stream) {
        cerr << "Unable to read stream. \n";
        return memory;
    }
    
    
    string line;
    bool found = false;

    while (!found && (getline(stream, line))) {
        istringstream line_stream(line);
        string key;

        if (getline(line_stream, key, ':')) {
            if (key == "MemTotal") {
                if (line_stream >> memory.total) {
                    memory.total_mem_valid = true;
                }
            } else if (key == "MemAvailable") {
                if (line_stream >> memory.available) {
                    memory.available_mem_valid = true;
                }
            }
        }

        if (memory.total_mem_valid && memory.available_mem_valid) {
            found = true;
            if (memory.available <= memory.total) {
                memory.used_mem_valid = true;
                memory.used = memory.total - memory.available;
            }
        }
    }
    return memory;
}



string get_hostname() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        return "Unable to resolve host name";
    }
    hostname[sizeof(hostname) - 1] = '\0';
    return string(hostname);
}

string get_uptime() {
    ifstream file("/proc/uptime");
    int uptime_hours = uptime_in_hours(file);
    
    string uptime_hours_string = (uptime_hours != -1) ? to_string(uptime_hours) + "h": "Unavailable";

    return uptime_hours_string;
}

string get_memory() {
    ifstream file("/proc/meminfo");
    if (!file.is_open()) {
        cerr << "Unable to open file \n";
    }

    MemoryInfo memory = get_mem_info_from_stream(file);
    
    double used = convertTo(memory.used, StorageUnit::GiB);
    double total = convertTo(memory.total, StorageUnit::GiB);
    double available = convertTo(memory.available, StorageUnit::GiB);


    string memoryString;

    if (memory.used_mem_valid && memory.total_mem_valid) {
        // if both are valid
        memoryString = format("{:.2f}", used) + " GiB / " + format("{:.2f}", total) + " GiB";
    } 
    else if (memory.total_mem_valid && !memory.used_mem_valid) {
        // if only total is valid
        memoryString = format("{:.2f}", total) + " GiB of total memory, Used memory unavailable.";
    }
    else {
        // neither are valid
        memoryString = "Unable to get memory usage.";
    }

    return memoryString;
}

void print_stats(string hostname, string uptime, string memory, string online) {
    cout << "Hostname: " << hostname << "\n";
    cout << "Online: " << online << "\n";
    cout << "Uptime: " << uptime << "\n";
    cout << "Memory: " << memory << endl;
}

int main() {
    string hostname = get_hostname();
    string uptime = get_uptime();
    string memory = get_memory();

    bool online = true;
    string online_string = online ? "true" : "false";

    cout << "TinyMonitor™ v"<< PRODUCT_VERSION << "\n";
    print_stats(hostname, uptime, memory, online_string);
    
    return 0;
}
