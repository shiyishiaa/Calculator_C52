cmake_minimum_required(VERSION 3.16)
project(Calculator)

set(CMAKE_CXX_STANDARD 14)

set(INC_DIR D:/Keil_v5/C51/INC)
set(ATMEL_INC_DIR D:/Keil_v5/C51/INC/Atmel)
set(LINK_DIR D:/Keil_v5/C51/LIB)

include_directories(${INC_DIR})
include_directories(${ATMEL_INC_DIR})
link_directories(${LINK_DIR})
link_libraries(C51)

add_executable(Calculator Calculator.c)