#ifndef APILINK_H
#define APILINK_H

#include "profile.h"
#include <string>
#include <curl/curl.h>

class ApiLink {
public:
    ApiLink(const std::string& feed_url);
    ~ApiLink();

    // Fetch and return the raw JSON response from the MTA API
    std::string fetchTrainData(Profile& profile);

protected:
    // Handles the HTTP request and writes the response
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp);
    
    // Helper function to set up CURL options
    void setupCurl();

    // Parses JSON response virtual because this can be implemented for train or bus later
    virtual void parseResponse(const std::string& json_data, Profile& profile) = 0;

     // Function to perform the actual HTTP request
     std::string makeRequest();

private:
    std::string feedUrl;
    CURL* curlHandle;
};

#endif // APILINK_H
