cmake_minimum_required(VERSION 3.25)
project(trabalho_2)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 23)

add_executable(trabalho_2
        main.cpp
        src/Builders.cpp
        src/Dominios.cpp
        src/Entidades.cpp
        src/ComandosSQL.cpp
        src/Controladoras.cpp
        src/Telas.cpp
        )

target_link_libraries(trabalho_2 ${CURSES_LIBRARIES} sqlite3)
target_include_directories(trabalho_2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)