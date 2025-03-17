#ifndef STOP_REGISTRY_H
#define STOP_REGISTRY_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

class StopRegistry {
public:
    // Constructor that initializes the stop registry by loading data from a file
    StopRegistry() {
        loadFromFile();
    }

    // Function to get stop name by stop id
    std::string getStopName(const std::string& stop_id) {
        auto it = stop_map.find(stop_id);
        if (it != stop_map.end()) {
            return it->second;
        }
        return "Unknown Stop";  // Return default message if not found
    }

private:
    // Map to store stop_id to stop_name mapping
    std::unordered_map<std::string, std::string> stop_map;

    // Function to load stop data from a file
    void loadFromFile() 
    {
        const char* env_path = std::getenv("MTA_MAPPER_CONFIG_PATH");
        char stopsPath[256];
        strcpy(stopsPath,env_path);
        strcat(stopsPath, "stops.txt" );
        if (!env_path)
        {
            std::cerr << "Error: MTA_MAPPER_CONFIG_PATH is not set!" << std::endl;
        }

        std::ifstream file(stopsPath);
        if (!file.is_open()) 
        {
            std::cerr << "Error: Could not open file " << stopsPath << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string stop_id, stop_name;
            
            // Read the stop_id and stop_name from each line
            if (std::getline(ss, stop_id, ',') && std::getline(ss, stop_name, ',')) {
                stop_map[stop_id] = stop_name;
            }
        }

        file.close();
    }
};

#endif // STOP_REGISTRY_H
