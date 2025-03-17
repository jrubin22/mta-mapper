#include "subwayApiLink.h"
#include "gtfs-realtime-NYCT.pb.h" 
#include <iostream>
#include <ctime>

SubwayApiLink::SubwayApiLink(const std::string& url, std::map<std::string, std::shared_ptr<Stop>>& stops): 
    ApiLink(url),
    stops(stops)
     {}


void SubwayApiLink::parseResponse(const std::string& response, Profile& profile) 
{
    transit_realtime::FeedMessage feed_message;

    if (!feed_message.ParseFromString(response)) 
    {
        std::cerr << "Failed to parse the response as Protobuf." << std::endl;
        return;
    }

    std::time_t currentTime = std::time(nullptr);

    for (const auto& entity : feed_message.entity()) 
    {
        if (entity.has_trip_update()) 
        {
            const transit_realtime::TripUpdate& trip_update = entity.trip_update();
            std::string trainLine = trip_update.trip().route_id();

            for (const auto& config : profile.getConfigs()) 
            {
                if (config.train_line == trainLine) 
                {
                    for (const auto& stop_time : trip_update.stop_time_update()) 
                    {
                        std::string stopId = stop_time.stop_id();
                        char direction = stopId.back();

                        if (stopId.find(config.station_id) == 0) 
                        {
                            for (char dir : config.directions) 
                            {
                                if (direction == dir && stop_time.has_arrival()) 
                                {
                                    std::time_t arrivalTime = stop_time.arrival().time();
                                    int minutesFromNow = (arrivalTime - currentTime) / 60;

                                    if (stops.count(config.station_id)) 
                                    {
                                        stops[config.station_id]->updateArrivalTime(direction, minutesFromNow);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}