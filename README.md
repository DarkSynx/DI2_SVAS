# DI2_SVAS

BUG on DEAD ISLAND 2, audio service disabled and re-enabled;  this application does the work for you you can compile the project yourself with "Dev-C++ for Windows" https://sourceforge.net/projects/embarcadero-devcpp/ don't forget to create the "DI2_SVAS.ini" file containing line

BUG sur DEAD ISLAND 2, du service audio à désactivé et réactivé; cette application fait le travail pour vous
vous pouvez compiler le projet vous même avec "Dev-C++ for Windows" https://sourceforge.net/projects/embarcadero-devcpp/
n'oubliez pas de créé le fichier "DI2_SVAS.ini" contenant la ligne : 
```txt
time = 70
```
pour 70 second

Stop Audio Service Windows; Start Dead Islan 2.exe ; Wait 60s; Start Audio Service Windows; 
Dev-C++ 

![image](https://user-images.githubusercontent.com/9467611/236637781-afbfb05d-039c-42a5-a92e-9036cb1ca200.png)

```c++
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
```
