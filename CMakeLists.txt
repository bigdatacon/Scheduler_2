cmake_minimum_required(VERSION 3.4)
project(Scheduler_1)
set(CMAKE_CXX_STANDARD 17)

# Find packages for Python and its development libraries
find_package(Python3 REQUIRED COMPONENTS Development)

# Add pybind11 as a subdirectory
add_subdirectory(extern/pybind11)

# Include directories for Python and pybind11 headers
include_directories(${Python3_INCLUDE_DIRS} extern/pybind11/include)

# Specify the source files for the my_module
set(MY_MODULE_SOURCES
        my_module/module.cpp
        my_module/InputData.cpp
)

# Specify the header files for the my_module
set(MY_MODULE_HEADERS
        my_module/DataContainer.h
        my_module/utils.h
        my_module/InputData.h
)

# Create the pybind11 module
pybind11_add_module(my_module ${MY_MODULE_SOURCES})

# Create the executable for the main program
add_executable(Scheduler_1 main.cpp ${MY_MODULE_HEADERS})

# Link the Python libraries to the my_module and Scheduler_1 targets
target_link_libraries(my_module PRIVATE ${Python3_LIBRARIES})
target_link_libraries(Scheduler_1 PRIVATE ${Python3_LIBRARIES})
