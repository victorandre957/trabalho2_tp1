cmake_minimum_required(VERSION 3.25)
project(trabalho_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(trabalho_1
        main.cpp
        src/Dominios.cpp
        src/Entidades.cpp
        src/TestesUnitarios.cpp
        )

target_include_directories(trabalho_1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)