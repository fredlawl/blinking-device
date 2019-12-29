# Documentation for this file can be found: https://github.com/queezythegreat/arduino-cmake
cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME bdevice-firmware)
project(${PROJECT_NAME})

set(${PROJECT_NAME}_BOARD uno)
set(${PROJECT_NAME}_HDRS instruction.h)
set(${PROJECT_NAME}_SKETCH bdevice-firmware.ino)
set(${PROJECT_NAME}_PROGRAMMER atmel_ice)
set(${PROJECT_NAME}_PORT /dev/cu.usbmodem14201)
set(${PROJECT_NAME}_SERIAL @SERIAL_PORT@)
set(uno.upload.speed 115200)
set(${PROJECT_NAME}_AFLAGS -v)

if (CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions(-DDEBUG=1)
endif()

generate_arduino_firmware(${PROJECT_NAME})
