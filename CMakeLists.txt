cmake_minimum_required(VERSION 3.0)
project(sx1509)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lwiringPi -lpthread")

#file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/*(.cpp,.cc,.cxx,.hpp,.hxx,.c,.h))
set(SOURCE_FILES main.cpp sx1509_registers.h SparkFunSX1509.h SparkFunSX1509.cpp)
add_executable(sx1509 ${SOURCE_FILES})
