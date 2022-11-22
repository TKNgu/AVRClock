
#Cmake version.
cmake_minimum_required(VERSION 3.10.2)

# C++ std 14.
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_CXX_FLAGS "-O3 -mmcu=atmega328p -DF_CPU=16000000")

# Monitor Service.
project(Clock LANGUAGES CXX)

# Source code
file(GLOB SRC src/*.cpp)

# Build
add_executable(${CMAKE_PROJECT_NAME}.bin ${SRC})

# Run
add_custom_target(run
	avr-objcopy -j .text -j .data -O ihex ${CMAKE_PROJECT_NAME}.bin ${CMAKE_PROJECT_NAME}.hex
	DEPENDS ${CMAKE_PROJECT_NAME}.bin)
