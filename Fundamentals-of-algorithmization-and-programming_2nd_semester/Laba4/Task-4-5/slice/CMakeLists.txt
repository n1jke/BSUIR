cmake_minimum_required(VERSION 3.20)
project(slice)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_COMPILER clang++)

# all necessary source files
add_library(slice STATIC slice.cpp Iterator.cpp pair.cpp)

# inst rules
install(TARGETS slice DESTINATION lib)
install(FILES slice.h Iterator.h Allocator.h pair.h DESTINATION include)
