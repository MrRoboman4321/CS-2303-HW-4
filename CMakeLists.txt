cmake_minimum_required(VERSION 3.12)
project(CS_2303_HW_4)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(CS_2303_HW_4
        src/Ant.cpp
        src/Ant.h
        src/AntsAndDoodles.cpp
        src/Doodlebug.cpp
        src/Doodlebug.h
        src/Grid.cpp
        src/Grid.h
        src/Organism.cpp
        src/Organism.h
        src/Production.cpp
        src/Production.h
        src/Tests2.cpp
        src/Tests2.h)
