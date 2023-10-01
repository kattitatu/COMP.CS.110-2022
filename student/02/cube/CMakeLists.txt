cmake_minimum_required(VERSION 3.5)

project(cube LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cube main.cpp)

install(TARGETS cube
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
