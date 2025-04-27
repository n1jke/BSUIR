cmake_minimum_required(VERSION 3.16)
project(string)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(string SHARED stringg.cpp stringg.h)

# Ensure Position Independent Code for shared library
set_target_properties(string PROPERTIES POSITION_INDEPENDENT_CODE ON)
