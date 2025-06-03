cmake_minimum_required(VERSION 3.16)

project(eight_queens LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
if (NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
endif()

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    queens.c
    queens.h
)

add_executable(eight_queens
    ${PROJECT_SOURCES}
)

target_link_libraries(eight_queens PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
) 