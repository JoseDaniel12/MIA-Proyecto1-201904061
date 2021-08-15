cmake_minimum_required(VERSION 3.20)
project(MIA-Proyecto1-201904061)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        MIA-Proyecto1-201904061
        src/main.cpp
        src/analizador/scanner.cpp
        src/analizador/scanner.h
        src/analizador/parser.cpp
        src/analizador/parser.h
        src/comandos/Command.cpp
        src/comandos/Command.h
        src/comandos/Mkdisk.cpp
        src/comandos/Mkdisk.h
        src/comandos/Param.cpp
        src/comandos/Param.h
        src/structs.h
        src/comandos/Rmdisk.cpp
        src/comandos/Rmdisk.h
        src/comandos/Fdisk.cpp
        src/comandos/Fdisk.h
)
