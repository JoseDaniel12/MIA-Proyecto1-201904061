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
        src/comandos/Mount.cpp src/comandos/Mount.h src/Entidades/Disco.cpp src/Entidades/Disco.h src/comandos/Umount.cpp src/comandos/Umount.h src/comandos/Mkfs.cpp src/comandos/Mkfs.h src/comandos/Rep.cpp src/comandos/Rep.h src/comandos/Exec.cpp src/comandos/Exec.h src/comandos/Usuarios/Login.cpp src/comandos/Usuarios/Login.h src/comandos/Archivos/MkFile.cpp src/comandos/Archivos/MkFile.h src/comandos/Mkdir.cpp src/comandos/Mkdir.h src/comandos/Archivos/Cat.cpp src/comandos/Archivos/Cat.h src/comandos/Pause.cpp src/comandos/Pause.h src/comandos/Reportes/tree.cpp src/comandos/Mkuser.cpp src/comandos/Mkuser.h src/comandos/Mkgrp.cpp src/comandos/Mkgrp.h src/comandos/Logout.cpp src/comandos/Logout.h)
