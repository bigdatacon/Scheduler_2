#!/bin/bash

# Check for necessary files
if [ ! -f "my_module/module.cpp" ]; then
    echo "File my_module/module.cpp not found."
    exit 1
fi

if [ ! -f "my_module/DataContainer.h" ]; then
    echo "File my_module/DataContainer.h not found."
    exit 1
fi

if [ ! -f "my_module/utils.h" ]; then
    echo "File my_module/utils.h not found."
    exit 1
fi

if [ ! -f "my_module/InputData.h" ]; then
    echo "File my_module/InputData.h not found."
    exit 1
fi

# Paths to pybind11 and Python
PYBIND11_INCLUDE="-I./extern/pybind11/include"
PYTHON_INCLUDE=$(python3-config --includes)
PYTHON_LIB=$(python3-config --ldflags)

# Path to nlohmann json library
NLOHMANN_JSON_INCLUDE="-I./json/include"  # Adjusted path

# Detect platform
UNAME_S=$(uname -s)

# Additional linker flags for macOS
if [ "$UNAME_S" = "Darwin" ]; then
    ARCH_FLAGS="-arch arm64"  # or "-arch x86_64" if you're using an Intel Mac
else
    ARCH_FLAGS=""
fi

# Use g++ as the compiler
COMPILER=g++

# Compile my_module as a shared library with InputData.cpp
$COMPILER -O3 -Wall -shared -std=c++17 -fPIC $PYBIND11_INCLUDE $PYTHON_INCLUDE $NLOHMANN_JSON_INCLUDE \
    my_module/module.cpp my_module/InputData.cpp -o my_module$(python3-config --extension-suffix) $PYTHON_LIB $ARCH_FLAGS -v

# Compile main.cpp to executable
$COMPILER -O3 -Wall -std=c++17 $NLOHMANN_JSON_INCLUDE main.cpp -o main -v

echo "Build completed."
