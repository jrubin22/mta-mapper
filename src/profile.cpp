#include "profile.h"

Profile::Profile(const std::string& filename) 
{
    loadConfig(filename);
}

void Profile::loadConfig(const std::string& filename) 
{
    try 
    {
        YAML::Node config_yaml = YAML::LoadFile(filename);
        YAML::Node monitors = config_yaml["subway_monitors"];

        if (monitors && monitors.IsSequence()) 
        {
            for (const auto& monitor : monitors) 
            {
                SubwayConfig config;
                config.train_line = monitor["train_line"].as<std::string>();
                config.station_id = monitor["station_id"].as<std::string>();

                if (monitor["directions"]) 
                {
                    for (const auto& dir : monitor["directions"]) 
                    {
                        config.directions.push_back(dir.as<char>());
                    }
                }

                configs.push_back(config);
            }
        } else 
        {
            std::cerr << "Error: Missing or incorrect 'subway_monitors' section in YAML file." << std::endl;
        }
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Error loading YAML file: " << e.what() << std::endl;
    }
}

const std::vector<SubwayConfig>& Profile::getConfigs() const 
{
    return configs;
}
