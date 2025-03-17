#!/bin/bash


# Set the environment variable for the YAML config path
export MTA_MAPPER_CONFIG_PATH="/home/jrubin/git/mta-mapper/config/"

# Path to the binary
BUILD_BINARY_PATH="/home/jrubin/git/mta-mapper/build/src/mta-mapper"

# Run the compiled binary
$BUILD_BINARY_PATH
