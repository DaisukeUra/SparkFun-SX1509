cmake_minimum_required(VERSION 3.0)
project(sx1509)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lpthread -lpigpiod_if2 -lrt")
add_compile_options(-fPIC)

set(SOURCE_FILES SparkFunSX1509.cpp)
set(DEMO_FILES main.cpp)

link_directories(/usr/local/lib)
include_directories(/usr/local/include) 
add_library(sx1509 STATIC ${SOURCE_FILES})
target_link_libraries(sx1509 pigpiod_if2)

add_executable(sx1509_demo ${DEMO_FILES})
target_link_libraries(sx1509_demo sx1509)
