project(matrixs LANGUAGES CXX)
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
add_subdirectory(src ../bin/basbin)
add_subdirectory(test ../bin/testbin)
add_subdirectory(testgraph ../bin/testgraph)
add_subdirectory(gui_particle_machine ../bin/gui_particle_machine)

add_subdirectory(langc ../bin/langc)