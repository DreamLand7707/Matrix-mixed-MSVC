project(matrixs LANGUAGES CXX)
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
add_subdirectory(src ../bin/basbin)

add_subdirectory(test ../bin/testbin)

add_subdirectory(testgraph ../bin/testgraph)