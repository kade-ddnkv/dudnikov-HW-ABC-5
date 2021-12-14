cmake_minimum_required(VERSION 3.16)
project(ABCproject5)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_RELEASE  "-g -std=c++17 -pthread -O2"
        CACHE STRING "Compiler flags in asan build"
        FORCE)

set(CMAKE_CXX_FLAGS_DEBUG "-g -std=c++17 -pthread -Wall -Werror"
        CACHE STRING "Compiler flags in asan build"
        FORCE)

set(CMAKE_CXX_FLAGS_ASAN "-g -std=c++17 -pthread -Wall -Werror -fsanitize=address,undefined -fno-sanitize-recover=all"
        CACHE STRING "Compiler flags in asan build"
        FORCE)

add_executable(ABCproject5 main.cpp ConveyorWorker.cpp ConveyorWorker.h Doctor.cpp Doctor.h Receptionist.cpp Receptionist.h Person.h Work.cpp Work.h)
