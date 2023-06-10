
#Cmake version.
cmake_minimum_required(VERSION 3.10.2)

# C++ std 14.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_CXX_FLAGS "-O3 -mmcu=atmega328p -DF_CPU=16000000")

# Monitor Service.
project(Clock LANGUAGES CXX)

# Include
include_directories(
	~/.arduino15/packages/arduino/hardware/avr/1.8.6/variants/standard/
	~/.arduino15/packages/arduino/hardware/avr/1.8.6/cores/arduino/
	~/.arduino15/packages/arduino/hardware/avr/1.8.6/libraries/Wire/src/)

# Source code
file(GLOB SRC src/*.cpp
	/home/ngocpt/.arduino15/packages/arduino/hardware/avr/1.8.6/cores/arduino/wiring.c)

# Build
add_executable(${CMAKE_PROJECT_NAME}.bin ${SRC})

# Run
add_custom_target(run
	avr-objcopy -j .text -j .data -O ihex ${CMAKE_PROJECT_NAME}.bin ${CMAKE_PROJECT_NAME}.hex
	DEPENDS ${CMAKE_PROJECT_NAME}.bin)

# Upload
add_custom_target(upload
	avrdude "-C${PROJECT_SOURCE_DIR}/avrdude.conf" -v -V -patmega328p -carduino "-P/dev/ttyACM0" -b115200 -D "-Uflash:w:${CMAKE_PROJECT_NAME}.hex:i")
