#ifndef PROFILE_H
#define PROFILE_H

#include <iostream>
#include <vector>
#include <string>
#include <yaml-cpp/yaml.h>

// Structure to hold subway monitoring configuration
struct SubwayConfig {
    std::string train_line;
    std::string station_id;
    std::vector<char> directions;
};

// Profile class to manage multiple subway monitoring configurations
class Profile {
public:
    // Constructor
    Profile(const std::string& filename);

    // Load configuration from a YAML file
    void loadConfig(const std::string& filename);

    // Get configurations
    const std::vector<SubwayConfig>& getConfigs() const;

private:
    std::vector<SubwayConfig> configs;
};

#endif // PROFILE_H
