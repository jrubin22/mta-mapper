cmake_minimum_required(VERSION 3.10)

# Add the executable
add_executable(mta-mapper 
    main.cpp 
    apilink.cpp
    subwayApiLink.cpp 
    profile.cpp 
    Display.cpp
    Stop.cpp
    gtfs-realtime-NYCT.pb.cc
    gtfs-realtime.pb.cc
)

find_package(CURL REQUIRED)
find_package(Protobuf REQUIRED)
find_package(yaml-cpp REQUIRED)

message(STATUS "Protobuf libraries: ${Protobuf_LIBRARIES}")


# Include the headers directory
target_include_directories(mta-mapper PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${Protobuf_INCLUDE_DIRS}
    ${yaml-cpp_INCLUDE_DIRS}
    
)
target_link_libraries(mta-mapper 
    CURL::libcurl  
    protobuf::libprotobuf
    yaml-cpp
)


# target_link_libraries(your_target_name ${Protobuf_LIBRARIES})
# target_include_directories(your_target_name PRIVATE ${Protobuf_INCLUDE_DIRS})

