project(matrixs LANGUAGES CXX)
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(execute1 "1.cpp")
set(execute2 "2.cpp")
set(execute3 "3.cpp")

set(EXECUTABLE_OUTPUT_PATH "../../Debug")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_executable(cppdebug1 ${execute1})
add_executable(cppdebug2 ${execute2})
add_executable(cppdebug3 ${execute3})

target_link_libraries(cppdebug1 baspar)
target_include_directories(
    cppdebug1
    PUBLIC "../include"
    PUBLIC "E:\\VisualStudio\\VC\\Auxiliary\\VS\\include")
target_link_libraries(cppdebug2 baspar)
target_include_directories(
    cppdebug2
    PUBLIC "../include"
    PUBLIC "E:\\VisualStudio\\VC\\Auxiliary\\VS\\include")
target_link_libraries(cppdebug3 baspar)
target_include_directories(
    cppdebug3
    PUBLIC "../include"
    PUBLIC "E:\\VisualStudio\\VC\\Auxiliary\\VS\\include")