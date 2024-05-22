#!/bin/bash

# Check for necessary files
if [ ! -f "module.cpp" ]; then
    echo "File module.cpp not found."
    exit 1
fi

if [ ! -f "InputData.h" ]; then
    echo "File InputData.h not found."
    exit 1
fi

# Paths to pybind11 and Python
PYBIND11_INCLUDE="-I./extern/pybind11/include"
PYTHON_INCLUDE=$(python3-config --includes)
PYTHON_LIB=$(python3-config --ldflags)

# Path to nlohmann json library
#NLOHMANN_JSON_INCLUDE="-I./json"  # Путь к папке json в корне проекта
NLOHMANN_JSON_INCLUDE="-Ijson/include"  # Путь к папке json в корне проекта

# Detect platform
UNAME_S=$(uname -s)

# Additional linker flags for macOS
if [ "$UNAME_S" = "Darwin" ]; then
    ARCH_FLAGS="-arch arm64"  # or "-arch x86_64" if you're using an Intel Mac
else
    ARCH_FLAGS=""
fi

# Use clang as the compiler
COMPILER=clang++

# Compile my_module as a shared library with InputData.cpp
$COMPILER -O3 -Wall -shared -std=c++17 -fPIC $PYBIND11_INCLUDE $PYTHON_INCLUDE $NLOHMANN_JSON_INCLUDE \
    module.cpp InputData.cpp Solver.cpp OutputData.cpp -o my_module$(python3-config --extension-suffix) $PYTHON_LIB $ARCH_FLAGS -v -undefined dynamic_lookup

# Compile main.cpp to executable
#$COMPILER -O3 -Wall -std=c++17 $NLOHMANN_JSON_INCLUDE main.cpp -o main -v

echo "Build completed."