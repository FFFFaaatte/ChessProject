cmake_minimum_required(VERSION 3.5)

project(chessProject LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

file(
    GLOB HEADER
    include/*.h
    include/*/*.h
)
file(
    GLOB SOURCE
    src/*.cpp
    src/*/*.cpp
)

add_executable(
    chessProject
    main.cpp
    ${SOURCE}
    ${HEADER}
    )
target_link_libraries(chessProject Qt5::Core)
