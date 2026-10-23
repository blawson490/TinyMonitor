#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include "version.h"
#include "memory.h"
#include "utils.h"
#include <format>
using namespace std;


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

void print_stats(string hostname, string uptime, string memory, string online) {
    cout << "Hostname: " << hostname << "\n";
    cout << "Online: " << online << "\n";
    cout << "Uptime: " << uptime << "\n";
    cout << "Memory: " << memory << endl;
}

// Function to set the console text color using ANSI escape
// codes
void SetColor(int textColor)
{
    cout << "\033[" << textColor << "m";
}

void ResetText() { cout << "\033[0m"; }

void SetBold() { cout << "\033[1m";}

void DrawVerticalBorder() {
    cout << "│";
}

void DrawBottomBorder() {
    cout << "╰─────────────────────────────╯";
}

void DrawEmpty() {
    cout << "░";
}

void DrawFilled() {
    cout << "█";
}

void DrawProgress(int percentage, int length) {
    int total = 100;
    int progress = percentage;
    int totalLength = progress < 100 ? length : length - 1;
    int filledLength = (progress * totalLength) / 100;
    int emptyLength = totalLength - filledLength;
    SetColor(32);
    for (int i = 0; i <= filledLength; i++) {
        DrawFilled();
    }
    ResetText();
    for (int i = 0; i <= emptyLength; i++) {
        DrawEmpty();
    }

    cout << " " << percentage << "%";
}

void print(){
    SetColor(36);
    SetBold();
    cout << "╭──── " << "TinyMonitor™ v"<< PRODUCT_VERSION << " ────╮" << endl;
    ResetText();
    SetColor(36);
    // DrawVerticalBorder();
    // cout << format("{:<28} {}", "", "");
    // DrawVerticalBorder();
    // cout << endl;
    DrawVerticalBorder();
    ResetText();
    cout << format("{:<17} {}", "Hostname:", "LawsonSever");
    SetColor(36);
    DrawVerticalBorder();
    cout << endl;
    SetColor(36);
    DrawVerticalBorder();
    ResetText();
    cout << format("{:<20} {}", "Status:", "● Online");
    SetColor(36);
    DrawVerticalBorder();
    cout << endl;
    DrawVerticalBorder();
    ResetText();
    cout << format("{:<24} {}", "Uptime:", "127h");
    SetColor(36);
    DrawVerticalBorder();
    cout << endl;
    DrawVerticalBorder();
    ResetText();
    cout << format("{:<11} {}", "Memory:","14.64 / 62.48 GiB");
    SetColor(36);
    DrawVerticalBorder();
    cout << endl;
    DrawVerticalBorder();
    ResetText();
    DrawProgress(23, 23);
    SetColor(36);
    DrawVerticalBorder();
    cout << endl;
    DrawBottomBorder();
    cout << endl;
}

int main() {
    // string hostname = get_hostname();
    // string uptime = get_uptime();
    // string memory = get_memory_as_string();

    // bool online = true;
    // string online_string = online ? "true" : "false";

    // cout << "TinyMonitor™ v"<< PRODUCT_VERSION << "\n";
    // print_stats(hostname, uptime, memory, online_string);
    
    print();
    return 0;
}
