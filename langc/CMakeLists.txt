project(clanguage LANGUAGES C)
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_C_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH "../../Debug")
set(execu1 "1.c")
set(execu2 "2.c")
set(execu3 "3.c")
set(execu4 "4.c")
add_executable(cdebug1 ${execu1})
add_executable(cdebug2 ${execu2})
add_executable(cdebug3 ${execu3})
add_executable(cdebug4 ${execu4})