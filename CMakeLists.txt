cmake_minimum_required(VERSION 2.8)

project (auth-api)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
file(GLOB SOURCES auth-api.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(auth-api SHARED auth-api.c)
