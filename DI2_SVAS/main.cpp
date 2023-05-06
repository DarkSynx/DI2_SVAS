#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#include <shellapi.h>
#endif

void launch_dead_island() {
    #ifdef _WIN32
    // Lancement de DeadIsland.exe
    ShellExecute(NULL, "open", "DeadIsland.exe", NULL, NULL, SW_SHOWNORMAL);
    #endif
}

int read_time_from_ini(const std::string& ini_file) {
    std::ifstream file(ini_file);
    std::string line;
    int time_value = 60;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.find("time = ") != std::string::npos) {
                time_value = std::stoi(line.substr(line.find("time = ") + 7));
                break;
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open INI file: " << ini_file << std::endl;
    }

    return time_value;
}

int main() {
    std::string ini_file = "DI2_SVAS.ini";
    int time_value = read_time_from_ini(ini_file);

    std::cout << "- desactivation du service audio" << std::endl;
    system("SC stop Audiosrv");

    std::cout << "- Lancement de DeadIsland.exe..." << std::endl;
    std::thread dead_island_thread(launch_dead_island);

    std::cout << "- activation du service audio dans " << time_value << "s" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(time_value));

    std::cout << "- activation du service audio" << std::endl;
    system("SC start Audiosrv");

    dead_island_thread.join();

    return 0;
}