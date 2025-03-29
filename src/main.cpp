#include "subwayApiLink.h"
#include "profile.h"
#include "Display.h"
#include <cstdlib>
#include <iostream>
#include <csignal>
#include <cstring>
#include <chrono>
#include <thread>

// Global flag for clean shutdown
volatile std::sig_atomic_t keepRunning = 1;

// Signal handler for SIGINT (Ctrl+C) and SIGTERM
void signalHandler(int signal) 
{
    std::cout << "\n[INFO] Caught signal " << signal << ", exiting...\n";
    keepRunning = 0;
}

int main() 
{
    // Register signal handlers
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);


    const char* env_path = std::getenv("MTA_MAPPER_CONFIG_PATH");
    char configPath[256];
    strcpy(configPath,env_path);
    strcat(configPath, "config.yaml" );
    if (!env_path)
    {
        std::cerr << "Error: MTA_MAPPER_CONFIG_PATH is not set!" << std::endl;
        return 1;
    }
    
    std::string config_path(configPath);
    Profile profile(config_path);
    Display display;
    std::map<std::string, std::shared_ptr<Stop>> stops;


    // Iterate over the loaded subway configurations
    for (const auto& config : profile.getConfigs()) 
    {
        std::cout << "Monitoring Train Line: " << config.train_line << std::endl;
        std::cout << "Station ID: " << config.station_id << std::endl;
        std::cout << "Directions: ";
        for (const auto& dir : config.directions) 
        {
            std::cout << dir << " ";
        }
        std::cout << std::endl << std::endl;
        //Create Stops for each station in the profile
        stops[config.station_id] = std::make_shared<Stop>(config.station_id, config.train_line, config.directions);

    }
 
    // Replace with your actual API key and MTA feed URL
    std::string feedUrl = "https://api-endpoint.mta.info/Dataservice/mtagtfsfeeds/nyct%2Fgtfs";

    try 
    {
        // Initialize API connection
        SubwayApiLink subwayApi(feedUrl, stops);

        std::cout << "[INFO] Starting MTA Subway Tracker...\n";

        // Run loop (fetches data every 10 seconds)
        while (keepRunning) 
        {
            std::cout << "[INFO] Fetching train data...\n";

            // Get train data from MTA API
            std::string trainData = subwayApi.fetchTrainData(profile);

            // Proof of concept print from stops
            for (const auto& stop : stops)
            {
                display.update(stop.second);
                //stop.second->printInfo();
                std::this_thread::sleep_for(std::chrono::seconds(4));

            } 

            // Wait 10 seconds before next update
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }

    } 
    catch (const std::exception& e) 
    {
        std::cerr << "[ERROR] Exception: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    std::cout << "[INFO] Exiting cleanly...\n";
    return EXIT_SUCCESS;
}
