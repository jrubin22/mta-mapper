#ifndef SUBWAYAPILINK_H
#define SUBWAYAPILINK_H

#include "apilink.h"
#include "Stop.h"
#include "gtfs-realtime-NYCT.pb.h"
#include <map>
#include <memory>



class SubwayApiLink : public ApiLink 
{
    public:
        SubwayApiLink(const std::string& url, std::map<std::string, std::shared_ptr<Stop>>& stops);
    
        // Implement the parseResponse function
        void parseResponse(const std::string& data, Profile& profile) override;
    
    private:
        std::map<std::string, std::shared_ptr<Stop>>& stops;
    };
    
    #endif // SUBWAYAPILINK_H