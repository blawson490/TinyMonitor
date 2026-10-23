#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <format>
#include "memory.h"
#include "utils.h"
using namespace std;

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

std::string get_memory_as_string() {
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