#ifndef STOP_H
#define STOP_H

#include <string>
#include <vector>
#include <mutex>
#include <map>
#include "stopRegistry.h"
#define MAXSTOPS 4


class Stop {
public:
    Stop(const std::string& stationId, const std::string& trainLine, const std::vector<char>& directions);

    void updateArrivalTime(char direction, int minutesFromNow);
    void printInfo() const;

    std::string getStationId() const;
    std::string getStationName();
    std::string getTrainLine() const;
    std::map<char, std::vector<int>> getArrivalTimes();

private:
    std::string stationId;
    std::string trainLine;
    std::vector<char> directions;
    mutable std::mutex mutex;  // Protect concurrent updates

    // Store arrival times per direction (e.g., {'N': [5, 10, 15], 'S': [3, 8, 12]})
    std::map<char, std::vector<int>> arrivalTimes;
    StopRegistry Reg;

    void trimArrivals(char direction);

};

#endif // STOP_H
