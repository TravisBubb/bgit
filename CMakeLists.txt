cmake_minimum_required(VERSION 3.15)

set( CMAKE_CXX_COMPILER /usr/bin/g++ )
set( CMAKE_C_COMPILER /usr/bin/gcc )

project(bgit)

find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ZLIB::ZLIB)
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)