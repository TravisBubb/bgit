cmake_minimum_required(VERSION 3.13)

set( CMAKE_CXX_COMPILER "C:\\ProgramData\\mingw64\\mingw64\\bin\\g++.exe" )
set( CMAKE_C_COMPILER "C:\\ProgramData\\mingw64\\mingw64\\bin\\gcc.exe" )

project(bgit)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

add_executable(bgit ${SOURCE_FILES})