#include "Display.h"
#include <iostream>

void Display::update(std::shared_ptr<Stop> stop) 
{
    std::cout << "======================" << std::endl;
    std::cout << "Station: " << stop->getStationName() << std::endl;
    std::cout << "Train Line: " << stop->getTrainLine() << std::endl;
    std::cout << "Train Arrivals:" << std::endl;

    for (const auto& [direction, times] : stop->getArrivalTimes()) 
    {
        std::cout << "  Direction " << direction << ":";

        if (times.empty()) 
        {
            std::cout << " No upcoming trains" << std::endl;
        } 
        else 
        {
            for (int time : times) 
            {
                std::cout << " " << time << " min";
            }
            std::cout << std::endl;
        }
    }

    std::cout << "======================" << std::endl;
}
