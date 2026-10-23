#include <iostream>

struct MemoryInfo {
    unsigned long long total = 0;
    unsigned long long used = 0;
    unsigned long long available = 0;

    bool total_mem_valid = false;
    bool available_mem_valid = false;
    bool used_mem_valid = false;
};

MemoryInfo get_mem_info_from_stream(std::istream& stream);

std::string get_memory_as_string();