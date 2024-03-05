cmake_minimum_required(VERSION 3.14)
project(3Dgraph)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        scale.h
        function.h
        complex_function.h
        parameter_function.h
)
add_executable(3Dgraph ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(3Dgraph sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
