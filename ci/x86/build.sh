#!/bin/bash

# Variables
BUILD_DIR="build"
RUN_SCRIPT="ci/x86/run.sh"
CMAKE_CMD="cmake"
MAKE_CMD="make"

# Store the current directory
ORIGINAL_DIR=$(pwd)

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# Ensure the ci/x86 directory exists for the run.sh
mkdir -p "ci/x86"

# Navigate to the build directory using pushd
pushd "$BUILD_DIR" > /dev/null

# Run cmake to configure the project
$CMAKE_CMD ..

# Build the project
$MAKE_CMD

# Check if the build was successful
if [ $? -eq 0 ]; then
    popd
else
    echo "[ERROR] Build failed!"
    popd
    exit 1
fi

echo "[INFO] Build completed."
