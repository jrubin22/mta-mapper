cmake_minimum_required(VERSION 3.10)
project(mta-mapper)

if(CMAKE_CROSSCOMPILING)
    message(STATUS "Cross-compiling enabled")
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_SYSTEM_PROCESSOR arm)
    set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
    set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
endif()


# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the build binary directory
set(BUILD_BINARY_DIR "${CMAKE_BINARY_DIR}/src")

# Add your source directories here
add_subdirectory(src)

# Install dependencies
include_directories(include)

# Optionally, add other targets or build settings here

# Generate the run.sh file in ci/x86
configure_file(
    ${CMAKE_SOURCE_DIR}/ci/x86/run.sh.in
    ${CMAKE_BINARY_DIR}/ci/x86/run.sh
    @ONLY
)

# Make sure the run.sh is executable after generation
file(COPY ${CMAKE_BINARY_DIR}/ci/x86/run.sh
    DESTINATION ${CMAKE_SOURCE_DIR}/ci/x86
    FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
