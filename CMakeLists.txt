cmake_minimum_required(VERSION 3.30)
project(GestionStock C)

set(CMAKE_C_STANDARD 11)

add_executable(GestionStock main.c)

add_subdirectory(src)

target_link_libraries(GestionStock
    stockLib
)
