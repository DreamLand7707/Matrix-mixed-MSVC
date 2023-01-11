project(matrixs LANGUAGES CXX)
set(lsource "lib1.cpp;lib2.cpp;lib3.cpp;lib4.cpp")
set(rsource "gui_signal_module.cpp")
set(casiosource "casio_analy.cpp")

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

set(LIBRARY_OUTPUT_PATH "../../lib")

# file(COPY "../lib/libbasmar.a" DESTINATION "D:/Project/VSCode/CMakeMatrixtest")