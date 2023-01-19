project(matrixs LANGUAGES CXX)
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(execute1 "1.cpp")
set(execute2 "2.cpp")
set(execute3 "3.cpp")

set(EXECUTABLE_OUTPUT_PATH "../../Debug")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D_CRT_NON_CONFORMING_SWPRINTFS)
add_definitions(-DNOMINMAX)
add_definitions(-DMATRIX_DRL_USE)
add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
add_definitions(-D_SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING)

add_definitions(-D_UNICODE)
add_definitions(-DUNICODE)

add_executable(cppdebug1 ${execute1})
add_executable(cppdebug2 ${execute2})
add_executable(cppdebug3 ${execute3})

target_link_libraries(cppdebug1 basmar)
target_include_directories(
    cppdebug1
    PUBLIC "../include"
    PUBLIC "E:\\VisualStudio\\VC\\Auxiliary\\VS\\include")
target_link_libraries(cppdebug2 basmar)
target_include_directories(
    cppdebug2
    PUBLIC "../include"
    PUBLIC "E:\\VisualStudio\\VC\\Auxiliary\\VS\\include")
target_link_libraries(cppdebug3 basmar)
target_include_directories(
    cppdebug3
    PUBLIC "../include"
    PUBLIC "E:\\VisualStudio\\VC\\Auxiliary\\VS\\include")