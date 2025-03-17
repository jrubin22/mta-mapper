#include "Stop.h"
#include <iostream>
#include <algorithm>

Stop::Stop(const std::string& stationId, const std::string& trainLine, const std::vector<char>& directions):
     stationId(stationId),
     trainLine(trainLine), 
     directions(directions),
     Reg() 
    {
        for (char dir : directions)
        {
            arrivalTimes[dir] = {}; // Initialize empty vector for each direction
        }
    }

void Stop::updateArrivalTime(char direction, int minutesFromNow) 
{
    std::lock_guard<std::mutex> lock(mutex);
    
    if (std::find(directions.begin(), directions.end(), direction) != directions.end()) 
    {
        arrivalTimes[direction].push_back(minutesFromNow);
        // Keep arrival times sorted and limit storage to avoid growing indefinitely
        std::sort(arrivalTimes[direction].begin(), arrivalTimes[direction].end());
        if (arrivalTimes[direction].size() > MAXSTOPS) 
        {
            arrivalTimes[direction].resize(MAXSTOPS);
        }
    }
}

void Stop::trimArrivals(char direction) 
{
    auto& arrivals = arrivalTimes[direction];

    // Sort and keep only the most recent MAXSTOPS
    std::sort(arrivals.begin(), arrivals.end());
    if (arrivals.size() > MAXSTOPS) {
        arrivals.erase(arrivals.begin(), arrivals.end() - MAXSTOPS);
    }
}

void Stop::printInfo() const 
{
    std::cout << "Station: " << stationId << " | Train: " << trainLine << std::endl;
    for (const auto& [dir, times] : arrivalTimes) 
    {
        std::cout << "  Direction " << dir << ": ";
        for (int time : times) 
        {
            std::cout << time << " min, ";
        }
        std::cout << std::endl;
    }
}

std::string Stop::getStationId() const 
{
    return stationId;
}

std::string Stop::getStationName()
{
    return Reg.getStopName(stationId);
}

std::string Stop::getTrainLine() const 
{
    return trainLine;
}

std::map<char, std::vector<int>> Stop::getArrivalTimes()
{
    return arrivalTimes;
}
