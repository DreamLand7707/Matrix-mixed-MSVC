project(matrixs LANGUAGES CXX)
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(execute1 "g1.cpp")
set(execute2 "g2.cpp")
set(execute3 "g3.cpp")
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

add_executable(graphdebug1 ${execute1})
add_executable(graphdebug2 ${execute2})
add_executable(graphdebug3 ${execute3})

target_link_libraries(graphdebug1 baspar)
target_link_libraries(graphdebug1 EasyXw.lib)
target_link_libraries(graphdebug1 gui)
target_include_directories(
    graphdebug1
    PUBLIC "../include"
    PUBLIC "../include/drl_graph"
    PUBLIC "E:/VisualStudio/VC/Auxiliary/VS/include")

target_link_libraries(graphdebug2 baspar)
target_link_libraries(graphdebug2 EasyXw.lib)
target_include_directories(
    graphdebug2
    PUBLIC "../include"
    PUBLIC "../include/drl_graph"
    PUBLIC "E:/VisualStudio/VC/Auxiliary/VS/include")

target_link_libraries(graphdebug3 baspar)
target_link_libraries(graphdebug3 EasyXw.lib)
target_include_directories(
    graphdebug3
    PUBLIC "../include"
    PUBLIC "../include/drl_graph"
    PUBLIC "E:/VisualStudio/VC/Auxiliary/VS/include")