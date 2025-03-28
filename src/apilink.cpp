#include "apilink.h"
#include <iostream>
#include <stdexcept>

// Constructor: Initialize Feed URL, and set up CURL
ApiLink::ApiLink( const std::string& feed_url): 
    feedUrl(feed_url), 
    curlHandle(curl_easy_init()) 
{

    if (!curlHandle) {
        throw std::runtime_error("Failed to initialize CURL");
    }
    setupCurl();
}

// Destructor: Cleanup CURL
ApiLink::~ApiLink() 
{
    if (curlHandle) 
    {
        curl_easy_cleanup(curlHandle);
    }
}

// CURL write callback function
size_t ApiLink::writeCallback(void* contents, size_t size, size_t nmemb, void* userp) 
{
    size_t totalSize = size * nmemb;
    static_cast<std::string*>(userp)->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

void ApiLink::setupCurl() 
{
    // Set common CURL options
    curl_easy_setopt(curlHandle, CURLOPT_FOLLOWLOCATION, 1L);  // Follow redirects if necessary
    curl_easy_setopt(curlHandle, CURLOPT_USERAGENT, "MTA Subway Feed Client/1.0");  // Set a user agent
}


// Fetch train data from the MTA API
std::string ApiLink::fetchTrainData(Profile& profile) 
{
    // Fetch data from the API and parse it
    std::string data = makeRequest();
    parseResponse(data, profile);  // Call the parsing function after data is fetched
    return data;
}

std::string ApiLink::makeRequest() 
{
    CURL* curl;
    CURLcode res;
    std::string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, feedUrl.c_str());

        // Function to capture the response body
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, 
                         +[](void* ptr, size_t size, size_t nmemb, std::string* data) -> size_t 
                         {
                             data->append(static_cast<char*>(ptr), size * nmemb);
                             return size * nmemb;
                         });

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
            throw std::runtime_error("Failed to fetch data from API");
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    
    return response;
}
