#include <sstream>
#include <string>
#include "memory.h"


std::string test_file = "MemTotal:       8192000  kB\nMemAvailable:   3072000 kB";

int main(int argc, char* argv[]) {
    if (argc <= 1) return 1; // fail if no test case specified

    std::string test_case = argv[1];

    if (test_case == "1") {
        // Test reading from file function
        std::istringstream iss(test_file);
        MemoryInfo memory = get_mem_info_from_stream(iss);
        auto total = memory.total;
        auto available = memory.available;
        if (total == 8192000 && available == 3072000) {
            return 0;
        } else {
            std::cerr << "Total and available do not match test case" << std::endl;
            return 1;
        }
        return 1;
    }

    return 1;
}