project(matrixs LANGUAGES CXX)
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(lsource "./matrix/lib1.cpp;./matrix/lib2.cpp;./matrix/lib3.cpp;./matrix/lib4.cpp")
set(rsource "gui_signal_module.cpp")
set(casiosource "casio_analy.cpp")
# set(das_binary_tree "./drl_data_structures/")

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
include_directories(../include)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D_CRT_NON_CONFORMING_SWPRINTFS)
add_definitions(-DNOMINMAX)
add_definitions(-DMATRIX_DRL_USE)
add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
add_definitions(-D_SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING)

set(LIBRARY_OUTPUT_PATH "../../lib")

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

add_library(basmar STATIC ${lsource})
add_library(gui STATIC ${rsource})
add_library(drl_casio STATIC ${casiosource})
# add_library(das_binary_tree STATIC ${das_binary_tree})

set(LIBRARY_OUTPUT_PATH "../../lib")

target_include_directories(
    basmar
    PUBLIC "../include"
    PUBLIC "../include/drl_matrix"
    PUBLIC "../include/drl_graph"
    PUBLIC "E:/VisualStudio/VC/Auxiliary/VS/include"
    PUBLIC "../include/drl_particle"
    PUBLIC "../include/drl_data_structures")
target_include_directories(
    gui
    PUBLIC "../include"
    PUBLIC "../include/drl_matrix"
    PUBLIC "../include/drl_graph"
    PUBLIC "E:/VisualStudio/VC/Auxiliary/VS/include"
    PUBLIC "../include/drl_particle"
    PUBLIC "../include/drl_data_structures")
target_include_directories(
    drl_casio
    PUBLIC "../include"
    PUBLIC "../include/drl_matrix"
    PUBLIC "../include/drl_graph"
    PUBLIC "E:/VisualStudio/VC/Auxiliary/VS/include"
    PUBLIC "../include/drl_particle"
    PUBLIC "../include/drl_data_structures")
# target_include_directories(
#     das_binary_tree
#     PUBLIC "../include"
#     PUBLIC "../include/drl_matrix"
#     PUBLIC "../include/drl_graph"
#     PUBLIC "E:/VisualStudio/VC/Auxiliary/VS/include"
#     PUBLIC "../include/drl_particle"
#     PUBLIC "../include/drl_data_structures")

# file(COPY "../lib/libbasmar.a" DESTINATION "D:/Project/VSCode/CMakeMatrixtest")