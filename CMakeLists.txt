cmake_minimum_required(VERSION 2.8)

project (credid)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
file(GLOB SOURCES credid.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(credid SHARED credid.c)

install(FILES
    credid.h
  DESTINATION
    include
)

install(TARGETS credid
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include)
