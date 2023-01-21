project(matrixs LANGUAGES CXX)
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(executegui "main.cpp")
set(EXECUTABLE_OUTPUT_PATH "../../Debug")
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D_CRT_NON_CONFORMING_SWPRINTFS)
add_definitions(-DNOMINMAX)
add_definitions(-DMATRIX_DRL_USE)
add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
add_definitions(-D_SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING)

add_definitions(-D_UNICODE)
add_definitions(-DUNICODE)

# add_definitions(-D_DEBUG)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

add_executable(GPM1 ${executegui})

target_link_libraries(GPM1 basmar)
target_link_libraries(GPM1 EasyXw.lib)
target_link_libraries(GPM1 drl_casio)
target_link_libraries(GPM1 gui)
target_include_directories(
    GPM1
    PUBLIC "../include"
    PUBLIC "../include/drl_matrix"
    PUBLIC "../include/drl_graph"
    PUBLIC "E:/VisualStudio/VC/Auxiliary/VS/include"
    PUBLIC "../include/drl_particle")
