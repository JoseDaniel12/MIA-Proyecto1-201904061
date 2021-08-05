cmake_minimum_required(VERSION 3.20)
project(MIA-Proyecto1-201904061)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        MIA-Proyecto1-201904061
        main.cpp
        analizador/scanner.cpp
        analizador/scanner.h
        analizador/parser.cpp
        analizador/parser.h
        Command.cpp
        Command.h
)
